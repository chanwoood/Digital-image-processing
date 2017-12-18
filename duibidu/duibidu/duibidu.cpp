#include <iostream>
#include <stdio.h>

//图像操作
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace ::std;
using namespace ::cv;

int main()
{
	//图像读取
	Mat image = imread("0.jpg");

	//判断图像读取是否有问题
	if (!image.data)
	{
		cout << "图像读取出错!" << endl;
		return 0;
	}

	//原始图像显示
	namedWindow("原图像", WINDOW_NORMAL);
	imshow("原图像", image);


	//处理图像
	int data_max = 0, data_min = 255;
	int nl = image.rows;
	int nc = image.cols * image.channels();

	int i, j;
	uchar *data;
	//求出图像的灰度最大、最小值
	for (j = 0; j < nl; j++)
	{
		data = image.ptr<uchar>(j);
		for (i = 0; i < nc; i++)
		{
			if (data[i] > data_max)        data_max = data[i];
			if (data[i] < data_min)        data_min = data[i];
		}
	}
	//对比度拉伸
	int temp = data_max - data_min;
	for (j = 0; j < nl; j++)
	{
		data = image.ptr<uchar>(j);
		for (i = 0; i < nc; i++)
		{
			data[i] = (data[i] - data_min) * 255 / temp;
		}
	}

	//显示图像
	namedWindow("对比度拉伸后图像", WINDOW_NORMAL);
	imshow("对比度拉伸后图像", image);

	waitKey(0);
	return 0;
}
