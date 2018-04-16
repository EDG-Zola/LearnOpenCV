/************************************************************************/
/*		�˳���������ʾͼƬ�ߴ�任���õ�resize()��pyrUp()��pyrDown����  */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*						ȫ�ֱ���������                                  */
/************************************************************************/
const string NameWindow = "���򴰿�";
Mat g_srcImage, g_dstImage, g_tempImage;

/************************************************************************/
/*						helpText()������˵������                        */
/************************************************************************/
void helpText(){
	system("color 5E");
	cout << "\t��ӭ����ͼ���������Resize��ʾ����\n";
	cout << "\t����˵����\n";
	cout << "\t\t����ESC��q�� -- �˳�����\n"
		 << "\t\t����1�� -- ���ڡ�resize����������ͼƬ�Ŵ�\n"
		 << "\t\t����2�� -- ���ڡ�resize����������ͼƬ��С\n"
		 << "\t\t����3�� -- ���ڡ�pyrUp����������ͼƬ�Ŵ�\n"
		 << "\t\t����4�� -- ���ڡ�pyrDown����������ͼƬ��С\n";
}

/************************************************************************/
/*					main()������ͨ��������ʾЧ��                        */
/************************************************************************/
int main(){
	helpText();
	//1.����ԴͼƬ����ʾԭͼ
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "��ͼƬ1.jpgʧ��\n";
		return false;
	}
	imshow(NameWindow, g_srcImage);
	//2.������ֵ
	g_tempImage = g_srcImage;
	g_dstImage = g_tempImage;
	//��ѯ��ʽ��ⰴ��
	int c;
	while(1){
		c = waitKey(9);//��ȡ������ֵ��������ת��Ϊchar���ͣ�waitKey(1)Ϊת��Ϊ����ֵ
		switch(c){
			//����ESC�������˳�����
			case 27:{
				return 0;
				break;
			}
			//����q�������˳�����
			case 'q':{
				return 0;
				break;
			}
			//����1�������ڡ�resize����������ͼƬ�Ŵ�
			case '1':{
				resize(g_tempImage, g_dstImage, Size(g_tempImage.cols*2, g_tempImage.rows*2));
				cout << "������1�������£����ڡ�resize����������ͼƬ�Ŵ�\n";
				break;
		    }
			 //����2�������ڡ�resize����������ͼƬ��С
			case '2':{
				resize(g_tempImage, g_dstImage, Size(g_tempImage.cols/2, g_tempImage.rows/2), 0.0, 0.0, INTER_CUBIC);
				cout << "������2�������£����ڡ�resize����������ͼƬ��С\n";
				break;
			 }
			 //����3�������ڡ�pyrUp����������ͼƬ�Ŵ�
			case '3':{
				pyrUp(g_tempImage, g_dstImage, Size(g_tempImage.cols*2, g_tempImage.rows*2));
				cout << "������3�������£����ڡ�pyrUp����������ͼƬ�Ŵ�\n";
				break;
			 }
			 //����4�������ڡ�pyrDown����������ͼƬ��С
			case '4':{
				pyrDown(g_tempImage, g_dstImage, Size(g_tempImage.cols/2, g_tempImage.rows/2));
				cout << "������4�������£����ڡ�pyrDown����������ͼƬ��С\n";
				break;
			 }
		}
		imshow(NameWindow,g_dstImage);
		g_tempImage = g_dstImage;
	}
	return 0;
}