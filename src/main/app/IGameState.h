#ifndef I_GAME_STATE
#define	I_GAME_STATE

#include <memory>

namespace gs {

class IGameState {
public:
	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

typedef std::shared_ptr<IGameState> IGameStateShPtr;

}

#endif	/* I_GAME_STATE */
