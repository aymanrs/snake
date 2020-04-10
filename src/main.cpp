#include <SFML/Graphics.hpp>
#include <vector>

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
	unsigned int x;
	unsigned int y;
};

int main(){
	sf::RenderWindow app;
	app.create(sf::VideoMode(COLUMNS * (CASE_SIDE + BORDER_WIDTH), ROWS * (CASE_SIDE + BORDER_WIDTH)), "Snake");
	Direction snakeDirection = Direction::UP;
	std::vector<Case> body(1, Case{COLUMNS / 2, ROWS / 2});
	sf::Event event;
	while(app.isOpen()){
		while(app.pollEvent(event)){
			switch(event.type){
			case sf::Event::Closed:
				app.close();
				return 0;
			default:
				break;
			}
		}
	}
}
