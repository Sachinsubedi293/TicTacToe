#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstring>

using namespace std;
class TicTacToe {
private:
    sf::Texture mainTexture,tileBlank,tileCross,tileCircle,resetImage,lineImage,lineImageT;
    sf::SoundBuffer tapBuffer,winBuffer,drawBuffer,resetBuffer;
    sf::Font font;
  
public:
    sf::Sound tapSound,winSound,drawSound,resetSound;
    std::string msg;
    bool loadAssist();
    bool loadComponents(int);
    sf::Sprite fullWindow,line;
    sf::Sprite tile[9];
    int player = 1;
    void onClickHandle(sf::Vector2f);
    bool waitForReset;
    int set[9] = {0,0,0,0,0,0,0,0,0};
    int temp[9] = { 0,0,0,0,0,0,0,0,0 };
    bool isDraw();
    bool isGameWin();
    sf::Text text;
    sf::Sprite reset;
};
//loadAssist
bool TicTacToe::loadAssist() {
    if (!this->mainTexture.loadFromFile("images/mainImage.png")) {
        return false;
    }
    if (!this->tileBlank.loadFromFile("images/blank.png")) {
        return false;
    }
    if (!this->tileCross.loadFromFile("images/cross.png")) {
        return false;
    }
    if (!this->tileCircle.loadFromFile("images/circle.png")) {
        return false;
    }
    if (!this->resetImage.loadFromFile("images/reset.png")) {
        return false;
    }
    if (!this->lineImage.loadFromFile("images/line.png")) {
        return false;
    }
    if (!this->lineImageT.loadFromFile("images/linet.png")) {
        return false;
    }
    if (!this->tapBuffer.loadFromFile("sounds/Click.wav")) {
        return false;
    }
    if (!this->winBuffer.loadFromFile("sounds/Win.wav")) {
        return false;
    }
    if (!this->drawBuffer.loadFromFile("sounds/Draw.wav")) {
        return false;
    } 
    if (!this->resetBuffer.loadFromFile("sounds/Reset.wav")) {
        return false;
    }
    if (!this->font.loadFromFile("font.ttf"))
        return false;
    this->winSound.setBuffer(this->winBuffer);
    this->drawSound.setBuffer(this->drawBuffer);
    this->resetSound.setBuffer(this->resetBuffer);
    this->tapSound.setBuffer(this->tapBuffer);
    this->reset.setTexture(this->resetImage);
    this->text.setFont(this->font);
    this->text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);
    this->text.setPosition(sf::Vector2f(680.0f, 25.0f));
    this->reset.setPosition(sf::Vector2f(720.0f, 400.0f));
    this->fullWindow.setTexture(this->mainTexture);
    this->fullWindow.setPosition(sf::Vector2f(0.0f, 0.0f));

    return true;
}
//end loadAssist

//load Components
bool TicTacToe::loadComponents(int startingPlayer){
    this->waitForReset = false;

    this->tile[0].setPosition(sf::Vector2f(20.0f,20.0f));
    this->tile[1].setPosition(sf::Vector2f(230.0f, 20.0f));
    this->tile[2].setPosition(sf::Vector2f(440.0f, 20.0f));
    this->tile[3].setPosition(sf::Vector2f(20.0f, 210.0f));
    this->tile[4].setPosition(sf::Vector2f(230.0f, 210.0f));
    this->tile[5].setPosition(sf::Vector2f(440.0f, 210.0f));
    this->tile[6].setPosition(sf::Vector2f(20.0f, 400.0f));
    this->tile[7].setPosition(sf::Vector2f(230.0f, 400.0f));
    this->tile[8].setPosition(sf::Vector2f(440.0f, 400.0f));
    for (int i = 0; i < 9; i++) {
        this->tile[i].setTexture(this->tileBlank);
    }

    this->msg = std::string(this->player == 1 ? "Player 1's \nturn" : "Player 2's \nturn");
    this->text.setString(this->msg);
    return true;
}
//end Loadcomponents
//Draw
bool TicTacToe::isDraw() {
    for (int i = 0; i < 9; i++)
    {
        if (this->set[i] == 0) {
            return false;
        }
    }

    return true;
}
//end Draw
// Win
bool TicTacToe::isGameWin() {
    if (this->set[0] == this->set[1] && this->set[1] == this->set[2]&&this->set[0]!=0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(50.0f,100.0f));

        return true;
   }
    if (this->set[3] == this->set[4] && this->set[4] == this->set[5] && this->set[3] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(50.0f, 300.0f));
        return true;
    }
    if (this->set[6] == this->set[7] && this->set[7] == this->set[8] && this->set[6] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(50.0f, 500.0f));
        return true;
    }
    if (this->set[0] == this->set[3] && this->set[3] == this->set[6] && this->set[0] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(120.0f, 60.0f));
        this->line.setRotation(90.0f);
        return true;
    }
    if (this->set[1] == this->set[4] && this->set[4] == this->set[7] && this->set[1] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(350.0f, 60.0f));
        this->line.setRotation(90.0f);
        return true;
    }
    if (this->set[2] == this->set[5] && this->set[5] == this->set[8] && this->set[2] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(540.0f, 60.0f));
        this->line.setRotation(90.0f);
        return true;
    }
    if (this->set[0] == this->set[4] && this->set[4] == this->set[8] && this->set[0] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(140.0f, 110.0f));
        this->line.setRotation(45.0f);
        return true;
    }
    if (this->set[2] == this->set[4] && this->set[4] == this->set[6] && this->set[2] != 0) {
        this->line.setRotation(0.0f);
        this->line.setTexture(this->lineImage);
        this->line.setPosition(sf::Vector2f(540.0f, 110.0f));
        this->line.setRotation(135.0f);
        return true;
    }
    return false;
}
// end Win
//mouseClickHandeler
void TicTacToe::onClickHandle(sf::Vector2f pos) {
    if (!this->waitForReset) {
        for (int i = 0; i < 9; i++)
        {
            if (this->set[i] == 0) {
                if (this->tile[i].getGlobalBounds().contains(pos)) {
                    this->tapSound.play();
                    this->tile[i].setTexture(player == 1 ? this->tileCircle : this->tileCross);
                    this->set[i] = this->player;
                    if (this->isGameWin()) {
                        std::cout << "Player"<<this->player<<"\nWins!" << std::endl;
                        this->msg = this->player == 1 ? "Player 1 \nwins!" : "Player 2 \nwins!";
                        this->text.setString(this->msg);
                        this->winSound.play();
                        this->waitForReset = true;
                    }
                    else if (this->isDraw()) {
                        std::cout << "Game is Draw!" << std::endl;
                        this->waitForReset = true;
                        this->msg = "Draw.\nNobody wins!.";
                        this->text.setString(this->msg);
                        this->drawSound.play();
                     
                    }
                    else {
                        this->player = this->player == 1 ? 2 : 1;
                        this->msg = this->player == 1 ? "Player 1's \nturn" : "Player 2's \nturn";
                        this->text.setString(this->msg);
                    }
                    break;
                   
                }
           }
        }
   }
    if (this->reset.getGlobalBounds().contains(pos)) {
        this->loadComponents(this->player == 1 ? 2 : 1);
        this->resetSound.play();
        for (int i = 0; i < 9; i++) {
            this->set[i] = 0;
        }
        this->line.setTexture(this->lineImageT);
    }
}
//end mouseClickHandeler


int main()
{
    TicTacToe Game;

    if (!Game.loadAssist())
    {
        std::cout << "File Loading Error"<<std::endl;
    }
    if (!Game.loadComponents(Game.player))
    {
        std::cout << "Component Loading Error" << std::endl;
    }
    
    sf::RenderWindow window(sf::VideoMode(1000, 613), "Tic Tac Toe");
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type==sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    Game.onClickHandle(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }
        }
    
     
        window.clear();
        window.draw(Game.fullWindow);
        window.draw(Game.text);
        window.draw(Game.reset);
        for (int i = 0; i < 9; i++) {
            window.draw(Game.tile[i]);
   
        }
        window.draw(Game.line);
        window.display();
    }

    return 0;
}