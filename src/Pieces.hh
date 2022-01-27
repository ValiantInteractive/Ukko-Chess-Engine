#ifndef PIECES_HH
#define PIECES_HH

#include "Piece.hh"
#include "SquareManager.hh"
#include "Settings.hh"

#define ARRSIZE(arr) (int)(sizeof(arr)/sizeof(arr[0]))

namespace Pieces
{
	// initializing pieces in their correct positions
	void init();

	// getting invidual piece
	Piece& get(int n);
}

#endif
