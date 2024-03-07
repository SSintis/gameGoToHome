#include "workLibGame.h"

void playerMove(Sprite & player, Vector2f & moveRec)
{
    player.move(moveRec);
    Vector2f pos = player.getPosition();

    if (pos.x > 1200) player.setPosition(1200, pos.y);
    if (pos.x < 50) player.setPosition(50, pos.y);
    if (pos.y > 670) player.setPosition(pos.x, 670);
    if (pos.y < 120) player.setPosition(pos.x, 120);

    if ((pos.x > 1200) && (pos.y < 120)) player.setPosition(1200, 120);
    if ((pos.x > 1200) && (pos.y > 670)) player.setPosition(1200, 670);
    if ((pos.x < 50) && (pos.y < 120)) player.setPosition(50, 120);
    if ((pos.x < 50) && (pos.y > 670)) player.setPosition(50, 670);
}

void playerAnim(Sprite& player, FrameAnim& FramePlAnim, int traffic)
{
    FramePlAnim.Frame += FramePlAnim.Step;
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));
    if (traffic) if (FramePlAnim.Frame > 0) FramePlAnim.Step = -100;
    else FramePlAnim.Step = 0;
    else {
        if (FramePlAnim.Frame == 800) FramePlAnim.Step = 0;
        if (FramePlAnim.Frame <= 700) FramePlAnim.Step = 100;
    }
}
