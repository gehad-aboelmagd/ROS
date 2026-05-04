#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

#define MAX_LIMIT_LINEAR        1.0
#define MAX_LIMIT_ANGULAR       1.5

using std::placeholders::_1;

class CmdVelocityLimiter: public rclcpp::Node 
{
public:
    CmdVelocityLimiter(): Node("velocity_limiter")
    {
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel", 
            10, 
            std::bind(&CmdVelocityLimiter::velocity_callback, this, _1)
        );
    }

private:
    void velocity_callback(const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        double linear_x = msg->linear.x;
        double linear_y = msg->linear.y;
        double linear_z = msg->linear.z;

        double angular_x = msg->angular.x;
        double angular_y = msg->angular.y;
        double angular_z = msg->angular.z;

        if(linear_x > MAX_LIMIT_LINEAR || linear_y > MAX_LIMIT_LINEAR || linear_z > MAX_LIMIT_LINEAR ||
        angular_x > MAX_LIMIT_ANGULAR || angular_y > MAX_LIMIT_ANGULAR || angular_z > MAX_LIMIT_ANGULAR)
        {
            RCLCPP_INFO(
                this->get_logger(),
                "Exceeding Limit:\nLinear: [%.2f, %.2f, %.2f] | Angular: [%.2f, %.2f, %.2f]",
                linear_x, linear_y, linear_z,
                angular_x, angular_y, angular_z
            );
        }
    }

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CmdVelocityLimiter>());
    rclcpp::shutdown();
    return 0;
}