cmake_minimum_required(VERSION 3.25)

# ============================================================================
# Configuration
# ============================================================================

set(PROJECT_NAME "MyProject")
set(PROJECT_CXX_STANDARD 20)

# Export compile_commands.json for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Centralized target names
set(EXECUTABLE_NAME       "${PROJECT_NAME}")
set(TEST_EXECUTABLE_NAME  "tests-${PROJECT_NAME}")
set(STATIC_LIB_NAME       "lib-${PROJECT_NAME}")

# Option to enable/disable tests
option(BUILD_TESTING "Enable building tests" ON)

# ============================================================================
# Project setup : don't edit unless you know what you're doing
# ============================================================================

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD ${PROJECT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================================
# Collect all .cpp sources under src/
# ============================================================================

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory.")
endif()

# Path to main.cpp (if it exists)
set(MAIN_FILE "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Remove main.cpp from the list of sources used to build the library
list(REMOVE_ITEM PROJECT_SOURCES "${MAIN_FILE}")

# ============================================================================
# Static library (all sources except main.cpp)
# ============================================================================

if(PROJECT_SOURCES)
    add_library(${STATIC_LIB_NAME} STATIC ${PROJECT_SOURCES})

    target_include_directories(${STATIC_LIB_NAME}
        PUBLIC
        "${PROJECT_SOURCE_DIR}/src"
    )
else()
    message(STATUS "No library sources found (only main.cpp present?).")
endif()

# ============================================================================
# Executable (only if main.cpp exists)
# ============================================================================

if(EXISTS "${MAIN_FILE}")
    add_executable(${EXECUTABLE_NAME} "${MAIN_FILE}")

    if(TARGET ${STATIC_LIB_NAME})
        target_link_libraries(${EXECUTABLE_NAME}
            PRIVATE
            ${STATIC_LIB_NAME}
        )
    endif()

    target_include_directories(${EXECUTABLE_NAME}
        PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
    )
else()
    message(STATUS "No main.cpp found in src/, no executable will be built.")
endif()

# ============================================================================
# Tests (GoogleTest, sources in test/)
# ============================================================================

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )

    FetchContent_MakeAvailable(googletest)

    enable_testing()
    include(GoogleTest)

    # Collect all test sources under test/
    file(GLOB_RECURSE TEST_SOURCES
        CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
    )

    if(TEST_SOURCES)

        # Ensure library exists, else fail
        if(NOT TARGET ${STATIC_LIB_NAME})
            message(FATAL_ERROR "Static library ${STATIC_LIB_NAME} was not built — tests cannot be linked.")
        endif()

        add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCES})

        # Link tests with your static library and gtest_main (gtest provides its own main)
        target_link_libraries(${TEST_EXECUTABLE_NAME}
            PRIVATE
                ${STATIC_LIB_NAME}
                GTest::gtest_main
        )

        # Include paths for tests and source
        target_include_directories(${TEST_EXECUTABLE_NAME}
            PRIVATE
                "${PROJECT_SOURCE_DIR}/src"
                "${PROJECT_SOURCE_DIR}/test"
        )

        # Register tests with CTest
        gtest_discover_tests(${TEST_EXECUTABLE_NAME})

    else()
        message(STATUS "No test sources found in test/ directory.")
    endif()
else()
    message(STATUS "BUILD_TESTING=OFF: tests will not be built.")
endif()
