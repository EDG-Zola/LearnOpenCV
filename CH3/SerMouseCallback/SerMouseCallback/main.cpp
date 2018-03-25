#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
//��const�����滻#define�궨��
const string g_sWindowName = "���򴰿�";
/************************************************************************/
/*                        ȫ�ֺ���������                                */
/************************************************************************/
void on_MouseHandle(int event, int x, int y, int flags,void* param);
void DrawRectangle(cv::Mat &imag, cv::Rect box);
void ShowHelpText();
/************************************************************************/
/*                        ȫ�ֱ���������                                */
/************************************************************************/
Rect g_rectangle;
bool g_bDrawwingBox = false;//�Ƿ���л���
RNG g_rng(12345);
/************************************************************************/
/*                        main������                                   */
/************************************************************************/
int main(int argc, char** argv){
	//׼������
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC4), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);
	//�����������Ļص�����
	namedWindow(g_sWindowName);
	setMouseCallback(g_sWindowName, on_MouseHandle, (void*) &srcImage);
	//������ѭ���������л��Ƶı�ʶ��Ϊ��ʱ�����л���
	while(1){
		srcImage.copyTo(tempImage);//����ԭͼ����ʱ����
		if (g_bDrawwingBox)
			DrawRectangle(tempImage, g_rectangle);//�����л��Ƶı�ʶ��Ϊ��ʱ�����л���
		imshow(g_sWindowName, tempImage);
		if (waitKey(10) == 27)
			break;//����ESC���������˳�
	}
	return 0;
}

/************************************************************************/
/*  ���ص�����on_MouseHandle�����ݲ�ͬ������¼����в�ͬ�Ĳ���        */
/************************************************************************/
void on_MouseHandle(int event, int x, int y, int flags,void* param){
	Mat &image = *(cv::Mat*) param;
		switch(event){
			//����ƶ���Ϣ
			case EVENT_MOUSEMOVE:
			{
				//����Ƿ���л��Ʊ�ʶ��Ϊ��ʱ����¼���Ϳ�Rect������
				if(g_bDrawwingBox){
					g_rectangle.width = x - g_rectangle.x;
					g_rectangle.height = y - g_rectangle.y;
				}
				break;
			}
			//������������Ϣ
			case EVENT_LBUTTONDOWN:
				{
					g_bDrawwingBox = true;
					g_rectangle = Rect(x, y, 0 ,0);//��¼��ʼ��
				}
				break;
			//������̧��
			case EVENT_LBUTTONUP:
				{
					g_bDrawwingBox = false;
					//�Կ�͸�С��0ʱ���д���
					if (g_rectangle.width < 0)
					{
						g_rectangle.x += g_rectangle.width;
						g_rectangle.width *= -1;
					}
					if (g_rectangle.height < 0)
					{
						g_rectangle.y += g_rectangle.height;
						g_rectangle.height *= -1;
					}
					//���ú������л���
					DrawRectangle(image, g_rectangle);
				}
				break;
	}
}

/************************************************************************/
/*             DrawRectangle�������Զ���ľ��λ��ƺ���                  */
/************************************************************************/
void DrawRectangle(cv::Mat &img, cv::Rect box){
	rectangle(img, box.tl(), box.br(),
		Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ

}