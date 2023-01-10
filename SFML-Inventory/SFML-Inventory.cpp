
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cerrno>

#include "Scene.h"
#include "Inventory.h"
#include "Item.h"
#include "SFML-Inventory.h"

/* Deprecated, use sceneManager.acquire() instead
sf::Texture load_texture(sf::Texture& texture, const std::string& path) {
    try
    {
        if (!texture.loadFromFile(path)) {
            std::cerr << "Error loading texture: " << path;
        }
        return texture;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return texture;
    }

}
*/
void render(sf::RenderWindow &window, Scene &sceneManager) {

    std::map<std::string, sf::Sprite> sceneSprites = sceneManager.getSpriteMap();

    for (auto it = sceneSprites.begin(); it != sceneSprites.end(); ++it)
    {
        window.draw(it->second);
    }

}

bool GLOBAL_MOUSE_PRESSED = false;      // is mouse left button pressed at all
bool isDragging = false;                // internal variable used for checking if mouse still dragging a object
std::string dragging_name = "";         // sprite that the user is dragging ( a pointer to save memory )
sf::Vector2f dragger_original_position; // original sprite position

void tick(sf::RenderWindow& window, Scene& sceneManager, sf::Mouse &mouse, Inventory &inv) {

    // check if mouse button pressed
    if (mouse.isButtonPressed(mouse.Left))
        GLOBAL_MOUSE_PRESSED = true;
    else
        GLOBAL_MOUSE_PRESSED = false;

    // Get list of touching sprites
    std::map<std::string, sf::Sprite> listOfTouching = sceneManager.getSpritesTouchingMouse(mouse, window);

    // get mouse position
    sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    // TODO: Delete ( debug )
    //std::cout << "mousePosition = " << mousePosition.x << " : " << mousePosition.y << std::endl;
    //std::cout << " GLOBAL MOUSE PRESSED? " << GLOBAL_MOUSE_PRESSED << ", listOfTouching.size() > 0? " << (listOfTouching.size() > 0) << std::endl;

    if (GLOBAL_MOUSE_PRESSED) {

        if (listOfTouching.size() > 0)
        {
       
        std::string dragger_str;
        sf::Sprite dragger;

        if (dragging_name == "") // check if not dragging any sprite
        {
            // get sprite info
            dragger_str = listOfTouching.begin()->first;
            dragger = listOfTouching.begin()->second;

            dragging_name = dragger_str;

            // get sprite original position
            dragger_original_position = dragger.getPosition();
        }
        else
        {
            // assign 
            dragger_str = dragging_name;
            dragger = sceneManager.getSprite(dragger_str);
        }

        // move sprite to mouse
        sceneManager.setSpritePosition(dragger_str, mousePosition);

        // TODO: Delete ( debug )
        //std::cout << dragger.getPosition().x << " : " << dragger.getPosition().y << std::endl;

        isDragging = true;

        }

    }
    else {

        // get list of touched sprites
        std::vector<std::string> touching = sceneManager.getSpriteTouchingOtherSprites(dragging_name);
        if (touching.size() > 0) { 
            // if not empty ( grab the first one )
            
            // TODO: Delete ( debug )
            //std::cout << "touched_id : " << touching[0] << std::endl;
            
            // get corresponding item id of both items
            int touching_id, toucher_id;

            touching_id = inv.getItemIntId(touching[0]);
            toucher_id  = inv.getItemIntId(dragging_name);

            inv.swap_places(toucher_id, touching_id);

            sceneManager.setSpritePosition(dragging_name, dragger_original_position);
            
        }
        else if (isDragging) {
            // else reset to original position
            sceneManager.setSpritePosition(dragging_name, dragger_original_position);
        }
        
        isDragging = false;
        dragging_name = "";
    }

    // TODO: Delete ( debug )
    //std::cout << "isDragging : " << isDragging << std::endl;

}

Inventory prepInventory(Scene &sceneManager) {
    // prep inventory
    Inventory inv = Inventory(9);

    std::string default_texture_id = "grid_object";
    inv.setDefaultTextureId(default_texture_id);

    sf::Texture texture_coin;
    sf::Texture texture_sword;
    sf::Texture texture_stick;

    sceneManager.holder.acquire("texture_coin", thor::Resources::fromFile<sf::Texture>("resources/coin.png"));
    sceneManager.holder.acquire("texture_sword", thor::Resources::fromFile<sf::Texture>("resources/sword.png"));
    sceneManager.holder.acquire("texture_stick", thor::Resources::fromFile<sf::Texture>("resources/stick.png"));

    texture_coin = sceneManager.holder["texture_coin"];
    texture_sword = sceneManager.holder["texture_sword"];
    texture_stick = sceneManager.holder["texture_stick"];

    std::string coin_name = "Coin";
    std::string sword_name = "Sword";
    std::string stick_name = "Stick";

    Item coin = Item("texture_coin", coin_name, 0);
    Item sword = Item("texture_sword", sword_name, 1);
    Item stick = Item("texture_stick", stick_name, 2);

    inv.addItem(coin, 0);
    inv.addItem(sword, 1);
    inv.addItem(stick, 2);

    std::string grid_id_0 = "grid_0";
    std::string grid_id_1 = "grid_1";
    std::string grid_id_2 = "grid_2";
    std::string grid_id_3 = "grid_3";
    std::string grid_id_4 = "grid_4";
    std::string grid_id_5 = "grid_5";
    std::string grid_id_6 = "grid_6";
    std::string grid_id_7 = "grid_7";
    std::string grid_id_8 = "grid_8";

    inv.mapSpriteId(0, grid_id_0);
    inv.mapSpriteId(1, grid_id_1);
    inv.mapSpriteId(2, grid_id_2);
    inv.mapSpriteId(3, grid_id_3);
    inv.mapSpriteId(4, grid_id_4);
    inv.mapSpriteId(5, grid_id_5);
    inv.mapSpriteId(6, grid_id_6);
    inv.mapSpriteId(7, grid_id_7);
    inv.mapSpriteId(8, grid_id_8);

    return inv;
}

int loop(sf::RenderWindow &window, Scene &sceneManager) {

    Inventory inv = prepInventory(sceneManager);

    sf::Mouse mouse;

    while (window.isOpen())
    {
        // Clear Window
        window.clear();

        // Pool Events
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
        }

        // Render Here
        render(window, sceneManager);
            
        // Tick Here
        inv.updateTextures(sceneManager);
        tick(window, sceneManager, mouse, inv);

        // Display Things
        window.display();
    }

    return 0;
}

int main()
{
    GLOBAL_MOUSE_PRESSED = false;

    // Initialize Scene 
    Scene sceneManager = Scene();

    // Load Textures
    sf::Texture texture_grid_obj;

    sceneManager.holder.acquire("grid_object", thor::Resources::fromFile<sf::Texture>("resources/grid_object.png"));

    texture_grid_obj = sceneManager.holder["grid_object"];

    // Create Sprites 
    sf::Sprite grid_space_0;
    sf::Sprite grid_space_1;
    sf::Sprite grid_space_2;
    sf::Sprite grid_space_3;
    sf::Sprite grid_space_4;
    sf::Sprite grid_space_5;
    sf::Sprite grid_space_6;
    sf::Sprite grid_space_7;
    sf::Sprite grid_space_8;

    grid_space_0.setTexture(texture_grid_obj);
    grid_space_1.setTexture(texture_grid_obj);
    grid_space_2.setTexture(texture_grid_obj);
    grid_space_3.setTexture(texture_grid_obj);
    grid_space_4.setTexture(texture_grid_obj);
    grid_space_5.setTexture(texture_grid_obj);
    grid_space_6.setTexture(texture_grid_obj);
    grid_space_7.setTexture(texture_grid_obj);
    grid_space_8.setTexture(texture_grid_obj);

    // Move to positions
    grid_space_0.setOrigin(0, 0);
    grid_space_1.setOrigin(0, 0);
    grid_space_2.setOrigin(0, 0);

    grid_space_3.setOrigin(0, 0);
    grid_space_4.setOrigin(0, 0);
    grid_space_5.setOrigin(0, 0);

    grid_space_6.setOrigin(0, 0);
    grid_space_7.setOrigin(0, 0);
    grid_space_8.setOrigin(0, 0);


    grid_space_0.setPosition(32, 32);
    grid_space_1.setPosition(128, 32);
    grid_space_2.setPosition(224, 32);
    
    //grid_space_0.setPosition(96, 96);
    //grid_space_1.setPosition(192, 96);
    //grid_space_2.setPosition(288, 96);

    grid_space_3.setPosition(32, 128);
    grid_space_4.setPosition(128, 128);
    grid_space_5.setPosition(224, 128);

    grid_space_6.setPosition(32, 224);
    grid_space_7.setPosition(128, 224);
    grid_space_8.setPosition(224, 224);


    // Add sprites to the Scene

    std::string grid_id_0 = "grid_0";
    std::string grid_id_1 = "grid_1";
    std::string grid_id_2 = "grid_2";
    std::string grid_id_3 = "grid_3";
    std::string grid_id_4 = "grid_4";
    std::string grid_id_5 = "grid_5";
    std::string grid_id_6 = "grid_6";
    std::string grid_id_7 = "grid_7";
    std::string grid_id_8 = "grid_8";

    sceneManager.addSprite(grid_id_0, grid_space_0);
    sceneManager.addSprite(grid_id_1, grid_space_1);
    sceneManager.addSprite(grid_id_2, grid_space_2);

    sceneManager.addSprite(grid_id_3, grid_space_3);
    sceneManager.addSprite(grid_id_4, grid_space_4);
    sceneManager.addSprite(grid_id_5, grid_space_5);

    sceneManager.addSprite(grid_id_6, grid_space_6);
    sceneManager.addSprite(grid_id_7, grid_space_7);
    sceneManager.addSprite(grid_id_8, grid_space_8);

    // Create Window
    sf::RenderWindow window(sf::VideoMode(384, 384), "SFML Inventory");

    return loop(window, sceneManager);
}