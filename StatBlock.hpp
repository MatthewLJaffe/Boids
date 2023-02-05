#pragma once
#include "ECS.hpp"
#include "SliderComponent.hpp"
#include "EntityManager.hpp"

class StatBlock : public Component
{
public:
	StatBlock(std::vector<SliderComponent*> sliders, bool enabled);
	void update() override;
	void init() override;
	void adjustStatBlock(float yDisplacment);
	void toggleBlockVisibility();
	static std::vector<StatBlock*> statBlocks;
	std::vector<SliderComponent*> sliders;
	SpriteComponent* buttonSprite;
	TextComponent* blockTitle;
private:
	bool _enabled = false;
	bool _selected = false;
	float _buttonRadius = 0;
	float _blockHeight = 0;
	Entity* _slidersParent;
	const float sliderSpacing = 30;

};