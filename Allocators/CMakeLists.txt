
add_library(TTAllocators STATIC)

set_target_properties(
    TTAllocators
    PROPERTIES
    CXX_STANDARD 23
)

target_include_directories(
    TTAllocators
    PUBLIC
    "Include"
    PRIVATE
    "Source" # Not needed, but just for good measure
)

target_sources(
    TTAllocators
    PRIVATE
    # Interface
    "Include/PageAllocator.hpp"
    "Include/HoardAllocator.hpp"
    # Implementation
    "Source/PageAllocator.cpp"
    "Source/HoardAllocator.cpp"
)
