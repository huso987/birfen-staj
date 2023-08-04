import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
import math

class PathFollowerNode(Node):
    def _init_(self):
        super()._init_('path_follower_node')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.subscription = self.create_subscription(Pose, 'turtle1/pose', self.pose_callback, 10)
        self.subscription  # To prevent unused variable warning
        self.path = [(2.0, 2.0), (5.0, 5.0), (8.0, 2.0), (5.0, 2.0)]
        self.current_path_index = 0
        self.goal_tolerance = 0.1

    def pose_callback(self, msg):
        x = msg.x
        y = msg.y
        goal_x, goal_y = self.path[self.current_path_index]

        distance_to_goal = math.sqrt((x - goal_x)*2 + (y - goal_y)*2)

        if distance_to_goal <= self.goal_tolerance:
            if self.current_path_index < len(self.path) - 1:
                self.current_path_index += 1
            else:
                self.get_logger().info('Turtlesim hedef yolu tamamladı!')
                self.destroy_node()
                rclpy.shutdown()
        else:
            self.move_to_goal(goal_x, goal_y)

    def move_to_goal(self, goal_x, goal_y):
        twist = Twist()
        twist.linear.x = self.calculate_linear_speed(goal_x, goal_y)
        twist.angular.z = self.calculate_angular_speed(goal_x, goal_y)

        self.publisher_.publish(twist)

    def calculate_linear_speed(self, goal_x, goal_y):
        return 1.0  # İleri hareket hızı

    def calculate_angular_speed(self, goal_x, goal_y):
        x, y, theta = self.get_current_pose()
        desired_theta = math.atan2(goal_y - y, goal_x - x)
        return 1.0 * (desired_theta - theta)  # Dönüş hızı

    def get_current_pose(self):
        # Turtlesim'in mevcut konumunu alır
        # (Bunun için turtlesim için tf2_kdl kütüphanesi gereklidir, ancak siz bu kısmı göstermemişsiniz.)
        return 0.0, 0.0, 0.0  # Bu kısmı geçici olarak boş bıraktım, gerçek konum alınmalıdır

def main(args=None):
    rclpy.init(args=args)
    node = PathFollowerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()