# ⚔️ Sword Art World - RPG em C++

Um jogo de RPG de texto desenvolvido em C++ que simula a exploração de um mundo mágico. O projeto foi construído em três etapas para a disciplina de Estruturas de Dados II, evoluindo de um sistema linear de masmorras para um mundo aberto explorável com árvore de habilidades, utilizando estruturas de dados avançadas.

## 🚀 Funcionalidades

- **Sistema de Classes:** Escolha entre Guerreiro ou Mago, cada um com atributos focados e sua própria rota de evolução.
- **Árvore de Habilidades (Skill Tree):** Sistema de progressão avançado onde o jogador utiliza *Skill Points* (SP) ganhos no *Level Up* para desbloquear melhorias contínuas.
- **Exploração de Mapa (Grafo):** Navegação entre diferentes locais (Vila, Floresta, Caverna, etc.) com verificação de caminhos válidos.
- **Sistema de Combate:** Batalhas por turnos com inimigos carregados dinamicamente com base na localização.
- **Cidade e Loja:** Opções para descansar na Taverna e comprar poções e elixires.
- **Sistema de Progressão:** Ganho de XP, Ouro e evolução de personagem (*Level Up*).

## 🌳 Estruturas de Dados Aplicadas (V3.0 - Atual)

A terceira etapa do projeto adicionou profundidade à progressão do personagem, aplicando o conceito de hierarquia e dependência de habilidades.

### 1. Árvore AVL - Árvore de Habilidades
Implementada como uma **Árvore Binária de Busca Auto-balanceada (AVL)**.
- **Lógica:** A estrutura organiza as habilidades disponíveis alfabeticamente para buscas eficientes e se auto-balanceia a cada nova inserção utilizando **Rotações (Simples e Duplas, à Direita e à Esquerda)**, calculadas através do Fator de Balanceamento dos nós.
- **Integração no Jogo:** Cada nó da árvore armazena bônus de status (Ataque e HP) e uma chave string de `requisito`. Ao tentar desbloquear uma nova habilidade gastando *SP*, o sistema executa uma busca $O(\log n)$ na AVL para validar se a habilidade "pai" exigida já foi previamente aprendida, efetivando a progressão e aplicando os bônus no jogador.

## 🗺️ Estruturas de Dados Aplicadas (V2.0)

A segunda etapa do projeto exigiu a transição do jogo para um mapa aberto e um sistema de busca otimizado de inimigos, utilizando Classes, Vetores Nativos e Matriz de Adjacências conforme padrão da disciplina.

### 1. Grafo - Mapa do Jogo
Implementado utilizando uma **Matriz de Adjacências**.
- **Lógica:** Cada vértice representa um local do mapa (Ex: Vila Segura, Floresta Escura) e as arestas não-direcionadas representam as rotas de viagem. Cada nó do grafo também armazena a "Chave" do monstro que habita o local.
- **Efeito de Jogo:** Impede o jogador de viajar para locais desconectados e permite que os monstros habitem áreas específicas do mapa.

### 2. Tabela Hash - Bestiário de Inimigos
Armazena os status completos dos inimigos (HP, Força, XP, Ouro).
- **Lógica:** A busca é feita em tempo constante $O(1)$ usando o nome do monstro como chave. O tratamento de colisões foi feito utilizando **Encadeamento (Lista Encadeada)** com Struct de Nós.
- **Integração:** Ao viajar pelo Grafo, o jogo coleta a chave do vértice atual e consulta a Tabela Hash instantaneamente para iniciar o combate com os status corretos.

## 🧱 Estruturas de Dados Aplicadas (V1.0 - Legado)

*(Nota: A versão original com Pilha encontra-se preservada no histórico deste repositório através da tag `v1.0`. A Fila Circular segue ativa no sistema de combate atual).*

### 1. Pilha (Stack) - Andares da Masmorra
A masmorra era gerenciada por uma **Pilha estática**. 
- **Lógica:** O topo da pilha representava o andar atual. O avanço ocorria "desempilhando" (Pop) andares, e o recuo (monstros retomando andares durante o descanso) por empilhamento (Push).

### 2. Fila Circular (Circular Queue) - Turnos de Combate
O sistema de turnos utiliza uma **Fila Circular** para alternar entre o jogador e o inimigo.
- **Lógica:** Garante que cada entidade ataque uma vez por rodada de forma cíclica, otimizando a memória ao evitar deslocamentos de array desnecessários.

## 🛠️ Tecnologias e Conceitos

- **Linguagem:** C++
- **Biblioteca Padrão:** `<iostream>`, `<cstdlib>`, `<ctime>`, `<string>`
- **Manipulação de Memória:** Arrays estáticos, controle de índices, ponteiros e structs.
- **Modularização:** Classes independentes projetadas para isolar as lógicas da Árvore AVL, do Grafo, da Tabela Hash e da Fila Circular.

## 📝 Licença e Autoria

Projeto prático desenvolvido para a disciplina de **Estruturas de Dados II** do curso de Bacharelado em Sistemas de Informação.

🎓 **Instituição:** Centro Federal de Educação Tecnológica Celso Suckow da Fonseca (CEFET-RJ)  
👨‍🏫 **Professor:** Vladimir Erthal  
💻 **Desenvolvedor:** Filipe da Silva Assumpção