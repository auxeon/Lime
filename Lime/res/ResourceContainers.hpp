#ifndef RESOURCECONTAINERS_HPP
#define RESOURCECONTAINERS_HPP
#include "Pch.hpp"
// define all the different resource container classes here
// including audio
class Image {
public:
	string filename;
	unsigned char* imagedata;
	int w; // width
	int h; // height
	int ch; // channels
};
#endif // !RESOURCECONTAINERS_HPP
