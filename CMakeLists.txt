cmake_minimum_required(VERSION 3.15)

set(entrypoint "cliford")
set(namespace "core")
project(cliford 
    VERSION 1.0.0 
    DESCRIPTION "cliford generic command line interface"
)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)
target_sources(${PROJECT_NAME} PRIVATE ${sources})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# install public headers
set(public_headers
    include/${entrypoint}.hpp
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()


# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Install)
