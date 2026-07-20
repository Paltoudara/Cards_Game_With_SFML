#include"Menu.h"
#include"Main_Game.h"
#include"Ending_Screens.h"
#include"Pause_Menu.h"

int main() {
    //choice of the texture of the cards
    std::size_t choice{ 0 };
    //create a window with the  dimensions of the monitor  and make it fullscreen,use getDesktopMode() to get monitor resolution
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"SFML works!", sf::State::Fullscreen);
    window.setFramerateLimit(60);//set to only 60 frames,in order not to have unlimited fps
    //textures,font
    sf::Texture _backround{}, _pause{},_hide{};//texture for backround icon,pause button and back of the card icon
    //that hides the cards of player when the other player is playing 
    sf::Font font{};
    sf::Text text{ font }, deck_text{ font,"deck contains:" }, count_text{ font };
    //create a vector of file paths in order to load the textures from those file paths
    //create a vector of the 4 symbols of the cards
    std::vector<std::string>file_paths{}, colors{ "spades","hearts","clubs","diamonds" };
    // must stay alive!.Note that an sf::sprite is an icon widthxheight that you can draw it on screen and make changes to it,the sf::texture is the place in the memory where the texture is stored
    //so a texture is stored in the memory,and a sprite is the actual icon that you can draw on screen.In the end a sprite is really a pointer to a texture.
    std::vector<sf::Texture> textures{};
    std::vector<std::pair<std::string, sf::Sprite>> deck{};
    //this map contains the four aces,key:symbol like hearts diamonds etc,value:the sprite for that ace
    //player1 and player2 hashmaps that contain strings mapped to sprites
    std::unordered_map<std::string, sf::Sprite>player1{}, player2{}, aces{};
    std::string num{}, color{};
    //
    menu(window, choice);//menu function
    //if something closes the window we get out of the main function 
    if (!window.isOpen())return 0;//the window was closed from the menu function show the game ends
    //backround icon are for the main game
    if (!_backround.loadFromFile("assets\\backround\\green-casino-poker-table-texture-game-background-free-vector.jpg")
        || !_pause.loadFromFile("assets\\png-icons\\pause_icon.png")|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        //font texture=>simple font for text,pause texture for pause button on the pause menu
        std::exit(1);
    }
    //
    if (choice == 0&& !_hide.loadFromFile("assets\\playing-cards-pack - Copy\\PNG1\\card_back.png")) {//based on choice different hide texture for cards(that choice we got it from the menu function)
        std::exit(1);
    }
    else if(choice==1&& !_hide.loadFromFile("assets\\playing-cards-pack - Copy\\PNG2\\CardBackFaceBlueLargePattern.png")) {
        std::exit(1);
    }

    load_file_paths(file_paths, choice);//based on choice load the proper textures of the cards
    // load textures from files
    load_textures_from_files(textures, deck, file_paths, choice);
    //intialise the aces map,the map contains the strings:clubs,hearts,diamonds,spades mapped to sprites of aces.
    //the 4 last slots on the deck are the aces before the shuffle.//deck[48]->clubs,deck[49]->diamonds,deck[50]->hearts,
    //deck[51]->spades
    aces.emplace("clubs", deck[48].second);aces.emplace("diamonds", deck[49].second);
    aces.emplace("hearts", deck[50].second);aces.emplace("spades", deck[51].second);
    //shuffle the deck
    std::shuffle(deck.begin(), deck.end(), std::mt19937{ std::random_device{}() });
    //
    sf::Sprite pause{ _pause }, backround{ _backround }, table{ deck.back().second }, hide{_hide};
    //initialize the start of the game and give its player seven cards
    initialize_start_of_the_game(deck, color, num, table,player1,player2);
    //initialize flags,flag==true for player1 to play and false for player2 to play,when we tap with the mouse we change the flag 
    //to true from false
    bool flag{ true }, mouseclicked{false};
    
    pause.setPosition({ 1850.f,0.f });//pause button
    backround.setScale({ 1.f,(float)window.getSize().y / _backround.getSize().y });//backround
    //
    deck_text.setFillColor(sf::Color::Red);deck_text.setPosition({ 10.f,900.f });
    //
    count_text.setFillColor(sf::Color::Red);count_text.setPosition({ 10.f,930.f });
    //sound effect when someone drops a card at the table
    sf::Music music{};
    if (!music.openFromFile("assets\\music\\319896__theriavirra__drumsticks-lutner-2bn-hickory-no1.wav")) {//load the sound effect
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
        if (mouseclicked == true && flag == true) {//p1 plays
            player_plays(player1, flag, player2, deck, color, num, window, colors, table, aces, music);
        }
        else if (mouseclicked == true && flag == false) {//p2 plays
            player_plays(player2, flag, player1, deck, color, num, window, colors, table, aces, music);
        }
        if (mouseclicked == true && player1.size() == 0) {//player1 wins because he emptied his deck
            winner(window, true);
            return 0;
        }
        else if (mouseclicked == true && player2.size() == 0) {//player2 wins because he emptied his deck
            winner(window, false);
        }
        mouseclicked = false;
        //draw because either can play a card and the deck has no cards
        if (!can_he_play(player1, color, num) && !can_he_play(player2, color, num) && deck.size() == 0) {
            draw(window);
            return 0;
        }
        window.clear(sf::Color::Black);window.draw(backround);
        if (flag == true) {//based on the flag we draw the text,in order to show who's turn is to play
            text.setFillColor(sf::Color::Blue);text.setString("<= P1 Plays");text.setPosition({ 1750.f,80.f });
        }
        else {
            text.setFillColor(sf::Color::Red);text.setString("P2 Plays =>");text.setPosition({ 10.f,1000.f });
        }
        //draw stuff
        window.draw(text);
        draw_the_cards_of_the_players(window, player1, player2, choice, flag, hide);
        //set attributes for the table based on the choice==0 and choice==1
        table.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
        if (choice == 0) {
            table.setOrigin({ 32,32 });table.setScale({ 2.f,2.f });
        }
        else {
            table.setOrigin({ table.getLocalBounds().size.x / 2.f,table.getLocalBounds().size.y / 2.f });
            table.setScale({ 80.f / table.getLocalBounds().size.x,128.f / table.getLocalBounds().size.y });
        }
        //table card icon,pause button icon
        window.draw(table);window.draw(pause);
        //display text about how many cards the deck contains.
        window.draw(deck_text);count_text.setString(std::to_string(deck.size()) + " cards");window.draw(count_text);
        window.display();//display everything
    }
}




