#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/common.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>

class PclSub : public rclcpp::Node
{

public:
    PclSub(std::string name)
        : Node(name)
    {
        sub_novel = this->create_subscription<sensor_msgs::msg::PointCloud2>("/Laser_map", 10, std::bind(&PclSub::topic_callback, this, std::placeholders::_1));
        this->declare_parameter("pcd_path", "pointcloud2pcd.pcd");
        RCLCPP_INFO(this->get_logger(), "pointcloud2pcd node has been started.");
        RCLCPP_INFO(this->get_logger(), "pcd_path: %s", this->get_parameter("pcd_path").as_string().c_str());
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_novel;

    void topic_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
    {
        pcl::PointCloud<pcl::PointXYZI>::Ptr cloud =
        std::make_shared<pcl::PointCloud<pcl::PointXYZI>>();
        pcl::fromROSMsg(*msg, *cloud);
        pcl::io::savePCDFileASCII (this->get_parameter("pcd_path").as_string().c_str(), *cloud);
        RCLCPP_INFO(this->get_logger(), "points_size(%d,%d)",msg->height,msg->width);
        RCLCPP_INFO(this->get_logger(), "pcd file saved");
    } 
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PclSub>("pclsub");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}