#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>

using namespace std;
using namespace cv;

struct FaceLocation
{
	int x;
	int y;
	int width;
	int height;
};

vector<FaceLocation> detectFaces( vector<char>& jpg, double scale);
