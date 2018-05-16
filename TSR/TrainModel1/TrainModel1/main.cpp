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
#define trainnum 560

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//��ǩֵ,�ǶȺϲ��ˣ�
//***********560���������ݣ���8���ǩ*******************//
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
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8//18������
}; 
//*****************************�޸����ݼ�ʱ��Ҫ����************//
string labelname[500] = {"�������20km",//1,48������ 
	"�������30km",//2,//60������ 
	"�������50km",//3,//60������  
	"�������60km",//4,//35������ 
	"�������70km",//5,//60������ 
	"�������80km",//6,//60������ 
	"�������100km",//7,//56������ 
	"�������120km",//8,//60������  
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
        sample = imread(filename,-1);  
        //resize(sample,sample,Size(45,45));  //�ı�����ͼ�ߴ磬��10����70�����10*70������ͼ
        sample = sample.reshape(0,1);  //ת��Ϊһ�������� rows*cols*channels
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
	classifier.save("model8Class439Sample.txt"); //�����������ѵ���������

	 //�������������������ֱ��Ԥ��  
    //CvSVM classifier;  
	cout << "endinging SVM,starting predicting..\n";
    classifier.load("model8Class439Sample.txt");  
    vector<Mat> testdata; //�����������  
    Mat testmmat;  
    Mat test;  
    int testnum = 40;  //���ﶨ����testnum������������//*****************************�޸����ݼ�ʱ��Ҫ����************//
    for(int i = 0; i < testnum; i++)  
    {  
		//***************************����ͼƬ������ʽ1.jpg,2.jpg************************//
		
        sprintf(filename,"test/1 (%d).jpg",i+1);  //*****************************�޸����ݼ�ʱ��Ҫ����************//
        //*************ֱ�Ӱ�ͼƬ��Ϣ����***********  
        test = imread(filename,-1);  
        //resize(test,test,Size(10,70));  //����������ת��Ϊ10*70�ĳߴ�
        test = test.reshape(0,1);  
        test.convertTo(test, CV_32FC1);  
        testdata.push_back(test);  
        testmmat.push_back(test);  
	}

	WriteData("feature_test.txt",testmmat);  
	char textInImage[200];  
	//ʹ��ѵ���õķ���������Ԥ��  
	for (int i = 0;i < testdata.size() ; ++i)  
	{  
	    clock_t start = clock();  
	    int result = (int)classifier.predict(testdata[i]); //Ԥ��ı�ǩ��� 
	    std::cout<<"��������"<<i+1<<"�Ĳ��Խ��Ϊ��"  
	        <<result<< " " << labelname[result-1] << "\n";  
	    clock_t end = clock();  
	    double tt = static_cast<double>(end - start);  //����Ԥ��ʱ��
	    sprintf(textInImage, "elapsed time: %5.2f ms", tt);  
	    cout << textInImage << endl;  
	}  

	waitKey(0);
	return 0;
}