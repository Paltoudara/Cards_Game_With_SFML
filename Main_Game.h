#pragma once
#include<vector>
#include<string>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<random>
#include<utility>
//initialize_start_of_the_game=>gives each player 7 cards from the deck and also intializes the variables for the table.
//The strings in the deck and the players hashmaps have the format->card_symbol_num
inline void initialize_start_of_the_game(std::vector <std::pair<std::string, sf::Sprite>>&deck,std::string& color, std::string& num
	,sf::Sprite& table,std::unordered_map<std::string, sf::Sprite>& player1,std::unordered_map<std::string, sf::Sprite>& player2)
{
	//parse the format card_symbol_num.Take the symbol and the num and put them in the color,num variables.
	//Do this by using simple std::string methods
	std::string temp=deck.back().first;
	color = std::string{ temp.begin() + temp.find('_') + 1,temp.begin() + temp.find_last_of('_')};
	num = deck.back().first.substr(deck.back().first.find_last_of('_') + 1);
	table = deck.back().second;//we must give a card to the table
	deck.pop_back();
	//put those seven cards in the players hashmaps
	for (std::size_t i = 0; i < 7; i++) {//every card you give must be takek out from the deck
		player1.emplace(deck.back().first, deck.back().second); deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second); deck.pop_back();
	}
}
//can_he_play=>when one player plays,we check if any card on his hashmap contain the symbol or contain the num on the table
//color contains the symbol of the card on the table and num contains the num of the card on the table.
//std::string format from player hashmap->card_symbol_num
inline bool can_he_play(const std::unordered_map<std::string, sf::Sprite>& player,const std::string& color,const std::string& num) {
	for (const auto& [key, value] : player) {
		if (key.contains(color) || key.contains(num)|| key.contains("A")) {
			return true;
		}
	}
	return false;
}
//draw_the_cards_of_the_players->for every frame simply display the cards of the two players.
inline void draw_the_cards_of_the_players(sf::RenderWindow& window,std::unordered_map<std::string,sf::Sprite>& player1
	, std::unordered_map<std::string,sf::Sprite>& player2, const std::size_t choice, const bool flag, sf::Sprite& hide) {
	//hide sprite hides the cards for the player that is not his turn
	//we display normally the cards of the player how is his turn to play
	std::size_t i{ 0 };
	float j{ 0.f };
	auto t1 = player1.begin(), t2 = player2.begin();
	//
	while (t1 != player1.end() || t2 != player2.end()) {
		//for flag==true display player1 cards and display player2 cards hidden
		//here we just apply some attributes to the sprites before displaying them
		if (flag == true && t1 != player1.end()) {
			t1->second.setPosition({ 0.0f + i * 100.0f, j });
			if(choice==0)t1->second.setScale({ 2.f,2.f });
			else t1->second.setScale({ 80.f / t1->second.getLocalBounds().size.x,128.f / t1->second.getLocalBounds().size.y });
			window.draw(t1->second);
		}
		if (flag == true && t2 != player2.end()) {
			hide.setPosition({ 1200.f + i * 100.f, 960.f - j });
			if (choice == 0)hide.setScale({ 2.f,2.f });
			else hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
			window.draw(hide);

		}
		//for flag==false display player2 cards and display player1 cards  hidden
		if (flag == false && t1 != player1.end()) {
			hide.setPosition({ 0.0f + i * 100.0f, j });
			if (choice == 0)hide.setScale({ 2.f,2.f });
			else hide.setScale({ 80.f / hide.getLocalBounds().size.x,128.f / hide.getLocalBounds().size.y });
			window.draw(hide);
		}
		if (flag == false && t2 != player2.end()) {
			t2->second.setPosition({ 1200.f + i * 100.f, 960.f - j });
			if(choice==0)t2->second.setScale({ 2.f,2.f });
			else t2->second.setScale({ 80.f / t2->second.getLocalBounds().size.x,128.f / t2->second.getLocalBounds().size.y });
			window.draw(t2->second);
		}
		i++;
		//for every seven cards place the next sprite for choice==0 up 125.f pixels and for choice==1 up 130.0f pixels.
		//This is done simply for smooth display of the cards on the screen
		if (i % 7 == 0) {
			if (choice == 0) j += 125.0f;
			else j += 130.0f;
			i = 0;
		}
		//
		if (t1 != player1.end())++t1;
		if (t2 != player2.end())++t2;
	}
}
//
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>& player, 
	std::string& color, std::string& num, sf::Sprite& table, const std::unordered_map<std::string, sf::Sprite>& aces
	, const std::vector<std::string>& colors) {
	//
	//
	sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
	sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
	//
	std::string card_to_remove{};
	for (const auto& [key, value] : player) {
		//
		if (value.getGlobalBounds().contains(world_pos)&& (key.contains(color) || key.contains(num) || key.contains("A"))) {
			//
			card_to_remove = key;
			//
			color = key.contains('A') ? colors[rand() % 4] :
				std::string{ key.begin() + key.find('_') + 1,key.begin()+key.find_last_of('_')};//change color and num to represent what card is in the table right now
			num = key.substr(key.find_last_of('_')+1);
			table = key.contains('A') ? aces.at(color) : value;
			break;
		}
	}
	//
	if (!card_to_remove.empty()) {
		player.extract(card_to_remove);//
		return true;
	}
	return false;
}
//
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces, sf::Music& music) {
	//
	if (!can_he_play(player, color, num)&&deck.size()>0) {
		player.emplace(deck.back());
		deck.pop_back();
		if (!can_he_play(player, color, num)) {
			flag = !flag;
		}
	}
	else if (!can_he_play(player, color, num) && deck.size() == 0) { flag =!flag; }
	else if (check_for_card(window, player, color,num, table, aces, colors)) {
		//
		music.setVolume(100.f);
		music.play();
		//
		if (num == "07") {//
			flag = !flag;
			for (std::size_t i = 0; i < 2 && !deck.empty(); ++i) {//a 7
				other_player.emplace(deck.back());
				deck.pop_back();
			}
		}//
		else if (num != "08" && num != "09") {
			flag = !flag;
		}
	}
}
//std::cout << color << " " << num << '\n';
//std::cout << key << "\n\n";
