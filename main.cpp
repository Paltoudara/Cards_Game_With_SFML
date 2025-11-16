#include"Header1.h"
struct abilities {
    bool ability1;//play
    bool ability2;//draw
    bool ability3;//change color
};
int main() {
    sf::RenderWindow window(sf::VideoMode({ 2560, 1440 }), 
        "SFML works!",sf::State::Fullscreen);
    window.setFramerateLimit(60);
    std::vector<std::string>file_paths{};
    load_file_paths(file_paths);
    std::vector<sf::Texture> textures;  // must stay alive!
    std::vector<std::pair<std::size_t, sf::Sprite>> deck{};
   
    load_textures_from_files(textures,deck, file_paths);
    
    std::unordered_map<std::size_t,std::string>names{};
    
    for (std::size_t i = 1; i <= 52; i++) {
        std::string name{ file_paths[i - 1].substr(81) };
        names[i]={ name.begin(),name.begin() + name.find('.') };
    }
    shuffle_deck(deck);
    std::unordered_map<std::size_t, sf::Sprite>player1{};
    std::unordered_map<std::size_t, sf::Sprite>player2{};
    std::pair<std::size_t, sf::Sprite>table{deck.back().first,
    deck.back().second};
    deck.pop_back();
    
    give_players_cards(player1, player2, deck);
    std::string color{};
    std::string num{};
    std::vector<std::string>colors{ "clubs","diamonds"
        ,"hearts","spades" };
    if (names[table.first].contains('A')) {
        color = rand() % 4;
        num = "A";
    }
    else {
        if (names[table.first].contains("clubs")) {
            color = "clubs";
            num =names[table.first]
                .substr( names[table.first].find_last_of('_')+1);
        }
        else if (names[table.first].contains("diamonds")) {
            color = "diamonds";
            num = names[table.first]
                .substr(names[table.first].find_last_of('_')+1);
        }
        else if (names[table.first].contains("hearts")) {
            color = "hearts";
            num = names[table.first]
                .substr(names[table.first].find_last_of('_')+1);
        }
        else {
            color = "spades";
            num = names[table.first]
                .substr(names[table.first].find_last_of('_')+1);
        }
       
    }

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::Green);
        std::size_t i{ 0 };
        float j{0 };
        for ( auto& [key, value]:player1) {
            value.setPosition({ 200.0f + i * 300.0f, 100.0f+j });
            i++;
            if (i % 7==0) {
                j += 100.0f;
                i = 0;
            }
            window.draw(value);
        }
        i = 0;
        j = 1;
        for ( auto& [key, value] : player2) {
            value.setPosition({ 200.f + i * 300.f, 1240.f-j });
            i++;
            if (i % 7==0) {
                j += 100.0f;
                i = 0;
            }
            window.draw(value);
        }
        table.second.setPosition({ 1100.f, 720.f });
        window.draw(table.second);
        window.display();
        //player1
        bool can_play = false;
        for (const auto& [key, value] : player1) {
            if (names[key].contains(color)) {
                can_play = true;
                break;
            }
            if (names[key].contains(num)) {
                can_play = true;
                break;
            }
        }
        if (can_play) {
            //play a card
            while (true) {
                std::optional<sf::Event> event = window.pollEvent();
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    window.close();
                }
            }
        }
        else {
            //draw a card 
        }
        //
        can_play = false;
        for (const auto& [key, value] : player2) {
            if (names[key].contains(color)) {
                can_play = true;
                break;
            }
            if (names[key].contains(num)) {
                can_play = true;
                break;
            }
        }
        if (can_play) {
            //play card
            while (true) {
                std::optional<sf::Event> event = window.pollEvent();
                if (event->is<sf::Event::MouseButtonPressed>()) {
                 
                }
            }
        }
        else {
            //draw a card
        }
    }
  
    
  
}

