#include<iostream>
#include<algorithm>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<cstdlib>
#include<random>
#include<optional>
inline void load_file_paths(std::vector<std::string>&file_paths) {
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_0"+std::to_string(i)+".png");
	}
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_10.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_A.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_J.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_K.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_Q.png");
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_0"+std::to_string(i)+".png");
	}
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_10.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_A.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_J.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_K.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_Q.png");
	//
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_0"+std::to_string(i) + ".png");
	}
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_10.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_A.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_J.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_K.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_Q.png");
	//
	for (std::size_t i = 2; i < 10; i++) {
		file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_0" + std::to_string(i) + ".png");
	}
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_10.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_A.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_J.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_K.png");
	file_paths.emplace_back("C:\\Users\\user\\source\\repos\\Project_practice\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_Q.png");
	//
}
//create a vector deck
inline void load_textures_from_files(std::vector<sf::Texture>&textures,
	std::vector<std::pair<std::size_t, sf::Sprite>>& deck,std::vector<std::string>&file_paths) {
	textures.resize(file_paths.size());

	for (std::size_t i = 0; i < file_paths.size(); i++) {

		if (!textures[i].loadFromFile(file_paths[i])) {
			std::exit(1);
		}

		sf::Sprite sprite{ textures[i] }; // sprite uses stable texture reference
		deck.emplace_back(i + 1, sprite);
	}
}
//
inline void shuffle_deck(std::vector<std::pair<std::size_t, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//
inline void give_players_cards(std::unordered_map<std::size_t, sf::Sprite>&player1
, std::unordered_map<std::size_t, sf::Sprite>&player2
, std::vector<std::pair<std::size_t, sf::Sprite>>& deck) {
	for (std::size_t i = 0; i < 7; i++) {
		player1.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
	}
}
/*
#include<iostream>
#include<algorithm>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<cstdlib>
#include<random>
#include<optional>
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
//create a vector deck
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::size_t, sf::Sprite>>& deck, std::vector<std::string>& file_paths) {
	textures.resize(file_paths.size());

	for (std::size_t i = 0; i < file_paths.size(); i++) {

		if (!textures[i].loadFromFile(file_paths[i])) {
			std::exit(1);
		}

		sf::Sprite sprite{ textures[i] }; // sprite uses stable texture reference
		deck.emplace_back(i + 1, sprite);
	}
}
//
inline void shuffle_deck(std::vector<std::pair<std::size_t, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//
inline void give_players_cards(std::unordered_map<std::size_t, sf::Sprite>& player1
	, std::unordered_map<std::size_t, sf::Sprite>& player2
	, std::vector<std::pair<std::size_t, sf::Sprite>>& deck) {
	for (std::size_t i = 0; i < 7; i++) {
		player1.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second);
		deck.pop_back();
	}
}

inline bool can_he_play(const std::unordered_map<std::size_t
	,sf::Sprite>& player,const std::string&color,
const std::string& num,
	const std::unordered_map<std::size_t, std::string>&names) {
	for (const auto& [key, value] : player) {
		if (names.at(key).contains(color)
			||names.at(key).contains(num)) {
			return true;
		}
	}
	return false;
}

inline void set_the_table_of_cards(
sf::RenderWindow &window,std::unordered_map<std::size_t,
	sf::Sprite>&player1,std::unordered_map<std::size_t,
	sf::Sprite>&player2) {
	std::size_t i{ 0 };
	float j{ 0 };
	for (auto& [key, value] : player1) {
		value.setPosition({ 200.0f + i * 300.0f, 100.0f + j });
		i++;
		if (i % 7 == 0) {
			j += 100.0f;
			i = 0;
		}
		window.draw(value);
	}
	i = 0;
	j = 1;
	for (auto& [key, value] : player2) {
		value.setPosition({ 200.f + i * 300.f, 1240.f - j });
		i++;
		if (i % 7 == 0) {
			j += 100.0f;
			i = 0;
		}
		window.draw(value);
	}
}

*/
