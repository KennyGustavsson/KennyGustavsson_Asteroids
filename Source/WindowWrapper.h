#pragma once
#include "vector2.h"
#include "SDL.h"
#include <iostream>
#include <vector>

class WindowDimensions
{
public: 
	static int width;
	static int height;	

	static vector2 WrapCoordinates(vector2 position)
	{
		vector2 output = vector2(position.x, position.y);

		if (output.x < 0) {
			output.x = output.x + WindowDimensions::width;
		}
		if (output.x > WindowDimensions::width) {
			output.x = output.x - WindowDimensions::width;
		}

		if (output.y < 0) {
			output.y = output.y + WindowDimensions::height;
		}
		if (output.y > WindowDimensions::height) {
			output.y = output.y - WindowDimensions::height;
		}

		return output;
	}

	static void WrapDraw(vector2 position, SDL_Renderer* renderer, SDL_Color color)
	{
		position = WrapCoordinates(position);
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		SDL_RenderDrawPoint(renderer, position.x, position.y);
	}

	static void WrapDrawLine(vector2 a, vector2 b, SDL_Renderer* renderer, SDL_Color color) 
	{
		float N = DiagonalDistance(a, b);

		for (int i = 0; i <= N; i++)
		{
			float t = (N == 0) ? 0.0 : i / N;
			float x = Lerp(a.x, b.x, t);
			float y = Lerp(a.y, b.y, t);
			WrapDraw(vector2(x, y), renderer, color);
		}
	}

	static float Lerp(float v0, float v1, float t) 
	{
		return (1 - t) * v0 + t * v1;
	}

	static float DiagonalDistance(vector2 a, vector2 b) {
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		return std::max(std::abs(dx), std::abs(dy));
	}

	static void DrawWrapedCircle(SDL_Renderer* renderer, vector2 pos, float radius, int circleResolution, SDL_Color color) {
		float deltaTheta = 6.28318530718 / circleResolution;
		float theta = 0.0f;

		std::vector<vector2> points = std::vector<vector2>(circleResolution);

		for (int i = 0; i < circleResolution; i++) 
		{
			points[i] = vector2(pos.x + (radius * cos(theta)), pos.y + (radius * sin(theta)));
			theta += deltaTheta;
		}

		for (int i = 0; i < circleResolution; i++)
		{
			if(i == circleResolution - 1)
				WrapDrawLine(points[i], points[0], renderer, color);
			else
				WrapDrawLine(points[i], points[i + 1], renderer, color);
		}
	}
};


