#ifndef COLORS_HPP
#define COLORS_HPP
#include "Pch.hpp"

namespace colors {
	// converters
	// rgba(0,0,0,0) - rgba(255,255,255,255)
	LMVec4 rgba255(unsigned int r = 0, unsigned int g = 0, unsigned int b = 0, unsigned int a = 255) {
		LMVec4 colors;
		r = std::min(r, 255U);
		g = std::min(g, 255U);
		b = std::min(b, 255U);
		a = std::min(a, 255U);

		colors.x = (float)r / 255;
		colors.y = (float)g / 255;
		colors.z = (float)b / 255;
		colors.w = (float)a / 255;

		return colors;
	}

	//colors
	LMVec4 emerald = rgba255(39, 174, 96, 255);




}

#endif // !COLORS_HPP
