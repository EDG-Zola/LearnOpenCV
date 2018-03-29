/************************************************************************/
/*                  ʹ��addWeight()������ROI�ĸ���������Ի�ϵ���         */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_LinearBlending(){
	//1.��ȡͼƬ
	Mat srcImage1 = imread("dota_pa.jpg");
	Mat srcImage2 = imread("dota_logo.jpg");
	if (!srcImage1.data){
		cerr << " ��ȡdota_logo.jpgʧ�ܣ� " << endl;
		return false;
	}
	if (!srcImage2.data){
		cerr << " ��ȡdota_pa.jpgʧ�ܣ� " << endl;
		return false;
	}
	Mat dstImage;
	double alpha = 0.8;
	double beta = 1 - alpha;
	//2.��ȡdota_logo�ľ���������ΪROI_Image
	Mat ROI_Image = srcImage1(Rect(200, 250, srcImage2.cols, srcImage2.rows));
	
	//3.addWeight()�������л��Ȩ�ص���
	addWeighted(ROI_Image, alpha, srcImage2, beta, 0.0, ROI_Image);

	//4.��ʾ���
	namedWindow("����AddWeight()ʵ��ͼ�����Ч��");
	imshow("����AddWeight()ʵ��ͼ�����Ч��", ROI_Image);

	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_LinearBlending();
	return 0;
}