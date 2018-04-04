/************************************************************************/
/*			通过调用medianBlur()函数实现中值滤波                        */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
	Mat srcImage = imread("1.tif");
	Mat dstImage;
	//调用中值滤波medianBlur（）,第三个参数为核的大小
	medianBlur(srcImage, dstImage, 3);
	imshow("原图",srcImage);
	imshow("效果图：中值滤波", dstImage);
	waitKey(0);
	return 0;
}