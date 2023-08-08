import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Point
import math

class ObstacleAvoidanceBot(Node):
    def __init__(self):
        super().__init__('obstacle_avoidance_bot')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.subscription = self.create_subscription(Point, 'obstacle_detected', self.obstacle_callback, 10)
        self.subscription  
        self.twist = Twist()
        self.obstacle_detected = False

    def obstacle_callback(self, msg):
        self.obstacle_detected = True

    def move_forward(self):
        self.twist.linear.x = 0.2  # İleri hareket hızı
        self.twist.angular.z = 0.0  # Dönüş hızı
        self.publisher_.publish(self.twist)

    def turn_90_degrees(self):
        self.twist.linear.x = 0.0  # İleri hareket hızı
        self.twist.angular.z = math.pi / 2  # 90 derece dönüş hizi
        self.publisher_.publish(self.twist)

    def main_loop(self):
        rate = self.create_rate(10)
        while rclpy.ok():
            if not self.obstacle_detected:
                self.move_forward()
            else:
                self.turn_90_degrees()
                self.obstacle_detected = False
            rate.sleep()

def main(args=None):
    rclpy.init(args=args)
    bot_node = ObstacleAvoidanceBot()
    bot_node.main_loop()
    bot_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()