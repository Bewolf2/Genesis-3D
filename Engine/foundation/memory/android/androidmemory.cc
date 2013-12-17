/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifdef __ANDROID__
#include "stdneb.h"
#include "core/types.h"
#include "core/sysfunc.h"
#include <malloc.h>
//todo fix this later
#define _msize(ptr) 0

namespace Memory
{

#if NEBULA3_MEMORY_STATS
int volatile TotalAllocCount = 0;
int volatile TotalAllocSize = 0;
int volatile HeapTypeAllocCount[NumHeapTypes] = { 0 };
int volatile HeapTypeAllocSize[NumHeapTypes] = { 0 };
bool volatile MemoryLoggingEnabled = false;
unsigned int volatile MemoryLoggingThreshold = 0;
HeapType volatile MemoryLoggingHeapType = InvalidHeapType;
#endif

//------------------------------------------------------------------------------
/**
    Allocate a block of memory from one of the global heaps.
*/
void*
Alloc(HeapType heapType, size_t size, size_t alignment)
{
    n_assert(heapType < NumHeapTypes);
    
    // make sure everything has been setup already
    Core::SysFunc::Setup();
        
    void* allocPtr = 0;
#if NEBULA3_MEMORY_STATS
    size_t allocatedSize = 0;
#endif
        
    // allocate memory from global heap    
    allocPtr = malloc(size);
    if (0 == allocPtr)
    {
        n_error("Allocation failed from Heap '%s'!\n", GetHeapTypeName(heapType));
    }
#if NEBULA3_MEMORY_STATS
    allocatedSize = _msize(allocPtr);
#endif
        
#if NEBULA3_MEMORY_STATS                
    Threading::Interlocked::Increment(TotalAllocCount);
    Threading::Interlocked::Add(TotalAllocSize, allocatedSize);
    Threading::Interlocked::Increment(HeapTypeAllocCount[heapType]);
    Threading::Interlocked::Add(HeapTypeAllocSize[heapType], allocatedSize);
    if (MemoryLoggingEnabled && (size >= MemoryLoggingThreshold) &&
        ((MemoryLoggingHeapType == InvalidHeapType) || (MemoryLoggingHeapType == heapType)))
    {
        n_printf("Allocate(size=%d, allocSize=%d, heapType=%d): 0x%lx\n", size, allocatedSize, heapType, (long unsigned int) allocPtr);
    }
#endif
    return allocPtr;
}
    
//------------------------------------------------------------------------------
/**
    Re-Allocate a block of memory from one of the global heaps.
 
    NOTE that this function may also be used to shrink a memory block!
*/
void*
Realloc(HeapType heapType, void* ptr, size_t size)
{
    n_assert(heapType < NumHeapTypes);
    
    // make sure everything has been setup already
    Core::SysFunc::Setup();
                
    // get old size for stats tracking
#if NEBULA3_MEMORY_STATS
    size_t oldSize = _msize(ptr);
#endif
        
    // reallocate the memory
    void* allocPtr = realloc(ptr, size);
    if (0 == allocPtr)
    {
        n_error("Allocation failed from Heap '%s'!\n", GetHeapTypeName(heapType));
    }
        
#if NEBULA3_MEMORY_STATS
    size_t allocatedSize = _msize(allocPtr);
    Threading::Interlocked::Add(TotalAllocSize, size_t(allocatedSize - oldSize));
    Threading::Interlocked::Add(HeapTypeAllocSize[heapType], size_t(allocatedSize - oldSize));
    if (MemoryLoggingEnabled && (size >= MemoryLoggingThreshold) &&
        ((MemoryLoggingHeapType == InvalidHeapType) || (MemoryLoggingHeapType == heapType)))
    {
        n_printf("Reallocate(size=%d, allocSize=%d, heapType=%d): 0x%lx\n", size, allocatedSize, heapType, (long unsigned int) allocPtr);
    }
#endif
    return allocPtr;
}
    
//------------------------------------------------------------------------------
/**
    Free a block of memory.
*/
void
Free(HeapType heapType, void* ptr)
{
    if (0 != ptr)
    {
        n_assert(heapType < NumHeapTypes);
            
#if NEBULA3_MEMORY_STATS
        size_t allocatedSize = _msize(ptr);
#endif
        free(ptr);
            
#if NEBULA3_MEMORY_STATS
		int nAllocatedSize = -((int)allocatedSize);
        Threading::Interlocked::Add(TotalAllocSize, nAllocatedSize);
        Threading::Interlocked::Decrement(TotalAllocCount);
        Threading::Interlocked::Add(HeapTypeAllocSize[heapType], nAllocatedSize);
        Threading::Interlocked::Decrement(HeapTypeAllocCount[heapType]);
        if (MemoryLoggingEnabled && (allocatedSize >= MemoryLoggingThreshold) &&
            ((MemoryLoggingHeapType == InvalidHeapType) || (MemoryLoggingHeapType == heapType)))
        {
            n_printf("Mem::Free(heapType=%d, ptr=0x%lx, allocSize=%d)\n", heapType, (long unsigned int) ptr, allocatedSize);
        }
#endif
    }
}
    
//------------------------------------------------------------------------------
/**
    Duplicate a 0-terminated string, this method should no longer be used!
*/
char*
DuplicateCString(const char* from)
{
    n_assert(0 != from);
    size_t len = (unsigned int) strlen(from) + 1;
    char* to = (char*) Memory::Alloc(Memory::StringDataHeap, len);
    Memory::Copy((void*)from, to, len);
    return to;
}
    
//------------------------------------------------------------------------------
/**
    Test if 2 areas of memory areas are overlapping.
*/
bool
IsOverlapping(const unsigned char* srcPtr, size_t srcSize, const unsigned char* dstPtr, size_t dstSize)
{
    if (srcPtr == dstPtr)
    {
        return true;
    }
    else if (srcPtr > dstPtr)
    {
        return (srcPtr + srcSize) > dstPtr;
    }
    else
    {
        return (dstPtr + dstSize) > srcPtr;
    }
}
    
//------------------------------------------------------------------------------
/**
    Get the system's total memory status.
*/
TotalMemoryStatus
GetTotalMemoryStatus()
{
    n_error("IMPLEMENT ME: GetTotalMemoryStatus()!");
    TotalMemoryStatus status = { 0 };
    return status;
}
    
//------------------------------------------------------------------------------
/**
    Copy a chunk of memory (note the argument order is different from memcpy()!!!)
*/
void
Copy(const void* from, void* to, size_t numBytes)
{
    if (numBytes > 0)
    {
        n_assert(0 != from);
        n_assert(0 != to);
        n_assert(from != to);
        memcpy(to, from, numBytes);
    }
}

//------------------------------------------------------------------------------
/**
    Copy data from a system memory buffer to graphics resource memory. Some
    platforms may need special handling of this case.
*/
void CopyToGraphicsMemory(const void* from, void* to, size_t numBytes)
{
	Memory::Copy(from, to, numBytes);
}
    
//------------------------------------------------------------------------------
/**
    Overwrite a chunk of memory with 0's.
*/
void
Clear(void* ptr, size_t numBytes)
{
    memset(ptr, 0, numBytes);
}
    
//------------------------------------------------------------------------------
/**
    Fill memory with a specific byte.
*/
void
Fill(void* ptr, size_t numBytes, unsigned char value)
{
    memset(ptr, value, numBytes);
}
    
#if NEBULA3_MEMORY_STATS
//------------------------------------------------------------------------------
/**
    Enable memory logging.
*/
void
EnableMemoryLogging(unsigned int threshold, HeapType heapType)
{
    MemoryLoggingEnabled = true;
    MemoryLoggingThreshold = threshold;
    MemoryLoggingHeapType = heapType;
}
    
//------------------------------------------------------------------------------
/**
    Disable memory logging.
*/
void
DisableMemoryLogging()
{
    MemoryLoggingEnabled = false;
}
    
//------------------------------------------------------------------------------
/**
    Toggle memory logging.
*/
void
ToggleMemoryLogging(unsigned int threshold, HeapType heapType)
{
    if (MemoryLoggingEnabled)
    {
        DisableMemoryLogging();
    }
    else
    {
        EnableMemoryLogging(threshold, heapType);
    }
}
#endif // NEBULA3_MEMORY_STATS
    
#if NEBULA3_MEMORY_ADVANCED_DEBUGGING
//------------------------------------------------------------------------------
/**
    Debug function which validates all heaps. 
*/
bool
ValidateMemory()
{
    n_error("IMPLEMENT ME: ValidateMemory()");
    return true;
}
    
//------------------------------------------------------------------------------
/**
    Write memory debugging info to log.
*/
void
Checkpoint(const char* msg)
{
    n_printf("MEMORY LOG: %s\n", msg);
    ValidateMemory();
    
    // also dump a general alloc count/alloc size by heap type...
    n_printf("NEBULA ALLOC COUNT / SIZE: %d / %d\n", TotalAllocCount, TotalAllocSize);
    IndexT i;
    for (i = 0; i < NumHeapTypes; i++)
    {
        const char* heapName = GetHeapTypeName((HeapType)i);
        if (0 == heapName)
        {
            heapName = "UNKNOWN";
        }
        n_printf("HEAP %lx ALLOC COUNT / SIZE: %s %d / %d\n", Heaps[i], heapName, HeapTypeAllocCount[i], HeapTypeAllocSize[i]);
    }
}
    
//------------------------------------------------------------------------------
/**
    Generate a memory leak dump for all heaps managed by Nebula.
*/
void
DumpMemoryLeaks()
{
    n_error("IMPLEMENT ME: DumpMemoryLeaks()");
}
#endif // NEBULA3_MEMORY_ADVANCED_DEBUGGING


}

#endif