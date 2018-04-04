/************************************************************************/
/*			通过调用bilateralBlur()函数实现双边滤波                        */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
	Mat srcImage = imread("1.png");
	Mat dstImage;
	//调用中值滤波bilateralBlur(),第三个参数为核的大小
	bilateralFilter(srcImage, dstImage, 25, 25*2, 25/2);
	imshow("原图",srcImage);
	imshow("效果图：双边滤波", dstImage);
	imwrite("out.jpg", dstImage);
	waitKey(0);
	return 0;
}