/*
 * Window.h
 *
 *  Created on: 02.11.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_WINDOW_H_
#define SRC_WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <map>

#include "ChessBoard.h"




class Window {
public:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	ChessBoard* chessboard = nullptr;
	int screen_width = 680;
	int screen_height = 680;
	bool isRunning = false;
	std::map<std::string, SDL_Texture*> textures;
	Figure* selected_piece = nullptr;

	Window(ChessBoard* board);
	Window();
	virtual ~Window();
	void draw_board(int , int);
	void render_piece_texture(std::string , int , int );
	void render_pieces();
	void load_images();
	bool handle_events();
	void render();
	void render_possible_moves();
};

#endif /* SRC_WINDOW_H_ */
