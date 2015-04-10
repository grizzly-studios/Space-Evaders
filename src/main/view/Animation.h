#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

namespace gs {

typedef std::shared_ptr<sf::Sprite> SpriteShPtr;

enum class AnimationState {
	NOT_RUNNING,
	RUNNING,
	STOPPING
};

class Animation {
public:
	Animation(SpriteShPtr _sprite, int _firstFrameRowIndex, int _firstFrameColIndex,
		int _numOfFrames, int _frameIntervalMs, bool _isLooping);

	void start();
	void stop();
	void update(int deltaMs);

	AnimationState getState();

	bool operator==(Animation& animation);
	bool operator!=(Animation& animation);

private:
	void advanceFrame(int framesToAdvance);
	void setFrameCol(int columnIndex);

	SpriteShPtr sprite;
	int firstFrameRowIndex;
	int firstFrameColIndex;
	int numberOfFrames;
	int frameIntervalMs;
	bool isLooping;
	int elapsedTimeMs;
	int frameCounter;
	AnimationState state;
};

typedef std::shared_ptr<Animation> AnimationShPtr;

}

#endif // ANIMATION_H
