#include "Weapon.h"
#include "Enemy.h"
#include "SpriteEffect.h"

#include <random>
#include <algorithm>
#include <vector>

void Weapon::Shoot(const Vec2& pos, const Vec2& dir, const Upgrades& up)
{
	int iOfBanana = up.bananaBlack ? 2 : up.bananaYellow ? 1 : 0;
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int>colorOfBanana(0, iOfBanana);

	Vec2 tempDir = dir;

	for (size_t i = 0; i < quantity; ++i)
	{
		int r = colorOfBanana(rng);
  		bananas.emplace_back(Banana{ pos, tempDir, damage[r], speed, bananaSprite[r] });
		tempDir -= Vec2(0.1f, 0.1f); // do zmiany
	}
}

void Weapon::Update(float dt, const std::vector<Enemy> & enemy)
{
	// clean
	// 
	//for (size_t i = 0; i < bananas.size(); ++i)
	//{
	//	if (!Graphics::GetScreenRect().Contains(Vei2(bananas[i].pos)) ) //|| bananas[i].speed <= 0)
	//	{
	//		bananas[i].hit = true;
	//	}
	//	else
	//	{
	//		for (size_t j = 0; j < enemy.size(); ++j)
	//		{
	//			bananas[i].hit = enemy[j].GetRect().Contains(Vei2(bananas[i].pos));
	//		}
	//	}
	//}

	//if (bananas.size() > 0)
	//{
    //   	bananas.erase(std::remove_if(bananas.begin(), bananas.end(), [](const Banana& banana) {
	//		return banana.hit == true;
	//	}), bananas.end());
	//}

	// move
	for (size_t i = 0; i < bananas.size(); ++i)
	{
		bananas[i].pos += bananas[i].dir * bananas[i].speed;
		//bananas[i].speed -= std::max(bananas[i].speed - bananas[i].speed * 0.99f, 0.25f); // do zmiany
	}
}

void Weapon::Draw(Graphics& gfx) const
{
	for (const Banana& banana : bananas)
	{
		gfx.DrawSprite(banana.pos.x, banana.pos.y, banana.sprite, SpriteEffect::Chroma{});
	}
}
