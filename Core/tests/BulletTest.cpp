#include "Bullet.h"

#include <gtest/gtest.h>

TEST(BulletTest, BulletMoveOnce) {
	auto originalPosition = Position{ 0, 0 };
	Bullet bullet{ originalPosition, GameConfig::MoveDirection::RIGHT, Bullet::BulletType::PlayerBullet };

	bullet.move();

	auto bulletSpeed = bullet.getSpeed();
	auto expectedPosition = Position{ originalPosition.x + bulletSpeed, originalPosition.y };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}


TEST(BulletTest, BulletMoveMultiple) {
	auto originalPosition = Position{ 20, 30 };
	Bullet bullet{ originalPosition, GameConfig::MoveDirection::DOWN, Bullet::BulletType::PlayerBullet };

	bullet.move();
	bullet.move();
	bullet.move();

	auto bulletSpeed = bullet.getSpeed();
	auto expectedPosition = Position{ originalPosition.x, originalPosition.y + 3 * bulletSpeed };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}

TEST(BulletTest, BulletDirection) {
	Bullet bullet{ Position{0, 0}, GameConfig::MoveDirection::UP, Bullet::BulletType::PlayerBullet };

	EXPECT_EQ(bullet.getDirection(), GameConfig::MoveDirection::UP);
}

TEST(BulletTest, BulletChangeDirectionAndMove) {
	auto originalPosition = Position{ 50, 80 };
	Bullet bullet{ originalPosition, GameConfig::MoveDirection::LEFT, Bullet::BulletType::PlayerBullet };

	bullet.move();

	auto bulletSpeed = bullet.getSpeed();

	auto expectedPosition = Position{ originalPosition.x - bulletSpeed, originalPosition.y };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);

	bullet.setDirection(GameConfig::MoveDirection::DOWN);

	bullet.move();

	expectedPosition = Position{ originalPosition.x - bulletSpeed, originalPosition.y + bulletSpeed };

	EXPECT_EQ(bullet.getPosition().x, expectedPosition.x);
	EXPECT_EQ(bullet.getPosition().y, expectedPosition.y);
}