#include <iostream>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;


int main() {

	int score = 0;
	int gridOffset = 64;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 9);

	sf::Font font;
	if (!font.loadFromFile("assets/AnkaCoder-b.ttf")) {
		return 1;
	}

	bool selection = false;
	bool calculate = false;
	std::vector<sf::Vector2i> selectedCells;
	sf::Vector2i currentCell;

	sf::Texture textureCell;
	sf::Sprite spriteCell;
	sf::Texture textureSelection;
	sf::Sprite spriteSelection;
	sf::Text text;
	text.setFont(font);
	text.setString("1");

	textureCell.loadFromFile("./assets/Red.png");
	textureSelection.loadFromFile("./assets/Selection.png");
	spriteCell.setTexture(textureCell);
	spriteSelection.setTexture(textureSelection);

	short grid[10][10];
	for (int y = 0; y < 10; ++y) {
		for (int x = 0; x < 10; ++x) {
			grid[y][x] = (short) distribution(generator);
		}
	}

	sf::RenderWindow window(sf::VideoMode(788, 788), "CalcMatch");
	window.setFramerateLimit(30);
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Left:
							currentCell.x -= 1;
							break;
						case sf::Keyboard::Right:
							currentCell.x += 1;
							break;
						case sf::Keyboard::Up:
							currentCell.y -= 1;
							break;
						case sf::Keyboard::Down:
							currentCell.y += 1;
							break;
						case sf::Keyboard::Space:
							selection = true;
							break;
					}
					break;
				case sf::Event::KeyReleased:
					switch (event.key.code) {
						case sf::Keyboard::Space:
							selection = false;
							calculate = true;
							break;
					}
					break;
			}
		}

		if (calculate) {
			int result = 0;
			for (auto cell : selectedCells) {
				result += grid[cell.y][cell.x];
			}

			if (result == 10) {
				score += 100 - (selectedCells.size() * 10);
			}

			for (auto cell : selectedCells) {
				grid[cell.y][cell.x] = (short) distribution(generator);
			}

			calculate = false;
			selectedCells.clear();
		}

		if (selection) {
			auto found = false;
			for (auto cell : selectedCells) {
				if (cell.x == currentCell.x &&
					cell.y == currentCell.y) {
					found = true;
					break;
				}
			}
			if (!found) {
				selectedCells.push_back(sf::Vector2i(currentCell.x, currentCell.y));
			}
		}

		window.clear(sf::Color::Black);

		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				spriteCell.setPosition(x * 64 + gridOffset, y * 64 + gridOffset);
				text.setPosition(x * 64 + gridOffset, y * 64 + gridOffset);
				text.setString(std::to_string(grid[y][x]));

				window.draw(spriteCell);
				window.draw(text);

				if (currentCell.x == x &&
					currentCell.y == y) {
					spriteSelection.setPosition(x * 64 + gridOffset, y * 64 + gridOffset);
					window.draw(spriteSelection);
				}
			}
		}

		for (int i = 0; i < selectedCells.size(); ++i) {
			spriteSelection.setPosition(selectedCells[i].x * 64 + gridOffset, selectedCells[i].y * 64 + gridOffset);
			window.draw(spriteSelection);
		}

		text.setPosition(0, 0);
		text.setString("Score: " + std::to_string(score));
		window.draw(text);

		window.display();
	}

	return 0;
}
