#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv;
using namespace std;

void main()
{   // 加载矩阵
	Mat src = (Mat_<int>(7, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0);
	cout << "原矩阵：" << endl << "" << src << endl << endl;
	Mat dst = src.clone();

	for (int i = 3 / 2; i < src.rows -1; i++)
	{
		for (int j = 3 / 2; j < src.cols -1; j++)
		{
			int gray0 = src.at<int>(i - 1, j - 1);
			int gray1 = src.at<int>(i - 1, j);
			int gray2 = src.at<int>(i - 1, j + 1);
			int gray3 = src.at<int>(i, j - 1);
			int gray = src.at<int>(i, j); //中心像素
			int gray4 = src.at<int>(i, j + 1);
			int gray5 = src.at<int>(i + 1, j - 1);
			int gray6 = src.at<int>(i + 1, j);
			int gray7 = src.at<int>(i + 1, j + 1);

			//属于m通道但不是4通道的四种情况
			if (gray == gray2 && gray != gray1 && gray != gray4) {
				dst.at<int>(i - 1, j) = 1;
			}
			if (gray == gray7 && gray != gray6 && gray != gray4) {
				dst.at<int>(i + 1, j) = 1;
			}
			if (gray == gray5 && gray != gray3 && gray != gray6) {
				dst.at<int>(i + 1, j) = 1;
			}
			if (gray == gray0 && gray != gray1 && gray != gray3) {
				dst.at<int>(i - 1, j) = 1;
			}
		}
	}

	cout << "m连通变4连通：" << endl << "" << dst << endl << endl;
	system("pause");
}