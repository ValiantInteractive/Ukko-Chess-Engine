#ifndef BOARD_HH
#define BOARD_HH

#include "Global.hh"
#include "ScreenSize.hh"
#include "Renderer.hh"
#include "SquareManager.hh"

class Board
{
	public: 
		Board();
		void render();
		void makeBoard() const;
		void makeRects();
	
	private:
		// source and destination for texture
		SDL_Rect srcrect{};
		SDL_Rect dstrect{};
};

#endif
