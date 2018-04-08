/************************************************************************/
/*		结合轨迹条的功能来实现腐蚀、膨胀操作			                */
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
Mat g_srcImage, g_dsrImage, Matelenment;
int g_nTrackbarName = 1; //腐蚀/膨胀的滑动条，0表示腐蚀、1表示膨胀，默认选择为膨胀操作
int g_ngetStructSize = 3; //内核矩阵的大小

/************************************************************************/
/*					轨迹条操作的回调函数声明                            */
/************************************************************************/
static void on_TracebarNumberChange(int, void*); //改变腐蚀或膨胀操作
static void on_TracebarStructSizeChange(int, void*); //改变内核矩阵的大小
static void Process(); //处理腐蚀或膨胀操作

/************************************************************************/
/*					    主函数程序入口                                  */
/************************************************************************/
int main(){
	//控制台窗口颜色为紫色
	system("color 5E");
	//1.创建窗口函数
	namedWindow("原图");
	namedWindow("效果图：腐蚀/膨胀");

	//2.显示原图并将原图复制给目标图像
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data){	cerr << "打开图片1.jpg错误"; return false;}
	imshow("原图", g_srcImage);
	g_dsrImage = g_srcImage.clone();
	
	//3.创建使用内核矩阵
	Matelenment = getStructuringElement(MORPH_RECT, Size(g_ngetStructSize*2+1, g_ngetStructSize*2+1),
		Point(g_ngetStructSize, g_ngetStructSize));
	//4.创建轨迹条,最大内核矩阵滑动值为21
	createTrackbar("腐蚀/膨胀", "效果图：腐蚀/膨胀", &g_nTrackbarName, 1, on_TracebarNumberChange);
	on_TracebarNumberChange(g_nTrackbarName, 0);
	createTrackbar("内核矩阵大小", "效果图：腐蚀/膨胀", &g_ngetStructSize, 21, on_TracebarStructSizeChange);
	on_TracebarStructSizeChange(g_ngetStructSize, 0);

	//4.打印操作说明信息
	cout << "\t请滑动每个窗口的滑动条查看腐蚀膨胀效果" << endl;
	cout << "\t退出程序，请按'q'键\n";
	while(char(waitKey(1)) !=  'q') {}
	return 0;

}

/************************************************************************/
/*                  static void Process()函数                                    */
/************************************************************************/
static void Process(){
	//创建使用内核矩阵
	Matelenment = getStructuringElement(MORPH_RECT, Size(g_ngetStructSize*2+1, g_ngetStructSize*2+1),
		Point(g_ngetStructSize, g_ngetStructSize));
	//进行腐蚀或膨胀操作
	if(g_nTrackbarName == 1){
		dilate(g_srcImage, g_dsrImage, Matelenment);
	}
	else if(g_nTrackbarName == 0){
		erode(g_srcImage, g_dsrImage, Matelenment);
	}
	//显示腐蚀或膨胀操作
	imshow("效果图：腐蚀/膨胀", g_dsrImage);
}

/************************************************************************/
/*                  改变腐蚀/膨胀操作回调函数                                    */
/************************************************************************/
static void on_TracebarNumberChange(int, void*){
	//腐蚀和膨胀之间效果已经切换，只需要调用Process函数，使改变后的效果立即显示出来
	Process();
}

/************************************************************************/
/*                 改变内核矩阵大小回调函数                                    */
/************************************************************************/
static void on_TracebarStructSizeChange(int, void*){
	//腐蚀和膨胀之间效果已经切换，只需要调用Process函数，使改变后的效果立即显示出来
	Process();
}