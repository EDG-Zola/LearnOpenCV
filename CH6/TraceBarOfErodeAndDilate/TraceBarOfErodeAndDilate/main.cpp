/************************************************************************/
/*		��Ϲ켣���Ĺ�����ʵ�ָ�ʴ�����Ͳ���			                */
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
Mat g_srcImage, g_dsrImage, Matelenment;
int g_nTrackbarName = 1; //��ʴ/���͵Ļ�������0��ʾ��ʴ��1��ʾ���ͣ�Ĭ��ѡ��Ϊ���Ͳ���
int g_ngetStructSize = 3; //�ں˾���Ĵ�С

/************************************************************************/
/*					�켣�������Ļص���������                            */
/************************************************************************/
static void on_TracebarNumberChange(int, void*); //�ı丯ʴ�����Ͳ���
static void on_TracebarStructSizeChange(int, void*); //�ı��ں˾���Ĵ�С
static void Process(); //����ʴ�����Ͳ���

/************************************************************************/
/*					    �������������                                  */
/************************************************************************/
int main(){
	//����̨������ɫΪ��ɫ
	system("color 5E");
	//1.�������ں���
	namedWindow("ԭͼ");
	namedWindow("Ч��ͼ����ʴ/����");

	//2.��ʾԭͼ����ԭͼ���Ƹ�Ŀ��ͼ��
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data){	cerr << "��ͼƬ1.jpg����"; return false;}
	imshow("ԭͼ", g_srcImage);
	g_dsrImage = g_srcImage.clone();
	
	//3.����ʹ���ں˾���
	Matelenment = getStructuringElement(MORPH_RECT, Size(g_ngetStructSize*2+1, g_ngetStructSize*2+1),
		Point(g_ngetStructSize, g_ngetStructSize));
	//4.�����켣��,����ں˾��󻬶�ֵΪ21
	createTrackbar("��ʴ/����", "Ч��ͼ����ʴ/����", &g_nTrackbarName, 1, on_TracebarNumberChange);
	on_TracebarNumberChange(g_nTrackbarName, 0);
	createTrackbar("�ں˾����С", "Ч��ͼ����ʴ/����", &g_ngetStructSize, 21, on_TracebarStructSizeChange);
	on_TracebarStructSizeChange(g_ngetStructSize, 0);

	//4.��ӡ����˵����Ϣ
	cout << "\t�뻬��ÿ�����ڵĻ������鿴��ʴ����Ч��" << endl;
	cout << "\t�˳������밴'q'��\n";
	while(char(waitKey(1)) !=  'q') {}
	return 0;

}

/************************************************************************/
/*                  static void Process()����                                    */
/************************************************************************/
static void Process(){
	//����ʹ���ں˾���
	Matelenment = getStructuringElement(MORPH_RECT, Size(g_ngetStructSize*2+1, g_ngetStructSize*2+1),
		Point(g_ngetStructSize, g_ngetStructSize));
	//���и�ʴ�����Ͳ���
	if(g_nTrackbarName == 1){
		dilate(g_srcImage, g_dsrImage, Matelenment);
	}
	else if(g_nTrackbarName == 0){
		erode(g_srcImage, g_dsrImage, Matelenment);
	}
	//��ʾ��ʴ�����Ͳ���
	imshow("Ч��ͼ����ʴ/����", g_dsrImage);
}

/************************************************************************/
/*                  �ı丯ʴ/���Ͳ����ص�����                                    */
/************************************************************************/
static void on_TracebarNumberChange(int, void*){
	//��ʴ������֮��Ч���Ѿ��л���ֻ��Ҫ����Process������ʹ�ı���Ч��������ʾ����
	Process();
}

/************************************************************************/
/*                 �ı��ں˾����С�ص�����                                    */
/************************************************************************/
static void on_TracebarStructSizeChange(int, void*){
	//��ʴ������֮��Ч���Ѿ��л���ֻ��Ҫ����Process������ʹ�ı���Ч��������ʾ����
	Process();
}