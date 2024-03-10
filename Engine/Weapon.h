#pragma once
#include <vector>
#include <algorithm>
#include <string>
#include  "Graphics.h"
#include "Surface.h"
#include "Vec2.h"
#include "Upgrades.h"
#include "Enemy.h"

struct Banana {
	Banana(const Vec2& pos, const Vec2& dir, int dmg, float speed, const Surface & sprite)
		:
		pos(pos),
		dir(dir),
		dmg(dmg),
		speed(speed),
		sprite(sprite)
	{}
	Vec2 pos;
	Vec2 dir;
	int dmg;
	float speed;
	Surface sprite;
	bool hit = false;
};

class Weapon {
public:
	Weapon() = default;
	void Shoot(const Vec2 & pos, const Vec2 & dir, const Upgrades& up);
	void Update(float dt, const std::vector<Enemy>& enemy);
	void Draw(Graphics& gfx) const;
	std::vector<Banana>bananas;

private:
	int quantity = 1;
	float speed = 10.0f;

	int damage[3] = { 1, 5, 20 };
	const Surface bananaSprite[3]  = { Surface("Images/banana25x20green.bmp"),
										Surface("Images/banana25x20yellow.bmp"),
									    Surface("Images/banana25x20black.bmp") };
};