/************************************************************************/
/*                      图像的多通道分离与融合                          */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
/************************************************************************/
/*                            函数声明                                  */
/************************************************************************/
bool MultiChannelBlending();

/************************************************************************/
/*                            主函数                                    */
/************************************************************************/
int main(){
	system("color 5E");
	if(MultiChannelBlending()){
		cout << "运行成功，得到了你想要的图片" << endl;
	}
	waitKey(0);
	return 0;
}

bool MultiChannelBlending(){
	//0.定义相关变量
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channel;
	/************************************************************************/
	/*                            1.蓝色通道部分                            */
	/************************************************************************/
	Mat imageBlueChannel;
	Mat ROI_ImageBlueChannel;
	//1.1读入图片
	srcImage = imread("dota_jugg.jpg");
	//必须是灰度图！！！！
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "读取图片dota_jugg.jpg失败" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "读取图片dota_logo.jpg失败" <<endl;
		return false;
	}
	//1.2 分离图片，将蓝色通道赋值给imageBlueChannel
	split(srcImage, channel);
	imageBlueChannel = channel.at(0);//返回一个蓝色通道的引用！！！
	//1.3 将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	//logoImage必须是读取的灰度图！！
	ROI_ImageBlueChannel = imageBlueChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageBlueChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageBlueChannel);
	//1.4 将三个单通道合并成一个三通道
	merge(channel, srcImage);
	//1.5 显示效果
	namedWindow("1.蓝色通道部分");
	imshow("1.蓝色通道部分",srcImage);

	/************************************************************************/
	/*                            2.绿色通道部分                            */
	/************************************************************************/
	Mat imageGreenChannel;
	Mat ROI_ImageGreenChannel;
	//1.1读入图片
	srcImage = imread("dota_jugg.jpg");
	//必须是灰度图！！！！
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "读取图片dota_jugg.jpg失败" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "读取图片dota_logo.jpg失败" <<endl;
		return false;
	}
	//1.2 分离图片，将蓝色通道赋值给imageBlueChannel
	split(srcImage, channel);
	imageGreenChannel = channel.at(1);//返回一个蓝色通道的引用！！！
	//1.3 将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	//logoImage必须是读取的灰度图！！
	ROI_ImageGreenChannel = imageGreenChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageGreenChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageGreenChannel);
	//1.4 将三个单通道合并成一个三通道
	merge(channel, srcImage);
	//1.5 显示效果
	namedWindow("2.绿色通道部分");
	imshow("2.绿色通道部分",srcImage);

	/************************************************************************/
	/*                            3.红色通道部分                            */
	/************************************************************************/
	Mat imageRedChannel;
	Mat ROI_ImageRedChannel;
	//1.1读入图片
	srcImage = imread("dota_jugg.jpg");
	//必须是灰度图！！！！
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "读取图片dota_jugg.jpg失败" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "读取图片dota_logo.jpg失败" <<endl;
		return false;
	}
	//1.2 分离图片，将蓝色通道赋值给imageBlueChannel
	split(srcImage, channel);
	imageRedChannel = channel.at(2);//返回一个蓝色通道的引用！！！
	//1.3 将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	//logoImage必须是读取的灰度图！！
	ROI_ImageRedChannel = imageRedChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageRedChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageRedChannel);
	//1.4 将三个单通道合并成一个三通道
	merge(channel, srcImage);
	//1.5 显示效果
	namedWindow("3.红色色通道部分");
	imshow("3.红色通道部分",srcImage);
	return true;
}