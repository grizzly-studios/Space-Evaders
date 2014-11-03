#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../main/logic/Logic.h"
#include "../../main/event/IEventManager.hpp"
#include "../../main/event/GameEndEvent.h"

using namespace gs;

class MockEventManger : public IEventManager {
public:
	MOCK_METHOD2(addListener, bool(EventEnum eventType, IEventListenerPtr listener));
	MOCK_CONST_METHOD1(fireEvent, bool(Event& event));
};

bool IsMenuEvent(Event& event) {
	bool isMenuEvent = false;

	if (GAME_STATE_CHANGED_EVENT == event.getType()) {
		GameStateChangedEvent gameStateChangedEvent = (GameStateChangedEvent&) event;
		isMenuEvent = (MENU == gameStateChangedEvent.getState());
	}

	return isMenuEvent;
}

TEST(Logic, onEvent_firesMenuGameStateEventGivenOnGameEndEvent) {
	MockEventManger *pMockEventManger = new MockEventManger;
	IEventManagerPtr mockEventManger(pMockEventManger);

	EXPECT_CALL(*pMockEventManger, fireEvent(::testing::Truly(IsMenuEvent)));

	Logic logic(mockEventManger);

	GameEndEvent gameEndEvent;
	logic.onEvent(gameEndEvent);
}
