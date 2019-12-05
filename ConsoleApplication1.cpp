#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include "opencv_test.h"
using namespace cv;
using namespace std;
int showimg()
{
	// 读入一张图片  
	Mat img = imread("D:\\OPENCV\\colortest\\blue.jpg");
	// 创建一个名为 "photo"窗口  
	cvNamedWindow("photo");
	// 在窗口中显示游戏原画  
	imshow("photo", img);
	// 等待10000 ms后窗口自动关闭  
	waitKey(10000);
	return 0;
}