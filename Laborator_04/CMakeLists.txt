cmake_minimum_required(VERSION 3.13)
project(Laborator_04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# static library with the classes for items 4, 5 and 6
add_library(effective_cpp STATIC
    src/logger_functii.cpp
    src/item4_initializare.cpp
    src/item5_functii_generate.cpp
    src/item6_interzicere_copiere.cpp
)
target_include_directories(effective_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_compile_options(effective_cpp PRIVATE -Wall -Wextra)

# main program (the correct versions)
add_executable(Laborator_04 src/main.cpp)
target_link_libraries(Laborator_04 PRIVATE effective_cpp)
target_compile_options(Laborator_04 PRIVATE -Wall -Wextra)

# program with the bad classes
# no optimizations and address sanitizer, so the errors actually show up
# ordine_statica_club.cpp stays before ordine_statica_liga.cpp: link order decides the bug
add_executable(demo_greseli
    src/demo_greseli.cpp
    src/ordine_statica_club.cpp
    src/ordine_statica_liga.cpp
)
target_link_libraries(demo_greseli PRIVATE effective_cpp)
target_compile_options(demo_greseli PRIVATE -O0 -g -fsanitize=address)
target_link_options(demo_greseli PRIVATE -fsanitize=address)

# one target per forbidden piece of code, these must NOT build
# they are left out of the normal build: cmake --build build --target eroare_...
foreach(caz CONST_IN_CORP ATRIBUIRE_REFERINTA COPIE_PRIVATA COPIE_UNCOPYABLE COPIE_DELETE LINK_FRIEND)
    string(TOLOWER ${caz} nume)
    add_executable(eroare_${nume} EXCLUDE_FROM_ALL src/nu_compileaza.cpp)
    target_compile_definitions(eroare_${nume} PRIVATE ${caz})
    target_link_libraries(eroare_${nume} PRIVATE effective_cpp)
endforeach()
