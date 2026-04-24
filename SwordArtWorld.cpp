#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// PILHA (ANDARES DA MASMORRA)
const int MAX_MASMORRA = 10;
int pilhaMasmorra[MAX_MASMORRA];
int topoMasmorra = -1;

void pushMasmorra(int andar)
{
    if (topoMasmorra < MAX_MASMORRA - 1)
    {
        topoMasmorra++;
        pilhaMasmorra[topoMasmorra] = andar;
    }
}

int popMasmorra()
{
    int andarDescartado = -1;
    if (topoMasmorra >= 0)
    {
        andarDescartado = pilhaMasmorra[topoMasmorra];
        topoMasmorra--;
    }
    return andarDescartado;
}

bool pilhaMasmorraVazia()
{
    if (topoMasmorra == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// FILA CIRCULAR (TURNOS DE COMBATE)
const int MAX_FILA = 5;
int filaCombate[MAX_FILA];
int inicioFila = -1, fimFila = -1;

void enfila(int element)
{
    int prox = (fimFila + 1) % MAX_FILA;
    if (prox != inicioFila)
    {
        fimFila = prox;
        filaCombate[fimFila] = element;
        if (inicioFila == -1)
        {
            inicioFila = 0;
        }
    }
}

int desenfila()
{
    int element = -1;
    if (inicioFila >= 0)
    {
        element = filaCombate[inicioFila];
        if (inicioFila == fimFila)
        {
            inicioFila = -1;
            fimFila = -1;
        }
        else
        {
            inicioFila = (inicioFila + 1) % MAX_FILA;
        }
    }
    return element;
}

void pausar()
{
    cout << "\n> Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void menu(string name, int hpMAX, int hp, int xp, int level)
{
    system("cls");
    cout << "==========================================================" << endl;
    cout << "  JOGADOR: " << name << " | LVL: " << level << " | HP: " << hp << "/" << hpMAX << " | XP: " << xp << endl;
    cout << "==========================================================" << endl;
    cout << "           >>> O QUE DESEJA FAZER AGORA? <<<" << endl
         << endl;
    cout << "   [ AVENTURA ]                   [ CIDADE ]" << endl;
    cout << "   1. Explorar Masmorra           3. Descansar na Taverna" << endl;
    cout << "   2. Treinar na Arena            4. Loja de Itens" << endl;
    cout << endl;
    cout << "   [ PERSONAGEM ]                 [ SISTEMA ]" << endl;
    cout << "   5. Ver Status Detalhado        0. Desistir (Log-out)" << endl;
    cout << "   6. Abrir Inventario" << endl;
    cout << "\n==========================================================" << endl;
    cout << " Escolha sua acao: ";
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

void exibirStatus(string name, string className, int hpMAX, int mpMAX, int hp, int mp, int force, int level, int xp, int gold, int potion, int atributos)
{
    cout << "========================================" << endl;
    cout << "           FICHA DE PERSONAGEM          " << endl;
    cout << "========================================" << endl;
    cout << " NOME: " << name << " | CLASSE: " << className << endl;
    cout << " NIVEL: " << level << "     |  XP: " << xp << endl;
    cout << "----------------------------------------" << endl;
    cout << " [ STATUS ]             [ INVENTARIO ]  " << endl;
    cout << " HP:  " << hp << " / " << hpMAX << "           Gold:  " << gold << endl;
    cout << " MP:  " << mp << " / " << mpMAX << "           Potions: " << potion << endl;
    cout << " Forca: " << force << endl;
    cout << " Atributos: " << atributos << endl;
    cout << "========================================" << endl;
}

void exibirLoja(int gold)
{
    cout << "==========================================================" << endl;
    cout << "         MERCADO DO VIAJANTE - SWORD ART WORLD            " << endl;
    cout << "==========================================================" << endl;
    cout << "  Seu Ouro: " << gold << "g" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "  ITEM                     | PRECO | DESCRICAO            " << endl;
    cout << "---------------------------|-------|----------------------" << endl;
    cout << "  1. Pocao de Vida (P)     |  20g  | Recupera 20 HP       " << endl;
    cout << "  2. Pocao de Vida (G)     |  50g  | Recupera 60 HP       " << endl;
    cout << "  3. Pocao de Mana         |  30g  | Recupera 30 MP       " << endl;
    cout << "  4. Elixir de XP (P)      |  40g  | +50 pontos de XP     " << endl;
    cout << "  5. Elixir de XP (G)      | 100g  | +150 pontos de XP    " << endl;
    cout << "  0. Sair da Loja          |   -   | Voltar ao menu       " << endl;
    cout << "==========================================================" << endl;
    cout << " O que deseja comprar? (Digite o numero correspondente): ";
}

void inventario(int gold, int potionHP, int potionMP, int potionXP)
{
    cout << "===============================\n"
         << "         INVENTARIO          \n"
         << "===============================" << endl;
    cout << " Ouro: " << gold << "g" << endl;
    cout << " 1 - Pocao de Vida: " << potionHP << endl;
    cout << " 2 - Pocao de Mana: " << potionMP << endl;
    cout << " 3 - Elixir de XP: " << potionXP << endl;
    cout << " 0 - Fechar Mochila" << endl;
    cout << "===============================" << endl;
    cout << "Qual item deseja usar? ";
}

void disconnect(string name)
{
    cout << "================================================" << endl;
    cout << " [!] DESCONECTANDO DO SWORD ART WORLD...        " << endl;
    cout << "================================================" << endl;
    cout << "\n Bravo(a) " << name << ", suas conquistas serao lembradas." << endl;
    cout << " As lendas do reino aguardam seu retorno!" << endl;
    cout << "\n Ate a proxima aventura, heroi." << endl;
    cout << "================================================" << endl;
}

int main()
{
    srand(time(0));

    for (int i = MAX_MASMORRA; i >= 1; i--) // Inicializando a Pilha da Masmorra com os andares de 10 a 1 (topo é o 1)
    {
        pushMasmorra(i);
    }

    string name, className;
    int hp, mp, force, level = 1, gold = 50, potion = 0, xp = 0;
    int hpMAX, mpMAX, atributos = 0, potionHP = 0, potionMP = 0, potionXP = 0;

    system("cls");
    cout << "===============================\n"
         << "   BEM VINDO AO SWORD ART!     \n"
         << "===============================" << endl;
    cout << "Digite o nome do seu heroi: ";
    cin >> name;

    int option;
    do
    {
        system("cls");
        cout << "===============================\n"
             << "       Escolha de classe     \n"
             << "==============================="
             << "\n1. Guerreiro (Forca)"
             << "\n2. Mago (Magia)"
             << "\n3. Arqueiro (Equilibrio)"
             << "\n===============================" << endl;

        cout << "Opcao: ";
        cin >> option;

        if (option == 1)
        {
            className = "Guerreiro";
        }
        else if (option == 2)
        {
            className = "Mago";
        }
        else if (option == 3)
        {
            className = "Arqueiro";
        }
        else
        {
            cout << "Opçao invalida." << endl;
            pausar();
        }
    } while (option != 1 && option != 2 && option != 3);

    if (className == "Guerreiro")
    {
        hpMAX = (rand() % 20) + 70;
        mpMAX = (rand() % 20) + 20;
        force = (rand() % 10) + 20;
    }
    else if (className == "Mago")
    {
        hpMAX = (rand() % 20) + 50;
        mpMAX = (rand() % 20) + 40;
        force = (rand() % 10) + 10;
    }
    else
    {
        hpMAX = (rand() % 20) + 60;
        mpMAX = (rand() % 20) + 30;
        force = (rand() % 10) + 10;
    }

    hp = hpMAX;
    mp = mpMAX;

    system("cls");
    exibirStatus(name, className, hpMAX, mpMAX, hp, mp, force, level, xp, gold, potion, atributos);
    pausar();

    option = 0;
    do
    {
        menu(name, hpMAX, hp, xp, level);
        cin >> option;

        switch (option)
        {
        case 1: // Masmorra
        {
            system("cls");
            if (pilhaMasmorraVazia() != true)
            {
                int andarAtual = pilhaMasmorra[topoMasmorra];
                if (level < andarAtual)
                {
                    cout << "[!] Nivel insuficiente para o Andar " << andarAtual << "!" << endl;
                    cout << "Treine na Arena primeiro." << endl;
                    pausar();
                    break;
                }

                inicioFila = -1;
                fimFila = -1;

                enfila(1);
                enfila(2);

                // Geração dos stats do monstro com base no andar atual
                int mHP = (rand() % 30) + (andarAtual * 20);
                int mForca = (rand() % 5) + (andarAtual * 5);

                cout << "=== BATALHA: ANDAR " << andarAtual << " ===" << endl;
                cout << "Um Monstro de Rank " << andarAtual << " bloqueia o caminho!" << endl;
                pausar();

                while (hp > 0 && mHP > 0)
                {
                    system("cls");
                    int atual = desenfila();

                    cout << "------------------------------------------" << endl;
                    cout << " SUA VIDA: " << hp << "/" << hpMAX << " | VIDA MONSTRO: " << mHP << endl;
                    cout << "------------------------------------------" << endl;

                    if (atual == 1) // TURNO DO JOGADOR
                    {
                        int opcaoTurno;
                        int opcaoItem;

                        do
                        {
                            system("cls");
                            cout << "------------------------------------------" << endl;
                            cout << " SUA VIDA: " << hp << "/" << hpMAX << " | VIDA MONSTRO: " << mHP << endl;
                            cout << "------------------------------------------" << endl;
                            cout << ">>> SEU TURNO!" << endl;
                            cout << "1. Atacar\n2. Abrir Inventario" << endl;

                            cin >> opcaoTurno;

                            switch (opcaoTurno)
                            {
                            case 1:
                            {
                                int dano = (rand() % 10) + force;
                                mHP -= dano;
                                cout << "\nVoce atacou e causou " << dano << " de dano!" << endl;
                                pausar();
                                break;
                            }
                            case 2:
                            {
                                system("cls");
                                inventario(gold, potionHP, potionMP, potionXP);
                                cin >> opcaoItem;

                                switch (opcaoItem)
                                {
                                case 1:
                                    if (potionHP > 0)
                                    {
                                        potionHP -= 1;
                                        potion -= 1;
                                        int antes = hp;
                                        hp += 20;
                                        if (hp > hpMAX)
                                            hp = hpMAX;
                                        cout << "\nVoce usou uma Pocao de Vida! HP recuperado: " << (hp - antes) << endl;
                                    }
                                    else
                                    {
                                        cout << "\nVoce nao tem Pocao de Vida." << endl;
                                        opcaoTurno = 0;
                                    }
                                    break;
                                case 2:
                                    if (potionMP > 0)
                                    {
                                        potionMP -= 1;
                                        potion -= 1;
                                        int antes = mp;
                                        mp += 30;
                                        if (mp > mpMAX)
                                            mp = mpMAX;
                                        cout << "\nVoce usou uma Pocao de Mana! MP recuperado: " << (mp - antes) << endl;
                                    }
                                    else
                                    {
                                        cout << "\nVoce nao tem Pocao de Mana." << endl;
                                        opcaoTurno = 0;
                                    }
                                    break;
                                case 3:
                                    if (potionXP > 0)
                                    {
                                        potionXP -= 1;
                                        potion -= 1;
                                        xp += 50;
                                        cout << "\nVoce usou um Elixir de XP! XP ganho: 50" << endl;
                                        level = levelUp(xp, level);
                                    }
                                    else
                                    {
                                        cout << "\nVoce nao tem Elixir de XP." << endl;
                                        opcaoTurno = 0;
                                    }
                                    break;
                                case 0:
                                    cout << "\nVoce fechou a mochila sem usar nada." << endl;
                                    opcaoTurno = 0;
                                    break;
                                default:
                                    cout << "\nOpcao de item invalida!" << endl;
                                    opcaoTurno = 0;
                                    break;
                                }
                                pausar();
                                break;
                            }
                            default:
                                cout << "\nAcao invalida! Tente novamente." << endl;
                                opcaoTurno = 0;
                                pausar();
                                break;
                            }

                        } while (opcaoTurno != 1 && opcaoTurno != 2);

                        enfila(1); // Fim do turno, devolve o jogador para a fila
                    }
                    else // TURNO DO MONSTRO
                    {
                        int dano = (rand() % 5) + mForca;
                        hp -= dano;
                        cout << "\nO monstro atacou e causou " << dano << " de dano!" << endl;
                        pausar();
                        enfila(2); // Fim do turno, devolve o monstro para a fila
                    }
                }

                // Resultado da Batalha (POP DA MASMORRA)
                if (hp > 0)
                {
                    system("cls");
                    cout << "\n[VITORIA] Voce derrotou o monstro!" << endl;
                    int gXP = 50 + (andarAtual * 10);
                    int gGold = 20 + (andarAtual * 5);
                    xp += gXP;
                    gold += gGold;

                    cout << "Ganhos: +" << gXP << " XP | +" << gGold << " Gold" << endl;

                    popMasmorra();
                    cout << "\n[SISTEMA] POP executado! Andar " << andarAtual << " concluido e removido da Masmorra." << endl;

                    level = levelUp(xp, level);
                }
                else
                {
                    system("cls");
                    cout << "\n[DERROTA] Voce desmaiou de dor e foi resgatado..." << endl;
                    hp = 1;
                }
                pausar();
            }
            else
            {
                cout << "[!] Parabens! A MASMORRA esta vazia! Voce conquistou o topo de SWORD ART WORLD!" << endl;
                pausar();
            }
            break;
        }

        case 2: // ARENA DE TREINO
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "          ARENA DE TREINAMENTO          " << endl;
            cout << "========================================" << endl;
            cout << "Voce passa horas lutando contra bonecos de madeira..." << endl;

            int xpGanho = (rand() % 15) + 10;
            xp += xpGanho;

            cout << "\nO treinamento valeu a pena! Voce ganhou " << xpGanho << " de XP." << endl;
            level = levelUp(xp, level);
            pausar();
            break;
        }

        case 3: // TAVERNA (PUSH DA MASMORRA)
        {
            system("cls");
            cout << "================================================" << endl;
            cout << "              TAVERNA DO LIMAO E MEL            " << endl;
            cout << "================================================" << endl;
            cout << " Voce aluga um quarto e descansa profundamente..." << endl;
            cout << " . . . . . . . . . . . . . . . . . . . . . . . ." << endl;

            int recuperouHP = 0;
            int recuperouMP = 0;

            if (hp < hpMAX)
            {
                int antes = hp;
                hp += 30;
                if (hp > hpMAX)
                    hp = hpMAX;
                recuperouHP = hp - antes;
            }
            if (mp < mpMAX)
            {
                int antes = mp;
                mp += 10;
                if (mp > mpMAX)
                    mp = mpMAX;
                recuperouMP = mp - antes;
            }

            cout << "\n [RESTAURACAO CONCLUIDA]" << endl;
            if (recuperouHP > 0)
                cout << "  + " << recuperouHP << " HP recuperado." << endl;
            if (recuperouMP > 0)
                cout << "  + " << recuperouMP << " MP recuperado." << endl;
            if (recuperouHP == 0 && recuperouMP == 0)
                cout << "  Voce ja estava com energia total." << endl;

            cout << "\n Status Atual: HP [" << hp << "/" << hpMAX << "] | MP [" << mp << "/" << mpMAX << "]" << endl;
            cout << "------------------------------------------------" << endl;
            cout << " Voce acorda sentindo-se revigorado!" << endl;

            int andarRetomado = -1;
            if (pilhaMasmorraVazia() == true)
            {
                andarRetomado = MAX_MASMORRA;
            }
            else if (pilhaMasmorra[topoMasmorra] > 1)
            {
                andarRetomado = pilhaMasmorra[topoMasmorra] - 1;
            }

            if (andarRetomado > 0 && topoMasmorra < MAX_MASMORRA - 1)
            {
                pushMasmorra(andarRetomado);
                cout << "\n [!!!] AVISO: Enquanto voce dormia, monstros deram PUSH e retomaram o Andar " << andarRetomado << "!" << endl;
            }
            cout << "================================================" << endl;
            pausar();
            break;
        }

        case 4: // LOJA
        {
            int compra;
            do
            {
                system("cls");
                exibirLoja(gold);
                cin >> compra;
                switch (compra)
                {
                case 1:
                    if (gold >= 20)
                    {
                        gold -= 20;
                        potion += 1;
                        potionHP += 1;
                        cout << "\nVoce comprou uma Pocao de Vida (P)!" << endl;
                    }
                    else
                        cout << "\nOuro insuficiente." << endl;
                    pausar();
                    break;
                case 2:
                    if (gold >= 50)
                    {
                        gold -= 50;
                        potion += 3;
                        potionHP += 3;
                        cout << "\nVoce comprou uma Pocao de Vida (G)!" << endl;
                    }
                    else
                        cout << "\nOuro insuficiente." << endl;
                    pausar();
                    break;
                case 3:
                    if (gold >= 30)
                    {
                        gold -= 30;
                        potion += 1;
                        potionMP += 1;
                        cout << "\nVoce comprou uma Pocao de Mana!" << endl;
                    }
                    else
                        cout << "\nOuro insuficiente." << endl;
                    pausar();
                    break;
                case 4:
                    if (gold >= 40)
                    {
                        gold -= 40;
                        potion += 1;
                        potionXP += 1;
                        cout << "\nVoce comprou um Elixir de XP (P)!" << endl;
                    }
                    else
                        cout << "\nOuro insuficiente." << endl;
                    pausar();
                    break;
                case 5:
                    if (gold >= 100)
                    {
                        gold -= 100;
                        potion += 3;
                        potionXP += 3;
                        cout << "\nVoce comprou um Elixir de XP (G)!" << endl;
                    }
                    else
                        cout << "\nOuro insuficiente." << endl;
                    pausar();
                    break;
                case 0:
                    cout << "\nSaindo da loja..." << endl;
                    break;
                default:
                    cout << "\nItem invalido." << endl;
                    pausar();
                }
            } while (compra != 0);
            break;
        }

        case 5: // STATUS
        {
            system("cls");
            exibirStatus(name, className, hpMAX, mpMAX, hp, mp, force, level, xp, gold, potion, atributos);
            pausar();
            break;
        }

        case 6: // INVENTARIO
        {
            system("cls");
            inventario(gold, potionHP, potionMP, potionXP);
            int usar;
            cin >> usar;
            switch (usar)
            {
            case 1:
                if (potionHP > 0)
                {
                    potionHP -= 1;
                    potion -= 1;
                    int antes = hp;
                    hp += 20;
                    if (hp > hpMAX)
                        hp = hpMAX;
                    cout << "\nVoce usou uma Pocao de Vida! HP recuperado: " << (hp - antes) << endl;
                }
                else
                    cout << "\nVoce nao tem Pocao de Vida." << endl;
                pausar();
                break;
            case 2:
                if (potionMP > 0)
                {
                    potionMP -= 1;
                    potion -= 1;
                    int antes = mp;
                    mp += 30;
                    if (mp > mpMAX)
                        mp = mpMAX;
                    cout << "\nVoce usou uma Pocao de Mana! MP recuperado: " << (mp - antes) << endl;
                }
                else
                    cout << "\nVoce nao tem Pocao de Mana." << endl;
                pausar();
                break;
            case 3:
                if (potionXP > 0)
                {
                    potionXP -= 1;
                    potion -= 1;
                    xp += 50;
                    cout << "\nVoce usou um Elixir de XP! XP ganho: 50" << endl;
                    level = levelUp(xp, level);
                }
                else
                    cout << "\nVoce nao tem Elixir de XP." << endl;
                pausar();
                break;
            case 0:
                break;
            default:
                cout << "\nOpcao invalida." << endl;
                pausar();
            }
            break;
        }

        case 0: // DESISTIR
        {
            system("cls");
            disconnect(name);
            break;
        }

        default:
            cout << "\nOpcao invalida. Por favor, escolha uma opçao valida." << endl;
            pausar();
            break;
        }

    } while (option != 0);

    return 0;
}