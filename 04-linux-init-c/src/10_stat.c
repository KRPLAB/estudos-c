#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	struct stat st;

	// tenta ler infos do diretorio atual
	if(stat(".", &st) == 0) {
			printf("ID do Proprietario (UID): %d\n", st.st_uid);
			printf("Permissões (em octal): %o\n", st.st_mode & 0777);
	}

	return 0;
}
		
