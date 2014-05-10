#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>


class Button : public sf::RectangleShape
{

public:

    Button(const float x, const float y);
    ~Button();

    void setDown();
    void setUp();

protected:
private:


};

#endif // BUTTON_H
