#ifndef _CSOUNDBANK_H_
    #define _CSOUNDBANK_H_
 
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
 
class CSoundBank {
    public:
        static CSoundBank           SoundControl;//declare it static
 
        std::vector<Mix_Chunk*>     SoundList;//vector of sounds
 
    public:
        CSoundBank();//constructer
 
        int OnLoad(char* File);//load the sound
 
        void OnCleanup();//clean the sounds up
 
    public:
        void Play(int channel, int ID, int playCount);//play the sound
};
 
#endif
