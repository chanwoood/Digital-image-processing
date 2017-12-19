#include<opencv2\opencv.hpp>  
#include<iostream>  
using namespace std;
using namespace cv;

int main() {
	Mat a = (Mat_<int>(5, 5) << 1, 2, 2, 0, 2, 1, 1, 0, 1, 1, 0, 0, 1, 2, 2, 1, 2, 1, 1, 0, 1, 0, 1, 0, 0);
	cout << "原矩阵：" << endl << "" << a << endl << endl;
	//点对矩阵
	Mat b = Mat::zeros(3, 3, CV_8UC1);
	//最后一行没有下方元素，所以只到第四行
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (a.at<int>(i, j) == 0 && a.at<int>(i + 1, j) == 0) {
				b.at<uchar>(0, 0)++;
			}
			if (a.at<int>(i, j) == 0 && a.at<int>(i + 1, j) == 1) {
				b.at<uchar>(0, 1)++;
			}
			if (a.at<int>(i, j) == 0 && a.at<int>(i + 1, j) == 2) {
				b.at<uchar>(0, 2)++;
			}
			if (a.at<int>(i, j) == 1 && a.at<int>(i + 1, j) == 0) {
				b.at<uchar>(1, 0)++;
			}
			if (a.at<int>(i, j) == 1 && a.at<int>(i + 1, j) == 1) {
				b.at<uchar>(1, 1)++;
			}
			if (a.at<int>(i, j) == 1 && a.at<int>(i + 1, j) == 2) {
				b.at<uchar>(1, 2)++;
			}
			if (a.at<int>(i, j) == 2 && a.at<int>(i + 1, j) == 0) {
				b.at<uchar>(2, 0)++;
			}
			if (a.at<int>(i, j) == 2 && a.at<int>(i + 1, j) == 1) {
				b.at<uchar>(2, 1)=2;
			}
			if (a.at<int>(i, j) == 2 && a.at<int>(i + 1, j) == 2) {
				b.at<uchar>(2, 2)++;
			}
		}
	}
	cout << "点对矩阵：" << endl << "" << b << endl << endl;
	//灰度共生矩阵
	Mat c = (Mat_<double>(3, 3));
	for (int m = 0; m < 3; m++) {
		for (int n = 0; n < 3; n++) {
			c.at<double>(m, n) = b.at<uchar>(m, n) / 20.0;
		}
	}
	cout << "灰度共生矩阵：" << endl << c << endl;



	system("pause");
}