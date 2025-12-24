#include"Header.h"
//handle choice,optimize main
int main() {
    //only one window
    std::size_t choice{ 0 };
    sf::VideoMode video{ sf::VideoMode::getDesktopMode() };
    sf::RenderWindow window(video,
        "SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);
    menu(window, choice);
    std::cout << choice << '\n';
    //if something closes the window we get out 
    if (!window.isOpen())return 0;
    //
    sf::Texture _backround{};
    if (!_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\green-casino-poker-table-texture-game-background-free-vector.jpg")) {
        std::exit(1);
    }
    sf::Sprite  backround{ _backround };
    backround.setScale({ 1.f,(float)window.getSize().y / _backround.getSize().y });
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
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    //
    sf::Texture _pause{};
    if (!_pause.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\png-icons\\pause_icon.png")) {
        std::exit(1);
    }
    sf::Sprite pause{ _pause };
    pause.setPosition({ 1850.f,0.f });
    //
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
                sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
                if (pause.getGlobalBounds().contains(world_pos)) {
                    //if you tap pause button something new happens
                    //we have to open new window
                    pause_menu(window);
                    if (!window.isOpen())return 0;
                }
                else {
                    mouseclicked = true;
                }
            }
        }
        //event happens check it
        if (mouseclicked) {
            mouseclicked = false;
            if (flag == true) {
                player_plays(player1, flag, player2, deck, color, num, window, colors, table, aces);
            }
            else {
                player_plays(player2, flag, player1, deck, color, num, window, colors, table, aces);
            }
            //check if a player won
            if (player1.size() == 0) {
                winner(window,true);
                return 0;
            }
            else if (player2.size() == 0) {
                winner(window,false);
                return 0;
            }
            //
        }
        //draw because either can play and we have no cards
        if (!can_he_play(player1, color, num) && !can_he_play(player2, color, num)
            && deck.size() == 0) {
            draw(window);
            return 0;
        }
        window.clear(sf::Color::Black);
        window.draw(backround);
        if (flag == true) {
            text.setFillColor(sf::Color::Blue);
            text.setString("<= P1 Plays");
            text.setPosition({ 1750.f,80.f });
        }
        else {
            text.setFillColor(sf::Color::Red);
            text.setString("P2 Plays =>");
            text.setPosition({ 10.f,1000.f });
        }
        //draw stuff
        window.draw(text);
        set_the_table_of_cards(window, player1, player2);
        table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
        table.setOrigin({ 32,32 });
        table.setScale({ 2.f,2.f });
        window.draw(table);
        window.draw(pause);
        //
        //display everything
        window.display();
        //
    }
}
