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

        goal_x_ = 5.0;  // Hedef x koordinatı
        goal_y_ = 5.0;  // Hedef y koordinatı
        goal_tolerance_ = 0.1; // Hedefe ulaşma toleransı
        reached_goal_ = false;

        moveTowardsGoal();
    }

private:
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        double x = msg->x;
        double y = msg->y;
        double distance_to_goal = std::sqrt(std::pow(x - goal_x_, 2) + std::pow(y - goal_y_, 2));

        if (!reached_goal_ && distance_to_goal <= goal_tolerance_)
        {
            reached_goal_ = true;
            RCLCPP_INFO(this->get_logger(), "TurtleBot reached the goal!");
            stopTurtleBot();
        }
    }

    void moveTowardsGoal()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 1.0; // İleri hareket hızı
        twist->angular.z = calculateAngularSpeed(); // Dönüş hızı

        publisher_->publish(std::move(twist));
    }

    void stopTurtleBot()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.0; // Dur
        twist->angular.z = 0.0;
        publisher_->publish(std::move(twist));
    }

    double calculateAngularSpeed()
    {
        // Hedef açısını hesapla
        double theta = std::atan2(goal_y_ - current_y_, goal_x_ - current_x_);

        // Mevcut açıyı al
        double current_theta = current_pose_->theta;

        // Hedef açısına dönme açısını hesapla
        double desired_theta = theta - current_theta;

        return 1.0 * desired_theta;
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    double goal_x_;
    double goal_y_;
    double goal_tolerance_;
    bool reached_goal_;
    double current_x_;
    double current_y_;
    turtlesim::msg::Pose::SharedPtr current_pose_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleBotController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}