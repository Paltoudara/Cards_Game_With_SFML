//add to the pause menu the score
//add to the menu an option to reset the score
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
//done//
inline std::size_t change_textures(sf::RenderWindow& window) {
	//textures
	std::size_t choice{ 0 };
	sf::Texture _backround{};
	sf::Texture _classic_cards{};
	sf::Texture _vintage_cards{};
	sf::Font font{};
	//font
	//load them
	if (!_backround.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")
		|| !_classic_cards.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_clubs_03.png")
		|| !_vintage_cards.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_03.png")
		|| !font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {
		std::exit(1);
	}
	//sprites
	sf::Sprite classic_cards{ _classic_cards }, vintage_cards{ _vintage_cards }, backround{ _backround };
	//texts
	sf::Text text_title{ font,"  CLICK TO CHOOSE THE TEXTURE THAT YOU WANT:",80 }, text_classic{ font,"CLASSIC:",80 }
	, text_vintage{ font,"VINTAGE:",80 };
	//
	text_title.setFillColor(sf::Color::Black);
	text_title.setPosition({ 0.f,20.f });
	text_title.setOutlineColor(sf::Color::White);
	text_title.setOutlineThickness(5.f);
	//
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
	classic_cards.setScale({ 10.f,10.f });
	classic_cards.setPosition({ 300.f,400.f });
	vintage_cards.setPosition({ 1000.f,420.f });
	vintage_cards.setScale({ 450.f / vintage_cards.getLocalBounds().size.x,600.f / vintage_cards.getLocalBounds().size.y });
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
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
				if (classic_cards.getGlobalBounds().contains(world_pos)) {
					return 0;
				}
				else if (vintage_cards.getGlobalBounds().contains(world_pos)) {
					return 1;
				}
			}
		}
		window.clear();
		window.draw(backround);
		window.draw(classic_cards);
		window.draw(vintage_cards);
		window.draw(text_title);
		window.draw(text_classic);
		window.draw(text_vintage);
		window.display();
	}
	return 0;
}
//done//
inline void load_file_paths(std::vector<std::string>& file_paths, const std::size_t choice) {
	//load 52 carads
	//4 suits of 13 cards
	file_paths.reserve(52);
	std::vector<std::string>table{ "02","03","04","05","06","07","08","09","10","A","J","K","Q" };
	if (choice == 0) {
		for (std::size_t i = 0; i < table.size(); i++) {
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_clubs_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_diamonds_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_hearts_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_spades_"+table[i]+ ".png");
		}
	}
	else {
		for (std::size_t i = 0; i < table.size(); i++) {
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\card_diamonds_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\card_hearts_"+table[i]+".png");
			file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\card_spades_"+table[i]+".png");
		}
	}
}
//done//
inline void tutorial_of_the_game(sf::RenderWindow& window) {
	//textures,fonts
	sf::Texture _backround{};
	sf::Font font{};
	//load them
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//message
	sf::String message =
		L"We have a deck of 52 cards and two "
		L"players. The cards contain symbols. The symbols\n"
		L"are 4: ♠Spades, ♥Hearts, ♦Diamonds, ♣Clubs. "
		L"Every symbol contains Number cards: 2-10.\n"
		L"Face cards: Jack(J), Queen(Q), King(K) and Ace(A).Every player draw's 7 random cards\nand there is"
		L" a card in the table,you can drop cards from your hand at the table only\nif the symbol of your card or the number"
		L" matches the symbol or the number of the\ncard respectively at the table.Winner is the player that will have 0 cards left."
		L"If it is your\nturn and you can't play you have to draw a card and see if you can play it.If you can't\n"
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
	text_title.setFillColor(sf::Color::Black);
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	text_title.setOutlineColor(sf::Color::White);
	text_title.setOutlineThickness(5.f);
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
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				return;
			}
			else if (event->is<sf::Event::Closed>()) {
				//exit
				window.close();
				return;
			}

		}
		window.clear();
		window.draw(backround);
		window.draw(text_title);
		window.draw(text_rules);
		window.draw(text_tap);
		window.display();
	}
}
//done//
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	, const std::vector<std::string>& file_paths
	, std::unordered_map<std::string, sf::Sprite>& aces, const std::size_t choice) {
	textures.resize(file_paths.size());
	if (choice == 0) {
		for (std::size_t i = 0; i < file_paths.size(); i++) {

			if (!textures[i].loadFromFile(file_paths[i])) {
				std::exit(1);
			}
			//format d_symbol_num.png
			std::string name = { file_paths[i].substr(101) };
			name = std::string{ name.begin(),name.begin() + name.find('.') };
			sf::Sprite sprite{ textures[i] }; // sprite uses a stable texture reference
			if (name.contains('A')) {
				//aces will contain just the symbols
				aces.emplace(name.substr(name.find_first_of('_') + 1,
					name.find_last_of('_') - 2), sprite);
			}
			deck.emplace_back(std::move(name), sprite);
		}
	}
	else {
		for (std::size_t i = 0; i < file_paths.size(); i++) {
			if (!textures[i].loadFromFile(file_paths[i])) {
				std::exit(1);
			}
			//format d_symbol_num.png
			std::string name = { file_paths[i].substr(87) };
			name = std::string{ name.begin(),name.begin() + name.find('.') };
			sf::Sprite sprite{ textures[i] }; // sprite uses a stable texture reference
			if (name.contains('A')) {
				aces.emplace(name.substr(name.find_first_of('_') + 1,
					name.find_last_of('_') - 2), sprite);
			}
			deck.emplace_back(std::move(name), sprite);
		}
	}
}
//done//
inline void shuffle_deck(std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//done//
inline void initialize(std::vector <std::
	pair
	<std::string, sf::Sprite>>&
	deck, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces,
	const std::vector<std::string>& colors) {
	if (deck.back().first.contains('A')) {
		num = "A";
		color = colors[rand() % 4];
		table = aces.at(color);
	}
	else {
		color = std::string{ deck.back().first.begin() + deck.back().first.find('_') + 1
			,deck.back().first.begin() + deck.back().first.find_last_of('_')
		};
		num = deck.back().first.substr(
			deck.back().first.find_last_of('_') + 1);
		table = deck.back().second;
	}
	deck.pop_back();
}
//done//
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
//done//
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
//done//,optimize
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2, const std::size_t choice,const bool flag) {
	//
	sf::Texture _hide{};
	if (choice == 0) {
		std::size_t i{ 0 };
		float j{ 0.f };
		//
		if (!_hide.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG1\\Cards (large)\\card_back.png")) {
			std::exit(1);
		}
		sf::Sprite hide{ _hide };
		for (auto& [key, value] : player1) {
			if (flag == true) {
				value.setPosition({ 0.0f + i * 100.0f, j });
				value.setScale({ 2.f,2.f });
				window.draw(value);
			}
			else {
				hide.setPosition({ 0.0f + i * 100.0f, j });
				hide.setScale({ 2.f,2.f });
				window.draw(hide);
			}
			i++;
			if (i % 7 == 0) {
				j += 125.0f;
				i = 0;
			}
			//window.draw(value);
		}
		i = 0;
		j = 0;
		for (auto& [key, value] : player2) {
			if (flag == false) {
				value.setPosition({ 1200.f + i * 100.f, 960.f - j });
				value.setScale({ 2.f,2.f });
				window.draw(value);
			}
			else {
				hide.setPosition({ 1200.f + i * 100.f, 960.f - j });
				hide.setScale({ 2.f,2.f });
				window.draw(hide);
			}
			i++;
			if (i % 7 == 0) {
				j += 125.0f;
				i = 0;
			}
		}
	}
	else {
		std::size_t i{ 0 };
		float j{ 0.f };
		//
		if (!_hide.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\playing-cards-pack - Copy\\PNG2\\CardBackFaceBlueLargePattern.png")) {
			std::exit(1);
		}
		sf::Sprite hide{ _hide };
		for (auto& [key, value] : player1) {
			if (flag == true) {
				value.setPosition({ 0.0f + i * 100.0f, j });
				value.setScale({ 80.f / value.getLocalBounds().size.x,128.f / value.getLocalBounds().size.y });
				window.draw(value);
			}
			else {
				hide.setPosition({ 0.0f + i * 100.0f, j });
				hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
				window.draw(hide);
			}
			i++;
			if (i % 7 == 0) {
				j += 130.0f;
				i = 0;
			}
		}
		i = 0;
		j = 0;
		for (auto& [key, value] : player2) {
			if (flag == false) {
				value.setPosition({ 1200.f + i * 100.f, 960.f - j });
				value.setScale({ 80.f / value.getLocalBounds().size.x,128.f / value.getLocalBounds().size.y });
				window.draw(value);
			}
			else {
				hide.setPosition({ 1200.f + i * 100.f, 960.f - j });
				hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
				window.draw(hide);
			}
			i++;
			if (i % 7 == 0) {
				j += 130.0f;
				i = 0;
			}
			
		}
	}
}
//done//
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, const std::unordered_map<std::string, sf::Sprite>& aces
	, const std::vector<std::string>& colors) {
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
//done//
inline void winner(sf::RenderWindow& window, const bool flag_winner) {
	//music
	sf::Music music{};
	//load it 
	if (!music
		.openFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\music\\Clapping , Cheering & Applause - NO Copyright - Free Sound Effects.mp3")) {
		std::exit(1);
	}
	music.setVolume(100.f);
	music.play();
	//texture
	sf::Texture texture{};
	//load it
	if (flag_winner == true) {
		if (!texture.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\player1.png")) {
			std::exit(1);
		}
	}
	else {
		if (!texture.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\player2.png")) {
			std::exit(1);
		}
	}
	//
	sf::Vector2u texSize = texture.getSize();   // texture original size
	sf::Vector2u winSize = window.getSize();    // window size
	//sprite
	sf::Sprite sprite(texture);
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
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
//done
inline void draw(sf::RenderWindow& window) {
	//music,texture
	sf::Texture texture{};
	sf::Music music{};
	//load them
	if (!music.openFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\music\\Boo! sound effect.mp3")
		|| !texture.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\draw_texture_transparent.png")) {
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
//done
inline void menu(sf::RenderWindow& window, std::size_t& choice) {
	//music,textures,font
	sf::Music music,jumpscare_music{};
	sf::Texture _start{}, _tutorial{}, _exit{}, _github{}, _backround{}, _music_on{}, _music_off{}, _change_texture{}
	, _jumpscare{};
	sf::Font font{};
	//load them
	if (!music.openFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\music\\Sketchbook 2024-10-16.ogg")
		|| !_start.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutBlue.png")
		|| !_tutorial.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutFlameRed.png")
		|| !_change_texture.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutFlameBlue.png")
		|| !_exit.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutIce.png")
		|| !_github.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\github-mark\\github-mark-white.png")
		|| !_backround.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\dealer beauty.jpg")
		|| !_music_on.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\png-icons\\music_on.png")
		|| !_music_off.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\png-icons\\music_off.png")
		|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_jumpscare.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\68747470733a2f2f692e7974696d672e636f6d2f76692f524e6f48635745387462512f6d617872657364656661756c742e6a7067.jpg")
		|| !jumpscare_music.openFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\music\\712416__zombyklr__jumpscare-1.mp3")) {
		std::exit(1);
	}
	sf::Sprite start{ _start }, tutorial{ _tutorial }, exit{ _exit }, github{ _github }, backround{ _backround }
	, music_on{ _music_on }, music_off{ _music_off }, change_texture{ _change_texture }, jumpscare{_jumpscare};
	sf::Clock timer{};
	//
	music.setLooping(true);
	music.setVolume(100.f);
	music.play();
	//
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
	github.setPosition({ 1800.f,0.f });
	github.setScale({ 1 / 2.f,1 / 2.f });
	//
	music_on.setScale({ 64.f / _music_on.getSize().x,80.f / _music_on.getSize().y });
	//
	music_off.setScale({ 64.f / _music_off.getSize().x,80.f / _music_off.getSize().y });
	//
	//texts
	sf::Text text_start{ font,"start",50 }, text_tutorial{ font,"tutorial",50 }, text_exit{ font,"exit",50 }
	, text_change_texture{ font," textures",50 };
	//
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
	jumpscare.setScale({ window.getSize().x / jumpscare.getLocalBounds().size.x, window.getSize().y / jumpscare.getLocalBounds().size.y });
	//
	bool event{ false };
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is < sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				if (start.getGlobalBounds().contains(world_pos)) {
					//start
					return;
				}
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
					system("start https://github.com/Paltoudara?tab=repositories");
					timer.restart();
				}
				else if (music_on.getGlobalBounds().contains(world_pos)) {
					if (music.getStatus() == sf::SoundSource::Status::Playing) {
						music.stop();
					}
					else {
						music.play();
					}
					timer.restart();
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				//exit
				window.close();
				return;
			}
		}
		window.clear();
		if (!event && timer.getElapsedTime().asSeconds() >=10.f) {
			music.stop();
			event = true;
			window.draw(jumpscare);
			window.display();
			jumpscare_music.setVolume(100.f);
			jumpscare_music.play();
			sf::sleep(sf::seconds(2.0));
			music.play();

		}
		else {
			window.draw(backround);
			window.draw(start);
			window.draw(tutorial);
			window.draw(exit);
			window.draw(github);
			if (music.getStatus() == sf::SoundSource::Status::Playing) {
				window.draw(music_on);
			}
			else {
				window.draw(music_off);
			}
			window.draw(change_texture);
			//
			window.draw(text_start);
			window.draw(text_tutorial);
			window.draw(text_exit);
			window.draw(text_change_texture);
			window.display();
		}
	}
}
//done//
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces) {
	if (!can_he_play(player, color, num)) {
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
	}
	else if (check_for_card(window, player, color,
		num, table, aces, colors)) {
		//special cards
		if (num == "07") {//special card
			flag = !flag;
			for (std::size_t i = 0; i < 2 && !deck.empty(); ++i) {
				other_player.emplace(deck.back());
				deck.pop_back();
			}
		}
		else if (num != "08" && num != "09") {
			flag = !flag;
		}
	}
}
//done//
inline void pause_menu(sf::RenderWindow& window) {
	//textures,font
	sf::Texture _resume{}, _quit_game{}, _backround{};
	sf::Font font{};
	//load them
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_resume.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutBlue.png")
		|| !_quit_game.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\buttons\\LeftCutIce.png")
		|| !_backround.loadFromFile("C:\\Users\\user\\source\\repos\\Project_practice_1\\assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//sprites
	sf::Sprite resume{ _resume }, quit_game{ _quit_game }, backround{ _backround };
	//texts
	sf::Text text_resume{ font,"resume",30 }, text_quit_game{ font,"quit_game",30 };
	//
	resume.setPosition({ 960.f,540.f });
	resume.setOrigin({ resume.getLocalBounds().size.x / 2.f,resume.getLocalBounds().size.y / 2.f });
	resume.setScale({ 1 / 4.f,1 / 4.f });
	//
	quit_game.setPosition({ 960.f,650.f });
	quit_game.setOrigin({ quit_game.getLocalBounds().size.x / 2.f,quit_game.getLocalBounds().size.y / 2.f });
	quit_game.setScale({ 1 / 4.f,1 / 4.f });
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	text_resume.setPosition({ 970.f,530.f });
	text_resume.setOrigin({ text_resume.getLocalBounds().size.x / 2.f,text_resume.getLocalBounds().size.y / 2.f });
	//
	text_quit_game.setPosition({ 970.f,640.f });
	text_quit_game.setOrigin({ text_quit_game.getLocalBounds().size.x / 2.f,text_quit_game.getLocalBounds().size.y / 2.f });
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
		window.display();
	}
}
