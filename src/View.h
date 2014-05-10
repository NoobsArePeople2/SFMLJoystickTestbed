#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Joystick.hpp>

#include <map>
#include <vector>

#include "Button.h"

class View : public sf::Drawable
{

public:

    View(unsigned int joystickIndex);
    ~View();

    void update();
    virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;

protected:
private:

    std::string axisToString(sf::Joystick::Axis axis);

    unsigned int joystickIndex;

    sf::Font font;
    sf::Text name;
    sf::Text vendorAndProduct;

    sf::RectangleShape titleSeparator;

    sf::Text buttonHeader;
    std::vector<Button> buttons;
    std::vector<sf::Text> buttonLabels;

    sf::RectangleShape buttonSeparator;

    sf::Text axesHeader;

    typedef std::map<sf::Joystick::Axis, sf::Text> AxisMap;
    AxisMap axes;


    sf::RectangleShape metaSeparator;

};

#endif // VIEW_H
