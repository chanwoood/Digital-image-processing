#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{

	Mat src, src_gray, dst, abs_dst;

	//载入原始图  
	src = imread("0021m.bmp");  

	//显示原始图 
	imshow("原始图", src);

	//使用高斯滤波消除噪声，模板大小为9*9
	GaussianBlur(src, src, Size(9, 9), 0, 0, BORDER_DEFAULT);

	//转换为灰度图
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	//使用Laplace函数，第四个参数孔径尺寸为5，即模板大小为9*9
	Laplacian(src_gray, dst, CV_16S, 5,1, 0, BORDER_DEFAULT);

	//计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);

	//显示效果图
	imshow("效果图", abs_dst);

	waitKey(0);

	return 0;
}