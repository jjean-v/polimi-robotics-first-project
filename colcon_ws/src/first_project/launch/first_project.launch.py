from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    rviz_config = PathJoinSubstitution([
        FindPackageShare('first_project'),
        'rviz',
        'first_project.rviz'
    ])

    return LaunchDescription([
        Node(
            package='first_project',
            executable='odometer'
        ),
        Node(
            package='first_project',
            executable='tf_error'
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            arguments=['-d', rviz_config],
            output='screen'
        ),

    ])
