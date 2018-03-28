/************************************************************************/
/*                     使用感兴趣区域ROI实现图像叠加                    */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage(){
	//1.读取图片
	Mat srcImage = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage.data)
		cerr << " 读取dota_pa.jpg失败！ " << endl;
	if (!logoImage.data)
		cerr << " 读取dota_logo.jpg失败！ " << endl;
	//2.定义一个Mat类型并截取一个矩形区域
	//截取srcImage的区域，Rect的前两个参数为左上角坐标，后两个参数为矩形的长宽
	Mat ROI_Image = srcImage(Rect(0, 0, logoImage.cols, logoImage.rows));
	//3.加载掩膜（必须是灰度图）
	Mat mask = imread("dota_logo.jpg", 0);
	//4.将非0掩膜的logoImage的元素复制到ROI
	logoImage.copyTo(ROI_Image, mask);
	//5.显示结果
	namedWindow("利用ROI实现图像叠加效果");//可自行调整图片大小
	imshow("利用ROI实现图像叠加效果", srcImage);
	
	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_AddImage();
	return 0;
}