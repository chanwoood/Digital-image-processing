#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv;
using namespace std;

void main()
{   // 加载图片
	Mat srcImage = imread("0.jpg", 1);
		if (!srcImage.data)
			cout << "加载图像出错！" << endl;
	// 构造和原始图像大小类型一致的目标图像
	Mat resultImage = Mat::zeros(srcImage.size(), srcImage.type());

	// 对数变换
	double gray = 0;
	for (int i = 0; i < srcImage.rows; i++)
	{
		for (int j = 0; j < srcImage.cols*srcImage.channels(); j++)
		{
			gray = (double)srcImage.at<uchar>(i, j);
			// 对数变换
			gray = 30*log((double)(1 + gray));
			// saturate_cast 作用：大于255,则变为255；小于0，则变为0
			resultImage.at<uchar>(i, j) = saturate_cast<uchar>(gray);
		}
	}
	//归一化处理  
	normalize(resultImage, resultImage, 0, 255, NORM_MINMAX);
	//转换成8bit图像显示  
	convertScaleAbs(resultImage, resultImage);
	namedWindow("原始图");
	namedWindow("对数变换后的图");

	imshow("对数变换后的图",resultImage);
	imshow("原始图", srcImage);
	waitKey(0);
}