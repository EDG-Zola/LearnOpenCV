/************************************************************************/
/*                     �˳�������ǰ����ͼƬ���ӷ���                     */
/************************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/************************************************************************/
/*                        ��������                                      */
/************************************************************************/
bool LinearBlending();
bool ROI_AddImage();
bool ROI_LinearBlending();

/************************************************************************/
/*                        ������                                        */
/************************************************************************/
int main(){
	system("color 5E");//�ı�cmd���еı�����ɫΪ��ɫ��cool��
	if ( ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
		cout << "���гɹ����õ�������Ҫ��ͼ��" << endl;
		waitKey(0);
		return 0;
}
/************************************************************************/
/*                     ʹ�ø���Ȥ����ROIʵ��ͼ�����                    */
/************************************************************************/
bool ROI_AddImage(){
	//1.��ȡͼƬ
	Mat srcImage = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage.data){
		cerr << " ��ȡdota_pa.jpgʧ�ܣ� " << endl;
		return false;
	}
	if (!logoImage.data){
		cerr << " ��ȡdota_logo.jpgʧ�ܣ� " << endl;
		return false;
	}
	//2.����һ��Mat���Ͳ���ȡһ����������
	//��ȡsrcImage������Rect��ǰ��������Ϊ���Ͻ����꣬����������Ϊ���εĳ���
	Mat ROI_Image = srcImage(Rect(0, 0, logoImage.cols, logoImage.rows));
	//3.������Ĥ�������ǻҶ�ͼ��
	Mat mask = imread("dota_logo.jpg", 0);
	//4.����0��Ĥ��logoImage��Ԫ�ظ��Ƶ�ROI
	logoImage.copyTo(ROI_Image, mask);
	//5.��ʾ���
	namedWindow("1.����ROIʵ��ͼ�����Ч��");//�����е���ͼƬ��С
	imshow("1.����ROIʵ��ͼ�����Ч��", srcImage);
	return true;
}

/************************************************************************/
/*                  ʹ��addWeight()�����������Ի�ϵ���                */
/************************************************************************/
bool LinearBlending(){
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
	namedWindow("2.����AddWeight()ʵ��ͼ�����Ч��");//�����е���ͼƬ��С
	imshow("2.����AddWeight()ʵ��ͼ�����Ч��", dstImage);
	return true;
}

/************************************************************************/
/*                  ʹ��addWeight()������ROI�ĸ���������Ի�ϵ���         */
/************************************************************************/
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

	//3.��ʾ���
	namedWindow("3.����AddWeight()ʵ��ͼ�����Ч��");
	imshow("3.����AddWeight()ʵ��ͼ�����Ч��", ROI_Image);
	return true;
}