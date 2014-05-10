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
    win.setFramerateLimit(60);

    // Loop values
    float accumulator = 0.0f;
    int ticks = 0;
    sf::Clock clock;
    float updateInterval = 1.0f / 100.0f;
    int deathSpiral = 10;

    // Pads
    int numPads = 4;
    int fontSize = 14;
    std::vector<bool> pads(numPads, false);
    std::vector<std::vector<sf::Text> > gui;

    sf::Font font = sf::Font();
    if (!font.loadFromFile(resourcePath("ClearSans-Regular.ttf")))
    {
        printf("Unable to load font!\n");
        return 1;
    }

    View *view;
    bool added = false;


    sf::Joystick::update();
    for (int i = 0; i < numPads; ++i)
    {
        pads.at(i) = sf::Joystick::isConnected(i);
        int x = i % 2 == 0 ? 0 : 0.25 * width;
        x += i > 1 ? width * 0.5 : 0;
        int y = 0;

        std::vector<sf::Text> readout;

        sf::Text left = sf::Text("", font, fontSize);
        left.setPosition(x, y);

        sf::Text right = sf::Text("", font, fontSize);
        right.setPosition(x, y + 100);

        sf::Text buttons = sf::Text("", font, fontSize);
        buttons.setPosition(x, y + 300);

        sf::Text dpad = sf::Text("", font, fontSize);
        dpad.setPosition(x, y + 200);

        readout.push_back(left);
        readout.push_back(right);
        readout.push_back(buttons);
        readout.push_back(dpad);

        gui.push_back(readout);

        if (sf::Joystick::isConnected(i) && !added)
        {
            view = new View(i);
            added = true;
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
            }

            view->update();

            // Update loop
            for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
            {
                if (sf::Joystick::isConnected(i))
                {
                    bool hasX    = sf::Joystick::hasAxis(i, sf::Joystick::X);
                    bool hasY    = sf::Joystick::hasAxis(i, sf::Joystick::Y);
                    bool hasZ    = sf::Joystick::hasAxis(i, sf::Joystick::Z);
                    bool hasR    = sf::Joystick::hasAxis(i, sf::Joystick::R);
                    bool hasU    = sf::Joystick::hasAxis(i, sf::Joystick::U);
                    bool hasV    = sf::Joystick::hasAxis(i, sf::Joystick::V);
                    bool hasPovX = sf::Joystick::hasAxis(i, sf::Joystick::PovX);
                    bool hasPovY = sf::Joystick::hasAxis(i, sf::Joystick::PovY);

                    float x    = hasX    ? sf::Joystick::getAxisPosition(i, sf::Joystick::X)    : 0;
                    float y    = hasY    ? sf::Joystick::getAxisPosition(i, sf::Joystick::Y)    : 0;
                    float z    = hasZ    ? sf::Joystick::getAxisPosition(i, sf::Joystick::Z)    : 0;
                    float r    = hasR    ? sf::Joystick::getAxisPosition(i, sf::Joystick::R)    : 0;
                    float u    = hasU    ? sf::Joystick::getAxisPosition(i, sf::Joystick::U)    : 0;
                    float v    = hasV    ? sf::Joystick::getAxisPosition(i, sf::Joystick::V)    : 0;
                    float povX = hasPovX ? sf::Joystick::getAxisPosition(i, sf::Joystick::PovX) : 0;
                    float povY = hasPovY ? sf::Joystick::getAxisPosition(i, sf::Joystick::PovY) : 0;

                    std::ostringstream stream;
                    sf::Joystick::Identification joyId = sf::Joystick::getIdentification(i);
                    stream << joyId.name.toAnsiString() << "\n";
                    stream << "Vendor ID: " << joyId.vendorId << "\n";
                    stream << "Product ID: " << joyId.productId << "\n";
                    stream << "Axis X: " << x << "\nAxis Y: " << y << "\nAxis Z: " << z;
                    gui.at(i).at(0).setString(stream.str());
                    stream.str("");
                    stream.clear();

                    stream << "Axis R: " << r << "\nAxis U: " << u << "\nAxis V: " << v;
                    gui.at(i).at(1).setString(stream.str());
                    stream.str("");
                    stream.clear();

                    for (unsigned int j = 0; j < sf::Joystick::getButtonCount(i); ++j)
                    {
                        stream << "Button " << j << " " << (sf::Joystick::isButtonPressed(i, j) ? "is pressed" : "not pressed") << "\n";
                    }

                    gui.at(i).at(2).setString(stream.str());
                    stream.str("");
                    stream.clear();

                    stream << "PovX: " << povX << "\nPovY: " << povY;
                    gui.at(i).at(3).setString(stream.str());
                    stream.str("");
                    stream.clear();
                }
            }
        }

        // Draw
        win.clear(sf::Color(0, 0, 0));
        for (int j = 0; j < numPads; ++j)
        {
            // win.draw(gui.at(j).at(0));
            // win.draw(gui.at(j).at(1));
            // win.draw(gui.at(j).at(2));
            // win.draw(gui.at(j).at(3));
        }

        view->draw(win, sf::RenderStates::Default);

        win.display();
        ticks = 0;
    }

   return 0;
}
