/************************************************************************/
/*				�˳���ͨ��threshold()��������ͼ����ֵ����               */
/************************************************************************/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

/************************************************************************/
/*							ȫ�ֱ���������                              */
/************************************************************************/
const string NameWindow = "���򴰿�";
Mat g_srcImage, g_grayImage, g_dstImage;
int g_nTresholdValue = 100;
int g_nTresholdType = 3;	//��ֵ��ʽĬ��Ϊ ����ֵ��Ϊ0ģʽ

/************************************************************************/
/*							ȫ�ֺ���������                              */
/************************************************************************/
void helpText();//������ʾ����˵������
void on_Treshold(int, void*);

/************************************************************************/
/*							����������                                  */
/************************************************************************/
int main(){
	helpText();
	//1.����ͼ������ʾԭͼƬ
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "��ͼƬ1.jpgʧ��" << endl;
		return false;
	}
	imshow("ԭͼ", g_srcImage);
	//2.��һ��ͼƬ��Ϊ�Ҷ�ͼ
	cvtColor(g_srcImage, g_grayImage,COLOR_BGR2GRAY);
	//3.����������
	namedWindow(NameWindow);
	createTrackbar("��ֵ����ֵ", NameWindow, &g_nTresholdValue, 255, on_Treshold, 0);
	createTrackbar("��ֵģʽ", NameWindow, &g_nTresholdType, 4, on_Treshold, 0);
	//4.���ûص�����
	on_Treshold(0, 0);
	//5.��ѯ��ʽ��ⰴ��
	while(1){
		int c = waitKey(20);
		//�������ΪESC��q�����˳�����
		if(static_cast<char>(c) == 27 || static_cast<char>(c) == 'q')
			break;
	}
	return 0;
}

void on_Treshold(int, void*){
	threshold(g_grayImage, g_dstImage, g_nTresholdValue, 255, g_nTresholdType);
	imshow(NameWindow, g_dstImage);
}

void helpText(){
	system("color 5E");
	cout << "\t��ӭ������ֵ������ʾ����\n";
	cout << "\t����˵���������£�\n"
		 << "\t\t����ESC��q�� -- �˳�����\n"
		 << "\t\t������0 -- ��������ֵ\n"
		 << "\t\t������1 -- ����������ֵ\n"
		 << "\t\t������2 -- �ض���ֵ\n"
		 << "\t\t������3 -- ����ֵ��Ϊ0\n"
		 << "\t\t������4 -- ��ֵ��Ϊ0\n";
}



