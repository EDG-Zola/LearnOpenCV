/************************************************************************/
/*                       ����ͼƬ�ĶԱȶȺ�����                         */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
/************************************************************************/
/*                      ȫ�ֱ�������                                    */
/************************************************************************/
int g_nContrastValues = 0;//�Աȶ�
int g_nBrightValues = 0;//����
Mat g_srcImage, g_dstImage;
const string g_sContrast = "�Աȶȣ� ";
const string g_sBright = "���ȣ� ";
const string g_sWindowName = "Ч��ͼ����";

/************************************************************************/
/*						��������                                       */
/************************************************************************/
static void on_ContrastAndBright(int, void* );

/************************************************************************/
/*						������                                          */
/************************************************************************/
int main(){
	system("color 5E");
	//1. ����ͼƬ
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "��ȡͼƬ1.jpgʧ��" << endl;
		return false;
	}
	//��Ŀ��ͼƬ����ΪԴͼƬ�Ĵ�С����
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//2. ���öԱȶȺ����ȵĳ�ʼֵ
	g_nContrastValues = 80;
	g_nBrightValues = 80;
	//3. ����Ч������(�˲��������ڴ���������ǰ�棡��1)
	namedWindow(g_sWindowName, 1);//ʹ��Ĭ��ֵ���Զ�ƥ���С��
	//4.����������
	createTrackbar(g_sContrast, g_sWindowName, &g_nContrastValues, 300,  on_ContrastAndBright);//�Աȶȵ����ֵΪ300
	createTrackbar(g_sBright, g_sWindowName, &g_nContrastValues, 200,  on_ContrastAndBright);//���ȵ����ֵΪ200
	//5. ���лص������ĳ�ʼ��
	on_ContrastAndBright(g_nContrastValues, 0);
	on_ContrastAndBright(g_nBrightValues, 0);
	cout << "�������гɹ�" <<endl;
	
	//6. ���¡�q�������˳�����
	while(char(waitKey(1)) != 'q'){
	}
	
	return 0;
}

/************************************************************************/
/*					�ı�ͼ��ԱȶȺ����ȵĻص�����                      */
/************************************************************************/
static void on_ContrastAndBright(int, void* ){
	int rowNumber = g_srcImage.rows;
	int colNumber = g_srcImage.cols;
	for (int i = 0; i < rowNumber; ++i){
		for (int j = 0; j < colNumber; ++j){
			g_dstImage.at<Vec3b>(i, j)[0] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[0] + g_nBrightValues);//��ɫͨ��
			g_dstImage.at<Vec3b>(i, j)[1] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[1] + g_nBrightValues);//��ɫͨ��
			g_dstImage.at<Vec3b>(i, j)[2] = saturate_cast<uchar>((g_nContrastValues * 0.01) * g_srcImage.at<Vec3b>(i, j)[2] + g_nBrightValues);//��ɫͨ��
		}
	}
	//��������
	namedWindow("ԭʼͼ��");
	imshow("ԭʼͼ��", g_srcImage);
	imshow(g_sWindowName, g_dstImage);
}