#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int ts = 54; //tile size
Vector2i offset(48, 24); // the given window.

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
    double getX();
    void setX(int xTemp);

    double getY();
    void setY(int yTemp);

    double getCol();
    void setCol(int colTemp);

    double getRow();
    void setRow(int rowTemp);

    double getKind();
    void setKind(int kindTemp);

    double getMatch();
    void setMatch(int matchTemp);

    double getAlpha();
    void setAlpha(int alphaTemp);

private:
    int x, y, col, row, kind, match, alpha;

};
Piece grid[10][10];

//getX will return the private variable x
double Piece::getX() {
    return x;
}
//setX makes the private variable x set to xTemp
void Piece::setX(int xTemp) {
    x = xTemp;
}
//getY will return the private variable y
double Piece::getY() {
    return y;
}
//setY makes the private variable y set yTemp
void Piece::setY(int yTemp) {
    y = yTemp;
}
//getCol will return the private variable col
double Piece::getCol(){
    return col;
};
//setCol makes the private variable col set colTemp
void Piece::setCol(int colTemp){
    col = colTemp;
}
//getRow will return the private variable row
double Piece::getRow(){
    return row;
};
//setRow makes the private variable row set rowTemp
void Piece::setRow(int rowTemp){
    row = rowTemp;
}
//getKind will return the private variable kind
double Piece::getKind(){
    return kind;
};
//setKind makes the private variable kind set kindTemp
void Piece::setKind(int kindTemp){
    kind = kindTemp;
}
//getMatch will return the private variable match
double Piece::getMatch(){
    return match;
};
//setMatch makes the private variable match set matchTemp
void Piece::setMatch(int matchTemp){
    match = matchTemp;
}
//getAlpha will return the private variable alpha
double Piece::getAlpha(){
    return alpha;
};
//setAlpha makes the private variable alpha set alphaTemp
void Piece::setAlpha(int alphaTemp){
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
    srand(time(0));
    // specialized window class: sf::RenderWindow. adds high-level functions to help you draw things easily
    // opening a window called 'app', which has size of 740x480 pixels and titled "Match-3 Game"
    RenderWindow app(VideoMode(740, 480), "Match-3 Game!");
    app.setFramerateLimit(60);

    // creating 'textures' which are images mapped to a 2D entity
    Texture t1, t2;
    t1.loadFromFile("images/background.png");
    if (!t1.loadFromFile("images/background.png")) {
        return EXIT_FAILURE;                                  //check if file loaded correctly
    }

    t2.loadFromFile("images/gems.png");
    if (!t2.loadFromFile("images/gems.png")) {
        return EXIT_FAILURE;                                 //check if file loaded correctly
    }

    Sprite background(t1), gems(t2); // creating sprites which are textured rectangles with t1 and t2.

    // using a for loop to create the 8x8 tiles
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            grid[i][j].setKind(rand() % 3); // initializing the type of tile to random
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
    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed) {
                app.close();
            }

            if (e.type == Event::MouseButtonPressed) {
                if (e.key.code == Mouse::Left) {
                    if (!isSwap && !isMoving) {
                        click++;
                    }
                    pos = Mouse::getPosition(app) - offset;
                }
            }
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
                            grid[i + n][j].setMatch(+1);
                        }
                    }
                }

                if (grid[i][j].getKind() == grid[i][j + 1].getKind()) {
                    if (grid[i][j].getKind() == grid[i][j - 1].getKind()) {
                        for (int n = -1; n <= 1; n++) {
                            grid[i][j + n].setMatch(+1);
                        }
                    }
                }

            }
        }

        //Moving animation
        // This moves the tiles back to where they were if you moved them and it was not a collection of 3
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
        int score = 0;
        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                score += grid[i][j].getMatch();
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
        app.draw(background);

        for (int i = 1; i <= 8; i++) {
            for (int j = 1; j <= 8; j++) {
                Piece p = grid[i][j];
                gems.setTextureRect(IntRect(p.getKind()*49, 0, 49, 49));
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
