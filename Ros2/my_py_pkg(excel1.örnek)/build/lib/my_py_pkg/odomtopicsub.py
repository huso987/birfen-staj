import rclpy
from rclpy.node import Node
from nav_msgs.msg import Odometry

class OdomSubscriberNode(Node):
    def __init__(self):
        super().__init__('odom_subscriber')
        self.subscription = self.create_subscription(
            Odometry,
            'odom',
            self.odom_callback,
            10
        )

    def odom_callback(self, msg):
        # Odom verisini ekrana yazar
        self.get_logger().info('Odometry Verileri: x=%f, y=%f, z=%f', msg.pose.pose.position.x, msg.pose.pose.position.y, msg.pose.pose.position.z)

def main(args=None):
    rclpy.init(args=args)
    odom_subscriber = OdomSubscriberNode()
    rclpy.spin(odom_subscriber)
    odom_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()