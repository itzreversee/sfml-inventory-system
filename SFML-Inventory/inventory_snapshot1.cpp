
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cerrno>

#include "Scene.h"

void render(sf::RenderWindow &window, Scene &sceneManager) {

    std::map<std::string, sf::Sprite> sceneSprites = sceneManager.getSpriteMap();

    for (auto it = sceneSprites.begin(); it != sceneSprites.end(); ++it)
    {
        window.draw(it->second);
    }

}

void tick(sf::RenderWindow& window) {

}

int loop(sf::RenderWindow &window, Scene &sceneManager) {
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
            
        // Inventory Logic

        // Display Things
        window.display();
    }

    return 0;
}

sf::Texture load_texture(sf::Texture &texture, const std::string &path) {
    try 
    {
        if (!texture.loadFromFile(path)) {
                std::cerr << "Error loading texture: " << path;
        }
        return texture;
    }
    catch ( std::exception &e )
    {
        std::cerr << e.what() << std::endl;
        return texture;
    }
    
}

int main()
{

    // Load Textures
    sf::Texture texture_grid_obj;
    sf::Texture texture_coin;
    sf::Texture texture_sword;
    sf::Texture texture_stick;

    load_texture(texture_grid_obj, "resources/grid_object.png");
    load_texture(texture_coin, "resources/coin.png");
    load_texture(texture_sword, "resources/sword.png");
    load_texture(texture_stick, "resources/stick.png");

    // Create Sprites 
    sf::Sprite sprite_grid_obj;
    sf::Sprite sprite_coin;
    sf::Sprite sprite_sword;
    sf::Sprite sprite_stick;

    sprite_grid_obj.setTexture(texture_grid_obj);
    sprite_coin.setTexture(texture_coin);
    sprite_sword.setTexture(texture_sword);
    sprite_stick.setTexture(texture_stick);

    // Move to positions

    sprite_grid_obj.move(100, 0);
    sprite_coin.move(200, 0);
    sprite_sword.move(300, 0);

    // Add sprites to the Scene

    Scene sceneManager = Scene();

    std::string gird_object_id = "grid_object_id";
    std::string coin_id = "coin";
    std::string sword_id = "sword";
    std::string stick_id = "stick";

    sceneManager.addSprite(gird_object_id, sprite_grid_obj);
    sceneManager.addSprite(coin_id, sprite_coin);
    sceneManager.addSprite(sword_id, sprite_sword);
    sceneManager.addSprite(stick_id, sprite_stick);

    // Create Window
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Inventory");

    return loop(window, sceneManager);
}