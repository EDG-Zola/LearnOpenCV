#include "color_cvt.h"
#include "pre_img.h"
#include<direct.h> 
RNG rng(12345);
#define trainNum 1416
int main()
{
	char path[50];
	//这里载入分类器，方便直接训练
	for(int k = 0;k<trainNum;k++)
	{
		//只需要更改此文件夹名"00001/1 (%d).jpg"和k值（图片个数）******************************//
		sprintf(path,"00003/1 (%d).jpg",k+1);
		cout << path << endl;
		//读取图片
		Mat src = imread(path);
		Mat copy;
		src.copyTo(copy);
		//得到图像参数
		int width = src.cols;   //图像宽度
		int height = src.rows;   //图像高度
		//色彩分割
		double B=0.0,G=0.0,R=0.0,H=0.0,S=0.0,V=0.0;
		Mat Mat_rgb = Mat::zeros( src.size(), CV_8UC1 );
		Mat Mat_rgb_copy;//一个暂存单元
		//Mat copy;
		//src.copyTo(copy);
		int x,y,px,py; //循环
		for (y=0; y<height; y++)
		{
			for ( x=0; x<width; x++)
			{
				// 获取BGR值
				B = src.at<Vec3b>(y,x)[0];
				G = src.at<Vec3b>(y,x)[1];
				R = src.at<Vec3b>(y,x)[2];
				RGB2HSV(R,G,B,H,S,V); 
				//红色：337-360
				if((H>=312 && H<=360||H>=0&&H<=20)&&S>=17&&S<=100&&V>18&&V<=100)
				{
					Mat_rgb.at<uchar>(y,x) = 255;  //R   
					continue;
				}
				//黑色：0-30
				if((H>=0&&H<=360)&&S>=0&&S<=100&&V>=0&&V<=18)
				{
					Mat_rgb.at<uchar>(y,x) = 255; //黑色   
					continue;
				}
				////蓝色：200-228
				if((H>=200 && H<=248||H>=0&&H<=10)&&S>=17&&S<=100&&V>=18&&V<=100)
				{
					Mat_rgb.at<uchar>(y,x) = 255; //蓝色   
					continue;
				}
			}
		}
		//imshow("hsi",Mat_rgb);
		medianBlur(Mat_rgb,Mat_rgb,3);
		Mat element = getStructuringElement(MORPH_ELLIPSE,
			Size(2*1 + 1, 2*1 + 1),
			Point(1,1));
		Mat element1 = getStructuringElement(MORPH_ELLIPSE,
			Size(2*3 + 1, 2*3 + 1),
			Point(3,3));
		//形态学处理图像，开操作和闭操作，消除噪声，连通有效区域
		erode(Mat_rgb,Mat_rgb,element);
		dilate(Mat_rgb,Mat_rgb,element1);
		fillHole(Mat_rgb,Mat_rgb);
		Mat_rgb.copyTo(Mat_rgb_copy);
		/// 多边形逼近轮廓 + 获取矩形和圆形边界框
		//找轮廓
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours( Mat_rgb, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		/// 多边形逼近轮廓 + 获取矩形和圆形边界框
		vector<vector<Point> > contours_poly( contours.size() );
		vector<Rect> boundRect( contours.size() );
		vector<Point2f>center( contours.size() );
		vector<float>radius( contours.size() );

		for( int i = 0; i < contours.size(); i++ )
		{ 
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( contours_poly[i], center[i], radius[i] );
		}
		/// 画多边形轮廓 + 包围的矩形框 + 圆形框
		Mat drawing = Mat::zeros( Mat_rgb.size(), CV_8UC3 );
		static int count1 = 0;
		for( int i = 0; i< contours.size(); i++ )
		{
			Rect rect = boundRect[i];
			//首先进行一定的限制，筛选出区域
			//高宽比限制
			float ratio = (float)rect.width / (float)rect.height;
			//轮廓面积     
			float Area = (float)rect.width * (float)rect.height;
			float dConArea = (float)contourArea(contours[i]);
			float dConLen = (float)arcLength(contours[i],1);
			if(dConArea <400)
				continue;
			if(ratio>2||ratio<0.5)
				continue;

			//进行圆筛选，通过四块的缺失像素比较
			Mat roiImage;  
			Mat_rgb_copy(rect).copyTo(roiImage);
			//imshow("test",roiImage);
			Mat temp;
			copy(rect).copyTo(temp);
			//imshow("test2",temp);
			bool iscircle = isCircle(roiImage,temp);
			cout << "circle:" << iscircle << endl;
			if(!iscircle)
				continue;
			//接下来是形状限制！这里检测圆形标志牌
			float C = (4*PI*dConArea)/(dConLen*dConLen);
			if(C < 0.4)//利用圆度初步对形状进行筛选
				continue;
			//cout << C << "," << R << "," << E << "," << E << endl;
			copy(rect).copyTo(roiImage);
			//**********************************产生45x45x3的彩色训练图片***********************//
			//imshow("a",temp);
			resize(temp,temp,Size(45,45));
			//threshold(temp2,temp2,120,255,THRESH_BINARY_INV);
			//imshow("temp",temp);
			count1++;
			//***************修改存储的图片路径及图片名"00012_45/001 (%d).jpg"*****************//
			String directName = "00003_45c";
			_mkdir(directName.c_str());
			sprintf(path,"00003_45c/%d.jpg",count1);
			imwrite(path, temp);//保存最终的检测识别结果
		}
	}
	waitKey(0);
	return 0;
}