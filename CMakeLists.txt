cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FIND_PACKAGE( OpenCV REQUIRED )
FIND_PACKAGE(SWIG REQUIRED)
FIND_PACKAGE(Ruby REQUIRED)

INCLUDE(${SWIG_USE_FILE})
INCLUDE_DIRECTORIES(${RUBY_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(test_function.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(test_function.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(example ruby test_function.i test_function.cpp)
SWIG_LINK_LIBRARIES(example ${RUBY_LIBRARY} ${OpenCV_LIBS})