#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
// 包含相关头文件
#include <pcl/kdtree/kdtree_flann.h>
# include <pcl/filters/filter.h>
#include<pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ PointT;

int main()
{
	pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
	pcl::io::loadPCDFile("sphere.pcd", *cloud);

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out(new pcl::PointCloud<pcl::PointXYZ>);
	std::vector<int> mapping;
	pcl::removeNaNFromPointCloud(*cloud, *cloud_out, mapping); // 移除无效点，其中 cloud 为初始点云，cloud_out 为去除无效点后的点云

	pcl::KdTreeFLANN<pcl::PointXYZ> kdtree; //创建KDtree
	kdtree.setInputCloud(cloud_out); // 设置要搜索的点云，建立KDTree

	std::vector<int> indices; // 存储查询近邻点索引
	std::vector<float> distances; // 存储近邻点对应距离的平方

	PointT point = cloud_out->points[0]; // 初始化一个查询点

	// 查询距point最近的k个点
	//int k = 10;

	//int size = kdtree.nearestKSearch(point, k, indices, distances);

	//pcl::PointCloud<PointT>::Ptr cloud_nearest_point(new pcl::PointCloud<pcl::PointXYZ>);
	//for (size_t i = 0; i < indices.size(); ++i) {
	//	cloud_nearest_point->points.push_back(cloud_out->points[indices[i]]);
	//}
	//pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D viewer"));
	//viewer->setBackgroundColor(0, 0, 0);
	//// 原始点云（白色）
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud, 255, 255, 255);
	//viewer->addPointCloud(cloud, cloud_color_handler, "original cloud");

	////添加查询点
	//pcl::PointCloud<pcl::PointXYZ>::Ptr searchPointCloud(new pcl::PointCloud<pcl::PointXYZ>);
	//searchPointCloud->push_back(point);
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> searchPointColor(searchPointCloud, 255, 0, 0);
	//viewer->addPointCloud<pcl::PointXYZ>(searchPointCloud, searchPointColor, "search point");
	//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "search point");

	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_nearest_neighbors_color_handler(cloud_nearest_point, 51, 153, 255);
	//viewer->addPointCloud(cloud_nearest_point, cloud_nearest_neighbors_color_handler, "nearest neighbors");

	//// 设置点大小
	//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "nearest neighbors");

	//// 添加坐标系
	////viewer->addCoordinateSystem(1.0);
	////viewer->initCameraParameters();

	//// 开始可视化
	//while (!viewer->wasStopped())
	//{
	//	viewer->spinOnce(100);
	//}
	//

	//std::cout << "search point : " << size << std::endl;

	// 查询point半径为radius邻域球内的点
	double radius = 0.8;
	int size = kdtree.radiusSearch(point, radius, indices, distances);
	//创建窗口
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3d viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	//可视化原始点云
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> originalcloudcolor(cloud_out, 255, 255, 255);
	viewer->addPointCloud<pcl::PointXYZ>(cloud_out, originalcloudcolor, "originalcloud");
	//创建邻近点云
	pcl::PointCloud<pcl::PointXYZ>::Ptr radiuscloud(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < indices.size(); ++i) {
		radiuscloud->push_back(cloud_out->points[indices[i]]);
	}
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> nearestcolor(radiuscloud, 51, 153, 255);
	viewer->addPointCloud<pcl::PointXYZ>(radiuscloud, nearestcolor, "radiuscloud");
	//调整邻近点云大小
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "radiuscloud");
	//添加查询点
	pcl::PointCloud<pcl::PointXYZ>::Ptr searchpoint(new pcl::PointCloud<pcl::PointXYZ>);
	searchpoint->push_back(point);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> searchpointcolor(searchpoint, 255, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(searchpoint, searchpointcolor, "searchpoint");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "searchpoint");
	//可视化
	//可视化
	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
	}

	std::cout << "search point : " << size << std::endl;

	system("pause");
	return 0;
}