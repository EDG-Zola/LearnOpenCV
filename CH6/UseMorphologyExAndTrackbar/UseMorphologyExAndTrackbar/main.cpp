/************************************************************************/
/*    ʹ��morphologyEx(��������createTracebar���ۺ�չʾ��̬ѧ�˲�����   */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*						ȫ�ֱ���������                                  */
/************************************************************************/
Mat g_srcImage, g_dstImage, g_elment;
int g_nElementShape = MORPH_RECT;	//����Ĭ���ں˾�����״Ϊ����
int g_nMaxIterationNum = 10;	//���ĵ�������
int g_nOpenCloseNum = 0;	//�������㣬Ĭ��Ϊ0
int g_nErodeDilateNum = 0;	//��ʴ�������㣬Ĭ��Ϊ��ʴ
int g_nTopBlackNum = 0;		//��ñ��ñ���㣬Ĭ��Ϊ��ñ

/************************************************************************/
/*						�ص�����������                                  */
/************************************************************************/
static void on_OpenClose(int, void *);
static void on_ErodeDilate(int, void *);
static void on_TopBlack(int, void *);
static void showHelpText(void);

/************************************************************************/
/*						�������������	                               */
/************************************************************************/
int main(){
	showHelpText();
	//0.����ͼƬ
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "��ͼƬ1.jpgʧ��\n";
		return false;
	}
	//1.������������
	namedWindow("ԭͼ");
	namedWindow("��/������");
	namedWindow("��ʴ/��������");
	namedWindow("��ñ/��ñ����");
	
	//2.��ʾԭͼ������������
	imshow("ԭͼ", g_srcImage);
	createTrackbar("����ֵ", "��/������", &g_nOpenCloseNum, g_nMaxIterationNum*2+1, on_OpenClose);
	createTrackbar("����ֵ", "��ʴ/��������", &g_nErodeDilateNum, g_nMaxIterationNum*2+1, on_ErodeDilate);
	createTrackbar("����ֵ", "��ñ/��ñ����", &g_nTopBlackNum, g_nMaxIterationNum*2+1, on_TopBlack);

	//3.������ֵ
	g_nOpenCloseNum = 9;
	g_nErodeDilateNum = 9;
	g_nTopBlackNum = 2;

	//4.�ı��ں˾�����״
	while(1) {
		//4.1 ִ�лص�����
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlack(g_nTopBlackNum, 0);
		//4.2 ��ȡ����
		int c;
		c = waitKey(0);
		if((char)c == 'q' || (char)c == 27)
			break;
		switch(c){
			case 49:{g_nElementShape = MORPH_ELLIPSE; break;} //1��ASII��Ϊ49���ں���״Ϊ��ԲMORPH_ELLIPSE
			case 50:{g_nElementShape = MORPH_RECT; break;} //2��ASII��Ϊ50���ں���״Ϊ����MORPH_RECT
			case 51:{g_nElementShape = MORPH_CROSS; break;} //3��ASII��Ϊ51���ں���״Ϊʮ����MORPH_CROSS
			case 32:{g_nElementShape = (++g_nElementShape % 3); break;} //�ո��ASII��Ϊ32����״����Բ�����Ρ�ʮ������ѭ��
			default: break;
		}
	}
	return 0;
}

/************************************************************************/
/*						on_OpenClose()�ص�����                          */
/************************************************************************/
static void on_OpenClose(int, void *){
	//����ƫ����
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//�Զ����
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, g_elment);
	imshow("��/������", g_dstImage);
}

/************************************************************************/
/*						on_ErodeDilate()�ص�����                        */
/************************************************************************/
static void on_ErodeDilate(int, void *){
	//����ƫ����
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//�Զ����
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_DILATE, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_ERODE, g_elment);
	imshow("��ʴ/��������", g_dstImage);
}

/************************************************************************/
/*					void on_TopBlack()�ص�����                          */
/************************************************************************/
static void on_TopBlack(int, void *){
	//����ƫ����
	int offset = g_nTopBlackNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset: -offset;
	//�Զ����
	g_elment = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset));
	if(offset > 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, g_elment);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, g_elment);
	imshow("��ñ/��ñ����", g_dstImage);
}


static void showHelpText(void){
	//���һЩ������Ϣ
	system("color 5E");
	printf("\n\t������������۲�ͼ��Ч��\n\n");
	printf( "\n\t��������˵��: \n\n"
		"\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"
		"\t\t���̰�����1��- ʹ����Բ(Elliptic)�ṹԪ��\n"
		"\t\t���̰�����2��- ʹ�þ���(Rectangle )�ṹԪ��\n"
		"\t\t���̰�����3��- ʹ��ʮ����(Cross-shaped)�ṹԪ��\n"
		"\t\t���̰������ո�SPACE��- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n"	);
}