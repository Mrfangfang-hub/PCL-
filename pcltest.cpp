#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <thread>
#include <chrono>
#include <pcl/filters/voxel_grid.h>
#include <pcl/surface/mls.h>

int main(int argc, char** argv)
{
    // 创建点云对象
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 从PCD文件中读取点云数据
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("1.pcd", *cloud) == -1) // 请将"input.pcd"替换为你的点云文件路径
    {
        PCL_ERROR("Couldn't read file input.pcd\n");
        return (-1);
    }
    pcl::VoxelGrid<pcl::PointXYZ> vg;
    vg.setInputCloud(cloud);
    vg.setLeafSize(20.0f, 20.0f, 20.0f);  // 设置体素大小
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_smoothed(new pcl::PointCloud<pcl::PointXYZ>);
    vg.filter(*cloud_smoothed); 

    // 创建可视化对象
    pcl::visualization::PCLVisualizer::Ptr viewer0(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer0->setBackgroundColor(0, 0, 0);
    viewer0->addPointCloud<pcl::PointXYZ>(cloud, "original cloud");
    viewer0->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);
    viewer->addPointCloud<pcl::PointXYZ>(cloud_smoothed, "sample cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
    //viewer->addCoordinateSystem(1.0);
    //viewer->initCameraParameters();

    // 启动可视化
    while (!viewer->wasStopped())
    {
        viewer0->spinOnce(100);
        viewer->spinOnce(100);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
