/************************************************************************/
/*		此程序演示了运用Scharr算子进行X方向和Y方向、X和Y方向的效果       */
/************************************************************************/
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	//定义Sobel算子要输出的Mat类型
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	//1.载入原图并显示
	Mat srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "打开图片1.jpg失败" << endl;
		return false;
	}
	imshow("原图", srcImage);
	//2.调用Scharr()函数进行X方向导数，默认没有应用缩放
	// calculates absolute values, and converts the result to 8-bit.
	Scharr(srcImage, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X方向导数", abs_grad_x);
	//3.调用Scharr()函数进行Y方向导数，默认没有应用缩放
	// calculates absolute values, and converts the result to 8-bit.
	Scharr(srcImage, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y方向导数", abs_grad_y);
	//4.整合X和Y方向
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("X和Y方向合并后梯度Scharr", dst);
	waitKey(0);
	return 0;
}