#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>

#include "Coin.h"
#include "EnemyBat.h"

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class Player {

public:

	float down, left, right, up;
	int _score, _life;
	Player() {}

	Player(string player, RenderWindow &window)
	{
		score = 0;
		_score = 0;
		life = 3;
		if (!playerTexture.loadFromFile(player)) {
			cerr << "ERROR" << endl;
		}
		playerTexture.setSmooth(true);
		playerSprite.setScale(0.1, 0.1);
		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

		// Sprite initial position
		playerSprite.setTextureRect(IntRect(1000, 0, 1000, 1000));
	}

	void drawPlayer(RenderWindow &window) {
		window.draw(playerSprite);
	}
#pragma region Understand Animation of the Sprite

	/* Well, I'll explain quickly, what I do is, how do I get the animation from the character direction?, everything happens when and <1000,
	   the only thing that changes is the value of x, that's why I multiply it by a counter, so that it moves to the right, and then when
	   it would arrive at the end, that counter will set it to 0 so it starts again.  */

#pragma endregion

	void move(Time time, Clock clock) {
		_time = time;
		_clock = clock;
		_time = clock.getElapsedTime();

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			playerSprite.move(0, movPlayer * _time.asMilliseconds());
			playerSprite.setTextureRect(IntRect(1000 * spriteX, 0, 1000, 1000));

		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			playerSprite.move(0, -movPlayer * _time.asMilliseconds());
			playerSprite.setTextureRect(IntRect(1000 * spriteX, 1000, 1000, 1000));
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			playerSprite.move(movPlayer *_time.asMilliseconds(), 0);
			playerSprite.setTextureRect(IntRect(1000 * spriteX, 2000, 1000, 1000));

		}
		else if (Keyboard::isKeyPressed(Keyboard::Left)) {
			playerSprite.move(-movPlayer * _time.asMilliseconds(), 0);
			playerSprite.setTextureRect(IntRect(1000 * spriteX, 3000, 1000, 1000));


		}
		spriteX++;

		if (spriteX == 3) {
			spriteX = 0;
		}
		_clock.restart().asMilliseconds();
	}

	void getPlayer() {
		down = playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height*0.90);
		left = playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width*0.25);
		right = playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width *0.75);
		up = playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height*0.25);
	}
#pragma region Values of the player

	// pSprite.getPosition().x + (pSprite.getGlobalBounds().width / 4) esto me da la parte izquierda del personaje o lo mismo que multiplicar el tama�o por 0.25
	// pSprite.getPosition().x + (pSprite.getGlobalBounds().width *0.75 esto me da la parte derecha del personaje 
	// pSprite.getPosition().y + (pSprite.getGlobalBounds().height*0.25) esto me da la parte de arriba del personaje (a partir del casco)
	// pSprite.getPosition().y + (pSprite.getGlobalBounds().height*0.90) esto me da la parte de abajo del personaje

#pragma endregion



	bool CollisionCoin(Coin coin) {

		if (right < coin.left || left > coin.right ||
			up > coin.down || down < coin.up) {
			return false;
		}
		else {
			score++;
			_score = score;
			return true;
		}
	}

	bool CollisionBat(Bat enemyBat) {
		_life = life;
		if (right < enemyBat.left || left > enemyBat.right ||
			up > enemyBat.down || down < enemyBat.up) {
			return false;
		}
		else {
			life--;
			return true;
		}
	}
	void changePositionAfterCollisionWithEnemy(RenderWindow &window) {
		playerSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	}
private:
	Texture playerTexture;
	Sprite	playerSprite;
	Time _time;
	Clock _clock;

	int life;
	int score;
	int spriteX = 0;
	float movPlayer = 0.099;

};
