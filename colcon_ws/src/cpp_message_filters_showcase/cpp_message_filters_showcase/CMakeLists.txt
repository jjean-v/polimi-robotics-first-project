cmake_minimum_required(VERSION 3.8)
project(cpp_message_filters_showcase)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(message_filters REQUIRED)

add_executable(unsync_sensor_publisher src/unsync_sensor_publisher.cpp)
ament_target_dependencies(unsync_sensor_publisher rclcpp sensor_msgs)

add_executable(exact_pair_publisher src/exact_pair_publisher.cpp)
ament_target_dependencies(exact_pair_publisher rclcpp sensor_msgs)

add_executable(exact_sync_node src/exact_sync_node.cpp)
ament_target_dependencies(exact_sync_node rclcpp sensor_msgs message_filters)

add_executable(approximate_sync_node src/approximate_sync_node.cpp)
ament_target_dependencies(approximate_sync_node rclcpp sensor_msgs message_filters)

install(TARGETS
  unsync_sensor_publisher
  exact_pair_publisher
  exact_sync_node
  approximate_sync_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
