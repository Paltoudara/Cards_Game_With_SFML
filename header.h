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

//--------------------
//	INTERFACE BEGIN
//--------------------

//
inline void load_file_paths(
	std::vector<std::string>& file_paths);
//
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::vector<std::string>& file_paths
	, std::unordered_map<std::string, sf::Sprite>& aces);
//
inline void shuffle_deck(
	std::vector<std::pair<std::string, sf::Sprite>>& deck);

//
inline void initialize(std::vector <std::pair
	<std::string, sf::Sprite>>&
	deck, std::string& color, std::string& num, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces,
	std::vector<std::string>& colors);
//
inline void give_players_cards(std::unordered_map<std::string, sf::Sprite>& player1
	, std::unordered_map<std::string, sf::Sprite>& player2
	, std::vector<std::pair<std::string, sf::Sprite>>& deck);
//
inline bool can_he_play(const std::unordered_map<std::string
	, sf::Sprite>& player, const std::string& color,
	const std::string& num);
//
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2);
//
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces
	, std::vector<std::string>& colors);
//
inline void winner(const bool flag_winner);
//
inline void draw();
//
inline void menu();
//
inline void tutorial(sf::RenderWindow &window);
//
inline void settings();
//
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces);
//

//--------------------
//	INTERFACE END
//--------------------



//--------------------
//	IMPLEMENTATION BEGIN
//--------------------

//
//
inline void load_file_paths(std::vector<std::string>& file_paths) {
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_0" + std::to_string(i) + ".png");
	}
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_10.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_A.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_J.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_K.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_Q.png");
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_0" + std::to_string(i) + ".png");
	}
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_10.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_A.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_J.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_K.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_Q.png");
	//
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_0" + std::to_string(i) + ".png");
	}
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_10.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_A.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_J.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_K.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_Q.png");
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_0" + std::to_string(i) + ".png");
	}
	//C:\Users\panag\Source\Repos\Project_kati\playing-cards-pack.zip\PNG\Cards (large)
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_10.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_A.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_J.png");
	file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_K.png");
	file_paths.emplace_back("C:\\Users\\panag\\source\\repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_Q.png");
	//
}
//
//
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::vector<std::string>& file_paths
	, std::unordered_map<std::string, sf::Sprite>& aces) {
	textures.resize(file_paths.size());

	for (std::size_t i = 0; i < file_paths.size(); i++) {

		if (!textures[i].loadFromFile(file_paths[i])) {
			std::exit(1);
		}
		std::string name = { file_paths[i].substr(81) };
		name = std::string{ name.begin(),name.begin() + name.find('.') };
		sf::Sprite sprite{ textures[i] }; // sprite uses stable texture reference
		if (name.contains('A')) {
			aces.emplace(name.substr(name.find_first_of('_') + 1,
				name.find_last_of('_') - 2), sprite);
		}
		deck.emplace_back(std::move(name), sprite);
	}
}
//
//
inline void shuffle_deck(std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//
//
inline void initialize(std::vector <std::
	pair
	<std::string, sf::Sprite>>&
	deck, std::string& color, std::string& num, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces,
	std::vector<std::string>& colors) {
	if (deck.back().first.contains('A')) {
		num = "A";
		color = colors[rand() % 4];
		table = aces.at(color);
	}
	else {
		if (deck.back().first.contains("clubs")) {
			color = "clubs";
			num = deck.back().first.substr(
				deck.back().first.find_last_of('_') + 1);
		}
		else if (deck.back().first.contains("diamonds")) {
			color = "diamonds";
			num = deck.back().first.substr(
				deck.back().first.find_last_of('_') + 1);
		}
		else if (deck.back().first.contains("hearts")) {
			color = "hearts";
			num = deck.back().first.substr(
				deck.back().first.find_last_of('_') + 1);
		}
		else {
			color = "spades";
			num = deck.back().first.substr(
				deck.back().first.find_last_of('_') + 1);
		}
		table = deck.back().second;
	}
	deck.pop_back();
}
//
//
inline void give_players_cards(std::unordered_map<std::string, sf::Sprite>& player1
	, std::unordered_map<std::string, sf::Sprite>& player2
	, std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	for (std::size_t i = 0; i < 7; i++) {
		player1.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
	}
}
//
//
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
//
//
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2) {
	std::size_t i{ 0 };
	float j{ 0 };
	for (auto& [key, value] : player1) {
		value.setPosition({ 0.0f + i * 100.0f, j });
		value.setScale({ 2.f,2.f });
		i++;
		if (i % 7 == 0) {
			j += 125.0f;
			i = 0;
		}
		window.draw(value);
	}
	i = 0;
	j = 0;
	for (auto& [key, value] : player2) {
		value.setPosition({ 1200.f + i * 100.f, 960.f - j });
		value.setScale({ 2.f,2.f });
		i++;
		if (i % 7 == 0) {
			j += 125.0f;
			i = 0;
		}
		window.draw(value);
	}
}
//
//
bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces
	, std::vector<std::string>& colors) {
	sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
	sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
	std::string card_to_remove{};
	for (const auto& [key, value] : player) {
		if (value.getGlobalBounds().contains(world_pos)) {
			if (key.contains(color) || key.contains(num) ||
				key.contains("A")) {
				card_to_remove = key;
				std::cout << color << " " << num << '\n';
				std::cout << key << '\n';
				if (key.contains("A")) {
					color = colors[rand() % 4];
					num = "A";
					//for pc
					//table = aces.at(color + "_A");
					//for laptop
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
	if (!card_to_remove.empty()) {
		player.extract(card_to_remove);
		return true;
	}
	return false;
}
//

void winner(const bool flag_winner) {
	sf::VideoMode video = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window{ video,"sfml",sf::State::Fullscreen };
	window.setFramerateLimit(60);
	sf::Texture texture{};
	
	if (flag_winner == true) {
		if (!texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\player1.png")) {
			std::exit(1);
		}
	}
	else {
		if (!texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\player2.png")) {
			std::exit(1);
		}
	}
	sf::Vector2u texSize = texture.getSize();   // texture original size
	sf::Vector2u winSize = window.getSize();    // window size

	sf::Sprite sprite(texture);
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}

}

void draw() {
	sf::VideoMode video = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window{ video,"sfml",sf::State::Fullscreen };
	window.setFramerateLimit(60);
	sf::Texture texture{};
	if (!texture.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\draw_texture_transparent.png")) {
		std::exit(1);
	}
	sf::Vector2u texSize = texture.getSize();   // texture original size
	sf::Vector2u winSize = window.getSize();    // window size

	sf::Sprite sprite(texture);
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}

void menu() {
	sf::Texture texture1{};
	sf::Texture texture2{};
	sf::Texture texture3{};
	sf::Texture texture4{};
	sf::Texture texture5{};
	sf::Texture texture6{};
	sf::Font font{};
	if (!texture1.
		loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutBlue.png")) {
		std::exit(1);
	}
	if (!texture2.
		loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutFlameRed.png"))
	{
		std::exit(1);
	}
	if (!texture3.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutIce.png")) {
		std::exit(1);
	}
	if (!texture4.
		loadFromFile(R"(C:\Users\panag\Source\Repos\Project_kati\github-mark-c791e9551fe4\github-mark\github-mark-white.png)")) {
		std::exit(1);
	}
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::exit(1);
	}
	if (!texture5
		.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\dealer beauty.jpg")) {
		std::exit(1);
	}
	if (!texture6
		.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\cog_silver.png")) {
		std::exit(1);
	}
	sf::VideoMode video = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window{video,"sfml",sf::State::Fullscreen};
	window.setFramerateLimit(60);
	sf::Sprite sprite1{ texture1 };//start
	sprite1.setScale({1/4.f,1/4.f});
	sprite1.setPosition({ 960.f,540.f });
	sprite1.setOrigin({ sprite1.getLocalBounds().size.x/2.f,sprite1.getLocalBounds().size.y/2.f});
	//
	sf::Sprite sprite2{ texture2 };//tutorial
	sprite2.setScale({ 1 / 4.f,1 / 4.f });
	sprite2.setPosition({ 960.f,650.f });
	sprite2.setOrigin({ sprite1.getLocalBounds().size.x / 2.f,sprite1.getLocalBounds().size.y / 2.f });
	//
	sf::Sprite sprite3{ texture3 };//exit
	sprite3.setScale({ 1 / 4.f,1 / 4.f });
	sprite3.setPosition({ 960.f,760.f });
	sprite3.setOrigin({ sprite1.getLocalBounds().size.x / 2.f,sprite1.getLocalBounds().size.y / 2.f });
	sf::Sprite sprite4{ texture4 };//github
	sprite4.setPosition({ 1800.f,0.f});
	sprite4.setScale({1/2.f,1/2.f});
	sf::Sprite sprite5{texture5};
	sf::Sprite sprite6{ texture6 };//settings
	//texts
	sf::Text text1{ font,"start",50 };
	text1.setPosition({960.f,530.f});
	text1.setFillColor(sf::Color::White);
	text1.setOrigin({ text1.getLocalBounds().size.x / 2.f,text1.getLocalBounds().size.y / 2.f });
	sf::Text text2{font,"tutorial",50};
	text2.setPosition({ 960.f,640.f });
	text2.setFillColor(sf::Color::Black);
	text2.setOrigin({ text2.getLocalBounds().size.x / 2.f,text2.getLocalBounds().size.y / 2.f });
	sf::Text text3{font,"exit",50};
	text3.setPosition({ 960.f,750.f });
	text3.setFillColor(sf::Color::White);
	text3.setOrigin({ text3.getLocalBounds().size.x / 2.f,text3.getLocalBounds().size.y / 2.f });
	//
	sf::RectangleShape rectangle_p1{};
	sf::RectangleShape rectangle_p2{};
	rectangle_p1.setSize({ window.getSize().x / 2.f,window.getSize().y / 2.f });
	rectangle_p1.setFillColor(sf::Color::Blue);
	rectangle_p2.setSize({ (float)window.getSize().x,(float)window.getSize().y });
	rectangle_p2.setFillColor(sf::Color::Red);
	rectangle_p2.setPosition({ window.getSize().x / 2.f,window.getSize().y / 2.f });
	//

	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is < sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				if (sprite1.getGlobalBounds().contains(world_pos)) {
					window.close();
				}
				else if (sprite2.getGlobalBounds().contains(world_pos)) {
					tutorial(window);
				}
				else if (sprite3.getGlobalBounds().contains(world_pos)) {
					window.close();
					std::exit(0);
				}
				else if (sprite4.getGlobalBounds().contains(world_pos)) {
					system("start https://github.com/Paltoudara?tab=repositories");
				}
				else if (sprite6.getGlobalBounds().contains(world_pos)) {
					settings();
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
				std::exit(0);
			}
		}
		window.clear();
		window.draw(sprite5);
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		window.draw(sprite4);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(sprite6);
		window.display();
	}
}
//
inline void tutorial(sf::RenderWindow& window) {
	sf::Font font{};
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {
		std::exit(1);
	}
	//
	sf::Text text1{ font,"RULES OF THE GAME:",100 };
	text1.setPosition({ 920.f,20.f });
	text1.setFillColor(sf::Color::Green);
	text1.setOrigin({ text1.getLocalBounds().size.x / 2.f,text1.getLocalBounds().size.y / 2.f });
	//
	sf::String message =
		L"We have a deck of 52 cards and two "
		L"players. The cards contain symbols. The symbols\n"
		L"are 4: ♠Spades, ♥Hearts, ♦Diamonds, ♣Clubs. "
		L"Every symbol contains Number cards: 2\n-10. "
		L"Face cards: Jack(J), Queen(Q), King(K) and Ace(A).Every player draw's 7 random ca\nrds and there is"
		L" a card in the table,you can drop cards from your hand at the table on\nly if the symbol of your card or the number"
		L" matches the symbol or the number of the\ncard respectively at the table.Winner is the player that will have 0 cards left."
		L"If it is your\nturn and you can't play you have to draw a card and see if you can play it.If you can't\n"
		L"then the other player plays.Warning if you can't play and the deck has no cards then\nthe other player plays and "
		L"if no player can play a card and the deck is empty then dra\nw (Player 1 always starts first)"
		L".Special cards: the numbers 7,8,9 and A are special if yo\nu drop 7 then the other player has"
		L" to draw two cards(or less if the deck doesn't have t\nwo at the time).If you drop 8 then you can play again and the same goes for 9."
		L"If you d\nrop an ace then a random card between the four aces will appear in the table.Note th\nat"
		L" the special cards have no effect if they are at the table at the start of the game(als\no whatever"
		L" card is in the table you can drop an ace no matter what.TAP ANYWHERE";
	sf::Text text2{font,message,50};
	text2.setFillColor(sf::Color::Green);
	text2.setPosition({ 20.f,90.f });
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				return;
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
				std::exit(0);
			}
			
		}
		window.clear();
		window.draw(text1);
		window.draw(text2);
		window.display();
	}


}
//
inline void settings() {

}

inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player,bool &flag
,std::unordered_map<std::string,sf::Sprite>&other_player,std::vector<std::pair<std::string,sf::Sprite>>&deck
,std::string &color,std::string& num,sf::RenderWindow&window,std::vector<std::string>&colors,sf::Sprite&table
, std::unordered_map<std::string, sf::Sprite>&aces) {
	if (!can_he_play(player, color, num)) {
		if (deck.size() > 0) {
			player.emplace(deck.back());
			deck.pop_back();
			if (!can_he_play(player, color, num)) {
				//flag=true 
				flag =!flag;
			}
		}
		else {
			flag =!flag;
		}
	}
	else if (check_for_card(window, player, color,
		num, table, aces, colors)) {
		//special cards
		if (num == "07") {//special card
			flag = !flag;
			if (deck.size() >= 2) {
				other_player.emplace(deck.back());
				deck.pop_back();
				other_player.emplace(deck.back());
				deck.pop_back();
			}
			else {
				while (deck.size() != 0) {
					other_player.emplace(deck.back());
					deck.pop_back();
				}
			}

		}
		else if(num!="08" && num!="09") {
			flag = !flag;
		}
	}
}


//--------------------
//	IMPLEMENTATION END
//--------------------

