#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Item {
private:
	std::string textureId;
	std::string name;
	int id;

public:

	Item();
	Item(std::string x_textureId, std::string x_name, int x_id);

	std::string getTextureId();
	std::string getName();
	int getId();

	void setTextureId(std::string &newTextureId);
	void setName(std::string& newName);

	
};