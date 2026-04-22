# polimi-robotics-project



## Robotics Project

The goal of this group project is to emulate the movement of a robot using ros. Compute its odometry, and then show the difference between the actual movement and the computed odometry

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

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
$ ros2 bag play bags/rosbag2_2026_04_08-16_41_35_fixed/rosbag2_2026_04_08-16_41_35_fixed_0.db3
```
You'll see that you can control the speed of the bag file using the arrow keys, and the space bar to pause and resume the playback.

Now we will launch the node that computes the odometry in a second terminal:

First to create a new terminal in tmux, press `Ctrl+b` then `"`.

Then launch the node:

```shell
$ ros2 run first_project odometry_node
```
here's what you should see in the terminal:

```shell
[INFO] [XXXXXX.XXXXXX] [odometer]: vehicle state:'0'
 control_mode:'0'
 battery_voltage:'52.799999'
[INFO] [XXXXXX.XXXXXX] [odometer]: vehicle state:'0'
 control_mode:'0'
 battery_voltage:'52.799999'
```
You can also check the topics are the nodes that are being published using:

```shell
$ ros2 topic list
$ ros2 node list
```

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.


## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
