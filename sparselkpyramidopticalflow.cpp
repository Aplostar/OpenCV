#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

//static const int MAX_CORNERS = 1000;

using namespace cv;
using namespace std;

int main(int argc,char **argv)
{
	int win_size = 10;
	VideoCapture cap(0);

	if(!cap.isOpened())
		return -1;
	// Take the first frame and find corners in it
	Mat old_frame;
	cap>>old_frame;
	Mat old_gray;
	cvtColor(old_frame,old_gray,COLOR_BGR2GRAY);

	const int MAX_CORNERS = 100;
	vector<Point2f>cornersA,cornersB;
	goodFeaturesToTrack(old_gray,cornersA,MAX_CORNERS,0.01,5,cv::noArray(),3,true,0.04);
	Mat mask;
	mask = Mat::zeros(old_frame.rows,old_frame.cols,CV_8UC3);
	Mat frame;
	vector<uchar> features_found;
	Mat frame_gray;

	while(1)
	{
		cap>>frame;
		cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
		calcOpticalFlowPyrLK(old_gray,frame_gray,cornersA,cornersB,features_found,noArray(),Size(win_size*2+1,win_size*2+1),5,TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS,20,0.3));

		vector<Point2f>good_new,good_old;

		good_new = cornersB;
		good_old = cornersA;

		for(int i = 0;i<good_new.size();i++){
			Scalar color = Scalar(rand()%255,rand()%255,rand()%255);
			line(mask,good_new[i],good_old[i],color,2);
			circle(frame,good_new[i],5,color,-1);
		}

		add(frame,mask,frame);

		imshow("Frame",frame);

		char k = waitKey(30);
		if(k == 27)
		{
			break;
		}

		frame_gray.copyTo(old_gray);
		cornersA = good_new;

	}
	cap.release();
		destroyAllWindows();
		return 0;
}

