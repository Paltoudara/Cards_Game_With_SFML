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
			|| key.contains('A')) {
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
				std::cout << color << " " <<num<< '\n';
				std::cout << key << '\n';
				if (key.contains("A")) {
					color = colors[rand() % 4];
					num = "A";
					//for pc
					//table = aces.at(color + "_A");
					//for laptop
					table = aces.at(color );
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

//--------------------
//	IMPLEMENTATION END
//--------------------
