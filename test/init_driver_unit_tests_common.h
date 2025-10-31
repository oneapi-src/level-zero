/*
 * Copyright (C) 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "gtest/gtest.h"
#include "source/loader/ze_loader_internal.h"
#include "ze_api.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>

class InitDriverUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        if (!loader::context) {
            loader::context = new loader::context_t();
            loader::context->debugTraceEnabled = false;
        }
    }
};