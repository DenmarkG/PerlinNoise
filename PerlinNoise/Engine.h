#pragma once
#include <SDL.h>

class Color;

class Engine
{
	typedef SDL_Rect Rect;

public:
	const int kWorldSizeX;
	const int kWorldSizeY;

public:
	Engine();
	~Engine();

	int Init();
	void Teardown();

	void Update();

	void SetColor(const Color& color);

	SDL_Renderer* GetRenderer() const { return m_pRenderer; }

private:
	SDL_Renderer* m_pRenderer;
	SDL_Window* m_pWindow;

	bool m_shouldQuit;

private:
	void ProcessInput();
	void ProcessKeyboardEvent(SDL_KeyboardEvent* evt);
	void ProcessMouseEvent(SDL_MouseButtonEvent* evt);
};
