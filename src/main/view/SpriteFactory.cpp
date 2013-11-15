#include "SpriteFactory.h"

#include <SFML/Graphics/Sprite.hpp>

#include "../util/Logger.h"

#define SPRITE_SHEET "assets/sprites.png"
#define SPRITE_SHEET_SPRITE_WIDTH 32
#define SPRITE_SHEET_COLS 4
#define SPRITE_SHEET_ROWS 3

using namespace gs;

SpriteFactory::~SpriteFactory() {
	DBG("Destroyed");
}

void SpriteFactory::init() {
	if (!texture.loadFromFile(SPRITE_SHEET)) {
		ERR("Failed to load texture: " + std::string(SPRITE_SHEET));
	}
}

sf::Sprite SpriteFactory::createSprite(int colIndex, int rowIndex) {
	sf::Sprite sprite;

	// Check supplied indices are in range
	if (colIndex >= 0 && colIndex < SPRITE_SHEET_COLS
			&& rowIndex >= 0 && rowIndex < SPRITE_SHEET_ROWS) {
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(colIndex * SPRITE_SHEET_SPRITE_WIDTH,
				rowIndex * SPRITE_SHEET_SPRITE_WIDTH, SPRITE_SHEET_SPRITE_WIDTH,
				SPRITE_SHEET_SPRITE_WIDTH));
	}

	return sprite;
}
