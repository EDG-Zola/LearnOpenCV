#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("ԭͼ����ʴ����", srcImage);

	Mat elment1 = getStructuringElement(MORPH_RECT, Size(15,15));//����ָ����״�ͳߴ�ĽṹԪ�أ��ں˾���
	Mat desImage;
	erode(srcImage, desImage, elment1);
	imshow("Ч��ͼ����ʴ������15,15��", desImage);

	Mat elment2 = getStructuringElement(MORPH_RECT, Size(20,20));//����ָ����״�ͳߴ�ĽṹԪ��
	erode(srcImage, desImage, elment2);
	imshow("Ч��ͼ����ʴ������20,20��", desImage);

	waitKey(0);
}