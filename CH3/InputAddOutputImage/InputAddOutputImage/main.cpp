/*ROI（region of interest），感兴趣区域。
机器视觉、图像处理中，从被处理的图像以方框、圆、椭圆、不规则多边形等方式勾勒出需要处理的区域，
称为感兴趣区域，ROI。
在Halcon、OpenCV、Matlab等机器视觉软件上常用到各种算子（Operator）和函数来求得感兴趣区域ROI，
并进行图像的下一步处理。
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

int main(){
	/*图像的载入*/
	Mat girl = imread("girl.jpg");
	namedWindow("【1】动漫图");//创建一个名为"【1】动漫图"的窗口
	imshow("【1】动漫图", girl);//显示名为"【1】动漫图"的窗口

	/*初级图像混合*/
	//载入图片
	Mat image = imread("dota.jpg", 199);
	Mat logo = imread("dota_logo.jpg");
	//载入后先显示
	namedWindow("原图画");
	imshow("原图画", image);

	namedWindow("Logo图");
	imshow("Logo图", logo);

	//定义一个Mat类型，用于存放图像ROI
	Mat imageROI = image(Range(350, 350+logo.rows), Range(800, 800+logo.cols));
	//将logo加到原图上
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	//显示原图+logo图
	namedWindow("Image+Logo");
	imshow("原图+Logo图", image);

	//将生成的原图+Logo图存储为图像文件
	imwrite("ImageAddLogo.jpg", image);
	waitKey(0);
	return 0;
}