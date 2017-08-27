#include "Game.hpp"


Game::Game()
{
    m_window.create(sf::VideoMode(640, 480), "Space invaders");//, sf::Style::Fullscreen);

    m_window.setFramerateLimit(60);
    m_window.setActive(false);

    m_window.setMouseCursorVisible(false);

}

void Game::start()
{
    m_window.setActive(false);
    std::thread thr_d([=]{drawing();});
    thr_d.detach();

        while (m_window.isOpen())
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                events(event);
                player.control(event);
            }sf::sleep(sf::milliseconds(m_event_delay));
        }
}

void Game::drawing()
{

    while (m_window.isOpen()) {
            m_window.setActive(true);

            m_window.clear(sf::Color::Black);

            m_window.draw(player);
            m_window.draw(creatures);
            m_window.draw(bullets);

            m_window.display();

  }
}

void Game::events(sf::Event event)
{
    if (event.type == sf::Event::Closed)
                m_window.close();

    if ((event.type == sf::Event::KeyPressed) && (event.key.code==sf::Keyboard::Escape))
                m_window.close();
}
