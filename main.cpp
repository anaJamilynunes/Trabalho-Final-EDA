#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>

#include "TextProcessor.hpp"
#include "FrequencyCounter.hpp"

#include "rbtreeDictionary.hpp"
#include "chainedHashDictionary.hpp"

using namespace std;

int main(int argc, char* argv[])
{

//HELP

    if(argc == 2)
    {
        string arg = argv[1];

        if(arg == "--help" || arg == "help")
        {
            cout << "Uso:\n\n";

            cout << ".\\freq.exe rbtree livro.txt\n";
            cout << ".\\freq.exe rbtree testePontuacao.txt\n";
            cout << ".\\freq.exe rbtree testeHifen.txt\n";
            cout << ".\\freq.exe chained livro.txt\n";
            cout << ".\\freq.exe chained testePontuacao.txt\n";
            cout << ".\\freq.exe chained testeHifen.txt\n";

            cout << "Estrturas disponíveis:\n";
            cout << "  rbtree\n";
            cout << "  chained\n\n";

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

    vector<string> words =
        TextProcessor::extractWords(
            filename);

    if(words.empty())
    {
        cout << "Arquivo vazio ou inexistente.\n";
        return 1;
    }

    cout << "\nTOTAL EXTRAIDO = "
         << words.size()
         << endl;

    cout << "\nPALAVRAS EXTRAIDAS:\n";

    for(auto& w : words)
    {
        cout << "[" << w << "]\n";
    }

    // ARQUIVO DE RESULTADOS

    ofstream out(
        "results.csv",
        ios::app
    );

    // RBTREE

    if(structure == "rbtree")
    {
        RBTreeDictionary<
            string,
            int
        > dictionary;

        auto start =
            chrono::high_resolution_clock::now();

        FrequencyCounter<
            RBTreeDictionary<
                string,
                int
            >
        >::build(
            dictionary,
            words);

        auto end =
            chrono::high_resolution_clock::now();

        auto duration =
            chrono::duration_cast
            <
                chrono::milliseconds
            >(end - start);

        cout << "\nRBTree criada.\n";

        cout << "\n===== ESTATISTICAS RBTREE =====\n";

        cout << "Palavras distintas: "
             << dictionary.size()
             << endl;

        cout << "Tempo: "
             << duration.count()
             << " ms\n";

        cout << "Comparacoes: "
             << dictionary.getComparisons()
             << endl;

        cout << "Rotacoes: "
             << dictionary.getRotations()
             << endl;

        cout << "Recoloracoes: "
             << dictionary.getRecolorings()
             << endl;

        out
            << "rbtree,"
            << dictionary.size() << ","
            << duration.count() << ","
            << dictionary.getComparisons() << ","
            << dictionary.getRotations() << ","
            << dictionary.getRecolorings()
            << "\n";

        cout << "\nVOCABULARIO:\n";
        dictionary.printVocabulary();
    }

    // HASH ENCADEADA


    else if(structure == "chained")
    {
        ChainedHashDictionary<
            string,
            int
        > dictionary;

        auto start =
            chrono::high_resolution_clock::now();

        FrequencyCounter<
            ChainedHashDictionary<
                string,
                int
            >
        >::build(
            dictionary,
            words);

        auto end =
            chrono::high_resolution_clock::now();

        auto duration =
            chrono::duration_cast
            <
                chrono::milliseconds
            >(end - start);

        cout << "\nHash criada.\n";

        cout << "\n===== ESTATISTICAS HASH =====\n";

        cout << "Palavras distintas: "
             << dictionary.size()
             << endl;

        cout << "Tempo: "
             << duration.count()
             << " ms\n";

        cout << "Comparacoes: "
             << dictionary.getComparisons()
             << endl;

        cout << "Colisoes: "
             << dictionary.getCollisions()
             << endl;

        cout << "Load Factor: "
             << dictionary.getLoadFactor()
             << endl;

        cout << "Maior cadeia: "
             << dictionary.getLargestChain()
             << endl;

        out
            << "chained,"
            << dictionary.size() << ","
            << duration.count() << ","
            << dictionary.getComparisons() << ","
            << dictionary.getCollisions() << ","
            << dictionary.getLoadFactor() << ","
            << dictionary.getLargestChain()
            << "\n";
        
        cout << "\nVOCABULARIO:\n";
        dictionary.printVocabulary();
    }

    else
    {
        cout << "Estrutura invalida.\n";
        return 1;
    }

    out.close();

}