#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>
#include <cmath>

class TurtleBotController : public rclcpp::Node
{
public:
    TurtleBotController()
        : Node("turtlebot_controller")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "pose", 10, std::bind(&TurtleBotController::poseCallback, this, std::placeholders::_1));

        target_distance_ = 1.0;  // Hedef mesafe (1 metre)
        current_distance_ = 0.0;

        moveTurtleBot();
    }

private:
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        // Mevcut pozisyonu al
        double x = msg->x;
        double y = msg->y;

        // Hedef pozisyon ile mesafeyi hesapla
        current_distance_ = std::sqrt(std::pow(x - start_x_, 2) + std::pow(y - start_y_, 2));

        if (current_distance_ >= target_distance_)
        {
            RCLCPP_INFO(this->get_logger(), "TurtleBot reached the target distance!");
            stopTurtleBot();
        }
    }

    void moveTurtleBot()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.5; // İleri hareket hızı (0.5 m/s)
        twist->angular.z = 0.0;
        publisher_->publish(std::move(twist));

        start_x_ = current_x_;
        start_y_ = current_y_;
    }

    void stopTurtleBot()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.0; // Dur
        twist->angular.z = 0.0;
        publisher_->publish(std::move(twist));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    double target_distance_;
    double current_distance_;
    double start_x_;
    double start_y_;
    double current_x_;
    double current_y_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleBotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}