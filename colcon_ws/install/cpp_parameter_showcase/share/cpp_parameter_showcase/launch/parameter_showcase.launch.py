from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    config_file = PathJoinSubstitution([
        FindPackageShare('cpp_parameter_showcase'),
        'config',
        'demo_params.yaml'
    ])

    return LaunchDescription([
        Node(
            package='cpp_parameter_showcase',
            executable='basic_parameters_node',
            output='screen',
            parameters=[config_file],
        ),
        Node(
            package='cpp_parameter_showcase',
            executable='validated_parameters_node',
            output='screen',
            parameters=[config_file],
        ),
        Node(
            package='cpp_parameter_showcase',
            executable='parameter_monitor_node',
            output='screen',
            parameters=[{'target_node': '/validated_parameters_node'}],
        ),
        Node(
            package='cpp_parameter_showcase',
            executable='flexible_parameters_node',
            output='screen',
            parameters=[config_file],
        ),
    ])
