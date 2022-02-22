#include "Engine.hh"

Engine::Engine() = default;

Engine::~Engine() = default;

bool Engine::PlayMove()
{
	// clear existing stuff
	clearEngine();
	clearPlayer();

	// check if engine has moves
	getEngineMoves();

	if(!enginePairs.empty())
	{
		clearEngine();

		MinMax m = maxi(2);

		Move::execute(m._bestMove->first, m._bestMove->second);
	
		return true;
	}
	else
	{
		if(Global::engineInCheck)
			Global::state = VICTORY;
		else
			Global::state = DRAW;
		return false;
	}
}

// returns the best move for the engine
MinMax Engine::engineBest()
{
	getEngineMoves();

	std::pair<Piece*, Square>* m = nullptr; 

	double balance = evaluate();

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// evaluate move
		double a = evaluate() + 0.01;

		if(a > balance)
		{
			m = &enginePairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

MinMax Engine::playerBest()
{
	getPlayerMoves();

	std::pair<Piece*, Square>* m = nullptr;

	double balance = evaluate();

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		double a = evaluate() + 0.01;

		if(a > balance)
		{
			m = &playerPairs[i];
			balance = a;
		}
	}

	return MinMax(balance, m);
}

double Engine::evaluate()
{
	// king multiplier
	// center multiplier
	// line multiplier

	getMaterialBalance();
	double calc = engineMaterial - playerMaterial;
	
	// this is just an example conversion
	double eval = calc / 20;
	
	// maybe we have some use for this later dunno
	Global::evaluation = eval;
	return eval;
}


void Engine::getMaterialBalance()
{
	engineMaterial = materialValue(false);
	playerMaterial = materialValue(true);
}

MinMax Engine::maxi(int depth)
{
	if(depth == 0)
		return engineBest();

	getEngineMoves();

	int score = 0;
	int max = INT_MIN;
	std::pair<Piece*, Square>* m = nullptr;

	MinMax bestMove;

	for(int i = 0; i < (int)enginePairs.size(); i++)
	{
		// make fake move
		makeFakeMove(&enginePairs[i]);

		// call to min
		MinMax move = mini(depth - 1);

		score = move._evaluation;

		// make fake move normal
		fakeMoveNormal(&enginePairs[i]);

		if(score > max)
		{
			max = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(max, m);
}

MinMax Engine::mini(int depth)
{
	if(depth == 0) 
		return playerBest();

	getPlayerMoves();

	int score = 0;
	int min = INT_MAX;
	std::pair<Piece*, Square>* m = nullptr;

	for(int i = 0; i < (int)playerPairs.size(); i++)
	{
		makeFakeMove(&playerPairs[i]);
		
		MinMax move = maxi(depth - 1);
		score = move._evaluation;

		fakeMoveNormal(&playerPairs[i]);

		if(score < min)
		{
			min = score;
			m = move._bestMove;
		}
	}
	
	return MinMax(min, m);
}

//TODO rewrite this
double Engine::materialValue(bool player)
{
	double n = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(player && Sqr::getSquare(i, j).piece->user == PLAYER)
				n += getValue(Sqr::getSquare(i, j));

			if((!player) && Sqr::getSquare(i, j).piece->user == ENGINE)
				n += getValue(Sqr::getSquare(i, j));
		}
	}
	
	return n;
}

double Engine::getValue(Square square)
{
	double n = 0;
	switch(square.piece->type)
	{
		case KING: n += 1000; break; // might not be final
		case NONE: break;
		case ROOK: n += 5; break;
		case PAWN: n += 1; break;
		case QUEEN: n += 9; break;
		case KNIGHT: n += 3; break;
		case BISHOP: n += 3.25; break;
	}
	return n;
}

void Engine::makeFakeMove(std::pair<Piece*, Square>* move)
{
	// get the target piece
	target = Sqr::squareHelper(move->second.x, move->second.y)->piece;

	// source goes to target
	Sqr::squareHelper(move->second.x, move->second.y)->piece = move->first;

	// source is set to zero
	Global::ghost(Sqr::squareHelper(move->first->x, move->first->y)->piece);
}

void Engine::fakeMoveNormal(std::pair<Piece*, Square>* move)
{
	// source goes to normal
	Sqr::squareHelper(move->second.x, move->second.y)->piece = target;

	// target goes to normal
	Sqr::squareHelper(move->first->x, move->first->y)->piece = move->first;
}

void Engine::getEngineMoves()
{
	// get all pieces first
	clearEngine();
	getEnginePieces();

	for(auto& i : enginePieces)
	{
		// get legal moves for the piece
		std::vector<Square> moves = LegalMove::getLegal(*i);

		for(auto& j : moves)
		{
			enginePairs.push_back(std::make_pair(i, j));
			engineMoves.push_back(j);
		}
	}
}

void Engine::getPlayerMoves()
{
	clearPlayer();
	getPlayerPieces();

	for(auto& i : playerPieces)
	{
		std::vector<Square> moves = LegalMove::getLegal(*i);
		for(auto& j : moves)
		{
			playerPairs.push_back(std::make_pair(i, j));
			playerMoves.push_back(j);
		}
	}
}

void Engine::clearEngine()
{
	enginePieces.clear();
	engineMoves.clear();
	enginePairs.clear();
}

void Engine::clearPlayer()
{
	playerPieces.clear();
	playerMoves.clear();
	playerPairs.clear();
}



