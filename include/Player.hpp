#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "Bullet.hpp"

class Player : public sf::Sprite
{
    public:
        static int totalScore;
        Player();

        void control(const sf::Event &event);

    private:

        const sf::Vector2f sizeOfPlayer = {30.f, 16.f};

        //function used in thread
        void checkJoystickMove();

        void shoot();

        sf::Texture tx_player;
        //m_speed must be divider of 640
        const int m_speed = 10;

        //TODO delay should be dependant on m_speed
        //delay for checking axis of pad. More means slower player
        const int m_joystick_delay=30;
        //when pad is disconnected there is infinity loop checking if it is connected again
        const int m_disconnected_joystick_delay=300;
};

#endif // PLAYER_HPP
