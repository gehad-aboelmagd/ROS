#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class MinimalSubscriber : public rclcpp::Node
{
public:
    MinimalSubscriber() : Node("minimal_subscriber"), got_topic_1_(false)
    {
        subscriber1_ = this->create_subscription<std_msgs::msg::Int32>(
            "topic1", 10,
            [this](std_msgs::msg::Int32::SharedPtr msg) {
                this->topic_callback(msg, "topic1");
            });

        subscriber2_ = this->create_subscription<std_msgs::msg::Int32>(
            "topic2", 10,
            [this](std_msgs::msg::Int32::SharedPtr msg) {
                this->topic_callback(msg, "topic2");
            });
    }

private:
    void topic_callback(const std_msgs::msg::Int32::SharedPtr msg, std::string topic)
    {

        RCLCPP_INFO(this->get_logger(),
                    "Received from %s: %d",
                    topic.c_str(), msg->data);

        if (topic == "topic1")
        {
            last_topic1_ = msg->data;
            got_topic_1_ = true;
        }
        else if (topic == "topic2")
        {
            last_topic2_ = msg->data;
            got_topic_2_ = true;
        }

        if (got_topic_1_ && got_topic_2_)
        {
            int sum = last_topic1_ + last_topic2_;

            RCLCPP_INFO(this->get_logger(),
                        "SUM = %d", sum);

            // reset AFTER using both
            got_topic_1_ = false;
            got_topic_2_ = false;
        }
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber1_;
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscriber2_;

    int last_topic1_;
    int last_topic2_;
    bool got_topic_1_;
    bool got_topic_2_;
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}