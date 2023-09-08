#include "PageAllocator.hpp"

#if TTA_IS_PLATFORM_WINDOWS
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#elif TTA_IS_PLATFORM_POSIX
#   include <sys/mman.h>
#   include <unistd.h>
#endif

namespace tt
{
    const size_t PageAllocator::GetPageSize()
    {
#       if TTA_IS_PLATFORM_WINDOWS
            SYSTEM_INFO sysInfo;
            return sysInfo.dwPageSize; // TODO(3011): Test this when on Windows.
#       elif TTA_IS_PLATFORM_POSIX
            return sysconf(_SC_PAGESIZE);
#       endif
    }

    PageAllocator::PagePtr PageAllocator::Alloc(size_t allocSize)
    {
        AllocAssert(false, AllocConstString("Not implemented"));
    }

    void PageAllocator::Dealloc(PagePtr&& ptr)
    {
        AllocAssert(false, AllocConstString("Not Implemented"));
    }
}
