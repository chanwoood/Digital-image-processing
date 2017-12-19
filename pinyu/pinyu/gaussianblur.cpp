#include<opencv2/opencv.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;
void main()
{
	Mat input = imread("11.bmp", 0);  //此处省略检测读取是否正确
	imshow("原始图", input);

	//最佳显示尺寸，FFT要求尺寸为2的n次方
	int w = getOptimalDFTSize(input.cols);
	int h = getOptimalDFTSize(input.rows);

	//扩充图像边界
	Mat padded;
	copyMakeBorder(input, padded, 0, h - input.rows, 0, w - input.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded, CV_32FC1);

	//中心化，将四周亮的低频分量移到中心
	//也就是原图像乘以-1的x+y次方
	for (int i = 0; i < padded.rows; i++) {
		float *ptr = padded.ptr<float>(i);
		for (int j = 0; j < padded.cols; j++)
			ptr[j] *= pow(-1, i + j);
	}

	//创建通道
	Mat plane[] = { padded,Mat::zeros(padded.size(),CV_32F) };
	Mat complexImg;
	//合并通道，plane 为空白数组，2代表两个plane，一个存放实部，一个虚部
	merge(plane, 2, complexImg);
	//就地离散傅里叶变换
	dft(complexImg, complexImg);

	//高斯平滑滤波器
	Mat gaussianBlur(padded.size(), CV_32FC2);
	float D0 = 2 * 10 * 10;
	for (int i = 0; i<padded.rows; i++)
	{
		float*p = gaussianBlur.ptr<float>(i);
		for (int j = 0; j<padded.cols; j++)
		{
			//此处为公式
			float d = pow(i - padded.rows / 2, 2) + pow(j - padded.cols / 2, 2);
			p[2 * j] = expf(-d / D0);
			p[2 * j + 1] = expf(-d / D0);

		}
	}
	//矩阵元素对应相乘，不是矩阵相乘  
	multiply(complexImg, gaussianBlur, gaussianBlur);

	//分离通道   
	split(complexImg, plane);
	//第一个参数为实部，第二个为虚部，两者都为输入。
	//第三个参数为输出的幅度，即实部
	magnitude(plane[0], plane[1], plane[0]);

	//经过高斯平滑效果图（逆变换）
	idft(gaussianBlur, gaussianBlur);
	split(gaussianBlur, plane);
	magnitude(plane[0], plane[1], plane[0]);
	normalize(plane[0], plane[0], 1, 0, CV_MINMAX);
	imshow("高斯平滑滤波效果", plane[0]);

	waitKey();
}