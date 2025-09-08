#include <stdio.h>
#include "../include/coordenadas.h"

void gerenciar_conversao(int opcao, double x, double y, double z,
                        double *cil_r, double *cil_theta, double *cil_z,
                        double *esf_rho, double *esf_theta, double *esf_phi) {
    switch (opcao) {
        case 1:
            cartesiano_para_cilindrico(x, y, z, cil_r, cil_theta, cil_z);
            printf("Coordenadas Cilíndricas: (r=%.2f, θ=%.2f rad, z=%.2f)\n", *cil_r, *cil_theta, *cil_z);
            break;
        case 2:
            cartesiano_para_esferico_math(x, y, z, esf_rho, esf_theta, esf_phi);
            printf("Coordenadas Esféricas (Matemática): (ρ=%.2f, θ=%.2f rad, φ=%.2f rad)\n", *esf_rho, *esf_theta, *esf_phi);
            break;
        case 3:
            cartesiano_para_esferico_phys(x, y, z, esf_rho, esf_theta, esf_phi);
            printf("Coordenadas Esféricas (Física): (ρ=%.2f, θ=%.2f rad, φ=%.2f rad)\n", *esf_rho, *esf_theta, *esf_phi);
            break;
        case 4:
            cilindrico_para_cartesiano(x, y, z, cil_r, cil_theta, cil_z);
            printf("Coordenadas Cartesianas: (x=%.2f, y=%.2f, z=%.2f)\n", *cil_r, *cil_theta, *cil_z);
            break;
        case 5:
            esferico_para_cartesiano(x, y, z, esf_rho, esf_theta, esf_phi);
            printf("Coordenadas Cartesianas: (x=%.2f, y=%.2f, z=%.2f)\n", *esf_rho, *esf_theta, *esf_phi);
            break;
        case 6:
            cilindrico_para_esferico(x, y, z, cil_r, cil_theta, cil_z);
            printf("Coordenadas Esféricas: (ρ=%.2f, θ=%.2f rad, φ=%.2f rad)\n", *cil_r, *cil_theta, *cil_z);
            break;
        case 7:
            esferico_para_cilindrico(x, y, z, esf_rho, esf_theta, esf_phi);
            printf("Coordenadas Cilíndricas: (r=%.2f, θ=%.2f rad, z=%.2f)\n", *esf_rho, *esf_theta, *esf_phi);
            break;
        default:
            printf("Opção inválida. Por favor, escolha uma opção entre 1 e 7.\n");
            break;
    }
}

int main() {
    // Ponto cartesiano inicial
    double input_x;
    double input_y;
    double input_z;

    // Variáveis para guardar os resultados
    double cil_r, cil_theta, cil_z;
    double esf_rho, esf_theta, esf_phi;

    // Variável para a opção do usuário
    int opcao;

    printf("============== Bem Vinde ao Conversor de Coordenadas ==============\n");
    printf("Aqui você pode:\n");
    printf("1. Converter de Cartesiano para Cilíndrico\n");
    printf("2. Converter de Cartesiano para Esférico (Matemática)\n");
    printf("3. Converter de Cartesiano para Esférico (Física)\n");
    printf("4. Converter de Cilíndrico para Cartesiano\n");
    printf("5. Converter de Esférico para Cartesiano\n");
    printf("6. Converter de Cilíndrico para Esférico\n");
    printf("7. Converter de Esférico para Cilíndrico\n");

    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);

    printf("Digite as coordenadas do ponto:\n");
    printf("coord_1: ");
    scanf("%lf", &input_x);
    printf("coord_2: ");
    scanf("%lf", &input_y);
    printf("coord_3: ");
    scanf("%lf", &input_z);

    printf("Ponto Cartesiano Original: (coord_1=%.2f, coord_2=%.2f, coord_3=%.2f)\n\n", input_x, input_y, input_z);

    gerenciar_conversao(opcao, input_x, input_y, input_z,
                        &cil_r, &cil_theta, &cil_z,
                        &esf_rho, &esf_theta, &esf_phi);

    printf("========================= Fim do programa =========================\n");
    return 0;
}