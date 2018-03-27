/************************************************************************/
/*                          ���ڻ��ƻ�����ͼ��                          */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;
/************************************************************************/
/*                    ȫ�ֱ���������                                    */
/************************************************************************/
const int g_nWindowWidth = 600;//���崰�ڴ�СΪ600
const string g_sWindowName1 = "����ͼ1"; //���ڱ�ǩ����ĺ�
const string g_sWindowName2 = "����ͼ2"; //���ڱ�ǩ����ĺ�

/************************************************************************/
/*       DrawEclipse()���������ڻ��Ʋ�ͬ�Ƕȣ���ͬ�ߴ����Բ           */
/************************************************************************/
void DrwaEclipse(Mat img, double angle){
	int thickness = 2;//�߿�Ϊ2
	int lineType = 8;//����Ϊ��ͨ����
	ellipse(img,
		Point(g_nWindowWidth/2, g_nWindowWidth/2),
		Size(g_nWindowWidth/4, g_nWindowWidth/16),
		angle, /*�Ƕ�*/
		0,
		360, /*�Ƕȷ�Χ*/
		Scalar(255, 129, 0),/*��ɫΪ����ɫ*/
		thickness,
		lineType);
}

/************************************************************************/
/*             DraweFilledCircle()����������ʵ��Բ�Ļ���                */
/************************************************************************/
void DraweFilledCirclee(Mat img, Point center){
	int thickness = -1;//�߿�Ϊ-1����˻��Ƶ�ԲΪʵ�ĵ�
	int lineType = 8;//����Ϊ��ͨ����
	circle(img,
		center,
		g_nWindowWidth/32,/*Բ�İ뾶*/
		Scalar(0, 0, 255),/*��ɫΪ��ɫ*/
		thickness,
		lineType);
}

/************************************************************************/
/*                DrawePolygon()���������ڰ����εĻ���                  */
/************************************************************************/
void DrawePolygon(Mat img){
	int lineType = 8;//����Ϊ��ͨ����
	//����һЩ��1�У�20�еĵ�
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(    g_nWindowWidth/4,   7*g_nWindowWidth/8 );
	rookPoints[0][1]  = Point(  3*g_nWindowWidth/4,   7*g_nWindowWidth/8 );
	rookPoints[0][2]  = Point(  3*g_nWindowWidth/4,  13*g_nWindowWidth/16 );
	rookPoints[0][3]  = Point( 11*g_nWindowWidth/16, 13*g_nWindowWidth/16 );
	rookPoints[0][4]  = Point( 19*g_nWindowWidth/32,  3*g_nWindowWidth/8 );
	rookPoints[0][5]  = Point(  3*g_nWindowWidth/4,   3*g_nWindowWidth/8 );
	rookPoints[0][6]  = Point(  3*g_nWindowWidth/4,     g_nWindowWidth/8 );
	rookPoints[0][7]  = Point( 26*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][8]  = Point( 26*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][9]  = Point( 22*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][10] = Point( 22*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][11] = Point( 18*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][12] = Point( 18*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][13] = Point( 14*g_nWindowWidth/40,    g_nWindowWidth/4 );
	rookPoints[0][14] = Point( 14*g_nWindowWidth/40,    g_nWindowWidth/8 );
	rookPoints[0][15] = Point(    g_nWindowWidth/4,     g_nWindowWidth/8 );
	rookPoints[0][16] = Point(    g_nWindowWidth/4,   3*g_nWindowWidth/8 );
	rookPoints[0][17] = Point( 13*g_nWindowWidth/32,  3*g_nWindowWidth/8 );
	rookPoints[0][18] = Point(  5*g_nWindowWidth/16, 13*g_nWindowWidth/16 );
	rookPoints[0][19] = Point(    g_nWindowWidth/4,  13*g_nWindowWidth/16 );
	
	const Point* ppt[1] = {rookPoints[0]};//����εĶ��㼯
	int npt[] = {20};//Ҫ���ƵĶ���ζ�����Ŀ
	fillPoly(img,
		ppt,
		npt,/*Բ�İ뾶*/
		1,/*Ҫ���ƵĶ���ζ�������*/
		Scalar(255, 255, 255),/*��ɫΪ��ɫ*/
		lineType);
}

/************************************************************************/
/*                     DrawLine()���������ڻ�����                       */
/************************************************************************/
void DrawLine(Mat img, Point start, Point end){
	int thickness = 2;//�߿�Ϊ2
	int lineType = 8;//����Ϊ��ͨ����
	line(img,
		start,/*�ߵ���ʼ��*/
		end,/*�ߵ���ֹ��*/
		Scalar(0, 0, 0),/*��ɫΪ��ɫ*/
		thickness,
		lineType);
}
int main(){
	//�����հ׵�Mat����
	Mat atomImage = Mat::zeros(g_nWindowWidth, g_nWindowWidth, CV_8UC3);
	Mat rookImage = Mat::zeros(g_nWindowWidth, g_nWindowWidth, CV_8UC3);

	/************************************************************************/
	/*                        1.����ԭ��ʾ��ͼ                              */
	/************************************************************************/
	//1.1�Ȼ���һЩ��Բ
	DrwaEclipse(atomImage, 90);
	DrwaEclipse(atomImage, 0);
	DrwaEclipse(atomImage, 45);
	DrwaEclipse(atomImage, -45);
	//1.2�ٻ���Բ��
	DraweFilledCirclee(atomImage, Point(g_nWindowWidth/2, g_nWindowWidth/2));

	/************************************************************************/
	/*                         2.�������ͼ��                               */
	/************************************************************************/
	//2.1�Ȼ���һ����Բ
	DrawePolygon(rookImage);
	//2.2�ڻ���һ������
	rectangle(rookImage,
	Point(0, 7*g_nWindowWidth/8),/*���ε����ϵ�����*/
	Point(g_nWindowWidth, g_nWindowWidth),/*���ε����µ�����*/
	Scalar(0, 255, 255),/*��ɫΪ��ɫ*/
	-1,/*ʵ��*/
	8 /*����Ϊ��ͨ����*/
	);
	//2.3����һЩ�߶�
	DrawLine(rookImage, Point(0, 15*g_nWindowWidth/16),               Point(g_nWindowWidth,    15*g_nWindowWidth/16));//һ�������ϵĺ���
	DrawLine(rookImage, Point(g_nWindowWidth/4,   7*g_nWindowWidth/8), Point(g_nWindowWidth/4,   g_nWindowWidth));//һ�������ϵ�����
	DrawLine(rookImage, Point(g_nWindowWidth/2,   7*g_nWindowWidth/8), Point(g_nWindowWidth/2,   g_nWindowWidth));//һ�������ϵ�����
	DrawLine(rookImage, Point(3*g_nWindowWidth/4, 7*g_nWindowWidth/8), Point(3*g_nWindowWidth/4, g_nWindowWidth));//һ�������ϵ�����

	/************************************************************************/
	/*                       3.��ʾ���Ƶ�ͼ��                               */
	/************************************************************************/
	imshow(g_sWindowName1, atomImage);
	moveWindow(g_sWindowName1, 0, 200);
	imshow(g_sWindowName2, rookImage);
	moveWindow(g_sWindowName2, g_nWindowWidth, 200);

	waitKey(0);
	return 0;
}