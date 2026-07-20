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
	//textures,fonts
	sf::Texture _backround{};
	sf::Font font{};
	//load them from those file paths
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")
		|| !_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")) {
		std::exit(1);
	}
	//this message is in utf-8 the L understands far more than simple ascii characters
	sf::String message =
		L"To make the huffman tree is simple:"
		L"First you take all possibilities and sort them by increasing order(if two possibilities\n)"
		L"have the same chance the order doesn't matter the real algo uses a priority queue"
		L" take the two smallest possibilities\nand merge them(take the sum of their possibilities).Take the new possibility and then"
		L" put it with the others and re-sort\nand then do the same.Stop when there is only one tree.I read sedgewick book,the figure he shows,puts the merged\npossibilities wherever he wants in the sorted order"
		L". I also asked chat gpt and gemini pro.They said the same."
		L"In the e\nnd sort,take the two mins and then re-sort and then continue until there is only one tree left.";
	//sprite
	sf::Sprite backround{ _backround };
	//texts
	sf::Text text_title{ font,"HUFFMAN TREE EXPLANATION:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });text_title.setFillColor(sf::Color::Black);//color of the text
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);//and give thickness to the outline
	//
	text_rules.setFillColor(sf::Color::Black);text_rules.setPosition({ 250.f,120.f });
	text_rules.setOutlineColor(sf::Color::White);text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });text_tap.setFillColor(sf::Color::Black);
	text_tap.setOutlineColor(sf::Color::White);text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//again make the backround to have the same size as the window
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {//capture all events
			if (event->is<sf::Event::MouseButtonPressed>()) {//mouse button pressed
				return;
			}
			else if (event->is<sf::Event::Closed>()) {//event that will close the window like alt-f4
				//exit
				window.close();
				return;
			}

		}
		//this loop runs every frame
		window.clear();
		window.draw(backround);
		window.draw(text_title);
		window.draw(text_rules);
		window.draw(text_tap);
		window.display();
	}
}
//change_textures function
//Note that texture is->brief Image living on the graphics card that can be used for drawing
//Note that sprite is->Drawable representation of a texture, with its
//own transformations, color, etc. pretty much sprite is the pointer to the texture
inline std::size_t change_textures(sf::RenderWindow& window) {
	//textures
	sf::Texture _backround{},_classic_cards{},_vintage_cards{};
	sf::Font font{};
	//font used for texts on the window
	//load them,those are the files paths,if a single texture is not loaded properly exit->1
	if (!_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg")//backround
		|| !_classic_cards.loadFromFile("assets\\playing-cards-pack - Copy\\PNG1\\card_clubs_03.png")//classic cards texture
		|| !_vintage_cards.loadFromFile("assets\\playing-cards-pack - Copy\\PNG2\\card_clubs_03.png")//vintage cards texture
		|| !font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")) {//font
		std::exit(1);
	}
	//sprites from the textures you loaded
	sf::Sprite classic_cards{ _classic_cards }, vintage_cards{ _vintage_cards }, backround{ _backround };
	//texts
	sf::Text text_title{ font,"  CLICK TO CHOOSE THE TEXTURE THAT YOU WANT:",80 }, text_classic{ font,"CLASSIC:",80 }
	, text_vintage{ font,"VINTAGE:",80 };
	//those are texts and we apply them some properties
	text_title.setFillColor(sf::Color::Black);text_title.setPosition({ 0.f,20.f });//2d position at the window
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);//creates the outline layer pretty much,outline must have a thickness in order
	//to appear
	//we do the same for the other texts
	text_classic.setFillColor(sf::Color::Black);text_classic.setPosition({ 460.f,320.f });
	text_classic.setOutlineColor(sf::Color::White);text_classic.setOutlineThickness(5.f);
	//
	text_vintage.setFillColor(sf::Color::Black);text_vintage.setPosition({ 1050.f,320.f });
	text_vintage.setOutlineColor(sf::Color::White);text_vintage.setOutlineThickness(5.f);
	//classic-> 640x640 default,height
	//vintage -> 450x600 default,width,height
	//every sprite has some widthxheight in pixels
	//the set scale takes two args and both are applied like this 
	//new sprite dimensions are (widthx10)x(heightx10)
	//we can change the sprites dimension to make it appear bigger or smaller
	classic_cards.setScale({ 10.f,10.f });classic_cards.setPosition({ 300.f,400.f });vintage_cards.setPosition({ 1000.f,420.f });
	vintage_cards.setScale({ 450.f / vintage_cards.getLocalBounds().size.x,600.f / vintage_cards.getLocalBounds().size.y });
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });
	//window.getSize() gives the dimensions of the window 
	//in this setScale call we wanna make the backround as big as the window in order to do that
	//we make the division with the window x,y cords and the local bounds cords in order to properly scale the backround to be the size of the window.
	//Note that localBounds=width and height of the texture originaly ,the scaling doesn't affect local bounds
	//it only affects globalBounds
	while (window.isOpen()) {//this loop runs for every frame
		while (const auto event = window.pollEvent()) {//we parse here all the events happened to the window
			if (event->is<sf::Event::Closed>()) {//an event that will close our window
				window.close();
				return 0;
			}
			else if (event->is<sf::Event::MouseButtonPressed>()) {//this is not limited to only left right click
				//of the mouse
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };//take where the mouse is at the window
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				//check collision with classic_cards sprite or vintage_cards sprite
				if (classic_cards.getGlobalBounds().contains(world_pos)) {//this is not exactly perfect collision
					return 0;//sometimes because of the texture the collision may not be perfect 
				}
				else if (vintage_cards.getGlobalBounds().contains(world_pos)) {
					return 1;
				}
			}
		}
		//this is the frame
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
//load_file_paths function
//Note that the choice->is the choice of the user we got from the menu
inline void load_file_paths(std::vector<std::string>& file_paths, const std::size_t choice) {
	//keep file paths to load the textures later
	file_paths.reserve(52);
	//reserve space for 52 cards
	std::vector<std::string>table{ "02","03","04","05","06","07","08","09","10","J","K","Q","A" };
	//look up table
	//the deck is 52 cards-> 4 suits of 13 cards
	//every suit contains 2,3,4,5,6,7,8,9,10,A,J,K,Q
	//PNG1 for classic cards,PNG2 for vintage cards
	std::string png_number=choice==0?"PNG1":"PNG2";
	//create the file paths vector
	for (std::size_t i = 0; i < table.size(); i++) {
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_clubs_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_diamonds_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_hearts_" + table[i] + ".png");
		file_paths.emplace_back("assets\\playing-cards-pack - Copy\\" + png_number + "\\card_spades_" + table[i] + ".png");
	}
	
}
//simply explains the rules of the game
//Note that the sprites are placed by their top left corner in the position given to them 
//in order to change that and make them placed from the middle in the position given to them 
//we change the origin of them to be (width/2)x(height/2)
//the default origin of a sprite is the top left corner(change that with setOrigin function)
inline void tutorial_of_the_game(sf::RenderWindow& window) {
	//textures,fonts
	sf::Texture _backround{};
	sf::Font font{};
	//load them from those file paths
	if (!font.openFromFile("C:\\Windows\\Fonts\\segoeui.ttf")//font
		|| !_backround.loadFromFile("assets\\backround\\360_F_267103158_QTPpB2GxYh8RZBL4X9XL42SM7jiZ5yXL.jpg"))//backround
	{
		std::exit(1);
	}
	//this message is in utf-8 the L understands far more than simple ascii characters
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
	//sprite
	sf::Sprite backround{ _backround };
	//texts
	sf::Text text_title{ font,"RULES OF THE GAME:",100 }, text_rules{ font,message,30 }, text_tap{ font,"TAP ANYWHERE",100 };
	//
	text_title.setPosition({ 930.f,20.f });text_title.setFillColor(sf::Color::Black);//color of the text
	text_title.setOrigin({ text_title.getLocalBounds().size.x / 2.f,text_title.getLocalBounds().size.y / 2.f });
	//set origin simply makes them be placed by the middle
	//the set origin funtion ignores all transformation scaling etc of the sprite 
	text_title.setOutlineColor(sf::Color::White);text_title.setOutlineThickness(5.f);
	//
	text_rules.setFillColor(sf::Color::Black);text_rules.setPosition({ 370.f,120.f });text_rules.setOutlineColor(sf::Color::White);
	text_rules.setOutlineThickness(5.f);
	//
	text_tap.setPosition({ 1200.f,970.f });text_tap.setFillColor(sf::Color::Black);text_tap.setOutlineColor(sf::Color::White);
	text_tap.setOutlineThickness(10.f);
	//
	backround.setScale({ window.getSize().x / backround.getLocalBounds().size.x,window.getSize().y / backround.getLocalBounds().size.y });//we wanna mek the
	//backround the size of our window whick is the same as the desktop width and height,getSize().x gives the width,getSize().y gives the height
	//again make the backround to have the same size as the window
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {//capture all events
			if (event->is<sf::Event::MouseButtonPressed>()) {//mouse button pressed
				return;//return back to the menu
			}
			else if (event->is<sf::Event::Closed>()) {//event happened that will close the window like alt-f4
				//close window
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
	//textures must contain 52 textures like the 52 cards because the deck will contain 52 sprites
	for (std::size_t i = 0; i < file_paths.size(); i++) {
		if (!textures[i].loadFromFile(file_paths[i])) {//if the texture is not loaded exit->1
			std::exit(1);//someday make the textures deallocate when something fails to load
		}
		//make name will have the following format=>card_symbol_num.png 
		std::string name=file_paths[i].substr(file_paths[i].find_last_of('\\')+1);
		name = std::string{ name.begin(),name.begin() + name.find('.') };
		//by the end of this name->card_symbol_num,we do this in order to parse the symbol and num later
		deck.emplace_back(std::move(name), textures[i]);//every name has a sprite on it
		//we have 52 unique names and cards set on them
	}
}

//menu function
inline void menu(sf::RenderWindow& window, std::size_t& choice) {
	//chance for the easter egg 1/1000 chance
	std::random_device rd{};
	std::mt19937 gen(rd());
	std::bernoulli_distribution chance(1.0 / 1000.0);//create the 1/1000 chance for the huffman button to appear to happen
	bool flag = chance(gen);//if true
	//music,textures,font's
	sf::Music music, jumpscare_music{};
	sf::Texture _start{}, _tutorial{}, _exit{}, _github{}, _backround{}, _music_on{}, _music_off{}, _change_texture{},_jumpscare{}
	, _huffman_button{}, _reset_score{};
	sf::Font font{};//a text needs a font in order to draw it on screen
	//
	if (!music.openFromFile("assets\\music\\WhiteNoiz.mp3")
		|| !_start.loadFromFile("assets\\buttons\\LeftCutBlue.png")
		|| !_tutorial.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")
		|| !_change_texture.loadFromFile("assets\\buttons\\LeftCutFlameBlue.png")//button
		|| !_exit.loadFromFile("assets\\buttons\\LeftCutIce.png")
		|| !_github.loadFromFile("assets\\github-mark\\github-mark-white.png")//github logo
		|| !_backround.loadFromFile("assets\\backround\\dealer beauty.jpg")//backround of the menu
		|| !_music_on.loadFromFile("assets\\png-icons\\music_on.png")//music icon on
		|| !_music_off.loadFromFile("assets\\png-icons\\music_off.png")//music icon off
		|| !font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")//font
		|| !_jumpscare.loadFromFile("assets\\backround\\68747470733a2f2f692e7974696d672e636f6d2f76692f524e6f48635745387462512f6d617872657364656661756c742e6a7067.jpg")//jumpscare icon
		|| !jumpscare_music.openFromFile("assets\\music\\712416__zombyklr__jumpscare-1.mp3")//jumpscare music
		|| !_huffman_button.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")//button
		|| !_reset_score.loadFromFile("assets\\buttons\\LeftCutFlameRed.png")//button
		) {
		std::exit(1);//exit if a texture fails to load
	}
	//sprite for every texture we loaded
	sf::Sprite start{ _start }, tutorial{ _tutorial }, exit{ _exit }, github{ _github }, backround{ _backround }
		, music_on{ _music_on }, music_off{ _music_off }, change_texture{ _change_texture }, jumpscare{ _jumpscare }
	, huffman_button{ _huffman_button }, reset_score{ _reset_score };
	sf::Clock timer{};//timer because in a certain time we want the jumpscare to appear
	//music of the menu will loop,and it will start playing on loop with the play function
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
	//place the jumpscare when a certain time has passed
	bool event{ false };//for the jumpscare because it appears one time only
	while (window.isOpen()) {//while the window is open and not closed
		//reset timer of the jumpscare if the user does something to the menu
		//remember the jumpscare is actived if the user stays on the menu and doesn't do anything 
		//for 360 seconds,if in those seconds he does something then the time resets to 0
		while (const auto event = window.pollEvent()) {//this lines takes all the events happening to the window
			if (event->is < sf::Event::MouseButtonPressed>()) {//click event,take the position of the mouse and check if the user tapped a texture
				//take mouse pos 
				sf::Vector2i mous_pos{ sf::Mouse::getPosition(window) };
				sf::Vector2f world_pos{ window.mapPixelToCoords(mous_pos) };
				//check for collision with global bounds
				if (start.getGlobalBounds().contains(world_pos)) {
					//start
					return;
				}
				//if for some reason the window closes the game ends
				else if (tutorial.getGlobalBounds().contains(world_pos)) {
					tutorial_of_the_game(window);timer.restart();
					if (!window.isOpen())return;//an event happened that closed the window
				}
				else if (exit.getGlobalBounds().contains(world_pos)) {
					//exit
					window.close();
					return;
				}
				else if (change_texture.getGlobalBounds().contains(world_pos)) {
					//this is where the user gives his choice about what sprite of the cards he wants to see in the main game
					choice = change_textures(window);timer.restart();
					if (!window.isOpen())return;
				}
				else if (github.getGlobalBounds().contains(world_pos)) {
					//open github
					system("start https://github.com/Paltoudara?tab=repositories");timer.restart();
				}
				//music icon to handle
				else if (music_on.getGlobalBounds().contains(world_pos)) {
					//when we tap the music if it off make it play
					//if it is on make it stop playing
					if (music.getStatus() == sf::SoundSource::Status::Playing)music.stop();
					else music.play();
					timer.restart();
				}
				else if (flag==true && huffman_button.getGlobalBounds().contains(world_pos)) {
					//if we got the 1/1000 show the button and accept clicks on it
					huffman_tree_explanation(window);timer.restart();
					if (!window.isOpen())return;
				}
				else if (reset_score.getGlobalBounds().contains(world_pos)) {
					//tapped the reset score button so change the score file
					std::ofstream score_file("score.txt");
					if (!score_file.is_open()) { std::exit(1); }
					score_file << "0\n";score_file << "0";score_file.close();
					//reset the file that contains the scores of the two players,recreate it and put 0's
				}
			}
			else if (event->is<sf::Event::Closed>()) {//an event happened that will close the window like alt+f4
				//close the window
				window.close();
				return;
			}
		}
		//this is the frame,this below runs every frame
		window.clear();
		if (!event && timer.getElapsedTime().asSeconds() >= 360.f) {//6x60 d
			//if event happends draw it and the jumpscare
			music.stop();//stop the music currently playing
			event = true;//the jumpscare will happend and it will not happen again
			window.draw(jumpscare);window.display();
			jumpscare_music.setVolume(100.f);jumpscare_music.play();
			sf::sleep(sf::seconds(2.0));
			music.play();

		}
		else {
			//if event didn't happend draw everything that the menu has 
			//from the textures we have loaded
			window.draw(backround);window.draw(start);window.draw(tutorial);window.draw(exit);window.draw(github);
			//if music is playing draw icon that it is on 
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
