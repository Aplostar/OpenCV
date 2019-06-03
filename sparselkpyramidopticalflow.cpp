#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc,char **argv)
{
	int win_size = 10;
	VideoCapture cap(0);		// Capture the live feed from your camera
					// Can replace this with cap(argv[1]) to feed a video instead of the camera
	
	if(!cap.isOpened())		// Throw an error if the camera feed can not be captured or camera does not open
	{	
		cout<<"Error in capturing the feed...";
		return -1;
	}
	// Take the first frame and find corners in it
	Mat old_frame;
	cap>>old_frame;
	Mat old_gray;
	
	// Convert it into grayscale
	cvtColor(old_frame,old_gray,COLOR_BGR2GRAY);

	const int MAX_CORNERS = 100;
	vector<Point2f>cornersA,cornersB;
	// Find corners
	goodFeaturesToTrack(old_gray,cornersA,MAX_CORNERS,0.01,5,cv::noArray(),3,true,0.04);
	
	// Create a mask for drawing purposes
	Mat mask;
	mask = Mat::zeros(old_frame.rows,old_frame.cols,CV_8UC3);
	Mat frame;
	
	vector<uchar> features_found;
	Mat frame_gray;

	while(1)
	{
		cap>>frame;		// Capture the current frame
		cvtColor(frame,frame_gray,COLOR_BGR2GRAY);
		
		// Calculate the new positions of the features using pyramidal LK optical flow algorithm
		calcOpticalFlowPyrLK(old_gray,frame_gray,cornersA,cornersB,features_found,noArray(),Size(win_size*2+1,win_size*2+1),5,TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS,20,0.3));

		vector<Point2f>good_new,good_old;
		
		// Store the new vectors
		good_new = cornersB;		
		good_old = cornersA;

		for(int i = 0;i<good_new.size();i++){
			Scalar color = Scalar(rand()%255,rand()%255,rand()%255);
			line(mask,good_new[i],good_old[i],color,2);
			circle(frame,good_new[i],5,color,-1);
		}

		add(frame,mask,frame);			// Create a copy of the image for display purposes

		imshow("Frame",frame);			// Show the current image
	
		char k = waitKey(30);
		if(k == 27)
		{
			break;
		}

		frame_gray.copyTo(old_gray);		// Make the current frame as the old frame for the next loop.
		cornersA = good_new;

	}	
	cap.release();					// Release the cap variable and destroy all windows.
	destroyAllWindows();
	return 0;
}

