/************************************************************************/
/*		此程序用来演示图片尺寸变换，用到resize()、pyrUp()、pyrDown（）  */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*						全局变量的声明                                  */
/************************************************************************/
const string NameWindow = "程序窗口";
Mat g_srcImage, g_dstImage, g_tempImage;

/************************************************************************/
/*						helpText()函数：说明操作                        */
/************************************************************************/
void helpText(){
	system("color 5E");
	cout << "\t欢迎来到图像金字塔和Resize演示程序\n";
	cout << "\t按键说明：\n";
	cout << "\t\t按下ESC或q键 -- 退出程序\n"
		 << "\t\t按下1键 -- 基于【resize】函数进行图片放大\n"
		 << "\t\t按下2键 -- 基于【resize】函数进行图片缩小\n"
		 << "\t\t按下3键 -- 基于【pyrUp】函数进行图片放大\n"
		 << "\t\t按下4键 -- 基于【pyrDown】函数进行图片缩小\n";
}

/************************************************************************/
/*					main()函数，通过按键显示效果                        */
/************************************************************************/
int main(){
	helpText();
	//1.载入源图片并显示原图
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "打开图片1.jpg失败\n";
		return false;
	}
	imshow(NameWindow, g_srcImage);
	//2.参数赋值
	g_tempImage = g_srcImage;
	g_dstImage = g_tempImage;
	//轮询方式检测按键
	int c;
	while(1){
		c = waitKey(9);//读取按键的值，并将其转化为char类型，waitKey(1)为转换为整型值
		switch(c){
			//按下ESC按键，退出程序
			case 27:{
				return 0;
				break;
			}
			//按下q按键，退出程序
			case 'q':{
				return 0;
				break;
			}
			//按下1键，基于【resize】函数进行图片放大
			case '1':{
				resize(g_tempImage, g_dstImage, Size(g_tempImage.cols*2, g_tempImage.rows*2));
				cout << "按键【1】被按下，基于【resize】函数进行图片放大\n";
				break;
		    }
			 //按下2键，基于【resize】函数进行图片缩小
			case '2':{
				resize(g_tempImage, g_dstImage, Size(g_tempImage.cols/2, g_tempImage.rows/2), 0.0, 0.0, INTER_CUBIC);
				cout << "按键【2】被按下，基于【resize】函数进行图片缩小\n";
				break;
			 }
			 //按下3键，基于【pyrUp】函数进行图片放大
			case '3':{
				pyrUp(g_tempImage, g_dstImage, Size(g_tempImage.cols*2, g_tempImage.rows*2));
				cout << "按键【3】被按下，基于【pyrUp】函数进行图片放大\n";
				break;
			 }
			 //按下4键，基于【pyrDown】函数进行图片缩小
			case '4':{
				pyrDown(g_tempImage, g_dstImage, Size(g_tempImage.cols/2, g_tempImage.rows/2));
				cout << "按键【4】被按下，基于【pyrDown】函数进行图片缩小\n";
				break;
			 }
		}
		imshow(NameWindow,g_dstImage);
		g_tempImage = g_dstImage;
	}
	return 0;
}