The normal behavior of the package is to launch it with

'''
ros2 launch first_project first_project.launch.py
'''

However, the bag rosbag2_2026_04_08-16_38_55_fixed is uncentered.
For this specific one, the package must be launched with

'''
ros2 launch first_project first_project.launch.py x:=11.273 y:=-7.158 theta:=2.134
'''

Where the initial position and angle (x,y,theta) have been determined with tf2_echo on the bag.

The odometry computation requires three parameters :
- WHEEL_RADIUS :            has been estimated from the slide's measurements. 
                            (see First_project.pdf p.4)
- COMPUTED_GEAR_RATIO :     has been computed from the theoretical equation of the linear velocity, using the velocity from the robot output. 
                            (see odometer.cpp line 108 for the equation)
- LENGTH_BETWEEN_WHEELS :   has firstly been computed from the slide's measurements (see First_project.pdf p.4),
                            but has been adapted to fit the real angular velocity and theoretical equation.
                            (see odometer.cpp line 109 for the equation)

We computed the odometry with Euler estimation.

The reset service can be called at any time with 
'''
ros2 service call /reset first_project/srv/Reset {}
'''
This service resets the position to (0,0,0) as requested.
Therefore it is needed to launch the package again with the initial position for the uncentered bag.

The odometer node subscribes to the bags and therefore we have been able to adapt it to the simulation time.
However, the tf_error node does not and we had to decide on an arbitrary value for the wall_timer.
To keep it readable in a terminal, we ended up choosing 250ms.