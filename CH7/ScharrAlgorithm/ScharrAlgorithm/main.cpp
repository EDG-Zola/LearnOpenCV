/************************************************************************/
/*		�˳�����ʾ������Scharr���ӽ���X�����Y����X��Y�����Ч��       */
/************************************************************************/
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	//����Sobel����Ҫ�����Mat����
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	//1.����ԭͼ����ʾ
	Mat srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "��ͼƬ1.jpgʧ��" << endl;
		return false;
	}
	imshow("ԭͼ", srcImage);
	//2.����Scharr()��������X��������Ĭ��û��Ӧ������
	// calculates absolute values, and converts the result to 8-bit.
	Scharr(srcImage, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("X������", abs_grad_x);
	//3.����Scharr()��������Y��������Ĭ��û��Ӧ������
	// calculates absolute values, and converts the result to 8-bit.
	Scharr(srcImage, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Y������", abs_grad_y);
	//4.����X��Y����
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("X��Y����ϲ����ݶ�Scharr", dst);
	waitKey(0);
	return 0;
}