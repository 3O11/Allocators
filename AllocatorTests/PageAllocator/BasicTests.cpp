#include <catch2/catch_test_macros.hpp>
#include <PageAllocator.hpp>

TEST_CASE("Test allocating and deallocating a single page")
{
    tt::PageAllocator pageAllocator;
    INFO("Page size: " << tt::PageAllocator::GetPageSize());

    tt::PageAllocator::PagePtr ptr = pageAllocator.Alloc(1);
    unsigned char *charPtr = reinterpret_cast<unsigned char *>(ptr.Get());
    for (size_t i = 0; i < ptr.Size(); ++i)
    {
        *charPtr = (unsigned char)(i & 255);
    }
    pageAllocator.Dealloc(std::move(ptr));
}

TEST_CASE("Test allocating and deallocating multiple pages out of order")
{
    tt::PageAllocator pageAllocator;
    std::vector<tt::PageAllocator::PagePtr> ptrs;

    for (size_t i = 0; i < 16; ++i)
    {
        ptrs.push_back(pageAllocator.Alloc(1));
    }

    for (size_t i = 0; i < 16; ++i)
    {
        ptrs.erase(ptrs.begin() + (rand() % ptrs.size()));
    }
}
