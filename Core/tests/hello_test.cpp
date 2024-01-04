#include "Bullet.h"

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}

TEST(BulletTest, BulletMove) {
	Bullet bullet{ Position{0, 0},  GameConfig::MoveDirection::RIGHT, Bullet::BulletType::PlayerBullet };

	bullet.move();

	auto expectedPosition = Position{ 10, 0 };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}