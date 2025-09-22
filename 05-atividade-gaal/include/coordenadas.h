#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Definições para a interface gráfica
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define INPUT_FIELD_WIDTH 150
#define INPUT_FIELD_HEIGHT 30
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40

// Estrutura para campos de entrada
typedef struct {
    SDL_Rect rect;
    char text[32];
    int active;
    int cursor_pos;
} InputField;

// Estrutura para botões
typedef struct {
    SDL_Rect rect;
    char text[64];
    int id;
} Button;

// Estrutura principal da aplicação
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    InputField input_fields[3];
    Button buttons[7];
    int selected_conversion;
    char result_text[256];
    int running;
} App;

// Funções de conversão de coordenadas
void cartesiano_para_cilindrico(double x, double y, double z, double *rho_out, double *theta_out, double *z_out);
void cilindrico_para_cartesiano(double rho, double theta, double z, double *x_out, double *y_out, double *z_out);
void cartesiano_para_esferico_math(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out);
void cartesiano_para_esferico_phys(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out);
void esferico_para_cartesiano(double rho, double theta, double phi, double *x_out, double *y_out, double *z_out);
void cilindrico_para_esferico(double rho, double theta, double z, double *rho_out, double *theta_out, double *phi_out);
void esferico_para_cilindrico(double rho, double theta, double phi, double *rho_out, double *theta_out, double *z_out);

// Funções da interface SDL2
int init_sdl(App *app);
void cleanup_sdl(App *app);
void handle_events(App *app);
void render(App *app);
void render_input_field(App *app, InputField *field, const char *label, int x, int y);
void render_button(App *app, Button *button);
void render_text(App *app, const char *text, int x, int y, SDL_Color color);
void perform_conversion(App *app);
void update_input_field(InputField *field, char c);
void delete_char_input_field(InputField *field);

#endif