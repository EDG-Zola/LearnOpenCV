/************************************************************************/
/*		结合轨迹条的功能来实现方框滤波、均值滤波、高斯滤波              */
/************************************************************************/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*					创建全局变量                                       */
/************************************************************************/
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6; //方框滤波的轨迹条参数值
int g_nMeanFilterValue = 10; //均值滤波的轨迹条参数值
int g_nGaussianFilterValue = 6; //高斯滤波的轨迹条参数值
int g_nMedianFilterValue = 10; //中值滤波的轨迹条参数值
int g_nBilateralFilterValue = 10; //双边滤波的轨迹条参数值

/************************************************************************/
/*					轨迹条操作的回调函数声明                            */
/************************************************************************/
static void on_BoxFilter(int, void*);
static void on_MeanFilter(int, void*);
static void on_GaussianFilter(int, void*);
static void on_MedianFilter(int, void*);
static void on_BilateralFilter(int, void*);

/************************************************************************/
/*					    主函数程序入口                                  */
/************************************************************************/
int main(){
	//控制台窗口颜色为紫色
	system("color 5E");
	//1.创建窗口函数
	namedWindow("原图");
	namedWindow("效果图：方框滤波");
	namedWindow("效果图：均值滤波");
	namedWindow("效果图：高斯滤波");
	namedWindow("效果图：中值滤波");
	namedWindow("效果图：双边滤波");

	//2.显示原图并将原图复制给目标图像
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data){	cerr << "打开图片1.jpg错误"; return false;}
	imshow("原图", g_srcImage);
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	//3.创建轨迹条,最大滑动值为40
	createTrackbar("内核值", "效果图：方框滤波", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	createTrackbar("内核值", "效果图：均值滤波", &g_nMeanFilterValue, 50, on_MeanFilter);
	on_MeanFilter(g_nMeanFilterValue, 0);
	createTrackbar("内核值", "效果图：高斯滤波", &g_nGaussianFilterValue, 50, on_GaussianFilter);
	on_GaussianFilter(g_nGaussianFilterValue, 0);
	createTrackbar("内核值", "效果图：中值滤波", &g_nMedianFilterValue, 50, on_MedianFilter);
	on_MedianFilter(g_nMedianFilterValue, 0);
	createTrackbar("内核值", "效果图：双边滤波", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);

	//4.打印操作说明信息
	cout << "\t请滑动每个窗口的滑动条查看滤波效果" << endl;
	cout << "\t退出程序，请按'q'键\n";
	while(char(waitKey(1)) !=  'q') {}
	return 0;

}

/************************************************************************/
/*                  方框滤波回调函数                                    */
/************************************************************************/
static void on_BoxFilter(int, void*){
	//方框滤波函数操作
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1), Point(-1,-1), true, 4);
	//显示窗口
	imshow("效果图：方框滤波", g_dstImage1);
}

/************************************************************************/
/*                  均值滤波回调函数                                    */
/************************************************************************/
static void on_MeanFilter(int, void*){
	//均值滤波函数操作
	blur(g_srcImage, g_dstImage2, Size(g_nMeanFilterValue+1, g_nMeanFilterValue+1), Point(-1,-1), 4);
	//显示窗口
	imshow("效果图：均值滤波", g_dstImage2);
}

/************************************************************************/
/*                  高斯滤波回调函数                                    */
/************************************************************************/
static void on_GaussianFilter(int, void*){
	//高斯滤波函数操作
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianFilterValue*2+1, g_nGaussianFilterValue*2+1), 0, 0);
	//显示窗口
	imshow("效果图：高斯滤波", g_dstImage3);
}

/************************************************************************/
/*                  中值滤波回调函数                                    */
/************************************************************************/
static void on_MedianFilter(int, void*){
	//高斯滤波函数操作
	medianBlur(g_srcImage, g_dstImage4, g_nMedianFilterValue*2+1);
	//显示窗口
	imshow("效果图：中值滤波", g_dstImage4);
}

/************************************************************************/
/*                  双边滤波回调函数                                    */
/************************************************************************/
static void on_BilateralFilter(int, void*){
	//高斯滤波函数操作
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
	//显示窗口
	imshow("效果图：双边滤波", g_dstImage5);
}
