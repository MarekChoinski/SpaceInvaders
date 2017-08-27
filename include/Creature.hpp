#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.hpp"

class Creature : public sf::Drawable
{
    public:
        //ctors
        Creature();
        //Creature(sf::Vector2f i_position, unsigned short int i_points);

        //move creature
        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f &offset);

        //setters and getters
        void setPosition(const sf::Vector2f& i_position) { shape.setPosition(i_position); }
        sf::Vector2f getPosition() const { return shape.getPosition(); }

        void setPoints(const unsigned short int& i_points) { m_points=i_points; }
        int getPoints() const { return m_points; }

        sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }

        void setTexture(const sf::Texture& i_texture) { shape.setTexture(i_texture); }

        bool isAlive() const { return alive; }

        void kill() { alive = false; Player::totalScore += this->m_points;}

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:

        unsigned short int m_points;
        //TODO shape name
        sf::Sprite shape;
        bool alive;
};

#endif // CREATURE_HPP
