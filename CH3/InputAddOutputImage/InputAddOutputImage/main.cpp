/*ROI��region of interest��������Ȥ����
�����Ӿ���ͼ�����У��ӱ������ͼ���Է���Բ����Բ�����������εȷ�ʽ���ճ���Ҫ���������
��Ϊ����Ȥ����ROI��
��Halcon��OpenCV��Matlab�Ȼ����Ӿ�����ϳ��õ��������ӣ�Operator���ͺ�������ø���Ȥ����ROI��
������ͼ�����һ������
*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

int main(){
	/*ͼ�������*/
	Mat girl = imread("girl.jpg");
	namedWindow("��1������ͼ");//����һ����Ϊ"��1������ͼ"�Ĵ���
	imshow("��1������ͼ", girl);//��ʾ��Ϊ"��1������ͼ"�Ĵ���

	/*����ͼ����*/
	//����ͼƬ
	Mat image = imread("dota.jpg", 199);
	Mat logo = imread("dota_logo.jpg");
	//���������ʾ
	namedWindow("ԭͼ��");
	imshow("ԭͼ��", image);

	namedWindow("Logoͼ");
	imshow("Logoͼ", logo);

	//����һ��Mat���ͣ����ڴ��ͼ��ROI
	Mat imageROI = image(Range(350, 350+logo.rows), Range(800, 800+logo.cols));
	//��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	//��ʾԭͼ+logoͼ
	namedWindow("Image+Logo");
	imshow("ԭͼ+Logoͼ", image);

	//�����ɵ�ԭͼ+Logoͼ�洢Ϊͼ���ļ�
	imwrite("ImageAddLogo.jpg", image);
	waitKey(0);
	return 0;
}