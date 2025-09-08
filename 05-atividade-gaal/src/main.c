#include <stdio.h>
#include "../include/coordenadas.h"

int main() {
    // Ponto cartesiano inicial
    double input_x;
    double input_y;
    double input_z;

    // Variáveis para guardar os resultados
    double cil_r, cil_theta, cil_z;
    double esf_rho, esf_theta, esf_phi;

    // Opção escolhida
    int opcao;

    printf("============== Bem Vinde ao Conversor de Coordenadas ==============\n");
    printf("Aqui você pode:\n");
    printf("1. Converter de Cartesiano para Cilíndrico\n");
    printf("2. Converter de Cartesiano para Esférico (Matemática)\n");
    printf("3. Converter de Cartesiano para Esférico (Física)\n");
    printf("4. Converter de Cilíndrico para Cartesiano\n");
    printf("5. Converter de Esférico para Cartesiano\n");

    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);

    printf("Digite as coordenadas do ponto:\n");
    printf("x: ");
    scanf("%lf", &input_x);
    printf("y: ");
    scanf("%lf", &input_y);
    printf("z: ");
    scanf("%lf", &input_z);

    printf("Ponto Cartesiano Original: (x=%.2f, y=%.2f, z=%.2f)\n\n", input_x, input_y, input_z);

    // --- Testando as conversões ---

    // 1. Cartesiano para Cilíndrico
    cartesiano_para_cilindrico(input_x, input_y, input_z, &cil_r, &cil_theta, &cil_z);
    printf("Convertido para Cilíndrico: (r=%.2f, theta=%.2f rad, z=%.2f)\n", cil_r, cil_theta, cil_z);

    // 2. Cartesiano para Esférico
    cartesiano_para_esferico_math(input_x, input_y, input_z, &esf_rho, &esf_theta, &esf_phi);
    printf("Convertido para Esférico: (rho=%.2f, theta=%.2f rad, phi=%.2f rad)\n", esf_rho, esf_theta, esf_phi);
    
    // (Poderíamos adicionar testes para as funções inversas também)

    return 0;
}