#include "Map.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

TEST(MapTest, MapSizes) {
	BattleCity::Matrix<int> tiles = std::vector{
		std::vector{0 , 0},
		std::vector{1 , 2},
		std::vector{1 , 2},
	};
	BattleCity::GameLogic::Map map{ tiles };

	EXPECT_EQ(map.getWidth(), 2);
	EXPECT_EQ(map.getHeight(), 3);
}

TEST(MapTest, MapTilesAt) {
	BattleCity::Matrix<int> tiles = std::vector{
		std::vector{0 , 0},
		std::vector{1 , 2},
		std::vector{1 , 2},
	};
	BattleCity::GameLogic::Map map{ tiles };

	EXPECT_EQ(map.at(1, 1), 2);
}

TEST(MapTest, MapTilesAtOutOfRange) {
	BattleCity::Matrix<int> tiles = std::vector{
		std::vector{0 , 0},
		std::vector{1 , 2},
		std::vector{1 , 2},
	};
	BattleCity::GameLogic::Map map{ tiles };

	EXPECT_EQ(map.at(1, 1), 2);
}