#!/bin/bash

echo "=== Teste do Conversor de Coordenadas ==="
echo ""

echo "1. Testando versão console..."
echo "1
1.0
2.0
3.0" | ./gaal_converter --console

echo ""
echo "2. Verificando se o executável gráfico foi criado..."
if [ -f ./gaal_converter ]; then
    echo "✓ Executável gráfico foi criado com sucesso!"
    echo ""
    echo "3. Para testar a versão gráfica, execute:"
    echo "   ./gaal_converter"
    echo ""
    echo "   Ou se preferir a versão console:"
    echo "   ./gaal_converter --console"
else
    echo "✗ Erro: Executável não foi criado"
fi
