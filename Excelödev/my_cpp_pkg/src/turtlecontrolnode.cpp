#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>

class TurtleControlNode : public rclcpp::Node
{
public:
    TurtleControlNode(const std::string &turtle_name, double goal_x, double goal_y)
        : Node("turtle_control_node_" + turtle_name)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(turtle_name + "/cmd_vel", 10);
        subscription_ = this->create_subscription<turtlesim::msg::Pose>(
            turtle_name + "/pose", 10, std::bind(&TurtleControlNode::poseCallback, this, std::placeholders::_1));
        
        goal_x_ = goal_x;
        goal_y_ = goal_y;
        goal_tolerance_ = 0.1;
        reached_goal_ = false;

        moveTowardGoal();
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
            RCLCPP_INFO(this->get_logger(), "Robot reached the goal: %s", this->get_namespace());
            stopRobot();
        }
    }

    void moveTowardGoal()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 1.0; // İleri hareket hızı
        twist->angular.z = 0.0; // Dönüş hızı

        publisher_->publish(std::move(twist));
    }

    void stopRobot()
    {
        auto twist = std::make_unique<geometry_msgs::msg::Twist>();
        twist->linear.x = 0.0; // İleri hareket hızı
        twist->angular.z = 0.0; // Dönüş hızı

        publisher_->publish(std::move(twist));
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    double goal_x_;
    double goal_y_;
    double goal_tolerance_;
    bool reached_goal_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

   
    double goal_x_turtle1 = 5.0;
    double goal_y_turtle1 = 5.0;

  
    double goal_x_turtle2 = 8.0;
    double goal_y_turtle2 = 2.0;

    auto turtle1_node = std::make_shared<TurtleControlNode>("turtle1", goal_x_turtle1, goal_y_turtle1);
    auto turtle2_node = std::make_shared<TurtleControlNode>("turtle2", goal_x_turtle2, goal_y_turtle2);

    rclcpp::spin(turtle1_node);
    rclcpp::spin(turtle2_node);

    rclcpp::shutdown();
    return 0;
}