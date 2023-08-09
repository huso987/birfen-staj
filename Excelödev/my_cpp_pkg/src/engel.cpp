#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <cmath>

class RobotController : public rclcpp::Node
{
public:
    RobotController()
        : Node("robot_controller")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "scan", 10, std::bind(&RobotController::scanCallback, this, std::placeholders::_1));

        is_obstacle_detected_ = false;

        moveForward();
    }

private:
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // Orta hücreyi kullanarak engel kontrolü yap
        size_t middle_index = msg->ranges.size() / 2;
        float middle_range = msg->ranges[middle_index];

        if (middle_range < obstacle_threshold_)
        {
            is_obstacle_detected_ = true;
            turn90Degrees();
            is_obstacle_detected_ = false;
            moveForward();
        }
    }

    void moveForward()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.5; // İleri hareket hızı (0.5 m/s)
        twist->angular.z = 0.0; // Dönüş hızı (0 derece/s)
        publisher_->publish(std::move(twist));
    }

    void turn90Degrees()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.0; // İleri hareket hızı (0 m/s)
        twist->angular.z = 1.5708; // 90 derece dönüş hızı (1.5708 rad/s)
        publisher_->publish(std::move(twist));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    bool is_obstacle_detected_;
    float obstacle_threshold_ = 0.5; // Engeli algılama mesafe eşiği
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}