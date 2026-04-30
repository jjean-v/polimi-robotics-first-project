import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory


rviz_config = os.path.join(
    get_package_share_directory('first_project'),
    'config',
    'first_project_config.rviz'
)


def generate_launch_description():

    x = DeclareLaunchArgument("x", default_value="0.0")
    y = DeclareLaunchArgument("y", default_value="0.0")
    theta = DeclareLaunchArgument("theta", default_value="0.0")

    return LaunchDescription([
        x,
        y,
        theta,
        Node(
            package='first_project',
            executable='odometer',
            parameters=[
                {'use_sim_time': True},
                {'x': LaunchConfiguration('x')},
                {'y': LaunchConfiguration('y')},
                {'theta': LaunchConfiguration('theta')}
                ],
        ),
        Node(
            package='first_project',
            executable='tf_error',
        ),
        Node(
            package='rviz2',
            namespace='',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config],
        )
    ])
