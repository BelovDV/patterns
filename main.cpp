#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using std::vector;

sf::Texture texture;
sf::Sprite sprite[8];
vector<std::pair<sf::Vector2i, int>> mas;
vector<sf::Sprite> pixels;

vector<vector<sf::Vector2i>> types =
{
	{{0, 1}, {1, 0}, {1, 1}, {2, 0}},
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}}
};

void move_down(sf::Clock& clock)
{
	int delta = 0;
	if (clock.getElapsedTime() > sf::milliseconds(4))
		delta = 1, clock.restart();
	static int speed = 1;
	for (auto& it : mas)
		it.first += sf::Vector2i(0, speed * delta);
	if (mas.size())
		if (mas[0].first.y > 480 || mas[0].first.y < 1)
		{
			speed *= -1;
			for (auto& it : mas)
				it.first += sf::Vector2i(0, 10 * speed * delta);
		}
}

void display(sf::RenderWindow& window)
{
	window.clear(sf::Color::White);

	pixels.clear();
	for (const auto& it : mas)
	{
		for (auto& i : types[it.second])
		{
			pixels.push_back(sprite[1]);
			pixels.back().move(sf::Vector2f(it.first + i * 18));
		}
	}

	for (const auto& it : pixels)
		window.draw(it);

	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 480), "The Game!");

	texture.loadFromFile("tiles.png");
	for (int i = 0; i != 8; ++i)
	{
		sprite[i] = sf::Sprite(texture);
		sprite[i].setTextureRect(sf::IntRect(i * 18, 0, 18, 18));
	}

	mas.push_back({ sf::Vector2i(10, 0), 0 });
	mas.push_back({ sf::Vector2i(100, 0), 1 });

	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		move_down(clock);
		display(window);
	}

	//system("pause");

	return 0;
}