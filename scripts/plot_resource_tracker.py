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
    
    # Check if CSV has any data rows
    if len(df) == 0:
        print(f"Error: CSV file '{csv_file}' contains no data rows (only header).")
        print("Make sure the application runs with ZEL_ENABLE_SYSTEM_RESOURCE_TRACKER_CHECKER=1")
        return
    
    # Convert time from milliseconds to seconds
    df['TimeSec'] = df['TimeMs'] / 1000.0
    
    # Detect potential memory leaks - track memory increases that don't get freed
    # For create/destroy operations, memory should return to baseline
    # Look for APIs that destroy resources but memory doesn't decrease
    df['PotentialLeak_KB'] = 0
    
    # Create/Destroy pairs to monitor for leaks
    create_destroy_pairs = {
        'zeContextCreate': 'zeContextDestroy',
        'zeCommandQueueCreate': 'zeCommandQueueDestroy',
        'zeModuleCreate': 'zeModuleDestroy',
        'zeKernelCreate': 'zeKernelDestroy',
        'zeEventPoolCreate': 'zeEventPoolDestroy',
        'zeCommandListCreate': 'zeCommandListDestroy',
        'zeCommandListCreateImmediate': 'zeCommandListDestroy',
        'zeEventCreate': 'zeEventDestroy',
        'zeFenceCreate': 'zeFenceDestroy',
        'zeImageCreate': 'zeImageDestroy',
        'zeSamplerCreate': 'zeSamplerDestroy',
        'zeMemAllocDevice': 'zeMemFree',
        'zeMemAllocHost': 'zeMemFree',
        'zeMemAllocShared': 'zeMemFree',
    }
    
    # Track memory at create and check if it decreased at destroy
    for idx, row in df.iterrows():
        api = row['APICall']
        # If this is a destroy operation, check if memory decreased
        if api in create_destroy_pairs.values():
            # Memory should decrease on destroy - if it increased, it's a leak
            if row['Delta_VmRSS_KB'] > 100:  # Threshold: 100KB increase on destroy = leak
                df.at[idx, 'PotentialLeak_KB'] = row['Delta_VmRSS_KB']
    
    # Calculate cumulative leaks over time
    df['CumulativeLeak_KB'] = df['PotentialLeak_KB'].cumsum()
    
    # Create figure with multiple subplots
    fig, axes = plt.subplots(4, 3, figsize=(18, 16))
    fig.suptitle(f'Level Zero System Resource Tracking\n{Path(csv_file).name}', fontsize=16)
    
    # Plot 1: Memory Leak Detection Over Time
    ax1 = axes[0, 0]
    # Plot cumulative leaks
    ax1.plot(df['TimeSec'], df['CumulativeLeak_KB'] / 1024, label='Cumulative Leaks', 
             linewidth=3, color='red')
    # Mark individual leak events
    leak_events = df[df['PotentialLeak_KB'] > 0]
    if not leak_events.empty:
        ax1.scatter(leak_events['TimeSec'], leak_events['CumulativeLeak_KB'] / 1024, 
                   color='darkred', s=100, marker='x', linewidths=3, 
                   label=f'Leak Events ({len(leak_events)})', zorder=5)
    ax1.set_xlabel('Time (s)')
    ax1.set_ylabel('Memory Leaked (MB)')
    ax1.set_title('Memory Leak Detection Over Time', fontweight='bold', color='darkred')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    if df['CumulativeLeak_KB'].max() > 0:
        ax1.set_facecolor('#fff5f5')  # Light red background if leaks detected
    
    # Plot 2: Memory Usage Over Time (VmRSS, VmSize, VmData)
    ax2 = axes[0, 1]
    ax2.plot(df['TimeSec'], df['VmRSS_KB'] / 1024, label='VmRSS', linewidth=2)
    ax2.plot(df['TimeSec'], df['VmSize_KB'] / 1024, label='VmSize', linewidth=2, alpha=0.7)
    ax2.plot(df['TimeSec'], df['VmData_KB'] / 1024, label='VmData', linewidth=2, alpha=0.7)
    ax2.set_xlabel('Time (s)')
    ax2.set_ylabel('Memory (MB)')
    ax2.set_title('System Memory Usage Over Time')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    
    # Plot 3: Leak Events by API Type
    ax3 = axes[0, 2]
    if not leak_events.empty:
        leak_by_api = leak_events.groupby('APICall')['PotentialLeak_KB'].sum().sort_values(ascending=True) / 1024
        if not leak_by_api.empty:
            leak_by_api.plot(kind='barh', ax=ax3, color='orangered')
            ax3.set_xlabel('Total Leaked Memory (MB)')
            ax3.set_title('Memory Leaks by API Call', fontweight='bold')
            ax3.grid(True, alpha=0.3, axis='x')
            ax3.set_facecolor('#fff5f5')
        else:
            ax3.text(0.5, 0.5, 'No Leaks Detected!', ha='center', va='center', 
                    fontsize=14, color='green', fontweight='bold', transform=ax3.transAxes)
            ax3.set_title('Memory Leaks by API Call')
            ax3.axis('off')
    else:
        ax3.text(0.5, 0.5, 'No Leaks Detected!', ha='center', va='center', 
                fontsize=14, color='green', fontweight='bold', transform=ax3.transAxes)
        ax3.set_title('Memory Leaks by API Call')
        ax3.axis('off')
    
    # Plot 4: Memory Deltas (showing per-call changes)
    ax4 = axes[1, 0]
    ax4.plot(df['TimeSec'], df['Delta_VmRSS_KB'] / 1024, label='Delta VmRSS', linewidth=1.5)
    ax4.plot(df['TimeSec'], df['Delta_VmSize_KB'] / 1024, label='Delta VmSize', linewidth=1.5, alpha=0.7)
    ax4.axhline(y=0, color='black', linestyle='--', linewidth=0.5)
    ax4.set_xlabel('Time (s)')
    ax4.set_ylabel('Memory Change (MB)')
    ax4.set_title('Memory Deltas Per API Call')
    ax4.legend()
    ax4.grid(True, alpha=0.3)
    
    # Plot 5: Level Zero Resource Counts
    ax5 = axes[1, 1]
    has_resources = False
    if df['Contexts'].max() > 0:
        ax5.plot(df['TimeSec'], df['Contexts'], label='Contexts', linewidth=2)
        has_resources = True
    if df['CommandQueues'].max() > 0:
        ax5.plot(df['TimeSec'], df['CommandQueues'], label='CommandQueues', linewidth=2)
        has_resources = True
    if df['Modules'].max() > 0:
        ax5.plot(df['TimeSec'], df['Modules'], label='Modules', linewidth=2)
        has_resources = True
    if df['Kernels'].max() > 0:
        ax5.plot(df['TimeSec'], df['Kernels'], label='Kernels', linewidth=2)
        has_resources = True
    ax5.set_xlabel('Time (s)')
    ax5.set_ylabel('Resource Count')
    ax5.set_title('L0 Resource Counts (Contexts, Queues, Modules, Kernels)')
    if has_resources:
        ax5.legend()
    ax5.grid(True, alpha=0.3)
    
    # Plot 6: Command Lists and Event Resources
    ax6 = axes[1, 2]
    has_cmd_resources = False
    if df['CommandLists'].max() > 0:
        ax6.plot(df['TimeSec'], df['CommandLists'], label='CommandLists', linewidth=2)
        has_cmd_resources = True
    if df['EventPools'].max() > 0:
        ax6.plot(df['TimeSec'], df['EventPools'], label='EventPools', linewidth=2)
        has_cmd_resources = True
    if df['Events'].max() > 0:
        ax6.plot(df['TimeSec'], df['Events'], label='Events', linewidth=2)
        has_cmd_resources = True
    if df['Fences'].max() > 0:
        ax6.plot(df['TimeSec'], df['Fences'], label='Fences', linewidth=2)
        has_cmd_resources = True
    ax6.set_xlabel('Time (s)')
    ax6.set_ylabel('Resource Count')
    ax6.set_title('L0 Command Lists and Events')
    if has_cmd_resources:
        ax6.legend()
    ax6.grid(True, alpha=0.3)
    
    # Plot 7: Total Memory Allocations
    ax7 = axes[2, 0]
    ax7.plot(df['TimeSec'], df['TotalMemory_Bytes'] / (1024*1024), label='Total Memory', 
             linewidth=2, color='red')
    ax7.set_xlabel('Time (s)')
    ax7.set_ylabel('Memory (MB)')
    ax7.set_title('Total L0 Memory Allocations')
    ax7.legend()
    ax7.grid(True, alpha=0.3)
    
    # Plot 8: API Call Distribution (top 10 most frequent)
    ax8 = axes[2, 1]
    api_counts = df['APICall'].value_counts().head(10).sort_values(ascending=True)
    if len(api_counts) > 0:
        api_counts.plot(kind='barh', ax=ax8, color='steelblue')
        ax8.set_xlabel('Call Count')
        ax8.set_title('Top 10 Most Frequent API Calls')
        ax8.grid(True, alpha=0.3, axis='x')
    else:
        ax8.text(0.5, 0.5, 'No API calls recorded', ha='center', va='center',
                fontsize=12, transform=ax8.transAxes)
        ax8.set_title('Top 10 Most Frequent API Calls')
        ax8.axis('off')
    
    # Plot 9: Top 10 API Calls by Memory Usage
    ax9 = axes[2, 2]
    # Calculate total memory delta per API call type
    memory_by_api = (df.groupby('APICall')['Delta_VmRSS_KB'].sum() / 1024).sort_values(ascending=True).tail(10)
    if len(memory_by_api) > 0:
        memory_by_api.plot(kind='barh', ax=ax9, color='coral')
        ax9.set_xlabel('Total Memory Delta (MB)')
        ax9.set_title('Top 10 API Calls by Memory Impact')
        ax9.grid(True, alpha=0.3, axis='x')
    else:
        ax9.text(0.5, 0.5, 'No API calls recorded', ha='center', va='center',
                fontsize=12, transform=ax9.transAxes)
        ax9.set_title('Top 10 API Calls by Memory Impact')
        ax9.axis('off')
    
    # Plot 10: Memory Usage by API Call (average per call)
    ax10 = axes[3, 0]
    # Calculate average memory delta per API call type
    avg_memory_by_api = (df.groupby('APICall')['Delta_VmRSS_KB'].mean() / 1024).sort_values(ascending=True).tail(10)
    if len(avg_memory_by_api) > 0:
        avg_memory_by_api.plot(kind='barh', ax=ax10, color='mediumseagreen')
        ax10.set_xlabel('Avg Memory Delta per Call (MB)')
        ax10.set_title('Top 10 API Calls by Avg Memory per Call')
        ax10.grid(True, alpha=0.3, axis='x')
    else:
        ax10.text(0.5, 0.5, 'No API calls recorded', ha='center', va='center',
                fontsize=12, transform=ax10.transAxes)
        ax10.set_title('Top 10 API Calls by Avg Memory per Call')
        ax10.axis('off')
    
    # Plot 11: Cumulative memory by API over time
    ax11 = axes[3, 1]
    # Get top 5 API calls by total memory impact
    top5_apis = df.groupby('APICall')['Delta_VmRSS_KB'].sum().nlargest(5).index
    if len(top5_apis) > 0:
        for api in top5_apis:
            api_data = df[df['APICall'] == api]
            ax11.plot(api_data['TimeSec'], (api_data['Delta_VmRSS_KB'].cumsum() / 1024), label=api, linewidth=2)
        ax11.set_xlabel('Time (s)')
        ax11.set_ylabel('Cumulative Memory Delta (MB)')
        ax11.set_title('Cumulative Memory Impact by Top 5 APIs')
        ax11.legend(fontsize=8)
        ax11.grid(True, alpha=0.3)
    else:
        ax11.text(0.5, 0.5, 'No API calls recorded', ha='center', va='center',
                fontsize=12, transform=ax11.transAxes)
        ax11.set_title('Cumulative Memory Impact by Top 5 APIs')
        ax11.axis('off')
    
    # Plot 12: Leak detection timeline with annotations
    ax12 = axes[3, 2]
    if not leak_events.empty:
        # Show individual leak magnitudes over time
        ax12.bar(leak_events['TimeSec'], leak_events['PotentialLeak_KB'] / 1024, 
                width=0.01, color='red', alpha=0.7, label='Leak Magnitude')
        ax12.set_xlabel('Time (s)')
        ax12.set_ylabel('Leaked Memory (MB)')
        ax12.set_title('Individual Leak Events Timeline', fontweight='bold')
        ax12.legend()
        ax12.grid(True, alpha=0.3, axis='y')
        ax12.set_facecolor('#fff5f5')
        
        # Add text annotation for total
        total_leaked = leak_events['PotentialLeak_KB'].sum() / 1024
        ax12.text(0.95, 0.95, f'Total: {total_leaked:.2f} MB\n{len(leak_events)} events', 
                 transform=ax12.transAxes, ha='right', va='top',
                 bbox=dict(boxstyle='round', facecolor='white', alpha=0.8),
                 fontsize=10, fontweight='bold', color='darkred')
    else:
        ax12.text(0.5, 0.5, 'No Memory Leaks Detected!\n✓ All resources properly cleaned up', 
                 ha='center', va='center', fontsize=14, color='green', 
                 fontweight='bold', transform=ax12.transAxes)
        ax12.set_title('Individual Leak Events Timeline')
        ax12.axis('off')
    
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
    
    # Print leak detection summary
    print(f"\n=== MEMORY LEAK DETECTION ===")
    if df['CumulativeLeak_KB'].max() > 0:
        print(f"⚠️  LEAKS DETECTED!")
        print(f"Total leaked memory: {df['CumulativeLeak_KB'].max() / 1024:.2f} MB ({df['CumulativeLeak_KB'].max():.2f} KB)")
        print(f"Number of leak events: {len(leak_events)}")
        if not leak_events.empty:
            print(f"\nLeak events by API:")
            leak_summary = leak_events.groupby('APICall')['PotentialLeak_KB'].agg(['count', 'sum', 'mean'])
            leak_summary.columns = ['Count', 'Total_KB', 'Avg_KB']
            leak_summary = leak_summary.sort_values('Total_KB', ascending=False)
            for api, row in leak_summary.iterrows():
                print(f"  {api}: {row['Count']} events, {row['Total_KB']/1024:.2f} MB total, {row['Avg_KB']/1024:.2f} MB avg")
    else:
        print(f"✓ No memory leaks detected!")
        print(f"  All resources were properly cleaned up.")
    
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
