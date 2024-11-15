# Events Deadlock Checker Design Document
This document outlines the design and implementation details of the events checker.

## Introduction
The Events Checker validates usage of events. 
- It is designed to detect potential deadlocks that might occur due to improper event usage in the Level Zero API. It prints out warning messages for user when it detects a potential deadlock.
- It may also detect whether an event is being used more than once without being reset. Consider a case in which a single event is signaled from twice.

## Objectives
- Detect potential deadlocks caused by event usage.
- Provide detailed information to help developers identify and resolve deadlock issues.

## Design Overview
The checker creates an internal Directed Acyclic Graph (DAG) of dependencies between API calls (the actions that are nodes in the graph) and events (the edges in the graph). It also maintains a topological sort and when an attempt is made to insert an edge that causes a cycle in the graph it warns the user of a potential deadlock and returns without inserting that edge.

## API Implemented
### zeEventCreate
### zeEventDestroy
### zeCommandListAppendMemoryCopy
### zeCommandListAppendWriteGlobalTimestamp
### zeCommandListAppendBarrier
### zeCommandListAppendMemoryRangesBarrier
### zeCommandListAppendMemoryFill
### zeCommandListAppendMemoryCopyRegion
### zeCommandListAppendMemoryCopyFromContext
### zeCommandListAppendImageCopy
### zeCommandListAppendImageCopyRegion
### zeCommandListAppendImageCopyToMemory
### zeCommandListAppendImageCopyFromMemory
### zeCommandListAppendSignalEvent
### zeCommandListAppendWaitOnEvents
### zeEventHostSignal
### zeCommandListAppendEventReset
### zeEventHostReset
### zeCommandListAppendQueryKernelTimestamp
### zeCommandListAppendLaunchKernel
### zeCommandListAppendLaunchCooperativeKernel
### zeCommandListAppendLaunchKernelIndirect
### zeCommandListAppendLaunchMultipleKernelsIndirect
### zeCommandListUpdateMutableCommandSignalEventExp
### zeCommandListUpdateMutableCommandWaitEventsExp
### zeCommandListAppendImageCopyToMemoryExt
### zeCommandListAppendImageCopyFromMemoryExt
### zeCommandListImmediateAppendCommandListsExp
