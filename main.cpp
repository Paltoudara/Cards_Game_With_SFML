#include"header.h"
int main() {
    //for window
    sf::RenderWindow window(sf::VideoMode({ 2560, 1440 }),
        "SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    //
    std::vector<std::string>file_paths{};
    //load file paths for later to load the textures
    load_file_paths(file_paths);
    //
    std::vector<sf::Texture> textures;  // must stay alive!
    std::unordered_map<std::string, sf::Sprite>aces{};
    std::vector<std::pair<std::string, sf::Sprite>> deck{};
    //load textures from files
    load_textures_from_files(textures, deck, file_paths,
        aces);
    //
    std::unordered_map<std::string, sf::Sprite>player1{};
    std::unordered_map<std::string, sf::Sprite>player2{};
    //shuffle the deck
    shuffle_deck(deck);
    //
    sf::Sprite table{ deck.back().second };
    std::string color{};
    std::string num{};
    std::vector<std::string>colors{ "spades","hearts",
    "clubs","diamonds" };
    
    //initialize the game
    initialize(deck, color, num, table, aces, colors);
    //give each player 7 cards
    give_players_cards(player1, player2, deck);
    //
    //initialize flags
    bool flag{ true };
    bool mouseclicked{ false };
    bool p1{ false };
    bool p2{false };
    //
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                mouseclicked = true;
            }
        }
        if (mouseclicked) {
            mouseclicked = false;
            if (flag == true) 
            {
                if (can_he_play(player1, color, num)) {
                    if (check_for_card(window, player1, color,
                        num, table, aces, colors)) {
                        flag = false;
                    }
                }
                else {
                    if (deck.size()>0) {
                        player1.emplace(deck.back());
                        deck.pop_back();
                        if (!can_he_play(player1, color, num)) {
                            flag = false;
                        }

                    }
                    else {
                        p1 = true;
                    }
                }
            }
            else if (flag == false) {
                if (can_he_play(player2, color, num)) {
                    if (check_for_card(window, player2, color,
                        num, table, aces, colors)) {
                        flag = true;
                    }
                }
                else {
                    if (deck.size() > 0) {
                        player2.emplace(deck.back());
                        deck.pop_back();
                        if (!can_he_play(player2, color, num)) {
                            flag = true;
                        }
                    }
                    else {
                        p2 = true;
                    }
                }
            }
            if (player1.size() == 0) {
                std::cout << "player1 won\n";
                std::exit(0);
            }
            else if(player2.size()==0) {
                std::cout << "player2 won\n";
                std::exit(0);
            }
            
        }
        if (p1 && p2) {
            std::cout << "no player wins" << '\n';
        }
        else {
            p1 = false;
            p2 = false;
        }
        window.clear(sf::Color::Black);
        set_the_table_of_cards(window, player1, player2);
        table.setPosition({ 2560.f/2, 1440.f/2 });
        window.draw(table);
        window.display();
    }
}

