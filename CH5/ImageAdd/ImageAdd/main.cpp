/************************************************************************/
/*                     此程序整合前三种图片叠加方法                     */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/************************************************************************/
/*                        函数声明                                      */
/************************************************************************/
bool LinearBlending();
bool ROI_AddImage();
bool ROI_LinearBlending();

/************************************************************************/
/*                        主函数                                        */
/************************************************************************/
int main(){
	system("color 5E");//改变cmd运行的背景颜色为紫色，cool！
	if ( ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
		cout << "运行成功，得到了你想要的图像！" << endl;
		waitKey(0);
		return 0;
}
/************************************************************************/
/*                     使用感兴趣区域ROI实现图像叠加                    */
/************************************************************************/
bool ROI_AddImage(){
	//1.读取图片
	Mat srcImage = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage.data){
		cerr << " 读取dota_pa.jpg失败！ " << endl;
		return false;
	}
	if (!logoImage.data){
		cerr << " 读取dota_logo.jpg失败！ " << endl;
		return false;
	}
	//2.定义一个Mat类型并截取一个矩形区域
	//截取srcImage的区域，Rect的前两个参数为左上角坐标，后两个参数为矩形的长宽
	Mat ROI_Image = srcImage(Rect(0, 0, logoImage.cols, logoImage.rows));
	//3.加载掩膜（必须是灰度图）
	Mat mask = imread("dota_logo.jpg", 0);
	//4.将非0掩膜的logoImage的元素复制到ROI
	logoImage.copyTo(ROI_Image, mask);
	//5.显示结果
	namedWindow("1.利用ROI实现图像叠加效果");//可自行调整图片大小
	imshow("1.利用ROI实现图像叠加效果", srcImage);
	return true;
}

/************************************************************************/
/*                  使用addWeight()函数进行线性混合叠加                */
/************************************************************************/
bool LinearBlending(){
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
	namedWindow("2.利用AddWeight()实现图像叠加效果");//可自行调整图片大小
	imshow("2.利用AddWeight()实现图像叠加效果", dstImage);
	return true;
}

/************************************************************************/
/*                  使用addWeight()函数和ROI的概念进行线性混合叠加         */
/************************************************************************/
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

	//3.显示结果
	namedWindow("3.利用AddWeight()实现图像叠加效果");
	imshow("3.利用AddWeight()实现图像叠加效果", ROI_Image);
	return true;
}