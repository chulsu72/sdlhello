#include "SDL.h"


// [important] 
// origin auth   : Ryan C. Gordon (https://www.youtube.com/@RyanGordon)  
// origin yutubu : Writing a simple media player with SDL, part 1 (https://www.youtube.com/watch?v=6hIaEHzlmFc)
// origin source : https://github.com/icculus/sdlamp/blob/7527bbffbf20224be204b32cf4632e3368016209/sdlamp.c  
// 
// HOW TO COMFILE (GCC) : gcc sdlamp.c -o sdlamp -I /usr/include/SDL2/ -lSDL2
// HOW TO COMFILE (FTE) : fte ./sdlamp 실행 => LANG=C gcc .... ( 위에 yutubu 중간에 fte 의 tools 메뉴의 comfile.. 하는 법이 살짝 나옴 ) 


static SDL_AudioDeviceID audio_device = 0 ;

int main(int argc, char **argv)
{

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  SDL_AudioSpec wavspec;
  Uint8 *wavbuf = NULL;
  Uint32 wavlen = 0;

  if(SDL_LoadWAV("music.wav", &wavspec, &wavbuf, &wavlen) == NULL) {
  
    fprintf(stderr, "Uhoh, couldn't load wav file! %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

#if 0
  SDL_zero(desired);
  desired.freq = 48000;
  desired.format = AUDIO_F32;
  desired.samples = 4096;
  desired.callback = NULL;
#endif

  audio_device = SDL_OpenAudioDevice(NULL, 0, &wavspec, NULL, 0);

  SDL_QueueAudio(audio_device, wavbuf, wavlen);
  SDL_FreeWAV(wavbuf);

  SDL_PauseAudioDevice(audio_device, 0);

  SDL_Delay(5000);

  SDL_CloseAudioDevice(audio_device);
  SDL_Quit();

  return 0;

}
