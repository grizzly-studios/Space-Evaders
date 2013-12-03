#ifndef SPRITE_FACTORY_H
#define SPRITE_FACTORY_H

#include <SFML/Graphics/Texture.hpp>

#include "ISpriteFactory.hpp"

namespace gs {

class SpriteFactory : public ISpriteFactory {
public:
	virtual ~SpriteFactory();

	virtual void init();
	virtual sf::Sprite createSprite(int colIndex, int rowIndex);

private:
	sf::Texture texture;
};

}

#endif /* SPRITE_FACTORY_H */
