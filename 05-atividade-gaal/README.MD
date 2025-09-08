# Projeto: Conversor de Coordenadas Geométricas

**Autor:** Kauan da Rosa Paulino
**Disciplina:** Geometria Analítica e Álgebra Linear

## Descrição

Este projeto é uma ferramenta de linha de comando desenvolvida em C que realiza a conversão de coordenadas entre os sistemas Cartesiano, Cilíndrico e Esférico. O programa demonstra a aplicação prática de conceitos de trigonometria e vetores.

---

## Como Compilar e Executar

Existem duas maneiras de compilar o projeto, dependendo do sistema operacional.

### Em Linux ou macOS (Método Recomendado)

O projeto contém um `Makefile` que automatiza todo o processo.

1.  **Abra o terminal** na pasta raiz do projeto.
2.  **Para compilar**, execute o comando:
    ```bash
    make
    ```
    Isso criará um arquivo executável chamado `gaal_converter`.

3.  **Para executar o programa**, use o seguinte comando:
    ```bash
    ./gaal_converter
    ```

4.  **(Opcional) Para limpar** os arquivos gerados pela compilação, execute:
    ```bash
    make clean
    ```

### Em Windows

O Windows não possui a ferramenta `make` nativamente. Para compilar, será necessário usar o compilador `gcc` (que pode ser instalado através do MinGW ou TDM-GCC) diretamente pelo terminal (CMD ou PowerShell).

1.  **Abra o terminal** na pasta raiz do projeto.
2.  **Execute o seguinte comando de compilação**:
    ```bash
    gcc src\main.c src\coordenadas.c -Iinclude -o gaal_converter.exe -lm
    ```
    * `src\main.c src\coordenadas.c`: Nossos arquivos de código-fonte.
    * `-Iinclude`: Informa ao compilador para procurar cabeçalhos na pasta `include`.
    * `-o gaal_converter.exe`: Define o nome do arquivo de saída.
    * `-lm`: Adiciona a biblioteca de matemática.

3.  **Para executar o programa**, use o comando:
    ```bash
    .\gaal_converter.exe
    ```