#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>

#define COLUMNS 20
#define ROWS 20
#define CASE_SIDE 30
#define BORDER_WIDTH 2

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct Case
{
	int x;
	int y;
};

bool operator ==(Case a, Case b) { return a.x == b.x && a.y == b.y; }

int main(){
	sf::RenderWindow app;
	app.create(sf::VideoMode(COLUMNS * (CASE_SIDE + BORDER_WIDTH), ROWS * (CASE_SIDE + BORDER_WIDTH)), "Snake");
launch:
	Direction snakeDirection = Direction::UP;
	std::vector<Case> body(1, Case{COLUMNS / 2, ROWS / 2});
	std::mt19937 rng(time(NULL));
	int score = 0;
	bool add = false;
	Case apple{(int)(rng() % COLUMNS), (int)(rng() % ROWS)}, anc;
	while(apple == body[0]) apple = Case{(int)(rng() % COLUMNS), (int)(rng() % ROWS)};
	sf::Font ubuntuFont;
	if(!ubuntuFont.loadFromFile("res/Ubuntu-Regular.ttf")){
		app.close();
		return 0;
	}
	sf::Text displayScore("0",ubuntuFont, 18);
	displayScore.setFillColor(sf::Color::Black);
	sf::Event event;
	sf::RectangleShape displayCase;
	displayCase.setSize(sf::Vector2f(CASE_SIDE, CASE_SIDE));
	displayCase.setOutlineThickness(BORDER_WIDTH);
	displayCase.setOutlineColor(sf::Color::Black);
	sf::Clock clock;
	while(app.isOpen()){
		while(app.pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				app.close();
				return 0;
			case sf::Event::KeyPressed:
				switch(event.key.code){
				case sf::Keyboard::Up:
					snakeDirection = Direction::UP;
					break;
				case sf::Keyboard::Down:
					snakeDirection = Direction::DOWN;
					break;
				case sf::Keyboard::Left:
					snakeDirection = Direction::LEFT;
					break;
				case sf::Keyboard::Right:
					snakeDirection = Direction::RIGHT;
					break;
				case sf::Keyboard::Space:
					goto launch;
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		while(clock.getElapsedTime().asMilliseconds() < 160);
		clock.restart();
		app.clear(sf::Color::Black);
		if(body[0] == apple){
			score++;
			apple = Case{(int)(rng() % COLUMNS), (int)(rng() % ROWS)};
			while(std::find(body.begin(), body.end(), apple) != body.end()) apple = {(int)(rng() % COLUMNS), (int)(rng() % ROWS)};
			add = true;
			anc = body.back();
		}
		for(unsigned int i = body.size() - 1;i > 0;i--){
			body[i] = body[i-1];
		}
		if(add){
			add = false;
			body.push_back(anc);
		}
		switch(snakeDirection)
		{
		case Direction::UP:
			body[0].y--;
			break;
		case Direction::DOWN:
			body[0].y++;
			break;
		case Direction::LEFT:
			body[0].x--;
			break;
		case Direction::RIGHT:
			body[0].x++;
			break;
		}
		if(body[0].x < 0 || body[0].x >= COLUMNS || body[0].y < 0 || body[0].y >= ROWS || std::find(body.begin() + 1, body.end(), body[0]) != body.end()){
			while(true){
				if(app.waitEvent(event)){
					if(event.type == sf::Event::Closed){
						app.close();
						return 0;
					} else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) goto launch;
				}
			}
		}
		displayCase.setFillColor(sf::Color::White);
		for(int i = 0;i < COLUMNS;i++){
			for(int j = 0;j < ROWS;j++){
				displayCase.setPosition((CASE_SIDE + BORDER_WIDTH) * i, (CASE_SIDE + BORDER_WIDTH) * j);
				app.draw(displayCase);
			}
		}
		displayCase.setFillColor(sf::Color::Red);
		for(size_t i = 1;i < body.size();i++){
			displayCase.setPosition((CASE_SIDE + BORDER_WIDTH) * body[i].x, (CASE_SIDE + BORDER_WIDTH) * body[i].y);
			app.draw(displayCase);
		}
		displayCase.setPosition((CASE_SIDE + BORDER_WIDTH) * body[0].x, (CASE_SIDE + BORDER_WIDTH) * body[0].y);
		displayCase.setFillColor(sf::Color::Blue);
		app.draw(displayCase);
		displayCase.setPosition(apple.x * (CASE_SIDE + BORDER_WIDTH), apple.y * (CASE_SIDE + BORDER_WIDTH));
		displayCase.setFillColor(sf::Color::Green);
		app.draw(displayCase);
		displayScore.setString(std::to_string(score));
		app.draw(displayScore);
		app.display();
	}
}
