# polimi-robotics-project



## Robotics Project

The goal of this group project is to emulate the movement of a robot using ros. Compute its odometry, and then show the difference between the actual movement and the computed odometry

## Usage

Here is a rapid exemple on how to launch the node to check if everything is working properly

build the project using colcon build:

```shell
$ colcon build
```
update the environment, so he knows the new nodes that has ben created:

```shell
$ source install/setup.bash
```

Launch tmux to have several terminals in the same window, it will be useful for the next steps:

```shell
$ tmux new -s session1
```

In the first terminal, launch the bag file:

```shell
$ ros2 bag play bags/rosbag2_2026_04_08-16_41_35_fixed/rosbag2_2026_04_08-16_41_35_fixed_0.db3 --clock
```
You'll see that you can control the speed of the bag file using the arrow keys, and the space bar to pause and resume the playback.

Now we will launch the node that computes the odometry in a second terminal:

First to create a new terminal in tmux, press `Ctrl+b` then `"`.

Then launch the node, it will also launch rviz2 with a pre-configured view:

```shell
$ ros2 launch first_project first_project.launch.py
```
here's what you should see in the terminal:

```shell
[INFO] [XXXXX.XXXXX] [odometer]:
Receiving:
 Linear velocity: '0.594000'
 Angular velocity: '-0.020000'
 Battery voltage: '52.500000'
[INFO] [XXXXX.XXXXX] [odometer]:
Publishing:
 Odometer message:
 position x:'1.000000'
 position y:'1.000000'
 position z:'1.000000'
```
You can also check the topics are the nodes that are being published using:

```shell
$ ros2 topic list
$ ros2 node list
```

To call the tf_error node, you can use the following command in a third terminal:

```shell
$ ros2 run first_project tf_error
```

The input should look like this:

```shell
tf_error: 0.012657581828534603
time_from_start: 450
travelled_distance: 148.35484313964844
```

To call the reset service, you can use the following command in a third terminal:

```shell
$  ros2 service call /reset first_project/srv/Reset {}
```


## Roadmap

- [x] Create Odometer node 
- [x] Odometer node subscribe to the bunker_status message 
- [x] Odometer node publish the odometry message to /project_odom topic
- [x] Compute the real odometry and publish it to /project_odom topic
- [x] Use tf2 to publish the transform between the odometry frame and the base frame
- [x] Create a launch file to launch the node and rviz2 with a pre-configured view
- [x] Change the launch file to be able to launch rviz2 without absolute path to the config file
- [x] Add a service to reset the odometry to zero
- [x] Create the tf_error node and publish the error between the odometry and the real position to a topic
