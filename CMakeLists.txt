cmake_minimum_required(VERSION 2.8.3)
project(ros_service_examples)

find_package(catkin REQUIRED COMPONENTS roscpp roslib message_generation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

add_service_files(FILES
  MP3InventoryService.srv)

generate_messages()

catkin_package(
  CATKIN_DEPENDS roscpp roslib message_runtime)
  
include_directories(${catkin_INCLUDE_DIRS})
add_executable(mp3_inventory src/mp3_inventory.cpp)
add_executable(mp3_controller src/mp3_controller.cpp)

target_link_libraries(mp3_inventory
  ${catkin_LIBRARIES})

target_link_libraries(mp3_controller
  ${catkin_LIBRARIES})
