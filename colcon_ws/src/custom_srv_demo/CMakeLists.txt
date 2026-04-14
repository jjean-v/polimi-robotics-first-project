cmake_minimum_required(VERSION 3.8)
project(custom_srv_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(srv_files
  "srv/CanMove.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${srv_files}
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(can_move_server src/can_move_server.cpp)
ament_target_dependencies(can_move_server rclcpp)

add_executable(can_move_client src/can_move_client.cpp)
ament_target_dependencies(can_move_client rclcpp)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)

target_link_libraries(can_move_server "${cpp_typesupport_target}")
target_link_libraries(can_move_client "${cpp_typesupport_target}")

install(TARGETS
  can_move_server
  can_move_client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
