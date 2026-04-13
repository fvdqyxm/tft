cmake_minimum_required(VERSION 3.16)

project(MatrixProject LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

option(MATRIX_ENABLE_NATIVE "Enable CPU-specific tuning flags (march=native)" ON)
option(MATRIX_ENABLE_FAST_MATH "Enable fast math optimizations" ON)
option(MATRIX_ENABLE_IPO "Enable interprocedural optimization (LTO/IPO) for release builds" ON)
option(MATRIX_BUILD_TESTS "Build matrix test executable and register CTest tests" ON)

add_library(matrix STATIC matrix.c)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(matrix PUBLIC c_std_11)
target_compile_options(matrix PRIVATE
    $<$<AND:$<CONFIG:Release>,$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>>>:
        -O3
        -DNDEBUG
        -fstrict-aliasing
        -fomit-frame-pointer
        -fno-math-errno
        -fno-trapping-math
    >
)

if(MATRIX_ENABLE_FAST_MATH)
    target_compile_options(matrix PRIVATE
        $<$<AND:$<CONFIG:Release>,$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>,$<C_COMPILER_ID:AppleClang>>>:-ffast-math>
    )
endif()

if(MATRIX_ENABLE_NATIVE)
    include(CheckCCompilerFlag)
    set(MATRIX_NATIVE_FLAGS "")
    check_c_compiler_flag("-mcpu=native" MATRIX_HAS_MCPU_NATIVE)
    if(MATRIX_HAS_MCPU_NATIVE)
        list(APPEND MATRIX_NATIVE_FLAGS -mcpu=native)
    endif()
    check_c_compiler_flag("-march=native" MATRIX_HAS_MARCH_NATIVE)
    if(MATRIX_HAS_MARCH_NATIVE)
        list(APPEND MATRIX_NATIVE_FLAGS -march=native)
    endif()
    check_c_compiler_flag("-mtune=native" MATRIX_HAS_MTUNE_NATIVE)
    if(MATRIX_HAS_MTUNE_NATIVE)
        list(APPEND MATRIX_NATIVE_FLAGS -mtune=native)
    endif()
    if(MATRIX_NATIVE_FLAGS)
        target_compile_options(matrix PRIVATE
            $<$<CONFIG:Release>:${MATRIX_NATIVE_FLAGS}>
        )
    endif()
endif()

if(MATRIX_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT matrix_ipo_supported OUTPUT matrix_ipo_error)
    if(matrix_ipo_supported)
        set_property(TARGET matrix PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    endif()
endif()

if(MATRIX_BUILD_TESTS)
    enable_testing()
    add_executable(matrix_tests tests.c)
    target_link_libraries(matrix_tests PRIVATE matrix)
    add_test(NAME matrix_tests COMMAND matrix_tests)
endif()
