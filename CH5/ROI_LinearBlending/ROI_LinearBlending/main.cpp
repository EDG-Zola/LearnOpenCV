/************************************************************************/
/*                  使用addWeight()函数和ROI的概念进行线性混合叠加         */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_LinearBlending(){
	//1.读取图片
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat srcImage2 = imread("dota_logo.jpg");
	if (!srcImage1.data){
		cerr << " 读取dota_logo.jpg失败！ " << endl;
		return false;
	}
	if (!srcImage2.data){
		cerr << " 读取dota_pa.jpg失败！ " << endl;
		return false;
	}
	Mat dstImage;
	double alpha = 0.8;
	double beta = 1 - alpha;
	//2.截取dota_logo的矩形区域作为ROI_Image
	Mat ROI_Image = srcImage1(Rect(200, 250, srcImage2.cols, srcImage2.rows));
	
	//3.addWeight()函数进行混合权重叠加
	addWeighted(ROI_Image, alpha, srcImage2, beta, 0.0, ROI_Image);

	//4.显示结果
	namedWindow("利用AddWeight()实现图像叠加效果");
	imshow("利用AddWeight()实现图像叠加效果", ROI_Image);

	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_LinearBlending();
	return 0;
}