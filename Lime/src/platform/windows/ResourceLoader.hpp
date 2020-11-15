#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP
// call all loading related libraries here
#include "Pch.hpp"
#include "ResourceContainers.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
template <typename T>
T loadResource(string filename) {
	LM_TRACE("loading resource...");
}

// templated loader specializations
template <>
Image loadResource<Image>(string filename) {
	Image img;
	img.imagedata = stbi_load(filename.c_str(), &img.w, &img.h, &img.ch, 0);
	return img;
}


#endif // !RESOURCELOADER_HPP
