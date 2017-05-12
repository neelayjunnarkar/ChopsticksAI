#include "human.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string_view>

namespace Human {

// Returns false if invalid hit input
// Modifies inputted players
bool handle_hit(Chopsticks::Player &p, Chopsticks::Player &other, const std::vector<std::string> &input) {
	if (input[1] == "l") { // Lefthand attack
		if (p.left.is_dead())
			return false;
		if (input[2] == "l") { // Lefthand victim
			if (other.left.is_dead())
				return false;
			p.left.hit(other.left);
		} else if (input[2] == "r") { // Righthand victim
			if (other.right.is_dead())
				return false;
			p.left.hit(other.right);
		} else { // Bad input
			return false;
		}
		return true;
	} else if (input[1] == "r") { // Righthand attack
		if (p.right.is_dead())
			return false;
		if (input[2] == "l") { // Lefthand victim
			if (other.left.is_dead())
				return false;
			p.right.hit(other.left);
		} else if (input[2] == "r") { // Righthand victim // Lefthand victim
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

bool handle_combine(Chopsticks::Player &p, const std::vector<std::string> &input) {
	int l_f;
	int r_f;
	try {
		l_f = std::stoi(input[1]);
		r_f = std::stoi(input[2]);
	} catch (...) {
		return false;
	}
	if (l_f < 0 || l_f >= 5)
		return false;
	if (r_f <0 || r_f >= 5)
		return false;
	if (p.left.fingers + p.right.fingers != l_f + r_f)
		return false;
	
	// Switching hands
	if (l_f == p.right.fingers && r_f == p.left.fingers)
		return false;

	// Not changing anything
	if (l_f == p.left.fingers && r_f == p.right.fingers)
		return false;

	p.left.fingers = l_f;
	p.right.fingers = r_f;
	return true;
}

Chopsticks::State move(Chopsticks::Player p, Chopsticks::Player other) {
	std::vector<std::string> input;
	while (true) {
		input.clear();
		std::cout << "Please input move: h <l|r> <l|r> or c <0..5> <0..5>\n";
		std::string input_str;
		std::getline(std::cin, input_str);
		std::istringstream iss(input_str);
		do {
			std::string token;
			iss >> token;
			if (token != "")
				input.push_back(token);
		} while (iss);

		// If incorrect number of inputs, re-ask for input
		if (input.size() != 3)
			continue;

		if (input[0] == "h") { // Hit
			if (handle_hit(p, other, input)) {
				break;
			} else { // Bad hit input
				continue;
			}
		} else if (input[0] == "c") { // Combine
			if (handle_combine(p, input)) {
				break;
			} else { // Bad combine input
				continue;
			}
		} else { // Invalid first input
			continue;
		}
	}
	return std::make_pair(p, other);
}
}
