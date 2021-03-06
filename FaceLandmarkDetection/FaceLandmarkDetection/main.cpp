// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

This example program shows how to find frontal human faces in an image and
estimate their pose.  The pose takes the form of 68 landmarks.  These are
points on the face such as the corners of the mouth, along the eyebrows, on
the eyes, and so forth.



The face detector we use is made using the classic Histogram of Oriented
Gradients (HOG) feature combined with a linear classifier, an image pyramid,
and sliding window detection scheme.  The pose estimator was created by
using dlib's implementation of the paper:
One Millisecond Face Alignment with an Ensemble of Regression Trees by
Vahid Kazemi and Josephine Sullivan, CVPR 2014
and was trained on the iBUG 300-W face landmark dataset (see
https://ibug.doc.ic.ac.uk/resources/facial-point-annotations/):
C. Sagonas, E. Antonakos, G, Tzimiropoulos, S. Zafeiriou, M. Pantic.
300 faces In-the-wild challenge: Database and results.
Image and Vision Computing (IMAVIS), Special Issue on Facial Landmark Localisation "In-The-Wild". 2016.
You can get the trained model file from:
http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2.
Note that the license for the iBUG 300-W dataset excludes commercial use.
So you should contact Imperial College London to find out if it's OK for
you to use this model file in a commercial product.


Also, note that you can train your own models using dlib's machine learning
tools.  See train_shape_predictor_ex.cpp to see an example.




Finally, note that the face detector is fastest when compiled with at least
SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
chip then you should enable at least SSE2 instructions.  If you are using
cmake to compile this program you can enable them by using one of the
following commands when you create the build project:
cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
This will set the appropriate compiler options for GCC, clang, Visual
Studio, or the Intel compiler.  If you are using another compiler then you
need to consult your compiler's manual to determine how to enable these
instructions.  Note that AVX is the fastest but requires a CPU from at least
2011.  SSE4 is the next fastest and is supported by most current machines.
*/

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>


using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	try
	{
		// This example takes in a shape model file and then a list of images to
		// process.  We will take these filenames in as command line arguments.
		// Dlib comes with example images in the examples/faces folder so give
		// those as arguments to this program.
		if (argc == 1)
		{
			cout << "Call this program like this:" << endl;
			cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
			cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
			cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
			return 0;
		}

		// We need a face detector.  We will use this to get bounding boxes for
		// each face in an image.
		// 需要一个人脸检测器来抓取一张图片中的人脸，并给每个人脸用方框抓取
		frontal_face_detector detector = get_frontal_face_detector();
		// And we also need a shape_predictor.  This is the tool that will predict face
		// landmark positions given an image and face bounding box.  Here we are just
		// loading the model from the shape_predictor_68_face_landmarks.dat file you gave
		// as a command line argument.
		// 需要一个人脸形状预测器，预测给定图片的脸部特征点和脸部轮廓，
		// 这里用命令行加载文件shape_predictor_68_face_landmarks.dat中的数据
		shape_predictor sp;
		deserialize(argv[1]) >> sp;

		// 声明两个图片窗口，一个用于显示抓取的人脸，一个用于绘制脸部特征点轮廓
		image_window win, win_faces;
		// Loop over all the images provided on the command line.
		// 寻找命令行中所有的输入图片
		for (int i = 2; i < argc; ++i)
		{
			cout << "processing image " << argv[i] << endl;
			// 加载彩色图片到array2d<rgb_pixel>类的img对象
			array2d<rgb_pixel> img;
			load_image(img, argv[i]);
			// Make the image larger so we can detect small faces.
			// 调用pyrimid_up()函数使图像更大，以便我们可以检测到小脸
			pyramid_up(img);

			// Now tell the face detector to give us a list of bounding boxes
			// around all the faces in the image.
			// 现在告诉面部检测器，获取图像中所有面部的边界框列表
			std::vector<rectangle> dets = detector(img);
			cout << "Number of faces detected: " << dets.size() << endl;

			// Now we will go ask the shape_predictor to tell us the pose of
			// each face we detected.
			// 现在我们将用shape_predictor告诉我们检测到的每张脸的姿势，
			std::vector<full_object_detection> shapes;
			for (unsigned long j = 0; j < dets.size(); ++j)
			{
				full_object_detection shape = sp(img, dets[j]);
				// 这里的shape_predictor_68_face_landmarks.dat只支持68个特征点，
				// 这些特征点的像素存储在shape对象中
				cout << "number of parts: " << shape.num_parts() << endl;
				// 这里只输出了shape中的前两个特征点像素的位置
				cout << "pixel position of first part:  " << shape.part(0) << endl;
				cout << "pixel position of second part: " << shape.part(1) << endl;
				// You get the idea, you can get all the face part locations if
				// you want them.  Here we just store them in shapes so we can
				// put them on the screen.
				// 因此，你能够获取一个人脸所有特征点的像素位置，这些像素点位置存储在shape对象中
				// 图片中所有人脸特征点的像素位置存储在shapes对象中
				shapes.push_back(shape);
			}

			// Now let's view our face poses on the screen.
			// 在屏幕上显示脸部姿态
			win.clear_overlay();
			// 将img加载到显示窗口中
			win.set_image(img);
			win.add_overlay(render_face_detections(shapes));

			// We can also extract copies of each face that are cropped, rotated upright,
			// and scaled to a standard size as shown here:
			// 我们还可以提取裁剪，直立旋转和缩放到标准尺寸的每张脸的副本
			dlib::array<array2d<rgb_pixel> > face_chips;
			extract_image_chips(img, get_face_chip_details(shapes), face_chips);
			win_faces.set_image(tile_images(face_chips));

			cout << "Hit enter to process the next image..." << endl;
			cin.get();
		}
	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}

// ----------------------------------------------------------------------------------------

