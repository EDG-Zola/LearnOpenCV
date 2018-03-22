#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("ԭͼ��canny��Ե���", srcImage);
	Mat dstImage, grayImage, edgeImage;
	//������srcImageͬ���ͺʹ�С�ľ���dst
	dstImage.create(srcImage.size(), srcImage.type());
	
	//��srcת��Ϊ�Ҷ�ͼ
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	//�þ�ֵ�˲�����
	blur(grayImage, edgeImage, Size(3, 3));
	//����Canny����
	Canny(edgeImage, edgeImage, 3, 9, 3);
	//��ʾЧ��ͼ
	imshow("Ч��ͼ��canny��Ե���", edgeImage);
	
	waitKey(0);
}