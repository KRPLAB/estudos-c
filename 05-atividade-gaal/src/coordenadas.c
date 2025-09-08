#include <math.h>

void cartesiano_para_cilindrico(double x, double y, double z, double *rho_out, double *theta_out, double *z_out){
	*rho_out = sqrt((x*x) + (y*y));
	*theta_out = atan2(y,x);
	*z_out = z;
}

void cilindrico_para_cartesiano(double rho, double theta, double z, double *x_out, double *y_out, double *z_out){
	*x_out = cos(theta) * rho;
	*y_out = sin(theta) * rho;
	*z_out = z;
}

// VERSÃO PADRÃO DA FÍSICA / ISO (versão alternativa)
// Comentário: O uso de atan2 para os dois ângulos
// é a melhor abordagem, pois evita divisão por zero e lida
// corretamente com todos os quadrantes
void cartesiano_para_esferico_phys(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out){
	*rho_out = sqrt((x*x) + (y*y) + (z*z));
	*theta_out = atan2(y,x); // theta (θ) é o ângulo azimutal no plano XY
	*phi_out = atan2(sqrt((x*x) + (y*y)),z); // phi (φ) é o ângulo de inclinação a partir de Z
}

// VERSÃO PADRÃO DA MATEMÁTICA (utilizada aqui)
// A única mudança é a troca de papéis entre theta e phi.
void cartesiano_para_esferico_math(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out){
	*rho_out = sqrt((x*x) + (y*y) + (z*z));
	*phi_out = atan2(y,x);
	*theta_out = atan2(sqrt((x*x) + (y*y)),z);
}

void esferico_para_cartesiano(double rho, double theta, double phi, double *x_out, double *y_out, double *z_out){
	*x_out = cos(theta)*(rho*sin(phi));
	*y_out = sin(theta)*(rho*sin(phi));
	*z_out = cos(phi)*rho;
}

void cilindrico_para_esferico(double rho, double theta, double z, double *rho_out, double *theta_out, double *phi_out){
	*rho_out = sqrt((rho*rho) + (z*z));
	*theta_out = theta;
	*phi_out = atan2(rho,z);
}

void esferico_para_cilindrico(double rho, double theta, double phi, double *rho_out, double *theta_out, double *z_out){
	*rho_out = rho*sin(phi);
	*theta_out = theta;
	*z_out = rho*cos(phi);
}
