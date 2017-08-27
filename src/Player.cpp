#include "Player.hpp"

int Player::totalScore =0;

Player::Player()
{

    tx_player.loadFromFile("texture/t_player.bmp");
    this->setTexture(tx_player);

    this->setPosition(sf::Vector2f(80,460));

    //TODO this should be in a constructor and choosen in settings
    bool joystickControl = true;

    if(joystickControl)
    {
       std::thread thr_j([=]{checkJoystickMove();});
       thr_j.detach();
    }
}

void Player::control(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                //TODO shape name
                if(this->getPosition().x < (640 - sizeOfPlayer.x) )
                this->move(m_speed, 0);
            break;

            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                //TODO shape name
                if(this->getPosition().x > 0)
                this->move(-1 * m_speed, 0);
            break;

            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                shoot();
            break;


            default:
                break;
        }
    }

    sf::Joystick::update();

    if( sf::Joystick::isButtonPressed(0, 2) ||
        sf::Joystick::isButtonPressed(0, 7))
    {
        shoot();
    }



}

//TODO settings for pad
void Player::checkJoystickMove()
{
    for(;;)
    {
        sf::Joystick::update();

        while(sf::Joystick::isConnected(0))
        {
            sf::Joystick::update();

            if ( sf::Joystick::hasAxis(0, sf::Joystick::X) )
            {
                if( sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 10)
                {
                    if(this->getPosition().x < (640 - sizeOfPlayer.x) )
                        this->move(m_speed, 0);
                }

                else if( sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -10)
                {
                    if(this->getPosition().x > 0)
                        this->move(-1 * m_speed, 0);
                }
            }

         sf::sleep(sf::milliseconds(m_joystick_delay));
        }

     sf::sleep(sf::milliseconds(m_disconnected_joystick_delay));
    }

}

void Player::shoot()
{
    float x = this->getPosition().x + (sizeOfPlayer.x)/2;
    float y = 480 - sizeOfPlayer.y - Bullet::getSize().y;

    Bullet::newBullet( {x, y} );
}
