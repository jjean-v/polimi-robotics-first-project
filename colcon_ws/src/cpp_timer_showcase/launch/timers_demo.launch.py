from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_timer_showcase',
            executable='basic_timer_node',
            output='screen',
        ),
        Node(
            package='cpp_timer_showcase',
            executable='multi_timer_node',
            output='screen',
        ),
        Node(
            package='cpp_timer_showcase',
            executable='control_timer_node',
            output='screen',
        ),
    ])
