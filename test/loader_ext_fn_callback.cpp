/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "loader/ze_loader.h"
#include "layers/zel_tracing_api.h"
#include "ze_api.h"

#include <cstdint>

namespace {

// Signature of the sample extension function exposed by the null driver.
typedef ze_result_t (ZE_APICALL *pfnSampleExtFunc_t)(
    ze_driver_handle_t, uint32_t, uint32_t*);

constexpr uintptr_t kInstanceSentinel = 0xABCD1234u;

// State the prologue/epilogue callbacks record into, reached via pTracerUserData
// (the tracer's pUserData set at zelTracerCreate time).
struct CallbackState {
  int prologCount = 0;
  int epilogCount = 0;
  void* prologUserData = nullptr;
  void* epilogUserData = nullptr;
  ze_result_t epilogResult = ZE_RESULT_FORCE_UINT32;
  uintptr_t instanceValueSeenInEpilog = 0;
  bool prologRanBeforeEpilog = false;
};

void ZE_APICALL prologueCb(void* /*pParams*/, ze_result_t /*result*/,
                           void* pTracerUserData, void** ppTracerInstanceUserData) {
  auto* s = static_cast<CallbackState*>(pTracerUserData);
  s->prologCount++;
  s->prologUserData = pTracerUserData;
  *ppTracerInstanceUserData = reinterpret_cast<void*>(kInstanceSentinel);
}

void ZE_APICALL epilogueCb(void* /*pParams*/, ze_result_t result,
                           void* pTracerUserData, void** ppTracerInstanceUserData) {
  auto* s = static_cast<CallbackState*>(pTracerUserData);
  s->epilogCount++;
  s->epilogUserData = pTracerUserData;
  s->epilogResult = result;
  s->prologRanBeforeEpilog = (s->prologCount == 1);
  s->instanceValueSeenInEpilog =
      reinterpret_cast<uintptr_t>(*ppTracerInstanceUserData);
}

ze_driver_handle_t getFirstDriver() {
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  uint32_t count = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&count, nullptr));
  EXPECT_GT(count, 0u);
  count = 1;
  ze_driver_handle_t hDriver = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&count, &hDriver));
  EXPECT_NE(nullptr, hDriver);
  return hDriver;
}

pfnSampleExtFunc_t getSampleExtFunc(ze_driver_handle_t hDriver) {
  void* addr = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zeDriverGetExtensionFunctionAddress(hDriver, "zeSampleExtFunc", &addr));
  EXPECT_NE(nullptr, addr);
  return reinterpret_cast<pfnSampleExtFunc_t>(addr);
}

// Creates a disabled tracer whose pUserData is delivered to the callbacks.
zel_tracer_handle_t createTracer(void* pUserData) {
  zel_tracer_desc_t desc = {};
  desc.stype = ZEL_STRUCTURE_TYPE_TRACER_DESC;
  desc.pUserData = pUserData;
  zel_tracer_handle_t hTracer = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerCreate(&desc, &hTracer));
  EXPECT_NE(nullptr, hTracer);
  return hTracer;
}

// Registers both prologue and epilogue for a named extension function.
void registerCbs(zel_tracer_handle_t hTracer, ze_driver_handle_t hDriver,
                 const char* name) {
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, name, ZEL_REGISTER_PROLOGUE, prologueCb));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, name, ZEL_REGISTER_EPILOGUE, epilogueCb));
}

// Disables and destroys a tracer (destroy requires the disabled state).
void teardownTracer(zel_tracer_handle_t hTracer) {
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, false));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDestroy(hTracer));
}

// ---------------------------------------------------------------------------
// Dynamic control suite: tracing is toggled at runtime via
// zelEnableTracingLayer/zelDisableTracingLayer (no ZE_ENABLE_TRACING_LAYER env).
// Each test balances enable/disable and destroys its tracer so process state
// stays clean.
// ---------------------------------------------------------------------------

TEST(ExtFnCallback, PrologueAndEpilogueFireOnCall) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 21, &out));

  EXPECT_EQ(42u, out);
  EXPECT_EQ(1, state.prologCount);
  EXPECT_EQ(1, state.epilogCount);
  EXPECT_EQ(&state, state.prologUserData);
  EXPECT_EQ(&state, state.epilogUserData);
  EXPECT_TRUE(state.prologRanBeforeEpilog);
  EXPECT_EQ(ZE_RESULT_SUCCESS, state.epilogResult);
  EXPECT_EQ(kInstanceSentinel, state.instanceValueSeenInEpilog);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

TEST(ExtFnCallback, RegisterBeforeFetchStillFires) {
  auto hDriver = getFirstDriver();

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);
  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 5, &out));

  EXPECT_EQ(10u, out);
  EXPECT_EQ(1, state.prologCount);
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

TEST(ExtFnCallback, UnregisterStopsCallbacks) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  // Clear both slots (null callback) while still disabled.
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, nullptr));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE, nullptr));

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 7, &out));

  EXPECT_EQ(14u, out);
  EXPECT_EQ(0, state.prologCount);
  EXPECT_EQ(0, state.epilogCount);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

TEST(ExtFnCallback, UnknownFunctionNameNeverFires) {
  auto hDriver = getFirstDriver();

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeNeverImplementedExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);
  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 3, &out));

  EXPECT_EQ(6u, out);
  EXPECT_EQ(0, state.prologCount);
  EXPECT_EQ(0, state.epilogCount);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

TEST(ExtFnCallback, NullArgumentsReturnErrors) {
  auto hDriver = getFirstDriver();

  CallbackState state;
  auto hTracer = createTracer(&state);

  EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE,
            zelTracerDriverExtensionRegisterCallback(
                nullptr, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, prologueCb));
  EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, nullptr, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, prologueCb));
  EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_POINTER,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, nullptr, ZEL_REGISTER_PROLOGUE, prologueCb));

  teardownTracer(hTracer);
}

// Registration is only permitted while the tracer is disabled.
TEST(ExtFnCallback, RegisterWhileEnabledIsRejected) {
  auto hDriver = getFirstDriver();

  CallbackState state;
  auto hTracer = createTracer(&state);
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  EXPECT_EQ(ZE_RESULT_ERROR_INVALID_ARGUMENT,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, prologueCb));

  teardownTracer(hTracer);
}

// Two-level gate: registered + tracer enabled but tracing layer NOT enabled
// (driver gate closed) -> must not fire.
TEST(ExtFnCallback, NotEnabledDoesNotFire) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 9, &out));

  EXPECT_EQ(18u, out);              // body runs
  EXPECT_EQ(0, state.prologCount);  // gate closed -> no callbacks
  EXPECT_EQ(0, state.epilogCount);

  teardownTracer(hTracer);
}

// Disabling the tracing layer stops callbacks even while still registered.
TEST(ExtFnCallback, DisableStopsCallbacks) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 1, &out));
  EXPECT_EQ(1, state.prologCount);  // fires while enabled

  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 1, &out));
  EXPECT_EQ(1, state.prologCount);  // no additional fire after disable
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
}

// Multiple tracers registered for the same function stack: all fire on one call.
// This is the capability the tracer-based design adds over the old per-driver
// last-writer-wins registry.
TEST(ExtFnCallback, MultipleTracersStack) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState s1;
  CallbackState s2;
  auto hTracer1 = createTracer(&s1);
  auto hTracer2 = createTracer(&s2);
  registerCbs(hTracer1, hDriver, "zeSampleExtFunc");
  registerCbs(hTracer2, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer1, true));
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer2, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 11, &out));

  EXPECT_EQ(22u, out);
  EXPECT_EQ(1, s1.prologCount);
  EXPECT_EQ(1, s1.epilogCount);
  EXPECT_EQ(1, s2.prologCount);
  EXPECT_EQ(1, s2.epilogCount);
  EXPECT_EQ(kInstanceSentinel, s1.instanceValueSeenInEpilog);
  EXPECT_EQ(kInstanceSentinel, s2.instanceValueSeenInEpilog);

  teardownTracer(hTracer1);
  teardownTracer(hTracer2);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// Exercises the driver-side install refcount that gates the single loader wrapper
// shared by every tracer on a (driver, function) pair. The refcount is a single
// count per (driver, function) - it counts distinct tracers holding at least one
// callback for it, not prologue/epilogue separately. Two tracers register the
// same function; when one unregisters (2->1) the wrapper must stay installed so
// the surviving tracer keeps firing, and only the last unregister (1->0) tears it
// down. The surviving tracer's callbacks are the observable proof that the shared
// wrapper was not removed early.
TEST(ExtFnCallback, MultipleTracersRefcount) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState s1;
  CallbackState s2;
  auto hTracer1 = createTracer(&s1);
  auto hTracer2 = createTracer(&s2);

  // 0->1 then 1->2: both tracers reference the same function's single wrapper.
  registerCbs(hTracer1, hDriver, "zeSampleExtFunc");
  registerCbs(hTracer2, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer1, true));
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer2, true));

  // Baseline: both tracers fire through the single shared wrapper.
  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 11, &out));
  EXPECT_EQ(22u, out);
  EXPECT_EQ(1, s1.prologCount);
  EXPECT_EQ(1, s1.epilogCount);
  EXPECT_EQ(1, s2.prologCount);
  EXPECT_EQ(1, s2.epilogCount);

  // 2->1: unregister tracer1 (registration requires the disabled state). The
  // wrapper must remain installed because tracer2 still holds a reference.
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer1, false));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer1, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, nullptr));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer1, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE, nullptr));

  // The surviving tracer must still fire; tracer1 must not. This is the key
  // regression check: a broken refcount that uninstalled at 2->1 would silently
  // stop tracer2 from firing (the driver would no longer see the wrapper).
  out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 12, &out));
  EXPECT_EQ(24u, out);
  EXPECT_EQ(1, s1.prologCount);  // unchanged - tracer1 unregistered
  EXPECT_EQ(1, s1.epilogCount);
  EXPECT_EQ(2, s2.prologCount);  // fired again through the still-installed wrapper
  EXPECT_EQ(2, s2.epilogCount);

  // 1->0: unregister the last tracer - the wrapper is now uninstalled and no
  // callback fires for either tracer.
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer2, false));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer2, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE, nullptr));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer2, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE, nullptr));

  out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 13, &out));
  EXPECT_EQ(26u, out);
  EXPECT_EQ(1, s1.prologCount);
  EXPECT_EQ(2, s2.prologCount);

  teardownTracer(hTracer1);
  teardownTracer(hTracer2);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// Prologue-only install: the app registers just a prologue, so only the prologue
// trampoline is installed on the driver (the epilogue slot stays null). The
// prologue must fire and the epilogue must never fire. This exercises the
// split-refcount fast path where no per-call instance frame is built because no
// epilogue is installed to consume it.
TEST(ExtFnCallback, PrologueOnlyFires) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE,
                prologueCb));

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 8, &out));

  EXPECT_EQ(16u, out);
  EXPECT_EQ(1, state.prologCount);
  EXPECT_EQ(0, state.epilogCount);  // no epilogue installed

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// Epilogue-only install: the app registers just an epilogue, so only the epilogue
// trampoline is installed on the driver (the prologue slot stays null). The
// epilogue must fire. Because no prologue ran, there is no instance frame, so the
// epilogue self-gathers from the active tracers and sees a null instance value.
TEST(ExtFnCallback, EpilogueOnlyFires) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE,
                epilogueCb));

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 9, &out));

  EXPECT_EQ(18u, out);
  EXPECT_EQ(0, state.prologCount);  // no prologue installed
  EXPECT_EQ(1, state.epilogCount);
  EXPECT_EQ(ZE_RESULT_SUCCESS, state.epilogResult);
  EXPECT_EQ(0u, state.instanceValueSeenInEpilog);  // no frame -> null instance

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// Per-phase refcount independence: one tracer supplies only the prologue and a
// different tracer supplies only the epilogue. Both phase trampolines end up
// installed on the driver from different sources, and both callbacks fire on a
// single call. Removing the prologue tracer's callback (prologue 1->0) must not
// disturb the epilogue tracer, whose epilogue keeps firing via the self-gather
// path - proving the two install refcounts are tracked independently.
TEST(ExtFnCallback, PerPhaseRefcountAcrossTracers) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState sProlog;
  CallbackState sEpilog;
  auto hTracerProlog = createTracer(&sProlog);
  auto hTracerEpilog = createTracer(&sEpilog);

  // Prologue phase 0->1 from tracerProlog; epilogue phase 0->1 from tracerEpilog.
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracerProlog, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE,
                prologueCb));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracerEpilog, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE,
                epilogueCb));

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracerProlog, true));
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracerEpilog, true));

  // Both phases installed (from different tracers): each fires once.
  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 10, &out));
  EXPECT_EQ(20u, out);
  EXPECT_EQ(1, sProlog.prologCount);
  EXPECT_EQ(0, sProlog.epilogCount);
  EXPECT_EQ(0, sEpilog.prologCount);
  EXPECT_EQ(1, sEpilog.epilogCount);

  // Prologue 1->0: remove the prologue tracer's callback. The epilogue refcount
  // is untouched, so the epilogue trampoline must remain installed.
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracerProlog, false));
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracerProlog, hDriver, "zeSampleExtFunc", ZEL_REGISTER_PROLOGUE,
                nullptr));

  out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 15, &out));
  EXPECT_EQ(30u, out);
  EXPECT_EQ(1, sProlog.prologCount);  // unchanged - prologue uninstalled
  EXPECT_EQ(2, sEpilog.epilogCount);  // epilogue still installed and firing

  teardownTracer(hTracerProlog);
  teardownTracer(hTracerEpilog);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// Underflow guard: a disable with no matching enable must be a safe no-op. If
// the unsigned counter had underflowed, the subsequent enable would not detect
// the 0->1 edge, the driver gate would never open, and the callback would not
// fire - so a passing "fires" assertion proves no corruption occurred.
TEST(ExtFnCallback, DisableWithoutEnableIsSafe) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  // Counter is 0 here (all prior tests balanced). Extra disables must no-op.
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");

  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 2, &out));
  EXPECT_EQ(1, state.prologCount);  // enable's 0->1 edge still worked
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// ---------------------------------------------------------------------------
// Environment suite: run with ZE_ENABLE_TRACING_LAYER=1 (separate ctest entry).
// The driver gate is opened at init; the app never calls zelEnableTracingLayer,
// and per documented behavior it stays enabled for the whole process.
// ---------------------------------------------------------------------------

TEST(ExtFnCallbackEnviron, EnvKeepsTracingEnabled) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  // No zelEnableTracingLayer call: the driver gate was opened at init.
  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 4, &out));

  EXPECT_EQ(8u, out);
  EXPECT_EQ(1, state.prologCount);
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
}

// A spurious disable under static enablement must not turn tracing off (sticky
// env) and must not corrupt state (underflow guard).
TEST(ExtFnCallbackEnviron, EnvDisableIsNoOp) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());  // counter 0 -> no-op

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 6, &out));

  EXPECT_EQ(12u, out);
  EXPECT_EQ(1, state.prologCount);  // still fires: env-enabled tracing is sticky
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
}

// ---------------------------------------------------------------------------
// Unsupported-driver suite: run with ZE_ENABLE_TRACING_LAYER=1 AND
// ZEL_TEST_NULL_DRIVER_TRACING_UNSUPPORTED=1 (separate ctest entry). The driver
// advertises "zelDriverEnableTracing" (the symbol resolves), but its
// implementation returns ZE_RESULT_ERROR_UNSUPPORTED_FEATURE - i.e. presence of
// the hook does not imply support. The loader's load-time capability probe must
// therefore treat the driver as unsupported (leaving its cached gate hook null)
// and never open the gate, so extension callbacks never fire even though the
// tracing layer is enabled and callbacks are registered. The extension function
// itself still works normally.
// ---------------------------------------------------------------------------

TEST(ExtFnCallbackUnsupported, StubDriverNeverFiresCallbacks) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));

  uint32_t out = 0;
  // The extension function still succeeds and performs its work...
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 5, &out));
  EXPECT_EQ(10u, out);

  // ...but because the driver reported the gate hook as unsupported, the probe
  // left the cached hook null and the gate was never opened, so no prologue or
  // epilogue ever fired.
  EXPECT_EQ(0, state.prologCount);
  EXPECT_EQ(0, state.epilogCount);

  teardownTracer(hTracer);
}

// ---------------------------------------------------------------------------
// Lazy-gate suite: proves the tracing-layer enable path skips the per-driver
// extension-tracing gate while no extension callback is registered, and opens
// it lazily on the first registration (install-after-enable ordering). Runs as
// its own ctest process so the process-wide monotonic "any callback registered"
// latch starts clear - no other ExtFnCallback test may share this process.
// ---------------------------------------------------------------------------

typedef ze_result_t (ZE_APICALL *pfnGetEnableCount_t)(ze_driver_handle_t, uint32_t*);

pfnGetEnableCount_t getEnableCountFunc(ze_driver_handle_t hDriver) {
  void* addr = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zeDriverGetExtensionFunctionAddress(
                hDriver, "zelTestGetDriverTracingEnableCount", &addr));
  EXPECT_NE(nullptr, addr);
  return reinterpret_cast<pfnGetEnableCount_t>(addr);
}

TEST(ExtFnCallbackLazyGate, LayerEnableSkipsGateUntilRegister) {
  auto hDriver = getFirstDriver();
  auto fn = getSampleExtFunc(hDriver);
  ASSERT_NE(nullptr, fn);
  auto getCount = getEnableCountFunc(hDriver);

  // Fresh process: the loader has never opened this driver's gate.
  uint32_t count = 999;
  ASSERT_EQ(ZE_RESULT_SUCCESS, getCount(hDriver, &count));
  ASSERT_EQ(0u, count);

  // Enable the tracing layer with NO extension callback registered. The
  // optimization must skip the per-driver enable loop, so the driver's gate is
  // never toggled (without it, the loop would open the gate here -> count 1).
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelEnableTracingLayer());
  ASSERT_EQ(ZE_RESULT_SUCCESS, getCount(hDriver, &count));
  EXPECT_EQ(0u, count) << "enable loop ran despite no registered ext callback";

  // Register a callback AFTER the layer was enabled. The install-after-enable
  // path must now open the driver gate (0->1 latch transition) exactly once.
  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc");
  ASSERT_EQ(ZE_RESULT_SUCCESS, getCount(hDriver, &count));
  EXPECT_EQ(1u, count) << "registration did not open the gate after enable";

  // End-to-end: the callback fires even though it was registered after enable.
  ASSERT_EQ(ZE_RESULT_SUCCESS, zelTracerSetEnabled(hTracer, true));
  uint32_t out = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, 6, &out));
  EXPECT_EQ(12u, out);
  EXPECT_EQ(1, state.prologCount);
  EXPECT_EQ(1, state.epilogCount);

  teardownTracer(hTracer);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelDisableTracingLayer());
}

// ---------------------------------------------------------------------------
// Destroy-cleanup suite: proves that destroying a tracer releases its share of
// the driver-side extension-wrapper install refcounts (so a destroyed tracer no
// longer forces the wrapper installed), while co-registered tracers on the same
// function keep theirs. Install state is toggled purely by register/destroy
// (independent of the layer enable), so these run without enabling tracing.
// ---------------------------------------------------------------------------

typedef ze_result_t (ZE_APICALL *pfnGetInstallState_t)(ze_driver_handle_t,
                                                       const char*, uint32_t*);

pfnGetInstallState_t getInstallStateFunc(ze_driver_handle_t hDriver) {
  void* addr = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zeDriverGetExtensionFunctionAddress(
                hDriver, "zelTestGetDriverExtensionInstallState", &addr));
  EXPECT_NE(nullptr, addr);
  return reinterpret_cast<pfnGetInstallState_t>(addr);
}

uint32_t installState(pfnGetInstallState_t fn, ze_driver_handle_t hDriver) {
  uint32_t flags = 0xFFu;
  EXPECT_EQ(ZE_RESULT_SUCCESS, fn(hDriver, "zeSampleExtFunc", &flags));
  return flags;
}

void registerEpilogueOnly(zel_tracer_handle_t hTracer,
                          ze_driver_handle_t hDriver) {
  EXPECT_EQ(ZE_RESULT_SUCCESS,
            zelTracerDriverExtensionRegisterCallback(
                hTracer, hDriver, "zeSampleExtFunc", ZEL_REGISTER_EPILOGUE,
                epilogueCb));
}

TEST(ExtFnCallbackDestroyCleanup, DestroyReleasesInstallWithoutUnregister) {
  auto hDriver = getFirstDriver();
  auto getState = getInstallStateFunc(hDriver);

  ASSERT_EQ(0u, installState(getState, hDriver)) << "stale install at start";

  CallbackState state;
  auto hTracer = createTracer(&state);
  registerCbs(hTracer, hDriver, "zeSampleExtFunc"); // prologue + epilogue
  EXPECT_EQ(0x3u, installState(getState, hDriver))
      << "both phases should be installed after registration";

  // Destroy WITHOUT explicitly clearing the callbacks: destroy must release the
  // driver-side install so the wrapper is fully removed.
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDestroy(hTracer));
  EXPECT_EQ(0u, installState(getState, hDriver))
      << "destroy leaked the driver-side extension install";
}

TEST(ExtFnCallbackDestroyCleanup, DestroyKeepsCoRegisteredTracerInstalled) {
  auto hDriver = getFirstDriver();
  auto getState = getInstallStateFunc(hDriver);

  ASSERT_EQ(0u, installState(getState, hDriver)) << "stale install at start";

  CallbackState s1, s2;
  auto hTracer1 = createTracer(&s1);
  auto hTracer2 = createTracer(&s2);
  registerEpilogueOnly(hTracer1, hDriver);
  registerEpilogueOnly(hTracer2, hDriver);
  EXPECT_EQ(0x2u, installState(getState, hDriver))
      << "epilogue wrapper should be installed for two tracers";

  // Destroying one co-registered tracer must NOT uninstall the shared wrapper.
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDestroy(hTracer1));
  EXPECT_EQ(0x2u, installState(getState, hDriver))
      << "destroy removed a wrapper another tracer still holds";

  // Destroying the last holder releases it.
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelTracerDestroy(hTracer2));
  EXPECT_EQ(0u, installState(getState, hDriver))
      << "last destroy did not release the wrapper";
}

}  // namespace
