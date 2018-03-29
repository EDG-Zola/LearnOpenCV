/************************************************************************/
/*                       调整图片的对比度和亮度                         */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
/************************************************************************/
/*                      全局变量声明                                    */
/************************************************************************/
int g_nContrastValues = 0;//对比度
int g_nBrightValues = 0;//亮度
Mat g_srcImage, g_dstImage;
const string g_sContrast = "对比度： ";
const string g_sBright = "亮度： ";
const string g_sWindowName = "效果图窗口";

/************************************************************************/
/*						函数声明                                       */
/************************************************************************/
static void on_ContrastAndBright(int, void* );

/************************************************************************/
/*						主函数                                          */
/************************************************************************/
int main(){
	system("color 5E");
	//1. 读入图片
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "读取图片1.jpg失败" << endl;
		return false;
	}
	//将目标图片设置为源图片的大小类型
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//2. 设置对比度和亮度的初始值
	g_nContrastValues = 80;
	g_nBrightValues = 80;
	//3. 创建效果窗口(此步骤必须放在创建滑动条前面！！1)
	namedWindow(g_sWindowName, 1);//使用默认值（自动匹配大小）
	//4.创建滑动条
	createTrackbar(g_sContrast, g_sWindowName, &g_nContrastValues, 300,  on_ContrastAndBright);//对比度的最大值为300
	createTrackbar(g_sBright, g_sWindowName, &g_nContrastValues, 200,  on_ContrastAndBright);//亮度的最大值为200
	//5. 进行回调函数的初始化
	on_ContrastAndBright(g_nContrastValues, 0);
	on_ContrastAndBright(g_nBrightValues, 0);
	cout << "程序运行成功" <<endl;
	
	//6. 按下‘q’键，退出程序
	while(char(waitKey(1)) != 'q'){
	}
	
	return 0;
}

/************************************************************************/
/*					改变图像对比度和亮度的回调函数                      */
/************************************************************************/
static void on_ContrastAndBright(int, void* ){
	int rowNumber = g_srcImage.rows;
	int colNumber = g_srcImage.cols;
	for (int i = 0; i < rowNumber; ++i){
		for (int j = 0; j < colNumber; ++j){
			g_dstImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[0] + g_nBrightValues);//蓝色通道
			g_dstImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[1] + g_nBrightValues);//绿色通道
			g_dstImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[2] + g_nBrightValues);//红色通道
		}
	}
	//创建窗口
	namedWindow("原始图像");
	imshow("原始图像", g_srcImage);
	imshow(g_sWindowName, g_dstImage);
}