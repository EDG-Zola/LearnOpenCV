/************************************************************************/
/*					使用floodFill()函数实现漫水填充                     */
/************************************************************************/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

int main(){
	Mat srcImage = imread("1.jpg");
	imshow("原图", srcImage);
	Rect ccmp;
	floodFill(srcImage, Point(50, 300), Scalar(155, 255, 55), &ccmp, Scalar(20, 20, 20), Scalar(20, 20, 20), 8);
	imshow("漫水填充", srcImage);
	waitKey(0);
	return 0;
	
}