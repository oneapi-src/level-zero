# System Resource Tracker Checker

## Overview

The System Resource Tracker is a Level Zero validation layer checker that monitors both Level Zero API resources and system resources in real-time. It tracks resource allocation and deallocation across all Level Zero API calls that create or destroy resources, providing detailed insights into memory usage, resource lifecycles, and system-level metrics.

**Platform Support:** Linux only. This checker uses `/proc/self/status` for system metrics and is not available on Windows or macOS.

## Features

- **Level Zero Resource Tracking**: Monitors all L0 resources including contexts, command queues, modules, kernels, event pools, command lists, events, fences, images, samplers, and memory allocations
- **System Resource Monitoring**: Tracks real system metrics via `/proc/self/status` including:
  - Virtual memory size (VmSize)
  - Resident set size (VmRSS)
  - Data segment size (VmData)
  - Peak virtual memory (VmPeak)
  - Thread count
  - File descriptor count
- **Delta Tracking**: Calculates resource changes (deltas) for each API call
- **Cumulative Summaries**: Maintains running totals of all resource types
- **CSV Export**: Optionally exports timestamped data for graphing and analysis
- **Per-Process Isolation**: Each process creates a unique output file with PID appended
- **Thread-Safe**: Uses mutex protection for concurrent access
- **Low Overhead**: Minimal performance impact (< 1ms per API call)

## Usage

### Basic Tracking with Debug Logging

Enable the checker to log resource usage to the Level Zero debug log:

```bash
export ZE_ENABLE_VALIDATION_LAYER=1
export ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER=1
export ZEL_ENABLE_LOADER_LOGGING=1
export ZEL_LOADER_LOGGING_LEVEL=debug

# Run your Level Zero application
./my_level_zero_app
```

### CSV Output for Graphing

Set the `ZEL_SYSTEM_RESOURCE_TRACKER_CSV` environment variable to specify the output CSV file path:

```bash
export ZE_ENABLE_VALIDATION_LAYER=1
export ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER=1
export ZEL_SYSTEM_RESOURCE_TRACKER_CSV=tracker_output.csv

# Run your Level Zero application
./my_level_zero_app
```

**Note:** The actual output file will include the process ID (e.g., `tracker_output_pid12345.csv`) to ensure each process creates a unique file. This prevents conflicts when multiple processes use the tracker simultaneously.

## Tracked API Calls

The System Resource Tracker monitors the following Level Zero API functions:

### Context Management
- `zeContextCreate` - Creates L0 context, increments context count

### Command Queue Management
- `zeCommandQueueCreate` - Creates command queue, increments queue count
- `zeCommandQueueDestroy` - Destroys command queue, decrements queue count

### Module and Kernel Management
- `zeModuleCreate` - Creates module from binary, increments module count
- `zeModuleDestroy` - Destroys module, decrements module count
- `zeKernelCreate` - Creates kernel from module, increments kernel count
- `zeKernelDestroy` - Destroys kernel, decrements kernel count

### Event Management
- `zeEventPoolCreate` - Creates event pool, increments pool count
- `zeEventPoolDestroy` - Destroys event pool, decrements pool count
- `zeEventCreate` - Creates event, increments event count
- `zeEventDestroy` - Destroys event, decrements event count

### Command List Management
- `zeCommandListCreate` - Creates regular command list, increments list count
- `zeCommandListCreateImmediate` - Creates immediate command list, increments list count
- `zeCommandListDestroy` - Destroys command list, decrements list count
- `zeCommandListReset` - Resets command list state

### Synchronization
- `zeFenceCreate` - Creates fence, increments fence count
- `zeFenceDestroy` - Destroys fence, decrements fence count

### Image and Sampler Management
- `zeImageCreate` - Creates image, increments image count
- `zeImageDestroy` - Destroys image, decrements image count
- `zeSamplerCreate` - Creates sampler, increments sampler count
- `zeSamplerDestroy` - Destroys sampler, decrements sampler count

### Memory Management
- `zeMemAllocDevice` - Allocates device memory, tracks allocation size and count
- `zeMemAllocHost` - Allocates host memory, tracks allocation size and count
- `zeMemAllocShared` - Allocates shared memory, tracks allocation size and count
- `zeMemFree` - Frees memory, tracks deallocation

### Command List Append Operations
The tracker also monitors all command list append operations to measure memory deltas after each call:

**Memory Operations:**
- `zeCommandListAppendMemoryCopy` - Appends memory copy command
- `zeCommandListAppendMemoryFill` - Appends memory fill command
- `zeCommandListAppendMemoryCopyRegion` - Appends region-based memory copy
- `zeCommandListAppendMemoryCopyFromContext` - Appends cross-context memory copy
- `zeCommandListAppendMemoryPrefetch` - Appends memory prefetch hint
- `zeCommandListAppendMemAdvise` - Appends memory advice hint

**Image Operations:**
- `zeCommandListAppendImageCopy` - Appends image copy command
- `zeCommandListAppendImageCopyRegion` - Appends region-based image copy
- `zeCommandListAppendImageCopyToMemory` - Appends image-to-memory copy
- `zeCommandListAppendImageCopyFromMemory` - Appends memory-to-image copy

**Synchronization:**
- `zeCommandListAppendBarrier` - Appends barrier command
- `zeCommandListAppendMemoryRangesBarrier` - Appends memory ranges barrier
- `zeCommandListAppendSignalEvent` - Appends event signal command
- `zeCommandListAppendWaitOnEvents` - Appends wait on events command
- `zeCommandListAppendEventReset` - Appends event reset command

**Kernel Execution:**
- `zeCommandListAppendLaunchKernel` - Appends kernel launch command
- `zeCommandListAppendLaunchCooperativeKernel` - Appends cooperative kernel launch
- `zeCommandListAppendLaunchKernelIndirect` - Appends indirect kernel launch

**Query Operations:**
- `zeCommandListAppendQueryKernelTimestamps` - Appends kernel timestamp query
- `zeCommandListAppendWriteGlobalTimestamp` - Appends global timestamp write

## Output Format

### Debug Log Output

When logging is enabled, each tracked API call produces output like:

```
[debug] [System Resource Tracker] zeContextCreate: VmSize=1234KB (+10KB) VmRSS=567KB (+5KB) VmData=890KB (+3KB) Threads=4
[debug] Current L0 Resources:
  Contexts: 1, Queues: 0, Modules: 0, Kernels: 0
  EventPools: 0, CommandLists: 0, Events: 0, Fences: 0
  Images: 0, Samplers: 0
  Total Memory: 0 bytes
```

### CSV Format

The CSV file contains the following columns:

| Column | Description |
|--------|-------------|
| `CallNumber` | Sequential call number |
| `TimeMs` | Elapsed time in milliseconds since tracker started |
| `APICall` | Level Zero API function name |
| `VmSize_KB` | Virtual memory size (KB) |
| `VmRSS_KB` | Resident set size (KB) |
| `VmData_KB` | Data segment size (KB) |
| `VmPeak_KB` | Peak virtual memory size (KB) |
| `Threads` | Number of threads |
| `Delta_VmSize_KB` | Change in VmSize since previous call (KB) |
| `Delta_VmRSS_KB` | Change in VmRSS since previous call (KB) |
| `Delta_VmData_KB` | Change in VmData since previous call (KB) |
| `Contexts` | Current number of L0 contexts |
| `CommandQueues` | Current number of L0 command queues |
| `Modules` | Current number of L0 modules |
| `Kernels` | Current number of L0 kernels |
| `EventPools` | Current number of L0 event pools |
| `CommandLists` | Current number of L0 command lists |
| `Events` | Current number of L0 events |
| `Fences` | Current number of L0 fences |
| `Images` | Current number of L0 images |
| `Samplers` | Current number of L0 samplers |
| `TotalMemory_Bytes` | Total L0 memory allocated (bytes) |

## Visualization

### Using the Provided Python Script

A plotting script is provided to automatically generate visualizations:

```bash
# Install required Python packages
pip install pandas matplotlib

# Generate plots
python3 scripts/plot_resource_tracker.py tracker_output.csv
```

This will:
- Display interactive plots showing memory usage, resource counts, and API call distribution
- Save plots to `tracker_output_plot.png`
- Print summary statistics

### Manual Analysis

You can also import the CSV into any data analysis tool:

**Python/Pandas:**
```python
import pandas as pd
df = pd.read_csv('tracker_output.csv')
print(df.describe())
```

**Excel/LibreOffice Calc:**
- Open the CSV file directly
- Create charts using the time series data

**R:**
```r
data <- read.csv('tracker_output.csv')
plot(data$TimeMs, data$VmRSS_KB, type='l')
```

## Example Visualizations

The plotting script generates 9 comprehensive visualizations:

1. **System Memory Usage Over Time** - VmRSS, VmSize, VmData trends
2. **Memory Deltas Per API Call** - Shows which calls increase/decrease memory in MB
3. **L0 Resource Counts** - Tracks contexts, queues, modules, kernels over time
4. **Command Lists and Events** - Monitors command list and event pool usage
5. **Total Memory Allocations** - Shows cumulative L0 memory allocations in MB
6. **Top 10 Most Frequent API Calls** - Bar chart sorted by call frequency
7. **Top 10 API Calls by Memory Impact** - Total memory delta in MB per API type
8. **Top 10 API Calls by Avg Memory per Call** - Average memory delta in MB per call
9. **Cumulative Memory Impact by Top 5 APIs** - Memory trends over time for highest-impact APIs

### Example Plot

![Example System Resource Tracker Plot](example_system_resource_tracker_plot.png)

The example above shows a typical visualization with all 9 plots displaying memory usage patterns, resource lifecycle, and API call analysis. Command list append operations that have high memory deltas will automatically appear in plots 7, 8, and 9.

## Use Cases

- **Performance Analysis**: Identify memory leaks or excessive allocations
- **Resource Optimization**: Track resource lifecycle and identify unused resources
- **Debugging**: Correlate application behavior with resource usage patterns
- **Benchmarking**: Compare resource usage across different runs or code versions
- **CI/CD Integration**: Automated tracking of resource usage in test pipelines
- **Capacity Planning**: Understand peak resource requirements for production workloads
- **Regression Testing**: Detect unexpected increases in resource consumption

## Implementation Details

### Architecture

The System Resource Tracker is implemented as a validation layer checker that uses epilogue intercepts. When enabled, the validation layer injects calls to the tracker's epilogue functions after each tracked API call completes.

**Key Components:**
- `SystemResourceMetrics`: Structure holding system-level metrics (VmSize, VmRSS, etc.)
- `ResourceTracker`: Singleton-like structure maintaining cumulative resource counts and metrics
- `getSystemResourceMetrics()`: Parses `/proc/self/status` to read current system metrics
- `writeCsvData()`: Atomic CSV line writer using ostringstream
- `logResourceSummary()`: Formats and logs cumulative resource usage
- Epilogue functions: 27 functions corresponding to tracked API calls

### Thread Safety

The tracker uses a mutex to protect shared state:
- All epilogue functions acquire the mutex before accessing shared state
- CSV writes are performed atomically using ostringstream to build complete lines
- The mutex is released after completing all tracking operations

### Performance Considerations

- Tracking overhead is approximately < 1ms per API call
- System metrics are read by parsing a small text file (`/proc/self/status` on Linux)
- CSV writes are buffered and flushed after each call to ensure crash safety
- The tracker only runs when explicitly enabled via environment variable

### Platform Support

The System Resource Tracker is **Linux-only** and relies on `/proc/self/status` for system resource metrics. The checker is automatically excluded from builds on Windows and macOS.

## Troubleshooting

### CSV Parsing Errors

If you encounter `pandas.errors.ParserError` with messages like "Expected X fields, saw Y", this indicates corrupted CSV data. This can happen if:

1. The CSV file was generated by an older version with a data race bug (fixed in current version)
2. The application crashed during a write operation

**Solution**: Generate a new CSV file with the current version of the tracker, which uses:
- Atomic line writes to prevent data corruption
- Unique filenames per process (with PID appended) to prevent conflicts

## Notes

- Each process creates a unique CSV file with the process ID appended (e.g., `tracker_pid12345.csv`)
- CSV output is flushed after each API call to ensure data is captured even if the application crashes
- The tracker uses atomic line writes to prevent data corruption in multi-threaded applications
- The tracker adds minimal overhead (< 1ms per API call)
- CSV files can grow large for long-running applications; consider log rotation for production use
- Both CSV output and debug logging can be enabled simultaneously
