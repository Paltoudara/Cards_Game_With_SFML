#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<SFML/Audio.hpp>
#include<cstdlib>
//winner function=>it is just the winner screen with some clapping audio.This function also updates the scores of the two players
//that are in the score.txt
inline void winner(sf::RenderWindow& window, const bool flag_winner) {
	//clapping audio
	sf::Music music{};
	//score_1 ->player1,score_2 ->player2
	std::size_t score_1{}, score_2{};
	//we open the file score.txt for reading and also writing.The file has literaly two numbers>=0 inside
	std::fstream file("score.txt", std::ios::in | std::ios::out);
	//texture for the backround of the screen
	sf::Texture _backround{};
	//load the clapping audio
	if (!music.openFromFile("assets\\music\\Clapping , Cheering & Applause - NO Copyright - Free Sound Effects.mp3"))
	{
		return;
	}
	//take the scores of the two players
	if (!file.is_open()) { std::cout << "failed to open the file score.txt"; std::exit(1); }
	file >> score_1 >> score_2;
	file.seekg(0, std::ios::beg);
	//play the clapping audio only once
	music.setVolume(100.f);
	music.play();
	//
	if (flag_winner == true && !_backround.loadFromFile("assets\\backround\\player1.png")) { return; }
	else if (flag_winner == false && !_backround.loadFromFile("assets\\backround\\player2.png")) { return; }
	//update the score of the player who won
	if (flag_winner == true) { score_1++; }
	else if (flag_winner == false) { score_2++; }
	//write the new scores back to the file score.txt and close it 
	file << score_1 << "\n";
	file << score_2;
	file.close();
	//
	sf::Vector2u texSize = _backround.getSize(),winSize = window.getSize();     
	//change scale of the backround sprite to cover all the screen
	sf::Sprite backround(_backround);
	backround.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();
		window.draw(backround);
		window.display();
	}
}
//
inline void draw(sf::RenderWindow& window) {
	//
	sf::Texture texture{};
	sf::Music music{};
	//
	if (!music.openFromFile("assets\\music\\Boo! sound effect.mp3")
		|| !texture.loadFromFile("assets\\backround\\draw_texture_transparent.png")) {
		std::exit(1);
	}
	music.setVolume(100.f);
	music.play();
	//
	sf::Vector2u texSize = texture.getSize(),winSize = window.getSize();  
	//
	sf::Sprite sprite{ texture };
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	//
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
//dealloc properly all textures that do not load properly
