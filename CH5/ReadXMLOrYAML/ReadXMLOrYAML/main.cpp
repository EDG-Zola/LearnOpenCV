/************************************************************************/
/*					 ��ȡtest.yaml����ӡ���                            */
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
	//����̨��ɫ:����ɫ
	system("color 6F");
	FileStorage fs2("test.yaml", FileStorage::READ);
	//��һ�ַ�����ʹ��fileNode����
	int frameCount = (int) fs2["frameCount"];
	//�ڶ��ַ�����ʹ��fileNode��<<�����
	string date;
	fs2["calibrationDate"] >> date;
	Mat cameraMat, distCoeffs;
	fs2["cameraMat"] >> cameraMat;
	fs2["distCoeffs"] >> distCoeffs;
	//��ӡ���ǰ���test.yaml�ļ��ж�ȡ������
	cout << "frameCount: " << frameCount << endl;
	cout << "calibration date" << date << endl;
	cout << "camera mat" << cameraMat << endl;
	cout << "distCoeffs mat" << distCoeffs << endl;
	//��ȡFileNode�Ľṹ������
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