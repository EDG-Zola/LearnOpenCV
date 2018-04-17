/************************************************************************/
/*				此程序演示了使用Laplacian()函数的效果                   */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	Mat srcImage, dst, gray, abs_dst;
	Mat contrastImage;
	//1.载入原图并显示
	srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "打开图片1.jpg失败" << endl;
		return false;
	}
	imshow("原图", srcImage);
	//2.用高斯滤波器对原图降噪
	GaussianBlur(srcImage, srcImage, Size(3,3), 0, 0, BORDER_DEFAULT);
	//3.转换为灰度图
	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
	//4.进行拉普拉斯变换,ksize = 3
	Laplacian(gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//5.计算绝对值，将计算结果转换为8位
	convertScaleAbs(dst, abs_dst, 1, 0);
	//6.显示效果
	imshow("Laplacian算子效果", abs_dst);
	//addWeighted(srcImage, 1, abs_dst, -1, 0, contrastImage);
	//imshow("增强对比效果图", contrastImage);
	waitKey(0);
	return 0;
}

