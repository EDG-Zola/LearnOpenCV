#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("原图：腐蚀操作", srcImage);

	Mat elment1 = getStructuringElement(MORPH_RECT, Size(15,15));//返回指定形状和尺寸的结构元素（内核矩阵）
	Mat desImage;
	erode(srcImage, desImage, elment1);
	imshow("效果图：腐蚀操作（15,15）", desImage);

	Mat elment2 = getStructuringElement(MORPH_RECT, Size(20,20));//返回指定形状和尺寸的结构元素
	erode(srcImage, desImage, elment2);
	imshow("效果图：腐蚀操作（20,20）", desImage);

	waitKey(0);
}