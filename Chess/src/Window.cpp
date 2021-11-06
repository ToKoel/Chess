/*
 * Window.cpp
 *
 *  Created on: 02.11.2021
 *      Author: tobiaskohler
 */

#include "Window.h"

Window::Window() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, 680, 680, 0);

	renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	screen_width = 680;
	screen_height = 680;

	resize_window(screen_height, screen_width);
	SDL_RenderPresent(renderer);

	isRunning = true;
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();
}

void Window::resize_window(int height, int width){
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
		x /= 80;
		y /= 80;
		std::cout << "clicked, pos: "<< x << ", " << y << std::endl;
		break;
	}

	return false;

}

void Window::render(){
//	resize_window(680, 680);
	SDL_RenderPresent(renderer);
}

