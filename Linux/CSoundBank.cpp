#include "CSoundBank.h"
 
CSoundBank CSoundBank::SoundControl;
 
CSoundBank::CSoundBank() {
}
 
int CSoundBank::OnLoad(char* File) {
    Mix_Chunk* TempSound = NULL;
 
    if((TempSound = Mix_LoadWAV(File)) == NULL) {//load the sound file, if it fails then exit
        return -1;
    }
 
    SoundList.push_back(TempSound);//push the sound back into the list
 
    return (SoundList.size() - 1);//return the ID of the sound
}
 
void CSoundBank::OnCleanup() {
    for(int i = 0;i < SoundList.size();i++) {
        Mix_FreeChunk(SoundList[i]);//free the entire vector
    }
 
    SoundList.clear();//clear the list
}
 
void CSoundBank::Play(int channel, int ID, int playCount) {
    if(ID < 0 || ID >= SoundList.size()) return;//if the sound is out of bounds then exit
    if(SoundList[ID] == NULL) return;//if the sound dosent exist then return
 
    Mix_PlayChannel(channel, SoundList[ID], playCount);//play the sound
}
