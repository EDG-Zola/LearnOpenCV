/************************************************************************/
/*                  使用addWeight()函数进行线性混合叠加                */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage(){
	//1.读取图片
	Mat srcImage1 = imread("mogu.jpg");
	Mat srcImage2 = imread("rain.jpg");
	if (!srcImage1.data){
		cerr << " 读取mogu.jpg失败！ " << endl;
		return false;
	}
	if (!srcImage2.data){
		cerr << " 读取rain.jpg失败！ " << endl;
		return false;
	}
	Mat dstImage;
	double alpha = 0.3;
	double beta = 1 - alpha;

	//2.addWeight()函数进行混合权重叠加
	addWeighted(srcImage1, alpha, srcImage2, beta, 0.0, dstImage);

	//3.显示结果
	namedWindow("利用AddWeight()实现图像叠加效果", 0);//可自行调整图片大小
	imshow("利用AddWeight()实现图像叠加效果", dstImage);

	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_AddImage();
	return 0;
}