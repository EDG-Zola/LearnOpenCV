/************************************************************************/
/*                     ʹ�ø���Ȥ����ROIʵ��ͼ�����                    */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage(){
	//1.��ȡͼƬ
	Mat srcImage = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage.data)
		cerr << " ��ȡdota_pa.jpgʧ�ܣ� " << endl;
	if (!logoImage.data)
		cerr << " ��ȡdota_logo.jpgʧ�ܣ� " << endl;
	//2.����һ��Mat���Ͳ���ȡһ����������
	//��ȡsrcImage������Rect��ǰ��������Ϊ���Ͻ����꣬����������Ϊ���εĳ���
	Mat ROI_Image = srcImage(Rect(0, 0, logoImage.cols, logoImage.rows));
	//3.������Ĥ�������ǻҶ�ͼ��
	Mat mask = imread("dota_logo.jpg", 0);
	//4.����0��Ĥ��logoImage��Ԫ�ظ��Ƶ�ROI
	logoImage.copyTo(ROI_Image, mask);
	//5.��ʾ���
	namedWindow("����ROIʵ��ͼ�����Ч��");//�����е���ͼƬ��С
	imshow("����ROIʵ��ͼ�����Ч��", srcImage);
	
	waitKey(0);
	return true;
}

int main(){
	bool flag = ROI_AddImage();
	return 0;
}