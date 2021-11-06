/*
 * Team.cpp
 *
 *  Created on: 23.10.2021
 *      Author: tobiaskohler
 */

#include "Team.h"

Team::Team(std::string color): color(color) {
	std::cout << "generating pawns" << std::endl;
	for(int i=0; i<8; i++){
		pawns.push_back(Pawn(0,0, color));
	}
	std::cout << "pawns generated" << std::endl;

	std::cout << "generating knights, bishops, rooks" << std::endl;
	for(int i=0; i<2; i++){
		knights.push_back(Knight(0,0, color));
		bishops.push_back(Bishop(0,0, color));
		rooks.push_back(Rook(0,0, color));
	}
	std::cout << "finished" << std::endl;

	king.set_color(color);
	queen.set_color(color);
	if(color=="black"){
		king.set_type("k");
		queen.set_type("q");
	}
	else{
		king.set_type("K");
		queen.set_type("Q");
	}


	std::cout << "team finished" << std::endl;
}

Team::~Team() {
	// TODO Auto-generated destructor stub
}

