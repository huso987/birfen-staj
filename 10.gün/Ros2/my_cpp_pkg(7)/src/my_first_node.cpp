#include "rclcpp/rclcpp.hpp"
#include <iostream>

class Mynode: public rclcpp::Node
{
public:
    Mynode(): Node("cpp_deneme"){
     RCLCPP_INFO(this-> get_logger(),"merhaba cpp");
     timer_=this->create_wall_timer(std::chrono::seconds(1),
                                    std::bind(&Mynode::timerCallback,this));
    } 

private:
  void timerCallback(){
    counter_++;
    RCLCPP_INFO(this-> get_logger(),"nasilsin %d", counter_);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  int counter_;
};


int main(int argc,char **argv){
    rclcpp::init(argc,argv);
    auto node=std::make_shared<Mynode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}