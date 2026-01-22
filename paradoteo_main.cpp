#include"Header.h"
//handle choice
int main() {
    ////only one window
    std::size_t choice{ 0 };//choice of the texture of the cards
    sf::VideoMode video{ sf::VideoMode::getDesktopMode() };//take the dimensions of the monitor 
    sf::RenderWindow window(video,
        "SFML works!", sf::State::Fullscreen);//create a window with the  dimensions of the monitor  and make it fullscreen
    //textures,font
    sf::Texture _backround{}, _pause{};//texture for backround and pause
    sf::Font font{};
    sf::Text text{ font }, deck_text{ font,"deck contains:" }
    , count_text{ font };
    //structure of the game
    std::vector<std::string>file_paths{};//create a vector of file paths in order to load the textures from those file paths
    std::vector<sf::Texture> textures;  // must stay alive!.Note that an sf::sprite is an icon widthxheight that you can draw it on screen and make changes to it,the sf::texture is the place in the memory where the texture is stored
    //so a texture is stored in the memory,and a sprite is the actual icon that you can draw on screen.In the end a sprite is really a pointer to a texture.
    std::unordered_map<std::string, sf::Sprite>aces{};//this map contains the four aces,key:symbol like hearts diamonds etc,value:the sprite for that ace
    std::vector<std::pair<std::string, sf::Sprite>> deck{};
    std::unordered_map<std::string, sf::Sprite>player1{};
    std::unordered_map<std::string, sf::Sprite>player2{};
    std::string num{};
    std::vector<std::string>colors{ "spades","hearts",
    "clubs","diamonds" };//vector of symbols
    std::string color{};
    window.setFramerateLimit(60);//set to only 60 frames,in order not to have unlimited fps
    menu(window, choice);//menu function
    //if something closes the window we get out 
    if (!window.isOpen())return 0;//the window was closed from the menu function show the game ends
    //
    if (!_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\green-casino-poker-table-texture-game-background-free-vector.jpg")//those icons are for the main game
        || !_pause.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\png-icons\\pause_icon.png")//this icon is for the pause menu
        || !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::exit(1);
    }
    sf::Texture _hide{};//this is the texture that hides the cards of player when the other player is playing 
    if (choice == 0) {//based on choice different hide texture for cards(that choice we got it from the menu function)
        if (!_hide.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_back.png")) {
            std::exit(1);
        }
    }
    else {
        if (!_hide.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\CardBackFaceBlueLargePattern.png")) {
            std::exit(1);
        }
    }
    sf::Sprite hide{ _hide };//sprite
    load_file_paths(file_paths, choice);//based on choice load the proper textures of the cards
    // load textures from files
    load_textures_from_files(textures, deck, file_paths, choice);
    initialise_aces(aces, deck);
    //shuffle the deck
    shuffle_deck(deck);//shuffle deck
    //
    sf::Sprite pause{ _pause }, backround{ _backround }, table{ deck.back().second };

    //initialize the game
    initialize(deck, color, num, table, aces, colors);//initialize the game state
    //give each player 7 cards
    give_players_cards(player1, player2, deck);//give each player 7 cards
    //initialize flags
    bool flag{ true };//who plays true for player1,false for player2
    bool mouseclicked{ false };//when we tap with the mouse the logic of the game is activated
    //
    //
    pause.setPosition({ 1850.f,0.f });//pause button
    backround.setScale({ 1.f,(float)window.getSize().y / _backround.getSize().y });//backround
    //
    deck_text.setFillColor(sf::Color::Red);
    deck_text.setPosition({ 10.f,900.f });
    //
    count_text.setFillColor(sf::Color::Red);
    count_text.setPosition({ 10.f,930.f });
    //sound effect when someone drops a card at the table
    sf::Music music{};
    if (!music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\music\\319896__theriavirra__drumsticks-lutner-2bn-hickory-no1.wav")) {//load the sound effect
        std::exit(1);
    }
    //
    std::srand(static_cast<unsigned int>(std::time(NULL)));//random
    while (window.isOpen()) {//this loop runs for every frame of the window
        while (const auto event = window.pollEvent()) {//pull all events that happend to the window here
            if (event->is<sf::Event::Closed>()) {//if something happends and closes the window close it and the game ends
                window.close();
                return 0;
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {//if a mouse button is pressed this is not only limited
                //to left right click
                sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
                sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
                if (pause.getGlobalBounds().contains(world_pos)) {//the user tapped the pause menu
                    //if you tap pause button something new happens
                    //we have to open new window
                    pause_menu(window);
                    if (!window.isOpen())return 0;
                }
                else {//the user tapped something else show activate the game logic with this flag
                    mouseclicked = true;
                }
            }
        }
        //mouse button pressed check it 
        if (mouseclicked) {
            mouseclicked = false;
            if (flag == true) {//p1 plays
                player_plays(player1, flag, player2, deck, color, num, window, colors, table, aces, music);
            }
            else {//p2 plays
                player_plays(player2, flag, player1, deck, color, num, window, colors, table, aces, music);
            }
            //a player wins if he emptied his deck
            //check if a player won
            if (player1.size() == 0) {
                winner(window, true);
                return 0;
            }
            else if (player2.size() == 0) {
                winner(window, false);
                return 0;
            }
            //
        }
        //draw because either can play a card and the deck has no cards
        if (!can_he_play(player1, color, num) && !can_he_play(player2, color, num)
            && deck.size() == 0) {
            draw(window);
            return 0;
        }
        window.clear(sf::Color::Black);
        window.draw(backround);
        if (flag == true) {//based on the flag we draw the text,in order to show who plays
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
        set_the_table_of_cards(window, player1, player2, choice, flag, hide);
        if (choice == 0) {//based on the texture that the user choose some things about the table change
            table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
            table.setOrigin({ 32,32 });//the classic card has a size 64x64 so origin is half of width,height in order
            //to position it from the middle
            table.setScale({ 2.f,2.f });
        }
        else {
            table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
            table.setOrigin({ table.getLocalBounds().size.x / 2.f,table.getLocalBounds().size.y / 2.f });
            table.setScale({ 80.f / table.getLocalBounds().size.x,128.f / table.getLocalBounds().size.y });
        }
        window.draw(table);
        window.draw(pause);
        //
        //display everything
        window.draw(deck_text);
        count_text.setString(std::to_string(deck.size()) + " cards");
        window.draw(count_text);
        window.display();
        //
    }
}
