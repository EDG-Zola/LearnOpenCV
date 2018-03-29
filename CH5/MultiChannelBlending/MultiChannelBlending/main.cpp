/************************************************************************/
/*                      ͼ��Ķ�ͨ���������ں�                          */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
/************************************************************************/
/*                            ��������                                  */
/************************************************************************/
bool MultiChannelBlending();

/************************************************************************/
/*                            ������                                    */
/************************************************************************/
int main(){
	system("color 5E");
	if(MultiChannelBlending()){
		cout << "���гɹ����õ�������Ҫ��ͼƬ" << endl;
	}
	waitKey(0);
	return 0;
}

bool MultiChannelBlending(){
	//0.������ر���
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channel;
	/************************************************************************/
	/*                            1.��ɫͨ������                            */
	/************************************************************************/
	Mat imageBlueChannel;
	Mat ROI_ImageBlueChannel;
	//1.1����ͼƬ
	srcImage = imread("dota_jugg.jpg");
	//�����ǻҶ�ͼ��������
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "��ȡͼƬdota_jugg.jpgʧ��" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "��ȡͼƬdota_logo.jpgʧ��" <<endl;
		return false;
	}
	//1.2 ����ͼƬ������ɫͨ����ֵ��imageBlueChannel
	split(srcImage, channel);
	imageBlueChannel = channel.at(0);//����һ����ɫͨ�������ã�����
	//1.3 ��ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	//logoImage�����Ƕ�ȡ�ĻҶ�ͼ����
	ROI_ImageBlueChannel = imageBlueChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageBlueChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageBlueChannel);
	//1.4 ��������ͨ���ϲ���һ����ͨ��
	merge(channel, srcImage);
	//1.5 ��ʾЧ��
	namedWindow("1.��ɫͨ������");
	imshow("1.��ɫͨ������",srcImage);

	/************************************************************************/
	/*                            2.��ɫͨ������                            */
	/************************************************************************/
	Mat imageGreenChannel;
	Mat ROI_ImageGreenChannel;
	//1.1����ͼƬ
	srcImage = imread("dota_jugg.jpg");
	//�����ǻҶ�ͼ��������
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "��ȡͼƬdota_jugg.jpgʧ��" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "��ȡͼƬdota_logo.jpgʧ��" <<endl;
		return false;
	}
	//1.2 ����ͼƬ������ɫͨ����ֵ��imageBlueChannel
	split(srcImage, channel);
	imageGreenChannel = channel.at(1);//����һ����ɫͨ�������ã�����
	//1.3 ��ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	//logoImage�����Ƕ�ȡ�ĻҶ�ͼ����
	ROI_ImageGreenChannel = imageGreenChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageGreenChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageGreenChannel);
	//1.4 ��������ͨ���ϲ���һ����ͨ��
	merge(channel, srcImage);
	//1.5 ��ʾЧ��
	namedWindow("2.��ɫͨ������");
	imshow("2.��ɫͨ������",srcImage);

	/************************************************************************/
	/*                            3.��ɫͨ������                            */
	/************************************************************************/
	Mat imageRedChannel;
	Mat ROI_ImageRedChannel;
	//1.1����ͼƬ
	srcImage = imread("dota_jugg.jpg");
	//�����ǻҶ�ͼ��������
	logoImage = imread("dota_logo.jpg", 0);
	if(!srcImage.data){
		cout << "��ȡͼƬdota_jugg.jpgʧ��" <<endl;
		return false;
	}
	if(!logoImage.data){
		cout << "��ȡͼƬdota_logo.jpgʧ��" <<endl;
		return false;
	}
	//1.2 ����ͼƬ������ɫͨ����ֵ��imageBlueChannel
	split(srcImage, channel);
	imageRedChannel = channel.at(2);//����һ����ɫͨ�������ã�����
	//1.3 ��ԭͼ����ɫͨ���ģ�500,250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	//logoImage�����Ƕ�ȡ�ĻҶ�ͼ����
	ROI_ImageRedChannel = imageRedChannel(Rect(500,250,logoImage.cols, logoImage.rows));
	addWeighted(ROI_ImageRedChannel, 1.0, logoImage, 0.5, 0.0, ROI_ImageRedChannel);
	//1.4 ��������ͨ���ϲ���һ����ͨ��
	merge(channel, srcImage);
	//1.5 ��ʾЧ��
	namedWindow("3.��ɫɫͨ������");
	imshow("3.��ɫͨ������",srcImage);
	return true;
}