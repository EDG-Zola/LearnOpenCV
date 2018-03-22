#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("原图：均值滤波", srcImage);

	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));
	imshow("效果图：均值滤波（7,7）", dstImage);

	blur(srcImage, dstImage, Size(15, 15));
	imshow("效果图：均值滤波（15,15）", dstImage);

	waitKey(0);
}