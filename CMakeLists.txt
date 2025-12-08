cmake_minimum_required(VERSION 3.25)

# Configuration
set(PROJECT_NAME "MyProject")
set(PROJECT_CXX_STANDARD 20)

# Export compile_commands.json for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Project setup : don't edit unless you know what you're doing
# ============================================================================

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD ${PROJECT_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Get all source files
file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

if(NOT PROJECT_SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory.")
endif()

# ============================================================================
# Split sources: library sources vs main sources
# Here we assume that any 'main.cpp' contains the program entry point.
# ============================================================================

set(LIB_SOURCES  "")
set(MAIN_SOURCES "")

foreach(SRC ${PROJECT_SOURCES})
    get_filename_component(SRC_NAME "${SRC}" NAME)
    if(SRC_NAME STREQUAL "main.cpp")
        list(APPEND MAIN_SOURCES "${SRC}")
    else()
        list(APPEND LIB_SOURCES "${SRC}")
    endif()
endforeach()

# ============================================================================
# Static library (no main)
# ============================================================================

set(STATIC_LIB_NAME "${PROJECT_NAME}_lib")

if(LIB_SOURCES)
    add_library(${STATIC_LIB_NAME} STATIC ${LIB_SOURCES})

    target_include_directories(${STATIC_LIB_NAME}
        PUBLIC
        "${PROJECT_SOURCE_DIR}/src"
    )
else()
    message(STATUS "No library sources found (all sources are main files?).")
endif()

# ============================================================================
# Executable only if there is at least one main source
# ============================================================================

if(MAIN_SOURCES)
    add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

    # Link with the static library if it exists
    if(TARGET ${STATIC_LIB_NAME})
        target_link_libraries(${PROJECT_NAME}
            PRIVATE
            ${STATIC_LIB_NAME}
        )
    endif()

    target_include_directories(${PROJECT_NAME}
        PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
    )
else()
    message(STATUS "No main.cpp found, no executable will be built.")
endif()
