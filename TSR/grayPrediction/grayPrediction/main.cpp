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
#define trainnum 657	//ѵ������Ŀ
#define testnum  120	//���Լ���Ŀ
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//��ǩֵ,�ǶȺϲ��ˣ�
//***********771��ѵ���������ݣ�120���������ݣ���11���ǩ*******************//
//*****************************�޸����ݼ�ʱ��Ҫ����************//
float label[trainnum] =   
{  
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//48��//
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//60������
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//60������
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//35������
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//60������
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//60������
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//56������
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//60������
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//30������
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//30������
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//30������
	6,6,6,6,6,6,6,6,6,6,6,6,6,//13������
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//18������
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,//38������
	1,1,1,1,1,1,1,1,//8������
	2,2,2,2,//4������
	3,3,//2������
	4,4,4,4,//4������
	5,5,5,//3������
	6,6,//2������
	7,7,7,7,7,7,//6������
	8,8,8,8,8,//5������
	10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,//17������
	11,11,11,11,11,11,11,11 //8������
}; 


float testlabel[testnum] = 
{
	1,1,//2������
	3,3,3,3,//4������
	2,//1
	4,4,4,4,4,//5
	6,6,//2
	8,8,//2
	6,//1
	8,//1
	6,//1
	8,8,8,//3
	5,5,5,5,5,5,//6
	2,2,2,2,2,2,//6
	7,7,7,7,7,7,//6
	9,9,9,9,9,9,//6
	10,10,10,//3
	11,11,//2
	2,2,2,2,2,2,2,2,2,2,//10
	3,3,3,3,3,3,3,3,3,3,//10
	4,4,4,4,4,//5
	5,5,5,5,5,5,5,5,5,5,//10
	6,6,6,6,6,//5
	7,7,7,7,7,//5
	8,8,8,8,8,//5
	9,9,9,9,9,//5
	10,10,10,10,10,//5
	11,11,11,11,11,//5
	5,5//2
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
	CvSVM classifier;  
    classifier.load("model11Class657Sample.txt");  
	//*********************************************1.����ѵ������****************************//
	vector<Mat> traindata; //����ѵ������  
    Mat trainmmat;  
    Mat train;  
    for(int i = 0; i < trainnum; i++)  
    {  
		//***************************����ͼƬ������ʽ1.jpg,2.jpg************************//
		
        sprintf(filename,"traindata/1 (%d).jpg",i+1);  //*****************************�޸����ݼ�ʱ��Ҫ����************//
        //*************ֱ�Ӱ�ͼƬ��Ϣ����***********  
        train = imread(filename,-1);  //��ȡ��ɫͼ
        //resize(test,test,Size(10,70));  //����������ת��Ϊ10*70�ĳߴ�
        train = train.reshape(0,1);  //��ɫͼ
        train.convertTo(train, CV_32FC1);  
        traindata.push_back(train);  
        trainmmat.push_back(train);  
	}
	static int correctTrainNum = 0;
	clock_t start = clock();  //����ѵ����Ԥ������Ҫ��ʱ��
	for (int i = 0;i < traindata.size() ; ++i)  
	{  
		int result = (int)classifier.predict(traindata[i]); //Ԥ��ı�ǩ��� 
		if (result == label[i])
			correctTrainNum++;
		/*std::cout<<"��������"<<i+1<<"�Ĳ��Խ��Ϊ��"  
		<<result<< " " << labelname[result-1] << "\n";  */
	}  
	clock_t end = clock();  
	double tt = static_cast<double>(end - start);  //����Ԥ��ʱ��
	cout << "Ԥ��ѵ����������: " << tt << " ms" << endl;
	cout << "ѵ������Ϊ: " << static_cast<double> (correctTrainNum)/trainnum*100 << "%" << endl;
	//*********************************************2.������Ծ���****************************//
    vector<Mat> testdata; //�����������  
    Mat testmmat;  
    Mat test;  
    for(int i = 0; i < testnum; i++)  
    {  
		//***************************����ͼƬ������ʽ1.jpg,2.jpg************************//
		
        sprintf(filename,"testdata/1 (%d).jpg",i+1);  //*****************************�޸����ݼ�ʱ��Ҫ����************//
        //*************ֱ�Ӱ�ͼƬ��Ϣ����***********  
        test = imread(filename,-1);  //��ȡ��ɫͼ
        //resize(test,test,Size(10,70));  //����������ת��Ϊ10*70�ĳߴ�
        test = test.reshape(0,1);  //��ɫͼ
        test.convertTo(test, CV_32FC1);  
        testdata.push_back(test);  
        testmmat.push_back(test);  
	}

	WriteData("feature_test.txt",testmmat);  
	char textInImage[200]; 
	static int correctTestNum = 0;
	start = clock();  
	//ʹ��ѵ���õķ���������Ԥ��  
	for (int i = 0;i < testdata.size() ; ++i)  
	{  
	   
	    int result = (int)classifier.predict(testdata[i]); //Ԥ��ı�ǩ��� 
		if(result == testlabel[i])
			correctTestNum++;
	    /*std::cout<<"��������"<<i+1<<"�Ĳ��Խ��Ϊ��"  
	        <<result<< " " << labelname[result-1] << "\n";  
	    sprintf(textinimage, "elapsed time: %5.2f ms", tt);  
	    cout << textinimage << endl;  */
	}  
	end = clock();  
	tt = static_cast<double>(end - start);  //����Ԥ��ʱ��
	cout << "Ԥ����Լ�������: " << tt << " ms" << endl;
	cout << "���Ծ���Ϊ: " << static_cast<double> (correctTestNum)/testnum*100 << "%" << endl;
	waitKey(0);
	return 0;
}