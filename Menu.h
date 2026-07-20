#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
#include<unordered_map>
#include<cstdlib>
#include<random>
#include<utility>
#include<SFML/Audio.hpp>
#include <SFML/System.hpp>
#include<fstream>
inline void huffman_tree_explanation(sf::RenderWindow& window) {
	//
	sf::Texture _backround{};
	sf::Font font{};
	//
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//
	sf::String message =
		L"To make the huffman tree is simple:"
		L"First you take all possibilities and sort them by increasing order(if two possibilities\n)"
		L"have the same chance the order doesn't matter the real algo uses a priority queue"
		L" take the two smallest possibilities\nand merge them(take the sum of their possibilities).Take the new possibility and then"
		L" put it with the others and re-sort\nand then do the same.Stop when there is only one tree.I read sedgewick book,the figure he shows,puts the merged\npossibilities wherever he wants in the sorted order"
		L". I also asked chat gpt and gemini pro.They said the same."
		L"In the e\nnd sort,take the two mins and then re-sort and then continue until there is only one tree left.";
	//
	sf::Sprite backround{ _backround };
	//
	sf::Text text_title{ font,"HUFFMAN TREE EXPLANATION:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });text_title.setFillColor(sf::Color::Black);//
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);//
	//
	text_rules.setFillColor(sf::Color::Black);text_rules.setPosition({ 250.f,120.f });
	text_rules.setOutlineColor(sf::Color::White);text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });text_tap.setFillColor(sf::Color::Black);
	text_tap.setOutlineColor(sf::Color::White);text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {//
			if (event->is<sf::Event::MouseButtonPressed>()) {//
				return;
			}
			else if (event->is<sf::Event::Closed>()) {//
				//
				window.close();
				return;
			}

		}
		//
		window.clear();
		window.draw(backround);
		window.draw(text_title);
		window.draw(text_rules);
		window.draw(text_tap);
		window.display();
	}
}
//
inline std::size_t change_textures(sf::RenderWindow& window) {
	//
	sf::Texture _backround{},_classic_cards{},_vintage_cards{};
	sf::Font font{};
	//
	if (!_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")
		|| !_classic_cards.loadFromFile("assets\\playing-cards-pack - Copy\\PNG1\\card_clubs_03.png")
		|| !_vintage_cards.loadFromFile("assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_03.png")
		|| !font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {
		std::exit(1);
	}
	//
	sf::Sprite classic_cards{ _classic_cards }, vintage_cards{ _vintage_cards }, backround{ _backround };
	//
	sf::Text text_title{ font,"  CLICK TO CHOOSE THE TEXTURE THAT YOU WANT:",80 }, text_classic{ font,"CLASSIC:",80 }
	, text_vintage{ font,"VINTAGE:",80 };
	//
	text_title.setFillColor(sf::Color::Black);text_title.setPosition({ 0.f,20.f });//
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);//
	//
	text_classic.setFillColor(sf::Color::Black);text_classic.setPosition({ 460.f,320.f });
	text_classic.setOutlineColor(sf::Color::White);text_classic.setOutlineThickness(5.f);
	//
	text_vintage.setFillColor(sf::Color::Black);text_vintage.setPosition({ 1050.f,320.f });
	text_vintage.setOutlineColor(sf::Color::White);text_vintage.setOutlineThickness(5.f);
	//
	classic_cards.setScale({ 10.f,10.f });classic_cards.setPosition({ 300.f,400.f });vintage_cards.setPosition({ 1000.f,420.f });
	vintage_cards.setScale({ 450.f / vintage_cards.getLocalBounds().size.x,600.f / vintage_cards.getLocalBounds().size.y });
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return 0;
			}
			else if (event->is<sf::Event::MouseButtonPressed>()) {
				//
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				//
				if (classic_cards.getGlobalBounds().contains(world_pos)) {//
					return 0;//
				}
				else if (vintage_cards.getGlobalBounds().contains(world_pos)) {
					return 1;
				}
			}
		}
		//
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
//
//
inline void load_file_paths(std::vector<std::string>& file_paths, const std::size_t choice) {
	//
	file_paths.reserve(52);
	//
	std::vector<std::string>table{ "02","03","04","05","06","07","08","09","10","J","K","Q","A" };
	//
	std::string png_number=choice==0?"PNG1":"PNG2";
	//
	for (std::size_t i = 0; i < table.size(); i++) {
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_clubs_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_diamonds_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_hearts_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_spades_" + table[i] + ".png");
	}
	
}
//
inline void tutorial_of_the_game(sf::RenderWindow& window) {
	//
	sf::Texture _backround{};
	sf::Font font{};
	//
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg"))
	{
		std::exit(1);
	}
	//
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
	//
	sf::Sprite backround{ _backround };
	//
	sf::Text text_title{ font,"RULES OF THE GAME:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });text_title.setFillColor(sf::Color::Black);
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	//
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);
	//
	text_rules.setFillColor(sf::Color::Black);text_rules.setPosition({ 370.f,120.f });text_rules.setOutlineColor(sf::Color::White);
	text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });text_tap.setFillColor(sf::Color::Black);text_tap.setOutlineColor(sf::Color::White);
	text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });//
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::MouseButtonPressed>()) {
				return;
			}
			else if (event->is<sf::Event::Closed>()) {
				//
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
//
inline void load_textures_from_files(std::vector<sf::Texture>& textures,std::vector<std::pair<std::string, sf::Sprite>>& deck
	,const std::vector<std::string>& file_paths, const std::size_t choice) {

	textures.resize(file_paths.size());
	//
	for (std::size_t i = 0; i < file_paths.size(); i++) {
		if (!textures[i].loadFromFile(file_paths[i])) {
			std::exit(1);
		}
		//
		std::string name=file_paths[i].substr(file_paths[i].find_last_of('\\')+1);
		name = std::string{ name.begin(),name.begin() + name.find('.') };
		//
		deck.emplace_back(std::move(name), textures[i]);
		//
	}
}
//
inline void menu(sf::RenderWindow& window, std::size_t& choice) {
	//
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::bernoulli_distribution chance(1.0 / 1000.0);
	bool flag = chance(gen);
	//
	sf::Music music, jumpscare_music{};
	sf::Texture _start{}, _tutorial{}, _exit{}, _github{}, _backround{}, _music_on{}, _music_off{}, _change_texture{},_jumpscare{}
	, _huffman_button{}, _reset_score{};
	sf::Font font{};
	//
	if (!music.openFromFile("assets\\music\\WhiteNoiz.mp3")
		|| !_start.loadFromFile("assets\\buttons\\LeftCutBlue.png")
		|| !_tutorial.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")
		|| !_change_texture.loadFromFile("assets\\buttons\\LeftCutFlameBlue.png")
		|| !_exit.loadFromFile("assets\\buttons\\LeftCutIce.png")
		|| !_github.loadFromFile("assets\\github-mark\\github-mark-white.png")
		|| !_backround.loadFromFile("assets\\backround\\dealer beauty.jpg")
		|| !_music_on.loadFromFile("assets\\png-icons\\music_on.png")
		|| !_music_off.loadFromFile("assets\\png-icons\\music_off.png")/
		|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_jumpscare.loadFromFile("assets\\backround\\68747470733a2f2f692e7974696d672e636f6d2f76692f524e6f48635745387462512f6d617872657364656661756c742e6a7067.jpg")
		|| !jumpscare_music.openFromFile("assets\\music\\712416__zombyklr__jumpscare-1.mp3")
		|| !_huffman_button.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")
		|| !_reset_score.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")
		) {
		std::exit(1);
	}
	//
	sf::Sprite start{ _start }, tutorial{ _tutorial }, exit{ _exit }, github{ _github }, backround{ _backround }
		, music_on{ _music_on }, music_off{ _music_off }, change_texture{ _change_texture }, jumpscare{ _jumpscare }
	, huffman_button{ _huffman_button }, reset_score{ _reset_score };
	sf::Clock timer{};
	//
	music.setLooping(true);music.setVolume(100.f);music.play();
	
	start.setScale({ 1 / 4.f,1 / 4.f });start.setPosition({ 960.f,540.f });
	start.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	tutorial.setScale({ 1 / 4.f,1 / 4.f });tutorial.setPosition({ 960.f,650.f });
	tutorial.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	exit.setScale({ 1 / 4.f,1 / 4.f });exit.setPosition({ 960.f,760.f });
	exit.setOrigin({ start.getLocalBounds().size.x / 2.f,start.getLocalBounds().size.y / 2.f });
	//
	change_texture.setScale({ 1 / 4.f,1 / 4.f });change_texture.setPosition({ 960.f,870.f });
	change_texture.setOrigin({ change_texture.getLocalBounds().size.x / 2.f,change_texture.getLocalBounds().size.y / 2.f });
	//
	huffman_button.setScale({ 1 / 4.f,1 / 4.f });huffman_button.setPosition({ 960.f,980.f });
	huffman_button.setOrigin({ huffman_button.getLocalBounds().size.x / 2.f,huffman_button.getLocalBounds().size.y / 2.f });
	//
	reset_score.setScale({ 1 / 3.5f,1 / 3.5f });reset_score.setPosition({ 960.f,440.f });
	reset_score.setOrigin({ reset_score.getLocalBounds().size.x / 2.f,reset_score.getLocalBounds().size.y / 2.f });
	//
	github.setPosition({ 1800.f,0.f });github.setScale({ 1 / 2.f,1 / 2.f });
	//
	music_on.setScale({ 64.f / _music_on.getSize().x,80.f / _music_on.getSize().y });
	//
	music_off.setScale({ 64.f / _music_off.getSize().x,80.f / _music_off.getSize().y });
	//
	sf::Text text_start{ font,"start",50 }, text_tutorial{ font,"tutorial",50 }, text_exit{ font,"exit",50 }
	, text_change_texture{ font," textures",50 }, text_huffman{ font,"huffman",50 }, text_reset_score{ font,"clear score",50 };
	//
	text_start.setPosition({ 960.f,530.f });text_start.setFillColor(sf::Color::White);//
	text_start.setOrigin({ text_start.getLocalBounds().size.x / 2.f,text_start.getLocalBounds().size.y / 2.f });
	//
	text_tutorial.setPosition({ 960.f,640.f });text_tutorial.setFillColor(sf::Color::Black);
	text_tutorial.setOrigin({ text_tutorial.getLocalBounds().size.x / 2.f,text_tutorial.getLocalBounds().size.y / 2.f });
	//
	text_exit.setPosition({ 960.f,750.f });text_exit.setFillColor(sf::Color::White);
	text_exit.setOrigin({ text_exit.getLocalBounds().size.x / 2.f,text_exit.getLocalBounds().size.y / 2.f });
	//
	text_change_texture.setPosition({ 960.f,860.f });text_change_texture.setFillColor(sf::Color::White);
	text_change_texture.setOrigin({ text_change_texture.getLocalBounds().size.x / 2.f,text_change_texture.getLocalBounds().size.y / 2.f });
	//
	text_huffman.setPosition({ 960.f,970.f });text_huffman.setFillColor(sf::Color::White);
	text_huffman.setOrigin({ text_huffman.getLocalBounds().size.x / 2.f,text_huffman.getLocalBounds().size.y / 2.f });
	//
	text_reset_score.setPosition({ 970.f,430.f });text_reset_score.setFillColor(sf::Color::White);
	text_reset_score.setOrigin({ text_reset_score.getLocalBounds().size.x / 2.f,text_reset_score.getLocalBounds().size.y / 2.f });
	//
	jumpscare.setScale({ window.getSize().x / jumpscare.getLocalBounds().size.x, window.getSize().y / jumpscare.getLocalBounds().size.y });
	//
	bool event{ false };
	while (window.isOpen()) {
		//
		while (const auto event = window.pollEvent()) {
			if (event->is < sf::Event::MouseButtonPressed>()) {
				
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				//
				if (start.getGlobalBounds().contains(world_pos)) {
					//
					return;
				}
				//
				else if (tutorial.getGlobalBounds().contains(world_pos)) {
					//
					tutorial_of_the_game(window);timer.restart();
					if (!window.isOpen())return;
				}
				else if (exit.getGlobalBounds().contains(world_pos)) {
					//
					window.close();
					return;
				}
				else if (change_texture.getGlobalBounds().contains(world_pos)) {
					//
					choice = change_textures(window);timer.restart();
					if (!window.isOpen())return;
				}
				else if (github.getGlobalBounds().contains(world_pos)) {
					//
					system("start https://github.com/Paltoudara?tab=repositories");timer.restart();
				}
				//
				else if (music_on.getGlobalBounds().contains(world_pos)) {
					//
					if (music.getStatus() == sf::SoundSource::Status::Playing)music.stop();
					else music.play();
					timer.restart();
				}
				else if (flag==true && huffman_button.getGlobalBounds().contains(world_pos)) {
					//
					huffman_tree_explanation(window);timer.restart();
					if (!window.isOpen())return;
				}
				else if (reset_score.getGlobalBounds().contains(world_pos)) {
					//
					std::ofstream score_file("score.txt");
					if (!score_file.is_open()) { std::exit(1); }
					score_file << "0\n";score_file << "0";score_file.close();
					//
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				//
				window.close();
				return;
			}
		}
		//
		window.clear();
		if (!event && timer.getElapsedTime().asSeconds() >= 360.f) {//
			//
			music.stop();//
			event = true;//
			window.draw(jumpscare);window.display();
			jumpscare_music.setVolume(100.f);jumpscare_music.play();
			sf::sleep(sf::seconds(2.0));
			music.play();

		}
		else {
			//
			window.draw(backround);window.draw(start);window.draw(tutorial);window.draw(exit);window.draw(github);
			//
			if (music.getStatus() == sf::SoundSource::Status::Playing) window.draw(music_on);
			else window.draw(music_off);
			
			window.draw(change_texture);window.draw(text_start);window.draw(text_tutorial);window.draw(text_exit);
			window.draw(text_change_texture);
			if (flag) {
				window.draw(huffman_button);
				window.draw(text_huffman);
			}
			window.draw(reset_score);window.draw(text_reset_score);window.display();
		}
	}
}
