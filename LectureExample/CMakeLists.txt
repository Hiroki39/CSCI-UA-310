cmake_minimum_required (VERSION 3.15)

project (Homework)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -std=c++14 -g)

# Find all cpp files and store in list mains
file(GLOB mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(mainfile IN LISTS mains)
  if(testclosest_pair.cpp STREQUAL ${mainfile})
      add_executable(testclosest_pair testclosest_pair.cpp closest_pair.cpp point.cpp)
  elseif(testpolygon.cpp STREQUAL ${mainfile})
      add_executable(testpolygon polygon.cpp testpolygon.cpp point.cpp)
  else()
    # Get file name without directory
      get_filename_component(mainname ${mainfile} NAME_WE)
      add_executable(${mainname} ${mainfile})
  endif()
endforeach()
