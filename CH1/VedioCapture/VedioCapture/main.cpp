/*������Ƶ��Ҫ��ͷ�ļ�*/

#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
	//������Ƶ1.avi
	VideoCapture capture("1.avi");
	//ѭ����ʾÿһ֡
	while(1){
		Mat frame;
		capture >> frame;
		imshow("��ȡ��Ƶ",frame);//ֻ��ʾÿһ֡��û������
		waitKey(1);//��ʱ30ms,��ʾ��һ֡,����1����������Լ��ٻ��������
	}
}