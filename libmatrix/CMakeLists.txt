cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(libmatrix CXX C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(library_sources
    src/CMatrix.hpp
    src/CMatrix.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../gsl ${CMAKE_BINARY_DIR}/gsl/ EXCLUDE_FROM_ALL)
include_directories(gsl
                    ${CMAKE_BINARY_DIR}/gsl/)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(GenerateExportHeader)
add_library(matrix STATIC ${library_sources})
target_link_libraries(matrix gsl)
generate_export_header(matrix)
add_compiler_export_flags()
