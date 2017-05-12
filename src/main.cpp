#include <iostream>

#include "Chopsticks.h"
#include "human.h"

int main() {
	Chopsticks game(Human::move, Human::move);
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
