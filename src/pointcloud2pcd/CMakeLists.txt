cmake_minimum_required(VERSION 3.5)
project(pointcloud2pcd)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
set(PCL_INCLUDE_DIRS /usr/include/pcl-1.12 )  
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED)
# find_package(PCL REQUIRED COMPONENTS common io)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pointcloud2pcd_node 
  src/pointcloud2pcd.cpp
)
ament_target_dependencies(pointcloud2pcd_node 
  rclcpp 
  sensor_msgs
  pcl_conversions
)

install(TARGETS
  pointcloud2pcd_node
  DESTINATION lib/${PROJECT_NAME}
)

target_link_libraries(pointcloud2pcd_node ${PCL_LIBRARIES})

ament_package()