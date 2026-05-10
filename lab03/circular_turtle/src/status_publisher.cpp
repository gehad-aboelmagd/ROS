#include <cmath>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include "circular_turtle/msg/robot_status.hpp"

class StatusPublisher : public rclcpp::Node
{
public:
    StatusPublisher(): Node("status_publisher")
    {
        pose_sub_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10,
                std::bind(&StatusPublisher::pose_callback, this, std::placeholders::_1));

        status_pub_ = this->create_publisher<circular_turtle::msg::RobotStatus>("/robot/status",10);

        RCLCPP_INFO(this->get_logger(), "Status publisher started");
    }

private:

    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        circular_turtle::msg::RobotStatus status;

        status.pose.x = msg->x;
        status.pose.y = msg->y;
        status.pose.theta = msg->theta;

        if (msg->linear_velocity > 0.01)
            status.state = "running";
        else
            status.state = "stopped";

        status.temperature =
            35.0 + std::sin(msg->theta);


        if (previous_theta_ > 3.0 &&
            msg->theta < -3.0)
        {
            lap_count_++;
        }

        previous_theta_ = msg->theta;
        status.lap_count = lap_count_;

        status_pub_->publish(status);

        RCLCPP_INFO(
        this->get_logger(),
        "STATUS -> state: %s temp: %.2f lap: %d",
        status.state.c_str(),
        status.temperature,
        status.lap_count
    );
    }

    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_sub_;
    rclcpp::Publisher<circular_turtle::msg::RobotStatus>::SharedPtr status_pub_;
    
    int lap_count_ = 0;
    double previous_theta_ = 0.0;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<StatusPublisher>());

    rclcpp::shutdown();

    return 0;
}