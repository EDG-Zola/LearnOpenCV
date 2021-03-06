/************************************************************************/
/*    使用morphologyEx(）函数加createTracebar来综合展示形态学滤波操作   */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*						全局变量的声明                                  */
/************************************************************************/
Mat g_srcImage, g_dstImage, g_elment;
int g_nElementShape = MORPH_RECT;	//设置默认内核矩阵形状为矩形
int g_nMaxIterationNum = 10;	//最大的迭代次数
int g_nOpenCloseNum = 0;	//开闭运算，默认为0
int g_nErodeDilateNum = 0;	//腐蚀膨胀运算，默认为腐蚀
int g_nTopBlackNum = 0;		//礼帽黑帽运算，默认为礼帽

/************************************************************************/
/*						回调函数的声明                                  */
/************************************************************************/
static void on_OpenClose(int, void *);
static void on_ErodeDilate(int, void *);
static void on_TopBlack(int, void *);
static void showHelpText(void);

/************************************************************************/
/*						主函数程序入口	                               */
/************************************************************************/
int main(){
	showHelpText();
	//0.载入图片
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "打开图片1.jpg失败\n";
		return false;
	}
	//1.创建命名窗口
	namedWindow("原图");
	namedWindow("开/闭运算");
	namedWindow("腐蚀/膨胀运算");
	namedWindow("礼帽/黑帽运算");
	
	//2.显示原图，创建滑动条
	imshow("原图", g_srcImage);
	createTrackbar("迭代值", "开/闭运算", &g_nOpenCloseNum, g_nMaxIterationNum*2+1, on_OpenClose);
	createTrackbar("迭代值", "腐蚀/膨胀运算", &g_nErodeDilateNum, g_nMaxIterationNum*2+1, on_ErodeDilate);
	createTrackbar("迭代值", "礼帽/黑帽运算", &g_nTopBlackNum, g_nMaxIterationNum*2+1, on_TopBlack);

	//3.参数赋值
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackNum = 2;

	//4.改变内核矩阵形状
	while(1) {
		//4.1 执行回调函数
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlack(g_nTopBlackNum, 0);
		//4.2 获取按键
		int c;
		c = waitKey(0);
		if((char)c == 'q' || (char)c == 27)
			break;
		switch(c){
			case 49:{g_nElementShape = MORPH_ELLIPSE; break;} //1的ASII码为49，内核形状为椭圆MORPH_ELLIPSE
			case 50:{g_nElementShape = MORPH_RECT; break;} //2的ASII码为50，内核形状为矩形MORPH_RECT
			case 51:{g_nElementShape = MORPH_CROSS; break;} //3的ASII码为51，内核形状为十字形MORPH_CROSS
			case 32:{g_nElementShape = (++g_nElementShape % 3); break;} //空格的ASII码为32，形状在椭圆、矩形、十字形中循环
			default: break;
		}
	}
	return 0;
}

/************************************************************************/
/*						on_OpenClose()回调函数                          */
/************************************************************************/
static void on_OpenClose(int, void *){
	//计算偏移量
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//自定义核
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, g_elment);
	imshow("开/闭运算", g_dstImage);
}

/************************************************************************/
/*						on_ErodeDilate()回调函数                        */
/************************************************************************/
static void on_ErodeDilate(int, void *){
	//计算偏移量
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//自定义核
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_DILATE, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_ERODE, g_elment);
	imshow("腐蚀/膨胀运算", g_dstImage);
}

/************************************************************************/
/*					void on_TopBlack()回调函数                          */
/************************************************************************/
static void on_TopBlack(int, void *){
	//计算偏移量
	int offset = g_nTopBlackNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//自定义核
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, g_elment);
	imshow("礼帽/黑帽运算", g_dstImage);
}


static void showHelpText(void){
	//输出一些帮助信息
	system("color 5E");
	printf("\n\t请调整滚动条观察图像效果\n\n");
	printf( "\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
		"\t\t键盘按键【1】- 使用椭圆(Elliptic)结构元素\n"
		"\t\t键盘按键【2】- 使用矩形(Rectangle )结构元素\n"
		"\t\t键盘按键【3】- 使用十字型(Cross-shaped)结构元素\n"
		"\t\t键盘按键【空格SPACE】- 在矩形、椭圆、十字形结构元素中循环\n"	);
}