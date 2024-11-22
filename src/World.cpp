#include "World.h"

World::World(sf::RenderWindow& wnd, float L, float mass)
    : L(L), m(mass)
{
    nexaLight.loadFromFile("./resources/Nexa-ExtraLight.ttf");

    background.setOutlineColor(sf::Color(18, 188, 148)); // draw an aesthetic outline around the world
    background.setOutlineThickness(2.f);
    background.setFillColor(sf::Color::Black); 

    const float wndWidth = wnd.getSize().x;
    const float wndHeight = wnd.getSize().y;

    // did some algebra for this one. 
    // .05 * wndH = padR                        | we want the padding at the bottom to be the same as on the right
    // .05 * wndH = padRPercent * wndW          | express the padding on the right as a percent of the width
    // .05 * wndH / wndW = padRPercent          | solve for the percent to be used in the width calculation
    const float pRPercent = .05f * wndHeight / wndWidth; 

    // calculate the size of the world
    this->width = wndWidth * (.70-pRPercent); // the 70% space left after the left most of the position minus the percent of the width for
                                             // padding
    this->height = wndHeight * .75; // and the height is 75% of the screen
    background.setSize(sf::Vector2f(width, height));

    // calculate the position of the world space
    auto x = .3 * wndWidth; // 30% the screen space to the right to leave that much space for the menu to the left
    auto y = .2 * wndHeight; // 1/5 the screen space down from the top to leave space for the title
    background.setPosition(sf::Vector2f(x, y));

    /******************************************************************************************/
    /*                               Create the coordinate system                             */
    /******************************************************************************************/

    // aesthetics of axes
    x_axis.setOutlineColor(sf::Color::White);
    x_axis.setOutlineThickness(1.f);
    x_axis.setFillColor(sf::Color::White); 
    y_axis.setOutlineColor(sf::Color::White);
    y_axis.setOutlineThickness(1.f);
    y_axis.setFillColor(sf::Color::White); 

    x_axis.setSize({ width , 0.f }); // a line with no thickness minus a border 
    y_axis.setSize({ 0.f , height});


    // position of axes
    // start right after the border at the height of the bob at minimum
    x_axis.setPosition(background.getGlobalBounds().getPosition() + sf::Vector2f{2.f , height - 0.2f*L}); 
    // start right after the border centered
    y_axis.setPosition(background.getGlobalBounds().getPosition() + sf::Vector2f{width / 2.f , 2.f}); 

    // the tick marks on the x-axis
    int nTicksX = static_cast<int>(4 * width / L); // 4 ticks per length L
    x_ticks = std::vector<sf::RectangleShape>(nTicksX); 
    // set the positions from left to right in world corrdinates
    sf::Vector2f pos = { (nTicksX / 2) * -L / 4.f, 0.f };
    for(int i = 0; i < nTicksX; i++) // 
    {
        // this ensures that you do not draw a tick on the origin
        if(pos.x >= -1.f && pos.x < L/4.f) 
        {
            pos += {.25f * L , 0.f}; // increment the pos as usual
            i--; // decrease the index counter
            continue; // move on
        }

        if(screenPos(pos).x < background.getGlobalBounds().getPosition().x || 
            screenPos(pos).x > background.getGlobalBounds().getPosition().x + width)
        {
            pos += {.25f * L , 0.f}; // increment the pos as usual
            i--; // decrease the index counter as if this part of the loop hadn't happened
            nTicksX--; // decrease the number of elements by one
            x_ticks.pop_back(); // remove this element
            continue; // move on without drawing
        }

        x_ticks.at(i).setOutlineColor(sf::Color::White);
        x_ticks.at(i).setOutlineThickness(1.f);
        x_ticks.at(i).setFillColor(sf::Color::White); 

        x_ticks.at(i).setSize({0.f, 7.f}); 

        x_ticks.at(i).setPosition(screenPos(pos));
        pos += {.25f * L , 0.f}; // move to the next tick a L/4 to the right
    }

    // the tick marks on the y-axis

    // TODO: fix the issue in the math below. a tick is drawn slightly above the world frame
    // temporary fix is just to decrease the number of ticks by 1. if someone has a dramatically
    // different screen size than mine, this is not guaranteed to not be buggy
    int nTicksY = static_cast<int>(4 * height / L); // 4 ticks per length L
    y_ticks = std::vector<sf::RectangleShape>(nTicksY); 
    const int nTicksBelowXAxis = static_cast<int>(4.f * 0.2f); // the number of ticks that fit below the x-axis
    // set the positions from bottom to top in world corrdinates
    pos = { 0.f, nTicksBelowXAxis * -L / 4.f };
    for(int i = 0; i < nTicksY; i++) // 
    {
        // this ensures that you do not draw a tick on the origin
        if(pos.y >= -1.f && pos.y < L/4.f) 
        {
            pos += { 0.f, .25f * L }; // increment the pos as usual
            i--; // decrease the index counter
            continue; // move on
        }

        if(screenPos(pos).y < background.getGlobalBounds().getPosition().y || 
            screenPos(pos).y > background.getGlobalBounds().getPosition().y + height)
        {
            pos += { 0.f , 0.25f * L}; // increment the pos as usual
            i--; // decrease the index counter as if this part of the loop hadn't happened
            nTicksY--; // decrease the number of elements by one
            y_ticks.pop_back(); // remove this element
            continue; // move on without drawing
        }

        y_ticks.at(i).setOutlineColor(sf::Color::White);
        y_ticks.at(i).setOutlineThickness(1.f);
        y_ticks.at(i).setFillColor(sf::Color::White); 

        y_ticks.at(i).setSize({7.f, 0.f}); 

        y_ticks.at(i).setPosition(screenPos(pos));
        pos += { 0.f, .25f * L }; // move to the next tick a L/4 to the right
    }

    const int n_xlabels = int(nTicksX / 4); // with truncation to integer value this should always work
    tick_xlabels = std::vector<sf::Text>(n_xlabels);
    pos = { (n_xlabels / 2) * -L , -10.f}; // start from the left, right below the tick mark
    for(int i = 0; i < n_xlabels; i++)
    {
        // this ensures that you do not draw a tick label on the origin
        if(pos.x >= -1.f && pos.x < L) 
        {
            pos += { L,0.f }; // increment the pos as usual
            i--; // decrease the index counter
            continue; // move on
        }

        
        tick_xlabels.at(i).setCharacterSize(15.f);
        tick_xlabels.at(i).setFont(nexaLight);
        tick_xlabels.at(i).setFillColor(sf::Color::White);
        std::string numString = ((pos.x < 0.f) ? "-":"") +             // print a negative sign if necessary
                                ((std::abs(pos.x) > L + 1.f) ? 
                                std::to_string(int((std::abs(pos.x) + 1.f) / L)) + "L" : "L"); // prepend integer in front of L
        tick_xlabels.at(i).setString(numString);
        // center the label under the tick
        tick_xlabels.at(i).setPosition(screenPos(pos) - sf::Vector2f{tick_xlabels.at(i).getLocalBounds().getSize().x / 2.f, 0.f});
        pos += { L, 0.f }; // shift the position to the next value
    }

    const int n_ylabels = int(nTicksY / 4); // with truncation to integer value this should always work
    tick_ylabels = std::vector<sf::Text>(n_ylabels);
    pos = { 10.f , L }; // start from the bottom to the top, to the right of the tick mark
    for(int i = 0; i < n_ylabels; i++)
    {
        // this ensures that you do not draw a tick label on the origin
        if(pos.y >= -1.f && pos.y < L) 
        {
            pos += { 0.f, L }; // increment the pos as usual
            i--; // decrease the index counter
            continue; // move on
        }

        
        tick_ylabels.at(i).setCharacterSize(15.f);
        tick_ylabels.at(i).setFont(nexaLight);
        tick_ylabels.at(i).setFillColor(sf::Color::White);
        std::string numString = ((pos.y < 0.f) ? "-":"") +             // print a negative sign if necessary
                                ((std::abs(pos.y) > L + 1.f) ? 
                                std::to_string(int((std::abs(pos.y) + 1.f) / L)) + "L" : "L"); // if the length is 1L only put L
        tick_ylabels.at(i).setString(numString);
        // center the label with the tick
        tick_ylabels.at(i).setPosition(screenPos(pos) - sf::Vector2f{ 0.f , tick_ylabels.at(i).getLocalBounds().getSize().y / 2.f});
        pos += { 0.f, L }; // shift the position to the next value
    }

    /******************************************************************************************/
    /*                               Create the physical system                               */
    /******************************************************************************************/
}

void World::draw(sf::RenderWindow& wnd)
{
    // Draw the background
    wnd.draw(background);

    // draw the cartesian coordinate system relative to L
    wnd.draw(x_axis);
    wnd.draw(y_axis);
    for(auto& tick : x_ticks)
    {
        wnd.draw(tick);
    }
    for(auto& tick : y_ticks)
    {
        wnd.draw(tick);
    }
    for(auto& label : tick_xlabels)
    {
        wnd.draw(label);
    }
    for(auto& label : tick_ylabels)
    {
        wnd.draw(label);
    }
}

bool World::withinWorld(sf::Vector2f globalPos) const
{
    // check that position given is within the x values of the background box
    bool withinWorld = globalPos.x >= background.getGlobalBounds().getPosition().x &&
                    globalPos.x <= background.getGlobalBounds().getPosition().x + width;
    // check that position given is within the y values of the background box
    withinWorld = withinWorld && globalPos.y >= background.getGlobalBounds().getPosition().y &&
                    globalPos.y <= background.getGlobalBounds().getPosition().y + height;
    return withinWorld;
}
