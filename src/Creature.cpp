#include "Creature.hpp"

////FIXME not sure if is it used
//Creature::Creature(sf::Vector2f i_position, unsigned short int i_points)
//                   : m_points(i_points), alive(true)
//{
//    //shape.setSize( {sizeOfCreature.x, sizeOfCreature.y} );
//}

Creature::Creature() : alive(true), m_points( 0 )
{
//ctor
}


void Creature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //TODO shape name
    if(alive)
        target.draw(shape);
}

void Creature::move(float offsetX, float offsetY)
{
    shape.move(offsetX, offsetY);
}

void Creature::move(const sf::Vector2f &offset)
{
    shape.move(offset);
}

