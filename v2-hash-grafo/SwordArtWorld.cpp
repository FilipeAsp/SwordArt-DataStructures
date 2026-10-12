#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Fila e Pilha

const int MAX_VERTICES = 15;
const int MAX_FILA = 5;

// Turnos de combate
class Fila
{
private:
    int vetor[MAX_FILA];
    int inicio = -1, fim = -1, tamanho = 0;

public:
    bool vazia()
    {
        return tamanho == 0;
    }

    bool cheia()
    {
        return tamanho == MAX_FILA;
    }

    void enfila(int valor)
    {
        if (!cheia())
        {
            fim = (fim + 1) % MAX_FILA;
            vetor[fim] = valor;
            tamanho++;
            if (inicio == -1)
            {
                inicio = 0;
            }
        }
    }

    int desenfila()
    {
        if (!vazia())
        {
            int valor = vetor[inicio];
            inicio = (inicio + 1) % MAX_FILA;
            tamanho--;
            return valor;
        }
        return -1;
    }
};

// TABELA HASH (Bestiário)
// Chave: Nome do Monstro (string) | Valor: Atributos do Monstro (Struct)

struct Monstro
{
    string nome;
    int hpBase;
    int forcaBase;
    int xpDrop;
    int goldDrop;
};

class TabelaHash
{
private:
    static const int MAX = 11;

    struct No
    {
        string chave;
        Monstro valor;
        No *prox;
    };

    No *tabelaHash[MAX];

    int funcaoHash(string chave)
    {
        int soma = 0;
        for (int i = 0; i < chave.length(); i++)
        {
            soma += chave[i];
        }
        return soma % MAX;
    }

public:
    TabelaHash()
    {
        for (int i = 0; i < MAX; i++)
        {
            tabelaHash[i] = NULL;
        }
    }

    void inserir(string chave, Monstro valor)
    {
        int posicao = funcaoHash(chave);
        No *temp = tabelaHash[posicao];

        while (temp != NULL)
        {
            if (temp->chave == chave)
            {
                temp->valor = valor;
                return;
            }
            temp = temp->prox;
        }

        No *novo = new No;
        novo->chave = chave;
        novo->valor = valor;
        novo->prox = tabelaHash[posicao];
        tabelaHash[posicao] = novo;
    }

    Monstro *buscarMonstro(string chave)
    {
        int posicao = funcaoHash(chave);
        No *temp = tabelaHash[posicao];

        while (temp != NULL)
        {
            if (temp->chave == chave)
            {
                return &(temp->valor);
            }
            temp = temp->prox;
        }
        return NULL;
    }
};

// GRAFO (Mapa do Jogo)
// Usando Matriz de Adjacências

class Grafo
{
private:
    int numVertices;
    int matrizAdj[MAX_VERTICES][MAX_VERTICES];
    string locais[MAX_VERTICES];
    string monstrosLocais[MAX_VERTICES];

public:
    Grafo(int n)
    {
        if (n > MAX_VERTICES)
            numVertices = MAX_VERTICES;
        else
            numVertices = n;

        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                matrizAdj[i][j] = 0;
            }
        }
    }

    void configurarLocal(int id, string nomeLocal, string chaveMonstro)
    {
        if (id >= 0 && id < numVertices)
        {
            locais[id] = nomeLocal;
            monstrosLocais[id] = chaveMonstro;
        }
    }

    void adicionarCaminho(int v1, int v2)
    {
        if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
        {
            matrizAdj[v1][v2] = 1;
            matrizAdj[v2][v1] = 1;
        }
    }

    bool caminhoExiste(int origem, int destino)
    {
        if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices)
        {
            return matrizAdj[origem][destino] > 0;
        }
        return false;
    }

    void mostrarCaminhosPossiveis(int atual)
    {
        cout << "\n[ Voce esta em: " << locais[atual] << " ]" << endl;
        cout << "Caminhos disponiveis para viajar:" << endl;
        for (int j = 0; j < numVertices; j++)
        {
            if (matrizAdj[atual][j] > 0)
            {
                cout << "  -> (" << j << ") " << locais[j];
                if (monstrosLocais[j] != "Nenhum")
                {
                    cout << " [PERIGO]";
                }
                cout << endl;
            }
        }
    }

    string getNomeLocal(int id)
    {
        return locais[id];
    }

    string getChaveMonstro(int id)
    {
        return monstrosLocais[id];
    }

    void limparMonstroLocal(int id)
    {
        monstrosLocais[id] = "Nenhum";
    }
};

// FUNÇÕES AUXILIARES

void pausar()
{
    cout << "\n> Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int levelUp(int xp, int level)
{
    int xpNecessario = level * 100;
    if (xp >= xpNecessario)
    {
        level++;
        cout << "\n[!] Parabens! Voce subiu para o nivel " << level << "!" << endl;
    }
    return level;
}

void popularBestiario(TabelaHash &bestiario)
{
    bestiario.inserir("Lobo Gigante", {"Lobo Gigante", 40, 10, 30, 10});
    bestiario.inserir("Goblin", {"Goblin Mago", 60, 15, 50, 25});
    bestiario.inserir("Orc", {"Orc Guerreiro", 100, 25, 80, 50});
    bestiario.inserir("Dragao", {"Dragao Anciao", 300, 40, 300, 200});
}

void popularMapa(Grafo &mapa)
{

    mapa.configurarLocal(0, "Vila Segura", "Nenhum");
    mapa.configurarLocal(1, "Floresta Escura", "Lobo Gigante");
    mapa.configurarLocal(2, "Caverna Umida", "Goblin");
    mapa.configurarLocal(3, "Acampamento Inimigo", "Orc");
    mapa.configurarLocal(4, "Covil do Dragao", "Dragao");

    mapa.adicionarCaminho(0, 1); // Vila <-> Floresta
    mapa.adicionarCaminho(1, 2); // Floresta <-> Caverna
    mapa.adicionarCaminho(1, 3); // Floresta <-> Acampamento
    mapa.adicionarCaminho(2, 4); // Caverna <-> Covil
    mapa.adicionarCaminho(3, 4); // Acampamento <-> Covil
}

// MAIN

int main()
{
    srand(time(0));

    TabelaHash bestiario;
    popularBestiario(bestiario);

    Grafo mapa(5);
    popularMapa(mapa);

    string nome, classe;
    int hp, hpMAX, force, level = 1, gold = 50, xp = 0, pocaoHP = 2;
    int localAtual = 0;

    system("cls");
    cout << "===============================\n"
         << "     RPG MEDIEVAL MAGICO       \n"
         << "===============================" << endl;
    cout << "Digite o nome do seu heroi: ";
    cin >> nome;

    int opcaoClasse;
    do
    {
        system("cls");
        cout << "Escolha sua classe:\n1. Guerreiro (Foco HP)\n2. Mago (Dano Alto)\nOpcao: ";
        cin >> opcaoClasse;

        if (opcaoClasse == 1)
        {
            classe = "Guerreiro";
            hpMAX = 100;
            force = 20;
        }
        else if (opcaoClasse == 2)
        {
            classe = "Mago";
            hpMAX = 60;
            force = 35;
        }
        else
        {
            cout << "Opçao invalida.";
            pausar();
        }
    } while (opcaoClasse != 1 && opcaoClasse != 2);

    hp = hpMAX;
    bool jogando = true;

    while (jogando)
    {
        system("cls");
        cout << "==========================================================" << endl;
        cout << " JOGADOR: " << nome << " | LVL: " << level << " | HP: " << hp << "/" << hpMAX << " | OURO: " << gold << "g" << endl;
        cout << " LOCAL ATUAL: " << mapa.getNomeLocal(localAtual) << endl;
        cout << "==========================================================" << endl;
        cout << " 1. Viajar (Usar Grafo)" << endl;
        cout << " 2. Descansar (Custa 10g - Apenas na Vila)" << endl;
        cout << " 3. Comprar Pocao (Custa 20g)" << endl;
        cout << " 0. Sair do Jogo" << endl;
        cout << "==========================================================" << endl;
        cout << " Escolha: ";

        int escolha;
        cin >> escolha;

        switch (escolha)
        {
        case 1:
        {
            system("cls");
            mapa.mostrarCaminhosPossiveis(localAtual);
            cout << "Digite o numero do destino (ou -1 para cancelar): ";
            int destino;
            cin >> destino;

            if (destino == -1)
                break;

            if (!mapa.caminhoExiste(localAtual, destino))
            {
                cout << "\n[!] Caminho bloqueado ou inexistente!" << endl;
                pausar();
                break;
            }

            localAtual = destino;
            cout << "\nVoce chegou em: " << mapa.getNomeLocal(localAtual) << endl;
            pausar();

            string chave = mapa.getChaveMonstro(localAtual);
            if (chave != "Nenhum")
            {
                Monstro *monstro = bestiario.buscarMonstro(chave);

                if (monstro != NULL)
                {
                    system("cls");
                    cout << "=== BATALHA INICIADA ===" << endl;
                    cout << "Um(a) " << monstro->nome << " selvagem ataca voce!" << endl;
                    pausar();

                    int mHP = monstro->hpBase;
                    Fila turnos;
                    turnos.enfila(1);
                    turnos.enfila(2);

                    while (hp > 0 && mHP > 0)
                    {
                        system("cls");
                        int turnoAtual = turnos.desenfila();

                        if (turnoAtual == 1)
                        {
                            cout << "--- SEU TURNO ---" << endl;
                            cout << "HP: " << hp << "/" << hpMAX << " | INIMIGO HP: " << mHP << "/" << monstro->hpBase << endl;
                            cout << "1. Atacar\n2. Usar Pocao (" << pocaoHP << ")\nEscolha: ";
                            int acao;
                            cin >> acao;

                            if (acao == 1)
                            {
                                int dano = (rand() % 10) + force;
                                mHP -= dano;
                                cout << "Voce causou " << dano << " de dano!" << endl;
                            }
                            else if (acao == 2 && pocaoHP > 0)
                            {
                                pocaoHP--;
                                hp += 40;
                                if (hp > hpMAX)
                                    hp = hpMAX;
                                cout << "Voce recuperou 40 HP!" << endl;
                            }
                            else
                            {
                                cout << "Falhou!" << endl;
                            }
                            pausar();
                            turnos.enfila(1);
                        }
                        else
                        {
                            cout << "--- TURNO DO INIMIGO ---" << endl;
                            int danoM = (rand() % 5) + monstro->forcaBase;
                            hp -= danoM;
                            cout << "O " << monstro->nome << " causou " << danoM << " de dano!" << endl;
                            pausar();
                            turnos.enfila(2);
                        }
                    }

                    if (hp > 0)
                    {
                        cout << "\n[VITORIA] Voce derrotou o " << monstro->nome << "!" << endl;
                        xp += monstro->xpDrop;
                        gold += monstro->goldDrop;
                        level = levelUp(xp, level);
                        mapa.limparMonstroLocal(localAtual);

                        if (localAtual == 4)
                        {
                            cout << "\n*** PARABENS! VOCE MATOU O DRAGAO E ZEROU O JOGO! ***" << endl;
                            jogando = false;
                        }
                    }
                    else
                    {
                        cout << "\n[DERROTA] Voce desmaiou e foi levado de volta a Vila..." << endl;
                        localAtual = 0;
                        hp = 1;
                    }
                    pausar();
                }
            }
            break;
        }
        case 2:
            if (localAtual != 0)
            {
                cout << "\nVoce so pode descansar com seguranca na Vila Segura!" << endl;
            }
            else if (gold >= 10)
            {
                gold -= 10;
                hp = hpMAX;
                cout << "\nVoce descansou na taverna e recuperou todo seu HP!" << endl;
            }
            else
            {
                cout << "\nOuro insuficiente!" << endl;
            }
            pausar();
            break;
        case 3:
            if (gold >= 20)
            {
                gold -= 20;
                pocaoHP++;
                cout << "\nVoce comprou uma Pocao de HP!" << endl;
            }
            else
            {
                cout << "\nOuro insuficiente!" << endl;
            }
            pausar();
            break;
        case 0:
            jogando = false;
            break;
        }
    }

    cout << "\nObrigado por jogar!" << endl;
    return 0;
}