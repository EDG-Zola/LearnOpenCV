/************************************************************************/
/*		��Ϲ켣���Ĺ�����ʵ�ַ����˲�����ֵ�˲�����˹�˲�              */
/************************************************************************/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*					����ȫ�ֱ���                                       */
/************************************************************************/
Mat g_srcImage, g_dsrImage1, g_dsrImage2, g_dsrImage3;
int g_nBoxFilterValue = 3; //�����˲��Ĺ켣������ֵ
int g_nMeanFilterValue = 3; //��ֵ�˲��Ĺ켣������ֵ
int g_nGaussianFilterValue = 3; //��˹�˲��Ĺ켣������ֵ

/************************************************************************/
/*					�켣�������Ļص���������                            */
/************************************************************************/
static void on_BoxFilter(int, void*);
static void on_MeanFilter(int, void*);
static void on_GaussianFilter(int, void*);

/************************************************************************/
/*					    �������������                                  */
/************************************************************************/
int main(){
	//����̨������ɫΪ��ɫ
	system("color 5E");
	//1.�������ں���
	namedWindow("ԭͼ");
	namedWindow("Ч��ͼ�������˲�");
	namedWindow("Ч��ͼ����ֵ�˲�");
	namedWindow("Ч��ͼ����˹�˲�");
	
	//2.��ʾԭͼ����ԭͼ���Ƹ�Ŀ��ͼ��
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data){	cerr << "��ͼƬ1.jpg����"; return false;}
	imshow("ԭͼ", g_srcImage);
	g_dsrImage1 = g_srcImage.clone();
	g_dsrImage2 = g_srcImage.clone();
	g_dsrImage3 = g_srcImage.clone();

	//3.�����켣��,��󻬶�ֵΪ40
	createTrackbar("�ں�ֵ", "Ч��ͼ�������˲�", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ����ֵ�˲�", &g_nMeanFilterValue, 40, on_MeanFilter);
	on_MeanFilter(g_nMeanFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ����˹�˲�", &g_nGaussianFilterValue, 40, on_GaussianFilter);
	on_GaussianFilter(g_nGaussianFilterValue, 0);

	//4.��ӡ����˵����Ϣ
	cout << "\t�뻬��ÿ�����ڵĻ������鿴�˲�Ч��" << endl;
	cout << "\t�˳������밴'q'��\n";
	while(char(waitKey(1)) !=  'q') {}
	return 0;
	
}

/************************************************************************/
/*                  �����˲��ص�����                                    */
/************************************************************************/
static void on_BoxFilter(int, void*){
	//�����˲���������
	boxFilter(g_srcImage, g_dsrImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1), Point(-1,-1), true, 4);
	//��ʾ����
	imshow("Ч��ͼ�������˲�", g_dsrImage1);
}

/************************************************************************/
/*                  ��ֵ�˲��ص�����                                    */
/************************************************************************/
static void on_MeanFilter(int, void*){
	//��ֵ�˲���������
	boxFilter(g_srcImage, g_dsrImage2, -1, Size(g_nMeanFilterValue+1, g_nMeanFilterValue+1), Point(-1,-1), true, 4);
	//��ʾ����
	imshow("Ч��ͼ����ֵ�˲�", g_dsrImage2);
}

/************************************************************************/
/*                  ��˹�˲��ص�����                                    */
/************************************************************************/
static void on_GaussianFilter(int, void*){
	//��˹�˲���������
	boxFilter(g_srcImage, g_dsrImage3, -1, Size(g_nGaussianFilterValue+1, g_nGaussianFilterValue+1), Point(-1,-1), true, 4);
	//��ʾ����
	imshow("Ч��ͼ����˹�˲�", g_dsrImage3);
}