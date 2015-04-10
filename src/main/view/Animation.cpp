#include "../view/Animation.h"

#include "../app/Globals.h"

using namespace gs;

namespace {

int getLastFrameIndex(int firstFrameColIndex, int numberOfFrames) {
	return firstFrameColIndex + numberOfFrames - 1;
}

}

Animation::Animation(SpriteShPtr _sprite, int _firstFrameRowIndex, int _firstFrameColIndex,
	int _numOfFrames, int _frameIntervalMs,bool _isLooping)
	: sprite(_sprite),
		firstFrameRowIndex(_firstFrameRowIndex),
		firstFrameColIndex(_firstFrameColIndex),
		numberOfFrames(_numOfFrames),
		frameIntervalMs(_frameIntervalMs),
		isLooping(_isLooping),
		elapsedTimeMs(0),
		frameCounter(0),
		state(AnimationState::NOT_RUNNING) {
}

void Animation::start() {
	state = AnimationState::RUNNING;
	elapsedTimeMs = 0;
	frameCounter = 0;
	setFrameCol(firstFrameColIndex);
}

void Animation::stop() {
	state = AnimationState::STOPPING;
}

void Animation::update(int deltaMs) {
	if (state != AnimationState::NOT_RUNNING) {
		elapsedTimeMs += deltaMs;

		if (elapsedTimeMs >= frameIntervalMs) {
			int framesToAdvance = (elapsedTimeMs / frameIntervalMs);
			elapsedTimeMs -= (elapsedTimeMs * framesToAdvance);

			advanceFrame(framesToAdvance);
		}
	}
}

AnimationState Animation::getState() {
	return state;
}

bool Animation::operator==(Animation& animation) {
	return sprite == animation.sprite &&
		firstFrameRowIndex == animation.firstFrameRowIndex &&
		firstFrameColIndex == animation.firstFrameColIndex &&
		numberOfFrames == animation.numberOfFrames &&
		frameIntervalMs == animation.frameIntervalMs &&
		isLooping == animation.isLooping;
}

bool Animation::operator!=(Animation& animation) {
	return !(*this == animation);
}

void Animation::advanceFrame(int framesToAdvance) {
	if (state == AnimationState::STOPPING) {
		state = AnimationState::NOT_RUNNING;
		// Show the last frame of the animation.
		int lastFrameCol = getLastFrameIndex(firstFrameColIndex, numberOfFrames);
		setFrameCol(lastFrameCol);
	} else {
		frameCounter += framesToAdvance;

		if (isLooping) {
			frameCounter = firstFrameColIndex + (frameCounter - firstFrameColIndex) % numberOfFrames;
		} else {
			int lastFrameCol = getLastFrameIndex(firstFrameColIndex, numberOfFrames);

			if (frameCounter > lastFrameCol) {
				state = AnimationState::NOT_RUNNING;
				frameCounter = lastFrameCol;
			}
		}

		setFrameCol(frameCounter);
	}
}

void Animation::setFrameCol(int columnIndex) {
	sprite->setTextureRect(sf::IntRect(columnIndex * GBL::SHEET_SPRITE_WIDTH, firstFrameRowIndex * GBL::SHEET_SPRITE_WIDTH,
			GBL::SHEET_SPRITE_WIDTH, GBL::SHEET_SPRITE_WIDTH));
}
