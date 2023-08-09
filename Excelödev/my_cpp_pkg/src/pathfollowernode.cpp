#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>

class PathFollowerNode : public rclcpp::Node
{
public:
    PathFollowerNode()
        : Node("path_follower_node")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10, std::bind(&PathFollowerNode::poseCallback, this, std::placeholders::_1));

        // Belirli bir yol (koordinatlar) tanımlayın
        path_ = {{2.0, 2.0}, {5.0, 5.0}, {8.0, 2.0}, {5.0, 2.0}};
        current_path_index_ = 0;
        goal_tolerance_ = 0.1;
    }

private:
    void poseCallback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        double x = msg->x;
        double y = msg->y;
        double goal_x = path_[current_path_index_].first;
        double goal_y = path_[current_path_index_].second;

        double distance_to_goal = std::sqrt(std::pow(x - goal_x, 2) + std::pow(y - goal_y, 2));

        if (distance_to_goal <= goal_tolerance_)
        {
            if (current_path_index_ < path_.size() - 1)
            {
                current_path_index_++;
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "Turtlesim hedef yolu tamamladı!");
                rclcpp::shutdown();
            }
        }
        else
        {
            moveTowardGoal(goal_x, goal_y);
        }
    }

    void moveTowardGoal(double goal_x, double goal_y)
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = calculateLinearSpeed(goal_x, goal_y);
        twist->angular.z = calculateAngularSpeed(goal_x, goal_y);

        publisher_->publish(std::move(twist));
    }

    double calculateLinearSpeed(double goal_x, double goal_y)
    {
        return 1.0; // İleri hareket hızı
    }

    double calculateAngularSpeed(double goal_x, double goal_y)
    {
        auto current_pose = getCurrentPose();
        double desired_theta = std::atan2(goal_y - current_pose[1], goal_x - current_pose[0]);
        return 1.0 * (desired_theta - current_pose[2]); // Dönüş hızı
    }

    std::array<double, 3> getCurrentPose()
    {
        
        return {0.0, 0.0, 0.0}; 
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    std::vector<std::pair<double, double>> path_;
    size_t current_path_index_;
    double goal_tolerance_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PathFollowerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}