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
            executable='tf_lookup_demo'
        ),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=[
                '--x', '0.2',
                '--y', '-0.2',
                '--z', '0.1',
                '--yaw', '0.0',
                '--pitch', '0.0',
                '--roll', '0.0',
                '--frame-id', 'turtle1',
                '--child-frame-id', 'laser',
            ]
        ),
    ])
