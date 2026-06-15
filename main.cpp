#include <iostream>
#include <string>
#include "AVLDictionary.hpp"
#include "OpenAddressHashDictionary.hpp"
#include "RBTreeDictionary.hpp"
#include "ChainedHashDictionary.hpp"
#include "Dictionary.hpp"

int main()
{
    //RBTREE

    std::cout << "Teste - RBTreeDictionary\n";
    std::cout << "-----------------------------\n";

    RBTreeDictionary<std::string, int> rb;

    rb.insert("maria", 10);
    rb.insert("joao", 20);
    rb.insert("ana", 30);
    rb.insert("carlos", 40);

    std::cout << "Tamanho: "
              << rb.size()
              << "\n";

    std::cout << "Contem ana? "
              << rb.contains("ana")
              << "\n";

    std::cout << "Contem pedro? "
              << rb.contains("pedro")
              << "\n";

    std::cout << "Valor de joao: "
              << rb.get("joao")
              << "\n";

    rb.update("joao", 99);

    std::cout << "Novo valor de joao: "
              << rb.get("joao")
              << "\n";

    std::cout << "Insercao duplicada (ana): "
              << rb.insert("ana", 500)
              << "\n";

    rb.remove("carlos");

    std::cout << "Contem carlos? "
              << rb.contains("carlos")
              << "\n";

    std::cout << "\nElementos em ordem:\n";
    rb.printInOrder();

    std::cout << "\nEstrutura vazia? "
              << rb.empty()
              << "\n";

    rb.clear();

    std::cout << "Tamanho apos clear: "
              << rb.size()
              << "\n\n";



    //HASH COM ENCADEAMENTO EXTERIOR

    std::cout << "Teste - ChainedHashDictionary\n";
    std::cout << "-----------------------------\n";

    ChainedHashDictionary<std::string, int> hash;

    hash.insert("livro", 100);
    hash.insert("mesa", 200);
    hash.insert("cadeira", 300);
    hash.insert("janela", 400);

    std::cout << "Tamanho: "
              << hash.size()
              << "\n";

    std::cout << "Contem mesa? "
              << hash.contains("mesa")
              << "\n";

    std::cout << "Contem porta? "
              << hash.contains("porta")
              << "\n";

    std::cout << "Valor de cadeira: "
              << hash.get("cadeira")
              << "\n";

    hash.update("cadeira", 999);

    std::cout << "Novo valor de cadeira: "
              << hash.get("cadeira")
              << "\n";

    std::cout << "Insercao duplicada (mesa): "
              << hash.insert("mesa", 9999)
              << "\n";

    hash.remove("livro");

    std::cout << "Contem livro? "
              << hash.contains("livro")
              << "\n";

    std::cout << "Estrutura vazia? "
              << hash.empty()
              << "\n";

    hash.clear();

    std::cout << "Tamanho apos clear: "
              << hash.size()
              << "\n";

    //TESTE DE POLIMORFISMO

    std::cout << "\nTeste - Polimorfismo\n";
    std::cout << "-----------------------------\n";

    Dictionary<std::string, int>* dict;

    //Usando RBTree

    RBTreeDictionary<std::string, int> rbPoly;

    dict = &rbPoly;

    dict->insert("A", 10);
    dict->insert("B", 20);

    std::cout
        << "RBTree -> tamanho: "
        << dict->size()
        << "\n";

    std::cout
        << "RBTree -> valor de A: "
        << dict->get("A")
        << "\n";

    //Usando Hash

    ChainedHashDictionary<std::string, int> hashPoly;

    dict = &hashPoly;

    dict->insert("X", 100);
    dict->insert("Y", 200);

    std::cout
        << "Hash -> tamanho: "
        << dict->size()
        << "\n";

    std::cout
        << "Hash -> valor de X: "
        << dict->get("X")
        << "\n";


        dict = &rbPoly;

    (*dict)["novo"] = 500;

    std::cout
        << "Valor de novo: "
        << dict->get("novo")
        << "\n";


    dict = &hashPoly;

    (*dict)["teste"] = 999;

    std::cout
        << "Valor de teste: "
        << dict->get("teste")
        << "\n";



    // AVL DICTIONARY

    std::cout << "\nTeste - AVLDictionary\n";
    std::cout << "-----------------------------\n";

    AVLDictionary<std::string, int> avl;

    avl.insert("maria", 10);
    avl.insert("joao", 20);
    avl.insert("ana", 30);
    avl.insert("carlos", 40);

    std::cout << "Tamanho: "
              << avl.size()
              << "\n";

    std::cout << "Contem ana? "
              << avl.contains("ana")
              << "\n";

    std::cout << "Contem pedro? "
              << avl.contains("pedro")
              << "\n";

    std::cout << "Valor de joao: "
              << avl.get("joao")
              << "\n";

    avl.update("joao", 99);

    std::cout << "Novo valor de joao: "
              << avl.get("joao")
              << "\n";

    std::cout << "Insercao duplicada (ana): "
              << avl.insert("ana", 500)
              << "\n";

    avl.remove("carlos");

    std::cout << "Contem carlos? "
              << avl.contains("carlos")
              << "\n";

    std::cout << "Estrutura vazia? "
              << avl.empty()
              << "\n";

    avl.clear();

    std::cout << "Tamanho apos clear: "
              << avl.size()
              << "\n";


    // HASH COM ENDERECAMENTO ABERTO

    std::cout << "\nTeste - OpenAddressHashDictionary\n";
    std::cout << "-----------------------------\n";

    OpenAddressHashDictionary<std::string, int> openHash;

    openHash.insert("livro", 100);
    openHash.insert("mesa", 200);
    openHash.insert("cadeira", 300);
    openHash.insert("janela", 400);

    std::cout << "Tamanho: "
              << openHash.size()
              << "\n";

    std::cout << "Contem mesa? "
              << openHash.contains("mesa")
              << "\n";

    std::cout << "Contem porta? "
              << openHash.contains("porta")
              << "\n";

    std::cout << "Valor de cadeira: "
              << openHash.get("cadeira")
              << "\n";

    openHash.update("cadeira", 999);

    std::cout << "Novo valor de cadeira: "
              << openHash.get("cadeira")
              << "\n";

    std::cout << "Insercao duplicada (mesa): "
              << openHash.insert("mesa", 9999)
              << "\n";

    openHash.remove("livro");

    std::cout << "Contem livro? "
              << openHash.contains("livro")
              << "\n";

    std::cout << "Estrutura vazia? "
              << openHash.empty()
              << "\n";

    openHash.clear();

    std::cout << "Tamanho apos clear: "
              << openHash.size()
              << "\n";


    return 0;
}
