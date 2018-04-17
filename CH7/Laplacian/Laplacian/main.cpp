/************************************************************************/
/*				�˳�����ʾ��ʹ��Laplacian()������Ч��                   */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(){
	Mat srcImage, dst, gray, abs_dst;
	Mat contrastImage;
	//1.����ԭͼ����ʾ
	srcImage = imread("1.jpg");
	if(!srcImage.data){
		cout << "��ͼƬ1.jpgʧ��" << endl;
		return false;
	}
	imshow("ԭͼ", srcImage);
	//2.�ø�˹�˲�����ԭͼ����
	GaussianBlur(srcImage, srcImage, Size(3,3), 0, 0, BORDER_DEFAULT);
	//3.ת��Ϊ�Ҷ�ͼ
	cvtColor(srcImage, gray, COLOR_BGR2GRAY);
	//4.����������˹�任,ksize = 3
	Laplacian(gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//5.�������ֵ����������ת��Ϊ8λ
	convertScaleAbs(dst, abs_dst, 1, 0);
	//6.��ʾЧ��
	imshow("Laplacian����Ч��", abs_dst);
	//addWeighted(srcImage, 1, abs_dst, -1, 0, contrastImage);
	//imshow("��ǿ�Ա�Ч��ͼ", contrastImage);
	waitKey(0);
	return 0;
}

