#include "Pch.hpp"
#include "ResourceLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "core/GraphicsManager.hpp"

// call all loading related libraries here

void loadResource(Image& img, string filename) {
	img.filename = filename;
	stbi_set_flip_vertically_on_load(true);
	img.imagedata = stbi_load(filename.c_str(), &img.w, &img.h, &img.ch, 0);
	return;
}

void loadResource(Grid& tilemap, string filename) {
	std::ifstream in(filename);
	ordered_json j = nlohmann::json::parse(in);

	std::vector<std::vector<Gridnode>> temp;
	int rows = 0;
	int cols;
	for (auto& row : j["data"]) {
		std::vector<Gridnode> temprow;
		cols = 0;
		for (auto& cell : row) {
			temprow.push_back(Gridnode{ cell });
			++cols;
		}
		temp.push_back(temprow);
		++rows;
	}
	tilemap.filename = j["mapname"];
	tilemap.cells = std::move(temp);
	tilemap.rows = rows;
	tilemap.cols = cols;
}