/************************************************************************/
/*				此程序通过threshold()函数进行图像阈值操作               */
/************************************************************************/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/************************************************************************/
/*							全局变量的声明                              */
/************************************************************************/
const string NameWindow = "程序窗口";
Mat g_srcImage, g_grayImage, g_dstImage;
int g_nTresholdValue = 100;
int g_nTresholdType = 3;	//阈值方式默认为 反阈值化为0模式

/************************************************************************/
/*							全局函数的声明                              */
/************************************************************************/
void helpText();//帮助显示操作说明函数
void on_Treshold(int, void*);

/************************************************************************/
/*							主函数程序                                  */
/************************************************************************/
int main(){
	helpText();
	//1.载入图像与显示原图片
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "打开图片1.jpg失败" << endl;
		return false;
	}
	imshow("原图", g_srcImage);
	//2.留一幅图片作为灰度图
	cvtColor(g_srcImage, g_grayImage,COLOR_BGR2GRAY);
	//3.创建滑动条
	namedWindow(NameWindow);
	createTrackbar("阈值参数值", NameWindow, &g_nTresholdValue, 255, on_Treshold, 0);
	createTrackbar("阈值模式", NameWindow, &g_nTresholdType, 4, on_Treshold, 0);
	//4.调用回调函数
	on_Treshold(0, 0);
	//5.轮询方式检测按键
	while(1){
		int c = waitKey(20);
		//如果按键为ESC或q键，退出程序
		if(static_cast<char>(c) == 27 || static_cast<char>(c) == 'q')
			break;
	}
	return 0;
}

void on_Treshold(int, void*){
	threshold(g_grayImage, g_dstImage, g_nTresholdValue, 255, g_nTresholdType);
	imshow(NameWindow, g_dstImage);
}

void helpText(){
	system("color 5E");
	cout << "\t欢迎来到阈值操作演示程序\n";
	cout << "\t按键说明操作如下：\n"
		 << "\t\t按下ESC或q键 -- 退出程序\n"
		 << "\t\t滑动到0 -- 二进制阈值\n"
		 << "\t\t滑动到1 -- 反二进制阈值\n"
		 << "\t\t滑动到2 -- 截断阈值\n"
		 << "\t\t滑动到3 -- 反阈值化为0\n"
		 << "\t\t滑动到4 -- 阈值化为0\n";
}



