////#include <iostream>
////#include <pcl/io/pcd_io.h>
////#include <pcl/point_types.h>
////#include <pcl/ModelCoefficients.h>
////#include <pcl/filters/project_inliers.h>
////#include <pcl/visualization/pcl_visualizer.h>
////int main(int argc, char** argv)
////{
////	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
////	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_projected(new pcl::PointCloud<pcl::PointXYZ>);
////	pcl::PCDReader reader;
////	reader.read<pcl::PointXYZ>("sphere.pcd", *cloud);
////	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
////	coefficients->values.push_back(0.0);
////	coefficients->values.push_back(0.0);
////	coefficients->values.push_back(1.0);
////	coefficients->values.push_back(0.0);
////
////	pcl::ProjectInliers<pcl::PointXYZ> proj;
////	proj.setInputCloud(cloud);
////	proj.setModelCoefficients(coefficients);
////	proj.setModelType(pcl::SACMODEL_PLANE);
////	proj.filter(*cloud_projected);
////
////	pcl::visualization::PCLVisualizer my_viewer1;
////	pcl::visualization::PCLVisualizer my_viewer2;
////	my_viewer1.addPointCloud(cloud);;
////	my_viewer2.addPointCloud(cloud_projected);
////
////	while (!my_viewer1.wasStopped())
////	{
////		my_viewer1.spinOnce(100);
////		my_viewer2.spinOnce(100);
////
////	}
////	system("pause");
////	return (0);
////}
////
