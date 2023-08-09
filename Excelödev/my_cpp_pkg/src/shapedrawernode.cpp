#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/set_background.hpp"
#include <string>
#include <iostream>

using namespace std::chrono_literals;

class ShapeDrawerNode : public rclcpp::Node
{
public:
    ShapeDrawerNode()
        : Node("shape_drawer_node")
    {
        publisher_ = create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        subscription_ = create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10, std::bind(&ShapeDrawerNode::pose_callback, this, std::placeholders::_1));
        background_color_changed_ = false;

        RCLCPP_INFO(this->get_logger(), "Enter the shape you want to draw (square, circle, triangle): ");
        std::cin >> shape_name_;

        draw_shape(shape_name_);
        set_background_color(0, 255, 0); // Arka plan rengini yeşil olarak değiştir
    }

private:
    void pose_callback(const turtlesim::msg::Pose::SharedPtr msg)
    {
        if (!background_color_changed_)
        {
            RCLCPP_INFO(this->get_logger(), "Arka plan rengi değişti!");
            background_color_changed_ = true;
        }
    }

    void draw_shape(const std::string &shape_name)
    {
        rclcpp::Rate rate(1);

        geometry_msgs::msg::Twist twist;
        twist.linear.x = 2.0;  // İleri hareket hızı
        twist.angular.z = 1.0; // Dönüş hızı

        if (shape_name == "kare")
        {
            for (int i = 0; i < 4; ++i)
            {
                publisher_->publish(twist);
                rate.sleep();
                twist.angular.z = -twist.angular.z;
            }
        }
        else if (shape_name == "yuvarlak")
        {
            for (int i = 0; i < 10; ++i)
            {
                publisher_->publish(twist);
                rate.sleep();
            }
        }
        else if (shape_name == "üçgen")
        {
            for (int i = 0; i < 3; ++i)
            {
                publisher_->publish(twist);
                rate.sleep();
                twist.angular.z = -2.0;
                rate.sleep();
            }
        }

        RCLCPP_INFO(this->get_logger(), "%s çizimi tamamlandı!", shape_name.c_str());
    }

    void set_background_color(int r, int g, int b)
    {
        auto set_background_client = create_client<turtlesim::srv::SetBackground>("clear");
        while (!set_background_client->wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Client interrupted while waiting for service.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Waiting for the service to appear...");
        }

        auto request = std::make_shared<turtlesim::srv::SetBackground::Request>();
        request->r = r;
        request->g = g;
        request->b = b;

        auto future = set_background_client->async_send_request(request);
        rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
    bool background_color_changed_;
    std::string shape_name_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ShapeDrawerNode>());
    rclcpp::shutdown();
    return 0;
}