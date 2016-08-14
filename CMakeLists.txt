cake_minimum_required(VERSION 2.8.11)
project(mono_slam)
find_package(OpenCV REQUIRED)

include_directories(include)
link_directories(src)

add_executable(car_exercise src/car_exercise.cpp) 
target_link_libraries(car_exercise ${OpenCV_LIBS})
set_target_properties(car_exercise PROPERTIES COMPILE_FLAGS "-g -std=c++11 -Wall -pedantic")

install(TARGETS car_exercise DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
