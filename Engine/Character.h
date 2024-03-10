#pragma once
#include <string>
#include <vector> 
#include "Graphics.h"
#include "Animation.h"
#include "Surface.h"
#include "Weapon.h"
#include "Upgrades.h"
#include "Enemy.h"
#include "Keyboard.h"

class Character
{
private:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};
public:
	Character(const Vec2& pos, const std::string & nameFile);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2& dir);
	void Update(float dt, const std::vector<Enemy> & enemy, const Keyboard & kbd);
	void ActivateEffect();
private:
	Vec2 dirForBananas = Vec2{ 0.0f, 0.0f };
	Weapon weapon;
	Upgrades upgrades;

	Vec2 pos;
	Vec2 vel = {0.0f, 0.0f};
	std::vector<Animation> animations;
	Surface sprite;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 200;
	static constexpr float effectDuration = 0.045f;
	float effectTime = 0.0f;
	bool effectActive = false;
};
