/************************************************************************/
/*			ͨ������bilateralBlur()����ʵ��˫���˲�                        */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
	Mat srcImage = imread("1.png");
	Mat dstImage;
	//������ֵ�˲�bilateralBlur(),����������Ϊ�˵Ĵ�С
	bilateralFilter(srcImage, dstImage, 25, 25*2, 25/2);
	imshow("ԭͼ",srcImage);
	imshow("Ч��ͼ��˫���˲�", dstImage);
	imwrite("out.jpg", dstImage);
	waitKey(0);
	return 0;
}