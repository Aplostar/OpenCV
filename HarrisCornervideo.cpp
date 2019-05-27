#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat frame;

void cornerHarris_demo( int thresh );

int main( int argc, char** argv )
{

  VideoCapture cap(argv[1]);
  while(1)
  {
	    cap>>frame;
	  cvtColor( frame, frame, COLOR_BGR2GRAY );

	  cornerHarris_demo(120);

  }
  cap.release();
  destroyAllWindows();
  return(0);
}
void cornerHarris_demo( int thresh )
{

  Mat dst, dst_norm, dst_norm_scaled;
  dst = Mat::zeros( frame.size(), CV_32FC1 );

  /// Detector parameters
  int blockSize = 3;
  int apertureSize = 3;
  double k = 0.04;

  /// Detecting corners
  cornerHarris( frame, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );

  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
            		circle(dst_norm,Point(i,j),1.5,0,2,8,0);
              }

          }
     }
  /// Showing the result
  namedWindow("harris",WINDOW_AUTOSIZE );
  imshow("harris",dst_norm);

  char ch = waitKey(25);
  if(ch == 27)
	  exit(1);
}
