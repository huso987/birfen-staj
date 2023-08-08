import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
import math

class MoveAndStopNode(Node):
    def __init__(self):
        super().__init__('move_and_stop_node')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.timer = self.create_timer(1.0, self.move_turtle)

        self.linear_speed = 0.2  # İleri hareket hızı
        self.distance_to_move = 1.0  # 1 metre

        self.current_distance = 0.0
        self.is_moving = False

    def move_turtle(self):
        if not self.is_moving:
            self.is_moving = True
            self.current_distance = 0.0
            self.move_forward()

    def move_forward(self):
        twist = Twist()
        twist.linear.x = self.linear_speed
        self.publisher_.publish(twist)

    def stop_turtle(self):
        twist = Twist()
        twist.linear.x = 0.0
        self.publisher_.publish(twist)
        self.is_moving = False

    def update_distance(self, msg):
        if self.is_moving:
            self.current_distance += abs(msg.linear.x)
            if self.current_distance >= self.distance_to_move:
                self.stop_turtle()

def main(args=None):
    rclpy.init(args=args)
    move_and_stop_node = MoveAndStopNode()
    rclpy.spin(move_and_stop_node)
    move_and_stop_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()