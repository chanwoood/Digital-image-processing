#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace ::std;
using namespace ::cv;

int main()
{
	//图像读取
	Mat src = imread("0.bmp", 0);

	//判断图像读取是否有问题
	if (!src.data)
	{
		cout << "图像读取出错!" << endl;
		return 0;
	}

	//原始图像显示
	namedWindow("原图像");
	imshow("原图像", src);
	//目标图像与原图像尺寸、类型一致
	Mat dst = Mat::zeros(src.size(), src.type());
	//自适应阈值处理
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 5);

	imshow("效果图", dst);
	waitKey(0);
}

