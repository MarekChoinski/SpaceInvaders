#include "Creature.hpp"

////FIXME not sure if is it used
//Creature::Creature(sf::Vector2f i_position, unsigned short int i_points)
//                   : m_points(i_points), alive(true)
//{
//    //shape.setSize( {sizeOfCreature.x, sizeOfCreature.y} );
//}

Creature::Creature() :
m_points( 0 ),
alive(true),
shootable(false)
{
//ctor
}
