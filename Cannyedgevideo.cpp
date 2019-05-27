#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

Mat dst;

int lowThreshold = 30;
const int ratio = 3;
const int kernel_size= 3;
const char* window_name = "Canny edge detector";
//cornerHarris
int main(int argc, char**argv){
	VideoCapture cap(argv[1]);

	while(1)
	{
		Mat frame;
		cap>>frame;
		if(frame.empty())
		{
			std::cout<<"Video could not be found"<<std::endl;
			return -1;
		}
		dst.create(frame.size(),frame.type());
		cvtColor(frame,frame,COLOR_BGR2GRAY);

		namedWindow(window_name);

		GaussianBlur(frame,dst, Size(3,3),1);

		Canny(dst,dst,lowThreshold,lowThreshold*ratio,kernel_size);

		imshow(window_name,dst);
		char ch = waitKey(25);
		if(ch==27)
			break;
	}
	cap.release();
	destroyAllWindows();
	return 0;
}
