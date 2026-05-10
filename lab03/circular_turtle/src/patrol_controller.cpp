#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_srvs/srv/empty.hpp>

using namespace std::placeholders;

class PatrolController: public rclcpp::Node
{
public:
    PatrolController(): Node("patrol_controller")
    {
        this->declare_parameter("linear_speed", 1.0);
        this->declare_parameter("angular_speed", 2.0);

        linear_speed_ = this->get_parameter("linear_speed").as_double();
        angular_speed_ = this->get_parameter("angular_speed").as_double();

        pub_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        timer_ = create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&PatrolController::control_loop, this));

        stop_srv_ = this->create_service<std_srvs::srv::Empty>(
            "/stop",
            std::bind(&PatrolController::stop_cb, this, _1, _2));

        cont_srv_ = this->create_service<std_srvs::srv::Empty>(
            "/continue",
            std::bind(&PatrolController::continue_cb, this, _1, _2));

        RCLCPP_INFO(get_logger(), "Patrol controller started");
    }
private:
    void control_loop()
    {
        geometry_msgs::msg::Twist msg;
        if(is_running_)
        {
            msg.linear.x = linear_speed_;
            msg.angular.z = angular_speed_;
        }
        else 
        {
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
        }
        pub_->publish(msg);
    }

    void stop_cb(const std::shared_ptr<std_srvs::srv::Empty::Request>,
        std::shared_ptr<std_srvs::srv::Empty::Response>)
    {
        is_running_ = false;
        RCLCPP_INFO(get_logger(), "Stopped");
    }

    void continue_cb(const std::shared_ptr<std_srvs::srv::Empty::Request>,
        std::shared_ptr<std_srvs::srv::Empty::Response>)
    {
        is_running_ = true;
        RCLCPP_INFO(get_logger(), "Running");
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    double linear_speed_ = 1.0, angular_speed_ = 2.0;

    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr stop_srv_;
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr cont_srv_;
    bool is_running_ = true;    
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PatrolController>());
    rclcpp::shutdown();
    return 0;
}