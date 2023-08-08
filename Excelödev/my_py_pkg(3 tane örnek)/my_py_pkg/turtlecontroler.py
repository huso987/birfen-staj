import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class TurtleController(Node):
    def _init_(self, robot_name):
        super()._init('turtle_controller' + robot_name)
        self.publisher_ = self.create_publisher(Twist, robot_name + '/cmd_vel', 10)

    def move_forward(self):
        twist = Twist()
        twist.linear.x = 2.0
        self.publisher_.publish(twist)

    def move_backward(self):
        twist = Twist()
        twist.linear.x = -2.0
        self.publisher_.publish(twist)

    def stop(self):
        twist = Twist()
        self.publisher_.publish(twist)

def main(args=None):
    rclpy.init(args=args)

    # İki farklı turtlesim robotu için iki Node oluşturun
    turtle_controller1 = TurtleController('turtle1')
    turtle_controller2 = TurtleController('turtle2')

    # Her bir turtle'ı belirli bir süre hareket ettirin
    rclpy.spin_once(turtle_controller1, timeout_sec=1.0)
    turtle_controller1.move_forward()
    rclpy.spin_once(turtle_controller2, timeout_sec=1.0)
    turtle_controller2.move_backward()
    rclpy.spin_once(turtle_controller1, timeout_sec=1.0)
    turtle_controller1.stop()
    rclpy.spin_once(turtle_controller2, timeout_sec=1.0)
    turtle_controller2.stop()

    # Düğümleri yok edin ve rclpy'yi kapatın
    turtle_controller1.destroy_node()
    turtle_controller2.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()