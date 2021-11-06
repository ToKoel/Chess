/*
 * Game.cpp
 *
 *  Created on: 05.11.2021
 *      Author: tobiaskohler
 */

#include "Game.h"

Game::Game() {
	chessboard.init();
	chessboard.set_game_window(&window);
	chessboard.load_images();
	chessboard.starting_positions_from_FEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	chessboard.render_board();
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::run(){
	bool quit = false;
	while (!quit)
	{
		quit = window.handle_events();
	}
}

