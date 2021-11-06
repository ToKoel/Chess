/*
 * Team.h
 *
 *  Created on: 23.10.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_TEAM_H_
#define SRC_TEAM_H_

#include <vector>
#include <string>
#include "Figure.h"

class Team {
public:
	std::string color;

	std::vector<Pawn> pawns;
	std::vector<Knight> knights;
	std::vector<Bishop> bishops;
	std::vector<Rook> rooks;

	std::vector<Figure*> alive_figures;
	std::vector<Figure*> dead_figures;

	King king{0,0, "white"};
	Queen queen{0,0, "white"};

	Team(std::string);
	virtual ~Team();
};

#endif /* SRC_TEAM_H_ */
