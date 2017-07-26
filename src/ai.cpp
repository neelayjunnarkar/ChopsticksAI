#include "ai.h"
#include <iostream>

namespace AI {

// Scores range from 0 to 9, higher is better
// Score of 9 means Player p has won
// Score of 0 means Player p has lost
// Scores range from 0 to 9, higher is better
float score(const Chopsticks::Player &p, const Chopsticks::Player &other) {
	if (other.left.fingers + other.right.fingers == 0)
		return 9.0;
	return ((float)(p.left.fingers + p.right.fingers)) / ((float)(other.left.fingers + other.right.fingers));
}

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

const std::array<Chopsticks::Hit, 4> hits {{{"l", "l"}, {"l", "r"}, {"r", "l"}, {"r", "r"}}};

// Modifies inputted players
bool handle_hit(Chopsticks::Player &p, Chopsticks::Player &other, const Chopsticks::Hit &hit) {
	if (hit.src == "l") { // Lefthand attack
		if (p.left.is_dead())
			return false;
		if (hit.dst == "l") { // Lefthand victim
			if (other.left.is_dead())
				return false;
			p.left.hit(other.left);
		} else if (hit.dst == "r") { // Righthand victim
			if (other.right.is_dead())
				return false;
			p.left.hit(other.right);
		} else { // Bad input
			return false;
		}
		return true;
	} else if (hit.src == "r") { // Righthand attack
		if (p.right.is_dead())
			return false;
		if (hit.dst == "l") { // Lefthand victim
			if (other.left.is_dead())
				return false;
			p.right.hit(other.left);
		} else if (hit.dst == "r") { // Righthand victim // Lefthand victim
			if (other.right.is_dead())
				return false;
			p.right.hit(other.right);
		} else { // Bad input
			return false;
		}
		return true;
	} else { // Bad input
		return false;
	}

}

// Assumes combo command is valid <- need to change
bool handle_combine(Chopsticks::Player &p, const Chopsticks::Combination &combo) {
	p.left.fingers = combo.l_f;
	p.right.fingers = combo.r_f;
	return true;
}


std::optional<float> move_backend(Chopsticks::Player p, Chopsticks::Player other, int depth, int depth_max, Chopsticks::Move move) {
	// Execute move
	bool bad_move = false;
	std::visit(overloaded {
		[&](Chopsticks::Hit hit) {
			if (!handle_hit(p, other, hit))
				bad_move = true;
		},
		[&](Chopsticks::Combination combo) {
			if (!handle_combine(p, combo))
				bad_move = true;
		} 
	}, move);

	if (bad_move) {
		return {};
	}

	if (depth == depth_max) {
		if (depth % 2 == 1) { // p is original player
			return score(p, other);
		} else { // other is original player
			return score(other, p);
		}
	}

	if (depth % 2 == 1) { // p is original player
		// maximize score of all sub moves
		++depth;
		float max = -1;
		for (const auto &hit : hits) {
			float val = move_backend(other, p, depth, depth_max, hit).value_or(-1);
			if (val > max) {
				max = val;
			}
		}
	//	std::cout << "max: " << max << "\n";
		return max;
	} else { // other is original player
		// minimize score 
		++depth;
		float min = 1000; // score max should be 9
		for (const auto &hit : hits) {
			float val = move_backend(other, p, depth, depth_max, hit).value_or(1000);
			if (val < min) {
				min = val;
			}
		}
	//	std::cout << "min: " << min << "\n";
		return min;
	}
	
}

Chopsticks::State move(Chopsticks::Player p, Chopsticks::Player other) {
	const int depth_max = 5;	
	std::pair<Chopsticks::Move, float> best_move; // <move, score>
	best_move.first = hits[0];
	best_move.second = move_backend(p, other, 1, depth_max, best_move.first).value_or(-1);
	for (int i = 1; i < hits.size(); ++i) {
		float val = move_backend(p, other, 1, depth_max, hits[i]).value_or(-1);
		if (val > best_move.second) {
			best_move.second = val;
			best_move.first = hits[i];
		}
	}
	std::visit(overloaded {
		[&](Chopsticks::Hit hit) {
			handle_hit(p, other, hit);	
		},
		[&](Chopsticks::Combination combo) {
			handle_combine(p, combo);
		} 
	}, best_move.first);

	return std::make_pair(p, other);	
}

}
