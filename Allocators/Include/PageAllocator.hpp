#ifndef TTALLOCATORS_PAGE_ALLOCATOR_HPP
#define TTALLOCATORS_PAGE_ALLOCATOR_HPP

#include "Utility.hpp"

#include <utility>

namespace tt
{
    class PageAllocator
    {
    public:
        class PagePtr
        {
        private:
            PagePtr(PageAllocator *source, void *beginPtr, size_t memorySize)
                : mMemorySource(source), mPtrBegin(beginPtr), mPtrMemorySize(memorySize)
            {}
        public:
            PagePtr(const PagePtr&) = delete;
            PagePtr& operator=(const PagePtr&) = delete;

            PagePtr(PagePtr&& other)
                : mMemorySource(other.mMemorySource), mPtrBegin(other.mPtrBegin), mPtrMemorySize(other.mPtrMemorySize)
            {
                other.mPtrBegin = nullptr;
                other.mPtrMemorySize = 0;
            }

            PagePtr& operator=(PagePtr&& other)
            {
                this->mMemorySource = other.mMemorySource;
                this->mPtrBegin = other.mPtrBegin;
                this->mPtrMemorySize = other.mPtrMemorySize;

                other.mMemorySource = nullptr;
                other.mPtrBegin = nullptr;
                other.mPtrMemorySize = 0;
            }

            ~PagePtr()
            {
                if (IsValid())
                {
                    mMemorySource->Dealloc(std::move(*this));
                }
            }

            void  *Get()           { return mPtrBegin; }
            size_t Size()    const { return mPtrMemorySize; }
            bool   IsValid() const { return mMemorySource && mPtrBegin; }
        private:
            PageAllocator *mMemorySource;
            void          *mPtrBegin;
            size_t         mPtrMemorySize;

            friend class PageAllocator;
        };
    public:
        PagePtr Alloc(size_t allocSize);
        void    Dealloc(PagePtr&& ptr);

        static const size_t GetPageSize();
    private:
    };
}

#endif //TTALLOCATORS_PAGE_ALLOCATOR_HPP
