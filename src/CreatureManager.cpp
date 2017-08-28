#include "CreatureManager.hpp"

CreatureManager::CreatureManager()
{

//set textures
tx_1_row.first.loadFromFile("texture/t1_1.bmp");
tx_1_row.second.loadFromFile("texture/t1_2.bmp");

tx_2_row.first.loadFromFile("texture/t2_1.bmp");
tx_2_row.second.loadFromFile("texture/t2_2.bmp");

tx_3_row.first.loadFromFile("texture/t3_1.bmp");
tx_3_row.second.loadFromFile("texture/t3_2.bmp");

for(int j=0; j<11; j++)
{
    creature[0][j].setTexture(tx_3_row.first);
    creature[1][j].setTexture(tx_2_row.first);
    creature[2][j].setTexture(tx_2_row.first);
    creature[3][j].setTexture(tx_1_row.first);
    creature[4][j].setTexture(tx_1_row.first);
}

//set start positions
    //TODO this should be range based
    float x = m_leftMargin;
    float y = m_upMargin;

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<11; j++)
        {
            creature[i][j].setPosition( {x, y} );
            x+=sizeOfCreature.x + spaceBeetwen.x;
        }x=m_leftMargin;
    y+=sizeOfCreature.y + spaceBeetwen.y;
    }


//set score
        for(int j=0; j<11; j++)
        {
            creature[0][j].setPoints( 30 );
            creature[1][j].setPoints( 20 );
            creature[2][j].setPoints( 20 );
            creature[3][j].setPoints( 10 );
            creature[4][j].setPoints( 10 );
        }


//start thread
    std::thread thr_m([=]{motion();});
    thr_m.detach();

    std::thread thr_cc([=]{checkCollisions();});
    thr_cc.detach();

}

void CreatureManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //TODO this should be range based
    for(int i=0; i<5; i++)
    for(int j=0; j<11; j++)
    {
        if(creature[i][j].isAlive())
        target.draw(creature[i][j]);
    }
}

void CreatureManager::motion()
{
    m_direction = Direction::right;
    m_isFirstTexture=true;

    for(;;)
    {
        //TODO should get local by reference, not member
        setDirectionOfCreatures();

        moveCreatures(m_direction);
        //TODO should get local by reference, not member
        animateCreatures();

        setShootableCreatures();

    //TODO idk if neccesary
    sf::sleep(sf::milliseconds(m_move_delay));
    }

}

int CreatureManager::getMostLeft()
{
    //for every column starting from left check if is there living creature
    for(int i =0; i<11; i++)
    {
        for(int j =0; j<5; j++)
        {
            if( creature[j][i].isAlive() )
                return i;
        }
    }

    return -1;
}

int CreatureManager::getMostRight()
{
    //for every column starting in right check if is there living creature
    for(int i =10; i>=0; i--)
    {
        for(int j =0; j<5; j++)
        {
            if( creature[j][i].isAlive() )
                return i;
        }
    }

    return -1;
}

void CreatureManager::checkCollisions()
{

    for(;;)
    {
        std::vector<sf::FloatRect> bulletBounds = Bullet::getAllBounds();

        int index=0;
        for(auto p: bulletBounds)
        {
            //TODO this should be range based
            for(int i=0; i<5; i++)
            for(int j=0; j<11; j++)
            {
                if(creature[i][j].isAlive())
                {
                    if( p.intersects( creature[i][j].getGlobalBounds() ) )
                    {
                        creature[i][j].kill();
                        Bullet::bullets.erase(Bullet::bullets.begin() + index);
                    }
                }

            }
            index++;
        }
        sf::sleep(sf::milliseconds(m_move_delay));
    }


}

void CreatureManager::moveCreatures(Direction direction)
{
    //TODO this should be range based
        for(int i=0; i<5; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(creature[i][j].isAlive())
                {
                    if(direction == Direction::right)
                    creature[i][j].move(m_step, 0);

                    else if(direction == Direction::left)
                    creature[i][j].move(-1 * m_step, 0);
                }

            }
        sf::sleep(sf::milliseconds(m_move_delay));
        }

}

void CreatureManager::animateCreatures()
{
    if(m_isFirstTexture)
        {
            for(int j=0; j<11; j++)
            {
                creature[0][j].setTexture(tx_3_row.first);
                creature[1][j].setTexture(tx_2_row.first);
                creature[2][j].setTexture(tx_2_row.first);
                creature[3][j].setTexture(tx_1_row.first);
                creature[4][j].setTexture(tx_1_row.first);
            }
            m_isFirstTexture=false;
        }

        else
        {
            for(int j=0; j<11; j++)
            {
                creature[0][j].setTexture(tx_3_row.second);
                creature[1][j].setTexture(tx_2_row.second);
                creature[2][j].setTexture(tx_2_row.second);
                creature[3][j].setTexture(tx_1_row.second);
                creature[4][j].setTexture(tx_1_row.second);
            }
            m_isFirstTexture=true;
        }
}

void CreatureManager::setDirectionOfCreatures()
{
        for(int i=0; i<5; i++)
        {
            if(creature[i][ getMostLeft() ].getPosition().x<=0)
            {
               m_direction = Direction::right;
               goLower(m_direction);
            }

            else if(creature[i][ getMostRight() ].getPosition().x>=640-sizeOfCreature.x)
            {
              m_direction = Direction::left;
              goLower(m_direction);
            }
        }

}

void CreatureManager::goLower(CreatureManager::Direction direction)
{

    for(int i=0; i<5; i++)
        {
            for(int j=0; j<11; j++)
            {
                if(creature[i][j].isAlive())
                {
                    if(direction == Direction::right)
                    creature[i][j].move(m_step, m_lower_step);

                    else if(direction == Direction::left)
                    creature[i][j].move(-1 * m_step, m_lower_step);
                }

            }
        sf::sleep(sf::milliseconds(m_move_delay));
        }

}

void CreatureManager::setShootableCreatures()
{
    //for every column set the most low creature shootable
    for(int i=0; i<11 ;i++)
    {
        for(int j=4; j>=0; j--)
        {
            if(creature[j][i].isAlive())
            {
                creature[j][i].setShootable(true);
                creature[j][i].setColor(sf::Color::Red);//TODO debug
                break;
            }

        }
    }
}
