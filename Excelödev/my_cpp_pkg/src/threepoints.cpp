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

        waypoints_ = {
            {1.0, 1.0},  // İlk nokta
            {5.0, 5.0},  // İkinci nokta
            {8.0, 2.0}   // Üçüncü nokta
        };
        current_waypoint_ = 0;

        moveTurtleBot();
    }

private:
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        // Mevcut pozisyonu al
        double x = msg->x;
        double y = msg->y;

        double target_x = waypoints_[current_waypoint_].first;
        double target_y = waypoints_[current_waypoint_].second;

        // Hedef pozisyon ile mesafeyi hesapla
        double distance_to_target = std::sqrt(std::pow(x - target_x, 2) + std::pow(y - target_y, 2));

        if (distance_to_target <= target_tolerance_)
        {
            current_waypoint_ = (current_waypoint_ + 1) % waypoints_.size(); // Sonraki noktaya geç
            moveTurtleBot();
        }
    }

    void moveTurtleBot()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        double target_x = waypoints_[current_waypoint_].first;
        double target_y = waypoints_[current_waypoint_].second;

        // Hedef noktaya doğru hareket et
        double angle_to_target = std::atan2(target_y - current_y_, target_x - current_x_);
        twist->linear.x = 0.5; // İleri hareket hızı (0.5 m/s)
        twist->angular.z = angle_to_target;
        publisher_->publish(std::move(twist));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    std::vector<std::pair<double, double>> waypoints_;
    int current_waypoint_;
    double current_x_;
    double current_y_;
    double target_tolerance_ = 0.1;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleBotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}