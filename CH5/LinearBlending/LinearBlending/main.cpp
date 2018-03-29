/************************************************************************/
/*                  ʹ��addWeight()�����������Ի�ϵ���                */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage(){
	//1.��ȡͼƬ
	Mat srcImage1 = imread("mogu.jpg");
	Mat srcImage2 = imread("rain.jpg");
	if (!srcImage1.data){
		cerr << " ��ȡmogu.jpgʧ�ܣ� " << endl;
		return false;
	}
	if (!srcImage2.data){
		cerr << " ��ȡrain.jpgʧ�ܣ� " << endl;
		return false;
	}
	Mat dstImage;
	double alpha = 0.3;
	double beta = 1 - alpha;

	//2.addWeight()�������л��Ȩ�ص���
	addWeighted(srcImage1, alpha, srcImage2, beta, 0.0, dstImage);

	//3.��ʾ���
	namedWindow("����AddWeight()ʵ��ͼ�����Ч��", 0);//�����е���ͼƬ��С
	imshow("����AddWeight()ʵ��ͼ�����Ч��", dstImage);

	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_AddImage();
	return 0;
}