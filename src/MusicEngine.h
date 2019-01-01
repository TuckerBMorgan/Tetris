#pragma once
#include <string>
#include <unordered_map>

#include <SDL_mixer.h>

#define DEFAULT_NUMBER_OF_LOADED_SONGS 10
#define LOADED_MUSIC_ARRAY_EXPANSION 5

typedef int SongId;

class MusicEngine {
    public:
        void init();
        SongId loadSong(std::string path);
        void playMusic(SongId song_id);
        void pauseCurrentMusic();
        void resumeMusic();
        bool getIsPlaying();

    private:
        int number_of_loaded_songs;
        bool is_playing;
        Mix_Music** loaded_music;
        int music_counter;
};