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
//done
inline void load_file_paths(std::vector<std::string>& file_paths) {
	//load 52 carads
	//4 suits of 13 cards
	file_paths.reserve(52);
	std::vector<std::string>table{ "02","03","04","05","06","07","08","09","10","A","J","K","Q" };
	for (std::size_t i = 0; i < table.size(); i++) {
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_clubs_"+table[i]+".png");
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_diamonds_" + table[i] + ".png");
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_hearts_" + table[i] + ".png");
		file_paths.emplace_back("C:\\Users\\panag\\Source\\Repos\\Project_kati\\playing-cards-pack\\PNG\\Cards (large)\\card_spades_" + table[i] + ".png");
	}
}
//done
inline void tutorial(sf::RenderWindow& window) {
	sf::Font font{};
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {
		std::exit(1);
	}
	//
	sf::Texture _backround{};
	if (!_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//
	sf::Sprite backround{ _backround };
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	sf::Text text1{ font,"RULES OF THE GAME:",100 };
	text1.setPosition({ 930.f,20.f });
	text1.setFillColor(sf::Color::Black);
	text1.setOrigin({ text1.getLocalBounds().size.x / 2.f,text1.getLocalBounds().size.y / 2.f });
	text1.setOutlineColor(sf::Color::White);
	text1.setOutlineThickness(5.f);
	//
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
	//
	sf::Text text2{ font,message,30 };
	text2.setFillColor(sf::Color::Black);
	text2.setPosition({ 370.f,120.f });
	text2.setOutlineColor(sf::Color::White);
	text2.setOutlineThickness(5.f);
	//
	sf::Text text3{ font,"TAP ANYWHERE",100 };
	text3.setPosition({ 1200.f,970.f });
	text3.setFillColor(sf::Color::Black);
	text3.setOutlineColor(sf::Color::White);
	text3.setOutlineThickness(10.f);
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				return;
			}
			else if (event->is<sf::Event::Closed>()) {
				//exit
				window.close();
			}

		}
		window.clear();
		window.draw(backround);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();
	}
}
//done
inline void load_textures_from_files(std::vector<sf::Texture>& textures,
	std::vector<std::pair<std::string, sf::Sprite>>& deck
	,const std::vector<std::string>& file_paths
	, std::unordered_map<std::string, sf::Sprite>& aces) {
	textures.resize(file_paths.size());

	for (std::size_t i = 0; i < file_paths.size(); i++) {

		if (!textures[i].loadFromFile(file_paths[i])) {
			std::exit(1);
		}
		std::string name = { file_paths[i].substr(81) };
		name = std::string{ name.begin(),name.begin() + name.find('.') };
		sf::Sprite sprite{ textures[i] }; // sprite uses a stable texture reference
		if (name.contains('A')) {
			aces.emplace(name.substr(name.find_first_of('_') + 1,
				name.find_last_of('_') - 2), sprite);
		}
		deck.emplace_back(std::move(name), sprite);
	}
}
//done
inline void shuffle_deck(std::vector<std::pair<std::string, sf::Sprite>>& deck) {
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::shuffle(deck.begin(), deck.end(), gen);
}
//done
inline void initialize(std::vector <std::
	pair
	<std::string, sf::Sprite>>&
	deck, std::string& color, std::string& num, sf::Sprite& table
	,const std::unordered_map<std::string, sf::Sprite>& aces,
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
//done
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
//done
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
//done
inline void set_the_table_of_cards(
	sf::RenderWindow& window, std::unordered_map<std::string,
	sf::Sprite>& player1, std::unordered_map<std::string,
	sf::Sprite>& player2) {
	//
	std::size_t i{ 0 };
	float j{ 0.f };
	//
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
//done
inline bool check_for_card(sf::RenderWindow& window, std::unordered_map<std::string, sf::Sprite>
	& player, std::string& color, std::string& num, sf::Sprite& table
	,const std::unordered_map<std::string, sf::Sprite>& aces
	,const std::vector<std::string>& colors) {
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
//done
inline void winner(sf::RenderWindow&window,const bool flag_winner) {
	sf::Music music{};
	if (!music
		.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Clapping , Cheering & Applause - NO Copyright - Free Sound Effects.mp3")) {
		std::exit(1);
	}
	music.setVolume(100.f);
	music.play();
	//
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
//done
inline void draw(sf::RenderWindow&window) {
	sf::Music music{};
	if (!music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Boo! sound effect.mp3")) {
		std::exit(1);
	}
	music.setVolume(100.f);
	music.play();
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
//
inline void menu(sf::RenderWindow&window) {
	/*
		texture[0]->start->1
		texture[1]->tutorial->2
		texture[2]->exit->3
		texture[3]->//github->4
		texture[4]->//backround->5
		texture[5]->//music_on->6
		texture[6]->//music_off->7
	*/

	/*
		sprites[0]->start->1
		sprites[1]->tutorial->2
		sprites[2]->exit->3
		sprites[3]->//github->4
		sprites[4]->//backround->5
		sprites[5]->//music_on->6
		sprites[6]->//music_off->7
	*/
	sf::Music music{};
	if (!music.openFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Sketchbook 2024-10-16.ogg")) {
		std::exit(1);
	}
	std::vector<sf::Texture>textures(7);
	sf::Font font{};
	//
	music.setLooping(true);
	music.setVolume(100.f);
	music.play();
	//
	//textures load
	if (!textures[0].
		loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutBlue.png")) {
		std::exit(1);
	}
	if (!textures[1].
		loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutFlameRed.png"))
	{
		std::exit(1);
	}
	if (!textures[2].loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutIce.png")) {
		std::exit(1);
	}
	if (!textures[3].
		loadFromFile(R"(C:\Users\panag\Source\Repos\Project_kati\github-mark-c791e9551fe4\github-mark\github-mark-white.png)")) {
		std::exit(1);
	}
	if (!textures[4]
		.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\dealer beauty.jpg")) {
		std::exit(1);
	}
	if (!textures[5].loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\music_on.png")) {
		std::exit(1);
	}
	if (!textures[6].loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\music_off.png")) {
		std::exit(1);
	}
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::exit(1);
	}
	//sprites
	std::vector<sf::Sprite>sprites{ (sf::Sprite)textures[0],(sf::Sprite)textures[1],
	(sf::Sprite)textures[2],(sf::Sprite)textures[3],(sf::Sprite)textures[4],(sf::Sprite)textures[5]
	,(sf::Sprite)textures[6] };
	//buttons
	sprites[0].setScale({ 1 / 4.f,1 / 4.f });
	sprites[0].setPosition({ 960.f,540.f });
	sprites[0].setOrigin({ sprites[0].getLocalBounds().size.x / 2.f,sprites[0].getLocalBounds().size.y / 2.f });
	sprites[1].setScale({ 1 / 4.f,1 / 4.f });
	sprites[1].setPosition({ 960.f,650.f });
	sprites[1].setOrigin({ sprites[0].getLocalBounds().size.x / 2.f,sprites[0].getLocalBounds().size.y / 2.f });
	sprites[2].setScale({ 1 / 4.f,1 / 4.f });
	sprites[2].setPosition({ 960.f,760.f });
	sprites[2].setOrigin({ sprites[0].getLocalBounds().size.x / 2.f,sprites[0].getLocalBounds().size.y / 2.f });
	//github
	sprites[3].setPosition({ 1800.f,0.f });
	sprites[3].setScale({ 1 / 2.f,1 / 2.f });
	//music_on
	sprites[5].setScale({ 64.f / textures[5].getSize().x,80.f / textures[5].getSize().y });
	//music_off
	sprites[6].setScale({ 64.f / textures[6].getSize().x,80.f / textures[6].getSize().y });
	//
	//texts
	sf::Text text_start{ font,"start",50 };
	sf::Text text_tutorial{ font,"tutorial",50 };
	sf::Text text_exit{ font,"exit",50 };
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
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is < sf::Event::MouseButtonPressed>()) {
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				if (sprites[0].getGlobalBounds().contains(world_pos)) {
					//start
					return;
				}
				else if (sprites[1].getGlobalBounds().contains(world_pos)) {
					tutorial(window);
				}
				else if (sprites[2].getGlobalBounds().contains(world_pos)) {
					//exit
					window.close();
				}
				else if (sprites[3].getGlobalBounds().contains(world_pos)) {
					system("start https://github.com/Paltoudara?tab=repositories");
				}
				else if (sprites[5].getGlobalBounds().contains(world_pos)) {
					if (music.getStatus() == sf::SoundSource::Status::Playing) {
						music.stop();
					}
					else {
						music.play();
					}

				}
			}
			else if (event->is<sf::Event::Closed>()) {
				//exit
				window.close();
			}
		}
		window.clear();
		window.draw(sprites[4]);//backround
		for (std::size_t i = 0; i < 4; i++) {
			window.draw(sprites[i]);//all buttons
		}
		//music
		if (music.getStatus() == sf::SoundSource::Status::Playing) {
			window.draw(sprites[5]);
		}
		else {
			window.draw(sprites[6]);
		}
		//
		window.draw(text_start);
		window.draw(text_tutorial);
		window.draw(text_exit);
		window.display();
	}
}

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
//has resume,exit
inline void pause_menu(sf::RenderWindow& window) {
	sf::Texture _resume{};
	sf::Texture	_quit_game{};
	sf::Texture _backround{};
	sf::Font font{};
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::exit(1);
	}
	//
	if (!_resume.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutBlue.png")) {
		std::exit(1);
	}
	if (!_quit_game.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\Buttons\\Buttons\\Left Cut\\LeftCutIce.png")) {
		std::exit(1);
	}
	if (!_backround.loadFromFile("C:\\Users\\panag\\Source\\Repos\\Project_kati\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//
	sf::Sprite resume{ _resume };
	sf::Sprite quit_game{ _quit_game };
	sf::Sprite backround{ _backround };
	sf::Text text1{ font,"resume",30};
	sf::Text text2{ font,"quit_game",30 };
	resume.setPosition({ 960.f,540.f });
	resume.setOrigin({ resume.getLocalBounds().size.x/2.f,resume.getLocalBounds().size.y/2.f});
	resume.setScale({1/4.f,1/4.f});
	//
	quit_game.setPosition({ 960.f,650.f });
	quit_game.setOrigin({quit_game.getLocalBounds().size.x/2.f,quit_game.getLocalBounds().size.y/2.f});
	quit_game.setScale({1/4.f,1/4.f});
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	text1.setPosition({ 970.f,530.f });
	text1.setOrigin({text1.getLocalBounds().size.x/2.f,text1.getLocalBounds().size.y/2.f});
	//
	text2.setPosition({ 970.f,640.f });
	text2.setOrigin({ text2.getLocalBounds().size.x / 2.f,text2.getLocalBounds().size.y/2.f});
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
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		window.clear();
		window.draw(backround);
		window.draw(resume);
		window.draw(quit_game);
		window.draw(text1);
		window.draw(text2);
		window.display();
	}
}



//--------------------
//	IMPLEMENTATION END
//--------------------
