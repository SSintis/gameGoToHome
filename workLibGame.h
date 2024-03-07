#pragma once
#include <SFML/Graphics.hpp>
#include "Meteor.h"
using namespace sf;

struct FrameAnim {
	int Frame = 0;
	int Step = 100;
	int Frame1 = 0;
	int Step1 = 100;
};

void playerMove(Sprite& player, Vector2f& moveRec);
void playerAnim(Sprite& player, FrameAnim& FramePlAnim, int traffic);