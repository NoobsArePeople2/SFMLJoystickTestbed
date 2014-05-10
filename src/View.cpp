#include <stdio.h>
#include <sstream>

#include "Button.h"
#include "ResourcePath.h"
#include "View.h"

///////////////////////////////////////////////////////////
View::View() :
    joystickIndex(0),
    joystickConnected(false)
{
    font.loadFromFile(resourcePath("ClearSans-Regular.ttf"));

    {
        notConnectedLabel = sf::Text("NOT CONNECTED\nConnect joystick to see info", font, 36);
        sf::FloatRect bounds = notConnectedLabel.getGlobalBounds();
        notConnectedLabel.setPosition((1024.0f - bounds.width) / 2.0f, 340);
    }

    {
        instructions = sf::Text("Use left and right arrow keys to select controllers.", font, 18);
        sf::FloatRect bounds = instructions.getGlobalBounds();
        instructions.setPosition((1024.0f - bounds.width) / 2.0f, 742);
    }
}


///////////////////////////////////////////////////////////
View::~View()
{
}


///////////////////////////////////////////////////////////
void View::setJoystick(unsigned int joystickIndex)
{
    this->joystickIndex = joystickIndex;
    joystickConnected = sf::Joystick::isConnected(joystickIndex);

    sf::Joystick::Identification id = sf::Joystick::getIdentification(joystickIndex);

    buttons.clear();
    buttonLabels.clear();
    axes.clear();
    indicatorLabels.clear();
    indicators.clear();

    {
        name = sf::Text(id.name, font, 36);
        sf::FloatRect bounds = name.getGlobalBounds();
        name.setPosition((1024.0f - bounds.width) / 2.0f, 0);
    }

    {
        std::ostringstream stream;
        stream << "Vendor ID: " << id.vendorId << "    Product ID: " << id.productId;// << "    Index: " << joystickIndex;
        vendorAndProduct = sf::Text(stream.str(), font, 24);
        sf::FloatRect bounds = vendorAndProduct.getGlobalBounds();
        vendorAndProduct.setPosition((1024.0f - bounds.width) / 2.0f, 46);
    }

    {
        titleSeparator = sf::RectangleShape(sf::Vector2f(1024.0f, 2.0f));
        titleSeparator.setPosition(0, 86);
    }

    {
        buttonHeader = sf::Text("Buttons", font, 36);
        buttonHeader.setPosition(64, 90);
        unsigned int cols = 0;
        float width = 192.0f;
        float height = 48.0f;
        float y = 150.0f;
        for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystickIndex); ++i)
        {
            float x = cols * width + 64;
            float buttonWidth = 30.0f;
            Button btn(x, y);
            buttons.push_back(btn);

            std::ostringstream stream;
            stream << i;
            sf::Text label(stream.str(), font, 26);
            label.setPosition(x + buttonWidth + 10, y - 6);
            buttonLabels.push_back(label);

            cols++;
            if (cols >= 5)
            {
                cols = 0;
                y += height;
            }
        }
    }

    {
        buttonSeparator = sf::RectangleShape(sf::Vector2f(1024.0f, 2.0f));
        buttonSeparator.setPosition(0, 424);
    }

    {
        axesHeader = sf::Text("Axes", font, 36);
        axesHeader.setPosition(64, 434);
    }

    {
        unsigned int cols = 0;
        float width = 320.0f;
        float height = 48.0f;
        float y = 490.0f;
        for (int i = sf::Joystick::X; i <= sf::Joystick::PovY; ++i)
        {
            float x = cols * width + 64;
            sf::Text axisText = sf::Text("", font, 26);
            sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
            if (sf::Joystick::hasAxis(joystickIndex, axis))
            {
                axisText.setString(axisToString(axis));
            }
            else
            {
                axisText.setString(axisToString(axis) + ": N/A");
            }
            axisText.setPosition(x, y);
            axes.insert(std::make_pair(axis, axisText));

            cols++;
            if (cols >= 3)
            {
                cols = 0;
                y += height;
            }
        }
    }

    {
        metaSeparator = sf::RectangleShape(sf::Vector2f(1024.0f, 2.0f));
        metaSeparator.setPosition(0, 640);
    }

    {
        controllerLabel = sf::Text("Controllers.", font, 18);
        sf::FloatRect bounds = controllerLabel.getGlobalBounds();
        controllerLabel.setPosition((1024.0f - bounds.width) / 2.0f, 660);

        float labelX = 64.0f;
        float labelW = 240.0f;
        float labelY = 690.0f;
        sf::Text currentLabel = sf::Text("Current", font, 18);
        currentLabel.setColor(sf::Color::Blue);
        currentLabel.setPosition(labelX, labelY);
        indicatorLabels.push_back(currentLabel);

        sf::Text connectedLabel = sf::Text("Connected", font, 18);
        connectedLabel.setColor(sf::Color::Green);
        connectedLabel.setPosition(labelX += labelW, labelY);
        indicatorLabels.push_back(connectedLabel);

        sf::Text disconnectedLabel = sf::Text("Disconnected", font, 18);
        disconnectedLabel.setColor(sf::Color::White);
        disconnectedLabel.setPosition(labelX += labelW, labelY);
        indicatorLabels.push_back(disconnectedLabel);

        sf::Text selectedDisconnectedLabel = sf::Text("Selected but disconnected", font, 18);
        selectedDisconnectedLabel.setColor(sf::Color::Yellow);
        selectedDisconnectedLabel.setPosition(labelX += labelW, labelY);
        indicatorLabels.push_back(selectedDisconnectedLabel);

        float size = 10.0f;
        float padding = 8.0f;
        float width = (size + padding) * sf::Joystick::Count;
        float x = (1024.0f - width) / 2.0f;
        for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
        {
            sf::RectangleShape rect(sf::Vector2f(size, size));
            rect.setPosition(x + (i * (size + padding)), 720);

            setIndicatorColor(rect, i, sf::Joystick::isConnected(i));
            indicators.push_back(rect);
        }
    }
}

///////////////////////////////////////////////////////////
void View::update()
{
    for (unsigned int i = 0; i < sf::Joystick::getButtonCount(joystickIndex); ++i)
    {
        if (sf::Joystick::isButtonPressed(joystickIndex, i))
        {
            buttons.at(i).setDown();
        }
        else
        {
            buttons.at(i).setUp();
        }
    }

    for (int i = sf::Joystick::X; i <= sf::Joystick::PovY; ++i)
    {
        sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
        if (sf::Joystick::hasAxis(joystickIndex, axis))
        {
            std::ostringstream stream;
            stream << sf::Joystick::getAxisPosition(joystickIndex, axis);
            axes[axis].setString(axisToString(axis) + ": " + stream.str());
        }
        else
        {
            axes[axis].setString(axisToString(axis) + ": N/A");
        }
    }

    for (unsigned int i = 0; i < sf::Joystick::Count; ++i)
    {
        setIndicatorColor(indicators.at(i), i, sf::Joystick::isConnected(i));
    }
}


///////////////////////////////////////////////////////////
void View::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (joystickConnected)
    {
        target.draw(name);
        target.draw(vendorAndProduct);
        target.draw(titleSeparator);


        target.draw(buttonHeader);
        for (std::vector<Button>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
        {
            target.draw(*it);
        }

        for (std::vector<sf::Text>::const_iterator it = buttonLabels.begin(); it != buttonLabels.end(); ++it)
        {
            target.draw(*it);
        }
        target.draw(buttonSeparator);


        target.draw(axesHeader);
        for (AxisMap::const_iterator it = axes.begin(); it != axes.end(); ++it)
        {
            target.draw(it->second);
        }
    }
    else
    {
        target.draw(notConnectedLabel);
    }

    target.draw(metaSeparator);

    target.draw(controllerLabel);

    for (std::vector<sf::Text>::const_iterator it = indicatorLabels.begin(); it != indicatorLabels.end(); ++it)
    {
        target.draw(*it);
    }

    for (std::vector<sf::RectangleShape>::const_iterator it = indicators.begin(); it != indicators.end(); ++it)
    {
        target.draw(*it);
    }

    target.draw(instructions);

}


/////////////////////////////////////////////////////////////
std::string View::axisToString(sf::Joystick::Axis axis)
{
    switch (axis)
    {
    case sf::Joystick::X:
        return std::string("X");

    case sf::Joystick::Y:
        return std::string("Y");

    case sf::Joystick::Z:
        return std::string("Z");

    case sf::Joystick::U:
        return std::string("U");

    case sf::Joystick::V:
        return std::string("V");

    case sf::Joystick::R:
        return std::string("R");

    case sf::Joystick::PovX:
        return std::string("PovX");

    case sf::Joystick::PovY:
        return std::string("PovY");

    default:
        return std::string("Unknown");
    }

}


/////////////////////////////////////////////////////////////
void View::setIndicatorColor(sf::RectangleShape& rect, unsigned int index, bool connected)
{
    if (connected)
    {
        if (index == joystickIndex)
        {
            rect.setFillColor(sf::Color::Blue);
        }
        else
        {
            rect.setFillColor(sf::Color::Green);
        }

    }
    else
    {
        if (index == joystickIndex)
        {
            rect.setFillColor(sf::Color::Yellow);
        }
        else
        {
            rect.setFillColor(sf::Color(173, 173, 173));
        }
    }
}
