#include "gtest/gtest.h"

#include "../src/main/event/EventManager.h"

namespace gs {

class MEventListener : public gs::IEventListener {
private:
	int localCounter;
public:
	MEventListener() : localCounter(0) {}
	virtual ~MEventListener() {}
	
	void onEvent(gs::Event& event) {
		localCounter++;
		globalCounter++;
	}
	
	int getLocalCount() {
		return localCounter;
	}
	
	static int globalCounter;
};

int MEventListener::globalCounter = 0;

class MEvent : public Event {
public:
	EventEnum getType() const {
		return GAME_START_EVENT;
	}
};

}

namespace {

class EventManagerTest : public ::testing::Test {
protected:
	EventManagerTest() {}

	virtual ~EventManagerTest() {}

	virtual void SetUp() {
		el1 = std::shared_ptr<gs::IEventListener>(new gs::MEventListener());
		el2 = std::shared_ptr<gs::IEventListener>(new gs::MEventListener());
		el3 = std::shared_ptr<gs::IEventListener>(new gs::MEventListener());
		el4 = std::shared_ptr<gs::IEventListener>(new gs::MEventListener());
	}

	virtual void TearDown() {}
	
	gs::EventManager em1;
	gs::EventManager em2;
	gs::EventManager em3;
	
	std::shared_ptr<gs::IEventListener> el1;
	std::shared_ptr<gs::IEventListener> el2;
	std::shared_ptr<gs::IEventListener> el3;
	std::shared_ptr<gs::IEventListener> el4;
};

TEST_F(EventManagerTest, AddsNewListener) {
  ASSERT_TRUE(em1.addListener(
	  gs::GAME_STATE_CHANGED_EVENT,el1));
}

TEST_F(EventManagerTest, ResusableELDifferentEM) {
  ASSERT_TRUE(em2.addListener(
	  gs::GAME_STATE_CHANGED_EVENT,el1));
}

TEST_F(EventManagerTest, ResusableELDifferentEvent) {
  ASSERT_TRUE(em2.addListener(
	  gs::GAME_START_EVENT,el1));
}

TEST_F(EventManagerTest, DifferentELDifferentLock) {
  EXPECT_FALSE(el1 == el2);
  EXPECT_NE(el1.get(), el2.get());
}

TEST_F(EventManagerTest, DifferentEL) {
  ASSERT_TRUE(em2.addListener(
		gs::GAME_START_EVENT,el2));
  ASSERT_TRUE(em2.addListener(
		gs::GAME_START_EVENT,el3));
  ASSERT_TRUE(em2.addListener(
		gs::GAME_START_EVENT,el4));
}

TEST_F(EventManagerTest, SameELImediately) {
	ASSERT_TRUE(em3.addListener(
		gs::GAME_START_EVENT,el2));
	ASSERT_FALSE(em3.addListener(
		gs::GAME_START_EVENT,el2));
}

TEST_F(EventManagerTest, SameELOutOfSequence) {
	ASSERT_TRUE(em3.addListener(
		gs::GAME_START_EVENT,el3));
	ASSERT_TRUE(em3.addListener(
		gs::GAME_START_EVENT,el4));
	ASSERT_FALSE(em3.addListener(
		gs::GAME_START_EVENT,el3));
}

TEST_F(EventManagerTest, 1Listener1Event2Fire) {
	EXPECT_TRUE(em1.addListener(
		gs::GAME_START_EVENT,el1));
	gs::MEvent event;
	ASSERT_TRUE(em1.fireEvent(
		event));
	EXPECT_EQ(1, gs::MEventListener::globalCounter);
	EXPECT_EQ(1, std::static_pointer_cast<gs::MEventListener>(el1)->getLocalCount());
	ASSERT_TRUE(em1.fireEvent(
		event));
	EXPECT_EQ(2, gs::MEventListener::globalCounter);
	EXPECT_EQ(2, std::static_pointer_cast<gs::MEventListener>(el1)->getLocalCount());
}

}