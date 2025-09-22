#include "../include/coordenadas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int init_sdl(App *app) {
    // Configurar locale para UTF-8
    setlocale(LC_ALL, "C.UTF-8");
    
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erro ao inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    // Criar janela
    app->window = SDL_CreateWindow("Conversor de Coordenadas",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!app->window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    // Criar renderer
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (!app->renderer) {
        printf("Erro ao criar renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(app->window);
        TTF_Quit();
        SDL_Quit();
        return 0;
    }

    // Carregar fonte (usando uma fonte padrão do sistema)
    app->font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16);
    if (!app->font) {
        // Tentar uma fonte alternativa
        app->font = TTF_OpenFont("/usr/share/fonts/TTF/arial.ttf", 16);
        if (!app->font) {
            printf("Erro ao carregar fonte: %s\n", TTF_GetError());
            SDL_DestroyRenderer(app->renderer);
            SDL_DestroyWindow(app->window);
            TTF_Quit();
            SDL_Quit();
            return 0;
        }
    }

    // Inicializar campos de entrada
    for (int i = 0; i < 3; i++) {
        app->input_fields[i].rect.x = 200;
        app->input_fields[i].rect.y = 150 + i * 50;
        app->input_fields[i].rect.w = INPUT_FIELD_WIDTH;
        app->input_fields[i].rect.h = INPUT_FIELD_HEIGHT;
        strcpy(app->input_fields[i].text, "0.0");
        app->input_fields[i].active = 0;
        app->input_fields[i].cursor_pos = 3;
    }

    // Inicializar botões
    const char *button_labels[] = {
        "Cart -> Cilindrico",
        "Cart -> Esferico (Mat)",
        "Cart -> Esferico (Fis)",
        "Cilin -> Cartesiano",
        "Esf -> Cartesiano",
        "Cilin -> Esferico",
        "Esf -> Cilindrico"
    };

    for (int i = 0; i < 7; i++) {
        app->buttons[i].rect.x = 50;
        app->buttons[i].rect.y = 280 + i * 45; 
        app->buttons[i].rect.w = BUTTON_WIDTH;
        app->buttons[i].rect.h = BUTTON_HEIGHT;
        strcpy(app->buttons[i].text, button_labels[i]);
        app->buttons[i].id = i + 1;
    }

    app->selected_conversion = 0;
    strcpy(app->result_text, "Resultado aparecera aqui");
    app->running = 1;

    return 1;
}

void cleanup_sdl(App *app) {
    if (app->font) TTF_CloseFont(app->font);
    if (app->renderer) SDL_DestroyRenderer(app->renderer);
    if (app->window) SDL_DestroyWindow(app->window);
    TTF_Quit();
    SDL_Quit();
}

void handle_events(App *app) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                app->running = 0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mx = e.button.x;
                    int my = e.button.y;

                    // Verificar clique em campos de entrada
                    for (int i = 0; i < 3; i++) {
                        app->input_fields[i].active = 0;
                        if (mx >= app->input_fields[i].rect.x && 
                            mx <= app->input_fields[i].rect.x + app->input_fields[i].rect.w &&
                            my >= app->input_fields[i].rect.y && 
                            my <= app->input_fields[i].rect.y + app->input_fields[i].rect.h) {
                            app->input_fields[i].active = 1;
                        }
                    }

                    // Verificar clique em botões
                    for (int i = 0; i < 7; i++) {
                        if (mx >= app->buttons[i].rect.x && 
                            mx <= app->buttons[i].rect.x + app->buttons[i].rect.w &&
                            my >= app->buttons[i].rect.y && 
                            my <= app->buttons[i].rect.y + app->buttons[i].rect.h) {
                            app->selected_conversion = app->buttons[i].id;
                            perform_conversion(app);
                        }
                    }
                }
                break;

            case SDL_TEXTINPUT:
                for (int i = 0; i < 3; i++) {
                    if (app->input_fields[i].active) {
                        update_input_field(&app->input_fields[i], e.text.text[0]);
                        break;
                    }
                }
                break;

            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    for (int i = 0; i < 3; i++) {
                        if (app->input_fields[i].active) {
                            delete_char_input_field(&app->input_fields[i]);
                            break;
                        }
                    }
                }
                break;
        }
    }
}

void render_text(App *app, const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderText_Solid(app->font, text, color);
    if (surface) {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(app->renderer, surface);
        if (texture) {
            SDL_Rect dest = {x, y, surface->w, surface->h};
            SDL_RenderCopy(app->renderer, texture, NULL, &dest);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

void render_input_field(App *app, InputField *field, const char *label, int x, int y) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};

    // Renderizar label
    render_text(app, label, x, y, white);

    // Renderizar campo
    if (field->active) {
        SDL_SetRenderDrawColor(app->renderer, 100, 150, 255, 255);
    } else {
        SDL_SetRenderDrawColor(app->renderer, 200, 200, 200, 255);
    }
    SDL_RenderFillRect(app->renderer, &field->rect);

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(app->renderer, &field->rect);

    // Renderizar texto
    render_text(app, field->text, field->rect.x + 5, field->rect.y + 5, black);
}

void render_button(App *app, Button *button) {
    SDL_Color white = {255, 255, 255, 255};

    // Renderizar botão
    SDL_SetRenderDrawColor(app->renderer, 70, 130, 180, 255);
    SDL_RenderFillRect(app->renderer, &button->rect);

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(app->renderer, &button->rect);

    // Renderizar texto do botão
    render_text(app, button->text, button->rect.x + 10, button->rect.y + 10, white);
}

void render(App *app) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};

    // Limpar tela
    SDL_SetRenderDrawColor(app->renderer, 30, 30, 30, 255);
    SDL_RenderClear(app->renderer);

    // Título
    render_text(app, "Conversor de Coordenadas 3D", 250, 30, white);

    // Labels e campos de entrada
    const char *labels[] = {"Coordenada 1:", "Coordenada 2:", "Coordenada 3:"};
    for (int i = 0; i < 3; i++) {
        render_input_field(app, &app->input_fields[i], labels[i], 50, 150 + i * 50);
    }

    // Botões
    for (int i = 0; i < 7; i++) {
        render_button(app, &app->buttons[i]);
    }

    // Resultado
    render_text(app, "Resultado:", 300, 300, white);
    render_text(app, app->result_text, 300, 320, yellow);

    // Instruções
    render_text(app, "Clique nos campos para inserir valores", 300, 530, white);
    render_text(app, "Clique nos botoes para converter", 300, 550, white);

    SDL_RenderPresent(app->renderer);
}

void perform_conversion(App *app) {
    double x = atof(app->input_fields[0].text);
    double y = atof(app->input_fields[1].text);
    double z = atof(app->input_fields[2].text);
    
    double result1, result2, result3;

    switch (app->selected_conversion) {
        case 1:
            cartesiano_para_cilindrico(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Cilindrico: r=%.3f, theta=%.3f rad, z=%.3f", result1, result2, result3);
            break;
        case 2:
            cartesiano_para_esferico_math(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Esferico (Mat): rho=%.3f, theta=%.3f rad, phi=%.3f rad", result1, result2, result3);
            break;
        case 3:
            cartesiano_para_esferico_phys(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Esferico (Fis): rho=%.3f, theta=%.3f rad, phi=%.3f rad", result1, result2, result3);
            break;
        case 4:
            cilindrico_para_cartesiano(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Cartesiano: x=%.3f, y=%.3f, z=%.3f", result1, result2, result3);
            break;
        case 5:
            esferico_para_cartesiano(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Cartesiano: x=%.3f, y=%.3f, z=%.3f", result1, result2, result3);
            break;
        case 6:
            cilindrico_para_esferico(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Esferico: rho=%.3f, theta=%.3f rad, phi=%.3f rad", result1, result2, result3);
            break;
        case 7:
            esferico_para_cilindrico(x, y, z, &result1, &result2, &result3);
            snprintf(app->result_text, sizeof(app->result_text),
                    "Cilindrico: r=%.3f, theta=%.3f rad, z=%.3f", result1, result2, result3);
            break;
        default:
            strcpy(app->result_text, "Selecione uma conversao");
            break;
    }
}

void update_input_field(InputField *field, char c) {
    int len = strlen(field->text);
    if (len < 31 && ((c >= '0' && c <= '9') || c == '.' || c == '-')) {
        field->text[len] = c;
        field->text[len + 1] = '\0';
        field->cursor_pos = len + 1;
    }
}

void delete_char_input_field(InputField *field) {
    int len = strlen(field->text);
    if (len > 0) {
        field->text[len - 1] = '\0';
        field->cursor_pos = len - 1;
    }
}