/************************************************************************/
/*					使用erode()函数进行膨胀操作                        */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*							全局变量声明                                */
/************************************************************************/
int g_ngetStructElement = 1; //内核矩阵的大小

/************************************************************************/
/*							主函数入口程序                              */
/************************************************************************/
int main(){
	system("color 5E");
	//1.创建Mat类及读取图片
	Mat srcImage, dstImage, element;
	srcImage = imread("2.jpg");

	//2.创建命名窗口及显示原图
	namedWindow("原图");
	namedWindow("腐蚀操作");
	imshow("原图", srcImage);

	//3.使用getStructuringElement创建一个内核矩阵
	element = getStructuringElement(MORPH_RECT, Size(g_ngetStructElement*2+1, g_ngetStructElement*2+1),
		Point(g_ngetStructElement, g_ngetStructElement));

	//4.使用erode函数显示效果
	erode(srcImage, dstImage, element);
	imshow("腐蚀操作", dstImage);

	//5,存储效果图
	imwrite("erode.jpg", dstImage);
	waitKey(0);
	return 0;
}