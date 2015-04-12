#include "gtest/gtest.h"

#include <cmath>

#include "../src/main/logic/MobileEntity.h"

namespace gs {

class OpenMobileEntity : public MobileEntity {
public:
	OpenMobileEntity() {}
	OpenMobileEntity(const MobileEntity& orig) : MobileEntity(orig) {}
	virtual ~OpenMobileEntity() {}
	
	sf::Vector2f getVector(const double & dt) const {
		return MobileEntity::getVector(dt);
	}
};

}

namespace {

class MobileEntityTest : public ::testing::Test {
protected:
	MobileEntityTest() {}

	virtual ~MobileEntityTest() {}

	virtual void SetUp() {
		me.setMagnitude(200.f/1000000.f);
		me.setDirection(gs::DOWN);
	}

	virtual void TearDown() {}
	
	gs::MobileEntity me;
	
};

TEST_F(MobileEntityTest, SetGet) {
	EXPECT_EQ(me.getDirection(), gs::DOWN);
	EXPECT_EQ(me.getMagnitude(), 200.f/1000000.f);
	me.setDirection(gs::UP);
	EXPECT_EQ(me.getDirection(), gs::UP);
	me.setMagnitude(200.f/10000.f);
	EXPECT_EQ(me.getMagnitude(), 200.f/10000.f);
	me.setDirection(gs::LEFT);
	EXPECT_EQ(me.getDirection(), gs::LEFT);
	me.setMagnitude(4000.f/10000.f);
	EXPECT_EQ(me.getMagnitude(), 4000.f/10000.f);
	me.setDirection(gs::RIGHT);
	EXPECT_EQ(me.getDirection(), gs::RIGHT);
	me.setMagnitude(6000.f/1000.f);
	EXPECT_EQ(me.getMagnitude(), 6000.f/1000.f);
	me.setPosition(sf::Vector2f(50, 60));
	EXPECT_EQ(me.getPosition(), sf::Vector2f(50, 60));
}

TEST_F(MobileEntityTest, CopyConstructor) {
	gs::MobileEntity newMe(me);
	EXPECT_EQ(newMe.getDirection(), gs::DOWN);
	EXPECT_EQ(newMe.getMagnitude(), 200.f/1000000.f);
}

TEST_F(MobileEntityTest, CopyViaEquals) {
	gs::MobileEntity newMe = me;
	EXPECT_EQ(newMe.getDirection(), gs::DOWN);
	EXPECT_EQ(newMe.getMagnitude(), 200.f/1000000.f);
	newMe.setMagnitude(800.f/1000000.f);
	EXPECT_EQ(newMe.getMagnitude(), 800.f/1000000.f);
	EXPECT_EQ(me.getMagnitude(), 200.f/1000000.f);
}

TEST_F(MobileEntityTest, GetVectorUp) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::UP);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, -500);
}

TEST_F(MobileEntityTest, GetVectorUpRight) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::UPRIGHT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	float expected = sqrt(pow(500,2)/2);
	EXPECT_EQ(vector.x, expected);
	EXPECT_EQ(vector.y, -expected);
}

TEST_F(MobileEntityTest, GetVectorRight) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::RIGHT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	EXPECT_EQ(vector.x, 500);
	EXPECT_EQ(vector.y, 0);
}

TEST_F(MobileEntityTest, GetVectorDownRight) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::DOWNRIGHT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	float expected = sqrt(pow(500,2)/2);
	EXPECT_EQ(vector.x, expected);
	EXPECT_EQ(vector.y, expected);
}

TEST_F(MobileEntityTest, GetVectorDown) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::DOWN);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	EXPECT_EQ(vector.x, 0);
	EXPECT_EQ(vector.y, 500);
}

TEST_F(MobileEntityTest, GetVectorDownLeft) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::DOWNLEFT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	float expected = sqrt(pow(500,2)/2);
	EXPECT_EQ(vector.x, -expected);
	EXPECT_EQ(vector.y, expected);
}

TEST_F(MobileEntityTest, GetVectorLeft) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::LEFT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	EXPECT_EQ(vector.x, -500);
	EXPECT_EQ(vector.y, 0);
}

TEST_F(MobileEntityTest, GetVectorUpLeft) {
	gs::OpenMobileEntity ome;
	ome.setDirection(gs::UPLEFT);
	ome.setMagnitude(100);
	sf::Vector2f vector = ome.getVector(5);
	float expected = sqrt(pow(500,2)/2);
	EXPECT_EQ(vector.x, -expected);
	EXPECT_EQ(vector.y, -expected);
}

TEST_F(MobileEntityTest, MoveFromOrigin) {
	me.setDirection(gs::UP);
	me.setMagnitude(20);
	ASSERT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, 0);
	me.move(30);
	ASSERT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, -600);
}

TEST_F(MobileEntityTest, MoveFromNonOrigin) {
	me.setDirection(gs::UP);
	me.setMagnitude(20);
	me.setPosition(sf::Vector2f(90,-20));
	EXPECT_EQ(me.getPosition().x, 90);
	ASSERT_EQ(me.getPosition().y, -20);
	me.move(30);
	EXPECT_EQ(me.getPosition().x, 90);
	ASSERT_EQ(me.getPosition().y, -620);
}

TEST_F(MobileEntityTest, MultipleMovements) {
	me.setDirection(gs::UP);
	me.setMagnitude(20);
	me.move(10);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, -200);
	me.move(30);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, -800);
	me.setDirection(gs::RIGHT);
	me.move(15);
	EXPECT_EQ(me.getPosition().x, 300);
	ASSERT_EQ(me.getPosition().y, -800);
}

TEST_F(MobileEntityTest, MoveUp) {
	me.setDirection(gs::UP);
	me.setMagnitude(30);
	me.move(15);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, -450);
	me.move(50);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, -1950);
}

TEST_F(MobileEntityTest, MoveUpRight) {
	me.setDirection(gs::UPRIGHT);
	me.setMagnitude(30);
	me.move(15);
	float expected_1st = sqrt(pow(30*15,2)/2);
	EXPECT_EQ(me.getPosition().x, expected_1st);
	ASSERT_EQ(me.getPosition().y, -expected_1st);
	me.move(50);
	float expected_2nd = sqrt(pow(30*50,2)/2);
	EXPECT_EQ(me.getPosition().x, expected_1st + expected_2nd);
	ASSERT_EQ(me.getPosition().y, -expected_1st - expected_2nd);
}

TEST_F(MobileEntityTest, MoveRight) {
	me.setDirection(gs::RIGHT);
	me.setMagnitude(30);
	me.move(15);
	EXPECT_EQ(me.getPosition().x, 450);
	ASSERT_EQ(me.getPosition().y, 0);
	me.move(50);
	EXPECT_EQ(me.getPosition().x, 1950);
	ASSERT_EQ(me.getPosition().y, 0);
}

TEST_F(MobileEntityTest, MoveDownRight) {
	me.setDirection(gs::DOWNRIGHT);
	me.setMagnitude(30);
	me.move(15);
	float expected_1st = sqrt(pow(30*15,2)/2);
	EXPECT_EQ(me.getPosition().x, expected_1st);
	ASSERT_EQ(me.getPosition().y, expected_1st);
	me.move(50);
	float expected_2nd = sqrt(pow(30*50,2)/2);
	EXPECT_EQ(me.getPosition().x, expected_1st + expected_2nd);
	ASSERT_EQ(me.getPosition().y, expected_1st + expected_2nd);
}

TEST_F(MobileEntityTest, MoveDown) {
	me.setDirection(gs::DOWN);
	me.setMagnitude(30);
	me.move(15);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, 450);
	me.move(50);
	EXPECT_EQ(me.getPosition().x, 0);
	ASSERT_EQ(me.getPosition().y, 1950);
}

TEST_F(MobileEntityTest, MoveDownLeft) {
	me.setDirection(gs::DOWNLEFT);
	me.setMagnitude(30);
	me.move(15);
	float expected_1st = sqrt(pow(30*15,2)/2);
	EXPECT_EQ(me.getPosition().x, -expected_1st);
	ASSERT_EQ(me.getPosition().y, expected_1st);
	me.move(50);
	float expected_2nd = sqrt(pow(30*50,2)/2);
	EXPECT_EQ(me.getPosition().x, -expected_1st - expected_2nd);
	ASSERT_EQ(me.getPosition().y, expected_1st + expected_2nd);
}

TEST_F(MobileEntityTest, MoveLeft) {
	me.setDirection(gs::LEFT);
	me.setMagnitude(30);
	me.move(15);
	EXPECT_EQ(me.getPosition().x, -450);
	ASSERT_EQ(me.getPosition().y, 0);
	me.move(50);
	EXPECT_EQ(me.getPosition().x, -1950);
	ASSERT_EQ(me.getPosition().y, 0);
}

TEST_F(MobileEntityTest, MoveUpLeft) {
	me.setDirection(gs::UPLEFT);
	me.setMagnitude(30);
	me.move(15);
	float expected_1st = sqrt(pow(30*15,2)/2);
	EXPECT_EQ(me.getPosition().x, -expected_1st);
	ASSERT_EQ(me.getPosition().y, -expected_1st);
	me.move(50);
	float expected_2nd = sqrt(pow(30*50,2)/2);
	EXPECT_EQ(me.getPosition().x, -expected_1st - expected_2nd);
	ASSERT_EQ(me.getPosition().y, -expected_1st - expected_2nd);
}

}