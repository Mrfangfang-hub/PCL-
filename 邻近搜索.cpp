#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
// �������ͷ�ļ�
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
	pcl::removeNaNFromPointCloud(*cloud, *cloud_out, mapping); // �Ƴ���Ч�㣬���� cloud Ϊ��ʼ���ƣ�cloud_out Ϊȥ����Ч���ĵ���

	pcl::KdTreeFLANN<pcl::PointXYZ> kdtree; //����KDtree
	kdtree.setInputCloud(cloud_out); // ����Ҫ�����ĵ��ƣ�����KDTree

	std::vector<int> indices; // �洢��ѯ���ڵ�����
	std::vector<float> distances; // �洢���ڵ��Ӧ�����ƽ��

	PointT point = cloud_out->points[0]; // ��ʼ��һ����ѯ��

	// ��ѯ��point�����k����
	//int k = 10;

	//int size = kdtree.nearestKSearch(point, k, indices, distances);

	//pcl::PointCloud<PointT>::Ptr cloud_nearest_point(new pcl::PointCloud<pcl::PointXYZ>);
	//for (size_t i = 0; i < indices.size(); ++i) {
	//	cloud_nearest_point->points.push_back(cloud_out->points[indices[i]]);
	//}
	//pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D viewer"));
	//viewer->setBackgroundColor(0, 0, 0);
	//// ԭʼ���ƣ���ɫ��
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud, 255, 255, 255);
	//viewer->addPointCloud(cloud, cloud_color_handler, "original cloud");

	////��Ӳ�ѯ��
	//pcl::PointCloud<pcl::PointXYZ>::Ptr searchPointCloud(new pcl::PointCloud<pcl::PointXYZ>);
	//searchPointCloud->push_back(point);
	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> searchPointColor(searchPointCloud, 255, 0, 0);
	//viewer->addPointCloud<pcl::PointXYZ>(searchPointCloud, searchPointColor, "search point");
	//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "search point");

	//pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_nearest_neighbors_color_handler(cloud_nearest_point, 51, 153, 255);
	//viewer->addPointCloud(cloud_nearest_point, cloud_nearest_neighbors_color_handler, "nearest neighbors");

	//// ���õ��С
	//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "nearest neighbors");

	//// �������ϵ
	////viewer->addCoordinateSystem(1.0);
	////viewer->initCameraParameters();

	//// ��ʼ���ӻ�
	//while (!viewer->wasStopped())
	//{
	//	viewer->spinOnce(100);
	//}
	//

	//std::cout << "search point : " << size << std::endl;

	// ��ѯpoint�뾶Ϊradius�������ڵĵ�
	double radius = 0.8;
	int size = kdtree.radiusSearch(point, radius, indices, distances);
	//��������
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3d viewer"));
	viewer->setBackgroundColor(0, 0, 0);
	//���ӻ�ԭʼ����
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> originalcloudcolor(cloud_out, 255, 255, 255);
	viewer->addPointCloud<pcl::PointXYZ>(cloud_out, originalcloudcolor, "originalcloud");
	//�����ڽ�����
	pcl::PointCloud<pcl::PointXYZ>::Ptr radiuscloud(new pcl::PointCloud<pcl::PointXYZ>);
	for (size_t i = 0; i < indices.size(); ++i) {
		radiuscloud->push_back(cloud_out->points[indices[i]]);
	}
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> nearestcolor(radiuscloud, 51, 153, 255);
	viewer->addPointCloud<pcl::PointXYZ>(radiuscloud, nearestcolor, "radiuscloud");
	//�����ڽ����ƴ�С
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "radiuscloud");
	//��Ӳ�ѯ��
	pcl::PointCloud<pcl::PointXYZ>::Ptr searchpoint(new pcl::PointCloud<pcl::PointXYZ>);
	searchpoint->push_back(point);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> searchpointcolor(searchpoint, 255, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(searchpoint, searchpointcolor, "searchpoint");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, "searchpoint");
	//���ӻ�
	//���ӻ�
	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
	}

	std::cout << "search point : " << size << std::endl;

	system("pause");
	return 0;
}