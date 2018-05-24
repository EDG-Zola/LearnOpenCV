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
//*****************************修改数据集时需要更改************//
#define trainnum 771
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//标签值,角度合并了！
//***********771个样本数据，共11类标签*******************//
//*****************************修改数据集时需要更改************//
float label[trainnum] =   
{  
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//50个//
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//41个
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//50个样本
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//50个样本
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//50个样本
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//50个样本
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//50个样本
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//50个样本
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//50个样本
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//44个样本
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//50个样本
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//50个样本
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//50个样本
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//42个样本
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//34个样本
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,//36个样本
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,//18个样本
	11,11,11,11,11,11//6个样本
}; 

//*****************************修改数据集时需要更改************//
string labelname[500] = {"最高限速20km",//1,91个样本 
	"最高限速30km",//2,//100个样本 
	"最高限速50km",//3,//100个样本  
	"最高限速60km",//4,//100个样本 
	"最高限速70km",//5,//94个样本 
	"最高限速80km",//6,//100个样本 
	"最高限速100km",//7,//92个样本 
	"最高限速120km",//8,//34个样本  
	"最低限速50km",//9,//36个样本  
	"解除限速40km",//10,//18个样本 
	"最高限速40km",//11,//6个样本 
};

int WriteData(string fileName, cv::Mat& matData)    
{    
	int retVal = 0;    

	// 打开文件    
	ofstream outFile(fileName.c_str(), ios_base::out);  //按新建或覆盖方式写入    
	if (!outFile.is_open())    
	{    
		cout << "打开文件失败" << endl;     
		retVal = -1;    
		return (retVal);    
	}    

	// 检查矩阵是否为空    
	if (matData.empty())    
	{    
		cout << "矩阵为空" << endl;     
		retVal = 1;    
		return (retVal);    
	}    
	// 写入数据
	/******************************这里是二值化的数据************************/
	for (int r = 0; r < matData.rows; r++)    
	{    
		for (int c = 0; c < matData.cols; c++)    
		{    
			if(c != 0)  
				outFile << ",";  
			float data = matData.at<float>(r,c);  //读取数据，at<type> - type 是矩阵元素的具体数据格式   
			outFile << data  ;   //每列数据用 tab 隔开    
		}    
		outFile << endl;  //换行  
	}    

	return (retVal);    
}    

//尺寸缩放
void floatscale(float* f,int num, int scale)  
{  
	for(int i = 0; i < num; i++)  
	{  
		f[i]=f[i]*scale;  
	}  
}  
int main()  
{     
    //读取sample中的样本  
    char filename[200];  
    Mat sample;  
    Mat train;  
    Mat Hu_train;  
    //读取图片数据，提取特征也在这里！  
    IplImage* ImageGray; //灰度图 
    float feavec[48];  
    for(int i = 0; i < trainnum; i++)  
    {  
		//***************************样本图片命名方式1.jpg,2.jpg************************//
		
        sprintf(filename,"result/1 (%d).jpg",1+i); //*****************************修改数据集时需要更改************// 
        //*************把图片信息直接放入************  
        sample = imread(filename,1); //-1为不改变，1位彩色图 
        sample = sample.reshape(1,1);  //转换为一个行向量 ，参数为（1,1）表示转为（rows*cols*channels,1）,（0,1）为单通道灰度图
        sample.convertTo(sample, CV_32F);  //换装存储格式为CV_32F
        train.push_back(sample);  //存储到Mat类train的一行中，现在变成(i,700)的矩阵
	}
	WriteData("feature_train.txt",train); 
	Mat labels(trainnum, 1, CV_32FC1, label);
	cout << train.cols << " " << train.rows << endl;
	cout << labels.cols << " " << labels.rows << endl; 


	//*********************SVM训练部分***********************  
    //准备开始训练  
    cout << "starting SVM...\n";
	CvSVM classifier;  
    CvSVMParams SVM_params;  
    SVM_params.kernel_type = CvSVM::LINEAR; //使用RBF分类非线性问题  
    SVM_params.svm_type = CvSVM::C_SVC;  
    SVM_params.degree = 0;  
    SVM_params.gamma = 0.01;  
    SVM_params.term_crit =  cvTermCriteria(CV_TERMCRIT_ITER, 1000, FLT_EPSILON);  
    SVM_params.C = 100;//把1改成了100  
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
	classifier.save("model11Class771ColorSample.txt"); //保存分类器的训练结果参数
	waitKey(0);
	return 0;
}