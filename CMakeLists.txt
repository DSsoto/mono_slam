cmake_minimum_required(VERSION 2.8.11)
project(mono_slam)
find_package(OpenCV REQUIRED)
find_package( Boost REQUIRED filesystem system)


include_directories(include ${Boost_INCLUDE_DIRS})
link_directories(src)

add_executable(mono_slam src/demo.cpp src/mono_slam_gpu.cpp src/mono_slam.cpp src/utils.cpp) 
target_link_libraries(mono_slam ${OpenCV_LIBS} ${Boost_LIBRARIES})
set_target_properties(mono_slam PROPERTIES COMPILE_FLAGS "-g -std=c++11 -Wall -pedantic")

install(TARGETS mono_slam DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
