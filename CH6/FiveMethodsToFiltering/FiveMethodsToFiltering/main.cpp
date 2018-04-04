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
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6; //�����˲��Ĺ켣������ֵ
int g_nMeanFilterValue = 10; //��ֵ�˲��Ĺ켣������ֵ
int g_nGaussianFilterValue = 6; //��˹�˲��Ĺ켣������ֵ
int g_nMedianFilterValue = 10; //��ֵ�˲��Ĺ켣������ֵ
int g_nBilateralFilterValue = 10; //˫���˲��Ĺ켣������ֵ

/************************************************************************/
/*					�켣�������Ļص���������                            */
/************************************************************************/
static void on_BoxFilter(int, void*);
static void on_MeanFilter(int, void*);
static void on_GaussianFilter(int, void*);
static void on_MedianFilter(int, void*);
static void on_BilateralFilter(int, void*);

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
	namedWindow("Ч��ͼ����ֵ�˲�");
	namedWindow("Ч��ͼ��˫���˲�");

	//2.��ʾԭͼ����ԭͼ���Ƹ�Ŀ��ͼ��
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data){	cerr << "��ͼƬ1.jpg����"; return false;}
	imshow("ԭͼ", g_srcImage);
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	//3.�����켣��,��󻬶�ֵΪ40
	createTrackbar("�ں�ֵ", "Ч��ͼ�������˲�", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ����ֵ�˲�", &g_nMeanFilterValue, 50, on_MeanFilter);
	on_MeanFilter(g_nMeanFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ����˹�˲�", &g_nGaussianFilterValue, 50, on_GaussianFilter);
	on_GaussianFilter(g_nGaussianFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ����ֵ�˲�", &g_nMedianFilterValue, 50, on_MedianFilter);
	on_MedianFilter(g_nMedianFilterValue, 0);
	createTrackbar("�ں�ֵ", "Ч��ͼ��˫���˲�", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);

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
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1), Point(-1,-1), true, 4);
	//��ʾ����
	imshow("Ч��ͼ�������˲�", g_dstImage1);
}

/************************************************************************/
/*                  ��ֵ�˲��ص�����                                    */
/************************************************************************/
static void on_MeanFilter(int, void*){
	//��ֵ�˲���������
	blur(g_srcImage, g_dstImage2, Size(g_nMeanFilterValue+1, g_nMeanFilterValue+1), Point(-1,-1), 4);
	//��ʾ����
	imshow("Ч��ͼ����ֵ�˲�", g_dstImage2);
}

/************************************************************************/
/*                  ��˹�˲��ص�����                                    */
/************************************************************************/
static void on_GaussianFilter(int, void*){
	//��˹�˲���������
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianFilterValue*2+1, g_nGaussianFilterValue*2+1), 0, 0);
	//��ʾ����
	imshow("Ч��ͼ����˹�˲�", g_dstImage3);
}

/************************************************************************/
/*                  ��ֵ�˲��ص�����                                    */
/************************************************************************/
static void on_MedianFilter(int, void*){
	//��˹�˲���������
	medianBlur(g_srcImage, g_dstImage4, g_nMedianFilterValue*2+1);
	//��ʾ����
	imshow("Ч��ͼ����ֵ�˲�", g_dstImage4);
}

/************************************************************************/
/*                  ˫���˲��ص�����                                    */
/************************************************************************/
static void on_BilateralFilter(int, void*){
	//��˹�˲���������
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
	//��ʾ����
	imshow("Ч��ͼ��˫���˲�", g_dstImage5);
}
