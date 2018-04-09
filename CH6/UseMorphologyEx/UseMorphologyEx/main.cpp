/************************************************************************/
/*			使用morphologyEx进行形态学的基本操作                        */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*			         		创建全局变量                                */
/************************************************************************/
int g_nStructElement = 3;//内核矩阵的大小

/************************************************************************/
/*							函数原型的声明                              */
/************************************************************************/
void helpText(void);//帮助操作的说明

/************************************************************************/
/*							 主函数程序入口                             */
/************************************************************************/


int main(){
	helpText();
	Mat srcImage, dstImage, element;
	srcImage = imread("1.jpg");
	dstImage = srcImage.clone();
	element = getStructuringElement(MORPH_RECT, Size(g_nStructElement*2+1, g_nStructElement*2+1), Point(g_nStructElement, g_nStructElement));

	//1.创建命名窗口
	namedWindow("原图");
	namedWindow("效果图");

	//2.通过输入字符，显示腐蚀、膨胀、开闭、礼貌、黑帽、形态学梯度效果
	int op;
	while (cin >> op){
		switch (op){
			case 0: {morphologyEx(srcImage, dstImage, MORPH_ERODE, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}		//腐蚀操作
			case 1: {morphologyEx(srcImage, dstImage, MORPH_DILATE, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}	//膨胀操作
			case 2: {morphologyEx(srcImage, dstImage, MORPH_OPEN, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}		//开操作
			case 3: {morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}		//闭操作
			case 4: {morphologyEx(srcImage, dstImage, MORPH_GRADIENT, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}	//梯度操作
			case 5: {morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}	//顶帽操作
			case 6: {morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);imshow("原图",srcImage);imshow("效果图",dstImage);break;}	//黑帽操作
			default: {cout << "输入错误，请输入数字0~7" << endl; continue;}
		}
	}
	waitKey(0);
	return 0;
}

void helpText(void){
	system("color 5E");
	cout << "\t\t操作说明\t\t\t\n";
	cout << "\t\t请输入数字0-7进行相应的操作\t\n";
	cout << "\t\t0:\t腐蚀操作\t\n";
	cout << "\t\t1:\t膨胀操作\t\n";
	cout << "\t\t2:\t开操作\t\n";
	cout << "\t\t3:\t闭操作\t\n";
	cout << "\t\t4:\t梯度操作\t\n";
	cout << "\t\t5:\t顶帽操作\t\n";
	cout << "\t\t6:\t黑帽操作\t\n";
}