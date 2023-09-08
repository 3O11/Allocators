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
        // TODO(3011): Add some sort of caching, because getting this info
        // may potentially be expensive, especially on Windows.
#       if TTA_IS_PLATFORM_WINDOWS
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);
            return sysInfo.dwPageSize; // TODO(3011): Test this when on Windows.
#       elif TTA_IS_PLATFORM_POSIX
            return sysconf(_SC_PAGESIZE);
#       endif
    }

    PageAllocator::PagePtr PageAllocator::Alloc(size_t pageCount)
    {
        void *tempMemPtr = nullptr;
#       if TTA_IS_PLATFORM_WINDOWS
            tempMemPtr = VirtualAlloc(nullptr, pageCount * GetPageSize(), MEM_RESERVE | MEM_COMMIT, PAGE_NOACCESS);
            AllocAssert(tempMemPtr, AllocConstString("Page allocation failed"));
#       elif TTA_IS_PLATFORM_POSIX
            tempMemPtr = mmap(nullptr, pageCount * GetPageSize(), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
            AllocAssert(tempMemPtr != MAP_FAILED, AllocConstString("Page allocation failed"));
#       endif
        return PagePtr(this, tempMemPtr, pageCount * GetPageSize());
    }

    void PageAllocator::Dealloc(PagePtr&& ptr)
    {
        // This clears the original PagePtr.
        PagePtr temp = std::move(ptr);
#       if TTA_IS_PLATFORM_WINDOWS
            VirtualFree(temp.mPtrBegin, 0, MEM_RELEASE);
#       elif TTA_IS_PLATFORM_POSIX
            munmap(temp.mPtrBegin, temp.mPtrMemorySize);
#       endif
    }
}
