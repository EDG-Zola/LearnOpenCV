/************************************************************************/
/*			此程序是用floodFill()函数来实现Photoshop的魔术棒的功能      */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*							全局变量的声明                              */
/************************************************************************/
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;	//原图像，目标图，灰度图，掩膜图
int g_nFillMode = 1;	//漫水填充模式（空范围、渐变+固定范围、渐变+浮动范围）
int g_nLowDifference = 20, g_nUpDifference = 20; //负差最大值，正差最大值
int g_nConnecty = 4;	//floodFill函数标识符低8位的连通值（4 or 8），默认为4
bool g_bIsColor = true;	//是否为彩色窗口的布尔值
bool g_bUseMask = false;	//是否用掩膜窗口的布尔值
int g_nNewMaskVal = 255;	//新的重新绘制的掩膜像素值

/************************************************************************/
/*							onMouse()回调函数							*/
/*							描述：鼠标是否按下							*/
/************************************************************************/
static void onMouse(int event, int x, int y, int, void *){
	//如果鼠标没有按下，则返回
	if(event != EVENT_LBUTTONDOWN)
		return;
	/************************************************************************/
	/*						1.调用floodFill函数前的参数准备                 */
	/************************************************************************/
	Point seed = Point(x, y);	//种子点坐标
	int lowDifference = g_nFillMode == 0 ?  0 : g_nLowDifference; //空范围的漫水填充设置为0，否则为全局g_nLowDifference
	int upDifference = g_nFillMode == 0 ?  0 : g_nUpDifference; //空范围的漫水填充设置为0，否则为全局g_nUpDifference
	//floodFill函数的标识符为低8位为连通方式，7-15位为g_nNewMaskVal左移8位的值，16-23位为填充模式
	//当填充模式为FLOODFILL_FIXED_RANGE时，表示考虑当前像素与种子像素之间的差值，表示按浮动范围填充，否则为空范围填充
	int flags = g_nConnecty + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	//随机生成bgr颜色
	int b = (unsigned char)theRNG() & 255; //随机生成一个0到255的值
	int g = (unsigned char)theRNG() & 255; //随机生成一个0到255的值
	int r = (unsigned char)theRNG() & 255; //随机生成一个0到255的值
	Rect ccomp; //定义重绘区域的最小边界矩形区域
	//当为彩色模式时，用Scalar(b, g, r)生成颜色，当为灰度模式时，用Scalar(r*0.299 + g*0.587 + b*0.144)填充
	Scalar newValue = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.144);
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage; //目标图的赋值
	int area; //表示像素被重绘的个数

	/************************************************************************/
	/*						2.调用floodFill函数				                */
	/************************************************************************/
	//是否显示掩膜窗口
	if(g_bUseMask){
		//阈值函数threshold( InputArray src, OutputArray dst,double thresh, double maxval, int type )
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newValue, &ccomp, Scalar(lowDifference, lowDifference, lowDifference),
			Scalar(upDifference, upDifference, upDifference), flags);
		imshow("mask", g_maskImage);
	}
	else 
		area = floodFill(dst, seed, newValue, &ccomp, Scalar(lowDifference, lowDifference, lowDifference),
		Scalar(upDifference, upDifference, upDifference), flags);
	
	imshow("效果图", dst);
	cout << area << "个像素被重绘\n";
}

/************************************************************************/
/*							帮助操作说明                                */
/************************************************************************/
void hlepText(){
	cout << "\t欢迎来到漫水填充程序~\n";
	cout << "\t此程序根据鼠标选取的点搜索与图片中像素相近的点，并用不同的颜色标注\n";
	cout << "\t按键操作说明：\n";
	cout << "\t\t键盘按键【ESC】 -- 退出程序\n";
	cout << "\t\t键盘按键【1】 -- 切换彩色图/灰度图模式\n";
	cout << "\t\t键盘按键【2】 -- 显示/隐藏窗口\n";
	cout << "\t\t键盘按键【3】 -- 恢复原始图像\n";
	cout << "\t\t键盘按键【4】 -- 使用空范围进行漫水填充\n";
	cout << "\t\t键盘按键【5】 -- 使用渐变、固定范围进行漫水填充\n";
	cout << "\t\t键盘按键【6】 -- 使用渐变、浮动范围进行漫水填充\n";
	cout << "\t\t键盘按键【7】 -- floodFill的标识符低8位使用4连通方式\n";
	cout << "\t\t键盘按键【8】 -- floodFill的标识符低8位使用8连通方式\n";
}

/************************************************************************/
/*						main()函数：判断按键                            */
/************************************************************************/
int main(){
	hlepText();
	//1.载入原图
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "载入图片1.jpg失败" << endl;
		return false;
	}
	//2.目标图,灰度图，掩膜图的设置
	g_dstImage = g_srcImage.clone();//复制原图到目标图，也可用g_srcImage.copyTo(g_dstImage)
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY); //灰度图的设置
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//掩膜图的创建，单通道8位
	//3.创建命名窗口，参数设置为自动匹配大小，不可改变
	namedWindow("效果图",WINDOW_AUTOSIZE);
	//4.创建滑动条，并调用鼠标回调函数（谓词函数）
	createTrackbar("负差最大值", "效果图", &g_nLowDifference, 255, 0);
	createTrackbar("正差最大值", "效果图", &g_nLowDifference, 255, 0);
	setMouseCallback("效果图", onMouse, 0);
	//4.循环轮询按键
	while(1){
		//先显示效果图
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);
		//获取按键铵值
		int c = waitKey(1);
		//判断是否按下ESC键
		if ( (c & 255) == 27){
			cout << "程序退出....";
				break;
		}
		switch( static_cast<char> (c) ){
			//按键1被按下，效果图在彩色图/灰度图之间切换
			case '1':{
				if(g_bIsColor){
					cout << "按键1被按下，切换彩色模式/灰色模式，当前操作为切换【彩色模式】为【灰色模式】" << endl;
					cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
					g_maskImage = Scalar::all(0); //将mask所有元素设置为0
					g_bIsColor = false;
				}
				else{
					cout << "按键1被按下，切换彩色模式/灰色模式，当前操作为切换【灰色模式】为【彩色模式】" << endl;
					g_srcImage.copyTo(g_dstImage);
					g_maskImage = Scalar::all(0); //将mask所有元素设置为0
					g_bIsColor = true;
				}
				break;
			}
			//按键2被按下，显示/隐藏掩膜窗口
			case '2':{
				if(g_bUseMask){
					destroyWindow("mask");
					g_bUseMask = false;
				}
				else{
					namedWindow("mask", 0);
					g_maskImage = Scalar::all(0);
					imshow("mask", g_maskImage);
					g_bUseMask = false;
				}
				break;
			 }
			//按键3被按下，恢复原始图像
			case '3':{
				cout << "按键3被按下，恢复原始图像" << endl;
				g_srcImage.copyTo(g_dstImage);
				cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
				g_maskImage = Scalar::all(0);
				break;
			}
			//按键4被按下，使用空范围的漫水填充
			case '4':{
				cout << "按键4被按下，使用空范围的漫水填充" << endl;
				g_nFillMode = 0;
				break;
			 }
			//按键5被按下，使用渐变、固定范围漫水填充
			case '5':{
				cout << "按键5被按下，使用渐变、固定范围漫水填充" << endl;
				g_nFillMode = 1;
				break;
			}
			//按键6被按下，使用渐变、浮动范围漫水填充
			case '6':{
				cout << "按键6被按下，使用渐变、浮动范围漫水填充" << endl;
				g_nFillMode = 2;
				break;
			}
			 //按键7被按下，floodFill的标识符使用4连通方式
			case '7':{
				cout << "按键7被按下，floodFill的标识符使用4连通方式" << endl;
				g_nConnecty = 4;
				break;
			 }
			 //按键6被按下，floodFill的标识符使用8连通方式
			case '8':{
				cout << "按键8被按下，floodFill的标识符使用8连通方式" << endl;
				g_nConnecty = 8;
				break;
			 }
		}
	}
	return 0;
}