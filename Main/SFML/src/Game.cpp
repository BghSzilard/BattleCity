#include "Game.h"
#include "SFMLMenu.h"
#include "GameConfig.h"
#include "SFMLBullet.h"
#include "SFMLEagle.h"

#include <algorithm>

namespace BattleCity
{
    Game::Game(TextureManager &textureManager)
            : m_textureManager(textureManager), m_tileMap(m_textureManager),
              m_playerTank(m_textureManager, {GameConfig::INITIAL_TANK_POS_X, GameConfig::INITIAL_TANK_POS_Y})
    {
//		std::srand(unsigned(std::time(nullptr)));
        // hardcoded screen size so that map nicely fills the screen (can be modified later)
        m_window.create(sf::VideoMode(1024, 1024), GameConfig::WINDOW_NAME);
        m_window.setFramerateLimit(GameConfig::FRAME_LIMIT);

        m_state = GameState::SFMLMenu;

        m_playerTank.setOnBulletShot([this](const SFML::SFMLTank &, SFMLBullet &&bullet)
                                     {
                                         m_playerBullet = std::make_unique<SFMLBullet>(std::move(bullet));
                                     });

        m_enemyTanks.emplace_back(SFML::SFMLTank(textureManager, {150.f, 150.f}));

        m_enemyTanks[0].setOnBulletShot([this](const SFML::SFMLTank &, SFMLBullet &&bullet)
                                        {
                                            bullets.emplace_back(std::move(bullet));
                                        });
    }

    void Game::runGame()
    {
        while (m_state != GameState::EXIT)
        {
            switch (m_state)
            {
                case GameState::SFMLMenu:
                    menu();
                    break;
                case GameState::SinglePlayerGame:
                    singlePlayer();
                    break;
            }
        }
    }

    void Game::menu()
    {
        // Create a Menu with the window reference
        SFMLMenu menu(m_window);

        // Main game loop
        while (m_window.isOpen())
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up)
                {
                    menu.changeMenuOption(SFMLMenu::MenuDirection::Upward);
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down)
                {
                    menu.changeMenuOption(SFMLMenu::MenuDirection::Downward);
                } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Enter)
                {
                    int chosenOption = menu.getChosenOption();
                    m_state = determineGameState(chosenOption);
                    return;
                }
            }

            // Clear the window
            m_window.clear();

            // Draw the menu
            menu.draw();

            // Display the window
            m_window.display();
        }

        m_state = GameState::EXIT;
    }

    BattleCity::Game::GameState Game::determineGameState(int option)
    {
        switch (option)
        {
            case 0:
                return BattleCity::Game::GameState::SinglePlayerGame;
                break;
            case 1:
                return BattleCity::Game::GameState::TwoPlayerGame;
                break;
            case 2:
                return BattleCity::Game::GameState::EXIT;
                break;
            default:
                return BattleCity::Game::GameState::EXIT;
        }
    }


    void Game::singlePlayer()
    {
        sf::Event event;
        SFMLEagle eagle;

        while (m_window.pollEvent(event))
        {
            // Press ESC or the X button in the window
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                m_state = GameState::EXIT;
        }

        // TODO: Check bounds of screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_playerTank.setMoveDirection(GameConfig::MoveDirection::LEFT);
            m_playerTank.moveTank(-1.0f * GameConfig::TANK_SPEED, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_playerTank.setMoveDirection(GameConfig::MoveDirection::RIGHT);
            m_playerTank.moveTank(1.0f * GameConfig::TANK_SPEED, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_playerTank.setMoveDirection(GameConfig::MoveDirection::UP);
            m_playerTank.moveTank(0, -1.f * GameConfig::TANK_SPEED);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_playerTank.setMoveDirection(GameConfig::MoveDirection::DOWN);
            m_playerTank.moveTank(0, 1.f * GameConfig::TANK_SPEED);
            m_enemyTanks[0].shootBullet();
        }
        if (!m_playerBullet && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_playerTank.shootBullet();
        }

        m_window.clear();
        m_window.draw(m_tileMap);
        m_window.draw(m_playerTank);
        for (auto &tank: m_enemyTanks)
        {
            m_window.draw(tank);
        }
        if (m_playerBullet)
        {
            m_window.draw(*m_playerBullet);
            m_playerBullet->move();
        }
        m_window.draw(eagle);
        for (auto &bullet: bullets)
        {
            if (bulletAlive(bullet))
            {
                bullet.move();
                m_window.draw(bullet);
            }
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                                     [this](const SFMLBullet &bullet)
                                     { return !bulletAlive(bullet); }),
                      bullets.end());


        m_window.display();

        if (m_playerBullet && !bulletAlive(*m_playerBullet))
            m_playerBullet = nullptr;
    }

    bool Game::bulletAlive(const SFMLBullet &bullet)
    {
        float xPos = bullet.getPosition().x;
        float yPos = bullet.getPosition().y;
        return (xPos >= 0 && xPos < GameConfig::SCREEN_WIDTH) && (yPos >= 0 && yPos < GameConfig::SCREEN_HEIGHT);
    }
}