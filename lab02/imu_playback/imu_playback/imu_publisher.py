import os
import csv
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu
from ament_index_python.packages import get_package_share_directory

class IMU_Publisher(Node):
    def __init__(self, path):
        super().__init__("hello_node")

        print("My file:***************", __file__)

        # self.path_ = os.path.abspath(
        #     os.path.join(os.path.dirname(__file__), '..', 'data', path)
        # )
        
        package_share_dir = get_package_share_directory('imu_playback')
        self.path_ = os.path.join(package_share_dir, 'data', 'imu_data.csv')
        

        with open(self.path_, mode='r') as f:
            self.data_ = list(csv.DictReader(f))

        self.index_ = 0

        self.publisher_ = self.create_publisher(Imu, "/imu/data", 10)
        self.timer_ = self.create_timer(0.1, self.timer_callback)

    def timer_callback(self):
        row = self.data_[self.index_]
        self.index_ = (self.index_ + 1) % len(self.data_)

        msg = Imu()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "base_link"

        msg.orientation.x = float(row['orient_x'])
        msg.orientation.y = float(row['orient_y'])
        msg.orientation.z = float(row['orient_z'])
        msg.orientation.w = float(row['orient_w'])

        msg.angular_velocity.x = float(row['gyro_x'])
        msg.angular_velocity.y = float(row['gyro_y'])
        msg.angular_velocity.z = float(row['gyro_z'])

        msg.linear_acceleration.x = float(row['accel_x'])
        msg.linear_acceleration.y = float(row['accel_y'])
        msg.linear_acceleration.z = float(row['accel_z'])

        self.publisher_.publish(msg)

        self.get_logger().info(
            f"Published IMU z_accel={msg.linear_acceleration.z:.2f}"
        )


def main(args=None):
    rclpy.init(args=args)
    node = IMU_Publisher("imu_data.csv")
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
