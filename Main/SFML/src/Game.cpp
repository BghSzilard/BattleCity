#include "Game.h"
#include "SFMLMenu.h"
#include "GameConfig.h"
#include "SFMLBullet.h"
#include "SFMLEagle.h"

namespace BattleCity
{
    Game::Game()
            : m_tileMap()
    {
//		std::srand(unsigned(std::time(nullptr)));
        // hardcoded screen size so that map nicely fills the screen (can be modified later)
        m_window.create(sf::VideoMode(1024, 1024), GameConfig::WINDOW_NAME);
        m_window.setFramerateLimit(GameConfig::FRAME_LIMIT);

        m_state = GameState::SFMLMenu;
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
        SFMLBullet bullet(0, 500, GameConfig::MoveDirection::RIGHT, Bullet::BulletType::PlayerBullet);
        SFMLEagle eagle;

        while (m_window.pollEvent(event))
        {
            // Press ESC or the X button in the window
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                m_state = GameState::EXIT;
        }


        // TODO: Check bounds of screen
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_playerTank.move(-1.0f * GameConfig::TANK_SPEED, 0);
            m_playerTank.setRotation(270.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_playerTank.move(1.0f * GameConfig::TANK_SPEED, 0);
            m_playerTank.setRotation(90.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_playerTank.move(0, -1.f * GameConfig::TANK_SPEED);
            m_playerTank.setRotation(0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_playerTank.move(0, 1.f * GameConfig::TANK_SPEED);
            m_playerTank.setRotation(180.f);
        }

        m_window.clear();
        m_window.draw(m_tileMap);
        m_window.draw(m_playerTank);
        m_window.draw(bullet);
        m_window.draw(eagle);
        m_window.display();
    }

}