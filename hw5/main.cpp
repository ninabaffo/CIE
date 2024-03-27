// Name: Nina Baffo
// Date: 10/20/2022
// Description: creating the Bejeweled game
#include <SFML/Graphics.hpp>
#include <time.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace sf;

// Tile size and the given window
int ts = 54;
Vector2i offset(48, 24);

class Piece {
public:
    Piece() {
        match = 0;
        alpha = 255;
        kind = rand()%7;
        row = x;
        col = y;
        x = y*ts;
        y = x*ts;
    }
    double getX() const;
    void setX(int xTemp);

    double getY() const ;
    void setY(int yTemp);

    double getCol() const ;
    void setCol(int colTemp);

    double getRow() const ;
    void setRow(int rowTemp);

    double getKind() const ;
    void setKind(int kindTemp);

    double getMatch() const ;
    void setMatch(int matchTemp);

    double getAlpha() const ;
    void setAlpha(int alphaTemp);

private:
    int x, y, col, row, kind, match, alpha;

};
Piece grid[10][10];

//getX will return the private variable x
double Piece::getX() const{
    return x;
}
//setX makes the private variable x set to xTemp
void Piece::setX(const int xTemp){
    x = xTemp;
}
//getY will return the private variable y
double Piece::getY() const{
    return y;
}
//setY makes the private variable y set yTemp
void Piece::setY(const int yTemp){
    y = yTemp;
}
//getCol will return the private variable col
double Piece::getCol() const {
    return col;
};
//setCol makes the private variable col set colTemp
void Piece::setCol(const int colTemp){
    col = colTemp;
}
//getRow will return the private variable row
double Piece::getRow() const{
    return row;
};
//setRow makes the private variable row set rowTemp
void Piece::setRow(const int rowTemp){
    row = rowTemp;
}
//getKind will return the private variable kind
double Piece::getKind() const{
    return kind;
};
//setKind makes the private variable kind set kindTemp
void Piece::setKind(const int kindTemp){
    kind = kindTemp;
}
//getMatch will return the private variable match
double Piece::getMatch() const{
    return match;
};
//setMatch makes the private variable match set matchTemp
void Piece::setMatch(const int matchTemp){
    match = matchTemp;
}
//getAlpha will return the private variable alpha
double Piece::getAlpha() const{
    return alpha;
};
//setAlpha makes the private variable alpha set alphaTemp
void Piece::setAlpha(const int alphaTemp){
    alpha = alphaTemp;
}

// Description: swap two pieces in the game grid
// Input: p1 and p2 are Piece objects pass-by-value to swap
// Output: updated grid of pieces
void swap(Piece p1, Piece p2) {
    int tmp = p1.getCol();
    p1.setCol(p2.getCol());
    p2.setCol(tmp);

    tmp = p1.getRow();
    p1.setRow(p2.getRow());
    p2.setRow(tmp);

    int p1Row = p1.getRow();
    int p1Col = p1.getCol();
    int p2Row = p2.getRow();
    int p2Col = p2.getCol();

    grid[p1Row][p1Col] = p1;
    grid[p2Row][p2Col] = p2;
}

int main() {
    srand((unsigned int) time(nullptr));
    float timer=0,delay=0.3;
    Clock clock;

    // specialized window class: sf::RenderWindow. adds high-level functions to help you draw things easily
    // opening a window called 'app', which has size of 740x480 pixels and titled "Match-3 Game"
    RenderWindow app(VideoMode(740, 480), "Match-3 Game!");
    app.setFramerateLimit(60);

    // creating another window to display game rules named window.
    RenderWindow window(VideoMode(740, 480), "Match-3 Game!");
    window.setFramerateLimit(60);

    // creating 'textures' which are images mapped to a 2D entity
    // check to make sure file loaded correctly. If not, return EXIT_FAILURE
    Texture t1, t2, t3;
    if (!t1.loadFromFile("images/background.png")) {return EXIT_FAILURE;}
    if (!t2.loadFromFile("images/gems.png")) {return EXIT_FAILURE;}
    if (!t3.loadFromFile("images/cursor.png")) {return EXIT_FAILURE;}

    // creating sprites which are textured rectangles with t1 and t2.
    Sprite background(t1), gems(t2);

    // Sound effect obtained from Zapsplat.com
    // loading a sound buffer from a file on disk. If sound file fails to load, return EXIT_FAILURE
    SoundBuffer buffer;
    if (!buffer.loadFromFile("sounds/pop.ogg")) {return EXIT_FAILURE;}

    Sound sound;
    sound.setBuffer(buffer);

    // Font obtained from https://www.1001freefonts.com/faq.php
    // if font file fails to load, return EXIT_FAILURE
    Font font;
    if (!font.loadFromFile("fonts/Space.ttf")) {return EXIT_FAILURE;}

    // To draw text, use the Text class. Used this to draw score
    int score = 0;
    Text text;
    text.setFont(font);
    text.setString("Score: " + to_string(score));
    text.setCharacterSize(35);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Italic);
    text.setPosition(480, 400);

    // creating timerText to print out the timer in the game in seconds
    const int gameTimer = 60;
    int currentTime = gameTimer*60;

    Text timerText;
    timerText.setFont(font);
    timerText.setString("Timer: " + to_string(currentTime));
    timerText.setFillColor(sf::Color::Black);
    timerText.setStyle(sf::Text::Italic);
    timerText.setPosition(480, 300);

    // 'windowText' is what displays the game rules
    sf::Text windowText;
    windowText.setFont(font);
    windowText.setCharacterSize(37);
    windowText.setFillColor(sf::Color::Black);
    windowText.setPosition(25, 60);
    windowText.setStyle(sf::Text::Bold);

    // adding GameState which will be used to add a welcome and instruction screen at the start of the game.
    // GS_start is the starting state. GS_play will direct user to play the game. GS_end will quit the program.
    enum GameState {GS_start, GS_play, GS_end};
    GameState gameVal;
    gameVal = GS_start;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // If gameVal is in the GS_start state, the directions will be displayed to the screen.
            // If the user wants to play, the directions say to press p. if they want to quit, press e for exit.
            // If gameVal == GS_end, aka the user wants to quit, the program stops.
            if (gameVal == GS_start) {
                window.clear(Color::White);
                windowText.setString("Welcome to Bejeweled! \n"
                                     "The rules of the game are \n as follows: To gain points, \n match at least three\n"
                                     "jewels of the same kind \n" "vertically or horizontally. \n"
                                     "You will score more points \n" "the more jewels that \n" "are matched together.\n"
                                      "press 'P' to play or 'E' to exit.");

                window.draw(windowText);
                window.display();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == Keyboard::P) {
                        gameVal = GS_play;
                    } else if (event.key.code == Keyboard::E) {
                        gameVal = GS_end;
                        app.close();
                        //clock.restart();
                    }
                    window.close();
                }
            }
        }
    }
        // using a for loop to create the 8x8 tiles
        // in the loop, initialize the type of tile to random
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                grid[i][j].setKind(rand() % 3);
                grid[i][j].setCol(j);
                grid[i][j].setRow(i);
                grid[i][j].setX(j * ts);
                grid[i][j].setY(i * ts);
            }
        }

        int x0, y0, x, y;
        int click = 0;
        Vector2i pos;
        bool isSwap = false, isMoving = false;

        // run the program as long as the window is open
        // Add a countdown timer to the game. Stop the game when the counter gets to zero. You should print a
        // game over message. The game should restart when the “R” key is pressed.
        while (app.isOpen()) {
            app.clear();
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer+=time;

            Event e;
            while (app.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    app.close();
                }

                if (e.type == Event::MouseButtonPressed) {
                    if (e.key.code == Mouse::Left) {
                        if (!isSwap && !isMoving) {
                            click++;
                            pos = Mouse::getPosition(app) - offset;
                        }
                    }
                }

                if (e.type == Event::KeyPressed) {
                    if (e.key.code == Keyboard::R) {
                        app.close();
                        window.clear(Color::White);
                        text.setString("Game Over");
                        window.draw(text);
                        window.display();
                    }
                }
            }
            if (currentTime > 0){
                currentTime--;
            }
            // mouse click. Based on this you are moving around the tiles in the game
            if (click == 1) {
                x0 = pos.x / ts + 1;
                y0 = pos.y / ts + 1;
            }
            if (click == 2) {
                x = pos.x / ts + 1;
                y = pos.y / ts + 1;
                if (abs(x - x0) + abs(y - y0) == 1) {
                    swap(grid[y0][x0], grid[y][x]);
                    isSwap = 1;
                    click = 0;
                } else {
                    click = 1;
                }
            }

            //Match finding
            // if all three i, j, n match then add it to match
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    if (grid[i][j].getKind() == grid[i + 1][j].getKind()) {
                        if (grid[i][j].getKind() == grid[i - 1][j].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                sound.play();
                                grid[i + n][j].setMatch(+1);
                            }
                        }
                    }

                    if (grid[i][j].getKind() == grid[i][j + 1].getKind()) {
                        if (grid[i][j].getKind() == grid[i][j - 1].getKind()) {
                            for (int n = -1; n <= 1; n++) {
                                grid[i][j + n].setMatch(+1);
                            }
                            sound.play();
                        }
                    }
                }
            }

            //Moving animation
            //This moves the tiles back to where they were if you moved them and it was not a collection of 3
            isMoving = false;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece &p = grid[i][j];
                    int dx, dy;
                    for (int n = 0; n < 4; n++)   // 4 - speed
                    {
                        dx = p.getX() - p.getCol() * ts;
                        dy = p.getY() - p.getRow() * ts;
                        if (dx) {
                            p.setX(p.getX() - dx / abs(dx));
                        }
                        if (dy) {
                            p.setY(p.getY() - dy / abs(dy));
                        }
                    }
                    if (dx || dy) {
                        isMoving = 1;
                    }
                }
            }

            //Deleting amimation
            if (!isMoving) {
                for (int i = 1; i <= 8; i++) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            if (grid[i][j].getAlpha() > 10) {
                                grid[i][j].setAlpha(-10);
                                isMoving = true;
                            }
                        }
                    }
                }
            }

            //Get score
            int score;
            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    score += grid[i][j].getMatch();
                    text.setString("Score: " + to_string(score));
                }
            }

            //Second swap if no match
            if (isSwap && !isMoving) {
                if (!score) {
                    swap(grid[y0][x0], grid[y][x]);
                }
                isSwap = 0;
            }

            //Update grid
            // this will take the 3 match out and fill in the rest of the game with other jewels
            if (!isMoving) {
                for (int i = 8; i > 0; i--) {
                    for (int j = 1; j <= 8; j++) {
                        if (grid[i][j].getMatch()) {
                            for (int n = i; n > 0; n--) {
                                if (!grid[n][j].getMatch()) {
                                    swap(grid[n][j], grid[i][j]);
                                    break;
                                }
                            }
                        }
                    }
                };

                for (int j = 1; j <= 8; j++) {
                    for (int i = 8, n = 0; i > 0; i--) {
                        if (grid[i][j].getMatch()) {
                            grid[i][j].setKind(rand() % 7);
                            grid[i][j].setY(-ts * n++);
                            grid[i][j].setMatch(0);
                            grid[i][j].setAlpha(255);
                        }
                    }
                }
            }

            //////draw///////
            timerText.setString("Timer: " + to_string(currentTime));
            // ^^ cannot get numbers to print for timer and score. I dont know why, I have tried everything
            // I caould think of
            app.draw(background);
            app.draw(text);
            app.draw(timerText);

            for (int i = 1; i <= 8; i++) {
                for (int j = 1; j <= 8; j++) {
                    Piece p = grid[i][j];
                    gems.setTextureRect(IntRect(p.getKind() * 49, 0, 49, 49));
                    gems.setColor(Color(255, 255, 255, p.getAlpha()));
                    gems.setPosition(p.getX(), p.getY());
                    gems.move(offset.x - ts, offset.y - ts);
                    app.draw(gems);
                }
            }
            app.display();
    }
        return 0;
}