/************************************************************************/
/*						此程序实现了傅里叶变换的过程                    */
/************************************************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

/************************************************************************/
/*							主函数                                      */
/************************************************************************/
int main(){
	system("color 5E");
	//1. 以灰度模式读取图片并显示
	Mat srcImage = imread("1.jpg", 0);
	if (!srcImage.data){
		cerr << "读取1.jpg图片错误" <<endl;
		return false;
	}
	imshow("图片的灰度图片", srcImage);
	
	//2. 将输入的图片扩充为最佳尺寸，边界用0填充
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	//边界用0填充
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//3.为傅里叶变换的实部和虚部分配存储空间
	//将planes数组组合合并成一个多通道的数组complexI
	Mat planes[] = {Mat_<float> (padded), Mat::zeros(padded.size(), CV_32F )};
	Mat complexI;
	merge(planes, 2, complexI);

	//4.就地进行傅里叶变换(输入和输出为相同的图片)
	dft(complexI, complexI);

	//5. 将复数转换为幅值,即log(1+sqrt(Re(DFT(I)^2 + Im(DFT(I)^2)))
	split(complexI, planes);//将多通道complexI分离成几个单通道数组
	//planes[0] = Re(DTE(I)), planes[1] = Im(DTE(I))
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];
	//对数尺寸缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然对数

	//6. 剪切和重分布幅度图象限
	//若有奇数行和奇数列，则进行频谱裁剪
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//重新排列傅里叶图像的象限，是原点位于图像的中心
	int cy = magnitudeImage.rows/2;
	int cx = magnitudeImage.cols/2;
	Mat q0(magnitudeImage, (Rect(0, 0, cx, cy))); //ROI区域的左上
	Mat q1(magnitudeImage, (Rect(cx, 0, cx, cy))); //ROI区域的右上
	Mat q2(magnitudeImage, (Rect(0, cy, cx, cy))); //ROI区域的左下
	Mat q3(magnitudeImage, (Rect(cx, cy, cx, cy))); //ROI区域的右下
	//交换象限（左上和右下进行交换）
	Mat temp;
	q0.copyTo(temp);
	q3.copyTo(q0);
	temp.copyTo(q3);
	//交换象限（右上和左下进行交换）
	q1.copyTo(temp);
	q2.copyTo(q1);
	temp.copyTo(q2);

	//7. 归一化，用0-1的浮点值将矩阵变换为可视化的格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);

	//8. 显示效果图
	imshow("频谱幅值", magnitudeImage);
	cout << "程序运行成功";
	waitKey(0);
	return 0;
}