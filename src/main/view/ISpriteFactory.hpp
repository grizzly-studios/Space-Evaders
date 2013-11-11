#ifndef I_SPRITE_FACTORY_HPP
#define	I_SPRITE_FACTORY_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/Sprite.hpp>

namespace gs {

class ISpriteFactory {
public:
	virtual void init() = 0;

	virtual sf::Sprite createSprite(int colIndex, int rowIndex) = 0;
};

typedef std::shared_ptr<ISpriteFactory> ISpriteFactoryShPtr;

}

#endif	/* I_SPRITE_FACTORY_HPP */
