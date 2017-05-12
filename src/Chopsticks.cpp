#include "Chopsticks.h"
#include <iostream>

Chopsticks::Chopsticks(std::function<State(Player,Player)> p1, std::function<State(Player, Player)> p2):
	_p1_move{p1},
	_p2_move{p2}{

}

bool Chopsticks::Hand::is_dead() const {
	return fingers == 0; 
}

void Chopsticks::Hand::hit(Chopsticks::Hand &other) {
	other.fingers += fingers;
	if (other.fingers >= 5)
		other.fingers = 0;
}

bool Chopsticks::Player::is_dead() const {
	return left.is_dead() && right.is_dead();
}

Chopsticks::Winner Chopsticks::get_winner() const {
	return _winner;
}

void Chopsticks::update() {
	if (_winner != Winner::NONE)
		return;

	std::cout << "Player: (left, right)\n";
	std::cout << "P1: (" << _p1.left.fingers << ", " << _p1.right.fingers << ")\n";
	std::cout << "P2: (" << _p2.left.fingers << ", " << _p2.right.fingers << ")\n";

	if (_turn == Turn::P1) {
		std::tie(_p1, _p2) = _p1_move(_p1, _p2);
		_turn = Turn::P2;
	} else if (_turn == Turn::P2) {
		std::tie(_p2, _p1) = _p2_move(_p2, _p1);
		_turn = Turn::P1;
	}

	if (_p1.is_dead() && !_p2.is_dead()) {
		_winner = Winner::P2;		
	} else if (_p2.is_dead() && !_p1.is_dead()) {
		_winner = Winner::P1;
	}
}
