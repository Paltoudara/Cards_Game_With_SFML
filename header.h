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
bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces
	, std::vector<std::string>& colors);
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
		i++;
		if (i % 7 == 0) {
			j += 100.0f;
			i = 0;
		}
		window.draw(value);
	}
	i = 0;
	j = 0;
	for (auto& [key, value] : player2) {
		value.setPosition({ 1200.f + i * 100.f, 960.f - j });
		i++;
		if (i % 7 == 0) {
			j += 100.0f;
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
void create_menu() {
	sf::VideoMode video = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window{video,"sfml",sf::State::Fullscreen};
	window.setFramerateLimit(60);
	sf::Font font{};
	sf::Texture texture1{};
	sf::Texture texture2{};
	sf::Texture texture3{};
	if (!texture1.
		loadFromFile("C:\\Users\\panag\\Downloads\\buttons-2\\start-2.png")) {
		std::exit(1);
	}
	if (!texture2.
		loadFromFile("C:\\Users\\panag\\Downloads\\buttons-2\\exit-2.png")) {
		std::exit(1);
	}
	if (!texture3.
		loadFromFile(R"(C:\Users\panag\Source\Repos\Project_kati\github-mark-c791e9551fe4\github-mark\github-mark-white.png)")) {
		std::exit(1);
	}
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::exit(1);
	}
	//
	sf::Sprite sprite1{ texture1 };
	sf::Sprite sprite2{ texture2 };
	sf::Sprite sprite3{texture3};
	sf::Text text{ font };
	text.setString("Welcome to my cards game");
	text.setPosition({ video.size.x / 2.f-520.f,video.size.y / 2.f - 200.f });
	text.setScale({ 3.f,3.f });
	text.setFillColor(sf::Color::White);
	//
	sprite1.setPosition({ video.size.x / 2.f,video.size.y / 2.f });
	sprite1.setScale({ 3.f,3.f });
	sprite1.setOrigin({ 137 / 2.f,37 / 2.f });
	sprite2.setPosition({ video.size.x / 2.f,video.size.y / 2.f+200.f });
	sprite2.setScale({ 3.f,3.f });
	sprite2.setOrigin({ 137 / 2.f,37 / 2.f });
	sprite3.setPosition({ 0.0f,850.f });
	
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
					std::exit(0);
				}
				else if (sprite3.getGlobalBounds().contains(world_pos)) {
					system("start https://github.com/Paltoudara?tab=repositories");
				}
			}
		}
		window.clear(sf::Color::Black);
		window.draw(rectangle_p1);
		window.draw(rectangle_p2);
		window.draw(text);
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		window.display();
	}
}


//--------------------
//	IMPLEMENTATION END
//--------------------
