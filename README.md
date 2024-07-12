# 

# 1.前言

记录一些学习PCL的过程，包括一些实例代码，一些好的内容也会进行分享。

# 2.文件介绍

## 1.投影.cpp

可以实现把三维点云投影到二维平面上，实现降维。通过把方程ax+by+cz+d=0中的a，b，c，d分别设置成a=b=d=0，c=1，从而得到z=0的平面，也就是每个点都失去z轴信息，从而完成投影。

![image](https://github.com/Mrfangfang-hub/PCL-/assets/56708235/19e42222-aa84-4a70-b2b5-f8af8d5db35e)

![image](https://github.com/Mrfangfang-hub/PCL-/assets/56708235/5f5718ee-75cb-4dc3-8aaf-b087e55e624a)

上图为投影效果。

## 2.邻近搜索.cpp
使用KDtree对点云数据进行K近邻搜索以及半径内近邻搜索，并对搜索后的点进行可视化，包括原始点云。K近邻搜索为注释掉的一段，需要使用时解除注释即可。对于KDtree的建立以及算法介绍强烈推荐blog.csdn.net/silangquan/article/details/41483689，这位博主有原理的详细解释，也有实际的例子和代码，适合新手学习。

![image](https://github.com/user-attachments/assets/63a19e78-090b-4e43-8f59-741b6c9aea78)

上图为设置搜索半径后的邻近搜索。
