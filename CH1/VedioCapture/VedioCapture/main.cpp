/*调用视频需要的头文件*/

#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
	//读入视频1.avi
	VideoCapture capture("1.avi");
	//循环显示每一帧
	while(1){
		Mat frame;
		capture >> frame;
		imshow("读取视频",frame);//只显示每一帧，没有声音
		waitKey(1);//延时30ms,显示下一帧,更改1这个参数可以加速或减慢播放
	}
}