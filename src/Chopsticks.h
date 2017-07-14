#ifndef CHOPSTICKS_H
#define CHOPSTICKS_H

#include <functional>
#include <variant>

class Chopsticks {
public:

	struct Hand {
		int fingers = 1;
		bool is_dead() const;
		void hit(Hand &other);
		bool operator==(const Hand &rhs) const;
	};

	struct Player {
		Hand left;
		Hand right;
		bool is_dead() const;
		bool operator==(const Player &rhs) const;
	};

	enum class Winner {
		P1,
		P2,
		NONE
	};

	using State = std::pair<Player, Player>;

	struct Combination {
		int l_f;
		int r_f;
	};

	struct Hit {
		std::string src;
		std::string dst;
	};

	using Move = std::variant<Combination, Hit>;
	
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
