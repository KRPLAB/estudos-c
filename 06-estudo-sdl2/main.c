#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Variáveis para a nossa janela e renderer
    SDL_Window* window = NULL;

    // Inicializa o SDL. Se der erro, ele avisa.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL não pôde ser inicializado! Erro: %s\n", SDL_GetError());
        return 1;
    }

    // Cria a janela
    window = SDL_CreateWindow(
        "Minha Janela SDL",             // Título da janela
        SDL_WINDOWPOS_UNDEFINED,      // Posição x inicial
        SDL_WINDOWPOS_UNDEFINED,      // Posição y inicial
        640,                          // Largura em pixels
        480,                          // Altura em pixels
        SDL_WINDOW_SHOWN              // Flags da janela
    );

    // Se a janela não foi criada, avisa o erro.
    if (window == NULL) {
        printf("A janela não pôde ser criada! Erro: %s\n", SDL_GetError());
        return 1;
    }

    // Mantém a janela aberta por 3 segundos (3000 milissegundos)
    SDL_Delay(3000);

    // Destrói a janela e libera a memória
    SDL_DestroyWindow(window);

    // Encerra o SDL
    SDL_Quit();

    return 0;
}