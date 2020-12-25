# 作业说明
Author ： 刘柯    student ID: 12021232

读入摄像头，回放视频。按一下空格键，则暂停回放，并将当前帧图像做一次Harris Corner检测，并将检测的结果叠加在原来图像上。

1. OpenCV里面与Harris角点检测相关的函数;
需要自己写代码实现Harris Corner检测算法，不能直接调用
2. 显示中间的处理结果及最终的检测结果，包括最大特征值图，最小 特征值图，R图(可以考虑彩色展示)，原图上叠加检测结果等，并将 这些中间结果都输出保存为图像文件。
【参考课件。及lkdemo.c】

**运行方式**：
我自己是在macOS上用makefile编译的，如果需要编译，请更改Makefile中INCLUDE_PATH，LIB_PATH，ADD_LIB的值，然后命令行输入make， 得到名为harris的可执行文件。


