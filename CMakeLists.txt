cmake_minimum_required(VERSION 2.8.11)

if(CMAKE_VERSION VERSION_GREATER 3.2)
  cmake_policy(VERSION 3.2)
  project(strtox VERSION 0.1 LANGUAGES CXX)
else()
  project(strtox CXX)
endif()

if(CMAKE_VERSION VERSION_LESS 3.0)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# strtox
add_library(strtox STATIC strtox/strtox.cpp)
target_include_directories(strtox INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  set_property(TARGET strtox PROPERTY CXX_STANDARD 14)
  set_property(TARGET strtox PROPERTY CXX_STANDARD_REQUIRED 17)
endif()

# strtox
add_library(strtox-asc STATIC strtox/asc.cpp)
target_include_directories(strtox-asc INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  set_property(TARGET strtox-asc PROPERTY CXX_STANDARD 14)
  set_property(TARGET strtox-asc PROPERTY CXX_STANDARD_REQUIRED 17)
endif()

# strtox-regex
add_library(strtox-regex STATIC strtox/regex.cpp)
target_include_directories(strtox-regex INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  set_property(TARGET strtox-regex PROPERTY CXX_STANDARD 14)
  set_property(TARGET strtox-regex PROPERTY CXX_STANDARD_REQUIRED 17)
endif()

# strtox-xsd
add_library(strtox-xsd STATIC strtox/xsd.cpp)
target_include_directories(strtox-xsd INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  set_property(TARGET strtox-xsd PROPERTY CXX_STANDARD 14)
  set_property(TARGET strtox-xsd PROPERTY CXX_STANDARD_REQUIRED 17)
endif()

add_subdirectory(tests)
add_subdirectory(benchmarks)

