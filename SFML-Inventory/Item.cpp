
#include <SFML/Graphics.hpp>

#include <string>

#include "Item.h"

Item::Item() {
	name = (std::string)"Missing Item!";
	id = 666;
}

Item::Item(std::string x_textureId, std::string x_name, int x_id) {
	textureId = x_textureId;
	name = x_name;
	id = x_id;
}

std::string Item::getTextureId() {
	return textureId;
}

std::string Item::getName() {
	return name;
}

int Item::getId() {
	return id;
}

void Item::setTextureId(std::string &newTextureId) {
	textureId = newTextureId;
}

void Item::setName(std::string& newName) {
	name = newName;
}