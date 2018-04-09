/************************************************************************/
/*			ʹ��morphologyEx������̬ѧ�Ļ�������                        */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*			         		����ȫ�ֱ���                                */
/************************************************************************/
int g_nStructElement = 3;//�ں˾���Ĵ�С

/************************************************************************/
/*							����ԭ�͵�����                              */
/************************************************************************/
void helpText(void);//����������˵��

/************************************************************************/
/*							 �������������                             */
/************************************************************************/


int main(){
	helpText();
	Mat srcImage, dstImage, element;
	srcImage = imread("1.jpg");
	dstImage = srcImage.clone();
	element = getStructuringElement(MORPH_RECT, Size(g_nStructElement*2+1, g_nStructElement*2+1), Point(g_nStructElement, g_nStructElement));

	//1.������������
	namedWindow("ԭͼ");
	namedWindow("Ч��ͼ");

	//2.ͨ�������ַ�����ʾ��ʴ�����͡����ա���ò����ñ����̬ѧ�ݶ�Ч��
	int op;
	while (cin >> op){
		switch (op){
			case 0: {morphologyEx(srcImage, dstImage, MORPH_ERODE, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}		//��ʴ����
			case 1: {morphologyEx(srcImage, dstImage, MORPH_DILATE, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}	//���Ͳ���
			case 2: {morphologyEx(srcImage, dstImage, MORPH_OPEN, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}		//������
			case 3: {morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}		//�ղ���
			case 4: {morphologyEx(srcImage, dstImage, MORPH_GRADIENT, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}	//�ݶȲ���
			case 5: {morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}	//��ñ����
			case 6: {morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);imshow("ԭͼ",srcImage);imshow("Ч��ͼ",dstImage);break;}	//��ñ����
			default: {cout << "�����������������0~7" << endl; continue;}
		}
	}
	waitKey(0);
	return 0;
}

void helpText(void){
	system("color 5E");
	cout << "\t\t����˵��\t\t\t\n";
	cout << "\t\t����������0-7������Ӧ�Ĳ���\t\n";
	cout << "\t\t0:\t��ʴ����\t\n";
	cout << "\t\t1:\t���Ͳ���\t\n";
	cout << "\t\t2:\t������\t\n";
	cout << "\t\t3:\t�ղ���\t\n";
	cout << "\t\t4:\t�ݶȲ���\t\n";
	cout << "\t\t5:\t��ñ����\t\n";
	cout << "\t\t6:\t��ñ����\t\n";
}