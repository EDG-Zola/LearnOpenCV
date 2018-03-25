#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
//用const变量替换#define宏定义
const string g_sWindowName = "程序窗口";
/************************************************************************/
/*                        全局函数的声明                                */
/************************************************************************/
void on_MouseHandle(int event, int x, int y, int flags,void* param);
void DrawRectangle(cv::Mat &imag, cv::Rect box);
void ShowHelpText();
/************************************************************************/
/*                        全局变量的声明                                */
/************************************************************************/
Rect g_rectangle;
bool g_bDrawwingBox = false;//是否进行绘制
RNG g_rng(12345);
/************************************************************************/
/*                        main函数：                                   */
/************************************************************************/
int main(int argc, char** argv){
	//准备参数
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC4), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);
	//设置鼠标操作的回调函数
	namedWindow(g_sWindowName);
	setMouseCallback(g_sWindowName, on_MouseHandle, (void*) &srcImage);
	//函数主循环，当进行绘制的标识符为真时，进行绘制
	while(1){
		srcImage.copyTo(tempImage);//复制原图到临时变量
		if (g_bDrawwingBox)
			DrawRectangle(tempImage, g_rectangle);//当进行绘制的标识符为真时，进行绘制
		imshow(g_sWindowName, tempImage);
		if (waitKey(10) == 27)
			break;//按下ESC键，程序退出
	}
	return 0;
}

/************************************************************************/
/*  鼠标回调函数on_MouseHandle：根据不同的鼠标事件进行不同的操作        */
/************************************************************************/
void on_MouseHandle(int event, int x, int y, int flags,void* param){
	Mat &image = *(cv::Mat*) param;
		switch(event){
			//鼠标移动消息
			case EVENT_MOUSEMOVE:
			{
				//如果是否进行绘制标识符为真时，记录长和宽到Rect变量中
				if(g_bDrawwingBox){
					g_rectangle.width = x - g_rectangle.x;
					g_rectangle.height = y - g_rectangle.y;
				}
				break;
			}
			//鼠标左键按下消息
			case EVENT_LBUTTONDOWN:
				{
					g_bDrawwingBox = true;
					g_rectangle = Rect(x, y, 0 ,0);//记录起始点
				}
				break;
			//鼠标左键抬起
			case EVENT_LBUTTONUP:
				{
					g_bDrawwingBox = false;
					//对宽和高小于0时进行处理
					if (g_rectangle.width < 0)
					{
						g_rectangle.x += g_rectangle.width;
						g_rectangle.width *= -1;
					}
					if (g_rectangle.height < 0)
					{
						g_rectangle.y += g_rectangle.height;
						g_rectangle.height *= -1;
					}
					//调用函数进行绘制
					DrawRectangle(image, g_rectangle);
				}
				break;
	}
}

/************************************************************************/
/*             DrawRectangle函数：自定义的矩形绘制函数                  */
/************************************************************************/
void DrawRectangle(cv::Mat &img, cv::Rect box){
	rectangle(img, box.tl(), box.br(),
		Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//随机颜色

}