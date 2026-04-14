cmake_minimum_required(VERSION 3.8)
project(cpp_tf_showcase)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)

add_executable(turtle_tf_broadcaster src/turtle_tf_broadcaster.cpp)
ament_target_dependencies(
  turtle_tf_broadcaster
  rclcpp
  geometry_msgs
  tf2
  tf2_ros
  turtlesim
)

add_executable(sensor_static_tf_broadcaster src/sensor_static_tf_broadcaster.cpp)
ament_target_dependencies(
  sensor_static_tf_broadcaster
  rclcpp
  geometry_msgs
  tf2
  tf2_ros
)

add_executable(tf_lookup_demo src/tf_lookup_demo.cpp)
ament_target_dependencies(
  tf_lookup_demo
  rclcpp
  geometry_msgs
  tf2
  tf2_ros
)

install(
  TARGETS
    turtle_tf_broadcaster
    sensor_static_tf_broadcaster
    tf_lookup_demo
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
