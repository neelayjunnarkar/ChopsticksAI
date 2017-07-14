#include <iostream>

#include "Chopsticks.h"
#include "human.h"
#include "ai.h"

int main() {
	Chopsticks game(Human::move, AI::move);
	while (game.get_winner() == Chopsticks::Winner::NONE) {
		game.update();
	}
	switch (game.get_winner()) {
		case Chopsticks::Winner::P1:
			std::cout << "Winner: P1\n";
		break;
		case Chopsticks::Winner::P2:
			std::cout << "Winner: P2\n";
		break;
		case Chopsticks::Winner::NONE:
			std::cout << "Winner: Something screwed up bad\n";
		break;
	}
}
