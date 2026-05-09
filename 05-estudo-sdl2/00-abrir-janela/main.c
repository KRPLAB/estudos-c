#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  // A janela onde tudo será renderizado
  SDL_Window *window = NULL;

  (void)argc;
  (void)argv;
  // A superfície onde a janela é renderizada
  SDL_Surface *screenSurface = NULL;

  // Inicializa a biblioteca SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  // Cria a janela
  window = SDL_CreateWindow("SDL Tutorial - Minha primeira janela",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  } else {
    // Obtém a superfície da janela
    screenSurface = SDL_GetWindowSurface(window);

    // Preenche a superfície de branco
    SDL_FillRect(screenSurface, NULL,
                 SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Atualiza a superfície para mostrar o que foi desenhado
    SDL_UpdateWindowSurface(window);

    // "Hack" (loop de eventos) para manter a janela aberta até o usuário fechar
    SDL_Event e;
    bool quit = false;

    while (!quit) {
      if (SDL_WaitEvent(&e) == 0) {
        printf("SDL_WaitEvent failed! SDL_Error: %s\n", SDL_GetError());
        break;
      }

      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  // Destrói a janela e libera sua memória (isso também cuida da screenSurface)
  SDL_DestroyWindow(window);

  // Encerra os subsistemas da SDL
  SDL_Quit();

  return 0;
}