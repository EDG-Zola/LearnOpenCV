/************************************************************************/
/*					ʹ��erode()�����������Ͳ���                        */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*							ȫ�ֱ�������                                */
/************************************************************************/
int g_ngetStructElement = 1; //�ں˾���Ĵ�С

/************************************************************************/
/*							��������ڳ���                              */
/************************************************************************/
int main(){
	system("color 5E");
	//1.����Mat�༰��ȡͼƬ
	Mat srcImage, dstImage, element;
	srcImage = imread("2.jpg");

	//2.�����������ڼ���ʾԭͼ
	namedWindow("ԭͼ");
	namedWindow("��ʴ����");
	imshow("ԭͼ", srcImage);

	//3.ʹ��getStructuringElement����һ���ں˾���
	element = getStructuringElement(MORPH_RECT, Size(g_ngetStructElement*2+1, g_ngetStructElement*2+1),
		Point(g_ngetStructElement, g_ngetStructElement));

	//4.ʹ��erode������ʾЧ��
	erode(srcImage, dstImage, element);
	imshow("��ʴ����", dstImage);

	//5,�洢Ч��ͼ
	imwrite("erode.jpg", dstImage);
	waitKey(0);
	return 0;
}