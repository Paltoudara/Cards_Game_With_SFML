#include"Menu.h"
#include"Main_Game.h"
#include"Ending_Screens.h"
#include"Pause_Menu.h"

int main() {
    //
    std::size_t choice{ 0 };
    //
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);//
    //
    sf::Texture _backround{}, _pause{},_hide{};//
    //
    sf::Font font{};
    sf::Text text{ font }, deck_text{ font,"deck contains:" }, count_text{ font };
    //
    std::vector<std::string>file_paths{}, colors{ "spades","hearts","clubs","diamonds" };
    //
    std::vector<sf::Texture> textures{};
    std::vector<std::pair<std::string, sf::Sprite>> deck{};
    //
    std::unordered_map<std::string, sf::Sprite>player1{}, player2{}, aces{};
    std::string num{}, color{};
    //
    menu(window, choice);
    //
    if (!window.isOpen())return 0;
    //
    if (!_backround.loadFromFile("assets\\backround\\green-casino-poker-table-texture-game-background-free-vector.jpg")
        || !_pause.loadFromFile("assets\\png-icons\\pause_icon.png")|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        //
        std::exit(1);
    }
    //
    if (choice == 0&& !_hide.loadFromFile("assets\\playing-cards-pack - Copy\\PNG1\\card_back.png")) {//based on choice different hide texture for cards(that choice we got it from the menu function)
        std::exit(1);
    }
    else if(choice==1&& !_hide.loadFromFile("assets\\playing-cards-pack - Copy\\PNG2\\CardBackFaceBlueLargePattern.png")) {
        std::exit(1);
    }

    load_file_paths(file_paths, choice);//
    //
    load_textures_from_files(textures, deck, file_paths, choice);
    //
    aces.emplace("clubs", deck[48].second);aces.emplace("diamonds", deck[49].second);
    aces.emplace("hearts", deck[50].second);aces.emplace("spades", deck[51].second);
    //
    std::shuffle(deck.begin(), deck.end(), std::mt19937{ std::random_device{}() });
    //
    sf::Sprite pause{ _pause }, backround{ _backround }, table{ deck.back().second }, hide{_hide};
    //
    initialize_start_of_the_game(deck, color, num, table,player1,player2);
    //
    bool flag{ true }, mouseclicked{false};
    
    pause.setPosition({ 1850.f,0.f });
    backround.setScale({ 1.f,(float)window.getSize().y / _backround.getSize().y });
    //
    deck_text.setFillColor(sf::Color::Red);deck_text.setPosition({ 10.f,900.f });
    //
    count_text.setFillColor(sf::Color::Red);count_text.setPosition({ 10.f,930.f });
    //
    sf::Music music{};
    if (!music.openFromFile("assets\\music\\319896__theriavirra__drumsticks-lutner-2bn-hickory-no1.wav")) {//load the sound effect
        std::exit(1);
    }
    //
    std::srand(static_cast<unsigned int>(std::time(NULL)));//
    while (window.isOpen()) {//
        while (const auto event = window.pollEvent()) {//
            if (event->is<sf::Event::Closed>()) {//
                window.close();
                return 0;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {//
                //
                sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
                sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
                if (pause.getGlobalBounds().contains(world_pos)) {//
                    //
                    pause_menu(window);
                    if (!window.isOpen())return 0;
                }
                else {//
                    mouseclicked = true;
                }
            }
        }
        //
        if (mouseclicked == true && flag == true) {//
            player_plays(player1, flag, player2, deck, color, num, window, colors, table, aces, music);
        }
        else if (mouseclicked == true && flag == false) {//
            player_plays(player2, flag, player1, deck, color, num, window, colors, table, aces, music);
        }
        if (mouseclicked == true && player1.size() == 0) {//
            winner(window, true);
            return 0;
        }
        else if (mouseclicked == true && player2.size() == 0) {//
            winner(window, false);
        }
        mouseclicked = false;
        //
        if (!can_he_play(player1, color, num) && !can_he_play(player2, color, num) && deck.size() == 0) {
            draw(window);
            return 0;
        }
        window.clear(sf::Color::Black);window.draw(backround);
        if (flag == true) {//
            text.setFillColor(sf::Color::Blue);text.setString("<= P1 Plays");text.setPosition({ 1750.f,80.f });
        }
        else {
            text.setFillColor(sf::Color::Red);text.setString("P2 Plays =>");text.setPosition({ 10.f,1000.f });
        }
        //
        window.draw(text);
        draw_the_cards_of_the_players(window, player1, player2, choice, flag, hide);
        //
        table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
        if (choice == 0) {
            table.setOrigin({ 32,32 });table.setScale({ 2.f,2.f });
        }
        else {
            table.setOrigin({ table.getLocalBounds().size.x / 2.f,table.getLocalBounds().size.y / 2.f });
            table.setScale({ 80.f / table.getLocalBounds().size.x,128.f / table.getLocalBounds().size.y });
        }
        //
        window.draw(table);window.draw(pause);
        //
        window.draw(deck_text);count_text.setString(std::to_string(deck.size()) + " cards");window.draw(count_text);
        window.display();//
    }
}
