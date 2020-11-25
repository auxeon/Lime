#include "Pch.hpp"
#include "ResourceLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "core/GraphicsManager.hpp"

// call all loading related libraries here

void loadResource(Image& img, string filename) {
	stbi_set_flip_vertically_on_load(true);
	img.imagedata = stbi_load(filename.c_str(), &img.w, &img.h, &img.ch, 0);
	return;
}