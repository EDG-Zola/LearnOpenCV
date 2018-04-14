/************************************************************************/
/*			�˳�������floodFill()������ʵ��Photoshop��ħ�����Ĺ���      */
/************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
using namespace std;

/************************************************************************/
/*							ȫ�ֱ���������                              */
/************************************************************************/
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;	//ԭͼ��Ŀ��ͼ���Ҷ�ͼ����Ĥͼ
int g_nFillMode = 1;	//��ˮ���ģʽ���շ�Χ������+�̶���Χ������+������Χ��
int g_nLowDifference = 20, g_nUpDifference = 20; //�������ֵ���������ֵ
int g_nConnecty = 4;	//floodFill������ʶ����8λ����ֵͨ��4 or 8����Ĭ��Ϊ4
bool g_bIsColor = true;	//�Ƿ�Ϊ��ɫ���ڵĲ���ֵ
bool g_bUseMask = false;	//�Ƿ�����Ĥ���ڵĲ���ֵ
int g_nNewMaskVal = 255;	//�µ����»��Ƶ���Ĥ����ֵ

/************************************************************************/
/*							onMouse()�ص�����							*/
/*							����������Ƿ���							*/
/************************************************************************/
static void onMouse(int event, int x, int y, int, void *){
	//������û�а��£��򷵻�
	if(event != EVENT_LBUTTONDOWN)
		return;
	/************************************************************************/
	/*						1.����floodFill����ǰ�Ĳ���׼��                 */
	/************************************************************************/
	Point seed = Point(x, y);	//���ӵ�����
	int lowDifference = g_nFillMode == 0 ?  0 : g_nLowDifference; //�շ�Χ����ˮ�������Ϊ0������Ϊȫ��g_nLowDifference
	int upDifference = g_nFillMode == 0 ?  0 : g_nUpDifference; //�շ�Χ����ˮ�������Ϊ0������Ϊȫ��g_nUpDifference
	//floodFill�����ı�ʶ��Ϊ��8λΪ��ͨ��ʽ��7-15λΪg_nNewMaskVal����8λ��ֵ��16-23λΪ���ģʽ
	//�����ģʽΪFLOODFILL_FIXED_RANGEʱ����ʾ���ǵ�ǰ��������������֮��Ĳ�ֵ����ʾ��������Χ��䣬����Ϊ�շ�Χ���
	int flags = g_nConnecty + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	//�������bgr��ɫ
	int b = (unsigned char)theRNG() & 255; //�������һ��0��255��ֵ
	int g = (unsigned char)theRNG() & 255; //�������һ��0��255��ֵ
	int r = (unsigned char)theRNG() & 255; //�������һ��0��255��ֵ
	Rect ccomp; //�����ػ��������С�߽��������
	//��Ϊ��ɫģʽʱ����Scalar(b, g, r)������ɫ����Ϊ�Ҷ�ģʽʱ����Scalar(r*0.299 + g*0.587 + b*0.144)���
	Scalar newValue = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.144);
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage; //Ŀ��ͼ�ĸ�ֵ
	int area; //��ʾ���ر��ػ�ĸ���

	/************************************************************************/
	/*						2.����floodFill����				                */
	/************************************************************************/
	//�Ƿ���ʾ��Ĥ����
	if(g_bUseMask){
		//��ֵ����threshold( InputArray src, OutputArray dst,double thresh, double maxval, int type )
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newValue, &ccomp, Scalar(lowDifference, lowDifference, lowDifference),
			Scalar(upDifference, upDifference, upDifference), flags);
		imshow("mask", g_maskImage);
	}
	else 
		area = floodFill(dst, seed, newValue, &ccomp, Scalar(lowDifference, lowDifference, lowDifference),
		Scalar(upDifference, upDifference, upDifference), flags);
	
	imshow("Ч��ͼ", dst);
	cout << area << "�����ر��ػ�\n";
}

/************************************************************************/
/*							��������˵��                                */
/************************************************************************/
void hlepText(){
	cout << "\t��ӭ������ˮ������~\n";
	cout << "\t�˳���������ѡȡ�ĵ�������ͼƬ����������ĵ㣬���ò�ͬ����ɫ��ע\n";
	cout << "\t��������˵����\n";
	cout << "\t\t���̰�����ESC�� -- �˳�����\n";
	cout << "\t\t���̰�����1�� -- �л���ɫͼ/�Ҷ�ͼģʽ\n";
	cout << "\t\t���̰�����2�� -- ��ʾ/���ش���\n";
	cout << "\t\t���̰�����3�� -- �ָ�ԭʼͼ��\n";
	cout << "\t\t���̰�����4�� -- ʹ�ÿշ�Χ������ˮ���\n";
	cout << "\t\t���̰�����5�� -- ʹ�ý��䡢�̶���Χ������ˮ���\n";
	cout << "\t\t���̰�����6�� -- ʹ�ý��䡢������Χ������ˮ���\n";
	cout << "\t\t���̰�����7�� -- floodFill�ı�ʶ����8λʹ��4��ͨ��ʽ\n";
	cout << "\t\t���̰�����8�� -- floodFill�ı�ʶ����8λʹ��8��ͨ��ʽ\n";
}

/************************************************************************/
/*						main()�������жϰ���                            */
/************************************************************************/
int main(){
	hlepText();
	//1.����ԭͼ
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data){
		cout << "����ͼƬ1.jpgʧ��" << endl;
		return false;
	}
	//2.Ŀ��ͼ,�Ҷ�ͼ����Ĥͼ������
	g_dstImage = g_srcImage.clone();//����ԭͼ��Ŀ��ͼ��Ҳ����g_srcImage.copyTo(g_dstImage)
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY); //�Ҷ�ͼ������
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//��Ĥͼ�Ĵ�������ͨ��8λ
	//3.�����������ڣ���������Ϊ�Զ�ƥ���С�����ɸı�
	namedWindow("Ч��ͼ",WINDOW_AUTOSIZE);
	//4.���������������������ص�������ν�ʺ�����
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
	setMouseCallback("Ч��ͼ", onMouse, 0);
	//4.ѭ����ѯ����
	while(1){
		//����ʾЧ��ͼ
		imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);
		//��ȡ�����ֵ
		int c = waitKey(1);
		//�ж��Ƿ���ESC��
		if ( (c & 255) == 27){
			cout << "�����˳�....";
				break;
		}
		switch( static_cast<char> (c) ){
			//����1�����£�Ч��ͼ�ڲ�ɫͼ/�Ҷ�ͼ֮���л�
			case '1':{
				if(g_bIsColor){
					cout << "����1�����£��л���ɫģʽ/��ɫģʽ����ǰ����Ϊ�л�����ɫģʽ��Ϊ����ɫģʽ��" << endl;
					cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
					g_maskImage = Scalar::all(0); //��mask����Ԫ������Ϊ0
					g_bIsColor = false;
				}
				else{
					cout << "����1�����£��л���ɫģʽ/��ɫģʽ����ǰ����Ϊ�л�����ɫģʽ��Ϊ����ɫģʽ��" << endl;
					g_srcImage.copyTo(g_dstImage);
					g_maskImage = Scalar::all(0); //��mask����Ԫ������Ϊ0
					g_bIsColor = true;
				}
				break;
			}
			//����2�����£���ʾ/������Ĥ����
			case '2':{
				if(g_bUseMask){
					destroyWindow("mask");
					g_bUseMask = false;
				}
				else{
					namedWindow("mask", 0);
					g_maskImage = Scalar::all(0);
					imshow("mask", g_maskImage);
					g_bUseMask = false;
				}
				break;
			 }
			//����3�����£��ָ�ԭʼͼ��
			case '3':{
				cout << "����3�����£��ָ�ԭʼͼ��" << endl;
				g_srcImage.copyTo(g_dstImage);
				cvtColor(g_dstImage, g_grayImage, COLOR_RGB2GRAY);
				g_maskImage = Scalar::all(0);
				break;
			}
			//����4�����£�ʹ�ÿշ�Χ����ˮ���
			case '4':{
				cout << "����4�����£�ʹ�ÿշ�Χ����ˮ���" << endl;
				g_nFillMode = 0;
				break;
			 }
			//����5�����£�ʹ�ý��䡢�̶���Χ��ˮ���
			case '5':{
				cout << "����5�����£�ʹ�ý��䡢�̶���Χ��ˮ���" << endl;
				g_nFillMode = 1;
				break;
			}
			//����6�����£�ʹ�ý��䡢������Χ��ˮ���
			case '6':{
				cout << "����6�����£�ʹ�ý��䡢������Χ��ˮ���" << endl;
				g_nFillMode = 2;
				break;
			}
			 //����7�����£�floodFill�ı�ʶ��ʹ��4��ͨ��ʽ
			case '7':{
				cout << "����7�����£�floodFill�ı�ʶ��ʹ��4��ͨ��ʽ" << endl;
				g_nConnecty = 4;
				break;
			 }
			 //����6�����£�floodFill�ı�ʶ��ʹ��8��ͨ��ʽ
			case '8':{
				cout << "����8�����£�floodFill�ı�ʶ��ʹ��8��ͨ��ʽ" << endl;
				g_nConnecty = 8;
				break;
			 }
		}
	}
	return 0;
}