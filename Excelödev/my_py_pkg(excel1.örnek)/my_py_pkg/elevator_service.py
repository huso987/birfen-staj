import rclpy
from rclpy.node import Node
from example_interfaces.srv import SetBool

class ElevatorServiceServer(Node):
    def __init__(self):
        super().__init__('elevator_service_server')
        self.srv = self.create_service(SetBool, 'elevator', self.elevator_callback)

    def elevator_callback(self, request, response):
        if request.data:
            if request.data == 5:
                response.success = True
                response.message = 'Asansör kaldırıldı.'
                self.get_logger().info('Asansör kaldırıldı.')
            else:
                response.success = False
                response.message = 'Asansör kaldırılamadı. Girilen rakam 5\'ten büyük.'
                self.get_logger().info('Asansör kaldırılamadı. Girilen rakam 5\'ten büyük.')
        else:
            response.success = False
            response.message = 'Geçersiz istek. 5 birim kaldır dediğinizde kaldırılır.'
            self.get_logger().info('Geçersiz istek. 5 birim kaldır dediğinizde kaldırılır.')
        return response

def main(args=None):
    rclpy.init(args=args)
    elevator_service_server = ElevatorServiceServer()
    rclpy.spin(elevator_service_server)
    elevator_service_server.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()