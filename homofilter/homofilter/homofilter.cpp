#include<opencv2/opencv.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;

void homofilter(Mat src, Mat &dst)
{

	src.convertTo(src, CV_64FC1);  //64位，对应double
	dst.convertTo(dst, CV_64FC1);
	//对数变换
	for (int i = 0; i < src.rows; i++)
	{
		double* srcdata = src.ptr<double>(i);
		for (int j = 0; j < src.cols; j++)
		{
			srcdata[j] = log(srcdata[j] + 0.0001);
		}
	}

	//离散余弦变换
	Mat mat_dct = Mat::zeros(src.rows, src.cols, CV_64FC1);
	dct(src, mat_dct);

	//滤波
	Mat H;
	double gammaH = 1.5;
	double gammaL = 0.5;
	double C = 1;
	double d0 = (src.rows / 2)*(src.rows / 2) + (src.cols / 2)*(src.cols / 2);
	double d2 = 0;
	H = Mat::zeros(src.rows, src.cols, CV_64FC1);

	double totalWeight = 0.0;
	for (int i = 0; i < src.rows; i++)
	{
		double * dataH = H.ptr<double>(i);
		for (int j = 0; j < src.cols; j++)
		{
			d2 = pow((i), 2.0) + pow((j), 2.0);
			dataH[j] = (gammaH - gammaL)*(1 - exp(-C*d2 / d0)) + gammaL;
			totalWeight += dataH[j];
		}
	}
	H.ptr<double>(0)[0] = 1.1;
	mat_dct = mat_dct.mul(H);

	//逆变换
	idct(mat_dct, dst);

	//取指数
	for (int i = 0; i < src.rows; i++)
	{
		double* srcdata = dst.ptr<double>(i);
		double* dstdata = dst.ptr<double>(i);
		for (int j = 0; j < src.cols; j++)
		{
			dstdata[j] = exp(srcdata[j]);
		}
	}

	//转换为8位灰度图像
	dst.convertTo(dst, CV_8UC1);

}

void main() {
	Mat src = imread("8.jpg", 0);
	imshow("原图像", src);
	Mat dst = Mat::zeros(src.size(), src.type());
	homofilter(src, dst);

	imshow("同态滤波", dst);
	waitKey(0);
}