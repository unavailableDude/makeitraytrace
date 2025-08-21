#pragma once


#include <cstdint>
#include <vector>

#include "Color4.hpp"
#include "Canvas.hpp"


namespace MIRT {


class Renderer {
public:
	Renderer(uint16_t width, uint16_t height);

	Canvas MakeArt();

	uint16_t GetWidth() const;
	uint16_t GetHeight() const;
	void SetImageDimensions(uint16_t width, uint16_t height);

private:
	uint16_t _width;
	uint16_t _height;
	float _aspectRatio;
};

}// namespace MIRT