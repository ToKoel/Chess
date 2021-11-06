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

class Window {
public:
	SDL_Window *window;
	SDL_Renderer *renderer;
	int screen_width;
	int screen_height;

	Window();
	virtual ~Window();

	bool handle_events();

	bool isRunning = false;

	void resize_window(int height, int width);
	void render();
	void render_possible_moves();
};

#endif /* SRC_WINDOW_H_ */
