cmake_minimum_required(VERSION 3.26)

project(TTAllocators
    LANGUAGES C CXX
    VERSION 0.0.1
)

add_subdirectory(Allocators)

if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(AllocatorTests)
endif()
