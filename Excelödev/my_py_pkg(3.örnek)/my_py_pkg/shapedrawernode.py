from turtle import turtlesize
import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist

import math

class ShapeDrawerNode(Node):
    def __init__(self):
        super().__init__('shape_drawer_node')
        self.publisher_ = self.create_publisher(Twist, 'turtle1/cmd_vel', 10)
        self.subscription = self.create_subscription(Pose, 'turtle1/pose', self.pose_callback, 10)
        self.subscription  # To prevent unused variable warning
        self.background_color_changed = False

    def pose_callback(self, msg):
        if not self.background_color_changed:
            self.get_logger().info('Arka plan rengi değişti!')
            self.set_background_color(0, 255, 0)  # Arka plan rengini yeşil olarak değiştir
            self.background_color_changed = True

    def draw_shape(self, shape_name):
        rate = self.create_rate(1)
        twist = Twist()
        twist.linear.x = 2.0  # İleri hareket hızı
        twist.angular.z = 1.0  # Dönüş hızı

        if shape_name == 'kare':
            for _ in range(4):
                self.publisher_.publish(twist)
                rate.sleep()
                twist.angular.z = -twist.angular.z  # Yönü tersine çevirerek kare çizdir

        elif shape_name == 'yuvarlak':
            duration = 10  # 10 saniye boyunca yuvarlak çizdir
            for _ in range(duration):
                self.publisher_.publish(twist)
                rate.sleep()

        elif shape_name == 'üçgen':
            for _ in range(3):
                self.publisher_.publish(twist)
                rate.sleep()
                twist.angular.z = -2.0  # 3 adımda 360 derece dönerek üçgen çizdir
                rate.sleep()

        self.get_logger().info(f'{shape_name.capitalize()} çizimi tamamlandı!')

    def set_background_color(self, r, g, b):
        # Arka plan rengini değiştiren turtlesim service çağrısı
        self.call_turtlesim_service('clear', r, g, b)

    def call_turtlesim_service(self, service_name, r, g, b):
        service_client = self.create_client('clear', 'turtlesim.srv/Color')
        while not service_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info(f'{service_name.capitalize()} service\'ı bekleniyor...')
        request = turtlesize.srv.Color.Request()
        request.r = r
        request.g = g
        request.b = b
        future = service_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)

def main(args=None):
    rclpy.init(args=args)
    shape_name = input('Turtlesim için çizdirmek istediğiniz şekli girin (kare, yuvarlak, üçgen): ')
    node = ShapeDrawerNode()
    node.draw_shape(shape_name)
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()