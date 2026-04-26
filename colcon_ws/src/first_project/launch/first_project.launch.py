import os
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='first_project',
            executable='odometer',
            parameters=[{'use_sim_time': True}],
        ),
        # Node(
        #     package='first_project',
        #     executable='tf_error',
        # ),
        Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', [os.path.join('colcon_ws','src','first_project', 'config', 'first_project_config.rviz')]],
        )
    ])
