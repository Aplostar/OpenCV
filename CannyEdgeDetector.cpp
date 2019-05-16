/*
 * 	Canny Edge Detector
 *
 *  The Canny() function in opencv takes in the following parameters - inputimg, outputarr, lowerthreshold, highertreshold,
 *  sobelaperture and boolean value for l2gradient
 *
 */

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int lowThreshold = 40;
const int maxLowThreshold = 100;
const int ratio = 3;
const int kernel_size= 3;
const char* window_name = "Canny edge detector";

int main(int argc, char**argv){
	src = imread(argv[1],1);
	if(src.empty())
	{
		std::cout<<"Image not found"<<std::endl;
		return -1;
	}
	dst.create(src.size(),src.type());
	cvtColor(src,src_gray,COLOR_BGR2GRAY);

	namedWindow(window_name,WINDOW_AUTOSIZE);

	GaussianBlur(src_gray,detected_edges, Size(5,5),1);
	Canny(detected_edges,detected_edges,lowThreshold,lowThreshold*ratio,kernel_size);

	imshow(window_name,detected_edges);
	waitKey(0);

	return 0;
}


