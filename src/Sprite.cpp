#include "Sprite.h"

//long functions for triangle shape and sprite



//
	// inside - check if point is inside player (can be an image or TriangleShape if no image)
	//
bool Sprite::inside(const glm::vec3 p) {

	// if there is no sprite image attached, then just use triangle case.
	//
	if (!bShowImage) {
		return TriangleShape::inside(p);
	}

	// if sprite image attached, then first check if point is inside bounds of image
	// in object space.  If point is inside bounds, then make sure the point is in
	// opaque part of image.
	//
	glm::vec3 s = glm::inverse(getMatrix()) * glm::vec4(p, 1);
	int w = spriteImage.getWidth();
	int h = spriteImage.getHeight();
	if (s.x > -w / 2 && s.x < w / 2 && s.y > -h / 2 && s.y < h / 2) {
		int x = s.x + w / 2;
		int y = s.y + h / 2;
		ofColor color = spriteImage.getColor(x, y);
		return (color.a != 0);   // check if color is opaque (not the transparent background)
	}
	else return false;
}
