/************************************************************************/
/*			ͨ������medianBlur()����ʵ����ֵ�˲�                        */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
	Mat srcImage = imread("1.tif");
	Mat dstImage;
	//������ֵ�˲�medianBlur����,����������Ϊ�˵Ĵ�С
	medianBlur(srcImage, dstImage, 3);
	imshow("ԭͼ",srcImage);
	imshow("Ч��ͼ����ֵ�˲�", dstImage);
	waitKey(0);
	return 0;
}