===============================================================
TRABALHO FINAL - ESTRUTURAS DE DADOS
CONTADOR DE FREQUÊNCIA DE PALAVRAS
README - INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO NO LINUX MINT
===============================================================

1. DESCRIÇÃO DO PROJETO
----------------------

Este projeto implementa um sistema de contagem de frequência de palavras
utilizando quatro diferentes estruturas de dados:

    - Árvore AVL completamente iterativa;
    - Árvore Rubro-Negra completamente iterativa;
    - Tabela Hash com Encadeamento Exterior;
    - Tabela Hash com Endereçamento Aberto.

O programa realiza a leitura de um arquivo texto, processa e normaliza
as palavras, constrói um dicionário de frequências utilizando a
estrutura escolhida pelo usuário e gera arquivos contendo o vocabulário
processado e as métricas experimentais obtidas durante a execução.

===============================================================

2. REQUISITOS DO SISTEMA
------------------------

O projeto foi desenvolvido em linguagem C++ utilizando exclusivamente
bibliotecas padrão da linguagem.

Compilador necessário:
    - g++ com suporte ao padrão C++17 ou superior.

Para verificar se o compilador está instalado, execute:

    g++ --version

Caso o compilador não esteja instalado, execute:

    sudo apt update
    sudo apt install build-essential

O pacote "build-essential" instala:
    - g++
    - gcc
    - make
    - bibliotecas básicas de desenvolvimento

Nenhuma biblioteca adicional externa é necessária.

===============================================================

3. ESTRUTURA DO PROJETO
-----------------------

O projeto deve conter os seguintes arquivos principais:

    main.cpp

    Dictionary.hpp

    AVLNode.hpp
    AVLDictionary.hpp
    AVLDictionary.tpp

    RBNode.hpp
    RBTreeDictionary.hpp
    RBTreeDictionary.tpp

    ChainHashNode.hpp
    ChainedHashDictionary.hpp
    ChainedHashDictionary.tpp

    OpenAddressHashDictionary.hpp
    OpenAddressHashDictionary.tpp

    TextProcessor.hpp
    TextProcessor.cpp

    FrequencyCounter.hpp
    FrequencyCounter.tpp

    CSVExporter.hpp
    CSVExporter.tpp

Além do arquivo texto que será utilizado como entrada.

===============================================================

4. COMPILAÇÃO
-------------

Abra um terminal dentro da pasta do projeto e execute:

    g++ -std=c++17 -O2 \
        main.cpp \
        TextProcessor.cpp \
        -o freq

Caso a compilação ocorra corretamente, será gerado o executável:

    freq

===============================================================

5. EXECUÇÃO
-----------

A execução do programa segue o formato:

    ./freq <estrutura> <arquivo>

Onde:

    <estrutura> pode assumir os valores:

        rbtree
        avl
        chained
        open

    <arquivo> corresponde ao arquivo texto a ser processado.

Exemplos:

    ./freq rbtree livro.txt

    ./freq avl livro.txt

    ./freq chained livro.txt

    ./freq open livro.txt

===============================================================

6. AJUDA
--------

O programa possui um sistema interno de ajuda.

Para visualizar as estruturas disponíveis execute:

    ./freq --help

ou

    ./freq help

A saída exibida será semelhante a:

    Uso:

    ./freq rbtree livro.txt
    ./freq chained livro.txt
    ./freq avl livro.txt
    ./freq open livro.txt

    Estruturas disponíveis:

      rbtree  (Árvore Rubro-Negra)
      chained (Hash de Encadeamento Externo)
      avl     (Árvore AVL)
      open    (Hash Endereçamento Aberto)

===============================================================

7. ARQUIVOS GERADOS
-------------------

Durante a execução, o programa gera automaticamente:

    vocabulario.csv

Arquivo contendo:

    palavra;frequência

ordenado alfabeticamente.

Também é gerado:

    results.csv

Arquivo contendo as métricas experimentais coletadas
durante cada execução.

Exemplo:

    rbtree,10170,202,4163531,6268,24300
    avl,10170,229,184934,7523
    chained,10170,281,10614213,10069,100.693,130
    open,10170,96,290806,91741,0.46415

===============================================================

8. MÉTRICAS COLETADAS
---------------------

Dependendo da estrutura utilizada, o programa coleta:

    - Número de palavras distintas;
    - Tempo de construção;
    - Número de comparações;
    - Número de rotações;
    - Número de recolorações;
    - Número de colisões;
    - Fator de carga;
    - Maior cadeia.

===============================================================

9. OBSERVAÇÕES
--------------

- O programa foi implementado utilizando apenas técnicas iterativas,
  não empregando recursão nas estruturas AVL e Rubro-Negra.

- O arquivo de entrada deve ser um arquivo texto (.txt)
  codificado preferencialmente em UTF-8.

- Caso o arquivo não exista ou esteja vazio,
  o programa encerrará exibindo a mensagem:

        Arquivo vazio ou inexistente.

===============================================================
FIM DO README
===============================================================