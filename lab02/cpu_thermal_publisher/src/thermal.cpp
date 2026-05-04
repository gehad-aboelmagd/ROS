#include <fstream>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class ThermalStatePublisher : public rclcpp::Node
{
public:
    ThermalStatePublisher() : Node("thermal_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("cpu_temp", 10);

        timer_ = this->create_wall_timer(
            1s,
            std::bind(&ThermalStatePublisher::timer_callback, this)
        );
    }

private:
    void timer_callback()
    {

        std::ifstream file("/sys/class/thermal/cooling_device0/max_state");

        if (!file.is_open()) {
            RCLCPP_INFO(this->get_logger(), "Failed to open the file");
            return;
        }

        int temp;
        file >> temp;

        std_msgs::msg::Int32 message;
        message.data = temp;

        RCLCPP_INFO(this->get_logger(), "data: '%d'", temp);
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThermalStatePublisher>());
    rclcpp::shutdown();
    return 0;
}