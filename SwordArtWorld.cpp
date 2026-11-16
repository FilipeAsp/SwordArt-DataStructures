#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int MAX_VERTICES = 15;
const int MAX_FILA = 5;

// 1. FILA (Turnos de combate)
class Fila {
private:
    int vetor[MAX_FILA];
    int inicio = -1, fim = -1, tamanho = 0;

public:
    bool vazia() { return tamanho == 0; }
    bool cheia() { return tamanho == MAX_FILA; }
    void enfila(int valor) {
        if (!cheia()) {
            fim = (fim + 1) % MAX_FILA;
            vetor[fim] = valor;
            tamanho++;
            if (inicio == -1) inicio = 0;
        }
    }
    int desenfila() {
        if (!vazia()) {
            int valor = vetor[inicio];
            inicio = (inicio + 1) % MAX_FILA;
            tamanho--;
            return valor;
        }
        return -1;
    }
};

// 2. TABELA HASH (Bestiário)
struct Monstro {
    string nome;
    int hpBase;
    int forcaBase;
    int xpDrop;
    int goldDrop;
};

class TabelaHash {
private:
    static const int MAX = 11;
    struct NoHash {
        string chave;
        Monstro valor;
        NoHash *prox;
    };
    NoHash *tabelaHash[MAX];

    int funcaoHash(string chave) {
        int soma = 0;
        for (int i = 0; i < chave.length(); i++) soma += chave[i];
        return soma % MAX;
    }

public:
    TabelaHash() {
        for (int i = 0; i < MAX; i++) tabelaHash[i] = NULL;
    }
    void inserir(string chave, Monstro valor) {
        int posicao = funcaoHash(chave);
        NoHash *temp = tabelaHash[posicao];
        while (temp != NULL) {
            if (temp->chave == chave) {
                temp->valor = valor;
                return;
            }
            temp = temp->prox;
        }
        NoHash *novo = new NoHash;
        novo->chave = chave;
        novo->valor = valor;
        novo->prox = tabelaHash[posicao];
        tabelaHash[posicao] = novo;
    }
    Monstro *buscarMonstro(string chave) {
        int posicao = funcaoHash(chave);
        NoHash *temp = tabelaHash[posicao];
        while (temp != NULL) {
            if (temp->chave == chave) return &(temp->valor);
            temp = temp->prox;
        }
        return NULL;
    }
};

// 3. GRAFO (Mapa do Jogo)
class Grafo {
private:
    int numVertices;
    int matrizAdj[MAX_VERTICES][MAX_VERTICES];
    string locais[MAX_VERTICES];
    string monstrosLocais[MAX_VERTICES];

public:
    Grafo(int n) {
        numVertices = (n > MAX_VERTICES) ? MAX_VERTICES : n;
        for (int i = 0; i < numVertices; i++)
            for (int j = 0; j < numVertices; j++)
                matrizAdj[i][j] = 0;
    }
    void configurarLocal(int id, string nomeLocal, string chaveMonstro) {
        if (id >= 0 && id < numVertices) {
            locais[id] = nomeLocal;
            monstrosLocais[id] = chaveMonstro;
        }
    }
    void adicionarCaminho(int v1, int v2) {
        if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
            matrizAdj[v1][v2] = 1;
            matrizAdj[v2][v1] = 1;
        }
    }
    bool caminhoExiste(int origem, int destino) {
        if (origem >= 0 && origem < numVertices && destino >= 0 && destino < numVertices)
            return matrizAdj[origem][destino] > 0;
        return false;
    }
    void mostrarCaminhosPossiveis(int atual) {
        cout << "\n[ Voce esta em: " << locais[atual] << " ]" << endl;
        cout << "Caminhos disponiveis para viajar:" << endl;
        for (int j = 0; j < numVertices; j++) {
            if (matrizAdj[atual][j] > 0) {
                cout << "  -> (" << j << ") " << locais[j];
                if (monstrosLocais[j] != "Nenhum") cout << " [PERIGO]";
                cout << endl;
            }
        }
    }
    string getNomeLocal(int id) { return locais[id]; }
    string getChaveMonstro(int id) { return monstrosLocais[id]; }
    void limparMonstroLocal(int id) { monstrosLocais[id] = "Nenhum"; }
};

// 4. ÁRVORE AVL (Habilidades)
struct NoArvore {
    string nome;
    int bonusDano;
    int bonusHP;
    
    string requisito; 
    bool desbloqueada; 
    
    NoArvore* esquerda;
    NoArvore* direita;
    int altura;
};

class ArvoreHabilidades {
private: 
    NoArvore* raiz;

public: 
    ArvoreHabilidades() {
        raiz = NULL;
    }

    NoArvore* buscar(string nome) {
        return buscarRec(raiz, nome);
    }

    void exibirArvore() {
        if (raiz == NULL) {
            cout << "Nenhuma habilidade disponivel." << endl;
            return;
        }
        exibirEmOrdem(raiz);
    }

private: 
    NoArvore* buscarRec(NoArvore* no, string nome) {
        if (no == NULL) return NULL;
        if(no->nome == nome){
            return no;
        }
        if(no->nome > nome){
            return buscarRec(no->esquerda, nome);
        } else {
            return buscarRec(no->direita, nome);
        }
    }

    int altura(NoArvore* no) {
        if (no == NULL) return 0;
        return no->altura;
    }

    int fatorBalanceamento(NoArvore* no) {
        if (no == NULL) return 0;
        return altura(no->esquerda) - altura(no->direita);
    }

    NoArvore* novoNo(string nome, int bonusDano, int bonusHP, string requisito) {
        NoArvore* novo = new NoArvore;
        novo->nome = nome;
        novo->bonusDano = bonusDano;
        novo->bonusHP = bonusHP;
        novo->requisito = requisito;
        novo->desbloqueada = false;
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->altura = 1;
        return novo;
    }

    NoArvore* rotacaoDireita(NoArvore* raizAtual) {
        NoArvore* novaRaiz = raizAtual->esquerda;
        NoArvore* novoEsq = novaRaiz->direita;

        novaRaiz->direita = raizAtual;
        raizAtual->esquerda = novoEsq;

        raizAtual->altura = 1 + max(altura(raizAtual->esquerda), altura(raizAtual->direita));
        novaRaiz->altura = 1 + max(altura(novaRaiz->esquerda), altura(novaRaiz->direita));

        return novaRaiz; 
    }

    NoArvore* rotacaoEsquerda(NoArvore* raizAtual) {
        NoArvore* novaRaiz = raizAtual->direita;
        NoArvore* novoDir = novaRaiz->esquerda;

        novaRaiz->esquerda = raizAtual;
        raizAtual->direita = novoDir;

        raizAtual->altura = 1 + max(altura(raizAtual->esquerda), altura(raizAtual->direita));
        novaRaiz->altura = 1 + max(altura(novaRaiz->esquerda), altura(novaRaiz->direita));

        return novaRaiz;
    }

    void exibirEmOrdem(NoArvore* no) {
        if (no != NULL) {
            exibirEmOrdem(no->esquerda);
            cout << " -> " << no->nome;
            if (no->desbloqueada) cout << " [DESBLOQUEADA]";
            else cout << " [Requer: " << no->requisito << "]";
            cout << " (+ " << no->bonusDano << " Atq | + " << no->bonusHP << " HP)\n";
            exibirEmOrdem(no->direita);
        }
    }

public: 
    void inserir(string nome, int bonusDano, int bonusHP, string requisito) {
        raiz = inserirRec(raiz, nome, bonusDano, bonusHP, requisito);
    }

private: 
    NoArvore* inserirRec(NoArvore* no, string nome, int bonusDano, int bonusHP, string requisito) {
        if (no == NULL) {
            return novoNo(nome, bonusDano, bonusHP, requisito);
        }

        if (nome < no->nome) {
            no->esquerda = inserirRec(no->esquerda, nome, bonusDano, bonusHP, requisito);
        } else if (nome > no->nome) {
            no->direita = inserirRec(no->direita, nome, bonusDano, bonusHP, requisito);
        } else {
            return no; 
        }

        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
        int fb = fatorBalanceamento(no);

        if (fb > 1 && nome < no->esquerda->nome)
            return rotacaoDireita(no);

        if (fb < -1 && nome > no->direita->nome)
            return rotacaoEsquerda(no);

        if (fb > 1 && nome > no->esquerda->nome) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        if (fb < -1 && nome < no->direita->nome) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        return no;
    }

public:
    bool tentarDesbloquear(string nome, int &sp, int &force, int &hpMAX, int &hp) {
        NoArvore* atual = buscar(nome);
        
        if (atual != NULL) {
            if (atual->desbloqueada) {
                cout << "\n[!] A habilidade " << nome << " ja foi desbloqueada!\n";
                return false;
            }
            
            if (atual->requisito != "Nenhum") {
                NoArvore* req = buscar(atual->requisito);
                if (req == NULL || !req->desbloqueada) {
                    cout << "\n[!] Voce precisa desbloquear '" << atual->requisito << "' primeiro!\n";
                    return false;
                }
            }

            if (sp <= 0) {
                cout << "\n[!] Pontos de Habilidade (SP) insuficientes!\n";
                return false;
            }

            atual->desbloqueada = true;
            sp--;
            force += atual->bonusDano;
            hpMAX += atual->bonusHP;
            hp += atual->bonusHP; 
            return true;
        } else {
            cout << "\n[!] Habilidade nao encontrada na arvore!\n";
            return false;
        }
    }
};

// FUNÇÕES AUXILIARES
void pausar() {
    cout << "\n> Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void levelUp(int xp, int &level, int &sp) {
    int xpNecessario = level * 100;
    if (xp >= xpNecessario) {
        level++;
        sp++; 
        cout << "\n[!] Parabens! Voce subiu para o nivel " << level << "!" << endl;
        cout << "[!] Voce ganhou 1 Ponto de Habilidade (SP)! Acesse a Arvore para usar." << endl;
    }
}

void popularBestiario(TabelaHash &bestiario) {
    bestiario.inserir("Lobo Gigante", {"Lobo Gigante", 40, 10, 30, 10});
    bestiario.inserir("Goblin", {"Goblin Mago", 60, 15, 50, 25});
    bestiario.inserir("Orc", {"Orc Guerreiro", 100, 25, 80, 50});
    bestiario.inserir("Dragao", {"Dragao Anciao", 300, 40, 300, 200});
}

void popularMapa(Grafo &mapa) {
    mapa.configurarLocal(0, "Vila Segura", "Nenhum");
    mapa.configurarLocal(1, "Floresta Escura", "Lobo Gigante");
    mapa.configurarLocal(2, "Caverna Umida", "Goblin");
    mapa.configurarLocal(3, "Acampamento Inimigo", "Orc");
    mapa.configurarLocal(4, "Covil do Dragao", "Dragao");

    mapa.adicionarCaminho(0, 1); 
    mapa.adicionarCaminho(1, 2); 
    mapa.adicionarCaminho(1, 3); 
    mapa.adicionarCaminho(2, 4); 
    mapa.adicionarCaminho(3, 4); 
}

int main() {
    srand(time(0));

    TabelaHash bestiario;
    popularBestiario(bestiario);

    Grafo mapa(5);
    popularMapa(mapa);
    
    ArvoreHabilidades arvore;

    string nome, classe;
    int hp, hpMAX, force, level = 1, gold = 50, xp = 0, pocaoHP = 2;
    int sp = 1; 
    int localAtual = 0;

    system("cls");
    cout << "===============================\n"
         << "     RPG MEDIEVAL MAGICO       \n"
         << "===============================" << endl;
    cout << "Digite o nome do seu heroi: ";
    cin >> nome;

    int opcaoClasse;
    do {
        system("cls");
        cout << "Escolha sua classe:\n1. Guerreiro (Foco HP)\n2. Mago (Dano Alto)\nOpcao: ";
        cin >> opcaoClasse;

        if (opcaoClasse == 1) {
            classe = "Guerreiro";
            hpMAX = 100;
            force = 20;
            
            arvore.inserir("Vitalidade", 0, 20, "Nenhum");
            arvore.inserir("Pele_de_Ferro", 0, 30, "Vitalidade");
            arvore.inserir("Golpe_Forte", 10, 0, "Nenhum");
            arvore.inserir("Furia_Titanica", 25, 0, "Golpe_Forte");
        }
        else if (opcaoClasse == 2) {
            classe = "Mago";
            hpMAX = 60;
            force = 35;
            
            arvore.inserir("Foco_Arcano", 10, 0, "Nenhum");
            arvore.inserir("Escudo_de_Mana", 0, 20, "Foco_Arcano");
            arvore.inserir("Raio_de_Gelo", 15, 0, "Nenhum");
            arvore.inserir("Nevasca", 30, 0, "Raio_de_Gelo");
        }
        else {
            cout << "Opcao invalida.";
            pausar();
        }
    } while (opcaoClasse != 1 && opcaoClasse != 2);

    hp = hpMAX;
    bool jogando = true;

    while (jogando) {
        system("cls");
        cout << "==========================================================" << endl;
        cout << " JOGADOR: " << nome << " [" << classe << "] | LVL: " << level << " | HP: " << hp << "/" << hpMAX << " | OURO: " << gold << "g" << endl;
        cout << " LOCAL ATUAL: " << mapa.getNomeLocal(localAtual) << endl;
        cout << "==========================================================" << endl;
        cout << " 1. Viajar (Explorar Mapa)" << endl;
        cout << " 2. Descansar (Custa 10g - Apenas na Vila)" << endl;
        cout << " 3. Comprar Pocao (Custa 20g)" << endl;
        cout << " 4. Arvore de Habilidades (SP: " << sp << ")" << endl;
        cout << " 0. Sair do Jogo" << endl;
        cout << "==========================================================" << endl;
        cout << " Escolha: ";

        int escolha;
        cin >> escolha;

        switch (escolha) {
        case 1: {
            system("cls");
            mapa.mostrarCaminhosPossiveis(localAtual);
            cout << "Digite o numero do destino (ou -1 para cancelar): ";
            int destino;
            cin >> destino;

            if (destino == -1) break;

            if (!mapa.caminhoExiste(localAtual, destino)) {
                cout << "\n[!] Caminho bloqueado ou inexistente!" << endl;
                pausar();
                break;
            }

            localAtual = destino;
            cout << "\nVoce chegou em: " << mapa.getNomeLocal(localAtual) << endl;
            pausar();

            string chave = mapa.getChaveMonstro(localAtual);
            if (chave != "Nenhum") {
                Monstro *monstro = bestiario.buscarMonstro(chave);

                if (monstro != NULL) {
                    system("cls");
                    cout << "=== BATALHA INICIADA ===" << endl;
                    cout << "Um(a) " << monstro->nome << " selvagem ataca voce!" << endl;
                    pausar();

                    int mHP = monstro->hpBase;
                    Fila turnos;
                    turnos.enfila(1);
                    turnos.enfila(2);

                    while (hp > 0 && mHP > 0) {
                        system("cls");
                        int turnoAtual = turnos.desenfila();

                        if (turnoAtual == 1) {
                            cout << "--- SEU TURNO ---" << endl;
                            cout << "HP: " << hp << "/" << hpMAX << " | INIMIGO HP: " << mHP << "/" << monstro->hpBase << endl;
                            cout << "1. Atacar\n2. Usar Pocao (" << pocaoHP << ")\nEscolha: ";
                            int acao;
                            cin >> acao;

                            if (acao == 1) {
                                int dano = (rand() % 10) + force;
                                mHP -= dano;
                                cout << "Voce causou " << dano << " de dano!" << endl;
                            }
                            else if (acao == 2 && pocaoHP > 0) {
                                pocaoHP--;
                                hp += 40;
                                if (hp > hpMAX) hp = hpMAX;
                                cout << "Voce recuperou 40 HP!" << endl;
                            }
                            else {
                                cout << "Falhou! Acao invalida ou sem pocoes." << endl;
                            }
                            pausar();
                            turnos.enfila(1);
                        }
                        else {
                            cout << "--- TURNO DO INIMIGO ---" << endl;
                            int danoM = (rand() % 5) + monstro->forcaBase;
                            hp -= danoM;
                            cout << "O " << monstro->nome << " causou " << danoM << " de dano!" << endl;
                            pausar();
                            turnos.enfila(2);
                        }
                    }

                    if (hp > 0) {
                        cout << "\n[VITORIA] Voce derrotou o " << monstro->nome << "!" << endl;
                        xp += monstro->xpDrop;
                        gold += monstro->goldDrop;
                        levelUp(xp, level, sp); 
                        mapa.limparMonstroLocal(localAtual);

                        if (localAtual == 4) {
                            cout << "\n*** PARABENS! VOCE MATOU O DRAGAO E ZEROU O JOGO! ***" << endl;
                            jogando = false;
                        }
                    }
                    else {
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
            if (localAtual != 0) {
                cout << "\nVoce so pode descansar com seguranca na Vila Segura!" << endl;
            }
            else if (gold >= 10) {
                gold -= 10;
                hp = hpMAX;
                cout << "\nVoce descansou na taverna e recuperou todo seu HP!" << endl;
            }
            else {
                cout << "\nOuro insuficiente!" << endl;
            }
            pausar();
            break;
        case 3:
            if (gold >= 20) {
                gold -= 20;
                pocaoHP++;
                cout << "\nVoce comprou uma Pocao de HP!" << endl;
            }
            else {
                cout << "\nOuro insuficiente!" << endl;
            }
            pausar();
            break;
        case 4: {
            system("cls");
            cout << "==========================================================" << endl;
            cout << "                   ARVORE DE HABILIDADES                  " << endl;
            cout << "==========================================================\n" << endl;
            
            arvore.exibirArvore(); 
            
            cout << "\n==========================================================" << endl;
            cout << "Pontos Disponiveis (SP): " << sp << endl;
            
            cout << "\nDigite o NOME exato da habilidade para desbloquear (ou '0' para Voltar): ";
            string habDesejada;
            cin >> habDesejada;
            
            if (habDesejada != "0") {
                if (arvore.tentarDesbloquear(habDesejada, sp, force, hpMAX, hp)) {
                    cout << "\nParabens! Seus atributos aumentaram!" << endl;
                    cout << "Novos Status Base -> Atq: " << force << " | HP Maximo: " << hpMAX << endl;
                }
            }
            pausar();
            break;
        }
        case 0:
            jogando = false;
            break;
        default:
            cout << "Opcao Invalida!" << endl;
            pausar();
            break;
        }
    }

    cout << "\nObrigado por jogar!" << endl;
    return 0;
}