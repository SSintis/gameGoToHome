#include "workLibGame.h"

int main()
{
    srand(time(NULL));
    //--------------------------------------------------------------------
    //Свойства окна
    //--------------------------------------------------------------------
    RenderWindow window(sf::VideoMode(1280, 720), L"Путь домой!");

    Image icon;
    if (!icon.loadFromFile("image\\icon.png")) 
        return 1;
    window.setIcon(32, 32, icon.getPixelsPtr());

    Texture textureInfoPanel;
    textureInfoPanel.loadFromFile("image\\Panel.png");
    RectangleShape GameInfoPanel(Vector2f(1280, 113));
    GameInfoPanel.setTexture(&textureInfoPanel);
    GameInfoPanel.setPosition(Vector2f(0, 0));
    //--------------------------------------------------------------------
    //Космос                                            
    //--------------------------------------------------------------------
    Texture textureSpace;
    textureSpace.loadFromFile("image\\newkos1.jpg");

    RectangleShape gamingBackGround(Vector2f(1280, 720));
    gamingBackGround.setTexture(&textureSpace);

    RectangleShape gamingBackGround2(Vector2f(1280, 720));
    gamingBackGround2.setTexture(&textureSpace);
    gamingBackGround2.setPosition(Vector2f(1280, 0));

    bool GameOver = false;
    Vector2f pos;
    Clock clock, clockAnimPlay, clockAnimMeteor;
    float time, timePlayer, timeGamingBackGround, timeMeteor;
    //--------------------------------------------------------------------
    //Космический корабль игрока
    //--------------------------------------------------------------------
    Vector2f moveRec;
    int traffic = 0;
    FrameAnim FramePlAnim;
    FramePlAnim.Frame = 700;
    Texture playerTexture;
    playerTexture.loadFromFile("image\\playeranim1.png");
    Sprite player;
    player.setTexture(playerTexture);
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));
    player.scale(0.7, 0.7);
    player.setPosition(Vector2f(80, 380));
    
    FrameAnim DestructAnim;
    DestructAnim.Frame = 5;
    DestructAnim.Frame1 = 15;
    Texture texdest;
    texdest.loadFromFile("image\\bum.png");
    Sprite destruction;
    destruction.setTexture(texdest);
    destruction.setTextureRect(IntRect(5, 15, 95, 80));
    destruction.scale(0.7, 0.7);

    //--------------------------------------------------------------------
    //Метеоры
    //--------------------------------------------------------------------

    Meteor meteor[15];
    int nMeteor = 15;

    while (window.isOpen())
    {
        sf::Event event;

        time = clock.getElapsedTime().asMicroseconds();

        timePlayer = time / 6000;
        timeGamingBackGround = time / 2000;
        timeMeteor = time / 3000;

        clock.restart();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::W) { moveRec.y = -0.5 * timePlayer; traffic = 2; }
                if (event.key.code == Keyboard::S) { moveRec.y = 0.5 * timePlayer; traffic = 1; }
                if (event.key.code == Keyboard::A) moveRec.x = -0.5 * timePlayer;
                if (event.key.code == Keyboard::D) moveRec.x = 0.5 * timePlayer;
                break;

            case Event::KeyReleased:
                if (event.key.code == Keyboard::W) { moveRec.y = 0; traffic = 0; }
                if (event.key.code == Keyboard::S) { moveRec.y = 0; traffic = 0; }
                if (event.key.code == Keyboard::A) moveRec.x = 0;
                if (event.key.code == Keyboard::D) moveRec.x = 0;
                break;
            default:
                break;
            }
        }
        if (GameOver) {
            if (clockAnimMeteor.getElapsedTime() > milliseconds(80)) {
                clockAnimMeteor.restart();
                DestructAnim.Frame += DestructAnim.Step;

                if (DestructAnim.Frame > 405) {
                    DestructAnim.Frame1 += DestructAnim.Step1; DestructAnim.Frame = 5;
                }

                if (DestructAnim.Frame1 > 415) {
                    GameOver = false; player.setPosition(Vector2f(80, 380));
                    for (int i = 0; i < nMeteor; ++i)meteor[i].restart();
                    DestructAnim.Frame = 5; DestructAnim.Frame1 = 15;
                }
                else {
                    destruction.setTextureRect(IntRect(DestructAnim.Frame, DestructAnim.Frame1, 95, 80));
                }
            }
        }

        else {
            if (clockAnimPlay.getElapsedTime() > milliseconds(100)) {
                clockAnimPlay.restart();
                playerAnim(player, FramePlAnim, traffic);
            }

            if (clockAnimMeteor.getElapsedTime() > milliseconds(80)) {
                clockAnimMeteor.restart();
                for (int i = 0; i < nMeteor; ++i) meteor[i].animation();
            }

            gamingBackGround.move(-0.2 * timeGamingBackGround, 0);
            pos = gamingBackGround.getPosition();
            if (pos.x < -1280) gamingBackGround.setPosition(1280, pos.y);

            gamingBackGround2.move(-0.2 * timeGamingBackGround, 0);
            pos = gamingBackGround2.getPosition();
            if (pos.x < -1280) gamingBackGround2.setPosition(1280, pos.y);

            playerMove(player, moveRec);//Движение космического корабля
            for (int i = 0; i < nMeteor; ++i) {
                meteor[i].move(timeMeteor);
                if (meteor[i].collision(player.getGlobalBounds())) {
                    GameOver = true;
                    destruction.setPosition(player.getPosition().x, player.getPosition().y); 
                    break;
                }
            }

        }
        window.clear();
        window.draw(gamingBackGround);
        window.draw(gamingBackGround2);

        window.draw(GameInfoPanel);
        if (GameOver) window.draw(destruction); else window.draw(player);
        for (int i = 0; i < nMeteor; ++i) meteor[i].draw(window);
        window.display();
    }

    return 0;
}