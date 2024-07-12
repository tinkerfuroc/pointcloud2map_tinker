# pcd_saver

Subscribes to a ROS2 PointCloud2 topic and stores received messages to Binary PCD files.

How to launch:
```
ros2 launch ros2_cloud_to_pcd cloud_to_pcd.xml \
    input/topic:=/lidar/pointcloud \
    output/path:=/tmp/ \
    output/prefix:=lidar
```

## Parameters
| Parameter       | Default       | Description                        |
|-----------------|---------------|------------------------------------|
| `input/topic`   | `/points_raw` | ROS2 Topic to subscribe            |
| `output/path`   | `/tmp/`       | Path where to store the PCD files. |
| `output/prefix` |               | Text to prepend to the output file |

