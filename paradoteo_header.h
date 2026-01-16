#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<cstdlib>
#include<random>
#include<optional>
#include<utility>
#include<SFML/Audio.hpp>
#include <SFML/System.hpp>
#include<random>
#include<fstream>
//maybe add score
//-------INTERFACE BEGIN-------

//change_textures->this funtion is used in order for the user to choose which card sleeves he wants to see in the game
inline std::size_t change_textures(sf::RenderWindow& window);
//load_file_paths->this function simply creates a vector that contains the file paths to the cards 
//the choice came from the user,from the function change_textures (for every choice we load different file paths)
inline void load_file_paths(std::vector<std::string>& file_paths, const std::size_t choice);
//tutorial_of_the_game->this function simply gives a simple explanation about the rules of the game to the user
inline void tutorial_of_the_game(sf::RenderWindow& window);
//load_textures_from_files->this function creates the deck of the 52 cards,the deck is type vector<name_of_card,sprite>
//sprites are pointers to textures that were loaded so we need a vector of 52 textures to stay alive in all the game
//aces simply contains the 4 symbols of the deck and the sprites for the aces cards
//choice again came from the change_textures function
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	, const std::vector<std::string>& file_paths, const std::size_t choice);
//shuffle_deck->shufflesthe deck vector in order for both players to recieve 7 random cards
inline void shuffle_deck(std::vector<std::pair<std::string, sf::Sprite>>& deck);
//initialiseze->initializes the state of the game,this is the start of the game 
inline void initialize(std::vector <std::
	pair
	<std::string, sf::Sprite>>&
	deck, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces,
	const std::vector<std::string>& colors);
//give_players_cards->gives each player 7 cards
inline void give_players_cards(std::unordered_map<std::string, sf::Sprite>& player1
	, std::unordered_map<std::string, sf::Sprite>& player2
	, std::vector<std::pair<std::string, sf::Sprite>>& deck);
//can_he_play->check if a player can play a card when it is his turn
inline bool can_he_play(const std::unordered_map<std::string
	, sf::Sprite>& player, const std::string& color,
	const std::string& num);
//set_the_table_of_cards->for every frame displays the game that is played beetween the two players
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2, const std::size_t choice, const bool flag, sf::Sprite& hide);
//check_for_card->wait until the player that is his is turn to play a card that is acceptable(matches symbols or numbers
//with the table card)
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces
	, const std::vector<std::string>& colors);
//winner->show the winner,to be a winner you have to empty all your deck at the table
inline void winner(sf::RenderWindow& window, const bool flag_winner);
//draw->in order for a draw to happen the deck must have 0 cards and both players must not be able to play
//a card to the table
inline void draw(sf::RenderWindow& window);
//menu->pretty much the UI of the game 
inline void menu(sf::RenderWindow& window, std::size_t& choice);
//player_plays->pretty much it follows the rules of the game and sees if a player can play or not
//for more see implementation details and read the rules of the game 
//add reset score to the menu
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces, sf::Music& music);
//pause_menu-> is a classic pause that all the games have
//add score to the pause menu!!!
inline void pause_menu(sf::RenderWindow& window);
//document:pretty much displays a text on the window that shows how to make the huffman tree
inline void huffman_tree_explanation(sf::RenderWindow& window);
//document:pretty much it initialises the aces map
//the map contains the symbols:clubs,hearts,diamonds,spades and the sprite of the ace of that symbol
//
inline void initialise_aces(std::unordered_map<std::string, sf::Sprite>& aces, const std::vector<std::pair<std::string, sf::Sprite>>& deck);
//

//-------INTERFACE END-------



//-------IMPLEMENTATION BEGIN-------



//change_textures function
//Note that texture is->brief Image living on the graphics card that can be used for drawing
//Note that sprite is->Drawable representation of a texture, with its
//own transformations, color, etc. pretty much sprite is the pointer to the texture
inline std::size_t change_textures(sf::RenderWindow& window) {
	//textures
	std::size_t choice{ 0 };
	sf::Texture _backround{};
	sf::Texture _classic_cards{};
	sf::Texture _vintage_cards{};
	sf::Font font{};
	//font used for texts on the window
	//load them those are the files paths,if a single texture is not loaded properly exit->1
	if (!_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")
		|| !_classic_cards.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_clubs_03.png")
		|| !_vintage_cards.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_03.png")
		|| !font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {
		std::exit(1);
	}
	//sprites from the textures you loaded
	sf::Sprite classic_cards{ _classic_cards }, vintage_cards{ _vintage_cards }, backround{ _backround };
	//texts
	sf::Text text_title{ font,"  CLICK TO CHOOSE THE TEXTURE THAT YOU WANT:",80 }, text_classic{ font,"CLASSIC:",80 }
	, text_vintage{ font,"VINTAGE:",80 };
	//those are texts and we apply them some properties
	text_title.setFillColor(sf::Color::Black);//color of the text
	text_title.setPosition({ 0.f,20.f });//2d position at the window
	text_title.setOutlineColor(sf::Color::White);//color for the outline layer
	text_title.setOutlineThickness(5.f);//creates the outline layer pretty much,outline must have a thickness in order
	//to appear
	//we do the same for the other texts
	text_classic.setFillColor(sf::Color::Black);
	text_classic.setPosition({ 460.f,320.f });
	text_classic.setOutlineColor(sf::Color::White);
	text_classic.setOutlineThickness(5.f);
	//
	text_vintage.setFillColor(sf::Color::Black);
	text_vintage.setPosition({ 1050.f,320.f });
	text_vintage.setOutlineColor(sf::Color::White);
	text_vintage.setOutlineThickness(5.f);
	//classic-> 640x640
	//vintage -> 450x600
	//every sprite has some widthxheight in pixels
	//the set scale takes two args and both are applied like this 
	//new sprite dimensions are (widthx10)x(heightx10)
	//we can change the sprites dimension to make it appear bigger or smaller
	classic_cards.setScale({ 10.f,10.f });
	classic_cards.setPosition({ 300.f,400.f });//put it on the screen
	vintage_cards.setPosition({ 1000.f,420.f });
	vintage_cards.setScale({ 450.f / vintage_cards.getLocalBounds().size.x,600.f / vintage_cards.getLocalBounds().size.y });
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//window.getSize() gives the dimensions of the window 
	//in this setScale call we wanna make the backround as big as the window in order to do that
	//we make the division with the window x,y cords and the local bounds cords in order to properly scale the backround
	//to be the size of the window
	//Note that localBounds=width and height of the texture originaly the scaling doesn't affect local bounds
	//it only affects globalBounds
	while (window.isOpen()) {//this loop runs for every frame
		while (const auto event = window.pollEvent()) {//we parse here all the events happened to the window
			if (event->is<sf::Event::Closed>()) {//an event that will close our window
				window.close();
				return 0;
			}
			else if (event->is<sf::Event::MouseButtonPressed>()) {//this is not limited to only left right click
				//of the mouse
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };//take where the mouse is at the window
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				/*std::cout << "(" << mous_pos.x << "," << mous_pos.y << ")" << '\n';
				std::cout << "(" <<world_pos.x << "," << world_pos.y << ")" << '\n';*/
				//check collision with classic_cards sprite or vintage_cards sprite
				if (classic_cards.getGlobalBounds().contains(world_pos)) {//this is not exactly perfect collision
					return 0;//sometimes because of the texture the collision may not be perfect 
				}
				else if (vintage_cards.getGlobalBounds().contains(world_pos)) {
					return 1;
				}
			}
		}
		//this is the frame
		window.clear();
		//draw the frame
		window.draw(backround);
		window.draw(classic_cards);
		window.draw(vintage_cards);
		window.draw(text_title);
		window.draw(text_classic);
		window.draw(text_vintage);
		window.display();
		//display the work we done to the frame
	}
	return 0;
}
//load_file_paths function
//Note that the choice->is the choice of the user we got from the menu
inline void load_file_paths(std::vector<std::string>& file_paths, const std::size_t choice) {
	//keep file paths to load the textures later
	file_paths.reserve(52);
	//reserve space for 52 cards
	std::vector<std::string>table{ "02","03","04","05","06","07","08","09","10","J","K","Q","A" };
	//look up table
	//the deck is 52 cards-> 4 suits of 13 cards
	//every suit contains 2,3,4,5,6,7,8,9,10,A,J,K,Q
	if (choice == 0) {//classic_cards
		for (std::size_t i = 0; i < table.size(); i++) {
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_clubs_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_diamonds_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_hearts_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_spades_" + table[i] + ".png");
		}
	}
	else {//vintage_cards
		for (std::size_t i = 0; i < table.size(); i++) {
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\card_diamonds_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\card_hearts_" + table[i] + ".png");
			file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\playing-cards-pack - Copy\\PNG2\\card_spades_" + table[i] + ".png");
		}
	}
}
//simply explains the rules of the game
//Note that the sprites are placed by their top left corner in the position given to them 
//in order to change that and make them placed from the middle in the position given to them 
//we change the origin of them to be (width/2)x(height/2)
//the default origin of a sprite is the top left corner(change that with setOrigin function)
inline void tutorial_of_the_game(sf::RenderWindow& window) {
	//textures,fonts
	sf::Texture _backround{};
	sf::Font font{};
	//load them from those file paths
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//message this message is in utf-8 the L understands far more than simple ascii characters
	sf::String message =
		L"We have a deck of 52 cards and two "
		L"players. The cards contain symbols. The symbols\n"
		L"are 4: ♠Spades, ♥Hearts, ♦Diamonds, ♣Clubs. "
		L"Every symbol contains Number cards: 2-10\n or"
		L" the letters Jack(J), Queen(Q), King(K) and Ace(A).Every player draw's 7 random cards\nand there is"
		L" a card in the table,you can drop cards from your hand at the table only if the\nsymbol of your card or the number or the letter"
		L" matches the symbol or the number or the le\ntter of the card respectively at the table.Winner is the player that will have 0 cards left."
		L"If it is\nyour turn and you can't play you have to draw a card and see if you can play it.If you can't\n"
		L"then the other player plays.Warning if you can't play and the deck has no cards then\nthe other player plays and "
		L"if no player can play a card and the deck is empty then draw\n(Player 1 always starts first)"
		L".Special cards: the numbers 7,8,9 and A are special if you\n drop 7 then the other player has"
		L" to draw two cards(or less if the deck doesn't have two\nat the time).If you drop 8 then you can play again and the same goes for 9."
		L"If you drop\nan ace then a random card between the four aces will appear in the table.Note that\n"
		L" the special cards have no effect if they are at the table at the start of the game(also\nwhatever"
		L" card is in the table you can drop an ace no matter what.";
	//sprite
	sf::Sprite backround{ _backround };
	//texts
	sf::Text text_title{ font,"RULES OF THE GAME:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });
	text_title.setFillColor(sf::Color::Black);//color of the text
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	//make them be placed by the middle
	//the set origin funtion ignores all transformation scaling etc of the sprite 
	text_title.setOutlineColor(sf::Color::White);//give outline to the text
	text_title.setOutlineThickness(5.f);//and give thickness to the outline
	//
	text_rules.setFillColor(sf::Color::Black);
	text_rules.setPosition({ 370.f,120.f });
	text_rules.setOutlineColor(sf::Color::White);
	text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });
	text_tap.setFillColor(sf::Color::Black);
	text_tap.setOutlineColor(sf::Color::White);
	text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//again make the backround to have the same size as the window
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {//capture all events
			if (event->is<sf::Event::MouseButtonPressed>()) {//mouse button pressed
				return;
			}
			else if (event->is<sf::Event::Closed>()) {//event that will close the window like alt-f4
				//exit
				window.close();
				return;
			}

		}
		//this loop runs every frame
		window.clear();
		//draw stuff to the window
		window.draw(backround);
		window.draw(text_title);
		window.draw(text_rules);
		window.draw(text_tap);
		window.display();
	}
}
//load_textures_from_files->simply load the texures from the file paths saved on the vector file_paths
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	, const std::vector<std::string>& file_paths, const std::size_t choice) {
	textures.resize(file_paths.size());
	//textures must contain 52 textures like the 52 cards
	for (std::size_t i = 0; i < file_paths.size(); i++) {

		if (!textures[i].loadFromFile(file_paths[i])) {//if the texture is not loaded exit->1
			std::exit(1);
		}
		//name will have the following format->d_symbol_num.png 
		std::string name{};
		if (choice == 0) {//classic cards
			name = { file_paths[i].substr(96) };
		}
		else {//vintage cards
			name = { file_paths[i].substr(82) };
		}
		name = std::string{ name.begin(),name.begin() + name.find('.') };
		sf::Sprite sprite{ textures[i] }; // sprite uses a stable texture reference
		//by the end of this name->d_symbol_num we do this in order to parse the symbol and num later
		deck.emplace_back(std::move(name), sprite);//every name has a sprite on it
		//we have 52 unique names and cards set on them
	}

}
//shuffle_deck->std::shuffle to shuffle the vector simple
inline void shuffle_deck(std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//initialize function
inline void initialize(std::vector <std::
	pair
	<std::string, sf::Sprite>>&deck
	, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces,
	const std::vector<std::string>& colors) {
	//simply intializes the state of the game
	//remember deck.back.first=name that has the following format->d_symbol_num
	if (deck.back().first.contains('A')) {//if the name contains and ace,pick a random between the four aces
		num = "A";
		color = colors[rand() % 4];//colors={ "spades","hearts","clubs", "diamonds"}
		table = aces.at(color);//aces-><name,sprite> contains the four aces and the sprites to them
	}
	else {
		//name format->d_symbol_num,parse this and take symbol ,num
		color = std::string{ deck.back().first.begin() + deck.back().first.find('_') + 1
			,deck.back().first.begin() + deck.back().first.find_last_of('_')
		};
		num = deck.back().first.substr(
			deck.back().first.find_last_of('_') + 1);
		table = deck.back().second;
	}
	//always initialize table
	deck.pop_back();
}
//give_players_cards->gives its player 7 cards
inline void give_players_cards(std::unordered_map<std::string, sf::Sprite>& player1
	, std::unordered_map<std::string, sf::Sprite>& player2
	, std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	for (std::size_t i = 0; i < 7; i++) {
		player1.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
	}//7 cards its player
}
//can_he_play,check if any card on the players deck can be played
//color and num contain the symbol and num of the table see if the names of the cards 
//,that the player holds contain the color or the num
//name format->d_symbol_num we see if color matches symbol and num matches num
inline bool can_he_play(const std::unordered_map<std::string
	, sf::Sprite>& player, const std::string& color,
	const std::string& num) {
	for (const auto& [key, value] : player) {
		if (key.contains(color) || key.contains(num)
			|| key.contains("A")) {
			return true;
		}
	}
	return false;
}
//set_the_table_of_cards->this function is used in the main loop
//in order to draw the players cards and the table card
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2, const std::size_t choice, const bool flag, sf::Sprite& hide) {
	//hide is the sprite that hides the cards 
	if (choice == 0) {
		std::size_t i{ 0 };
		float j{ 0.f };
		//
		//when player1 plays hide the cards of the player2 
		//when player2 plays hide the cards of the player1
		//flag==true means->player1 plays
		//flag==false means->player2 plays
		auto t1 = player1.begin();
		auto t2 = player2.begin();
		while (t1 != player1.end() || t2 != player2.end()) {
			if (flag == true) {//player1,hide player2
				if (t1 != player1.end()) {//display only for as many cards the player1 has
					t1->second.setPosition({ 0.0f + i * 100.0f, j });
					t1->second.setScale({ 2.f,2.f });
					window.draw(t1->second);
				}
				if (t2 != player2.end()) {//display only for as many cards the player2 has
					hide.setPosition({ 1200.f + i * 100.f, 960.f - j });
					hide.setScale({ 2.f,2.f });
					window.draw(hide);
				}
			}
			else {//player2,hide playe1
				if (t2 != player2.end()) {//display only for as many cards the player2 has
					t2->second.setPosition({ 1200.f + i * 100.f, 960.f - j });
					t2->second.setScale({ 2.f,2.f });
					window.draw(t2->second);
				}
				if (t1 != player1.end()) {//display only for as many cards the player1 has
					hide.setPosition({ 0.0f + i * 100.0f, j });
					hide.setScale({ 2.f,2.f });
					window.draw(hide);
				}
			}
			i++;
			//every seven cards place the next sprite up 125.f pixels
			if (i % 7 == 0) {
				j += 125.0f;
				i = 0;
			}
			if (t1 != player1.end())++t1;
			if (t2 != player2.end())++t2;
		}
	}
	else {
		std::size_t i{ 0 };
		float j{ 0.f };
		//
		//when player1 plays hide the cards of the player2 
		//when player2 plays hide the cards of the player1
		//flag==true means->player1 plays
		//flag==false means->player2 plays
		auto t1 = player1.begin();
		auto t2 = player2.begin();
		while (t1 != player1.end() || t2 != player2.end()) {
			if (flag == true) {//player1,hide player2
				if (t1 != player1.end()) {//display only for as many cards the player1 has
					t1->second.setPosition({ 0.0f + i * 100.0f, j });
					t1->second.setScale({ 80.f / t1->second.getLocalBounds().size.x,128.f / t1->second.getLocalBounds().size.y });
					window.draw(t1->second);
				}
				if (t2 != player2.end()) {//display only for as many cards the player2 has
					hide.setPosition({ 1200.f + i * 100.f, 960.f - j });
					hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
					window.draw(hide);
				}
			}
			else {//player2,hide playe1
				if (t2 != player2.end()) {//display only for as many cards the player2 has
					t2->second.setPosition({ 1200.f + i * 100.f, 960.f - j });
					t2->second.setScale({ 80.f / t2->second.getLocalBounds().size.x,128.f / t2->second.getLocalBounds().size.y });
					window.draw(t2->second);
				}
				if (t1 != player1.end()) {//display only for as many cards the player1 has
					hide.setPosition({ 0.0f + i * 100.0f, j });
					hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
					window.draw(hide);
				}
			}
			i++;
			//every seven cards place the next sprite up 125.f pixels
			if (i % 7 == 0) {
				j += 130.0f;
				i = 0;
			}
			if (t1 != player1.end())++t1;
			if (t2 != player2.end())++t2;
		}

	}
}
//check_for_card->this function simply waits for the player to play an acceptable card in the table
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces
	, const std::vector<std::string>& colors) {
	//get mouse cords and check the map of the player that plays and check if he tapped a card that is valid
	//if thats the case drop it to the table and extract the card that you played from the map
	sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
	sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
	std::string card_to_remove{};
	for (const auto& [key, value] : player) {
		if (value.getGlobalBounds().contains(world_pos)) {//collision
			if (key.contains(color) || key.contains(num) ||
				key.contains("A")) {//acceptable cards
				card_to_remove = key;
				std::cout << color << " " << num << '\n';
				std::cout << key << '\n';
				if (key.contains("A")) {
					color = colors[rand() % 4];
					num = "A";
					table = aces.at(color);
				}
				else {
					auto first = key.find_first_of('_') + 1;
					auto last = key.find_last_of('_');
					color = key.substr(first, last - first);
					num = key.substr(last + 1);
					table = value;
				}
				break;
			}
		}
	}
	//if he played a valid card then the card_to_remove variable will not be empty
	if (!card_to_remove.empty()) {
		player.extract(card_to_remove);
		return true;
	}
	return false;
}
//pretty much the screen of the winner
//every winner has a music
inline void winner(sf::RenderWindow& window, const bool flag_winner) {
	//music
	sf::Music music{};
	//load it 
	if (!music
		.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\music\\Clapping , Cheering & Applause - NO Copyright - Free Sound Effects.mp3")) {
		std::exit(1);
	}
	//read from the score file and do +1 at the score of the player that won
	std::ifstream file("score.txt");
	if (!file) {
		std::cout << "error opening the score file\n";
		std::exit(1);
	}
	std::size_t a{}, b{};
	file >> a >> b;
	file.close();
	//
	music.setVolume(100.f);
	music.play();
	//texture
	sf::Texture texture{};
	//load it
	//based on the flag load the certain texture
	if (flag_winner == true) {
		if (!texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\player1.png")) {
			std::exit(1);
		}
		std::ofstream file("score.txt");
		if (!file.is_open()) {
			std::cout << "error opening the file\n";
			std::exit(1);
		}
		//change the scores and put them back together
		a++;
		file << a <<"\n";
		file << b;
	}
	else {
		if (!texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\player2.png")) {
			std::exit(1);
		}
		std::ofstream file("score.txt");
		if (!file.is_open()) {
			std::cout << "error opening the file\n";
			std::exit(1);
		}
		//change the scores and put them back together
		b++;
		file << a << "\n";
		file << b;
	}
	file.close();
	//
	sf::Vector2u texSize = texture.getSize();   // texture original size
	sf::Vector2u winSize = window.getSize();    // window size
	//sprite
	sf::Sprite sprite(texture);
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	//this works the same if we took also the local bounds from the value sprite
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
//pretty much the screen of the draw
//the draw also has music
inline void draw(sf::RenderWindow& window) {
	//music,texture
	sf::Texture texture{};
	sf::Music music{};
	//load them
	if (!music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\music\\Boo! sound effect.mp3")
		|| !texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\draw_texture_transparent.png")) {
		std::exit(1);
	}
	music.setVolume(100.f);
	music.play();
	//mouse pos on screen
	sf::Vector2u texSize = texture.getSize();   // texture original size
	sf::Vector2u winSize = window.getSize();    // window size
	//sprite
	sf::Sprite sprite{ texture };
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	//this works the same if we took also the local bounds from the value sprite
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
//on progress
inline void menu(sf::RenderWindow& window, std::size_t& choice) {
	//chance for the easter egg 1/1000 chance
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::bernoulli_distribution chance(1.0 / 1000.0);
	bool flag = chance(gen);
	//music,textures,font
	sf::Music music, jumpscare_music{};
	sf::Texture _start{}, _tutorial{}, _exit{}, _github{}, _backround{}, _music_on{}, _music_off{}, _change_texture{}
	, _jumpscare{}, _huffman_button{}, _reset_score{};
	sf::Font font{};
	//load them,buttons backrounds and easter eggs
	if (!music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\music\\White Noiz.mp3")
		|| !_start.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutBlue.png")
		|| !_tutorial.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutFlameRed.png")
		|| !_change_texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutFlameBlue.png")
		|| !_exit.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutIce.png")
		|| !_github.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\github-mark\\github-mark-white.png")
		|| !_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\dealer beauty.jpg")
		|| !_music_on.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\png-icons\\music_on.png")
		|| !_music_off.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\png-icons\\music_off.png")
		|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_jumpscare.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\68747470733a2f2f692e7974696d672e636f6d2f76692f524e6f48635745387462512f6d617872657364656661756c742e6a7067.jpg")
		|| !jumpscare_music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\music\\712416__zombyklr__jumpscare-1.mp3")
		|| !_huffman_button.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutFlameRed.png")
		|| !_reset_score.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutFlameRed.png")
		) {
		std::exit(1);
	}
	sf::Sprite start{ _start }, tutorial{ _tutorial }, exit{ _exit }, github{ _github }, backround{ _backround }
		, music_on{ _music_on }, music_off{ _music_off }, change_texture{ _change_texture }, jumpscare{ _jumpscare }
	, huffman_button{ _huffman_button }, reset_score{_reset_score};
	sf::Clock timer{};//timer because in a certain time we want the jumpscare to appear
	//
	music.setLooping(true);
	music.setVolume(100.f);
	music.play();//play the music in loop while this function runs
	//so it turns forever
	//place the sprites on the windwo
	start.setScale({ 1 / 4.f,1 / 4.f });
	start.setPosition({ 960.f,540.f });
	start.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	tutorial.setScale({ 1 / 4.f,1 / 4.f });
	tutorial.setPosition({ 960.f,650.f });
	tutorial.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	exit.setScale({ 1 / 4.f,1 / 4.f });
	exit.setPosition({ 960.f,760.f });
	exit.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	change_texture.setScale({ 1 / 4.f,1 / 4.f });
	change_texture.setPosition({ 960.f,870.f });
	change_texture.setOrigin({ change_texture.getLocalBounds().size.x / 2.f,change_texture.getLocalBounds().size.y / 2.f });
	//
	huffman_button.setScale({ 1 / 4.f,1 / 4.f });
	huffman_button.setPosition({ 960.f,980.f });
	huffman_button.setOrigin({ huffman_button.getLocalBounds().size.x / 2.f,huffman_button.getLocalBounds().size.y / 2.f });
	//
	reset_score.setScale({ 1 / 3.5f,1 / 3.5f });
	reset_score.setPosition({960.f,440.f});
	reset_score.setOrigin({ reset_score.getLocalBounds().size.x / 2.f,reset_score.getLocalBounds().size.y / 2.f });
	//
	github.setPosition({ 1800.f,0.f });
	github.setScale({ 1 / 2.f,1 / 2.f });
	//
	music_on.setScale({ 64.f / _music_on.getSize().x,80.f / _music_on.getSize().y });
	//
	music_off.setScale({ 64.f / _music_off.getSize().x,80.f / _music_off.getSize().y });
	//
	//texts
	sf::Text text_start{ font,"start",50 }, text_tutorial{ font,"tutorial",50 }, text_exit{ font,"exit",50 }
	, text_change_texture{ font," textures",50 }, text_huffman{ font,"huffman",50 }, text_reset_score{font,"clear score",50};
	//place the texts
	text_start.setPosition({ 960.f,530.f });
	text_start.setFillColor(sf::Color::White);
	text_start.setOrigin({ text_start.getLocalBounds().size.x / 2.f,text_start.getLocalBounds().size.y / 2.f });
	//
	text_tutorial.setPosition({ 960.f,640.f });
	text_tutorial.setFillColor(sf::Color::Black);
	text_tutorial.setOrigin({ text_tutorial.getLocalBounds().size.x / 2.f,text_tutorial.getLocalBounds().size.y / 2.f });
	//
	text_exit.setPosition({ 960.f,750.f });
	text_exit.setFillColor(sf::Color::White);
	text_exit.setOrigin({ text_exit.getLocalBounds().size.x / 2.f,text_exit.getLocalBounds().size.y / 2.f });
	//
	text_change_texture.setPosition({ 960.f,860.f });
	text_change_texture.setFillColor(sf::Color::White);
	text_change_texture.setOrigin({ text_change_texture.getLocalBounds().size.x / 2.f,text_change_texture.getLocalBounds().size.y / 2.f });
	//
	text_huffman.setPosition({ 960.f,440.f });
	text_huffman.setFillColor(sf::Color::White);
	text_huffman.setOrigin({ text_huffman.getLocalBounds().size.x / 2.f,text_huffman.getLocalBounds().size.y / 2.f });
	//
	text_reset_score.setPosition({ 970.f,430.f });
	text_reset_score.setFillColor(sf::Color::White);
	text_reset_score.setOrigin({ text_reset_score.getLocalBounds().size.x / 2.f,text_reset_score.getLocalBounds().size.y / 2.f });
	//
	jumpscare.setScale({ window.getSize().x / jumpscare.getLocalBounds().size.x, window.getSize().y / jumpscare.getLocalBounds().size.y });
	//place the jumpscare when a certain time is passed
	bool event{ false };
	while (window.isOpen()) {
		//reset timer of the jumpscare if the user does something to the menu
		//remember the jumpscare is actived if the user stays on the menu and doesn't do anything 
		//for 360 seconds,if in those seconds he does something then the time resets to 0
		while (const auto event = window.pollEvent()) {
			if (event->is < sf::Event::MouseButtonPressed>()) {
				//take mouse pos
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				//check for collision with global bounds
				if (start.getGlobalBounds().contains(world_pos)) {
					//start
					return;
				}
				//if for some reason the window closes the game ends
				else if (tutorial.getGlobalBounds().contains(world_pos)) {
					tutorial_of_the_game(window);
					timer.restart();
					if (!window.isOpen())return;
				}
				else if (exit.getGlobalBounds().contains(world_pos)) {
					//exit
					window.close();
					return;
				}
				else if (change_texture.getGlobalBounds().contains(world_pos)) {
					choice = change_textures(window);
					timer.restart();
					if (!window.isOpen())return;
				}
				else if (github.getGlobalBounds().contains(world_pos)) {
					//open github
					system("start https://github.com/Paltoudara?tab=repositories");
					timer.restart();
				}
				//music icon to handle
				else if (music_on.getGlobalBounds().contains(world_pos)) {
					//when we tap the music if it off make it play
					//if it is on make it stop playing
					if (music.getStatus() == sf::SoundSource::Status::Playing) {
						music.stop();
					}
					else {
						music.play();
					}
					timer.restart();
				}
				else if (flag && huffman_button.getGlobalBounds().contains(world_pos)) {
					//if we got the 1/1000 show the func and accept clicks
					huffman_tree_explanation(window);
					timer.restart();
					if (!window.isOpen())return;
				}
				else if (reset_score.getGlobalBounds().contains(world_pos)) {
					std::ofstream score_file("score.txt");
					if (!score_file.is_open()) {
						std::cout << "error opening the score file\n";
						std::exit(1);
					}
					score_file << "0\n";
					score_file << "0";
					score_file.close();
					//reset the file that contains the scores of the two players
					//recreate it and put 0's
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				//exit
				window.close();
				return;
			}
		}
		//this is the frame
		window.clear();
		if (!event && timer.getElapsedTime().asSeconds() >= 360.f) {//6x60 d
			//if event happends draw it and the jumpscare
			music.stop();
			event = true;
			window.draw(jumpscare);
			window.display();
			jumpscare_music.setVolume(100.f);
			jumpscare_music.play();
			sf::sleep(sf::seconds(2.0));//sleep for 2 seconds that's how much the jumpscare is 
			//while the program sleeps we stay here and we enjoy the jumpscare and then the music plays and we continue
			music.play();

		}
		else {
			//if event didn't happend draw everything that the menu has
			window.draw(backround);
			window.draw(start);
			window.draw(tutorial);
			window.draw(exit);
			window.draw(github);
			//if music is playing draw icon that it is on 
			if (music.getStatus() == sf::SoundSource::Status::Playing) {
				window.draw(music_on);
			}
			//if not draw the icon that it doesn't plays
			else {
				window.draw(music_off);
			}
			window.draw(change_texture);
			//
			window.draw(text_start);
			window.draw(text_tutorial);
			window.draw(text_exit);
			window.draw(text_change_texture);
			if (flag) {//if we got the 1/1000 show the huffman button
				window.draw(huffman_button);
				window.draw(text_huffman);
			}
			window.draw(reset_score);
			window.draw(text_reset_score);
			window.display();
		}
	}
}
//this is the overall structure of the game
//when a player plays what happends
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces, sf::Music& music) {
	//when a player plays the might have a card to play or not 
	if (!can_he_play(player, color, num)) {
		//if they don't have a card they draw one from the deck
		//if the deck doesn't have cards to give then it is the other players turn 
		//remember flag==true->player1 plays
		//flag==false->player2 plays
		if (deck.size() > 0) {
			player.emplace(deck.back());
			deck.pop_back();
			if (!can_he_play(player, color, num)) {
				flag = !flag;
			}
		}
		else {
			flag = !flag;
		}
	}//if he can play wait untill he plays the right card in order to continue with the game
	else if (check_for_card(window, player, color,
		num, table, aces, colors)) {
		//special cards,if he plays a 7 the other draws 2 cards or less if the deck has less than two 
		music.setVolume(100.f);
		music.play();
		//play the sound effect 
		if (num == "07") {//special card
			flag = !flag;
			for (std::size_t i = 0; i < 2 && !deck.empty(); ++i) {
				other_player.emplace(deck.back());
				deck.pop_back();
			}
		}//8 and 9 the player plays again
		//any other than 8 and 9 then the other player plays
		else if (num != "08" && num != "09") {
			flag = !flag;
		}
	}
}
//this is the pause menu,contains two textures resume and quit game and a backround
//add score remains
//whatever instruction here is shown is explained above on what it does
inline void pause_menu(sf::RenderWindow& window) {
	//textures,font
	sf::Texture _resume{}, _quit_game{}, _backround{}, _score{};
	sf::Font font{};
	//load them
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_resume.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutBlue.png")
		|| !_quit_game.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutIce.png")
		|| !_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")
		|| !_score.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\buttons\\LeftCutFlameRed.png")
		) {
		std::exit(1);
	}
	//just read the scores from the file and display them on the pause menu
	std::ifstream file("score.txt");
	if (!file.is_open()) {
		std::cout << "failed to open the file\n";
		std::exit(1);
	}
	std::size_t score_p1{};
	std::size_t score_p2{};
	file >> score_p1;
	file >> score_p2;
	file.close();
	//sprites
	sf::Sprite resume{ _resume }, quit_game{ _quit_game }, backround{ _backround }, score{ _score };
	//texts
	sf::Text text_resume{ font,"resume",30 }, text_quit_game{ font,"quit_game",30 }, text_score{ font,
		"p1:" + std::to_string(score_p1) + "   ,   p2:" + std::to_string(score_p2),30 };
	//
	resume.setPosition({ 960.f,540.f });
	resume.setOrigin({ resume.getLocalBounds().size.x / 2.f,resume.getLocalBounds().size.y / 2.f });
	resume.setScale({ 1 / 4.f,1 / 4.f });
	//
	quit_game.setPosition({ 960.f,650.f });
	quit_game.setOrigin({ quit_game.getLocalBounds().size.x / 2.f,quit_game.getLocalBounds().size.y / 2.f });
	quit_game.setScale({ 1 / 4.f,1 / 4.f });
	//
	score.setScale({ 1 / 4.f, 1 / 3.0f });
	score.setPosition({ 960.f,440.f });
	score.setOrigin({ score.getLocalBounds().size.x / 2.f,score.getLocalBounds().size.y / 2.f });
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	text_resume.setPosition({ 970.f,530.f });
	text_resume.setOrigin({ text_resume.getLocalBounds().size.x / 2.f,text_resume.getLocalBounds().size.y / 2.f });
	//
	text_quit_game.setPosition({ 970.f,640.f });
	text_quit_game.setOrigin({ text_quit_game.getLocalBounds().size.x / 2.f,text_quit_game.getLocalBounds().size.y / 2.f });
	//
	text_score.setPosition({970.f,430.f});
	text_score.setOrigin({ text_score.getLocalBounds().size.x / 2.f,text_score.getLocalBounds().size.y / 2.f });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
			sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
			if (event->is<sf::Event::MouseButtonPressed>()) {
				if (resume.getGlobalBounds().contains(world_pos)) {
					return;
				}
				else  if (quit_game.getGlobalBounds().contains(world_pos)) {
					window.close();
					return;
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();
		window.draw(backround);
		window.draw(resume);
		window.draw(quit_game);
		window.draw(text_resume);
		window.draw(text_quit_game);
		window.draw(score);
		window.draw(text_score);
		window.display();
	}
}
//
inline void huffman_tree_explanation(sf::RenderWindow& window) {
	//textures,fonts
	sf::Texture _backround{};
	sf::Font font{};
	//load them from those file paths
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//message this message is in utf-8 the L understands far more than simple ascii characters
	sf::String message =
		L"To make the huffman tree is simple:"
		L"First you take all possibilities and sort them by increasing order(if two possibilities\n)"
		L"have the same chance the order doesn't matter the real algo uses a priority queue"
		L" take the two smallest possibilities\nand merge them(take the sum of their possibilities).Take the new possibility and then"
		L" put it with the others and re-sort\nand then do the same.Stop when there is only one tree.I read sedgewick book,the figure he shows,puts the merged\npossibilities wherever he wants in the sorted order"
		L". I also asked chat gpt and gemini pro.They said the same."
		L"In the e\nnd sort,take the two mins and then re-sort and then continue until there is only one tree left."
		;
	//sprite
	sf::Sprite backround{ _backround };
	//texts
	sf::Text text_title{ font,"HUFFMAN TREE EXPLANATION:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });
	text_title.setFillColor(sf::Color::Black);//color of the text
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	//make them be placed by the middle
	//the set origin funtion ignores all transformation scaling etc of the sprite 
	text_title.setOutlineColor(sf::Color::White);//give outline to the text
	text_title.setOutlineThickness(5.f);//and give thickness to the outline
	//apply properties to texts
	text_rules.setFillColor(sf::Color::Black);
	text_rules.setPosition({ 250.f,120.f });
	text_rules.setOutlineColor(sf::Color::White);
	text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });
	text_tap.setFillColor(sf::Color::Black);
	text_tap.setOutlineColor(sf::Color::White);
	text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//again make the backround to have the same size as the window
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {//capture all events
			if (event->is<sf::Event::MouseButtonPressed>()) {//mouse button pressed
				return;
			}
			else if (event->is<sf::Event::Closed>()) {//event that will close the window like alt-f4
				//exit
				window.close();
				return;
			}

		}
		//this loop runs every frame
		window.clear();
		//draw stuff to the window
		window.draw(backround);
		window.draw(text_title);
		window.draw(text_rules);
		window.draw(text_tap);
		window.display();
	}
}
//
inline void initialise_aces(std::unordered_map<std::string, sf::Sprite>& aces, const std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	//the for last slots are the aces
	//deck[48]->clubs
	//deck[49]->diamonds
	//deck[50]->hearts
	//deck[51]->spades
	aces.emplace("clubs", deck[48].second);
	aces.emplace("diamonds", deck[49].second);
	aces.emplace("hearts", deck[50].second);
	aces.emplace("spades", deck[51].second);
}
//

//-------IMPLEMENTATION END-------
