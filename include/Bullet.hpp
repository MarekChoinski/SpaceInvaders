#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

class Bullet : public sf::Drawable
{
    public:
        Bullet();
        static void newBullet(sf::Vector2f whereShooted);
        static sf::Vector2f getSize() { return sizeOfBullet; }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        static std::vector<sf::FloatRect> getAllBounds();
        static std::vector<sf::RectangleShape> bullets; //TODO friend?

    private:
        //static int bulletCount;


        static const sf::Vector2f sizeOfBullet;
        //function used in thread
        void moveAll();
        static const int m_speed_bullet=5;
        const unsigned int m_bullet_delay=30;
};

#endif // BULLET_HPP
