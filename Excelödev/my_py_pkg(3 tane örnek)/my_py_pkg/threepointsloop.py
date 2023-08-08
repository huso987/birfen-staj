import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import math
class PointToPointBot(Node):
    def __init__(self):
        super().__init__('point_to_point_bot')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.points = [
            (1.0, 0.0),  
            (0.0, 1.0),  
            (-1.0, 0.0)  
        ]
        self.current_point_index = 0

    def move_to_point(self, target_x, target_y):
        twist = Twist()
        rate = self.create_rate(10)

        while rclpy.ok():
            x, y = self.get_robot_position()  
            distance_to_target = ((target_x - x) * 2 + (target_y - y) * 2) ** 0.5

            if distance_to_target < 0.1:
                
                self.current_point_index = (self.current_point_index + 1) % len(self.points)
                target_x, target_y = self.points[self.current_point_index]
            
            twist.linear.x = 0.2  # İleri hareket hızı
            twist.angular.z = self.calculate_angular_speed(target_x, target_y, x, y)  # Dönüş hızı
            self.publisher_.publish(twist)
            rate.sleep()

    def calculate_angular_speed(self, target_x, target_y, current_x, current_y):
        desired_theta = math.atan2(target_y - current_y, target_x - current_x)
        current_theta = self.get_robot_orientation()
        return 0.5 * (desired_theta - current_theta)

    def get_robot_position(self):
        
        return 0.0, 0.0

    def get_robot_orientation(self):
        
        return 0.0

def main(args=None):
    rclpy.init(args=args)
    bot_node = PointToPointBot()
    target_x, target_y = bot_node.points[bot_node.current_point_index]
    bot_node.move_to_point(target_x, target_y)
    bot_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()