cmake_minimum_required(VERSION 3.10)
project(rpg)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(rpg
  src/main.cpp 
  src/bear.cpp
  src/elf.cpp
  src/bandit.cpp
  src/fight_visitor.cpp
  src/npc.cpp
  src/npc_factory.cpp
  src/observer.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wunused-parameter)

# enable_testing()

# add_executable(tests tests/test.cpp )
# target_include_directories(tests PRIVATE include)
# target_link_libraries(tests PRIVATE gtest_main)
# target_compile_options(tests PRIVATE -Wall -Wextra)

# Добавление тестов в тестовый набор
# add_test(NAME MyProjectTests COMMAND tests)