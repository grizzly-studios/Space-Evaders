#ifndef SPRITE_FACTORY_H
#define SPRITE_FACTORY_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ISpriteFactory.hpp"

namespace gs {

class SpriteFactory : public ISpriteFactory {
public:
	virtual ~SpriteFactory();

	virtual void init(std::string spriteSheetPath);
	virtual sf::Sprite createSprite(int colIndex, int rowIndex,
			sf::Vector2i size = sf::Vector2i(SPRITE_SHEET_SPRITE_WIDTH,SPRITE_SHEET_SPRITE_WIDTH));

private:
	sf::Texture texture;
};

}

#endif /* SPRITE_FACTORY_H */
