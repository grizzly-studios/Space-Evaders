#ifndef I_SPRITE_FACTORY_HPP
#define	I_SPRITE_FACTORY_HPP

#include <memory>
#include <string>

#define SPRITE_SHEET_SPRITE_WIDTH 32
#define SPRITE_SHEET_COLS 4
#define SPRITE_SHEET_ROWS 3

namespace sf {
	class Sprite;
}

namespace gs {

class ISpriteFactory {
public:
	virtual void init(std::string spriteSheetPath) = 0;

	virtual sf::Sprite createSprite(int colIndex, int rowIndex,
			sf::Vector2i size = sf::Vector2i(SPRITE_SHEET_SPRITE_WIDTH,SPRITE_SHEET_SPRITE_WIDTH)) = 0;
};

typedef std::shared_ptr<ISpriteFactory> ISpriteFactoryShPtr;

}

#endif	/* I_SPRITE_FACTORY_HPP */
