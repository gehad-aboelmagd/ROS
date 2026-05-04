import random
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32

class DistanceSensor(Node):
    def __init__(self):
        super().__init__("distance_sensor")
        self.publisher_ = self.create_publisher(Float32, "/sensor/distance", 10)
        self.timer = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        message = Float32()
        message.data = random.uniform(0.03, 5.0)
        self.publisher_.publish(message)
        self.get_logger().info(f'Publishing: {message.data}')


def main(args=None):
    print('Hi from my_python_pkg.')
    rclpy.init(args=args)
    node = DistanceSensor()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
