import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class ElevatorServiceServer(Node):
    def __init__(self):
        super().__init__('elevator_service_server')
        self.srv = self.create_service(AddTwoInts, 'elevator', self.elevator_callback)

    def elevator_callback(self, request, response):
        if request.a <= 5:
            response.sum = request.a
            self.get_logger().info(f'Asansör {request.a} birim yükseltildi.')
        else:
            response.sum = 0
            self.get_logger().info(f'Asansör yüksekliği 5 birimden büyük olduğu için kaldırılamadı.')
        return response

def main(args=None):
    rclpy.init(args=args)
    elevator_service_server = ElevatorServiceServer()
    rclpy.spin(elevator_service_server)
    elevator_service_server.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()