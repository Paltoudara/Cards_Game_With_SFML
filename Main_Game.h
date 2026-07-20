#pragma once
#include<vector>
#include<string>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<random>
#include<utility>
//initialize_start_of_the_game=>initializes the start of the game
inline void initialize_start_of_the_game(std::vector <std::pair<std::string, sf::Sprite>>&deck,std::string& color, std::string& num
	,sf::Sprite& table,std::unordered_map<std::string, sf::Sprite>& player1,std::unordered_map<std::string, sf::Sprite>& player2)
{
	//strings in the deck format=>card_symbol_num,parse this and take symbol ,num and put it in color and num values
	std::string temp=deck.back().first;
	color = std::string{ temp.begin() + temp.find('_') + 1,temp.begin() + temp.find_last_of('_')};
	num = deck.back().first.substr(deck.back().first.find_last_of('_') + 1);
	table = deck.back().second;//we must give a card to the table
	deck.pop_back();
	////gives each player 7 cards
	for (std::size_t i = 0; i < 7; i++) {//every card you give to the hashmaps of the players,take out from the deck
		player1.emplace(deck.back().first, deck.back().second); deck.pop_back();
		player2.emplace(deck.back().first, deck.back().second); deck.pop_back();
	}
}
//can_he_play,check if any card on the players deck can be played when it is his turn,
//color contains the symbol and num contains the num of the card on the table table,see if the names of the cards
//that the player holds contain the color or the num
//std::string from player map format->card_symbol_num,we see if color matches symbol or num matches num or the player has an ace
inline bool can_he_play(const std::unordered_map<std::string, sf::Sprite>& player,const std::string& color,const std::string& num) {
	for (const auto& [key, value] : player) {
		if (key.contains(color) || key.contains(num)|| key.contains("A")) {
			return true;
		}
	}
	return false;
}
//set_the_table_of_cards->for every frame display the game that is played beetween the two players
inline void draw_the_cards_of_the_players(sf::RenderWindow& window, std::unordered_map<std::string,sf::Sprite>& player1
	, std::unordered_map<std::string,sf::Sprite>& player2, const std::size_t choice, const bool flag, sf::Sprite& hide) {
	//hide is the sprite that hides the cards for the player that is not his turn
	//this code simply passes the two hashmaps of the players at the same time in order to draw the cards 
	//that they are holding at their hands if it is their turn
	//also remember that choice==0 for classic cards and choice==1 for vintage cards
	std::size_t i{ 0 };
	float j{ 0.f };
	auto t1 = player1.begin(), t2 = player2.begin();
	//
	while (t1 != player1.end() || t2 != player2.end()) {
		//for flag==true display player1 cards and display player2 cards hidden
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
		//every seven cards place the next sprite for choice==0 up 125.f pixels and for choice==1 up 130.0f pixels 
		if (i % 7 == 0) {
			if (choice == 0) j += 125.0f;
			else j += 130.0f;
			i = 0;
		}
		if (t1 != player1.end())++t1;
		if (t2 != player2.end())++t2;
	}
	//
}
//check_for_card->wait until the player that is his turn to play,plays a card that is acceptable(matches symbols or numbers
//with the table card)
//check_for_card->this function simply waits for the player to play an acceptable card in the table then it returns true
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>& player, 
	std::string& color, std::string& num, sf::Sprite& table, const std::unordered_map<std::string, sf::Sprite>& aces
	, const std::vector<std::string>& colors) {
	//get mouse cords and check the map of the player that plays and check if he tapped a card that is valid
	//if thats the case drop it to the table and extract the card that he played from his map
	sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
	sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
	//
	std::string card_to_remove{};
	for (const auto& [key, value] : player) {
		//collision,remember key is the name of card that contains card_symbol_num
		if (value.getGlobalBounds().contains(world_pos)&& (key.contains(color) || key.contains(num) || key.contains("A"))) {
			//acceptable cards that he can play according to the rules
			card_to_remove = key;
			//key has format=> card_symbol_num
			color = key.contains('A') ? colors[rand() % 4] :
				std::string{ key.begin() + key.find('_') + 1,key.begin()+key.find_last_of('_')};//change color and num to represent what card is in the table right now
			num = key.substr(key.find_last_of('_')+1);
			table = key.contains('A') ? aces.at(color) : value;
			break;
		}
	}
	//if he played a valid card then the card_to_remove variable will not be empty
	if (!card_to_remove.empty()) {
		player.extract(card_to_remove);//extract the card that he played
		return true;
	}
	return false;
}
//player_plays->pretty much it follows the rules of the game and sees if a player can play or not
//for more see implementation details and read the rules of the game 
//this is the overall structure of the game
//when a player plays what happends
inline void player_plays(std::unordered_map<std::string, sf::Sprite>& player, bool& flag
	, std::unordered_map<std::string, sf::Sprite>& other_player, std::vector<std::pair<std::string, sf::Sprite>>& deck
	, std::string& color, std::string& num, sf::RenderWindow& window, std::vector<std::string>& colors, sf::Sprite& table
	, std::unordered_map<std::string, sf::Sprite>& aces, sf::Music& music) {
	//when a player plays the might have a card to play or not 
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
		if (num == "07") {//special card
			flag = !flag;
			for (std::size_t i = 0; i < 2 && !deck.empty(); ++i) {//a 7
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
//when a texture fails to load plz deallocate properly not simply exit
//only for the files show error text,for textures we are already good
//std::cout << color << " " << num << '\n';
//std::cout << key << "\n\n";
