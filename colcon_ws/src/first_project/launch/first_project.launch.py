from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='first_project',
            executable='odometer',
            parameters=[{'use_sim_time': True}],
        ),
    ])
