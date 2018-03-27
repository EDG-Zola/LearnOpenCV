/************************************************************************/
/*                          用于绘制基本的图形                          */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
/************************************************************************/
/*                    全局变量的声明                                    */
/************************************************************************/
const int g_nWindowWidth = 600;//定义窗口大小为600
const string g_sWindowName1 = "绘制图1"; //窗口标签定义的宏
const string g_sWindowName2 = "绘制图2"; //窗口标签定义的宏

/************************************************************************/
/*       DrawEclipse()函数：用于绘制不同角度，相同尺寸的椭圆           */
/************************************************************************/
void DrwaEclipse(Mat img, double angle){
	int thickness = 2;//线宽为2
	int lineType = 8;//线型为联通线型
	ellipse(img,
		Point(g_nWindowWidth/2, g_nWindowWidth/2),
		Size(g_nWindowWidth/4, g_nWindowWidth/16),
		angle, /*角度*/
		0,
		360, /*角度范围*/
		Scalar(255, 129, 0),/*颜色为蓝绿色*/
		thickness,
		lineType);
}

/************************************************************************/
/*             DraweFilledCircle()函数：用于实心圆的绘制                */
/************************************************************************/
void DraweFilledCirclee(Mat img, Point center){
	int thickness = -1;//线宽为-1，因此绘制的圆为实心的
	int lineType = 8;//线型为联通线型
	circle(img,
		center,
		g_nWindowWidth/32,/*圆的半径*/
		Scalar(0, 0, 255),/*颜色为红色*/
		thickness,
		lineType);
}

/************************************************************************/
/*                DrawePolygon()函数：用于凹变形的绘制                  */
/************************************************************************/
void DrawePolygon(Mat img){
	int lineType = 8;//线型为联通线型
	//创建一些点1行，20列的点
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(    g_nWindowWidth/4,   7*g_nWindowWidth/8 );
	rookPoints[0][1]  = Point(  3*g_nWindowWidth/4,   7*g_nWindowWidth/8 );
	rookPoints[0][2]  = Point(  3*g_nWindowWidth/4,  13*g_nWindowWidth/16 );
	rookPoints[0][3]  = Point( 11*g_nWindowWidth/16, 13*g_nWindowWidth/16 );
	rookPoints[0][4]  = Point( 19*g_nWindowWidth/32,  3*g_nWindowWidth/8 );
	rookPoints[0][5]  = Point(  3*g_nWindowWidth/4,   3*g_nWindowWidth/8 );
	rookPoints[0][6]  = Point(  3*g_nWindowWidth/4,     g_nWindowWidth/8 );
	rookPoints[0][7]  = Point( 26*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][8]  = Point( 26*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][9]  = Point( 22*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][10] = Point( 22*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][11] = Point( 18*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][12] = Point( 18*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][13] = Point( 14*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][14] = Point( 14*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][15] = Point(    g_nWindowWidth/4,     g_nWindowWidth/8 );
	rookPoints[0][16] = Point(    g_nWindowWidth/4,   3*g_nWindowWidth/8 );
	rookPoints[0][17] = Point( 13*g_nWindowWidth/32,  3*g_nWindowWidth/8 );
	rookPoints[0][18] = Point(  5*g_nWindowWidth/16, 13*g_nWindowWidth/16 );
	rookPoints[0][19] = Point(    g_nWindowWidth/4,  13*g_nWindowWidth/16 );
	
	const Point* ppt[1] = {rookPoints[0]};//多边形的顶点集
	int npt[] = {20};//要绘制的多边形顶点数目
	fillPoly(img,
		ppt,
		npt,/*圆的半径*/
		1,/*要绘制的多边形顶点数量*/
		Scalar(255, 255, 255),/*颜色为白色*/
		lineType);
}

/************************************************************************/
/*                     DrawLine()函数：用于绘制线                       */
/************************************************************************/
void DrawLine(Mat img, Point start, Point end){
	int thickness = 2;//线宽为2
	int lineType = 8;//线型为联通线型
	line(img,
		start,/*线的起始点*/
		end,/*线的终止点*/
		Scalar(0, 0, 0),/*颜色为黑色*/
		thickness,
		lineType);
}
int main(){
	//创建空白的Mat对象
	Mat atomImage = Mat::zeros(g_nWindowWidth, g_nWindowWidth, CV_8UC3);
	Mat rookImage = Mat::zeros(g_nWindowWidth, g_nWindowWidth, CV_8UC3);

	/************************************************************************/
	/*                        1.绘制原子示例图                              */
	/************************************************************************/
	//1.1先绘制一些椭圆
	DrwaEclipse(atomImage, 90);
	DrwaEclipse(atomImage, 0);
	DrwaEclipse(atomImage, 45);
	DrwaEclipse(atomImage, -45);
	//1.2再绘制圆心
	DraweFilledCirclee(atomImage, Point(g_nWindowWidth/2, g_nWindowWidth/2));

	/************************************************************************/
	/*                         2.绘制组合图形                               */
	/************************************************************************/
	//2.1先绘制一个椭圆
	DrawePolygon(rookImage);
	//2.2在绘制一个矩形
	rectangle(rookImage,
	Point(0, 7*g_nWindowWidth/8),/*矩形的左上点坐标*/
	Point(g_nWindowWidth, g_nWindowWidth),/*矩形的右下点坐标*/
	Scalar(0, 255, 255),/*颜色为黄色*/
	-1,/*实心*/
	8 /*线型为联通线型*/
	);
	//2.3绘制一些线段
	DrawLine(rookImage, Point(0, 15*g_nWindowWidth/16),               Point(g_nWindowWidth,    15*g_nWindowWidth/16));//一条窗口上的横线
	DrawLine(rookImage, Point(g_nWindowWidth/4,   7*g_nWindowWidth/8), Point(g_nWindowWidth/4,   g_nWindowWidth));//一条窗口上的竖线
	DrawLine(rookImage, Point(g_nWindowWidth/2,   7*g_nWindowWidth/8), Point(g_nWindowWidth/2,   g_nWindowWidth));//一条窗口上的竖线
	DrawLine(rookImage, Point(3*g_nWindowWidth/4, 7*g_nWindowWidth/8), Point(3*g_nWindowWidth/4, g_nWindowWidth));//一条窗口上的竖线

	/************************************************************************/
	/*                       3.显示绘制的图形                               */
	/************************************************************************/
	imshow(g_sWindowName1, atomImage);
	moveWindow(g_sWindowName1, 0, 200);
	imshow(g_sWindowName2, rookImage);
	moveWindow(g_sWindowName2, g_nWindowWidth, 200);

	waitKey(0);
	return 0;
}