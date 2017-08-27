#include "Bullet.hpp"

const sf::Vector2f Bullet::sizeOfBullet = { 3.f, 7.f };
//int Bullet::bulletCount;
std::vector<sf::RectangleShape> Bullet::bullets;

Bullet::Bullet()
{
    std::thread thr_m( [=]{ moveAll(); } );
    thr_m.detach();

}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto p : bullets)
        target.draw(p);
}

void Bullet::newBullet(sf::Vector2f whereShooted)
{
    sf::RectangleShape bul;
    bul.setSize( sizeOfBullet );
    bul.setPosition( whereShooted );

    bullets.push_back( bul );
}

void Bullet::moveAll()
{

    for(;;)
    {
        for(auto& p : bullets)
            p.move(0, -1*m_speed_bullet);


        sf::sleep(sf::milliseconds(m_bullet_delay));


        for(unsigned int i=0; i<bullets.size(); i++)
        {
            if(bullets[i].getPosition().y < 0-bullets[i].getSize().y)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

    }
}

std::vector<sf::FloatRect> Bullet::getAllBounds()
{
    std::vector<sf::FloatRect> positions;

    for(auto p: bullets)
        positions.push_back( p.getGlobalBounds() );

    return positions;
}
