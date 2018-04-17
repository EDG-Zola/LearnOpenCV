/************************************************************************/
/*						������������ʾCanny��Ե���                     */
/************************************************************************/
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	//1.����ԭͼƬ
	Mat srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "��ԭͼƬ1.jpgʧ��" << endl;
		return 0;
	}
	imshow("ԭͼ",srcImage);
	Mat edgeImage = srcImage.clone();
	//2.Canny���
	//void Canny( InputArray image, OutputArray edges,
	//double threshold1, double threshold2,
	//	int apertureSize = 3, bool L2gradient = false );
	//threshold1:��һ���ͺ���ֵ
	//threshold2:�ڶ����ͺ���ֵ���Ƽ��ߵ���ֵ����2:1��3:1֮��
	//apertureSize:Sobel���ӵĿ׾���С
	//����һ��ֱ�ӵ���Canny����
	Canny(srcImage, edgeImage, 150, 100, 3);
	imshow("Ч��ͼ1",edgeImage);
	//��������ת��Ϊ�Ҷ�ͼ�����룬��Canny�����õ��ı�Ե�������룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ��Եͼ
	Mat dst, gray, edge;
	//2.1 ������srcImage��ͬ��С�����͵�dst
	dst.create(srcImage.size(), srcImage.type());
	//2.2 ת��Ϊ�Ҷ�ͼ
	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
	//2.3����:3X3���ں�
	blur(gray, edge,Size(3,3));
	//2.4����Canny
	Canny(edge, edge, 3, 9, 3);
	//2.5��dst����Ϊȫ0
	dst = Scalar::all(0);
	//2.6 ���õ��ı�Ե�������룬����ԭͼ��Ч��ͼ��
	srcImage.copyTo(dst, edge);
	//2.7��ʾ��ɫCannyЧ��
	imshow("��ɫCanny",dst);
	waitKey(0);
	return 0;
}