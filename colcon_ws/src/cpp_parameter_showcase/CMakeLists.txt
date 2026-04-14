cmake_minimum_required(VERSION 3.8)
project(cpp_parameter_showcase)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rcl_interfaces REQUIRED)

add_executable(basic_parameters_node src/basic_parameters_node.cpp)
ament_target_dependencies(basic_parameters_node rclcpp rcl_interfaces)

add_executable(validated_parameters_node src/validated_parameters_node.cpp)
ament_target_dependencies(validated_parameters_node rclcpp rcl_interfaces)

add_executable(parameter_monitor_node src/parameter_monitor_node.cpp)
ament_target_dependencies(parameter_monitor_node rclcpp rcl_interfaces)

add_executable(flexible_parameters_node src/flexible_parameters_node.cpp)
ament_target_dependencies(flexible_parameters_node rclcpp rcl_interfaces)

add_executable(local_only_parameters_node src/local_only_parameters_node.cpp)
ament_target_dependencies(local_only_parameters_node rclcpp rcl_interfaces)

install(TARGETS
  basic_parameters_node
  validated_parameters_node
  parameter_monitor_node
  flexible_parameters_node
  local_only_parameters_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
