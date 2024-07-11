# 

# 1.前言

记录一些学习PCL的过程，包括一些实例代码，一些好的内容也会进行分享。

# 2.文件介绍

## 1.投影.cpp

可以实现把三维点云投影到二维平面上，实现降维。通过把方程ax+by+cz+d=0中的a，b，c，d分别设置成a=b=d=0，c=1，从而得到z=0的平面，也就是每个点都失去z轴信息，从而完成投影。

![](C:\Users\Mrkun\AppData\Roaming\marktext\images\2024-07-11-14-41-57-image.png)

![](C:\Users\Mrkun\OneDrive\图片\本机照片\二维.png)

上图为投影效果。
