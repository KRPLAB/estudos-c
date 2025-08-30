#include <math.h>

void cartesiano_para_cilindrico(double x, double y, double z, double *r_out, double *theta_out, double *z_out){
	*r_out = sqrt((x*x) + (y*y));
	*theta_out = atan2(y,x);
	*z_out = z;
}

void cilindrico_para_cartesiano(double r, double theta, double z, double *x_out, double *y_out, double *z_out){                                                              *x_out = cos(theta) * r;
	*y_out = sin(theta) * r;
	*z_out = z;
}
