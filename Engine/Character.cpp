#include "Character.h"

Character::Character(const Vec2& pos, const std::string& nameFile)
	:
	pos(pos),
	sprite(nameFile)
{
	for (int i = 0; i < (int)Sequence::StandingLeft; i++)
	{
		animations.emplace_back(0, 50 * i, 50, 50, 5, sprite, 0.2f);
	}
	for (int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++)
	{
		animations.emplace_back(0, 50 * (i - (int)Sequence::StandingLeft), 50, 50, 1, sprite, 0.001f);
	}
}

void Character::Draw(Graphics& gfx) const
{
	if (effectActive)
	{
		animations[(int)iCurSequence].DrawColor((Vei2)pos, gfx, Colors::Blue);
	}
	else
	{
		animations[(int)iCurSequence].Draw((Vei2)pos, gfx);
	}

	weapon.Draw(gfx);
}

void Character::SetDirection(const Vec2& dir)
{
	if (dir.x < 0.0f)
	{
		iCurSequence = Sequence::WalkingLeft;
	}
	else if (dir.x > 0.0f)
	{
		iCurSequence = Sequence::WalkingRight;
	}
	else if (dir.y < 0.0f)
	{
		iCurSequence = Sequence::WalkingUp;
	}
	else if (dir.y > 0.0f)
	{
		iCurSequence = Sequence::WalkingDown;
	}
	else
	{
		if (vel.x < 0.0f)
		{
			iCurSequence = Sequence::StandingLeft;
		}
		else if (vel.x > 0.0f)
		{
			iCurSequence = Sequence::StandingRight;
		}
		else if (vel.y < 0.0f)
		{
			iCurSequence = Sequence::StandingUp;
		}
		else if (vel.y > 0.0f)
		{
			iCurSequence = Sequence::StandingDown;
		}
	}
	dirForBananas = dir;
	vel = dir * speed;
}

void Character::Update(float dt, const std::vector<Enemy>& enemy, const Keyboard& kbd)
{
	pos += vel * dt;
	animations[(int)iCurSequence].Update(dt);

	if (effectActive)
	{
		effectTime += dt;
		if (effectTime >= effectDuration)
		{
			effectActive = false;
		}
	}

	if (0 < weapon.bananas.size())
	{
		weapon.Update(dt, enemy);
	}

	if (kbd.KeyIsPressed(VK_SPACE))
	{
		weapon.Shoot(pos, dirForBananas, upgrades);
	}
}

void Character::ActivateEffect()
{
	effectActive = true;
	effectTime = 0.0f;
}

