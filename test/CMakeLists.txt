add_executable(test_xtl
        test_xtl_main.cpp
        test_delegate.cpp
        test_range.cpp
        test_utility.cpp
)

include_directories(
        "${CMAKE_SOURCE_DIR}/libs/Catch2/single_include/catch2"
)

target_link_libraries(test_xtl xtl)
