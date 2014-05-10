#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Button.h"
#include "ResourcePath.h"
#include "View.h"

int main()
{
    unsigned int width = 1024;
    unsigned int height = 768;
    sf::RenderWindow win(sf::VideoMode(width, height, 32), "SFML Joystick Testbed");
    win.setVerticalSyncEnabled(true);

    // Loop values
    float accumulator = 0.0f;
    int ticks = 0;
    sf::Clock clock;
    float updateInterval = 1.0f / 100.0f;
    int deathSpiral = 10;

    int joystickIndex = -1;
    View view;
    sf::Joystick::update();
    for (int i = 0; i < sf::Joystick::Count; ++i)
    {
        if (sf::Joystick::isConnected(i))
        {
            view.setJoystick(i);
            joystickIndex = i;
            break;
        }
    }

    while (win.isOpen())
    {
        accumulator += clock.restart().asSeconds();
        while (accumulator >= updateInterval && ticks < deathSpiral)
        {
            accumulator -= updateInterval;
            ++ticks;
            sf::Event event;
            while (win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    win.close();
                }
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        joystickIndex++;
                        if (joystickIndex >= sf::Joystick::Count)
                        {
                            joystickIndex = 0;
                        }

                        view.setJoystick(joystickIndex);
                    }
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        joystickIndex--;
                        if (joystickIndex < 0)
                        {
                            joystickIndex = sf::Joystick::Count - 1;
                        }

                        view.setJoystick(joystickIndex);
                    }
                }
            }

            view.update();
        }

        // Draw
        win.clear(sf::Color(0, 0, 0));
        view.draw(win, sf::RenderStates::Default);
        win.display();

        ticks = 0;
    }

    return 0;
}
