#include "rclcpp/rclcpp.hpp"
#include <stdio.h>
int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node=std::make_shared<rclcpp::Node>("cpp_deneme");
    RCLCPP_INFO(node-> get_logger(),"merhaba cpp");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}