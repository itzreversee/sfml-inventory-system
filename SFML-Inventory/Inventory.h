#pragma once

#include <vector>
#include <map>

#include "Item.h"
#include "Scene.h"

#include <Thor/Resources.hpp>

class Inventory {
private:
	std::vector<Item> items;
	std::map<int, std::string> sprite_item_map;

	std::string defaultTextureId;
	int slots;
public:

	Inventory();
	Inventory(int slots);

	void updateTextures(Scene& sceneManager);
	void setDefaultTextureId(std::string& textureId);
	std::string getDefaultTextureId();

	void addItem(Item &item, int slot);
	Item getItem(int &slot);

	void mapSpriteId(int int_id, std::string str_id);
	std::string getItemStringId(int &int_id);
	int getItemIntId(std::string &str_id);
	 
	void swap_places(int& slot_a, int& slot_b);

	std::vector<Item> getAllItems();
};