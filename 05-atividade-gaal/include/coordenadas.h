void cartesiano_para_cilindrico(double x, double y, double z, double *rho_out, double *theta_out, double *z_out);

void cilindrico_para_cartesiano(double rho, double theta, double z, double *x_out, double *y_out, double *z_out);

void cartesiano_para_esferico_math(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out);

void cartesiano_para_esferico_phys(double x, double y, double z, double *rho_out, double *theta_out, double *phi_out);

void esferico_para_cartesiano(double rho, double theta, double phi, double *x_out, double *y_out, double *z_out);