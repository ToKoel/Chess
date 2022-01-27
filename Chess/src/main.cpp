
#include <iostream>
#include "Game.h"



int main(){

	game();

	return 0;
}

//	Window game_window;
//
//
//	SDL_Surface* surface = IMG_Load("images/bishop_black.png");
//	SDL_Texture *texture = SDL_CreateTextureFromSurface(game_window.renderer, surface);
//	SDL_FreeSurface(surface);
//
//	SDL_Rect destination;
//	destination.x = 50;
//	destination.y = 50;
//	destination.w = 300;
//	destination.h = 300;
//
//
//
//	while(game_window.isRunning){
//		game_window.handle_events();
//		game_window.render();
//		SDL_RenderCopy(game_window.renderer, texture, NULL, &destination);
//		SDL_RenderPresent(game_window.renderer);
//	}



//	ChessBoard chessboard;
//	chessboard.starting_positions_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//	//chessboard.starting_positions_from_FEN("rnbqkbnr/p3pppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//	chessboard.print_board();
//
//
//	std::string selection = "";
//	Team* opponent = chessboard.get_team_ptr(1);
//	int rand_fig = 0;
//	std::string position  ="";
//	int num_moves = 0;
//
//	while(selection != "quit"){
//		if(!chessboard.get_current_round()){
//			std::cout << "select piece: " << std::endl;
//			std::cin >> selection;
//
//			chessboard.make_move(selection);
//		}else{
//			while(num_moves == 0){
//				rand_fig = rand() % opponent->alive_figures.size();
//				position = opponent->alive_figures[rand_fig]->get_position_string();
//				num_moves = chessboard.select_piece(position);
//			}
//			chessboard.move_piece(position, rand() % (num_moves));
//			num_moves = 0;
//		}
//		chessboard.print_board();
//
//	}

//
//
//	return 0;
//}



