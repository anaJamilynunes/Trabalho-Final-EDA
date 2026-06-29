#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

#include "TextProcessor.hpp"
#include "FrequencyCounter.hpp"
#include "Dictionary.hpp"

// O SEU EXPORTADOR COMPONENTE DE AUTORIA DA NOEMI
#include "CSVExporter.hpp"

// Inclusão das estruturas - jamily
#include "rbtreeDictionary.hpp"
#include "chainedHashDictionary.hpp"

// Inclusão das estruturas - noemi
#include "AVLDictionary.hpp"
#include "OpenAddressHashDictionary.hpp"

using namespace std;

int main(int argc, char* argv[])
{

    // HELP

    if(argc == 2)
    {
        string arg = argv[1];

        if(arg == "--help" || arg == "help")
        {
            cout << "Uso:\n\n";

            cout << ".\\freq.exe rbtree livro.txt\n";
            cout << ".\\freq.exe chained livro.txt\n";
            cout << ".\\freq.exe avl livro.txt\n";
            cout << ".\\freq.exe open livro.txt\n";

            cout << "\nEstruturas disponiveis:\n";
            cout << "  rbtree  (Arvore Rubro-Negra)\n";
            cout << "  chained (Hash de Encadeamento Externo)\n";
            cout << "  avl     (Arvore AVL)\n";
            cout << "  open    (Hash Enderecamento Aberto)\n\n";

            return 0;
        }
    }

    // VALIDACAO DOS ARGUMENTOS

    if(argc != 3)
    {
        cout << "\nNumero invalido de argumentos.\n";
        cout << "Digite:\n";
        cout << "    .\\freq.exe --help\n";
        return 1;
    }

    string structure = argv[1];
    string filename  = argv[2];

    // EXTRAÇÃO DAS PALAVRAS

    vector<string> words = TextProcessor::extractWords(filename);

    if(words.empty())
    {
        cout << "Arquivo vazio ou inexistente.\n";
        return 1;
    }

    cout << "\nTOTAL EXTRAIDO = " << words.size() << endl;


    // ARQUIVO DE RESULTADOS GERAIS

    ofstream out("results.csv", ios::app);

    // 1. RBTREE

    if(structure == "rbtree")
    {
        RBTreeDictionary<string, int> dictionary;

        auto start = chrono::high_resolution_clock::now();
        FrequencyCounter<RBTreeDictionary<string, int>>::build(dictionary, words);

        // CHAMADA DO SEU EXPORTADOR: Árvores não precisam ordenar (false)
        CSVExporter<string, int>::exportVocabulary(dictionary, "vocabulario.csv", false);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "\nRBTree criada.\n";
        cout << "\n===== ESTATISTICAS RBTREE =====\n";
        cout << "Palavras distintas: " << dictionary.size() << endl;
        cout << "Tempo: " << duration.count() << " ms\n";
        cout << "Comparacoes: " << dictionary.getComparisons() << endl;
        cout << "Rotacoes: " << dictionary.getRotations() << endl;
        cout << "Recoloracoes: " << dictionary.getRecolorings() << endl;

        out << "rbtree," << dictionary.size() << "," << duration.count() << ","
            << dictionary.getComparisons() << "," << dictionary.getRotations() << ","
            << dictionary.getRecolorings() << "\n";
    }

    // 2. HASH ENCADEADA 

    else if(structure == "chained")
    {
        ChainedHashDictionary<string, int> dictionary;

        auto start = chrono::high_resolution_clock::now();
        FrequencyCounter<ChainedHashDictionary<string, int>>::build(dictionary, words);

        // CHAMADA DO SEU EXPORTADOR: Tabelas Hash precisam ordenar (true)
        CSVExporter<string, int>::exportVocabulary(dictionary, "vocabulario.csv", true);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "\nHash Encadeada criada.\n";
        cout << "\n===== ESTATISTICAS HASH =====\n";
        cout << "Palavras distintas: " << dictionary.size() << endl;
        cout << "Tempo: " << duration.count() << " ms\n";
        cout << "Comparacoes: " << dictionary.getComparisons() << endl;
        cout << "Colisoes: " << dictionary.getCollisions() << endl;
        cout << "Load Factor: " << dictionary.getLoadFactor() << endl;
        cout << "Maior cadeia: " << dictionary.getLargestChain() << endl;

        out << "chained," << dictionary.size() << "," << duration.count() << ","
            << dictionary.getComparisons() << "," << dictionary.getCollisions() << ","
            << dictionary.getLoadFactor() << "," << dictionary.getLargestChain() << "\n";
    }

    // 3. AVL

    else if(structure == "avl")
    {
        AVLDictionary<string, int> dictionary;

        auto start = chrono::high_resolution_clock::now();
        FrequencyCounter<AVLDictionary<string, int>>::build(dictionary, words);

        // CHAMADA DO SEU EXPORTADOR: Árvores não precisam ordenar (false)
        CSVExporter<string, int>::exportVocabulary(dictionary, "vocabulario.csv", false);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

        cout << "\nAVL criada.\n";
        cout << "\n===== ESTATISTICAS AVL =====\n";
        cout << "Palavras distintas: " << dictionary.size() << endl;
        cout << "Tempo: " << duration.count() << " ms\n";
        cout << "Comparacoes: " << dictionary.getComparisons() << endl;
        cout << "Rotacoes: " << dictionary.getRotations() << endl;

        out << "avl," << dictionary.size() << "," << duration.count() << ","
            << dictionary.getComparisons() << "," << dictionary.getRotations() << "\n";
    }

    // 4. HASH ENDEREÇAMENTO ABERTO

    else if(structure == "open")
    {
        OpenAddressHashDictionary<string, int> dictionary;

        auto start = chrono::high_resolution_clock::now();
        FrequencyCounter<OpenAddressHashDictionary<string, int>>::build(dictionary, words);

        // CHAMADA DO SEU EXPORTADOR: Tabelas Hash precisam ordenar (true)
        CSVExporter<string, int>::exportVocabulary(dictionary, "vocabulario.csv", true);

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

       cout << "\nHash Enderecamento Aberto criada.\n";
        cout << "\n===== ESTATISTICAS HASH ABERTA =====\n";
        cout << "Palavras distintas: " << dictionary.size() << endl;
        cout << "Tempo: " << duration.count() << " ms\n";
        cout << "Comparacoes: " << dictionary.getComparisons() << endl;
        cout << "Colisoes: " << dictionary.getCollisions() << endl;      // <-- LINHA NOVA
        cout << "Load Factor: " << dictionary.getLoadFactor() << endl;    // <-- LINHA NOVA

        // Atualizando o salvamento do results.csv adicionando os dois novos dados no final
        out << "open," << dictionary.size() << "," << duration.count() << ","
            << dictionary.getComparisons() << "," << dictionary.getCollisions() << "," 
            << dictionary.getLoadFactor() << "\n";
    }
    else
    {
        cout << "Estrutura invalida.\n";
        return 1;
    }

    out.close();
    return 0;
}
