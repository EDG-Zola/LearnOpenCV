/************************************************************************/
/*                     访问图像中像素的三种方法                         */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/************************************************************************/
/*                           函数声明                                   */
/************************************************************************/
void colorReducePointer(Mat &inputImage, Mat &outputImage, int div);//使用指针访问
void colorReduceIteration(Mat &inputImage, Mat &outputImage, int div);//使用迭代器访问
void colorReduceDynamicAddr(Mat &inputImage, Mat &outputImage, int div);//使用动态地址访问
int main(){
	Mat srcImage = imread("1.jpg");
	imshow("原始图像", srcImage);

	Mat dstImage;
	//使效果图的大小、类型与原图像相同
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
	/************************************************************************/
	/*               方法一：用指针访问像素（注意越界问题）                 */
	/************************************************************************/
	//记录起始时间
	double time0 = static_cast<double> (getTickCount());
	colorReducePointer(srcImage, dstImage, 32);
	//记录终止时间
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "指针访问方法运行时间为： " << time0 << "秒" << endl;
	imshow("指针访问效果图", dstImage);

	/************************************************************************/
	/*               方法二：用迭代器访问像素（最安全）                     */
	/************************************************************************/
	//记录起始时间
	time0 = static_cast<double> (getTickCount());
	colorReduceIteration(srcImage, dstImage, 32);
	//记录终止时间
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "迭代器访问方法运行时间为： " << time0 << "秒" << endl;
	imshow("迭代器访问效果图", dstImage);

	/************************************************************************/
	/*         方法三：用动态地址配合at方法访问像素（简单明了）             */
	/************************************************************************/
	//记录起始时间
	time0 = static_cast<double> (getTickCount());
	colorReduceDynamicAddr(srcImage, dstImage, 32);
	//记录终止时间
	time0 = (static_cast<double> (getTickCount()) - time0)/getTickFrequency();
	cout << "动态指针访问方法运行时间为： " << time0 << "秒" << endl;
	imshow("动态地址访问效果图", dstImage);

	waitKey(0);
	return 0;
}

/************************************************************************/
/*               方法一：用指针访问像素（注意越界问题）                 */
/************************************************************************/
void colorReducePointer(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();//将输入图像的副本赋值给输出图像
	int rowNumber = outputImage.rows;//图像的行数
	int colNumber = outputImage.cols * outputImage.channels();//图像的列数*通道数
	for (int i = 0; i < rowNumber; ++i){
		uchar* data = outputImage.ptr<uchar>(i);//ptr是一个模板函数，返回每一行的首地址，将每一行的首地址赋值给data
		for (int j = 0; j < colNumber; ++j){
			data[j] = data[j] / div *div + div/2;//对每个像素颜色空间降维
		}
	}
}

/************************************************************************/
/*               方法二：用迭代器访问像素（最安全）                     */
/************************************************************************/
void colorReduceIteration(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();//指向图像的第一个像素
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//指向图像的最后个像素
	for (; it != itend; ++it){
		(*it)[0] = (*it)[0] / div *div + div/2;//对第一个像素的第一个通道元素进行颜色空间降维
		(*it)[1] = (*it)[1] / div *div + div/2;//对第二个像素的第二个通道元素进行颜色空间降维
		(*it)[2] = (*it)[2] / div *div + div/2;//对第三个像素的第三个通道元素进行颜色空间降维
	}
}

/************************************************************************/
/*         方法三：用动态地址配合at方法访问像素（简单明了）             */
/************************************************************************/
void colorReduceDynamicAddr(Mat &inputImage, Mat &outputImage, int div){
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	for (int i = 0; i < rowNumber; ++i){
		for (int j = 0; j < colNumber; ++j){
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div/2;//蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div/2;//蓝色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div/2;//蓝色通道
		}
	}
}