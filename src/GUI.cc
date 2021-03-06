#include "GUI.hh"

PieceFactory factory;

static Button promotionButton[8] = {
		QUEEN, static_cast<int>(Screen::getWidth() * 0.3f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(10),
		KNIGHT, static_cast<int>(Screen::getWidth() * 0.4f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(7),
		ROOK, static_cast<int>(Screen::getWidth() * 0.5f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(11),
		BISHOP, static_cast<int>(Screen::getWidth() * 0.6f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(6),
		QUEEN, static_cast<int>(Screen::getWidth() * 0.3f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(4),
		KNIGHT, static_cast<int>(Screen::getWidth() * 0.4f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(1),
		ROOK, static_cast<int>(Screen::getWidth() * 0.5f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(5),
		BISHOP, static_cast<int>(Screen::getWidth() * 0.6f), Screen::getHeight() / 2, Screen::getWidth() / 8, Screen::getHeight() / 6, *factory.getPiece(0)
};

bool GUI::onMouseRollOver(SDL_Point &mousePos, SDL_Rect &square)
{
	return SDL_PointInRect(&mousePos, &square);
}

Square *GUI::onSelect(SDL_Point &mousePos)
{
	int x = mousePos.x * 10 / Screen::getWidth();
	int y = mousePos.y * 8 / Screen::getHeight();

	if (Sqr::squareHelper(x, y) != nullptr)
		return &Sqr::getSquare(x, y);
	else
		return &Sqr::getSquare(7, y);
}

void GUI::displayPromotionTable()
{
	auto* rect = new SDL_Rect {Screen::getWidth() / 8, Screen::getHeight() / 5, static_cast<int>(Screen::getWidth() * 0.75f), Screen::getHeight() / 2};

	SDL_SetRenderDrawColor(Renderer::get(), 128, 128, 128, 255);
	SDL_RenderFillRect(Renderer::get(), rect);

	delete rect;
}
