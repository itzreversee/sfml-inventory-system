
#include <map>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Scene.h"

void Scene::addSprite(std::string& name, sf::Sprite sprite) {
	try {
		sceneSprites[name] = sprite;
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

void Scene::deleteSprite(std::string& name) {
	try {
		sceneSprites.erase(name);
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

sf::Sprite Scene::getSprite(std::string& name) {
	try {
		return sceneSprites[name];
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		return sceneSprites[name];
	}
}

void Scene::changeSpriteTexture(std::string& textureId, std::string& name, Scene &sceneManager) {
	sf::Texture& texture = sceneManager.holder[textureId];
	sceneSprites[name].setTexture(texture);
}

bool Scene::doesSpriteExist(std::string& name) {
	if (sceneSprites.count(name) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::map<std::string, sf::Sprite> Scene::getSpriteMap() {
	return sceneSprites;
}

std::map<std::string, sf::Sprite> Scene::getSpritesTouchingMouse(sf::Mouse& mouse, sf::RenderWindow& window) {

	std::map<std::string, sf::Sprite> listOfTouching;

	// iterate over sceneSprites and add it to the map if it's touching the mouse
	for (const auto& it : sceneSprites) {
		if (it.second.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
			//std::cout << it.first << " : Touching! " << std::endl;
			listOfTouching[it.first] = it.second;
		}
	}
	return listOfTouching;
}

std::vector<std::string> Scene::getSpriteTouchingOtherSprites(std::string& name) {

	std::vector<std::string> listOfTouching;

	// if none return empty string
	if (name == "") {
		return listOfTouching;
	}
	
	sf::Sprite toucher = sceneSprites[name];

	// iterate over sceneSprites and add them to the vector, remove it's own entry from that map
	for (const auto& it : sceneSprites) {
		if (it.second.getGlobalBounds().contains(toucher.getPosition().x, toucher.getPosition().y)) {
			//std::cout << it.first << " : Touching! " << std::endl;
			if (it.first == name) {
				continue;
			}
			listOfTouching.push_back(it.first);
		}
	}

	return listOfTouching;
}

void Scene::setSpritePosition(std::string& name, sf::Vector2f& new_position) {
	sceneSprites[name].setPosition(new_position);
}

sf::Vector2f Scene::getSpritePosition(std::string& name) {
	return sceneSprites[name].getPosition();
}