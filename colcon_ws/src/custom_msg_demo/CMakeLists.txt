cmake_minimum_required(VERSION 3.8)
project(custom_msg_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/RobotStatus.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(status_publisher src/status_publisher.cpp)
ament_target_dependencies(status_publisher rclcpp)

add_executable(status_subscriber src/status_subscriber.cpp)
ament_target_dependencies(status_subscriber rclcpp)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(status_publisher "${cpp_typesupport_target}")
target_link_libraries(status_subscriber "${cpp_typesupport_target}")

install(TARGETS
  status_publisher
  status_subscriber
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
