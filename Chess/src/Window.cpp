/*
 * Window.cpp
 *
 *  Created on: 02.11.2021
 *      Author: tobiaskohler
 */

#include "Window.h"

Window::Window(ChessBoard* board): chessboard(board) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, 680, 680, 0);

	renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	screen_width = 680;
	screen_height = 680;

	isRunning = true;

	load_images();
}

Window::~Window() {
	for(auto const& texture: textures){
		SDL_DestroyTexture(texture.second);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
}


bool Window::handle_events(){
	SDL_Event event;
	SDL_WaitEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		return true;
		break;


	case SDL_MOUSEBUTTONDOWN:
		int x,y;
		SDL_GetMouseState(&x,&y);
		x /= screen_width/8;
		y /= screen_height/8;

		selected_piece = chessboard->select_piece(y,x);
		std::cout << "selected piece: " << selected_piece << std::endl;
		break;


	case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&x, &y);
		x /= screen_width/8;
		y /= screen_height/8;

		std::cout << selected_piece << std::endl;
		chessboard->move_piece(selected_piece, y, x);
		render_pieces();
		selected_piece = nullptr;
		break;
	}

	return false;


}

void Window::load_images() {
	SDL_Surface* image = SDL_LoadBMP("images/king_white.bmp");
	textures["K"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/king_black.bmp");
	textures["k"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/knight_white.bmp");
	textures["N"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/knight_black.bmp");
	textures["n"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/pawn_white.bmp");
	textures["P"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/pawn_black.bmp");
	textures["p"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/rook_white.bmp");
	textures["R"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/rook_black.bmp");
	textures["r"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/queen_white.bmp");
	textures["Q"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/queen_black.bmp");
	textures["q"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/pawn_white.bmp");
	textures["B"] = SDL_CreateTextureFromSurface(renderer, image);

	image = SDL_LoadBMP("images/pawn_black.bmp");
	textures["b"] = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);
}

void Window::draw_board(int height, int width){
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
				SDL_SetRenderDrawColor(renderer, 255, 204, 153, 255);
			} else{
				SDL_SetRenderDrawColor(renderer, 204, 102, 0, 255);
			}

			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void Window::render_pieces(){
	SDL_RenderClear(renderer);
	draw_board(screen_width, screen_height);
	std::string type = "";
	int x = 0;
	int y = 0;

	for(int i=0; i<2; i++){
		for(int j=0; j< chessboard->get_teams()[i].alive_figures.size(); j++){
			type = chessboard->get_teams()[i].alive_figures[j]->get_type();
			x = chessboard->get_teams()[i].alive_figures[j]->get_position().x;
			y = chessboard->get_teams()[i].alive_figures[j]->get_position().y;
			render_piece_texture(type, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

void Window::render_piece_texture(std::string type, int x, int y) {

	SDL_Rect toRect;
	int square_side = screen_width/8 * 0.75;
	toRect.w = square_side;
	toRect.h = square_side;
	toRect.x = y*screen_width/8+0.15*square_side;
	toRect.y = x*screen_height/8+0.15*square_side;

	if(SDL_RenderCopy(renderer, textures[type], NULL, &toRect) <0){
		printf("Error: %s\n", SDL_GetError());
	}
}

void Window::render(){
	SDL_RenderPresent(renderer);
}

