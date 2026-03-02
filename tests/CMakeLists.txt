# Fetch Google Test from GitHub
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(tests test.cpp)

# Include parent directory for vector.hpp
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Compiler warnings (per-target to avoid affecting GoogleTest)
if(MSVC)
    target_compile_options(tests PRIVATE /W4)
else()
    target_compile_options(tests PRIVATE -Wall -Werror -pedantic)
endif()

# Link Google Test
target_link_libraries(tests PRIVATE GTest::gtest_main)
