/************************************************************************/
/*						�˳���ʵ���˸���Ҷ�任�Ĺ���                    */
/************************************************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*							������                                      */
/************************************************************************/
int main(){
	system("color 5E");
	//1. �ԻҶ�ģʽ��ȡͼƬ����ʾ
	Mat srcImage = imread("1.jpg", 0);
	if (!srcImage.data){
		cerr << "��ȡ1.jpgͼƬ����" <<endl;
		return false;
	}
	imshow("ͼƬ�ĻҶ�ͼƬ", srcImage);
	
	//2. �������ͼƬ����Ϊ��ѳߴ磬�߽���0���
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	//�߽���0���
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//3.Ϊ����Ҷ�任��ʵ�����鲿����洢�ռ�
	//��planes������Ϻϲ���һ����ͨ��������complexI
	Mat planes[] = {Mat_<float> (padded), Mat::zeros(padded.size(), CV_32F )};
	Mat complexI;
	merge(planes, 2, complexI);

	//4.�͵ؽ��и���Ҷ�任(��������Ϊ��ͬ��ͼƬ)
	dft(complexI, complexI);

	//5. ������ת��Ϊ��ֵ,��log(1+sqrt(Re(DFT(I)^2 + Im(DFT(I)^2)))
	split(complexI, planes);//����ͨ��complexI����ɼ�����ͨ������
	//planes[0] = Re(DTE(I)), planes[1] = Im(DTE(I))
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];
	//�����ߴ�����
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//����Ȼ����

	//6. ���к��طֲ�����ͼ����
	//���������к������У������Ƶ�ײü�
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//�������и���Ҷͼ������ޣ���ԭ��λ��ͼ�������
	int cy = magnitudeImage.rows/2;
	int cx = magnitudeImage.cols/2;
	Mat q0(magnitudeImage, (Rect(0, 0, cx, cy))); //ROI���������
	Mat q1(magnitudeImage, (Rect(cx, 0, cx, cy))); //ROI���������
	Mat q2(magnitudeImage, (Rect(0, cy, cx, cy))); //ROI���������
	Mat q3(magnitudeImage, (Rect(cx, cy, cx, cy))); //ROI���������
	//�������ޣ����Ϻ����½��н�����
	Mat temp;
	q0.copyTo(temp);
	q3.copyTo(q0);
	temp.copyTo(q3);
	//�������ޣ����Ϻ����½��н�����
	q1.copyTo(temp);
	q2.copyTo(q1);
	temp.copyTo(q2);

	//7. ��һ������0-1�ĸ���ֵ������任Ϊ���ӻ��ĸ�ʽ
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);

	//8. ��ʾЧ��ͼ
	imshow("Ƶ�׷�ֵ", magnitudeImage);
	cout << "�������гɹ�";
	waitKey(0);
	return 0;
}