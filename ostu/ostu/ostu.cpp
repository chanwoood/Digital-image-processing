#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

Mat src, dst;

void main()
{
	src = imread("0.jpg", 0);
	if (!src.data) {
		printf("读取图片错误! \n");
	}
	imshow("原始图", src);
	//使用otsu方法
	threshold(src, dst, 100, 255, THRESH_OTSU);
	imshow("效果图", dst);
	waitKey(0);
}
