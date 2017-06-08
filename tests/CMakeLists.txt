add_subdirectory(libfuzzyinput)

# Boost Test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_TEST_DYN_LINK)

# c++17
if(CMAKE_VERSION VERSION_LESS 3.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
endif()

# Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual -Wcast-qual -Wconversion -Wold-style-cast -Wno-unused-parameter")

# Sources
file(GLOB test_strtox_SOURCES "*.cpp")

# Target
add_definitions(-DCPP_ASSERT_FAIL=CPP_ASSERT_FAIL_THROW)
add_executable(test-strtox EXCLUDE_FROM_ALL ${test_strtox_SOURCES})
target_link_libraries(test-strtox strtox strtox-regex fuzzyinput ${Boost_LIBRARIES})

if(CMAKE_VERSION VERSION_GREATER 3.0)
  set_property(TARGET test-strtox PROPERTY CXX_STANDARD 14)
  set_property(TARGET test-strtox PROPERTY CXX_STANDARD_REQUIRED 17)
endif()

# make check
if (TARGET check)
else()
    add_custom_target(check)
endif()
add_custom_command(TARGET test-strtox
                   POST_BUILD
                   COMMAND test-strtox -i -s --detect_fp_exceptions=y -l message
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running test-strtox ..." VERBATIM)
add_dependencies(check test-strtox)


