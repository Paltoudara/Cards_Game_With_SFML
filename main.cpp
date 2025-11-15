#include"header.h"

int main() {
   /* sf::RenderWindow window(sf::VideoMode({ 2560, 1440 }), 
        "SFML works!",sf::State::Fullscreen);*/
    std::vector<std::string>file_paths{};
    load_file_paths(file_paths);
    std::unordered_map<std::size_t, sf::Texture> deck{};
    load_textures_from_files(deck, file_paths);
    std::vector<std::size_t>values{};
    std::unordered_map<std::size_t,std::string>map{};
    //create a map of sprites
    for (std::size_t i = 1; i <= 52; i++) {
        std::string name{ file_paths[i - 1].substr(81) };
        map[i]={ name.begin(),name.begin() + name.find('.') };
    }
    
   /* while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
       
        window.display();
    }*/
}
