#include<iostream>
#include<algorithm>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<cstdlib>
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
//
inline void load_textures_from_files(std::unordered_map<std::size_t, sf::Texture>& deck,std::vector<std::string>&file_paths) {
	sf::Texture texture{};
	for (std::size_t i = 1; i <= file_paths.size(); i++) {
		if (!texture.loadFromFile(file_paths[i - 1])) {
			std::exit(1);
		}
		deck[i] = texture;
	}
}
