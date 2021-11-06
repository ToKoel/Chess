/*
 * ChessBoard.h
 *
 *  Created on: 22.10.2021
 *      Author: tobiaskohler
 */

#ifndef SRC_CHESSBOARD_H_
#define SRC_CHESSBOARD_H_

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <typeinfo>
#include <map>
#include <SDL2/SDL_image.h>




#include "Figure.h"
#include "Team.h"

class image_cache{
	std::map<std::string, SDL_Surface*> cache_;
public:
	SDL_Surface* get_image(std::string file){
		std::map<std::string, SDL_Surface*>::iterator i = cache_.find(file);
		if(i == cache_.end()) {
			SDL_Surface* surf = IMG_Load(file.c_str());
			i = cache_.insert(i, make_pair(file, surf));
		}
		return i->second;
	}
	void flush(){
		std::map<std::string, SDL_Surface*>::iterator i = cache_.begin();
		for(;i != cache_.end();++i)
			SDL_FreeSurface(i->second);
		cache_.clear();
	}
	~image_cache() {flush();}
};

class ChessBoard {
	std::vector<std::vector<Figure*> > board;
	std::vector<Team> teams;
	std::vector<Figure> empties;
	Window* game_window;

	std::map<std::string, SDL_Texture*> textures;

	bool current_round = false;

public:
	static SDL_Texture* blackKingTexture;
	static SDL_Texture* whiteKingTexture;
	static SDL_Texture* blackKnightTexture;
	static SDL_Texture* whiteKnightTexture;
	static SDL_Texture* blackRookTexture;
	static SDL_Texture* whiteRookTexture;
	static SDL_Texture* blackBishopTexture;
	static SDL_Texture* whiteBishopTexture;
	static SDL_Texture* whiteQueenTexture;
	static SDL_Texture* blackQueenTexture;
	static SDL_Texture* whitePawnTexture;
	static SDL_Texture* blackPawnTexture;

	ChessBoard(Window*);
	ChessBoard();
	void set_game_window(Window* game_window);
	void init();
	void render_board();
	void render_piece_texture(std::string, int x, int y);
	void resize_window(int height, int width);
	void load_images();
	void toggle_current_round();
	bool get_current_round();
	void starting_positions();
	void update_board();
	void make_move(std::string);
	int select_piece(std::string);
	virtual ~ChessBoard();
	void print_board();
	void generate_possible_moves(int, int);
	void starting_positions_from_FEN(std::string FEN);
	Team* get_team_ptr(int);
	std::vector<Team> get_teams();
	void update_figures();
	void move_piece(std::string, int);
};

#endif /* SRC_CHESSBOARD_H_ */
