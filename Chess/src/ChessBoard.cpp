/*
 * ChessBoard.cpp
 *
 *  Created on: 22.10.2021
 *      Author: tobiaskohler
 */

#include "ChessBoard.h"



ChessBoard::ChessBoard(Window* game_window):game_window(game_window) {
	for(int i=0; i<32; i++){
		empties.push_back(Figure());
	}

	board.resize(8);
	for(int i=0; i<8; i++){
		board[i].resize(8);
	}

	std::cout << "generating teams" << std::endl;

	teams.push_back(Team("white"));
	teams.push_back(Team("black"));

	std::cout << "teams generated" << std::endl;

	load_images();
}

ChessBoard::ChessBoard(){
}

void ChessBoard::set_game_window(Window* window){
	game_window = window;
}

void ChessBoard::init(){
	for(int i=0; i<32; i++){
		empties.push_back(Figure());
	}

	board.resize(8);
	for(int i=0; i<8; i++){
		board[i].resize(8);
	}

	std::cout << "generating teams" << std::endl;

	teams.push_back(Team("white"));
	teams.push_back(Team("black"));

	std::cout << "teams generated" << std::endl;
}

ChessBoard::~ChessBoard() {
	for(auto const& texture: textures){
		SDL_DestroyTexture(texture.second);
	}
	std::cout << "chessboard destroyed" << std::endl;
}

void ChessBoard::resize_window(int height, int width){
	int box_width = width / 8;
	int box_height = height / 8;

	if(box_width >= box_height){
		box_width = box_height;
	} else{
		box_height = box_width;
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			SDL_Rect rect;
			rect.x = x * box_width;
			rect.y = y * box_height;
			rect.w = box_width;
			rect.h = box_height;
			if((x+y) % 2 == 0){
				SDL_SetRenderDrawColor(game_window->renderer, 255, 204, 153, 255);
			} else{
				SDL_SetRenderDrawColor(game_window->renderer, 204, 102, 0, 255);
			}

			SDL_RenderFillRect(game_window->renderer, &rect);
		}
	}
}

void ChessBoard::render_board(){
	SDL_RenderClear(game_window->renderer);
	resize_window(680, 680);
	std::string type = "";
	int x = 0;
	int y = 0;

	for(int i=0; i<2; i++){
		for(int j=0; j< teams[i].alive_figures.size(); j++){
			type = teams[i].alive_figures[j]->get_type();
			x = teams[i].alive_figures[j]->get_position().x;
			y = teams[i].alive_figures[j]->get_position().y;
			std::cout << type << std::endl;
			render_piece_texture(type, x, y);
		}
	}
	SDL_RenderPresent(game_window->renderer);
}

void ChessBoard::render_piece_texture(std::string type, int x, int y) {

	SDL_Rect toRect;
	toRect.w = 60;
	toRect.h = 60;
	toRect.x = y*680/8+12;
	toRect.y = x*680/8+12;

	if(SDL_RenderCopy(game_window->renderer, textures[type], NULL, &toRect) <0){
		printf("Error: %s\n", SDL_GetError());
	}

	std::cout << "render_piece_texture finished" << std::endl;
}

void ChessBoard::load_images() {
	SDL_Surface* image = SDL_LoadBMP("images/king_white.bmp");
	textures["K"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/king_black.bmp");
	textures["k"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/knight_white.bmp");
	textures["N"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/knight_black.bmp");
	textures["n"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/pawn_white.bmp");
	textures["P"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/pawn_black.bmp");
	textures["p"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/rook_white.bmp");
	textures["R"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/rook_black.bmp");
	textures["r"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/queen_white.bmp");
	textures["Q"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/queen_black.bmp");
	textures["q"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/pawn_white.bmp");
	textures["B"] = SDL_CreateTextureFromSurface(game_window->renderer, image);

	image = SDL_LoadBMP("images/pawn_black.bmp");
	textures["b"] = SDL_CreateTextureFromSurface(game_window->renderer, image);


	SDL_FreeSurface(image);
}

Team* ChessBoard::get_team_ptr(int a){
	return &teams[a];
}

void ChessBoard::toggle_current_round(){
	if(current_round){
		current_round = false;
	} else{
		current_round = true;
	}
}

std::vector<Team> ChessBoard::get_teams(){
	return teams;
}

bool ChessBoard::get_current_round(){
	return current_round;
}

int ChessBoard::select_piece(std::string pos_cr){
	int y = (char)pos_cr[0]-65;
	int x = (int)pos_cr[1]-49;

	std::cout << pos_cr << " selected" << std::endl;

	generate_possible_moves(x,y);
	board[x][y]->print_possible_moves();

	if(board[x][y]->get_moves().size() == 0){
		return 0;
	} else{
		return board[x][y]->get_num_possible_moves();
	}
}

void ChessBoard::move_piece(std::string pos_cr, int move_nr){
	int y = (char)pos_cr[0]-65;
	int x = (int)pos_cr[1]-49;

	std::cout << "selected move nr: " << move_nr+1 << std::endl;

	position new_position = (board[x][y]->get_moves())[move_nr];
	board[x][y]->clear_moves();
	if(board[new_position.x][new_position.y] != nullptr){
		board[new_position.x][new_position.y]->set_status(false);
	}
	board[x][y]->set_position(new_position);
	board[new_position.x][new_position.y] = board[x][y];
	board[x][y] = nullptr;

	update_figures();
	toggle_current_round();
}



void ChessBoard::make_move(std::string pos_cr){
	int y = (char)pos_cr[0]-65;
	int x = (int)pos_cr[1]-49;

	board[x][y]->toggle_selected();
	generate_possible_moves(x,y);

	if(board[x][y]->get_moves().size() == 0){
		return;
	}
	std::cout << "selected piece: " << board[x][y]->get_position_string() << std::endl;

	board[x][y]->print_possible_moves();

	int move_nr;
	std::cout << "Enter move number: ";
	std::cin >> move_nr;

	position new_position = (board[x][y]->get_moves())[move_nr-1];
	board[x][y]->clear_moves();
	if(board[new_position.x][new_position.y] != nullptr){
		board[new_position.x][new_position.y]->set_status(false);
	}
	board[x][y]->set_position(new_position);
	board[new_position.x][new_position.y] = board[x][y];
	board[x][y] = nullptr;

	update_figures();
	toggle_current_round();

}



void ChessBoard::update_figures(){
	for(int t=0; t<2; t++){
		for(int i=0; i< teams[t].alive_figures.size(); i++){
			if(teams[t].alive_figures[i]->get_status() == false){
				teams[t].dead_figures.push_back(teams[t].alive_figures[i]);
				auto pos = std::find(begin(teams[t].alive_figures), end(teams[t].alive_figures), teams[t].alive_figures[i]);
				teams[t].alive_figures.erase(pos);
			}
		}
	}
}

void ChessBoard::generate_possible_moves(int i, int j){
	if(board[i][j] != nullptr){
		switch(board[i][j]->get_int_type()){
		case 1: //pawn
			for(position p: board[i][j]->get_possible_movements_north()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						board[i+p.x][j+p.y] == nullptr){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_northeast()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						board[i+p.x][j+p.y] != nullptr && board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color()){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				}
			}

			for(position p: board[i][j]->get_possible_movements_northwest()){
							if(i+p.x < 8 &&
									i+p.x >=0 &&
									j+p.y < 8 &&
									j+p.y >= 0 &&
									board[i+p.x][j+p.y] != nullptr && board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color()){
								board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
							}
						}
			break;

		case 2: // rook
			for(position p: board[i][j]->get_possible_movements_north()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_south()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_east()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_west()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}
			break;

		case 3: case 5: case 6: //knight, king and queen
			for(position p: board[i][j]->get_possible_movements_north()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_south()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_east()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_west()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_northeast()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_southeast()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_northwest()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_southwest()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}
			break;

		case 4:
			for(position p: board[i][j]->get_possible_movements_northeast()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_southeast()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_northwest()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}

			for(position p: board[i][j]->get_possible_movements_southwest()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						(board[i+p.x][j+p.y] == nullptr || board[i+p.x][j+p.y]->get_color() != board[i][j]->get_color())){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
				} else {
					break;
				}
			}
			break;

		}
	}
}



void ChessBoard::starting_positions_from_FEN(std::string FEN){
	char delimiter = '/';
	std::string tmp = "";
	std::string originalString = FEN;
	std::vector<std::string> parts;

	std::istringstream iss(originalString);
	while(std::getline(iss, tmp, delimiter)){
		parts.push_back(tmp);
	}
	parts[7] = parts[7].substr(0, parts[7].find(' '));

	int rooks_count_black = 0;
	int rooks_count_white = 0;
	int knights_count_black = 0;
	int knights_count_white = 0;
	int bishops_count_black = 0;
	int bishops_count_white = 0;
	int pawns_count_black = 0;
	int pawns_count_white =0;

	int col = 0;

	for(int j=0; j<8; j++){
		for(int i=0; i<parts[j].length(); i++){
			if(parts[j][i] == 'r'){
				board[j][col] = &(teams[1].rooks[rooks_count_black]);
				teams[1].rooks[rooks_count_black].set_position(j, col);
				teams[1].rooks[rooks_count_black].set_texture("images/rook_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				rooks_count_black++;
				col++;
			}
			else if(parts[j][i] == 'R'){
				board[j][col] = &(teams[0].rooks[rooks_count_white]);
				teams[0].rooks[rooks_count_white].set_position(j, col);
				teams[0].rooks[rooks_count_white].set_texture("images/rook_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				rooks_count_white++;
				col++;
			}
			else if(parts[j][i] == 'n'){
				board[j][col] = &(teams[1].knights[knights_count_black]);
				teams[1].knights[knights_count_black].set_position(j, col);
				teams[1].knights[knights_count_black].set_texture("images/knight_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				knights_count_black++;
				col++;
			}
			else if(parts[j][i] == 'N'){
				board[j][col] = &(teams[0].knights[knights_count_white]);
				teams[0].knights[knights_count_white].set_position(j, col);
				teams[0].knights[knights_count_white].set_texture("images/knight_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				knights_count_white++;
				col++;
			}
			else if(parts[j][i] == 'b'){
				board[j][col] = &(teams[1].bishops[bishops_count_black]);
				teams[1].bishops[bishops_count_black].set_position(j, col);
				teams[1].bishops[bishops_count_black].set_texture("images/knight_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				bishops_count_black++;
				col++;
			}
			else if(parts[j][i] == 'B'){
				board[j][col] = &(teams[0].bishops[bishops_count_white]);
				teams[0].bishops[bishops_count_white].set_position(j, col);
				teams[0].bishops[bishops_count_white].set_texture("images/knight_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				bishops_count_white++;
				col++;
			}
			else if(parts[j][i] == 'p'){
				board[j][col] = &(teams[1].pawns[pawns_count_black]);
				teams[1].pawns[pawns_count_black].set_position(j, col);
				teams[1].pawns[pawns_count_black].set_texture("images/pawn_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				pawns_count_black++;
				col++;
			}
			else if(parts[j][i] == 'P'){
				board[j][col] = &(teams[0].pawns[pawns_count_white]);
				teams[0].pawns[pawns_count_white].set_position(j, col);
				teams[0].pawns[pawns_count_white].set_texture("images/pawn_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				pawns_count_white++;
				col++;
			}
			else if(parts[j][i] == 'q'){
				board[j][col] = &(teams[1].queen);
				teams[1].queen.set_position(j, col);
				teams[1].queen.set_texture("images/queen_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				col++;

			}
			else if(parts[j][i] == 'Q'){
				board[j][col] = &(teams[0].queen);
				teams[0].queen.set_position(j, col);
				teams[0].queen.set_texture("images/queen_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				col++;
			}
			else if(parts[j][i] == 'k'){
				board[j][col] = &(teams[1].king);
				teams[1].king.set_position(j, col);
				teams[1].king.set_texture("images/king_black.bmp");
				teams[1].alive_figures.push_back(board[j][col]);
				col++;

			}
			else if(parts[j][i] == 'K'){
				board[j][col] = &(teams[0].king);
				teams[0].king.set_position(j, col);
				teams[0].king.set_texture("images/king_white.bmp");
				teams[0].alive_figures.push_back(board[j][col]);
				col++;
			}
			else if(isdigit(parts[j][i])){
				int ia = parts[j][i] - '0';
				for(int n=0; n<ia; n++){
					board[j][col] = nullptr;
					col++;
				}
			}
		}
		col = 0;
	}

	for(Team t: teams){
		for(auto fig: t.pawns){
			fig.game_window = game_window;
		}
		for(auto fig: t.knights){
			fig.game_window = game_window;
		}
		for(auto fig: t.rooks){
					fig.game_window = game_window;
				}
		for(auto fig: t.bishops){
					fig.game_window = game_window;
				}
		t.king.game_window = game_window;
		t.queen.game_window = game_window;
	}

	for(Team t: teams){
		for(auto fig : t.pawns){
			if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &fig) != t.alive_figures.end()){
				t.dead_figures.push_back(&fig);
			}
		}
		for(auto fig : t.knights){
			if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &fig) != t.alive_figures.end()){
				t.dead_figures.push_back(&fig);
			}
		}
		for(auto fig : t.rooks){
			if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &fig) != t.alive_figures.end()){
				t.dead_figures.push_back(&fig);
			}
		}
		for(auto fig : t.bishops){
			if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &fig) != t.alive_figures.end()){
				t.dead_figures.push_back(&fig);
			}
		}
		if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &(t.king)) != t.alive_figures.end()){
				t.dead_figures.push_back(&(t.king));
		}
		if(std::find(t.alive_figures.begin(), t.alive_figures.end(), &(t.queen)) != t.alive_figures.end()){
			t.dead_figures.push_back(&(t.queen));
		}
	}
}


void ChessBoard::starting_positions(){
	for(int i=0; i<8; i++){
		teams[0].pawns[i].set_position(i,1);
		teams[1].pawns[i].set_position(i,6);

		board[1][i] = &(teams[0].pawns[i]);
		board[6][i] = &(teams[1].pawns[i]);
	}

	for(int i=2; i<6; i++){
		for(int j=0; j<8; j++){
			board[i][j] = (&empties[j+8*(i-2)]);
		}
	}

	board[0][1] = &(teams[0].knights[0]);
	board[0][6] = &(teams[0].knights[1]);
	board[7][1] = &(teams[1].knights[0]);
	board[7][6] = &(teams[1].knights[1]);

	board[0][0] = &(teams[0].rooks[0]);
	board[0][7] = &(teams[0].rooks[1]);
	board[7][0] = &(teams[1].rooks[0]);
	board[7][7] = &(teams[1].rooks[1]);

	board[0][2] = &(teams[0].bishops[0]);
	board[0][5] = &(teams[0].bishops[1]);
	board[7][2] = &(teams[1].bishops[0]);
	board[7][5] = &(teams[1].bishops[1]);

	board[0][3] = &(teams[0].king);
	board[0][4] = &(teams[0].queen);
	board[7][3] = &(teams[1].king);
	board[7][4] = &(teams[1].queen);

	teams[0].knights[0].set_position(0,1);
	teams[0].knights[1].set_position(0,6);
	teams[1].knights[0].set_position(7,1);
	teams[1].knights[1].set_position(7,6);

	teams[0].rooks[0].set_position(0,0);
	teams[0].rooks[1].set_position(0,7);
	teams[1].rooks[0].set_position(7,0);
	teams[1].rooks[1].set_position(7,7);

	teams[0].bishops[0].set_position(0,2);
	teams[0].bishops[1].set_position(0,5);
	teams[1].bishops[0].set_position(7,2);
	teams[1].bishops[1].set_position(7,5);

	teams[0].queen.set_position(7,3);
	teams[1].queen.set_position(0,3);
	teams[0].king.set_position(7,4);
	teams[1].king.set_position(0,4);
}

void ChessBoard::print_board() {
	std::cout << "------------------------------------------------------------------" << std::endl;
	char a = 'A';
	std::cout << "\t";
	for(int i=0; i<8;i++){
		std::cout << a << "\t";
		a++;
	}
	std::cout << std::endl;
	std::cout << "__________________________________________________________________" << std::endl;


	for(int i=0; i<8; i++){
		std::cout << i+1 << "\t";
		for(int j=0; j<8; j++){
			if(board[i][j] != nullptr){
				if(board[i][j]->get_color() == "white"){
					std::cout <<  (char)((int)(board[i][j]->get_type()[0])-32) << "\t";
				} else{
					std::cout << board[i][j]->get_type() << "\t";
				}
			} else{
				std::cout << "\t";
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << "----------------------------------------------------------" << std::endl;
}

