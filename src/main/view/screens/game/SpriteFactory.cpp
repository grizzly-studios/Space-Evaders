#include "SpriteFactory.h"

#include <cmath>

#include <SFML/Graphics/Sprite.hpp>

#include "../../../util/Logger.h"

#define SPRITE_SHEET "assets/sprites.png"

using namespace gs;

SpriteFactory::~SpriteFactory() {
	DBG << "Destroyed" << std::endl;
}

void SpriteFactory::init() {
	if (!texture.loadFromFile(SPRITE_SHEET)) {
		ERR << "Failed to load texture: " << std::string(SPRITE_SHEET) << std::endl;
	}
}

sf::Sprite SpriteFactory::createSprite(int colIndex, int rowIndex, sf::Vector2i size) {
	sf::Sprite sprite;

	sf::Vector2i offset;
	offset.x = round((SPRITE_SHEET_SPRITE_WIDTH - size.x) / 2);
	offset.y = round((SPRITE_SHEET_SPRITE_WIDTH - size.y) / 2);

	// Check supplied indices are in range
	if (colIndex >= 0 && colIndex < SPRITE_SHEET_COLS
			&& rowIndex >= 0 && rowIndex < SPRITE_SHEET_ROWS) {
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect((colIndex * SPRITE_SHEET_SPRITE_WIDTH) + offset.x,
				(rowIndex * SPRITE_SHEET_SPRITE_WIDTH) + offset.y, size.x,size.y));
	}

	return sprite;
}
