/*
 * Game.h
 *
 *  Created on: 05.11.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "ChessBoard.h"
#include "Window.h"

void game(){
	ChessBoard board;
	Window window(&board);

	board.starting_positions_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	window.render_pieces();

	bool quit = false;
	while(!quit){
		quit = window.handle_events();
	}
}


#endif /* SRC_GAME_H_ */
