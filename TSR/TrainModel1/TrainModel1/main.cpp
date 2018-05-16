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
#define trainnum 560

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//标签值,角度合并了！
//***********560个样本数据，共8类标签*******************//
//*****************************修改数据集时需要更改************//
float label[trainnum] =   
{  
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,//48个//
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//60个样本
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//60个样本
	4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,//35个样本
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//60个样本
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,//60个样本
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,//56个样本
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//60个样本
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,//30个样本
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,//30个样本
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,//30个样本
	6,6,6,6,6,6,6,6,6,6,6,6,6,//13个样本
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8//18个样本
}; 
//*****************************修改数据集时需要更改************//
string labelname[500] = {"最高限速20km",//1,48个样本 
	"最高限速30km",//2,//60个样本 
	"最高限速50km",//3,//60个样本  
	"最高限速60km",//4,//35个样本 
	"最高限速70km",//5,//60个样本 
	"最高限速80km",//6,//60个样本 
	"最高限速100km",//7,//56个样本 
	"最高限速120km",//8,//60个样本  
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
        sample = imread(filename,-1);  
        //resize(sample,sample,Size(45,45));  //改变样本图尺寸，宽10，高70，输出10*70的样本图
        sample = sample.reshape(0,1);  //转换为一个行向量 rows*cols*channels
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
	classifier.save("model8Class439Sample.txt"); //保存分类器的训练结果参数

	 //这里载入分类器，方便直接预测  
    //CvSVM classifier;  
	cout << "endinging SVM,starting predicting..\n";
    classifier.load("model8Class439Sample.txt");  
    vector<Mat> testdata; //定义测试数据  
    Mat testmmat;  
    Mat test;  
    int testnum = 40;  //这里定义了testnum个测试样本，//*****************************修改数据集时需要更改************//
    for(int i = 0; i < testnum; i++)  
    {  
		//***************************样本图片命名方式1.jpg,2.jpg************************//
		
        sprintf(filename,"test/1 (%d).jpg",i+1);  //*****************************修改数据集时需要更改************//
        //*************直接把图片信息放入***********  
        test = imread(filename,-1);  
        //resize(test,test,Size(10,70));  //将测试样本转换为10*70的尺寸
        test = test.reshape(0,1);  
        test.convertTo(test, CV_32FC1);  
        testdata.push_back(test);  
        testmmat.push_back(test);  
	}

	WriteData("feature_test.txt",testmmat);  
	char textInImage[200];  
	//使用训练好的分类器进行预测  
	for (int i = 0;i < testdata.size() ; ++i)  
	{  
	    clock_t start = clock();  
	    int result = (int)classifier.predict(testdata[i]); //预测的标签结果 
	    std::cout<<"测试样本"<<i+1<<"的测试结果为："  
	        <<result<< " " << labelname[result-1] << "\n";  
	    clock_t end = clock();  
	    double tt = static_cast<double>(end - start);  //计算预测时间
	    sprintf(textInImage, "elapsed time: %5.2f ms", tt);  
	    cout << textInImage << endl;  
	}  

	waitKey(0);
	return 0;
}