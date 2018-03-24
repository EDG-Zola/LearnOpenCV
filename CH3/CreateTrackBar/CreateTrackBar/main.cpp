#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/* ȫ�ֱ���������                                                                     */
/************************************************************************/
const string g_sWindoWName = "���Ի��ʵ��";
const int g_nMaxAlphaValue = 100;//Alpha�����ֵ
int g_nAlphaValueSlider;//��������Ӧ����
double g_dAlphaValue;
double g_dBetaValue;

//�����洢ͼ��ı���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;
/************************************************************************/
/* on_Trackbar��������Ӧ�������Ļص�����                                                                     */
/************************************************************************/
void on_Trackbar(int, void*){
	//�����ǰAlphaֵ��������ֵ�ı���
	//g_dAlphaValue =  (double) g_nAlphaValueSlider/g_nMaxAlphaValue;//ʹ��ǿ������ת��תΪdouble��
	//ʹ��C++���Ե�ǿ������ת��Ϊ�������
	g_dAlphaValue =  static_cast<double> (g_nAlphaValueSlider)/g_nMaxAlphaValue;
	//BetaֵΪ1 - Alphaֵ
	g_dBetaValue = 1.0 - g_dAlphaValue;
	//����Alpha��Betaֵ������ͼƬ�������Ի��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	
	
	//��ʾ���Ի�ϵ�Ч��ͼ
	imshow(g_sWindoWName, g_dstImage);
}
/************************************************************************/
/* ��������ڳ��򣺴������岢�ڻص�����on_Trackbar����ʾ                                                                     */
/************************************************************************/
int main(){
	//����ͼƬ����ͼƬ�ĳߴ������ͬ��
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");
	if(!g_srcImage1.data){
		cout << "��ȡ��һ��ͼƬ������ȷ��Ŀ¼���Ƿ���imreadָ��ָ����ͼƬ\n";
		return -1;
	}
	if(!g_srcImage2.data){
		cout << "��ȡ�ڶ���ͼƬ������ȷ��Ŀ¼���Ƿ���imreadָ��ָ����ͼƬ\n";
		return -1;
	}
	//���������ĳ�ʶλ������Ϊ70
	g_nAlphaValueSlider = 70;
	//��������,����Ϊ 1��WINDOW_AUTOSIZE�� 0��WINDOW_NORMAL
	namedWindow(g_sWindoWName, 1);
	//�ڴ�������ʱ������һ���������Ŀؼ�
	char TrackbarName[50];
	sprintf(TrackbarName, "͸��ֵ %d", g_nMaxAlphaValue);
	
	createTrackbar(TrackbarName, g_sWindoWName, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlider, 0);

	////��ȡ��ǰ��������λ�ú�����ʹ��
	//int currentAlphaValueSlider = getTrackbarPos(TrackbarName, g_sWindoWName);
	//cout << "��ǰ��������λ��Ϊ " << currentAlphaValueSlider << endl;

	waitKey(0);
	return 0;

}