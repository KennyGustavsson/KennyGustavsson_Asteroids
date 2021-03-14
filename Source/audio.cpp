#include "Audio.h"

/// <summary>
/// Audio is used to play sound effects.
/// </summary>
/// <param name="path"></param>
/// <param name="volume"></param>
Audio::Audio(const std::string& path, int volume) : chunk(Mix_LoadWAV(path.c_str()), Mix_FreeChunk)
{
	if (!chunk.get()) {
		std::cout << "Could not load audio with path: " << path << std::endl;
		std::cout << Mix_GetError() << std::endl;

		return;
	}

	Mix_VolumeChunk(chunk.get(), volume);
}

/// <summary>
/// Play the sound effect.
/// </summary>
void Audio::Play()
{
	Mix_PlayChannel(-1, chunk.get(), 0);
}

/// <summary>
/// Set the volume of the sound effect.
/// </summary>
/// <param name="volume"></param>
void Audio::SetVolume(int volume)
{
	Mix_VolumeChunk(chunk.get(), volume);
}

/// <summary>
/// Music is used to play a music file.
/// </summary>
/// <param name="path"></param>
/// <param name="volume"></param>
Music::Music(const std::string& path, int volume) : music(Mix_LoadMUS(path.c_str()), Mix_FreeMusic)
{
	if (!music.get()) {
		std::cout << "Could not load music with path: " << path << std::endl;
		std::cout << Mix_GetError() << std::endl;

		return;
	}
	Mix_VolumeMusic(volume);
}

/// <summary>
/// Plays the music
/// </summary>
void Music::Play()
{
	Mix_PlayMusic(music.get(), -1);
}

/// <summary>
/// Plays the music with a certain amout of loops
/// </summary>
/// <param name="loops"></param>
void Music::Play(int loops)
{
	Mix_PlayMusic(music.get(), loops);
}

/// <summary>
/// Pauses the music
/// </summary>
void Music::Pause()
{
	Mix_PauseMusic();
}

/// <summary>
/// Resumes the music
/// </summary>
void Music::Resume()
{
	Mix_ResumeMusic();
}

/// <summary>
/// Sets the volume of the music
/// </summary>
/// <param name="volume"></param>
void Music::SetVolume(int volume)
{
	Mix_VolumeMusic(volume);
}