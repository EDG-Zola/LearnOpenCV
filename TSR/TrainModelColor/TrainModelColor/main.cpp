#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/ml/ml.hpp>  
#include <opencv2\opencv.hpp>    
#include "opencv2/core/core.hpp"    
#include "highgui.h"    
#include "opencv2/imgproc/imgproc.hpp"    
#include "opencv2/features2d/features2d.hpp"    
#include "opencv2/nonfree/nonfree.hpp"    
#include <iostream>  
#include <time.h>  
//#include "MomentFeature.h"  
#include <iostream>    
#include <fstream>    
#include <iterator>    
#include <vector>    
using namespace cv;  
using namespace std; 
//*****************************�޸����ݼ�ʱ��Ҫ����************//
#define trainnum 771
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//��ǩֵ,�ǶȺϲ��ˣ�
//***********771���������ݣ���11���ǩ*******************//
//*****************************�޸����ݼ�ʱ��Ҫ����************//
float label[trainnum] =   
{  
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//50��//
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//41��
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//50������
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//50������
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//50������
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//50������
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//50������
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//50������
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//50������
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//44������
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//50������
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//50������
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//50������
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//42������
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//34������
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,//36������
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,//18������
	11,11,11,11,11,11//6������
}; 

//*****************************�޸����ݼ�ʱ��Ҫ����************//
string labelname[500] = {"�������20km",//1,91������ 
	"�������30km",//2,//100������ 
	"�������50km",//3,//100������  
	"�������60km",//4,//100������ 
	"�������70km",//5,//94������ 
	"�������80km",//6,//100������ 
	"�������100km",//7,//92������ 
	"�������120km",//8,//34������  
	"�������50km",//9,//36������  
	"�������40km",//10,//18������ 
	"�������40km",//11,//6������ 
};

int WriteData(string fileName, cv::Mat& matData)    
{    
	int retVal = 0;    

	// ���ļ�    
	ofstream outFile(fileName.c_str(), ios_base::out);  //���½��򸲸Ƿ�ʽд��    
	if (!outFile.is_open())    
	{    
		cout << "���ļ�ʧ��" << endl;     
		retVal = -1;    
		return (retVal);    
	}    

	// �������Ƿ�Ϊ��    
	if (matData.empty())    
	{    
		cout << "����Ϊ��" << endl;     
		retVal = 1;    
		return (retVal);    
	}    
	// д������
	/******************************�����Ƕ�ֵ��������************************/
	for (int r = 0; r < matData.rows; r++)    
	{    
		for (int c = 0; c < matData.cols; c++)    
		{    
			if(c != 0)  
				outFile << ",";  
			float data = matData.at<float>(r,c);  //��ȡ���ݣ�at<type> - type �Ǿ���Ԫ�صľ������ݸ�ʽ   
			outFile << data  ;   //ÿ�������� tab ����    
		}    
		outFile << endl;  //����  
	}    

	return (retVal);    
}    

//�ߴ�����
void floatscale(float* f,int num, int scale)  
{  
	for(int i = 0; i < num; i++)  
	{  
		f[i]=f[i]*scale;  
	}  
}  
int main()  
{     
    //��ȡsample�е�����  
    char filename[200];  
    Mat sample;  
    Mat train;  
    Mat Hu_train;  
    //��ȡͼƬ���ݣ���ȡ����Ҳ�����  
    IplImage* ImageGray; //�Ҷ�ͼ 
    float feavec[48];  
    for(int i = 0; i < trainnum; i++)  
    {  
		//***************************����ͼƬ������ʽ1.jpg,2.jpg************************//
		
        sprintf(filename,"result/1 (%d).jpg",1+i); //*****************************�޸����ݼ�ʱ��Ҫ����************// 
        //*************��ͼƬ��Ϣֱ�ӷ���************  
        sample = imread(filename,1); //-1Ϊ���ı䣬1λ��ɫͼ 
        sample = sample.reshape(1,1);  //ת��Ϊһ�������� ������Ϊ��1,1����ʾתΪ��rows*cols*channels,1��,��0,1��Ϊ��ͨ���Ҷ�ͼ
        sample.convertTo(sample, CV_32F);  //��װ�洢��ʽΪCV_32F
        train.push_back(sample);  //�洢��Mat��train��һ���У����ڱ��(i,700)�ľ���
	}
	WriteData("feature_train.txt",train); 
	Mat labels(trainnum, 1, CV_32FC1, label);
	cout << train.cols << " " << train.rows << endl;
	cout << labels.cols << " " << labels.rows << endl; 


	//*********************SVMѵ������***********************  
    //׼����ʼѵ��  
    cout << "starting SVM...\n";
	CvSVM classifier;  
    CvSVMParams SVM_params;  
    SVM_params.kernel_type = CvSVM::LINEAR; //ʹ��RBF�������������  
    SVM_params.svm_type = CvSVM::C_SVC;  
    SVM_params.degree = 0;  
    SVM_params.gamma = 0.01;  
    SVM_params.term_crit =  cvTermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON);  
    SVM_params.C = 100;//��1�ĳ���100  
    SVM_params.coef0 = 0;  
    SVM_params.nu = 0;  
    SVM_params.p = 0.005;  
	classifier.train_auto(train,labels ,Mat(),Mat(),SVM_params,  
	            10,  
	            classifier.get_default_grid(CvSVM::C),  
	            classifier.get_default_grid(CvSVM::GAMMA),  
	            classifier.get_default_grid(CvSVM::P),  
	            classifier.get_default_grid(CvSVM::NU),  
	            classifier.get_default_grid(CvSVM::COEF),  
	            classifier.get_default_grid(CvSVM::DEGREE)  
	            );  
	classifier.save("model11Class771ColorSample.txt"); //�����������ѵ���������
	waitKey(0);
	return 0;
}