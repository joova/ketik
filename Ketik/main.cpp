
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "RichText.hpp"


bool cek_ketik(char* file, char c, int idx){
    if(file[idx] == c){
        return true;
    } else {
        return false;
    }
}

void format_text(sfe::RichText &richText, char* file, int idx, bool cek) {
    std::string str(file);
    int len = str.length();
    
    //cek jika idx lebih dari len
    if((idx + 1) > len)
        return;
    
//    std:: cout << idx << "," << len << " : "<< kiri << " | " << pos << " | " << kanan << std::endl;
    
    richText.clear();
    
    std::string pos = str.substr(idx, 1);
    std::string kiri = str.substr(0, idx);
    std::string kanan = str.substr(idx + 1, len - idx);
    
    richText << sf::Color(0, 0, 0, 255) << kiri;
    if(cek == true) {
        richText << sf::Color(67, 160, 71, 255) << pos;
    }else {
        richText << sf::Color::Red << pos;
    }
    richText << sf::Color(0, 0, 0, 50) << kanan;

}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    // Performance
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(false);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    
    int idx = 0;
    char file[] = "the build phase will copy the required frameworks";
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text(file, font, 50);
    text.setFillColor(sf::Color(0,0,0,100));
    
    sfe::RichText richText(font);
    richText << sf::Color(0, 0, 0, 100) << file;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Check key press
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char c =  static_cast<char>(event.text.unicode);
                    
                    bool cek = cek_ketik(file, c, idx);
//                    std::cout << r << std::endl;
                    format_text(richText, file, idx, cek);
                    
                    idx++;
                }
            }
        }

        // Clear screen
        window.clear(sf::Color::White);

        // Draw the string
        window.draw(richText);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
