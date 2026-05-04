import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from std_msgs.msg import Bool

class DistanceSubscriber(Node):
    def __init__(self):
        super().__init__("distance_subscriber")
        self.subscriber = self.create_subscription(
            Float32, 
            "/sensor/distance", 
            self.listener_callback, 
            10
        )
        self.publisher_ = self.create_publisher(
            Bool,
            "/cmd/stop",
            10
        )

    
    def listener_callback(self, message):
        self.get_logger().info(f"Got: {message.data: .3f}")
        subscriber_message = Bool()
        subscriber_message.data = True if message.data > 0.2 else False
        self.publisher_.publish(subscriber_message)


def main(args=None):
    rclpy.init(args=args)

    node = DistanceSubscriber()
    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()