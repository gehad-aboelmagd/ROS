#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <chrono>

using namespace std::chrono_literals;

class OdometryNode : public rclcpp::Node
{
public:
    OdometryNode() : Node("odometry_node"), x_pos_(0.0)
    {
        publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

        timer_ = this->create_wall_timer(
            100ms,
            std::bind(&OdometryNode::timer_callback, this)
        );
    }

private:
    void timer_callback()
    {
        nav_msgs::msg::Odometry msg;

        msg.header.frame_id = "odom";

        msg.pose.pose.position.x = x_pos_;
        msg.pose.pose.position.y = 0.0;
        msg.pose.pose.position.z = 0.0;

        msg.pose.pose.orientation.x = 0.0;
        msg.pose.pose.orientation.y = 0.0;
        msg.pose.pose.orientation.z = 0.0;
        msg.pose.pose.orientation.w = 1.0;

        publisher_->publish(msg);

        RCLCPP_INFO(this->get_logger(), "x = %.2f", x_pos_);

        x_pos_ += 0.1;
    }

    double x_;

    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    float x_pos_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OdometryNode>());
    rclcpp::shutdown();
    return 0;
}