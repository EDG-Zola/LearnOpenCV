/************************************************************************/
/*                     ����ͼ�������ص����ַ���                         */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/************************************************************************/
/*                           ��������                                   */
/************************************************************************/
void colorReducePointer(Mat &inputImage, Mat &outputImage, int div);//ʹ��ָ�����
void colorReduceIteration(Mat &inputImage, Mat &outputImage, int div);//ʹ�õ���������
void colorReduceDynamicAddr(Mat &inputImage, Mat &outputImage, int div);//ʹ�ö�̬��ַ����
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("ԭʼͼ��", srcImage);

	Mat dstImage;
	//ʹЧ��ͼ�Ĵ�С��������ԭͼ����ͬ
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
	/************************************************************************/
	/*               ����һ����ָ��������أ�ע��Խ�����⣩                 */
	/************************************************************************/
	//��¼��ʼʱ��
	double time0 = static_cast<double> (getTickCount());
	colorReducePointer(srcImage, dstImage, 32);
	//��¼��ֹʱ��
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "ָ����ʷ�������ʱ��Ϊ�� " << time0 << "��" << endl;
	imshow("ָ�����Ч��ͼ", dstImage);

	/************************************************************************/
	/*               ���������õ������������أ��ȫ��                     */
	/************************************************************************/
	//��¼��ʼʱ��
	time0 = static_cast<double> (getTickCount());
	colorReduceIteration(srcImage, dstImage, 32);
	//��¼��ֹʱ��
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "���������ʷ�������ʱ��Ϊ�� " << time0 << "��" << endl;
	imshow("����������Ч��ͼ", dstImage);

	/************************************************************************/
	/*         ���������ö�̬��ַ���at�����������أ������ˣ�             */
	/************************************************************************/
	//��¼��ʼʱ��
	time0 = static_cast<double> (getTickCount());
	colorReduceDynamicAddr(srcImage, dstImage, 32);
	//��¼��ֹʱ��
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "��ָ̬����ʷ�������ʱ��Ϊ�� " << time0 << "��" << endl;
	imshow("��̬��ַ����Ч��ͼ", dstImage);

	waitKey(0);
	return 0;
}

/************************************************************************/
/*               ����һ����ָ��������أ�ע��Խ�����⣩                 */
/************************************************************************/
void colorReducePointer(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();//������ͼ��ĸ�����ֵ�����ͼ��
	int rowNumber = outputImage.rows;//ͼ�������
	int colNumber = outputImage.cols * outputImage.channels();//ͼ�������*ͨ����
	for (int i = 0; i < rowNumber; ++i){
		uchar* data = outputImage.ptr<uchar>(i);//ptr��һ��ģ�庯��������ÿһ�е��׵�ַ����ÿһ�е��׵�ַ��ֵ��data
		for (int j = 0; j < colNumber; ++j){
			data[j] = data[j] / div *div + div/2;//��ÿ��������ɫ�ռ併ά
		}
	}
}

/************************************************************************/
/*               ���������õ������������أ��ȫ��                     */
/************************************************************************/
void colorReduceIteration(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();//ָ��ͼ��ĵ�һ������
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//ָ��ͼ�����������
	for (; it != itend; ++it){
		(*it)[0] = (*it)[0] / div *div + div/2;//�Ե�һ�����صĵ�һ��ͨ��Ԫ�ؽ�����ɫ�ռ併ά
		(*it)[1] = (*it)[1] / div *div + div/2;//�Եڶ������صĵڶ���ͨ��Ԫ�ؽ�����ɫ�ռ併ά
		(*it)[2] = (*it)[2] / div *div + div/2;//�Ե��������صĵ�����ͨ��Ԫ�ؽ�����ɫ�ռ併ά
	}
}

/************************************************************************/
/*         ���������ö�̬��ַ���at�����������أ������ˣ�             */
/************************************************************************/
void colorReduceDynamicAddr(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	for (int i = 0; i < rowNumber; ++i){
		for (int j = 0; j < colNumber; ++j){
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div/2;//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div/2;//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div/2;//��ɫͨ��
		}
	}
}