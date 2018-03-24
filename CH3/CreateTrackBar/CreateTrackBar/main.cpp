#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/* 全局变量的声明                                                                     */
/************************************************************************/
const string g_sWindoWName = "线性混合实例";
const int g_nMaxAlphaValue = 100;//Alpha的最大值
int g_nAlphaValueSlider;//滑动条对应变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;
/************************************************************************/
/* on_Trackbar函数：响应滑动条的回调函数                                                                     */
/************************************************************************/
void on_Trackbar(int, void*){
	//求出当前Alpha值相对于最大值的比例
	//g_dAlphaValue =  (double) g_nAlphaValueSlider/g_nMaxAlphaValue;//使用强制类型转换转为double型
	//使用C++特性的强制类型转换为以下语句
	g_dAlphaValue =  static_cast<double> (g_nAlphaValueSlider)/g_nMaxAlphaValue;
	//Beta值为1 - Alpha值
	g_dBetaValue = 1.0 - g_dAlphaValue;
	//根据Alpha和Beta值将两张图片进行线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	
	
	//显示线性混合的效果图
	imshow(g_sWindoWName, g_dstImage);
}
/************************************************************************/
/* 主函数入口程序：创建窗体并在回调函数on_Trackbar中显示                                                                     */
/************************************************************************/
int main(){
	//加载图片（两图片的尺寸必须相同）
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");
	if(!g_srcImage1.data){
		cout << "读取第一幅图片错误，请确定目录下是否有imread指定指定的图片\n";
		return -1;
	}
	if(!g_srcImage2.data){
		cout << "读取第二幅图片错误，请确定目录下是否有imread指定指定的图片\n";
		return -1;
	}
	//将滑动条的初识位置设置为70
	g_nAlphaValueSlider = 70;
	//创建窗体,属性为 1：WINDOW_AUTOSIZE， 0：WINDOW_NORMAL
	namedWindow(g_sWindoWName, 1);
	//在创建窗体时，创建一个滑动条的控件
	char TrackbarName[50];
	sprintf(TrackbarName, "透明值 %d", g_nMaxAlphaValue);
	
	createTrackbar(TrackbarName, g_sWindoWName, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlider, 0);

	////获取当前滑动条的位置函数的使用
	//int currentAlphaValueSlider = getTrackbarPos(TrackbarName, g_sWindoWName);
	//cout << "当前滑动条的位置为 " << currentAlphaValueSlider << endl;

	waitKey(0);
	return 0;

}