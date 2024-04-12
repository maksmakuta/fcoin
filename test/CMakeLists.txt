project(fcoin_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(doctest REQUIRED)

add_executable(fcoin_test test_main.cpp)

target_include_directories(fcoin_test PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_test  PUBLIC fcoin_core)

target_compile_features(fcoin_test PRIVATE cxx_std_20)
target_link_libraries(fcoin_test PRIVATE doctest::doctest)
