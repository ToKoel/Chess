/*
 * Figures.cpp
 *
 *  Created on: 23.10.2021
 *      Author: tobiaskohler
 */

#include "Figure.h"

Figure::Figure() {
	set_type(" ");
	set_position(0,0);
	set_status(true);
}

Figure::~Figure() {

//	std::cout << "figure destroyed" << std::endl;
}

void Figure::move(){

}

void Figure::set_int_type(int i){
	int_type = i;
}

std::string Figure::get_type(){
	return type;
}

void Figure::set_texture(std::string tex){
	texture = tex;
}

std::string Figure::get_texture(){
	return texture;
}

int Figure::get_int_type(){
	return int_type;
}

void Figure::set_type(std::string t){
	type = t;
}

void Figure::set_position(int x, int y){
	current_pos.x = x;
	current_pos.y = y;
}

void Figure::set_position(position pos){
	current_pos = pos;
}

position Figure::get_position(){
	return current_pos;
}

std::string Figure::get_position_string(){
	std::string pos = "";
	int row = current_pos.x;
	int column = current_pos.y;

	char column_letter = 'A' + column;
	char row_char = '1' + row;

	pos += column_letter;
	pos += row_char;

	return pos;
}

std::vector<position> Figure::get_possible_movements_north(){
	return possible_movements_north;
}

std::vector<position> Figure::get_possible_movements_south(){
	return possible_movements_south;
}

std::vector<position> Figure::get_possible_movements_east(){
	return possible_movements_east;
}

std::vector<position> Figure::get_possible_movements_west(){
	return possible_movements_west;
}

std::vector<position> Figure::get_possible_movements_northeast(){
	return possible_movements_northeast;
}

std::vector<position> Figure::get_possible_movements_northwest(){
	return possible_movements_northwest;
}

std::vector<position> Figure::get_possible_movements_southeast(){
	return possible_movements_southeast;
}

std::vector<position> Figure::get_possible_movements_southwest(){
	return possible_movements_southwest;
}

void Figure::add_to_possible_movements_north(position p){
	possible_movements_north.push_back(p);
}

void Figure::add_to_possible_movements_south(position p){
	possible_movements_south.push_back(p);
}

void Figure::add_to_possible_movements_east(position p){
	possible_movements_east.push_back(p);
}

void Figure::add_to_possible_movements_west(position p){
	possible_movements_west.push_back(p);
}

void Figure::add_to_possible_movements_northeast(position p){
	possible_movements_northeast.push_back(p);
}

void Figure::add_to_possible_movements_northwest(position p){
	possible_movements_northwest.push_back(p);
}

void Figure::add_to_possible_movements_southeast(position p){
	possible_movements_southeast.push_back(p);
}

void Figure::add_to_possible_movements_southwest(position p){
	possible_movements_southwest.push_back(p);
}

void Figure::toggle_selected(){
	if(selected){
		selected = false;
	} else {
		selected = true;
	}
}

bool Figure::is_selected(){
	return selected;
}

void Figure::add_to_possible_moves(int x, int y){
	moves.push_back(position(x,y));
	num_possible_moves++;
}

void Figure::clear_moves(){
	moves.clear();
	num_possible_moves = 0;
}

int Figure::print_possible_moves(){
	char a = 'A';
	int count = 1;
	for(auto move : moves){
		std::cout << count << ": " << (char)(a+move.y) << move.x+1 << std::endl;
		count++;
	}
	return 0;
}

void Figure::set_num_possible_moves(int n){
	num_possible_moves = n;
}

int Figure::get_num_possible_moves(){
	return num_possible_moves;
}

void Figure::set_color(std::string c){
	color = c;
}

std::string Figure::get_color(){
	return color;
}

std::vector<position> Figure::get_moves(){
	return moves;
}

void Figure::set_status(bool b){
	status = b;
}

bool Figure::get_status(){
	return status;
}



Pawn::Pawn(int x, int y, std::string color){
	set_int_type(1);
	set_position(x,y);
	set_color(color);

	if(color=="black"){
		set_type("p");
		add_to_possible_movements_north(position(1,0));
		add_to_possible_movements_northeast(position(1,1));
		add_to_possible_movements_northwest(position(1,-1));
	} else{
		set_type("P");
		add_to_possible_movements_north(position(-1,0));
		add_to_possible_movements_northeast(position(-1,1));
		add_to_possible_movements_northwest(position(-1,-1));
	}
}

void Pawn::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

Rook::Rook(int x, int y, std::string color){
	if(color=="black"){
		set_type("r");
	} else{
		set_type("R");
	}
	set_int_type(2);
	set_position(x,y);
	set_color(color);

	for(int i=1; i<8; i++){
		add_to_possible_movements_east(position(0,i));
		add_to_possible_movements_north(position(-i,0));
		add_to_possible_movements_south(position(i,0));
		add_to_possible_movements_west(position(0,-i));
	}
}

void Rook::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

Knight::Knight(int x, int y, std::string color){
	if(color=="black"){
			set_type("n");
		} else{
			set_type("N");
		}
	set_int_type(3);
	set_position(x,y);
	set_color(color);
	add_to_possible_movements_north(position(2,1));
	add_to_possible_movements_south(position(2,-1));
	add_to_possible_movements_east(position(1,2));
	add_to_possible_movements_west(position(1,-2));
	add_to_possible_movements_northwest(position(-2,1));
	add_to_possible_movements_northeast(position(-2,-1));
	add_to_possible_movements_southwest(position(-1,2));
	add_to_possible_movements_southeast(position(-1,-2));
}

void Knight::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

Bishop::Bishop(int x, int y, std::string color){
	if(color=="black"){
			set_type("b");
		} else{
			set_type("B");
		}
	set_int_type(4);
	set_position(x,y);
	set_color(color);
	for(int i=1; i<8; i++){
		add_to_possible_movements_northeast(position(-i,i));
		add_to_possible_movements_northwest(position(-i,-i));
		add_to_possible_movements_southeast(position(i,i));
		add_to_possible_movements_southwest(position(i,-i));
	}

}

void Bishop::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

King::King(int x, int y, std::string color){
	if(color=="black"){
			set_type("k");
		} else{
			set_type("K");
		}
	set_int_type(5);
	set_position(x,y);
	set_color(color);

	add_to_possible_movements_east(position(0,1));
	add_to_possible_movements_north(position(-1,0));
	add_to_possible_movements_south(position(1,0));
	add_to_possible_movements_west(position(0,-1));

	add_to_possible_movements_northeast(position(-1,1));
	add_to_possible_movements_northwest(position(-1,-1));
	add_to_possible_movements_southeast(position(1,1));
	add_to_possible_movements_southwest(position(1,-1));
}

void King::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

Queen::Queen(int x, int y, std::string color){
	if(color=="black"){
			set_type("q");
		} else{
			set_type("Q");
		}
	set_int_type(6);
	set_position(x,y);
	set_color(color);

	for(int i=1; i<8; i++){
			add_to_possible_movements_east(position(0,i));
			add_to_possible_movements_north(position(-i,0));
			add_to_possible_movements_south(position(i,0));
			add_to_possible_movements_west(position(0,-i));

			add_to_possible_movements_northeast(position(-i,i));
			add_to_possible_movements_northwest(position(-i,-i));
			add_to_possible_movements_southeast(position(i,i));
			add_to_possible_movements_southwest(position(i,-i));
	}
}

void Queen::move(){
	position pos = get_position();
	set_position(pos.x, pos.y+1);
}

