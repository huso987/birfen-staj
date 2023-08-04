import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry


class TurtleBotController(Node):
    def __init__(self):
        super().__init__('turtlebot_controller')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.subscription = self.create_subscription(Odometry, 'odom', self.odometry_callback, 10)
        self.subscription  # To prevent unused variable warning
        self.target_position_x = 5.0  # Hedef X konumu
        self.target_position_y = 5.0  # Hedef Y konumu
        self.goal_tolerance = 0.1  # Hedefe ulaşma toleransı

    def odometry_callback(self, msg):
        # TurtleBot'un mevcut konumunu alır
        current_position_x = msg.pose.pose.position.x
        current_position_y = msg.pose.pose.position.y

        # Hedefe olan uzaklığı kontrol eder
        distance_to_target = ((current_position_x - self.target_position_x) * 2 + (current_position_y - self.target_position_y) * 2) ** 0.5

        if distance_to_target <= self.goal_tolerance:
            # Hedefe ulaşıldı, dur.
            self.stop_turtlebot()
        else:
            # Hedefe yönlendir
            self.move_turtlebot()

    def move_turtlebot(self):
        twist = Twist()
        twist.linear.x = 0.2  # İleri hareket hızı
        twist.angular.z = 0.2  # Dönüş hızı
        self.publisher_.publish(twist)

    def stop_turtlebot(self):
        twist = Twist()
        self.publisher_.publish(twist)
def main(args=None):
    rclpy.init(args=args)
    turtlebot_controller = TurtleBotController()
    rclpy.spin(turtlebot_controller)
    turtlebot_controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()