#pragma once

#include <map>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

class Scene {
private:
	std::map<std::string, sf::Sprite> sceneSprites;

public:
	thor::ResourceHolder<sf::Texture, std::string> holder;

	void addSprite(std::string& name, sf::Sprite sprite);
	void deleteSprite(std::string& name);

	sf::Sprite getSprite(std::string& name);

	void changeSpriteTexture(std::string &textureId, std::string& name, Scene& sceneManager);

	bool doesSpriteExist(std::string& name);

	std::map<std::string, sf::Sprite> getSpriteMap();

	std::map<std::string, sf::Sprite> getSpritesTouchingMouse(sf::Mouse& mouse, sf::RenderWindow& window);
	std::vector<std::string> getSpriteTouchingOtherSprites(std::string& name);

	void setSpritePosition(std::string& name, sf::Vector2f& new_position);
	sf::Vector2f getSpritePosition(std::string & name);
};