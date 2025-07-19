// library
#include <SFML/Graphics.hpp>
#include <iostream>


// main program
int main()
{
    // state of spaces
    char state[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    // position of cursor (index)
    int cursor_x = 1;
    int cursor_y = 1;

    // turn
    bool is_X_turn = true;

    // winner
    char winner = ' ';


    // create window
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "Title");

    // create shapes
    sf::CircleShape    circle;
    sf::RectangleShape line;
    sf::RectangleShape cursor;
    circle.setPointCount(60);


    // lambda function - draw grid
    auto DrawGrid = [&](float space, float width, float position_x, float position_y)
        {
            line.setSize({ space * 3, width });
            line.setOrigin(line.getSize().x / 2 , line.getSize().y / 2);
            line.setFillColor(sf::Color(128, 128, 128));
            // horizontal
            line.setRotation((0.f));
            line.setPosition({ position_x, position_y - space / 2 });
            window.draw(line);
            line.setPosition({ position_x, position_y + space / 2 });
            window.draw(line);
            // vertical
            line.setRotation((90.f));
            line.setPosition({ position_x - space / 2, position_y });
            window.draw(line);
            line.setPosition({ position_x + space / 2, position_y });
            window.draw(line);
        };

    // lambda function - draw X
    auto DrawX = [&](float size, float width, float position_x, float position_y)
        {
            line.setSize({ size, width });
            line.setOrigin(line.getSize().x / 2, line.getSize().y / 2);
            line.setFillColor(sf::Color(170, 255, 0));
            line.setPosition({ position_x, position_y });
            line.setRotation((45.f));
            window.draw(line);
            line.setRotation((-45.f));
            window.draw(line);
        };

    // lambda function - draw O
    auto DrawO = [&](float size, float width, float position_x, float position_y)
        {
            circle.setRadius(size / 2);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color(0, 170, 255));
            circle.setOutlineThickness(-width);
            circle.setPosition({ position_x, position_y });
            window.draw(circle);
        };

    // lambda function - draw winning line
    auto DrawWinningLine = [&](float size, float width, float position_x, float position_y, float angle, float scale = 1.f)
        {
            line.setSize({ size * scale, width });
            line.setOrigin(line.getSize().x / 2, line.getSize().y / 2);
            line.setFillColor(sf::Color::White);
            line.setPosition({ position_x, position_y });
            line.setRotation((angle));
            window.draw(line);
        };

    // lambda function - draw cursor
    auto DrawCursor = [&](float size, float width, float position_x, float position_y)
        {
            cursor.setSize({ size, size });
            cursor.setOrigin(cursor.getSize().x / 2, cursor.getSize().y / 2);
            cursor.setFillColor(sf::Color::Transparent);
            cursor.setOutlineColor(sf::Color::White);
            cursor.setOutlineThickness(-width);
            cursor.setPosition({ position_x, position_y });
            window.draw(cursor);
        };


    // while window is still open
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // when close button is clicked
            if (event.type == sf::Event::Closed)
            {
                // close window
                window.close();
            }

            // when window is resized
            else if (event.type == sf::Event::Resized)
            {
                // update view
                sf::View view(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f(window.getSize())));
                window.setView(view);
            }

            // when keyboard is pressed
            else if (event.type == sf::Event::KeyPressed)
            {
                auto key = event.key.scancode;

                // no winner yet
                if (winner == ' ')
                {
                    // move cursor with WASD
                    if ((key == sf::Keyboard::Scancode::A) && (cursor_x > 0))        cursor_x--;
                    else if ((key == sf::Keyboard::Scancode::D) && (cursor_x < 2))   cursor_x++;
                    else if ((key == sf::Keyboard::Scancode::W) && (cursor_y > 0))   cursor_y--;
                    else if ((key == sf::Keyboard::Scancode::S) && (cursor_y < 2))   cursor_y++;

                    // mark X or O (if empty) with space
                    if ((key == sf::Keyboard::Scancode::Space) && (state[cursor_y][cursor_x] == ' '))
                    {
                        state[cursor_y][cursor_x] = is_X_turn ? 'X' : 'O';
                        is_X_turn = !is_X_turn;
                    }
                }

                // restart with Esc
                if (key == sf::Keyboard::Scancode::Escape)
                {
                    // reset state
                    for (int i = 0; i < 3; i++)
                        for (int j = 0; j < 3; j++)
                            state[i][j] = ' ';
                    cursor_x = 1;
                    cursor_y = 1;
                    is_X_turn = true;
                    winner = ' ';
                }
            }

        }

        // size of window
        float window_w = window.getView().getSize().x;
        float window_h = window.getView().getSize().y;
        float window_min = (window_w < window_h) ? window_w : window_h;

        // parameters
        float space = 0.3f * window_min;  // size of space
        float size = 0.8f * space;       // size of mark
        float width = 0.1f * size;        // line width

        // fill window with color
        window.clear(sf::Color(64, 64, 64));

        // draw grid
        DrawGrid(space, width / 4, window_w / 2, window_h / 2);

        // loop through rows
        for (int j = 0; j < 3; j++)
        {
            // loop through columns
            for (int i = 0; i < 3; i++)
            {
                // draw O
                if (state[j][i] == 'O')
                    DrawO(size, width, window_w / 2 + space * (i - 1), window_h / 2 + space * (j - 1));
                // draw X
                else if (state[j][i] == 'X')
                    DrawX(size, width, window_w / 2 + space * (i - 1), window_h / 2 + space * (j - 1));
            }
        }

        // draw winning line
        {
            for (int i = 0; i < 3; i++)
            {
                // horizontal
                if ((state[i][0] != ' ') and (state[i][0] == state[i][1]) and (state[i][1] == state[i][2]))
                {
                    DrawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2 + space * (i - 1), 0.f);
                    winner = state[i][0];
                }
                // vertical
                if ((state[0][i] != ' ') and (state[0][i] == state[1][i]) and (state[1][i] == state[2][i]))
                {
                    DrawWinningLine(space * 3, width / 2, window_w / 2 + space * (i - 1), window_h / 2, 90.f);
                    winner = state[0][i];
                }
            }
            // diagonal 1
            if ((state[0][0] != ' ') and (state[0][0] == state[1][1]) and (state[1][1] == state[2][2]))
            {
                DrawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2, 45.f, 1.4f);
                winner = state[0][0];
            }
            // diagonal 2
            if ((state[0][2] != ' ') and (state[0][2] == state[1][1]) and (state[1][1] == state[2][0]))
            {
                DrawWinningLine(space * 3, width / 2, window_w / 2, window_h / 2, -45.f, 1.4f);
                winner = state[0][2];
            }
        }


        // draw cursor
        if (winner == ' ')
            DrawCursor(space, width / 2, window_w / 2 + space * (cursor_x - 1), window_h / 2 + space * (cursor_y - 1));

        // display
        window.display();
    }


    // program end successfully
    return 0;
}