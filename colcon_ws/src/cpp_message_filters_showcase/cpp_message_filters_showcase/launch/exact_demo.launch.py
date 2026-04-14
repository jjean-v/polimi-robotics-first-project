from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_message_filters_showcase',
            executable='exact_pair_publisher',
            output='screen',
        ),
        Node(
            package='cpp_message_filters_showcase',
            executable='exact_sync_node',
            output='screen',
            parameters=[{
                'queue_size': 10,
            }],
        ),
    ])
