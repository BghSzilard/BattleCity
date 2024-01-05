#include "Bullet.h"

#include <gtest/gtest.h>

TEST(BulletTest, BulletMoveOnce) {
	Bullet bullet{ Position{0, 0},  GameConfig::MoveDirection::RIGHT, Bullet::BulletType::PlayerBullet };

	bullet.move();

	auto expectedPosition = Position{ 10, 0 };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}


TEST(BulletTest, BulletMoveMultiple) {
	Bullet bullet{ Position{20, 30},  GameConfig::MoveDirection::DOWN, Bullet::BulletType::PlayerBullet };

	bullet.move();
	bullet.move();
	bullet.move();

	auto expectedPosition = Position{ 20, 60 };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}

TEST(BulletTest, BulletDirection) {
	Bullet bullet{ Position{0, 0},  GameConfig::MoveDirection::UP, Bullet::BulletType::PlayerBullet };

	EXPECT_EQ(bullet.getDirection(), GameConfig::MoveDirection::UP);
}

TEST(BulletTest, BulletChangeDirectionAndMove) {
	Bullet bullet{ Position{50, 80},  GameConfig::MoveDirection::LEFT, Bullet::BulletType::PlayerBullet };

	bullet.move();

	auto expectedPosition = Position{ 40, 80 };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);

	bullet.setDirection(GameConfig::MoveDirection::DOWN);

	bullet.move();

	expectedPosition = Position{ 40, 90 };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}