#include <SDL_mixer.h>
#include <stdint.h>
#include "MusicEngine.h"
#include <math.h>

//an experiment
void musicProvider(void* udata, uint8_t* stream, int len) {
    int i, pos=*(int*)udata;

    // fill buffer with...uh...music...
    for(i=0; i<len; i++)
        stream[i]=(i) * (cos(pos * 10.f) + 1.0);
    // set udata for next time
    pos+=len;
    *(int*)udata=pos;
}

void MusicEngine::init() {
    this->music_counter = 0;
    this->is_playing = false;
    this->number_of_loaded_songs = 0;
    this->loaded_music = new Mix_Music*[DEFAULT_NUMBER_OF_LOADED_SONGS];
  //  Mix_HookMusic(musicProvider, &music_counter);
}

SongId MusicEngine::loadSong(std::string path) {

    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(!music) {
        printf("There was an error loading song %s Error %s", path.c_str(), Mix_GetError());
        return -1;
    }

    if(this->number_of_loaded_songs > DEFAULT_NUMBER_OF_LOADED_SONGS) {
        //need to resize the array
        Mix_Music** new_array = new Mix_Music*[this->number_of_loaded_songs + LOADED_MUSIC_ARRAY_EXPANSION];
        Mix_Music** old_array = this->loaded_music;
        this->loaded_music = new_array;
        delete old_array;
    }

    this->loaded_music[this->number_of_loaded_songs] = music;
    int return_value = this->number_of_loaded_songs;
    this->number_of_loaded_songs+=1;
    return return_value;
}

void MusicEngine::playMusic(SongId song_id) {
    if(song_id >= this->number_of_loaded_songs) {
        return;
    }
    Mix_Music* song_to_play = this->loaded_music[song_id];
    Mix_PlayMusic(song_to_play, -1);
    Mix_VolumeMusic(1);
    this->is_playing = true;
}

void MusicEngine::resumeMusic() {
    Mix_ResumeMusic();
    this->is_playing = true;
}

void MusicEngine::pauseCurrentMusic() {
    Mix_PauseMusic();
    this->is_playing = false;
}

bool MusicEngine::getIsPlaying() {
    return this->is_playing;
}