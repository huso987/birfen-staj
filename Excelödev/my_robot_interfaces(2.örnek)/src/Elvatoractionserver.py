import rclpy
from rclpy.action import ActionServer
from my_robot_interfaces.action import Elevator

class ElevatorActionServer(rclpy.node.Node):
    def __init__(self):
        super().__init__('elevator_action_server')
        self._action_server = ActionServer(self, Elevator, 'elevator', self.elevator_callback)
        self.get_logger().info('Elevator action server is up!')

    def elevator_callback(self, goal_handle):
        goal = goal_handle.request
        target_floor = goal.target_floor
        if target_floor == 5:
            self.get_logger().info('Asansör kaldırıldı.')
            result = Elevator.Result()
            result.success = True
            result.message = 'Asansör kaldırıldı.'
            goal_handle.succeed(result)
        elif target_floor > 5:
            self.get_logger().info('Asansör kaldırılamadı. Girilen rakam 5\'ten büyük.')
            result = Elevator.Result()
            result.success = False
            result.message = 'Asansör kaldırılamadı. Girilen rakam 5\'ten büyük.'
            goal_handle.abort(result)
        else:
            self.get_logger().info('Geçersiz istek. 5 birim kaldır dediğinizde kaldırılır.')
            result = Elevator.Result()
            result.success = False
            result.message = 'Geçersiz istek. 5 birim kaldır dediğinizde kaldırılır.'
            goal_handle.abort(result)

def main(args=None):
    rclpy.init(args=args)
    elevator_action_server = ElevatorActionServer()
    rclpy.spin(elevator_action_server)
    rclpy.shutdown()

if __name__ == '_main_':
    main()