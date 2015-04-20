/* 
 * File:   GameScreen.h
 * Author: Will Poynter
 *
 * Created on October 10, 2014, 5:14 PM
 */

#ifndef GAMESCREEN_H
#define	GAMESCREEN_H

#include "IGameScreen.h"

#include <map>
#include <list>

#include <SFML/Graphics/Text.hpp>

#include "SpriteFactory.h"
#include "../../IStyleManager.h"
#include "../../../event/IEventManager.hpp"

#include "../../../event/EntityCreatedEvent.hpp"
#include "../../../event/EntityDeletedEvent.hpp"
#include "../../../event/EntityMovedEvent.hpp"
#include "../../../event/ScoreChangedEvent.hpp"

namespace gs {

typedef std::map<short, sf::Sprite> SpriteMap;
typedef std::list<sf::Sprite> SpriteList;

class GameScreen :public IGameScreen, public IEventListener {
public:
	GameScreen(IStyleManagerShPtr, ISpriteFactoryShPtr);
	virtual ~GameScreen();
	
	void update();
	void render(RenderWindowShPtr);
	virtual void onEvent(Event& event);
	
	virtual ScreensEnum getType() const;

private:
	void initHud();

	void onEntityCreated(EntityCreatedEvent& event);
	void onEntityMoved(EntityMovedEvent& event);
	void onEntityDeleted(EntityDeletedEvent& event);
	void onScoreChanged(ScoreChangedEvent& event);
	void onGameEnd();

	void setScore(int score);

	// Draw grid (for debugging)
	void drawGrid(RenderWindowShPtr window);

	IStyleManagerShPtr styleManager;
	ISpriteFactoryShPtr spriteFactory;

	SpriteMap spriteMap;
	SpriteList hudSprites;
	sf::Text levelText;
	sf::Text waveText;
	sf::Text scoreText;
	sf::Text multiText;
	sf::Vertex winLinePoints[2];
};

}

#endif	/* GAMESCREEN_H */

