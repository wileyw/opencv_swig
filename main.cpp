#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <cctype>
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>

#include "test_function.hpp"

using namespace std;
using namespace cv;

vector<char> getFileContent(const char* path)
{
  ifstream input(path, ios::binary);
  vector<char> buffer((
    std::istreambuf_iterator<char>(input)), 
    (std::istreambuf_iterator<char>()));
  return buffer;
}

int main( int argc, const char** argv )
{
	vector<char> jpg = getFileContent(argv[1]);
	vector<FaceLocation> locs = detectFaces(jpg, 3.0);
	for (int i = 0; i < locs.size(); i++) {
		cout << "{x: " << locs[i].x << ", "
			 << "y: " << locs[i].y << ", "
			 << "width: " << locs[i].width << ", "
			 << "height: " << locs[i].height << "}"
			 << endl;
	}
	return 0;
}