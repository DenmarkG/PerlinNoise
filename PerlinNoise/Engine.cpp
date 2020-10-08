#include <iostream>
#include <ctime>
#include <chrono>

#include "Engine.h"
#include "Color.h"
#include "Random.h"

#include "PerlinNoise.h"

int constexpr worldSize = 512;

constexpr int kGridCountX = 8;
constexpr int kGridCountY = 8;

Engine::Engine()
	: kWorldSizeX(worldSize)
	, kWorldSizeY(worldSize)
	, m_pRenderer(nullptr)
	, m_pWindow(nullptr)
	, m_shouldQuit(false)
	, m_noise(nullptr)
{
}

Engine::~Engine()
{
	//
}

int Engine::Init()
{
	// Init video for SDL and return error code if something goes wrong
	int errorCode = SDL_Init(SDL_INIT_VIDEO);
	if (errorCode != 0)
	{
		std::cout << "SDL_Init() failed. Error code" << errorCode << ":" << SDL_GetError() << std::endl;
		return errorCode;
	}

	// Init the window and return the error code 
	m_pWindow = SDL_CreateWindow("Random Mosaic",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		kWorldSizeX, kWorldSizeY,
		0);
	if (m_pWindow)
	{
		std::cout << "SDL_CreateWindow() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateWindow() failed. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	// Init the renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_pRenderer)
	{
		std::cout << "SDL_CreateRenderer() succeeded." << std::endl;
	}
	else
	{
		std::cout << "SDL_CreateRenderer() failed. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	m_noise = new PerlinNoise(kWorldSizeX, kWorldSizeY, kGridCountX, kGridCountY);

	return 0;
}

void Engine::Teardown()
{
	if (m_noise)
	{
		delete m_noise;
		m_noise = nullptr;
	}

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}


void Engine::Update()
{
	// Get the frame start time before the loop begins
	auto lastFrameTime = std::chrono::high_resolution_clock::now();

	// For frame locking:
	float step = 0;

	m_noise->GenerateGrid();

	// Clear the previous render state
	SetColor(Color::BLACK);
	SDL_RenderClear(m_pRenderer);

	for (int x = 0; x < kWorldSizeX; ++x)
	{
		for (int y = 0; y < kWorldSizeY; ++y)
		{
			float gridX = (x / (float)m_noise->GetSizeX()) * (float)m_noise->GetCellCountX();
			float gridY = (y / (float)m_noise->GetSizeY()) * (float)m_noise->GetCellCountY();

			float noiseValue = m_noise->CalculateNoiseAtScreenPosition(gridX, gridY);
			Color::uchar colorValue = static_cast<Color::uchar>(noiseValue * 255);
			Color color = { colorValue, colorValue, colorValue, 255 };
			SetColor(color);
			SDL_RenderDrawPoint(m_pRenderer, x, y);
		}
	}
	 
	// Update the input
	while (!m_shouldQuit)
	{
		// Update delta Time
		const float frameRate = 1/60;

		auto thisFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> lastFrameDuration = thisFrameTime - lastFrameTime;
		float deltaTime = lastFrameDuration.count();

		// For Frame Locking
		step += deltaTime;
		if (step > kWorldSizeX)
		{
			step = kWorldSizeX - step;
		}

		lastFrameTime = thisFrameTime;

		// Process Input
		ProcessInput();

		SetColor(Color::BLACK);
		SDL_RenderClear(m_pRenderer);

		//m_noise->SetOffsetX(step);

		for (int x = 0; x < kWorldSizeX; ++x)
		{
			for (int y = 0; y < kWorldSizeY; ++y)
			{
				float noiseValue = m_noise->CalculateNoiseAtScreenPosition((float)x, (float)y);
				Color::uchar colorValue = static_cast<Color::uchar>(noiseValue * 255);
				Color color = { colorValue, colorValue, colorValue, 255 };
				SetColor(color);
				SDL_RenderDrawPoint(m_pRenderer, x, y);				
			}
		}

		// Present the everything rendered to the screen
		SDL_RenderPresent(m_pRenderer);
	}
}


void Engine::SetColor(const Color& color)
{
	SDL_SetRenderDrawColor(m_pRenderer, color.R, color.G, color.B, color.A);
}

void Engine::ProcessInput()
{
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			m_shouldQuit = true;
			return;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			ProcessKeyboardEvent(&evt.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			ProcessMouseEvent(&evt.button);
		default:
			break;
		}
	}
}

void Engine::ProcessKeyboardEvent(SDL_KeyboardEvent* evt)
{
	//std::cout << std::endl;
	//std::cout << "Scancode: " << evt->keysym.scancode << std::endl;
	//std::cout << "Keycode: " << evt->keysym.sym << std::endl;
	//std::cout << "Key modifier Mask: " << evt->keysym.mod << std::endl;
	//std::cout << "State: " << (int)evt->state << std::endl;
	//std::cout << "Repeat?: " << (int)evt->repeat << std::endl;
	//std::cout << "Timestamp: " << evt->timestamp << std::endl;

	switch (evt->keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		m_shouldQuit = true;
		break;
	case SDL_SCANCODE_SPACE:
		break;
	}
}

void Engine::ProcessMouseEvent(SDL_MouseButtonEvent* evt)
{
	//std::cout << std::endl;
	//std::cout << "Button: " << (int)evt->button << std::endl;
	//std::cout << "Click count: " << (int)evt->clicks << std::endl;
	//std::cout << "State: " << (int)evt->state << std::endl;
	//std::cout << "Timestamp: " << evt->timestamp << std::endl;
	//std::cout << "X: " << evt->x << std::endl;
	//std::cout << "Y: " << evt->y << std::endl;
}

