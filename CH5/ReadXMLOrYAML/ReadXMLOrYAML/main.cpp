/************************************************************************/
/*					 读取test.yaml并打印输出                            */
/************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;
using namespace cv;
int main(){
	//控制台颜色:土黄色
	system("color 6F");
	FileStorage fs2("test.yaml", FileStorage::READ);
	//第一种方法，使用fileNode操作
	int frameCount = (int) fs2["frameCount"];
	//第二种方法，使用fileNode的<<运算符
	string date;
	fs2["calibrationDate"] >> date;
	Mat cameraMat, distCoeffs;
	fs2["cameraMat"] >> cameraMat;
	fs2["distCoeffs"] >> distCoeffs;
	//打印输出前面从test.yaml文件中读取的内容
	cout << "frameCount: " << frameCount << endl;
	cout << "calibration date" << date << endl;
	cout << "camera mat" << cameraMat << endl;
	cout << "distCoeffs mat" << distCoeffs << endl;
	//读取FileNode的结构的内容
	FileNode feature = fs2["features"];
	FileNodeIterator it = feature.begin(), it_end = feature.end();
	int idx = 0;
	vector<uchar> lbqval;
	for ( ; it != it_end; ++it, ++idx){
		cout << "feature #" << idx << endl;
		cout << "x: " << (int)(*it)["x"] << ", y: " << (int)(*it)["y"] << ", lbp:(" ;
		(*it)["lbp"] >> lbqval;
		for (int i = 0; i < (int)lbqval.size(); ++i){
			cout << " " << (int)lbqval[i];
		}
		cout << ")" <<endl;
	}
	fs2.release();
	
	waitKey(0);
	return 0;
}