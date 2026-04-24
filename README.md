# ⚔️ Sword Art World - RPG em C++

Um jogo de RPG de texto desenvolvido em C++ que simula a exploração de uma masmorra de 10 andares. O projeto foca na aplicação prática de **Estruturas de Dados Estáticas** para gerenciar a progressão do jogador e a lógica de combate por turnos.

## 🚀 Funcionalidades

* **Sistema de Classes:** Escolha entre Guerreiro, Mago ou Arqueiro, cada um com atributos (HP, MP e Força) gerados aleatoriamente.
* **Masmorra Dinâmica:** Exploração de 10 níveis de dificuldade crescente.
* **Combate por Turnos:** Sistema de batalha realista com gerenciamento de vida e inventário.
* **Cidade e Taverna:** Opções para descansar, recuperar atributos e comprar itens.
* **Sistema de Nível:** Ganho de XP e evolução de personagem (*Level Up*).

## 🏗️ Estruturas de Dados Aplicadas

O diferencial deste projeto é a utilização de conceitos fundamentais de Ciência da Computação:

### 1. Pilha (Stack) - Andares da Masmorra
A masmorra é gerenciada por uma **Pilha estática**.
* **Lógica:** O topo da pilha representa o andar atual. Para avançar, o jogador deve derrotar o monstro e executar um `pop()`.
* **Efeito de Jogo:** Na Taverna, se o jogador descansar, os monstros podem realizar um `push()`, retomando um andar anteriormente conquistado.

### 2. Fila Circular (Circular Queue) - Turnos de Combate
O sistema de turnos utiliza uma **Fila Circular** para alternar entre o jogador e o inimigo.
* **Lógica:** Garante que cada entidade ataque uma vez por rodada de forma cíclica.
* **Vantagem:** Otimização de memória em comparação com uma fila linear simples, evitando o deslocamento desnecessário de elementos.

## 🛠️ Tecnologias e Conceitos

* **Linguagem:** C++
* **Biblioteca Padrão:** `<iostream>`, `<cstdlib>`, `<ctime>`
* **Manipulação de Memória:** Arrays estáticos e controle de índices (`topo`, `inicio`, `fim`).
* **Modularização:** Funções específicas para exibição de menus, combate e lógica de subida de nível.


## 📝 Licença

Este projeto foi desenvolvido para fins educacionais como parte dos estudos de Sistemas de Informação no CEFET-RJ.
