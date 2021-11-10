/*
 * Figures.h
 *
 *  Created on: 23.10.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_FIGURE_H_
#define SRC_FIGURE_H_

#include <string>
#include <iostream>
#include <vector>
//#include "Window.h"
#include <typeinfo>

struct position{
	int x = 0;
	int y = 0;

	position(int x, int y): x(x), y(y){};
};

class Figure {

	std::string type = "empty";
	int int_type = 0;
	std::string color;
	std::string texture_name = "";
	std::string texture = "";
	bool status = true;
	bool selected = false;
	int num_possible_moves = 0;
	position current_pos{0,0};
	std::vector<position> moves;
	std::vector<position> possible_movements_north;
	std::vector<position> possible_movements_south;
	std::vector<position> possible_movements_east;
	std::vector<position> possible_movements_west;
	std::vector<position> possible_movements_northeast;
	std::vector<position> possible_movements_northwest;
	std::vector<position> possible_movements_southeast;
	std::vector<position> possible_movements_southwest;

public:
	bool has_moved = false;
	bool is_check = false;

	virtual void move();
	position get_position();
	std::string get_type();
	int get_int_type();
	void set_position(int x, int y);
	void set_position(position);
	void clear_moves();
	void set_texture(std::string);
	std::string get_texture();
	std::vector<position> get_moves();
	void add_to_possible_moves(int x, int y);
	void set_type(std::string);
	void toggle_selected();
	bool is_selected();
	void remove();
	void set_color(std::string);
	void set_int_type(int);
	void set_status(bool);
	void set_num_possible_moves(int);
	int get_num_possible_moves();
	bool get_status();
	std::string get_position_string();
	std::string get_color();
	int print_possible_moves();
	std::vector<position> get_possible_movements_north();
	std::vector<position> get_possible_movements_south();
	std::vector<position> get_possible_movements_east();
	std::vector<position> get_possible_movements_west();
	std::vector<position> get_possible_movements_northeast();
	std::vector<position> get_possible_movements_northwest();
	std::vector<position> get_possible_movements_southeast();
	std::vector<position> get_possible_movements_southwest();
	void add_to_possible_movements_north(position);
	void add_to_possible_movements_south(position);
	void add_to_possible_movements_east(position);
	void add_to_possible_movements_west(position);
	void add_to_possible_movements_northeast(position);
	void add_to_possible_movements_northwest(position);
	void add_to_possible_movements_southeast(position);
	void add_to_possible_movements_southwest(position);

	Figure();
	virtual ~Figure();
};

class Pawn : public Figure{
public:
	Pawn(int x, int y, std::string color);
	void move();
};

class Knight : public Figure{
public:
	Knight(int x, int y, std::string color);
	void move();
};

class Bishop : public Figure{
public:
	Bishop(int x, int y, std::string color);
	void move();
};

class Rook : public Figure{
public:
	Rook(int x, int y, std::string color);
	void move();
};

class Queen : public Figure{
public:
	Queen(int x, int y, std::string color);
	void move();
};

class King : public Figure{
public:
	King(int x, int y, std::string color);
	void move();
};

#endif /* SRC_FIGURE_H_ */
