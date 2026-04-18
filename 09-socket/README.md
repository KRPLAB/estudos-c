# 09-Socket: Servidor HTTP com C

Servidor HTTP minimalista em C, utilizando **sockets TCP** para aceitar conexões HTTP e servir conteúdo HTML estático.

## Arquitetura do Projeto

### Estrutura de Diretórios

```
09-socket/
├── build/                 # Artefatos de compilação (*.o, executáveis)
│   ├── bin/               # Binários compilados (server, client)
│   ├── obj/               # Objetos compilados
│   └── .*.a               # Bibliotecas estáticas intermediárias
│
├── src/                   # Código-fonte da aplicação
│   ├── network/           # Lógica de rede TCP/RAW
│   │   ├── server.c       # Implementação TCP e Raw Socket
│   │   └── Makefile
│   ├── client/            # Biblioteca do cliente HTTP
│   │   ├── client.c       # Funções de cliente HTTP
│   │   └── Makefile
│   └── utils/             # Funções utilitárias
│       ├── utils.c        # Parsing HTTP e tokenização
│       └── Makefile
│
├── include/               # Headers públicos (interfaces)
│   ├── network.h          # Interface de rede (servidor)
│   ├── client.h           # Interface do cliente HTTP
│   ├── utils.h            # Interface de utilitários
│   ├── common.h           # Definições compartilhadas
│   └── mime_types.h       # Tipos MIME
│
├── cmd/                   # Executáveis e pontos de entrada
│   ├── server/            # Servidor HTTP/Raw
│   │   ├── main.c         # Ponto de entrada do servidor
│   │   └── Makefile
│   └── client/            # Cliente HTTP
│       ├── main.c         # Ponto de entrada do cliente
│       └── Makefile
│
├── test/                  # Testes unitários
│       (Preparado para testes futuros)
│
├── assets/                # Recursos estáticos
│   ├── html/              # Páginas HTML servidas
│   │   ├── index.html     # Página principal
│   │   └── erro.html      # Página de erro
│   └── docs/              # Documentação estática
│
├── config/                # Configurações de build
│   └── config.mk          # Variáveis compartilhadas (CC, CFLAGS, etc)
│
├── Makefile               # Makefile principal (coordenador)
├── README.md              # Este arquivo
└── .gitignore             # Git: ignora build artifacts
```

---

## Convenções de Nomenclatura

| Diretório | Origem/Padrão | Função | Justificativa |
|-----------|---------------|--------|---------------|
| **build/** | Linux/GNU | Saída de compilação | Separação entre fonte e build (convenção universal) |
| **src/** | POSIX/C | Código-fonte |  Convenção padrão em projetos C (ex: Linux Kernel) |
| **include/** | C POSIX | Headers públicos | Separação de interface (*.h) do código (*.c) |
| **cmd/** | Go/Rust | Executáveis | Indica "comandos" executáveis vs bibliotecas |
| **test/** | JUnit/pytest | Testes | Diretório separado por tipo de artifacts |
| **assets/** | Web/UI | Recursos estáticos | HTML, CSS, imagens que a aplicação serve |
| **config/** | Docker/K8s | Configurações | Centralização de settings de build |

### Embasamento

- **`build/`**: Padrão do **CMake**, **Autotools**, **Meson**. Mantém o source tree limpo.
- **`src/`**: Convenção do **Linux Kernel** (`kernel/`, `fs/`, `net/`, etc). Separa interface de implementação.
- **`cmd/`**: Padrão de linguagens compiladas modernas (**Go**, **Rust**). Um diretório por executável.
- **`test/`**: Conformidade com **xUnit** — testes isolados do código produção.
- **`assets/`**: Explorado em projetos **web** e **mobile**. Recursos não-compilados.

---

## Compilação

### Compilar tudo
```bash
make build
# ou
make all
```

### Executar servidor
```bash
make run
```

### Usar cliente HTTP

#### Exibir ajuda
```bash
./build/bin/client --help
```

#### Conectar ao servidor em localhost:8080
```bash
./build/bin/client -h 127.0.0.1 -p 8080 -r /
```

#### Customizar requisição
```bash
./build/bin/client -h 192.168.1.100 -p 9000 -r /index.html
```

#### Teste em dois terminais
```bash
# Terminal 1 - Servidor
make run
# Saída: [TCP] Servidor aguardando conexões na porta 8080...

# Terminal 2 - Cliente
./build/bin/client -h 127.0.0.1 -p 8080 -r /
# Exibe resposta HTTP 200 OK com conteúdo do index.html
```

### Limpar artefatos
```bash
make clean
```

### Ver comandos disponíveis
```bash
make help
```

---

## Fluxo de Compilação

```
┌─ Makefile (raiz)
│
├─► make src/network           → .network.a
├─► make src/utils             → .utils.a
├─► make src/client            → .client.a
├─► make cmd/server            → server (usa network + utils)
│   │
│   ├─ server.o (cmd/server/main.c)
│   ├─ .network.a
│   └─ .utils.a
│
└─► make cmd/client            → client (usa client)
    │
    ├─ client.o (cmd/client/main.c)
    └─ .client.a
         │
         └─ client.c (src/client/client.c)
```

**Arquivo final**: `build/bin/server` + `build/bin/client`


---

## Estrutura Detalhada

### `include/` - Interfaces Públicas
```c
// network.h - Interface de rede
int net_tcp_setup(net_ctx_t *ctx, int port);
void net_tcp_run(net_ctx_t *ctx, ...);
int net_raw_run();

// common.h - Definições compartilhadas
enum method { GET, POST, PUT, PATCH, DELETE, UNKNOWN };

// utils.h - Utilitários
char *tokenize(char *str, const char *delimiters);
int identify_method(const char *first_line);
```

### `src/network/` - Implementação de Rede
- `server.c`: Setup TCP, loop principal, parsing HTTP, raw sockets

### `src/utils/` - Utilidades
- `utils.c`: Tokenização de strings, identificação de métodos HTTP

### `src/client/` - Biblioteca de Cliente HTTP
- `client.c`: Funções para conectar, enviar GET, receber resposta

### `cmd/server/` - Executável Servidor
- `main.c`: Ponto de entrada, argumentos (`tcp|raw`), inicialização

### `cmd/client/` - Executável Cliente HTTP
- `main.c`: Ponto de entrada, parse de argumentos (-h, -p, -r), execução

### `include/client.h` - Interface de Cliente
```c
// Cliente HTTP
int client_http_connect(client_ctx_t *ctx, const char *host, int port);
int client_http_send_get(client_ctx_t *ctx, const char *path, const char *host);
int client_http_recv(client_ctx_t *ctx, char *buffer, int buffer_size);
int client_http_close(client_ctx_t *ctx);
```

### `assets/html/` - Conteúdo Servido
- `index.html`: Página principal (HTTP 200)
- `erro.html`: Página de erro (HTTP 404)

---

## Benefícios considerados para utilizar essa arquitetura

- **Escalabilidade**: Fácil adicionar novos módulos em `src/`  
- **Clareza**: Separação clara entre interface (`include/`) e implementação (`src/`)  
- **Build limpo**: Artefatos isolados em `build/`  
- **Padrão industrial**: Segue convenções da indústria (Linux, GNU, Go)  
- **Manutenibilidade**: Mudanças no build (config.mk) propagam globalmente  
- **Testabilidade**: Espaço dedicado para testes (`test/`)  

---

## Próximos Passos

- [x] Arquitetura modular (server + client)
- [ ] Expandir suporte HTTP (POST, PUT, DELETE no cliente)
- [ ] Melhorar tratamento de erros (timeout, retry)
- [ ] Suporte a múltiplas conexões simultâneas
- [ ] Documentação técnica em `assets/docs/`
- [ ] Testes unitários em `test/`


---

## Notas

Este projeto demonstra **boas práticas de organização** em C, aplicáveis a servidores, bibliotecas e aplicações desktop.

Para modificar configurações globais de compilação:
```makefile
# Edit config/config.mk
CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -std=c11 -I$(INCLUDE_DIR)
LDFLAGS = -lm
```

---

**Autor**: Kauan da Rosa Paulino  
**Data**: Abril 2026
