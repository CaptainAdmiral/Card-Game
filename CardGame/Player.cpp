#include "Player.h"

Player::Player() {

}
Player::Player(int r, int g, int b) {
	color = std::make_tuple(r, g, b);

}
Player::~Player() {}

void Player::setColor(int r, int g, int b) {
	color = std::make_tuple(r, g, b);
}

std::tuple<int, int, int> Player::getColor() {
	return color;
}

void Player::draw() {
	deck.giveCardTo(hand);
}

void Player::draw(int amount) {
	for (int i = 0; i < amount; i++) {
		draw();
	}
}

void Player::setVisible(bool vis) {
	hand.setVisible(vis);
	for(CardPtr& card : hand.contents) {
		card->setVisible(vis);
	}
}