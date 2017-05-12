#ifndef CHOPSTICKS_H
#define CHOPSTICKS_H

#include <functional>

class Chopsticks {
public:

	struct Hand {
		int fingers = 1;
		bool is_dead() const;
		void hit(Hand &other);
	};

	struct Player {
		Hand left;
		Hand right;
		bool is_dead() const;
	};

	enum class Winner {
		P1,
		P2,
		NONE
	};

	using State = std::pair<Player, Player>;

	Chopsticks(std::function<State(Player, Player)> p1, std::function<State(Player, Player)> p2);

	void update();
	
	Winner get_winner() const;
private:
	Player _p1;
	Player _p2;

	std::function<State(Player, Player)> _p1_move;
	std::function<State(Player, Player)> _p2_move;

	enum class Turn {
		P1,
		P2
	} _turn = Turn::P1;

	Winner _winner = Winner::NONE;
};

#endif
