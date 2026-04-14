from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='sim'
        ),
        Node(
            package='cpp_tf_showcase',
            executable='turtle_tf_broadcaster'
        ),
        Node(
            package='cpp_tf_showcase',
            executable='sensor_static_tf_broadcaster'
        ),
        Node(
            package='cpp_tf_showcase',
            executable='tf_lookup_demo'
        ),
    ])
