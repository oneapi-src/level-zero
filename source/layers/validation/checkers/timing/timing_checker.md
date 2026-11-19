# Timing Checker

The Timing Checker is a validation-layer mode that measures the host-side (CPU)
duration of every Level Zero API call and reports per-API statistics. It is
useful for spotting which API calls dominate host time in an application and for
comparing host overhead across runs.

## What it measures

For every API the checker takes a high-resolution monotonic timestamp when the
call enters the validation layer (Prologue) and again when it returns
(Epilogue). The difference is the host-side duration of that call. Per API it
accumulates:

- **Calls** - number of times the API was called
- **Total** - sum of all host durations (ns)
- **Min** / **Max** - fastest and slowest single call (ns)
- **Avg** - Total / Calls (ns)

The clock is `QueryPerformanceCounter` on Windows and
`clock_gettime(CLOCK_MONOTONIC_RAW)` on other platforms.

## How to enable

The Timing Checker runs inside the validation layer, so the validation layer must
be enabled. Its output is written directly to `stderr`, so the loader logging
variables (`ZEL_ENABLE_LOADER_LOGGING`, `ZEL_LOADER_LOGGING_LEVEL`,
`ZEL_LOADER_LOG_CONSOLE`) are **not** required.

```bash
export ZE_ENABLE_VALIDATION_LAYER=1     # turn the validation layer on
export ZEL_ENABLE_TIMING_CHECKER=1      # enable the Timing Checker

./your_level_zero_application
```

On Windows set the same variables with `set` instead of `export`.

## Output modes

The three modes are independent and can be combined. All output goes to `stderr`.

| Environment Variable | Default | Effect |
|---|---|---|
| `ZEL_ENABLE_TIMING_CHECKER` | `0` | Enable the checker; a per-API summary table is printed at teardown |
| `ZEL_TIMING_CHECKER_CSV` | (unset) | Path to also export the per-API statistics as CSV |
| `ZEL_TIMING_CHECKER_LIVE` | `0` | Also print every individual call's duration as it happens |

### 1. Summary table (default when enabled)

Printed to `stderr` at process teardown. Rows are sorted by `%`, each API's
share of total host time, highest first:

```
==== Level Zero Host API Timing (ns) ====
Function                                       Calls           Total           Min           Max           Avg        %
zeInitDrivers                                      2        65581869           666      65581203      32790934   95.84%
zeCommandListCreateImmediate                       1         2783378       2783378       2783378       2783378    4.07%
zeCommandListAppendSignalEvent                     1         1928777       1928777       1928777       1928777    2.82%
zeDeviceGetMemoryProperties                        2           51819           718         51101         25909    0.08%
zeContextCreate                                    1            4219          4219          4219          4219    0.01%
zeDeviceGet                                        2             682           198           484           341    0.00%
```

### 2. CSV export (`ZEL_TIMING_CHECKER_CSV`)

```bash
export ZEL_TIMING_CHECKER_CSV=timing.csv
```

The process id is appended to the filename so concurrent processes do not
overwrite each other (for example `timing_2449615.csv`). One row per API, sorted
by `%` (share of total host time) descending. The `%` column is a percentage value:

```csv
Function,Calls,TotalNs,MinNs,MaxNs,AvgNs,%
zeInitDrivers,2,65581869,666,65581203,32790934,95.84
zeCommandListCreateImmediate,1,2783378,2783378,2783378,2783378,4.07
zeContextCreate,1,4219,4219,4219,4219,0.01
```

### 3. Live per-call logging (`ZEL_TIMING_CHECKER_LIVE`)

```bash
export ZEL_TIMING_CHECKER_LIVE=1
```

Each call is printed to `stderr` as it completes (verbose):

```
[timing] zeInitDrivers 66196062 ns
[timing] zeDeviceGet 566 ns
[timing] zeDeviceGetProperties 1301 ns
```

## Interpreting results

- The measured span includes the underlying driver call plus the small overhead
  of any other validation handlers, so it is best used for relative comparison
  (which APIs cost the most, run-to-run deltas) rather than as an absolute
  driver-only timing.
- First-call costs such as `zeInit` / `zeInitDrivers` are typically much larger
  than steady-state calls because they perform one-time driver initialization.

## Platform support

Linux and Windows. The checker has no external dependencies and works with any
Level Zero driver, including the null driver used by the loader tests.
