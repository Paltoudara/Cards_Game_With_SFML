#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<cstdlib>
//pause_menu=>Is a classic pause menu with 3 buttons.1 for resume(to return to the main game),2 for quit game,3 for the score
//(this one is not interactable,it just displays the scores of the two players).
inline void pause_menu(sf::RenderWindow& window) {
	//textures for the 3 buttons and the backround
	sf::Texture _resume{}, _quit_game{}, _backround{}, _score{};
	//font for texts
	sf::Font font{};
	std::size_t score_p1{}, score_p2{};
	//load the textures for the 3 buttons,the backround and load the font for the texts
	//if something fails to load close the window
	if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")
		|| !_resume.loadFromFile("assets\\buttons\\LeftCutBlue.png")
		|| !_quit_game.loadFromFile("assets\\buttons\\LeftCutIce.png")
		|| !_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")
		|| !_score.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")
		) {
		window.close();
		return;
	}
	//
	std::ifstream file("score.txt");
	if (!file.is_open()) { std::cout << "failed to open the score.txt file\n";std::exit(1); }
	//read the scores from the score.txt and display them in the score sprite
	file >> score_p1;
	file >> score_p2;
	file.close();
	//sprites for the 3 buttons and the backround
	sf::Sprite resume{ _resume }, quit_game{ _quit_game }, backround{ _backround }, score{ _score };
	//text for the 3 buttons
	sf::Text text_resume{ font,"resume",30 }, text_quit_game{ font,"quit_game",30 }, text_score{ font,
		"p1:" + std::to_string(score_p1) + "   ,   p2:" + std::to_string(score_p2),30 };
	//place the buttons on the screen properly and change their attributes for proper appearance
	resume.setPosition({ 960.f,540.f });
	resume.setOrigin({ resume.getLocalBounds().size.x / 2.f,resume.getLocalBounds().size.y / 2.f });
	resume.setScale({ 1 / 4.f,1 / 4.f });
	//
	quit_game.setPosition({ 960.f,650.f });
	quit_game.setOrigin({ quit_game.getLocalBounds().size.x / 2.f,quit_game.getLocalBounds().size.y / 2.f });
	quit_game.setScale({ 1 / 4.f,1 / 4.f });
	//
	score.setScale({ 1 / 4.f, 1 / 3.0f });
	score.setPosition({ 960.f,440.f });
	score.setOrigin({ score.getLocalBounds().size.x / 2.f,score.getLocalBounds().size.y / 2.f });
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//
	text_resume.setPosition({ 970.f,530.f });
	text_resume.setOrigin({ text_resume.getLocalBounds().size.x / 2.f,text_resume.getLocalBounds().size.y / 2.f });
	//
	text_quit_game.setPosition({ 970.f,640.f });
	text_quit_game.setOrigin({ text_quit_game.getLocalBounds().size.x / 2.f,text_quit_game.getLocalBounds().size.y / 2.f });
	//
	text_score.setPosition({ 970.f,430.f });
	text_score.setOrigin({ text_score.getLocalBounds().size.x / 2.f,text_score.getLocalBounds().size.y / 2.f });
	//
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			//take the mouse coords and check if a mouse button is pressed and also check if a collision with the two active 
			//buttons happened
			sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
			sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
			if (event->is<sf::Event::MouseButtonPressed>()) {
				if (resume.getGlobalBounds().contains(world_pos)) {
					return;
				}
				else  if (quit_game.getGlobalBounds().contains(world_pos)) {
					window.close();
					return;
				}
			}
			else if (event->is<sf::Event::Closed>()) {
				window.close();
				return;
			}
		}
		window.clear();
		window.draw(backround);
		window.draw(resume);
		window.draw(quit_game);
		window.draw(text_resume);
		window.draw(text_quit_game);
		window.draw(score);
		window.draw(text_score);
		window.display();
	}
}
