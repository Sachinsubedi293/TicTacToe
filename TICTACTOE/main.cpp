#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstring>
#include<fstream>
#include <iomanip>
using namespace std;
class Data {
private:
    int player1Value;
    int player2Value;
    int gamePlyed;

public:
    Data() {
        this->player1Value = 0;
        this->player2Value = 0;
        this->gamePlyed=0;
    }

    int getPlayer1Value() const {
        return player1Value;
    }

    int getPlayer2Value() const {
        return player2Value;
    }
    int getGamePlayed()const {
        return gamePlyed;
    }

    void incrementPlayer1Value(int incrementAmount) {
        player1Value += incrementAmount;
    }

    void incrementPlayer2Value(int incrementAmount) {
        player2Value += incrementAmount;
    }
    void incrementGamePlayed(int incrementAmount) {
        gamePlyed += incrementAmount;
    }

    void serialize(fstream& file) const {
        file.write((char*)this, sizeof(*this));
    }

    void deserialize(fstream& file) {
        file.read((char*)this, sizeof(*this));
    }
};
class TicTacToe {
private:
    sf::Texture mainTexture,tileBlank,tileCross,tileCircle,resetImage,lineImage,lineImageT,deleteData;
    sf::SoundBuffer tapBuffer,winBuffer,drawBuffer,resetBuffer,delBuffer;
    sf::Font font;
  
public:
    sf::Sound tapSound,winSound,drawSound,resetSound,delSound;
    std::string msg,calcs;
    bool loadAssist();
    bool loadComponents(int);
    sf::Sprite fullWindow,line;
    sf::Sprite tile[9];
    int player = 1;
    void onClickHandle(sf::Vector2f pos, Data& d);
    bool waitForReset;
    int set[9] = {0,0,0,0,0,0,0,0,0};
    int temp[9] = { 0,0,0,0,0,0,0,0,0 };;
    bool isDraw();
    bool isGameWin();
    sf::Text text;
    sf::Text calc;
    sf::Sprite reset,delData;
    void savedata(const Data& d) {
        fstream file("Data", ios::out | ios::binary);
        d.serialize(file);
    }

    void loaddata(Data& d) {
        fstream file("Data", ios::in | ios::binary);
        d.deserialize(file);
    }
    bool deleteFile(const char* filename) {
        if (remove(filename) == 0) {
            cout << "Data deleted successfully." << endl;
            return true;
        }
        else {
            cout << "Data deleting file." << endl;
            return false;
        }
    }
    void calculate(Data& d);
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
    if (!this->deleteData.loadFromFile("images/del.png")) {
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
    if (!this->delBuffer.loadFromFile("sounds/del.wav")) {
        return false;
    }
    if (!this->font.loadFromFile("font.ttf"))
        return false;
    this->delSound.setBuffer(this->delBuffer);
    this->winSound.setBuffer(this->winBuffer);
    this->drawSound.setBuffer(this->drawBuffer);
    this->resetSound.setBuffer(this->resetBuffer);
    this->tapSound.setBuffer(this->tapBuffer);
    this->reset.setTexture(this->resetImage);
    this->text.setFont(this->font);
    this->text.setCharacterSize(50);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(sf::Vector2f(700.0f, 25.0f));
    this->calc.setFont(this->font);
    this->calc.setCharacterSize(15);
    this->calc.setFillColor(sf::Color::Black);
    this->calc.setPosition(sf::Vector2f(680.0f, 200.0f));
    this->reset.setPosition(sf::Vector2f(720.0f, 400.0f));
    this->fullWindow.setTexture(this->mainTexture);
    this->fullWindow.setPosition(sf::Vector2f(0.0f, 0.0f));
    this->delData.setTexture(this->deleteData);
    this->delData.setPosition(sf::Vector2f(780.0f,500.0f));

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
void TicTacToe::calculate(Data& d)
{
    int totalDraws = d.getGamePlayed() - (d.getPlayer1Value() + d.getPlayer2Value());
    
    if (d.getGamePlayed() != 0) {
        if (d.getPlayer1Value() > 0 || d.getPlayer2Value() > 0) {
            this->calcs = "Stats\n Game Played: " + to_string(d.getGamePlayed()) + "\n" +
                "Draws:       " + to_string(totalDraws) + "\n" +
                "Player:      win     win%     win% (no draws)\n" +
                "Player1      " + to_string(d.getPlayer1Value()) + "       " +
                to_string((d.getPlayer1Value() * 100.0 / d.getGamePlayed())) + "%" + "     " +
                to_string((d.getPlayer1Value() * 100.0 / (d.getGamePlayed() - totalDraws))) + "%" + "\n" +
                "Player2      " + to_string(d.getPlayer2Value()) + "       " +
                to_string((d.getPlayer2Value() * 100.0 / d.getGamePlayed())) + "%" + "     " +
                to_string((d.getPlayer2Value() * 100.0 / (d.getGamePlayed() - totalDraws))) + "%" + "\n";
        }
        else {
            this->calcs ="Stats \nGame Played: " + to_string(d.getGamePlayed()) + "\n" +
                "Draws:       " + to_string(totalDraws) + "\n" +
                "Player:      win     win%     win% (no draws)\n" +
                "Player1      " + to_string(d.getPlayer1Value()) + "       " +
                to_string((d.getPlayer1Value() * 100.0 / d.getGamePlayed())) + "%" + "     " +
                to_string((d.getPlayer1Value() * 100.0 / d.getGamePlayed())) + "%" + "\n" +
                "Player2      " + to_string(d.getPlayer2Value()) + "       " +
                to_string((d.getPlayer2Value() * 100.0 / d.getGamePlayed())) + "%" + "     " +
                to_string((d.getPlayer2Value() * 100.0 / d.getGamePlayed())) + "%" + "\n";
        }


 
    }
    else {
        this->calcs = "Stats\nGame Played: 0\nDraws:       0\nPlayer:      win     win%     win% (no draws)\nPlayer1      0     N/A     N/A\nPlayer2      0     N/A     N/A";
    }

    this->calc.setString(this->calcs);
}


// end Win
//mouseClickHandeler
void TicTacToe::onClickHandle(sf::Vector2f pos, Data& d) {
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
                        d.incrementGamePlayed(1);

                        if (this->player == 1) {
                            d.incrementPlayer1Value(1);
                        }
                        else {
                            d.incrementPlayer2Value(1);
                        }
                        calculate(d);
                    }
                    else if (this->isDraw()) {
                        std::cout << "Game is Draw!" << std::endl;
                        this->waitForReset = true;
                        this->msg = "Draw.\nNobody wins!.";
                        this->text.setString(this->msg);
                        this->drawSound.play();
                        d.incrementGamePlayed(1);
                        calculate(d);
                     
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
        resetSound.play();
        for (int i = 0; i < 9; i++) {
            this->set[i] = 0;
        }
        this->line.setTexture(this->lineImageT);
    }
    if (this->delData.getGlobalBounds().contains(pos)) {
        deleteFile("Data");
        d = Data();
        delSound.play();
        calculate(d);
        
    }
}
//end mouseClickHandeler


int main()
{
    TicTacToe Game;
    Data d;

    if (!Game.loadAssist())
    {
        std::cout << "File Loading Error" << std::endl;
        return 0;
    }

    if (!Game.loadComponents(Game.player))
    {
        std::cout << "Component Loading Error" << std::endl;
        return 0;
    }

    Game.loaddata(d);
    Game.calculate(d);
    cout << "Player 1 Value: " << d.getPlayer1Value() << endl;
    cout << "Player 2 Value: " << d.getPlayer2Value() << endl;
    cout << "Game Played: " << d.getGamePlayed() << endl;
    sf::RenderWindow window(sf::VideoMode(1000, 613), "Tic Tac Toe");
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                // Save data to file before closing the window
                cout << "Updated Player 1 Value: " << d.getPlayer1Value() << endl;
                cout << "Updated Player 2 Value: " << d.getPlayer2Value() << endl;
                cout << "Updated GamePlayed: " << d.getGamePlayed() << endl;
                Game.savedata(d); // Save data to file
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    Game.onClickHandle(window.mapPixelToCoords(sf::Mouse::getPosition(window)), d); // Pass 'd' to the function
            }
        }
    
     
        window.clear();
        window.draw(Game.fullWindow);
        window.draw(Game.text);
        window.draw(Game.reset);
        window.draw(Game.delData);
        window.draw(Game.calc);
        for (int i = 0; i < 9; i++) {
            window.draw(Game.tile[i]);
   
        }
        window.draw(Game.line);
        window.display();
    }

    return 0;
}