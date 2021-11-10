/*
 * ChessBoard.h
 *
 *  Created on: 22.10.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_CHESSBOARD_H_
#define SRC_CHESSBOARD_H_

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <typeinfo>
#include <map>
#include <SDL2/SDL_image.h>

#include "Team.h"

struct my_Struct {

};

class ChessBoard {
	std::vector<std::vector<Figure*> > board;
	std::vector<Team> teams;

	bool current_round = false;
	std::string current_color = "white";

public:
	ChessBoard();
	void init();
	void toggle_current_color();
	void render_pieces();
	void render_piece_texture(std::string, int x, int y);
	void draw_board(int height, int width);
	void load_images();
	void toggle_current_round();
	bool get_current_round();
	void update_board();
	void make_move(std::string);
	int select_piece(std::string);
	Figure* select_piece(int, int);
	void move_piece(Figure* piece, int x, int y);
	virtual ~ChessBoard();
	void print_board();
	void generate_possible_moves(int, int);
	void starting_positions_from_FEN(std::string FEN);
	Team* get_team_ptr(int);
	std::vector<Team> get_teams();
	void update_figures();
	void move_piece(std::string, int);
};

#endif /* SRC_CHESSBOARD_H_ */
