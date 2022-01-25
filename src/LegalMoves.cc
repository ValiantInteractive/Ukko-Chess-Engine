#include "LegalMoves.hh"

namespace LegalMove
{
	// the vector to be returned
	std::vector<Square> sqrs;

	// knight, king
	void HandyFunc(Piece p, int x, int y)
	{
		// if square is not on board
		if(Sqr::squareHelper((p.x + x), (p.y + y)) != nullptr)
		{
			// if square is empty
			if(Sqr::squareHelper((p.x + x), (p.y + y))->piece.type == NONE)
				sqrs.push_back(*Sqr::squareHelper((p.x + x), (p.y + y)));
			
			// add if enemy is on square
			else
				if(Sqr::squareHelper((p.x + x), (p.y + y))->piece.color != p.color)
					sqrs.push_back(*Sqr::squareHelper((p.x + x), (p.y + y)));
		}
	}

	// rook, 
	void LooperFunc(Piece p, int x, int y)
	{
		// max distance
		for(int i = 0; i < 8; i++)
		{
			if(Sqr::squareHelper((p.x + i * x), (p.y + i * y)) != nullptr)
			{
				if(Sqr::squareHelper((p.x + i * x), (p.y + i * y))->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper((p.x + i * x), (p.y + i * y)));
				else
				{
					if(Sqr::squareHelper((p.x + i * x), (p.y + i * y))->piece.color != p.color)
						sqrs.push_back(*Sqr::squareHelper((p.x + i * x), (p.y + i * y)));
					else
						break;
				}
			}
			else
				break;
		}
	}

	void PawnFunc(Piece p, bool player)
	{
		int m = -1;
		if(player)
		{
			// first row is special
			if(p.y == 6)
				if(Sqr::squareHelper(p.x, 4)->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper(p.x, 4));
		}
		else
		{
			if(p.y == 1)
				if(Sqr::squareHelper(p.x, 3)->piece.type == NONE)
					sqrs.push_back(*Sqr::squareHelper(p.x, 3));

			m = 1;
		}
		
		// left
		Square* l = Sqr::squareHelper(p.x + 1 * m, p.y + 1 * m);
		// check that square is on the screen
		if(l != nullptr)
			// check if square is empty
			if(l->piece.type != NONE)
				// check that the square color is different to piece
				if(l->piece.color != p.color)
					// add square
					sqrs.push_back(*l);

		// center
		Square* c = Sqr::squareHelper(p.x, p.y + 1 * m);
		if(c != nullptr)
			if(c->piece.type == NONE)
				sqrs.push_back(*c);

		// right
		Square* r = Sqr::squareHelper(p.x - 1 * m, p.y + 1 * m);
		if(r != nullptr)
			if(r->piece.type != NONE)
				if(r->piece.color != p.color)
					sqrs.push_back(*r);
	}


	// vector type might need to be pointer
	std::vector<Square> show(Piece piece)
	{
		// clear vector to be sure
		sqrs.clear();

		switch(piece.type)
		{
			case PAWN:

			if(piece.user == PLAYER)
				PawnFunc(piece, true);

			else
				PawnFunc(piece, false);

			break;
			case KNIGHT:
			
			for(int i = -2; i < 3; i++)
				for(int j = -2; j < 3; j++)
					if((i != 0 && j != 0) && abs(i) != abs(j))
						HandyFunc(piece, i, j);
	
			break;
			case QUEEN: 
				
			break;
			case KING:

			for(int i = -1; i < 2; i++)
				for(int j = -1; j < 2; j++)
					if(!(i == 0 && j == 0))
						HandyFunc(piece, i, j);
			
			break;

			case BISHOP: break;

			case ROOK: 

			LooperFunc(piece, 1, 0);
			LooperFunc(piece, -1, 0);
			LooperFunc(piece, 0, 1);
			LooperFunc(piece, 0, -1);
			
			break;
			case NONE: break;
		}

		return sqrs;
	}
}


