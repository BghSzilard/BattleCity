#include "Level.h"
#include "ILevelReader.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Return;

using namespace BattleCity::GameLogic;

class MockLevelReader : public ILevelReader {
public:
	MOCK_METHOD(Level, readLevel, (std::string), (override));
};

TEST(LevelTest, LevelReader) {
	MockLevelReader levelReader;

	ON_CALL(levelReader, readLevel("LEVEL1.txt"))
		.WillByDefault(Return(Level(
			Map(std::vector{ std::vector{0 , 0}, std::vector{1 , 2}, std::vector{1 , 2}, }),
			std::vector<std::shared_ptr<Tank>>({ std::make_shared<Tank>(0, 0, Entity::MoveDirection::DOWN) })
	)));

	auto level = levelReader.readLevel("LEVEL1.txt");

	EXPECT_EQ(level.getMap().getWidth(), 2);
	EXPECT_EQ(level.getMap().getHeight(), 3);
	EXPECT_EQ(level.getMap().at(0, 1), 0);
}