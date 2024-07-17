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

## 3.try.cpp

在处理一些大型的点云数据时，总会出现部分点稀疏部分点密集的情况，直接进行曲面重构时的参数会无法同时满足不同情况，此时可以进行下采样降低密集点的密度，也可以进行上采样增加稀疏点的密度，这里直接把稀疏点和密集点划分为两部分，分别进行重构。

原始数据集如下图，可以看到稀疏和密集区较为明显：

![image](https://github.com/user-attachments/assets/2085352c-5c8b-49c7-a372-0931580219f0)

![image](https://github.com/user-attachments/assets/e8bf7663-9dd5-4dbe-ad98-f68265c66ca6)

运行代码后可以看出点云数据被很好地分成了两部分：

![image](https://github.com/user-attachments/assets/e85345b8-d1dc-411d-b504-cd79035bb63c)

![image](https://github.com/user-attachments/assets/77353788-c67a-4ac6-a2f2-4a4048de6b09)

![image](https://github.com/user-attachments/assets/032ac63d-c52b-458d-9d87-80f33b9c5542)

![image](https://github.com/user-attachments/assets/49cdb9ae-7b34-4a43-b1b5-8e1d006332fe)

## 4.pcltest.cpp

点云数据中总会出现点分布不均匀的情况，可以通过下采样来使得点数据分别更平均，有利于曲面重构等后续处理，PCL自带的VoxelGrid(体素栅格)可以很好的完成这一任务，主要就是创建一个三维体素栅格(就是每个比较小的立方体组成的体素栅格)。在每个体素(三维立方体)里面，求取该立方体内的所有点云重心点来代表这个立方体的表示，以此达到下采样的目的。

可以看到原数据上层有很明显的稀疏部分：

![image](https://github.com/user-attachments/assets/347bb866-c253-4fc1-b513-3e14ec0c52e2)

运行代码后效果变好了很多：

![image](https://github.com/user-attachments/assets/b1ef69a6-1bf6-436b-a6be-77b59e3b5297)

![image](https://github.com/user-attachments/assets/f30f15ac-2b4c-4851-bb74-95e86d31915b)
