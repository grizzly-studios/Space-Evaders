#include "gtest/gtest.h"

#include "../src/main/logic/Logic.h"

namespace gs {

class MEventManager : public IEventManager {
	bool addListener(EventEnum eventType, IEventListenerPtr listener) {
		return true;
	}
	
	bool fireEvent(Event& event) const {
		return true;
	}
};

}

namespace {

class LogicTest : public ::testing::Test {
protected:
	LogicTest() {}

	virtual ~LogicTest() {}

	virtual void SetUp() {
		em = gs::IEventManagerPtr(new gs::MEventManager);
		logic = gs::ILogicPtr(new gs::Logic(em));
	}

	virtual void TearDown() {}
	
	gs::ILogicPtr logic;
	gs::IEventManagerPtr em;
	
};

TEST_F(LogicTest, AddsNewListener) {
  ASSERT_TRUE(true);
}

}