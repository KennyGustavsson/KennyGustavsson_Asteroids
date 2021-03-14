#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <SDL_mixer.h>

class Audio 
{
public:
	Audio(const std::string& path, int volume);
	void Play();
	void SetVolume(int volume);

private:
	std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)> chunk;
};

class Music 
{
public:
	Music(const std::string& path, int volume);

	void Play();
	void Play(int loops);
	void Pause();
	void Resume();
	void SetVolume(int volume);

private:
	std::unique_ptr<Mix_Music, void(*)(Mix_Music*)> music;
};