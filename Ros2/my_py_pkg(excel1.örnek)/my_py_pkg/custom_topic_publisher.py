import rclpy
from rclpy.node import Node
from tf2_ros import TransformListener, Buffer, TransformStamped
from geometry_msgs.msg import Point

class CustomTopicPublisher(Node):
    def __init__(self):
        super().__init__('custom_topic_publisher')
        self.publisher_ = self.create_publisher(Point, 'custom_topic', 10)
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.timer = self.create_timer(1.0, self.publish_custom_topic)

    def publish_custom_topic(self):
        try:
            # robotun konumunu tf topicinden alın
            transform = self.tf_buffer.lookup_transform('map', 'base_link', rclpy.time.Time())
            robot_position = transform.transform.translation
            self.get_logger().info(f'Robotun Konumu: x={robot_position.x}, y={robot_position.y}, z={robot_position.z}')

            # Engel konumları
            box_position = Point()
            box_position.x = 5.0
            box_position.y = 5.0
            box_position.z = 0.0

            table_position = Point()
            table_position.x = 5.0
            table_position.y = 8.0
            table_position.z = 0.0

            # Robota en yakın engel
            closest_obstacle = 'kutu' if self.calculate_distance(robot_position, box_position) < self.calculate_distance(robot_position, table_position) else 'masa'
            self.get_logger().info(f'Robota en yakin engel: {closest_obstacle}')

            # Engel konumları
            self.publisher_.publish(box_position) # kutu konumu

        except Exception as e:
            self.get_logger().error(f'Hata: {str(e)}')

    def calculate_distance(self, point1, point2):
        return ( (point1.x - point2.x)*2 + (point1.y - point2.y)*2 + (point1.z - point2.z)*2 )*0.5

def main(args=None):
    rclpy.init(args=args)
    custom_topic_publisher = CustomTopicPublisher()
    rclpy.spin(custom_topic_publisher)
    custom_topic_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()