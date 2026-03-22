✖️⭕ Jogo da Velha (Tic-Tac-Toe) em C
===================================

* * * * *

✨ Visão Geral do Projeto
------------------------

Este projeto implementa um **Jogo da Velha completo em C**, com sistema de login, estatísticas, partidas salvas, bot e interface colorida --- atendendo todos os requisitos da disciplina de Estrutura de Dados.

* * * * *

📌 Funcionalidades (com Dropdown)
---------------------------------

### 🔽 **1\. Programação Estruturada / OOP em C**

<details> <summary><strong>Clique para expandir</strong></summary>

O sistema utiliza:

-   `struct Usuario` e `struct Partida` para organizar dados.

-   Uso intensivo de **ponteiros** para manipular as estruturas.

-   Código modular, simulando princípios de orientação a objetos.

</details>

* * * * *

### 🔽 **2\. Sistema de Login e Registro**

<details> <summary><strong>Clique para expandir</strong></summary>

Inclui:

-   Cadastro de usuários.

-   Autenticação com nome e senha.

-   **Mascaramento de senha com `*`** durante a digitação.

-   Dados persistidos em **usuarios.txt**.

</details>

* * * * *

### 🔽 **3\. Persistência de Dados (Estatísticas)**

<details> <summary><strong>Clique para expandir</strong></summary>

O arquivo `usuarios.txt` guarda:

-   Nome do usuário

-   Senha

-   Vitórias

-   Derrotas

Persistência automática após cada partida.

</details>

* * * * *

### 🔽 **4\. Modos de Jogo**

<details> <summary><strong>Clique para expandir</strong></summary>

-   Jogador **vs. Jogador** (com login ou como convidado)

-   Jogador **vs. Bot** (exige login)

-   Controle de turnos

-   Tabuleiro totalmente colorido

</details>

* * * * *

### 🔽 **5\. Resgate de Partidas (Salvar/Carregar)**

<details> <summary><strong>Clique para expandir</strong></summary>

O estado da partida é salvo em:

`partidas.txt`

O arquivo armazena:

-   Tabuleiro

-   Jogador atual

-   Informações da rodada

O jogador pode continuar uma partida inacabada a qualquer momento.

</details>

* * * * *

### 🔽 **6\. Estatísticas e Ranking**

<details> <summary><strong>Clique para expandir</strong></summary>

Exibe:

-   Nome do jogador

-   Vitórias

-   Derrotas

O ranking é montado a partir de `usuarios.txt`.

</details>

* * * * *

### 🔽 **7\. Interface Colorida**

<details> <summary><strong>Clique para expandir</strong></summary>

Utilização da biblioteca:

`#include <windows.h>`

Com ela, o jogo exibe:

-   Tabuleiro colorido

-   Mensagens destacadas

-   Melhor legibilidade

</details>

* * * * *

⚙️ Tecnologias e Compilação
---------------------------

### 🔽 **Dependências**

<details> <summary><strong>Clique para expandir</strong></summary>

-   Linguagem: **C**

-   Compilador: **GCC**

-   Sistema Operacional: **Windows**

    -   Necessário por causa de `windows.h`

</details>

* * * * *

### 🔽 **Como Compilar e Executar**

<details> <summary><strong>Clique para expandir</strong></summary>

Para compilar:

`gcc "Jogo da velha.c" -o jogo_da_velha.exe`

Para executar:

`jogo_da_velha.exe`

</details>
