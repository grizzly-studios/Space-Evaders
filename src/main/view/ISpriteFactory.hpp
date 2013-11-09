#ifndef I_SPRITE_FACTORY_HPP
#define	I_SPRITE_FACTORY_HPP

#include <tr1/memory>
#include <string>

#include <SFML/Graphics/Sprite.hpp>

namespace gs {

class ISpriteFactory {
public:
	virtual void init() = 0;

	virtual sf::Sprite createSprite(int colIndex, int rowIndex) = 0;
};

typedef std::tr1::shared_ptr<ISpriteFactory> ISpriteFactoryShPtr;

}

#endif	/* I_SPRITE_FACTORY_HPP */
