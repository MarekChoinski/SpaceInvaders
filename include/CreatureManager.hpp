#ifndef CREATUREMANAGER_HPP
#define CREATUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "Creature.hpp"
#include "Bullet.hpp"

class CreatureManager : public sf::Drawable
{
    public:
        CreatureManager();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        //function used in thread
        void motion();

        enum class Direction : char
        {
            right,
            left
        };

        void moveCreatures(CreatureManager::Direction direction);
        void animateCreatures();
        void setDirectionOfCreatures();
        //function used in thread
        void checkCollisions();

        void goLower();

        Direction m_direction;
        bool m_isFirstTexture;

        std::array<std::array<Creature, 11>, 5> creature;

        const sf::Vector2f sizeOfCreature{24.f, 16.f};
        const sf::Vector2f spaceBeetwen {10.f, 15.f};

        //starting position
        const float m_leftMargin = (640-(11*sizeOfCreature.x + 10*spaceBeetwen.x))/2;
        const float m_upMargin = 100;

        //amount of pixel taken every move
        const int m_step = 10;
        const int m_move_delay = 100;

        const int m_lower_step = 7;

        int getMostLeft();
        int getMostRight();

        std::pair <sf::Texture, sf::Texture> tx_1_row;
        std::pair <sf::Texture, sf::Texture> tx_2_row;
        std::pair <sf::Texture, sf::Texture> tx_3_row;
};

#endif // CREATUREMANAGER_HPP
