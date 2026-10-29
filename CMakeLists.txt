cmake_minimum_required(VERSION 3.14)
project(arac-kiralama LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(kiralama_core src/AracKiralama.cpp)
target_include_directories(kiralama_core PUBLIC include)

add_executable(arac_kiralama src/main.cpp)
target_link_libraries(arac_kiralama PRIVATE kiralama_core)

enable_testing()
add_executable(test_arac_kiralama tests/test_arac_kiralama.cpp)
target_link_libraries(test_arac_kiralama PRIVATE kiralama_core)
add_test(NAME arac_kiralama_testleri COMMAND test_arac_kiralama)
