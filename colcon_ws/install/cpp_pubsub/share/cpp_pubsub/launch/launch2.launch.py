from launch import LaunchDescription
from launch.actions import GroupAction
from launch_ros.actions import Node, PushRosNamespace


def generate_launch_description():
    robot1_group = GroupAction(
        actions=[
            PushRosNamespace('robot1'),
            Node(
                package='cpp_pubsub',
                executable='talker',
                remappings=[('topic', 'chatter')],
            ),
            Node(
                package='cpp_pubsub',
                executable='listener',
                remappings=[('topic', 'chatter')],
            ),
        ]
    )

    robot2_group = GroupAction(
        actions=[
            PushRosNamespace('robot2'),
            Node(
                package='cpp_pubsub',
                executable='talker',
            ),
            Node(
                package='cpp_pubsub',
                executable='listener',
            ),
        ]
    )

    return LaunchDescription([
        robot1_group,
        robot2_group,
    ])
