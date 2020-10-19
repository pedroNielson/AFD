#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void verificaFinal(int Final, int nEstF, int EstFim[100], string palAux)
{ // função recebe o estado final, o estado encontrado com a palavra, o vetor de estados finais e a palavra testada
    for (int j = 0; j < nEstF; j++)
    { // verifica se o estado recebido pertence ao vetor de estados finais
        if (Final == EstFim[j])
        {
            cout << "Palavra " << palAux << " aceita!" << endl;
        }
        else
        {
            cout << "Palavra " << palAux << " nao aceita!" << endl;
        }
    }
}

int testeAFD(string palAux, int EstIn, int trans[100][26])
{                              // recebe a palavra a ser testada, o estado inicial e a matriz de transição
    int tam = palAux.length(); // salva o tamanho da palavra para verificação de caracteres
    int next;                  // cria a variavel para mudar de estados
    for (int j = 0; j < tam; j++)
    { // percorre a palavra
        if (palAux[j] != ' ')
        {                                               // verifica se o caracter não é vazio
                                                       
            next = trans[EstIn - 1][(palAux[j] - 'a')]; // salva o proximo estado com o valor encontrado na matriz de transição

            EstIn = next; // muda o estado inicial
                         
        }
    }
    return next;
}

int main()
{
    ifstream arq01;                      //abrindo o arquivo 
    string x, z, y;                      // auxiliares para leitura do arquivo
    int nEst, mSimb, nEstF, nPal, EstIn; // variavei para salvar numero de simbolos, estados, palavras e estado inicial
    int EstFim[100];                     // cria vetor com estados finais
    int trans[100][26];                  // cria a matriz de transição
    vector<string> palavras;             // cria um vetor de string para salvar as palavras

    arq01.open("AFD1.txt"); //abre o aquivo
    if (arq01.is_open())
    {                      //verifica se o arquivo esta aberto
                           
        getline(arq01, x); //pega a primeira linha do aquivo
        getline(arq01, y); //pega a segunda linha do arquivo

        nEst = stoi(x);  //salva a primeira linha com o numero de estados
                        
        mSimb = stoi(y); // salva a segunda linha como o numero de simbolos
                         

        for (int i = 0; i < nEst; i++) // percorre linhas correspondentes as transições
        {
            getline(arq01, x);
            for (int j = 0; j < (mSimb * 2) - 1; j++)
            { // percorre a linha pegando somente o valor do estado de transição
                if (j % 2 == 0)
                {
                    z = x[j];
                    trans[i][j / 2] = stoi(z); // salva transição na posição correspondente do estado
                                               
                }
            }
        }
        getline(arq01, x); // pega a proxima linha após as transiçoes
        EstIn = stoi(x);   // salva valor com estado inicial
                           
        getline(arq01, x);
        nEstF = stoi(x); // salva valor com numero de estados finais
                        
        getline(arq01, y);
        for (int j = 0; j < (nEstF * 2) - 1; j++)
        { // percorre a linha dos estados finais salvanda apenas o valor do estado
            if (j % 2 == 0)
            {
                z = y[j];
                EstFim[j / 2] = stoi(z);
                
            }
        }
        getline(arq01, x);
        nPal = stoi(x); // salva o numero de palvras
                        

        for (int i = 0; i < nPal; i++)
        {
            getline(arq01, x);
            palavras.push_back(x); //salva as palavras no vetor
                                 
    }
    arq01.close();
    string palAux;
    int next;
    for (int i = 0; i < nPal; i++)
    {
        palAux = palavras[i];                       // salva a palavra a ser testada
        next = testeAFD(palAux, EstIn, trans);      // recebe o valor do estado que o automato chega a partir da palavra lida
                                                   
        verificaFinal(next, nEstF, EstFim, palAux); // verifica se o estado é final e fala se a palavra foi aceita ou nao
    }
}
}
