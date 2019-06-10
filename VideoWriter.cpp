#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(){
	VideoCapture cap(0);

	int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter video("outcpp.avi",VideoWriter::fourcc('M','J','P','G'),10, Size(frame_width,frame_height));
	Mat frame;
	while(1)
	{
		cap>>frame;
		if(frame.empty())
			break;
		video.write(frame);

		imshow("Frame",frame);
		char c = (char)waitKey(1);
		if(c == 27)
			break;

	}
	cap.release();
	video.release();
	destroyAllWindows();
	return 0;
}
