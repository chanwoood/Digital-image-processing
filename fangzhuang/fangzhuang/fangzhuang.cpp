#include <iostream>  
#include <opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

int main()
{

	//载入图片  
	Mat src = imread("0.jpg"), dst = imread("0.jpg");
	if (!src.data)
	{
		cout << "打开图像出错" << endl;
		return -1;
	}
	//获取图像信息  
	int height = src.rows;
	int width = src.cols* src.channels();   // 列项要乘通道数  

	//图像反转  
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j< width; j++)
		{
			dst.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);   // 每一个像素反转  
		}
	}

	//显示图片  
	namedWindow("原图像", WINDOW_NORMAL);
	namedWindow("反转后的图像", WINDOW_NORMAL);
	imshow("反转后的图像", dst);
	imshow("原图像", src);

	waitKey(0);
	return 0;
}