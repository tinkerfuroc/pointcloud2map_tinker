# Pointcloud2Map-Tinker

Pointcloud2Map for Tinker is based on [pcd2pgm](git@github.com:LihanChen2004/pcd2pgm.git).

This repository is used to convert the PointCloud2 data achieved when doing 3D SLAM to a grid map in pgm format.

The octomap packages in this repository are **not used** yet. We expect to use octomap to do the convertion in the future.

We first use `pointcloud2pcd` to convert PointCloud2 to `.pcd` file, then use `pcd2pgm` to convert the `.pcd` file to `.pgm` grid map

## Install depencies

```shell
rosdep install -r --from-paths src --ignore-src --rosdistro $ROS_DISTRO -y
```

## Build

```shell
colcon build --packages-select octomap_msgs octomap_ros
source ./install/setup.zsh 
colcon build
```

## Save PointCloud2 to `.pcd` file

```shell
ros2 run pointcloud2pcd pointcloud2pcd_node
```

`pointcloud2pcd_node` subscribes `/Laser_map` and converts the pointcloud2 data to a  `.pcd` file.

If the convertion runs successfully, the pointcloud2 data will be saved in `pointcloud2pcd.pcd`.

## Convert `.pcd` file to `.pgm` grid map

### Convert Map

```shell
ros2 launch pcd2pgm pcd2pgm.launch.py
```

### Save Map

```shell
ros2 run nav2_map_server map_saver_cli -f YOUR_MAP_NAME
```
