%module example

%{
#include "test_function.hpp"
%}


%include stl.i
%template(FaceVector)  std::vector<FaceLocation>;

/* Let's just grab the original header file here */
/*%include "test_function.hpp"*/

struct FaceLocation
{
	int x;
	int y;
	int width;
	int height;
};

std::vector<FaceLocation> detectFaces( std::vector<char>& jpg, double scale);

