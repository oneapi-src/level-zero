"""
 Copyright (C) 2025 Intel Corporation

 SPDX-License-Identifier: MIT

"""
#!/usr/bin/env python3
"""
Plot system resource tracking data from Level Zero resource tracker CSV output.

Usage:
    python3 plot_resource_tracker.py <csv_file>

Example:
    export ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER=1
    export ZEL_SYSTEM_RESOURCE_TRACKER_CSV=tracker_output.csv
    export ZEL_ENABLE_LOADER_LOGGING=1
    export ZEL_LOADER_LOGGING_LEVEL=debug
    ./my_level_zero_app
    python3 plot_resource_tracker.py tracker_output.csv
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path

def plot_resource_tracker(csv_file):
    """Plot resource tracking data from CSV file."""
    
    # Read CSV file
    df = pd.read_csv(csv_file)
    
    # Convert time from milliseconds to seconds
    df['TimeSec'] = df['TimeMs'] / 1000.0
    
    # Create figure with multiple subplots
    fig, axes = plt.subplots(3, 3, figsize=(18, 12))
    fig.suptitle(f'Level Zero System Resource Tracking\n{Path(csv_file).name}', fontsize=16)
    
    # Plot 1: Memory Usage Over Time (VmRSS, VmSize, VmData)
    ax1 = axes[0, 0]
    ax1.plot(df['TimeSec'], df['VmRSS_KB'], label='VmRSS', linewidth=2)
    ax1.plot(df['TimeSec'], df['VmSize_KB'], label='VmSize', linewidth=2, alpha=0.7)
    ax1.plot(df['TimeSec'], df['VmData_KB'], label='VmData', linewidth=2, alpha=0.7)
    ax1.set_xlabel('Time (s)')
    ax1.set_ylabel('Memory (KB)')
    ax1.set_title('System Memory Usage Over Time')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    
    # Plot 2: Memory Deltas (showing per-call changes)
    ax2 = axes[0, 1]
    ax2.plot(df['TimeSec'], df['Delta_VmRSS_KB'] / 1024, label='Delta VmRSS', linewidth=1.5)
    ax2.plot(df['TimeSec'], df['Delta_VmSize_KB'] / 1024, label='Delta VmSize', linewidth=1.5, alpha=0.7)
    ax2.axhline(y=0, color='black', linestyle='--', linewidth=0.5)
    ax2.set_xlabel('Time (s)')
    ax2.set_ylabel('Memory Change (MB)')
    ax2.set_title('Memory Deltas Per API Call')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    # Plot 3: Level Zero Resource Counts
    ax3 = axes[1, 0]
    if df['Contexts'].max() > 0:
        ax3.plot(df['TimeSec'], df['Contexts'], label='Contexts', linewidth=2)
    if df['CommandQueues'].max() > 0:
        ax3.plot(df['TimeSec'], df['CommandQueues'], label='CommandQueues', linewidth=2)
    if df['Modules'].max() > 0:
        ax3.plot(df['TimeSec'], df['Modules'], label='Modules', linewidth=2)
    if df['Kernels'].max() > 0:
        ax3.plot(df['TimeSec'], df['Kernels'], label='Kernels', linewidth=2)
    ax3.set_xlabel('Time (s)')
    ax3.set_ylabel('Resource Count')
    ax3.set_title('L0 Resource Counts (Contexts, Queues, Modules, Kernels)')
    ax3.legend()
    ax3.grid(True, alpha=0.3)
    
    # Plot 4: Command Lists and Event Resources
    ax4 = axes[1, 1]
    if df['CommandLists'].max() > 0:
        ax4.plot(df['TimeSec'], df['CommandLists'], label='CommandLists', linewidth=2)
    if df['EventPools'].max() > 0:
        ax4.plot(df['TimeSec'], df['EventPools'], label='EventPools', linewidth=2)
    if df['Events'].max() > 0:
        ax4.plot(df['TimeSec'], df['Events'], label='Events', linewidth=2)
    if df['Fences'].max() > 0:
        ax4.plot(df['TimeSec'], df['Fences'], label='Fences', linewidth=2)
    ax4.set_xlabel('Time (s)')
    ax4.set_ylabel('Resource Count')
    ax4.set_title('L0 Command Lists and Events')
    ax4.legend()
    ax4.grid(True, alpha=0.3)
    
    # Plot 5: Total Memory Allocations
    ax5 = axes[2, 0]
    ax5.plot(df['TimeSec'], df['TotalMemory_Bytes'] / (1024*1024), label='Total Memory', 
             linewidth=2, color='red')
    ax5.set_xlabel('Time (s)')
    ax5.set_ylabel('Memory (MB)')
    ax5.set_title('Total L0 Memory Allocations')
    ax5.legend()
    ax5.grid(True, alpha=0.3)
    
    # Plot 6: API Call Distribution (top 10 most frequent)
    ax6 = axes[2, 1]
    api_counts = df['APICall'].value_counts().head(10).sort_values(ascending=True)
    api_counts.plot(kind='barh', ax=ax6, color='steelblue')
    ax6.set_xlabel('Call Count')
    ax6.set_title('Top 10 Most Frequent API Calls')
    ax6.grid(True, alpha=0.3, axis='x')
    
    # Plot 7: Top 10 API Calls by Memory Usage
    ax7 = axes[2, 2]
    # Calculate total memory delta per API call type
    memory_by_api = (df.groupby('APICall')['Delta_VmRSS_KB'].sum() / 1024).sort_values(ascending=True).tail(10)
    memory_by_api.plot(kind='barh', ax=ax7, color='coral')
    ax7.set_xlabel('Total Memory Delta (MB)')
    ax7.set_title('Top 10 API Calls by Memory Impact')
    ax7.grid(True, alpha=0.3, axis='x')
    
    # Plot 8: Memory Usage by API Call (average per call)
    ax8 = axes[1, 2]
    # Calculate average memory delta per API call type
    avg_memory_by_api = (df.groupby('APICall')['Delta_VmRSS_KB'].mean() / 1024).sort_values(ascending=True).tail(10)
    avg_memory_by_api.plot(kind='barh', ax=ax8, color='mediumseagreen')
    ax8.set_xlabel('Avg Memory Delta per Call (MB)')
    ax8.set_title('Top 10 API Calls by Avg Memory per Call')
    ax8.grid(True, alpha=0.3, axis='x')
    
    # Plot 9: Cumulative memory by API over time
    ax9 = axes[0, 2]
    # Get top 5 API calls by total memory impact
    top5_apis = df.groupby('APICall')['Delta_VmRSS_KB'].sum().nlargest(5).index
    for api in top5_apis:
        api_data = df[df['APICall'] == api]
        ax9.plot(api_data['TimeSec'], (api_data['Delta_VmRSS_KB'].cumsum() / 1024), label=api, linewidth=2)
    ax9.set_xlabel('Time (s)')
    ax9.set_ylabel('Cumulative Memory Delta (MB)')
    ax9.set_title('Cumulative Memory Impact by Top 5 APIs')
    ax9.legend(fontsize=8)
    ax9.grid(True, alpha=0.3)
    
    plt.tight_layout()
    
    # Save plot
    output_file = Path(csv_file).stem + '_plot.png'
    plt.savefig(output_file, dpi=150, bbox_inches='tight')
    print(f"Plot saved to: {output_file}")
    
    # Show plot
    plt.show()
    
    # Print summary statistics
    print("\n=== Summary Statistics ===")
    print(f"Total API calls tracked: {len(df)}")
    print(f"Time span: {df['TimeSec'].max():.2f} seconds ({df['TimeMs'].max():.2f} ms)")
    print(f"Peak VmRSS: {df['VmRSS_KB'].max():.2f} KB ({df['VmRSS_KB'].max()/1024:.2f} MB)")
    print(f"Peak VmSize: {df['VmSize_KB'].max():.2f} KB ({df['VmSize_KB'].max()/1024:.2f} MB)")
    print(f"Total memory allocated: {df['TotalMemory_Bytes'].max():.2f} bytes "
          f"({df['TotalMemory_Bytes'].max()/(1024*1024):.2f} MB)")
    print(f"Number of threads: {df['Threads'].max()}")
    print(f"\nPeak resource counts:")
    print(f"  Contexts: {df['Contexts'].max()}")
    print(f"  CommandQueues: {df['CommandQueues'].max()}")
    print(f"  Modules: {df['Modules'].max()}")
    print(f"  Kernels: {df['Kernels'].max()}")
    print(f"  CommandLists: {df['CommandLists'].max()}")
    print(f"  Events: {df['Events'].max()}")
    
    # Print top API calls by memory usage
    print(f"\n=== Top 10 API Calls by Total Memory Impact ===")
    memory_by_api = df.groupby('APICall')['Delta_VmRSS_KB'].sum().sort_values(ascending=False).head(10)
    for api, mem in memory_by_api.items():
        print(f"  {api}: {mem:.2f} KB ({mem/1024:.2f} MB)")
    
    print(f"\n=== Top 10 API Calls by Average Memory per Call ===")
    avg_memory_by_api = df.groupby('APICall')['Delta_VmRSS_KB'].mean().sort_values(ascending=False).head(10)
    for api, mem in avg_memory_by_api.items():
        count = len(df[df['APICall'] == api])
        print(f"  {api}: {mem:.2f} KB/call ({count} calls)")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(__doc__)
        sys.exit(1)
    
    csv_file = sys.argv[1]
    if not Path(csv_file).exists():
        print(f"Error: File '{csv_file}' not found")
        sys.exit(1)
    
    try:
        import pandas
        import matplotlib
    except ImportError as e:
        print(f"Error: Required Python packages not installed")
        print(f"Install with: pip install pandas matplotlib")
        sys.exit(1)
    
    plot_resource_tracker(csv_file)
