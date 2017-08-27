#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

#include "Player.hpp"
#include "Creaturemanager.hpp"



class Game
{
    public:
        //ctor
        Game();
        //dtor
        virtual ~Game() = default;
        //starts game loop
        void start();

    private:
        //main window
        sf::RenderWindow m_window;

        //function used in thread drawing content on window
        void drawing();

        void events(sf::Event event);

        //DELAYS ARE FOR OPTIMALIZATION
        //delay of system events like closing window etc.
        const int m_event_delay=50;

        sf::RectangleShape shape;

        Player player;
        CreatureManager creatures;
        Bullet bullets;


};

#endif // GAME_HPP
