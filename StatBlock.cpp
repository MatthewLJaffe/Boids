#include "StatBlock.hpp"

std::vector<StatBlock*> StatBlock::statBlocks;


StatBlock::StatBlock(std::vector<SliderComponent*> sliders, bool enabled)
{
	this->_buttonRadius = 13;
	statBlocks.push_back(this);
	this->sliders = sliders;
	this->_blockHeight = static_cast<float>(sliders.size()) * sliderSpacing;
	this->_enabled = enabled;
	_slidersParent = &EntityManager::Instance().addEntity(0);
	for (size_t i = 0; i < sliders.size(); i++)
		_slidersParent->addChild(sliders[i]->entity);
	_slidersParent->setActive(enabled);
}

void StatBlock::init()
{
	buttonSprite = &entity->getComponent<SpriteComponent>();
	blockTitle = &entity->getComponent<TextComponent>();
	if (_enabled)
	{
		buttonSprite->setSprite(Assets::Instance().arrowDown);
	}
	else
		buttonSprite->setSprite(Assets::Instance().arrowRight);
}

void StatBlock::update()
{
	if (InputManager::Instance().getMousePressed())
	{
		Vector2 buttonCenter = buttonSprite->pos + Vector2(_buttonRadius, _buttonRadius);
		if (buttonCenter.distance(InputManager::Instance().getMousePos()) < _buttonRadius)
		{
			_selected = true;
		}
	}
	if (InputManager::Instance().getMouseReleased() && _selected)
	{
		_selected = false;
		Vector2 buttonCenter = buttonSprite->pos + Vector2(_buttonRadius, _buttonRadius);
		if (buttonCenter.distance(InputManager::Instance().getMousePos()) < _buttonRadius)
		{
			_enabled = !_enabled;
			toggleBlockVisibility();
		}
	}
}

void StatBlock::toggleBlockVisibility()
{
	bool offset = false;
	for (size_t i = 0; i < statBlocks.size(); i++)
	{
		if (statBlocks[i] == this)
		{
			offset = true;
			continue;
		}
		if (offset)
		{
			if (_enabled)
				statBlocks[i]->adjustStatBlock(_blockHeight);
			else
				statBlocks[i]->adjustStatBlock(-_blockHeight);
		}
	}
	if (_enabled)
		buttonSprite->setSprite(Assets::Instance().arrowDown);
	else
		buttonSprite->setSprite(Assets::Instance().arrowRight);
	_slidersParent->setActive(_enabled);
}

void StatBlock::adjustStatBlock(float yDisplacment)
{
	buttonSprite->pos.y += yDisplacment;
	blockTitle->pos.y += yDisplacment;
	for (auto slider : sliders)
	{
		Vector2 sliderPos = slider->getPos();
		slider->setPos(Vector2(sliderPos.x, sliderPos.y + yDisplacment));
	}
}

