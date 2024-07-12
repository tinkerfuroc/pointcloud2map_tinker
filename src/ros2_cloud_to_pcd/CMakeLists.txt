cmake_minimum_required(VERSION 3.14)
project(ros2_cloud_to_pcd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

find_package (PCL REQUIRED)
find_package (Boost REQUIRED)

ament_auto_add_library(cloud_to_pcd SHARED
        src/cloud_to_pcd.cpp
        )

target_link_libraries(cloud_to_pcd ${PCL_LIBRARIES}
        )

target_include_directories(cloud_to_pcd
        SYSTEM PUBLIC
        ${PCL_INCLUDE_DIRS}
        )

rclcpp_components_register_node(cloud_to_pcd
        PLUGIN "CloudToPcd"
        EXECUTABLE cloud_to_pcd_node
        )

ament_auto_package(INSTALL_TO_SHARE
        launch
        )

