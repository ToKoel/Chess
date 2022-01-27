#include "ChessBoard.h"

ChessBoard::ChessBoard(){
	init();
}
ChessBoard::~ChessBoard() {
}

void ChessBoard::init(){
	board.resize(8);
	for(int i=0; i<8; i++){
		board[i].resize(8);
	}

	teams.push_back(Team("white"));
	teams.push_back(Team("black"));
}

Team* ChessBoard::get_team_ptr(int a){
	return &teams[a];
}
std::vector<Team> ChessBoard::get_teams(){
	return teams;
}

void ChessBoard::toggle_current_round(){
	if(current_round){
		current_round = false;
	} else{
		current_round = true;
	}
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

Figure* ChessBoard::select_piece(int x, int y){
	for(Team t: teams){
		if(t.color == current_color){
			if(t.king.is_check == true){
				std::cout << "Check!" << std::endl;
				if(board[x][y] && (board[x][y]->get_type() == "k" || board[x][y]->get_type() == "K")){
					generate_possible_moves(x,y);
					board[x][y]->print_possible_moves();
					return board[x][y];
				} else{
					return nullptr;
				}
			} else{
				break;
			}
		}
	}

	if(board[x][y] && current_color == board[x][y]->get_color()){
		generate_possible_moves(x,y);
		board[x][y]->print_possible_moves();
		return board[x][y];
	}
	else{
		return nullptr;
	}
}

void ChessBoard::move_piece(Figure* piece, int x, int y){
	if(piece){
		position piece_pos = piece->get_position();
		std::cout << piece_pos.x << " " << piece_pos.y << std::endl;
		for(auto pos: board[piece_pos.x][piece_pos.y]->get_moves()){
			if(pos.x == x && pos.y == y){
				piece->clear_moves();
				if(board[pos.x][pos.y] != nullptr){
					board[pos.x][pos.y]->set_status(false);
				}
				piece->set_position(pos);

				board[pos.x][pos.y] = board[piece_pos.x][piece_pos.y];
				board[piece_pos.x][piece_pos.y] = nullptr;

				if(piece->get_type() == "p" || piece->get_type() == "P" || piece->get_type() == "k" || piece->get_type() == "K"){
					piece->has_moved = true;
				}

				update_figures();
			}
		}
		piece->clear_moves();

		std::cout << "moves cleared" << std::endl;
		piece_pos = piece->get_position();
		std::cout << piece_pos.x << " " << piece_pos.y << std::endl;
		generate_possible_moves(piece_pos.x,piece_pos.y);

		for(auto new_pos: piece->get_moves()){
			std::cout << new_pos.x << " " << new_pos.y << std::endl;
			if(board[new_pos.x][new_pos.y] != nullptr){
				if((board[new_pos.x][new_pos.y]->get_type() == "k" ||  board[new_pos.x][new_pos.y]->get_type() == "K") &&
						board[new_pos.x][new_pos.y]->get_color() != piece->get_color()){
					board[new_pos.x][new_pos.y]->is_check = true;
					std::cout << "Check!" << std::endl;
				}

			}
		}
		piece->clear_moves();

		toggle_current_color();
	}
}

void ChessBoard::toggle_current_color(){
	if(current_color == "white"){
		current_color = "black";
	}else{
		current_color = "white";
	}
}


// handle for computer move
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


// function for manual selection of the move
void ChessBoard::make_move(std::string pos_cr){
	int y = (char)pos_cr[0]-65;
	int x = (int)pos_cr[1]-49;

	for(Team t: teams){
		if(t.king.is_check){
			if(board[x][y]->get_type() != "k" || board[x][y]->get_type() != "K"){

			}
		}
	}


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
		for(auto i=0; i< teams[t].alive_figures.size(); i++){
			if(teams[t].alive_figures[i]->get_status() == false){
				if(teams[t].alive_figures[i]->get_int_type() == 5){
					std::cout << teams[t].color << " lost!" << std::endl;
				}
				teams[t].dead_figures.push_back(teams[t].alive_figures[i]);
				auto pos = std::find(begin(teams[t].alive_figures), end(teams[t].alive_figures), teams[t].alive_figures[i]);
				teams[t].alive_figures.erase(pos);
			}
		}
	}
}

void ChessBoard::generate_possible_moves(int i, int j){
	if(board[i][j] != nullptr){
		std::cout << board[i][j]->get_type() << std::endl;
		switch(board[i][j]->get_int_type()){
		case 1: //pawn
			for(position p: board[i][j]->get_possible_movements_north()){
				if(i+p.x < 8 &&
						i+p.x >=0 &&
						j+p.y < 8 &&
						j+p.y >= 0 &&
						board[i+p.x][j+p.y] == nullptr){
					board[i][j]->add_to_possible_moves(i+p.x, j+p.y);
					if(i+p.x+1 < 8 && i+p.x+1 >=0 &&
						board[i+2][j] == nullptr && board[i][j]->has_moved == false && board[i][j]->get_color()=="black"){
						board[i][j]->add_to_possible_moves(i+2, j);
					} else if(i+p.x-1 < 8 && i+p.x-1 >=0 &&
							board[i-2][j+p.y] == nullptr && board[i][j]->has_moved == false && board[i][j]->get_color()=="white"){
						board[i][j]->add_to_possible_moves(i-2, j);
					}
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
				teams[1].alive_figures.push_back(board[j][col]);
				rooks_count_black++;
				col++;
			}
			else if(parts[j][i] == 'R'){
				board[j][col] = &(teams[0].rooks[rooks_count_white]);
				teams[0].rooks[rooks_count_white].set_position(j, col);
				teams[0].alive_figures.push_back(board[j][col]);
				rooks_count_white++;
				col++;
			}
			else if(parts[j][i] == 'n'){
				board[j][col] = &(teams[1].knights[knights_count_black]);
				teams[1].knights[knights_count_black].set_position(j, col);
				teams[1].alive_figures.push_back(board[j][col]);
				knights_count_black++;
				col++;
			}
			else if(parts[j][i] == 'N'){
				board[j][col] = &(teams[0].knights[knights_count_white]);
				teams[0].knights[knights_count_white].set_position(j, col);
				teams[0].alive_figures.push_back(board[j][col]);
				knights_count_white++;
				col++;
			}
			else if(parts[j][i] == 'b'){
				board[j][col] = &(teams[1].bishops[bishops_count_black]);
				teams[1].bishops[bishops_count_black].set_position(j, col);
				teams[1].alive_figures.push_back(board[j][col]);
				bishops_count_black++;
				col++;
			}
			else if(parts[j][i] == 'B'){
				board[j][col] = &(teams[0].bishops[bishops_count_white]);
				teams[0].bishops[bishops_count_white].set_position(j, col);
				teams[0].alive_figures.push_back(board[j][col]);
				bishops_count_white++;
				col++;
			}
			else if(parts[j][i] == 'p'){
				board[j][col] = &(teams[1].pawns[pawns_count_black]);
				teams[1].pawns[pawns_count_black].set_position(j, col);
				teams[1].alive_figures.push_back(board[j][col]);
				pawns_count_black++;
				col++;
			}
			else if(parts[j][i] == 'P'){
				board[j][col] = &(teams[0].pawns[pawns_count_white]);
				teams[0].pawns[pawns_count_white].set_position(j, col);
				teams[0].alive_figures.push_back(board[j][col]);
				pawns_count_white++;
				col++;
			}
			else if(parts[j][i] == 'q'){
				board[j][col] = &(teams[1].queen);
				teams[1].queen.set_position(j, col);
				teams[1].alive_figures.push_back(board[j][col]);
				col++;

			}
			else if(parts[j][i] == 'Q'){
				board[j][col] = &(teams[0].queen);
				teams[0].queen.set_position(j, col);
				teams[0].alive_figures.push_back(board[j][col]);
				col++;
			}
			else if(parts[j][i] == 'k'){
				board[j][col] = &(teams[1].king);
				teams[1].king.set_position(j, col);
				teams[1].alive_figures.push_back(board[j][col]);
				col++;

			}
			else if(parts[j][i] == 'K'){
				board[j][col] = &(teams[0].king);
				teams[0].king.set_position(j, col);
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

