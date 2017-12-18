#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	//加载原图
	Mat srcImage = imread("7.jpg"); 
	Mat midImage, dstImage;

	//显示原始图
	imshow("原始图", srcImage);

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);//转为灰度图
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);  //高斯滤波，图像平滑

	//霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1, 0.001, 90, 30, 0, 80);

	//图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

	//显示效果图  
	imshow("效果图", srcImage);

	waitKey(0);

	return 0;
}