cmake_minimum_required(VERSION 3.10)
project(rpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Windows console fix
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")
endif()

# List all source files
set(SOURCES
    src/main.cpp 
    src/bear.cpp
    src/elf.cpp
    src/bandit.cpp
    src/fight_visitor.cpp
    src/npc.cpp
    src/npc_factory.cpp
    src/observer.cpp
)

# Main executable
add_executable(rpg ${SOURCES})
target_compile_options(rpg PRIVATE -Wall -Wextra -Wunused-parameter)

# Tests - need the same source files (excluding main.cpp)
set(TEST_SOURCES
    tests/test.cpp
    src/bear.cpp
    src/elf.cpp
    src/bandit.cpp
    src/fight_visitor.cpp
    src/npc.cpp
    src/npc_factory.cpp
    src/observer.cpp
)

add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE gtest gtest_main)
target_compile_options(tests PRIVATE -Wall -Wextra)

enable_testing()
add_test(NAME RPGTests COMMAND tests)