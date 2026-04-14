cmake_minimum_required(VERSION 3.8)
project(cpp_timer_showcase)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(basic_timer_node src/basic_timer_node.cpp)
ament_target_dependencies(basic_timer_node rclcpp)

add_executable(multi_timer_node src/multi_timer_node.cpp)
ament_target_dependencies(multi_timer_node rclcpp)

add_executable(control_timer_node src/control_timer_node.cpp)
ament_target_dependencies(control_timer_node rclcpp)

add_executable(callback_group_timers_node src/callback_group_timers_node.cpp)
ament_target_dependencies(callback_group_timers_node rclcpp)

install(TARGETS
  basic_timer_node
  multi_timer_node
  control_timer_node
  callback_group_timers_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
