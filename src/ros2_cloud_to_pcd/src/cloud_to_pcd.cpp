/*
 *  Copyright (c) 2022, Abraham Cano.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  v1.0 amc-nu 2022-12
 */

#include "cloud_to_pcd/cloud_to_pcd.hpp"

CloudToPcd::CloudToPcd(const rclcpp::NodeOptions &options) : Node("cloud_to_pcd", options)
{
  // IO
  pointcloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "input/topic", rclcpp::SensorDataQoS().keep_last(1),
      std::bind(&CloudToPcd::CloudCallback, this, std::placeholders::_1));
  output_path_ = this->declare_parameter<std::string>("output/path", "/tmp/");
  file_prefix_ = this->declare_parameter<std::string>("output/prefix", "");
  if (output_path_.empty())
  {
    RCLCPP_ERROR_STREAM(get_logger(), "Invalid Path provided:" << output_path_ << ". Terminating...");
    rclcpp::shutdown(nullptr, "Invalid Output Path");
  }
  if (!std::filesystem::exists(output_path_))
  {
    RCLCPP_INFO_STREAM(get_logger(), "The Provided path [" << output_path_ << "]doesn't exist. Trying to create.");
    if (std::filesystem::create_directories(output_path_))
    {
      RCLCPP_INFO_STREAM(get_logger(), "The Provided Path was created successfully.");
    }
    else
    {
      RCLCPP_ERROR_STREAM(get_logger(), "Could not create the output directory: " << output_path_ << ". Terminating");
      rclcpp::shutdown(nullptr, "Missing Permissions on the output path");
    }
  }
  RCLCPP_INFO_STREAM(get_logger(), "Saving BINARY PCDs to:" << output_path_ << ",  with prefix:" << file_prefix_);
}

void CloudToPcd::CloudCallback(const sensor_msgs::msg::PointCloud2::ConstSharedPtr input)
{
  sensor_msgs::msg::PointCloud2 cloud_result;
  std::string fname;
  fname = output_path_ + "/" + file_prefix_ + "_" +
          boost::lexical_cast<std::string>(input->header.stamp.sec) + "." +
          boost::lexical_cast<std::string>(input->header.stamp.nanosec) + ".pcd";

  pcl::PCLPointCloud2 pcl_cloud;
  pcl_conversions::moveToPCL(*(const_cast<sensor_msgs::msg::PointCloud2 *>(input.get())), pcl_cloud);
  pcl::io::savePCDFile(
      fname, pcl_cloud, Eigen::Vector4f::Zero(),
      Eigen::Quaternionf::Identity(), true);
  RCLCPP_INFO_STREAM(get_logger(), "Cloud saved to: " << fname);
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(CloudToPcd)
