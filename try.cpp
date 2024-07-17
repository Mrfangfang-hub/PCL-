//#include <pcl/point_types.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/kdtree/kdtree_flann.h>
//#include <iostream>
//#include <vector>
//#include <unordered_set>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <boost/thread/thread.hpp>
//#include <pcl/filters/voxel_grid.h>
//
//// DBSCAN参数
//const float EPSILON = 23; // 邻域半径
//const int MIN_POINTS = 10; // 构成簇的最小点数
//
//// DBSCAN算法
//void dbscan(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, std::vector<int>& labels) {
//    int cluster_id = 0;
//    labels.resize(cloud->points.size(), -1); // -1表示未分类
//
//    pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
//    kdtree.setInputCloud(cloud);
//
//    for (size_t i = 0; i < cloud->points.size(); ++i) {
//        if (labels[i] != -1) continue; // 已经处理过
//
//        std::vector<int> neighbors;
//        std::vector<float> distances;
//        kdtree.radiusSearch(cloud->points[i], EPSILON, neighbors, distances);
//
//        if (neighbors.size() < MIN_POINTS) {
//            labels[i] = -2; // 噪声点
//            continue;
//        }
//
//        // 创建新簇
//        cluster_id++;
//        std::vector<int> cluster;
//        cluster.push_back(i);
//        labels[i] = cluster_id;
//
//        // 遍历邻居
//        size_t index = 0;
//        while (index < cluster.size()) {
//            int point_idx = cluster[index];
//            std::vector<int> new_neighbors;
//            std::vector<float> new_distances;
//            kdtree.radiusSearch(cloud->points[point_idx], EPSILON, new_neighbors, new_distances);
//
//            if (new_neighbors.size() >= MIN_POINTS) {
//                for (size_t j = 0; j < new_neighbors.size(); ++j) {
//                    if (labels[new_neighbors[j]] == -1 || labels[new_neighbors[j]] == -2) {
//                        if (labels[new_neighbors[j]] == -1) {
//                            cluster.push_back(new_neighbors[j]);
//                        }
//                        labels[new_neighbors[j]] = cluster_id;
//                    }
//                }
//            }
//            index++;
//        }
//    }
//}
//
//int main(int argc, char** argv) {
//    // 加载点云数据
//    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//    if (pcl::io::loadPCDFile<pcl::PointXYZ>("1.pcd", *cloud) == -1) {
//        PCL_ERROR("Couldn't read file input.pcd \n");
//        return (-1);
//    }
//    pcl::VoxelGrid<pcl::PointXYZ> vg;
//    vg.setInputCloud(cloud);
//    vg.setLeafSize(10.0f, 10.0f, 10.0f);  // 设置体素大小
//    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_smoothed(new pcl::PointCloud<pcl::PointXYZ>);
//    vg.filter(*cloud_smoothed); 
//
//    // 执行DBSCAN聚类
//    std::vector<int> labels;
//    dbscan(cloud_smoothed, labels);
//
//    // 提取密集点和稀疏点
//    pcl::PointCloud<pcl::PointXYZ>::Ptr dense_points(new pcl::PointCloud<pcl::PointXYZ>);
//    pcl::PointCloud<pcl::PointXYZ>::Ptr sparse_points(new pcl::PointCloud<pcl::PointXYZ>);
//    for (size_t i = 0; i < labels.size(); ++i) {
//        if (labels[i] > 0) { // 密集点
//            dense_points->points.push_back(cloud_smoothed->points[i]);
//        }
//        else { // 稀疏点
//            sparse_points->points.push_back(cloud_smoothed->points[i]);
//        }
//    }
//    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer1(new pcl::visualization::PCLVisualizer("original_cloud"));
//    viewer1->setBackgroundColor(0, 0, 0); //设置背景
//    viewer1->addPointCloud(dense_points);
//    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer2(new pcl::visualization::PCLVisualizer("rebuild_cloud"));
//    viewer2->setBackgroundColor(0, 0, 0); //设置背景
//    viewer2->addPointCloud(sparse_points); //设置显示的网格
//    //viewer->addCoordinateSystem(1.0); //设置坐标系
//    //viewer->initCameraParameters();
//    dense_points->width = dense_points->points.size();
//    dense_points->height = 1;
//    sparse_points->width = sparse_points->points.size();
//    sparse_points->height = 1;
//    pcl::io::savePCDFileASCII("dense_points.pcd", *dense_points);
//    pcl::io::savePCDFileASCII("sparse_points.pcd", *sparse_points);
//    std::cout << "Saved " << dense_points->points.size() << " dense points to dense_points.pcd" << std::endl;
//    std::cout << "Saved " << sparse_points->points.size() << " sparse points to sparse_points.pcd" << std::endl;
//    while (!viewer1->wasStopped()) {
//    	viewer1->spinOnce(100);
//    	viewer2->spinOnce(100);
//    	boost::this_thread::sleep(boost::posix_time::microseconds(100000));
//    }
//    // 保存密集点和稀疏点
//
//
//    return 0;
//}
