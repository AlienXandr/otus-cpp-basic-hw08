cmake_minimum_required(VERSION 3.25)

project(08.homework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS NO)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
            -g
            -Wall
            -Wextra
            -Werror
            -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
            /EHsc
            /W4
            /WX)
endif ()

add_executable(${PROJECT_NAME} main.cpp
        src/count_words/multi_threaded/read_file_common_map/read_file_common_map.h
        src/count_words/multi_threaded/read_file_common_map/read_file_common_map.cpp
        src/count_words/multi_threaded/read_file_local_map/read_file_local_map.h
        src/count_words/multi_threaded/read_file_local_map/read_file_local_map.cpp
        src/count_words/multi_threaded/read_vector_common_map/read_vector_common_map.h
        src/count_words/multi_threaded/read_vector_common_map/read_vector_common_map.cpp
        src/count_words/multi_threaded/read_vector_local_map/read_vector_local_map.h
        src/count_words/multi_threaded/read_vector_local_map/read_vector_local_map.cpp

        src/count_words/helpers/filter/filter.cpp
        src/count_words/helpers/filter/filter.h
        src/count_words/helpers/to_lower/to_lower.cpp
        src/count_words/helpers/to_lower/to_lower.h
        src/count_words/helpers/add_word_in_map/add_word_in_map.cpp
        src/count_words/helpers/add_word_in_map/add_word_in_map.h
        src/count_words/helpers/print_top_words/print_top_words.h
        src/count_words/containers/mtx_map.h
        src/count_words/containers/IMap.h

        src/research_tests/compare_speed_calc_line/compare_speed_calc_line.cpp
        src/research_tests/compare_speed_calc_line/compare_speed_calc_line.h
        src/research_tests/regex_test/regex.hpp

)

