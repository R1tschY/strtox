add_executable(benchmark-float float.cpp)
target_link_libraries(benchmark-float strtox benchmark)

add_executable(benchmark-double double.cpp)
target_link_libraries(benchmark-double strtox benchmark)
