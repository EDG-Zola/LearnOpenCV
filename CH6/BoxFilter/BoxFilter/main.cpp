/************************************************************************/
/*              调用方框滤波函数实现均值滤波                            */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	Mat dstImage1;
	Mat dstImage2;
	namedWindow("均值滤波：原图");
	namedWindow("均值滤波5x5：效果图");
	namedWindow("均值滤波10x10：效果图");
	imshow("均值滤波：原图", srcImage);
	//调用方框滤波函数，使第6个参数normalize = true， 即进行归一化处理，实现均值滤波
	//滤波器核的大小为5x5
	boxFilter(srcImage, dstImage1, srcImage.depth(), Size(5,5), Point(-1,-1), true, 4);
	boxFilter(srcImage, dstImage2, srcImage.depth(), Size(10,10), Point(-1,-1), true, 4);
	imshow("均值滤波5x5：效果图", dstImage1);
	imshow("均值滤波10x10：效果图", dstImage2);
	waitKey(0);
	return 0;
}