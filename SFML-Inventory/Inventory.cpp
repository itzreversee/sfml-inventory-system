
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include <string>
#include <iostream>

#include "Item.h"
#include "Inventory.h"
#include "Scene.h"


Inventory::Inventory() {

}

Inventory::Inventory(int slots_) {
	items.reserve(slots_); // reserve space for x item slots in inventory
	items.resize(slots_);
	slots = slots_;
}

void Inventory::updateTextures(Scene& sceneManager) {
	
	Item item_;
	std::string item_texture_id;

	// iterate over items
	int i = 0;
	while (i < slots) {
		item_ = getItem(i);
		item_texture_id = item_.getTextureId();

		// if empty item
		if (item_.getId() == 666) {
			// if default texture id was not saved, continue ( this will create graphical bugs )
			if (defaultTextureId == (std::string)"") {
				i++;
				continue;
			}
			// else set it's texture to the default one
			item_texture_id = defaultTextureId;
		}

		// and use sceneManager to change it's texture
		sceneManager.changeSpriteTexture(item_texture_id, sprite_item_map[i], sceneManager);
		i++;
	}
}

void Inventory::setDefaultTextureId(std::string& textureId) {
	defaultTextureId = textureId;
}

std::string Inventory::getDefaultTextureId() {
	return defaultTextureId;
}

void Inventory::addItem(Item &item, int slot) {
	try {
		items[slot] = item;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Item Inventory::getItem(int &slot) {
	try {
		return items[slot];
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return items[slot];
	}
}

void Inventory::mapSpriteId(int int_id, std::string str_id) {
	sprite_item_map[int_id] = str_id;
}

std::string Inventory::getItemStringId(int &int_id) {
	for (auto& it : sprite_item_map) {
		if (it.first == int_id) {
			return it.second;
		}
	}

	return "";
}

int Inventory::getItemIntId(std::string &str_id) {
	for (auto& it : sprite_item_map) {
		if (it.second == str_id) {
			return it.first;
		}
	}
}

void Inventory::swap_places(int &slot_a, int &slot_b) {
	std::iter_swap(items.begin() + slot_a, items.begin() + slot_b);
}

std::vector<Item> Inventory::getAllItems() {
	return items;
}