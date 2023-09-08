include(${PROJECT_SOURCE_DIR}/CMake/catch2.cmake)

add_executable(AllocatorTests)

target_link_libraries(
    AllocatorTests
    PRIVATE
    TTAllocators
    Catch2::Catch2WithMain
)

target_sources(
    AllocatorTests
    PRIVATE
    "PageAllocator/BasicTests.cpp"
)
