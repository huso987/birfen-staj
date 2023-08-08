1) for moveandstop.py(Turtlebotun 1 metre gitmesini ve sonra durmasını sağlayın.)

open the terminal 
-------------------
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

new terminal
----------------
ros2 run my_py_pkg moveandstop



2) for threepointsloop.py(3 nokta arası sonsuz döngü ile gezin. )

open the terminal 
-------------------
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

new terminal
----------------
ros2 run my_py_pkg threeloop


3) for engeldenkac.py (Robot düz gitsin. Karşısında engel gördüğünde engel olmayan yöne doğru 90 derece dönsün.
 Tekrar düz gitmeye devam etsin. )

open the terminal 
-------------------
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

new terminal
----------------
ros2 run my_py_pkg engel