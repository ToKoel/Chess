/*
 * Game.h
 *
 *  Created on: 05.11.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_GAME_H_
#define SRC_GAME_H_

#include "Window.h"
#include "ChessBoard.h"

class Game {
public:
	Window window;
	ChessBoard chessboard;
	Game();
	virtual ~Game();

	void run();
};

#endif /* SRC_GAME_H_ */
