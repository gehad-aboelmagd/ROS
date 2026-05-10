from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        Node(
            package='turtlesim',
            executable='turtlesim_node'
        ),

        Node(
            package='circular_turtle',
            executable='patrol',
            name='patrol_controller',

            parameters=[
                {
                    "linear_speed": 3.0,
                    "angular_speed": 0.8
                }
            ]
        )
    ])