#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"

class Creature : public sf::Sprite
{
    public:
        //ctors
        Creature();
        //Creature(sf::Vector2f i_position, unsigned short int i_points);

        void setPoints(const unsigned short int& i_points) { m_points=i_points; }
        int getPoints() const { return m_points; }

        bool isAlive() const { return alive; }

        void kill() { alive = false; Player::totalScore += this->m_points;}


        bool isShootable() const { return this->shootable; };
        void setShootable(bool i_shootable) { this->shootable = i_shootable; };

    private:

        unsigned short int m_points;
        bool alive;
        bool shootable;
};

#endif // CREATURE_HPP
