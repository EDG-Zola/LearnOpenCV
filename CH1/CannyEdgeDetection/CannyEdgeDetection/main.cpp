#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("原图：canny边缘检测", srcImage);
	Mat dstImage, grayImage, edgeImage;
	//创建与srcImage同类型和大小的矩阵dst
	dstImage.create(srcImage.size(), srcImage.type());
	
	//将src转换为灰度图
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	//用均值滤波降噪
	blur(grayImage, edgeImage, Size(3, 3));
	//运行Canny算子
	Canny(edgeImage, edgeImage, 3, 9, 3);
	//显示效果图
	imshow("效果图：canny边缘检测", edgeImage);
	
	waitKey(0);
}