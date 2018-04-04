/************************************************************************/
/*              ���÷����˲�����ʵ�־�ֵ�˲�                            */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;
int main(){
	Mat srcImage = imread("1.jpg");
	Mat dstImage1;
	Mat dstImage2;
	namedWindow("��ֵ�˲���ԭͼ");
	namedWindow("��ֵ�˲�5x5��Ч��ͼ");
	namedWindow("��ֵ�˲�10x10��Ч��ͼ");
	imshow("��ֵ�˲���ԭͼ", srcImage);
	//���÷����˲�������ʹ��6������normalize = true�� �����й�һ������ʵ�־�ֵ�˲�
	//�˲����˵Ĵ�СΪ5x5
	boxFilter(srcImage, dstImage1, srcImage.depth(), Size(5,5), Point(-1,-1), true, 4);
	boxFilter(srcImage, dstImage2, srcImage.depth(), Size(10,10), Point(-1,-1), true, 4);
	imshow("��ֵ�˲�5x5��Ч��ͼ", dstImage1);
	imshow("��ֵ�˲�10x10��Ч��ͼ", dstImage2);
	waitKey(0);
	return 0;
}