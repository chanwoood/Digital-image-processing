#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream>  
using namespace cv;
using namespace std;

void main() {
	Mat src = imread("0.jpg", 1);
	Mat dst = Mat::zeros(src.size(), src.type());
	if (!src.data) {
		cout <<"打开图像出错！" << endl;
	}
	/*第四个参数表示x方向放大倍数，第五个参数表示y方向放大倍数
	第三个参数为最终放大倍数取0,表示由第四、第五个参数决定。
	第六个参数表示采用最近邻插值法*/
	resize(src, dst, src.size()*0, 3.0, 3.0, INTER_LANCZOS4);
	imshow("原图像", src);
	imshow("3*3倍放大（双三次）", dst);
	waitKey(0);
}