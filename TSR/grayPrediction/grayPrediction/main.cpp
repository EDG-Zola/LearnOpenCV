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
#define trainnum 657	//训练集数目
#define testnum  120	//测试集数目
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))  
//标签值,角度合并了！
//***********771个训练样本数据，120个测试数据，共11类标签*******************//
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
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,//18个样本
	9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,//38个样本
	1,1,1,1,1,1,1,1,//8个样本
	2,2,2,2,//4个样本
	3,3,//2个样本
	4,4,4,4,//4个样本
	5,5,5,//3个样本
	6,6,//2个样本
	7,7,7,7,7,7,//6个样本
	8,8,8,8,8,//5个样本
	10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,//17个样本
	11,11,11,11,11,11,11,11 //8个样本
}; 


float testlabel[testnum] = 
{
	1,1,//2个样本
	3,3,3,3,//4个样本
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
	CvSVM classifier;  
    classifier.load("model11Class657Sample.txt");  
	//*********************************************1.计算训练精度****************************//
	vector<Mat> traindata; //定义训练数据  
    Mat trainmmat;  
    Mat train;  
    for(int i = 0; i < trainnum; i++)  
    {  
		//***************************样本图片命名方式1.jpg,2.jpg************************//
		
        sprintf(filename,"traindata/1 (%d).jpg",i+1);  //*****************************修改数据集时需要更改************//
        //*************直接把图片信息放入***********  
        train = imread(filename,-1);  //读取彩色图
        //resize(test,test,Size(10,70));  //将测试样本转换为10*70的尺寸
        train = train.reshape(0,1);  //彩色图
        train.convertTo(train, CV_32FC1);  
        traindata.push_back(train);  
        trainmmat.push_back(train);  
	}
	static int correctTrainNum = 0;
	clock_t start = clock();  //计算训练集预测所需要的时间
	for (int i = 0;i < traindata.size() ; ++i)  
	{  
		int result = (int)classifier.predict(traindata[i]); //预测的标签结果 
		if (result == label[i])
			correctTrainNum++;
		/*std::cout<<"测试样本"<<i+1<<"的测试结果为："  
		<<result<< " " << labelname[result-1] << "\n";  */
	}  
	clock_t end = clock();  
	double tt = static_cast<double>(end - start);  //计算预测时间
	cout << "预测训练集共用了: " << tt << " ms" << endl;
	cout << "训练精度为: " << static_cast<double> (correctTrainNum)/trainnum*100 << "%" << endl;
	//*********************************************2.计算测试精度****************************//
    vector<Mat> testdata; //定义测试数据  
    Mat testmmat;  
    Mat test;  
    for(int i = 0; i < testnum; i++)  
    {  
		//***************************样本图片命名方式1.jpg,2.jpg************************//
		
        sprintf(filename,"testdata/1 (%d).jpg",i+1);  //*****************************修改数据集时需要更改************//
        //*************直接把图片信息放入***********  
        test = imread(filename,-1);  //读取彩色图
        //resize(test,test,Size(10,70));  //将测试样本转换为10*70的尺寸
        test = test.reshape(0,1);  //彩色图
        test.convertTo(test, CV_32FC1);  
        testdata.push_back(test);  
        testmmat.push_back(test);  
	}

	WriteData("feature_test.txt",testmmat);  
	char textInImage[200]; 
	static int correctTestNum = 0;
	start = clock();  
	//使用训练好的分类器进行预测  
	for (int i = 0;i < testdata.size() ; ++i)  
	{  
	   
	    int result = (int)classifier.predict(testdata[i]); //预测的标签结果 
		if(result == testlabel[i])
			correctTestNum++;
	    /*std::cout<<"测试样本"<<i+1<<"的测试结果为："  
	        <<result<< " " << labelname[result-1] << "\n";  
	    sprintf(textinimage, "elapsed time: %5.2f ms", tt);  
	    cout << textinimage << endl;  */
	}  
	end = clock();  
	tt = static_cast<double>(end - start);  //计算预测时间
	cout << "预测测试集共用了: " << tt << " ms" << endl;
	cout << "测试精度为: " << static_cast<double> (correctTestNum)/testnum*100 << "%" << endl;
	waitKey(0);
	return 0;
}