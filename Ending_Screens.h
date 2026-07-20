#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<SFML/Audio.hpp>
#include<cstdlib>

inline void winner(sf::RenderWindow& window, const bool flag_winner) {
	//
	sf::Music music{};
	//
	std::size_t score_1{}, score_2{};
	//
	std::fstream file("score.txt", std::ios::in | std::ios::out);
	//
	sf::Texture texture{};
	//
	if (!music.openFromFile("assets\\music\\Clapping , Cheering & Applause - NO Copyright - Free Sound Effects.mp3"))
	{
		std::exit(1);
	}
	//
	if (!file.is_open()) { std::cout << "failed to open the file score.txt"; std::exit(1); }
	file >> score_1 >> score_2;
	file.seekg(0, std::ios::beg);
	//
	music.setVolume(100.f);music.play();
	//
	if (flag_winner == true && !texture.loadFromFile("assets\\backround\\player1.png")) { std::exit(1); }
	else if (flag_winner == false && !texture.loadFromFile("assets\\backround\\player2.png")) { std::exit(1); }
	if (flag_winner == true) { score_1++; }
	else if (flag_winner == false) { score_2++; }
	file << score_1 << "\n";
	file << score_2;
	file.close();
	//
	sf::Vector2u texSize = texture.getSize();  
	sf::Vector2u winSize = window.getSize();     
	//
	sf::Sprite sprite(texture);
	sprite.setScale({ static_cast<float>(winSize.x) / texSize.x,static_cast<float>(winSize.y) / texSize.y });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();window.draw(sprite);window.display();
	}
}
//
inline void draw(sf::RenderWindow& window) {
	//music,texture
	sf::Texture texture{};
	sf::Music music{};
	//load them
	if (!music.openFromFile("assets\\music\\Boo! sound effect.mp3")
		|| !texture.loadFromFile("assets\\backround\\draw_texture_transparent.png")) {
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
	//this works the same if we took also the local bounds from the value sprite
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
