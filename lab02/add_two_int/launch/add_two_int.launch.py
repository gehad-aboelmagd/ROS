from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='add_two_int',
            executable='publisher1',
            name='minimal_publisher1',
            output='screen',
        ),
        Node(
            package='add_two_int',
            executable='publisher2',
            name='minimal_publisher2',
            output='screen',
        ),
        Node(
            package='add_two_int',
            executable='subscriber',
            name='minimal_subscriber',
            output='screen',
        )
    ])