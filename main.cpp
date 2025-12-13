
#include"Header.h"
int main() {
    //for window
    menu();
    sf::VideoMode video{ sf::VideoMode::getDesktopMode() };
    sf::RenderWindow window(video,
        "SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    //rectangles
    sf::RectangleShape rectangle_p1{};
    sf::RectangleShape rectangle_p2{};
    rectangle_p1.setSize({ window.getSize().x / 2.f,window.getSize().y / 2.f });
    rectangle_p1.setFillColor(sf::Color::Blue);
    rectangle_p2.setSize({ (float)window.getSize().x,(float)window.getSize().y });
    rectangle_p2.setFillColor(sf::Color::Red);
    rectangle_p2.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
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
    //
    sf::Font font{};
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::exit(1);
    }
    sf::Text text{ font };
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                mouseclicked = true;
            }
        }
        //event happens check it
        if (mouseclicked) {
            mouseclicked = false;
            if (flag == true)//player1 turn
            {
                if (!can_he_play(player1, color, num)) {
                    if (deck.size() > 0) {
                        player1.emplace(deck.back());
                        deck.pop_back();
                        if (!can_he_play(player1, color, num)) {
                            flag = false;
                        }
                    }
                    else {
                        flag = false;
                    }
                }
                else if (check_for_card(window, player1, color,
                    num, table, aces, colors)) {
                    //special cards
                    if (num == "08"||num=="09") {
                        flag = true;
                        //i play again
                    }
                    else if (num== "07") {//special card
                        flag = false;
                        if (deck.size() >= 2) {
                            player2.emplace(deck.back());
                            deck.pop_back();
                            player2.emplace(deck.back());
                            deck.pop_back();
                        }
                        else {
                            while (deck.size() != 0) {
                                player2.emplace(deck.back());
                                deck.pop_back();
                            }
                        }
                    
                    }
                    else {
                        flag = false;
                    }
                }
            }
            else {//player2 turn
                if (!can_he_play(player2, color, num)) {
                    if (deck.size() > 0) {
                        player2.emplace(deck.back());
                        deck.pop_back();
                        if (!can_he_play(player2, color, num)) {
                            flag = true;
                        }
                    }
                    else {
                        flag = true;
                    }
                }
                else if (check_for_card(window, player2, color,
                    num, table, aces, colors)) {
                    if (num == "08" || num == "09") {
                        flag = false;
                    }
                    else if (num == "07") {//special card
                        flag = true;
                        if (deck.size() >= 2) {
                            player1.emplace(deck.back());
                            deck.pop_back();
                            player1.emplace(deck.back());
                            deck.pop_back();
                        }
                        else {
                            while (deck.size() != 0) {
                                player1.emplace(deck.back());
                                deck.pop_back();
                            }
                        }
                    }
                    else {
                        flag = true;
                    }
                }
            }
            //check if a player won
            if (player1.size() == 0) {
                window.close();
                winner(true);
                std::exit(0);
            }
            else if (player2.size() == 0) {
                window.close();
                winner(false);
                std::exit(0);
            }
            //
        }
        //draw because either can play and we have no cards
        if (!can_he_play(player1, color, num) && !can_he_play(player2, color, num)
            && deck.size() == 0) {
            window.close();
            draw();
            std::exit(0);
        }
        window.clear(sf::Color::Black);
        if (flag == true) {
            text.setFillColor(sf::Color::Blue);
            text.setString("P1 Plays");
            text.setPosition({ 1800.f,10.f });
        }
        else {
            text.setFillColor(sf::Color::Red);
            text.setString("P2 Plays");
            text.setPosition({ 10.f,1010.f });
        }
        //draw stuff
        window.draw(rectangle_p1);
        window.draw(rectangle_p2);
        window.draw(text);
        set_the_table_of_cards(window, player1, player2);
        table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
        table.setOrigin({ 32,32 });
        table.setScale({ 2.f,2.f });
        window.draw(table);
        //
        //display everything
        window.display();
        //
    }
}
