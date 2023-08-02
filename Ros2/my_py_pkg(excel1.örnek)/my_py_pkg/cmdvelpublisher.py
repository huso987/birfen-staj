import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class CmdVelPublisher(Node):
    def __init__(self):
        super().__init__('cmd_vel_publisher')
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
        self.timer = self.create_timer(0.1, self.publish_cmd_vel)
        self.cmd_vel_msg = Twist()

    def publish_cmd_vel(self):
       
        self.cmd_vel_msg.linear.x = 3.2
        self.cmd_vel_msg.angular.z = 3.0
        self.publisher_.publish(self.cmd_vel_msg)

def main(args=None):
    rclpy.init(args=args)
    cmd_vel_publisher = CmdVelPublisher()
    rclpy.spin(cmd_vel_publisher)
    cmd_vel_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()