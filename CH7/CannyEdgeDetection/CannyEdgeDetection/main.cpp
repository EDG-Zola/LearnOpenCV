/************************************************************************/
/*						本程序用来演示Canny边缘检测                     */
/************************************************************************/
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	//1.载入原图片
	Mat srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "打开原图片1.jpg失败" << endl;
		return 0;
	}
	imshow("原图",srcImage);
	Mat edgeImage = srcImage.clone();
	//2.Canny检测
	//void Canny( InputArray image, OutputArray edges,
	//double threshold1, double threshold2,
	//	int apertureSize = 3, bool L2gradient = false );
	//threshold1:第一个滞后阈值
	//threshold2:第二个滞后阈值，推荐高低阈值比在2:1到3:1之间
	//apertureSize:Sobel算子的孔径大小
	//方法一：直接调用Canny函数
	Canny(srcImage, edgeImage, 150, 100, 3);
	imshow("效果图1",edgeImage);
	//方法二：转换为灰度图，降噪，用Canny，将得到的边缘用作掩码，拷贝原图到效果图上，得到彩色边缘图
	Mat dst, gray, edge;
	//2.1 创建与srcImage相同大小和类型的dst
	dst.create(srcImage.size(), srcImage.type());
	//2.2 转换为灰度图
	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
	//2.3降噪:3X3的内核
	blur(gray, edge,Size(3,3));
	//2.4调用Canny
	Canny(edge, edge, 3, 9, 3);
	//2.5将dst设置为全0
	dst = Scalar::all(0);
	//2.6 将得到的边缘用作掩码，拷贝原图到效果图上
	srcImage.copyTo(dst, edge);
	//2.7显示彩色Canny效果
	imshow("彩色Canny",dst);
	waitKey(0);
	return 0;
}