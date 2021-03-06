#include "Game.hpp"
#include "GameState.hpp"

#include <iostream>



Game::Game(int width, int height, std::string title) {

	sf::Image icon;
	icon.loadFromFile("Resources/Images/topIcon.png");

	data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	//data->window.setVerticalSyncEnabled(true);
	//data->window.setFramerateLimit(60);

	data->window.setPosition(sf::Vector2i(500, 100));

	data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());



	srand((unsigned int)time(NULL));
		
	data->state = new GameState(data);

	this->run();
}

void Game::run() {

	float newTime, frameTime;

	float currentTime = this->clock.getElapsedTime().asSeconds();

	float accumulator = dt;


	while (this->data->window.isOpen()) {

		//Check state changes
		if (data->newState) {
			delete data->state;
			data->state = data->newState;
			data->newState = nullptr;
		}

		newTime = this->clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime;

		currentTime = newTime;

		if (frameTime > 0.15f) {
			frameTime = 0.15f;
		}

		accumulator += frameTime;

		while (accumulator >= dt) {

			this->data->state->handleInput();
			this->data->state->update(dt);

			this->data->state->draw();

			accumulator -= dt;
		}

	
	}


}


