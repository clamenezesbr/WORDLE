# 🟩 Quase Wordle em C

Um mini-clone do clássico jogo **Wordle**, escrito em linguagem C para rodar no terminal.  
Ideal para praticar lógica, manipulação de arquivos e strings!


```
Update Here: #readme2.md
```

---



## 🎯 Objetivo

Adivinhar uma **palavra de 5 letras** escolhida aleatoriamente entre várias disponíveis no `dicionario.txt`.  
Você tem **6 tentativas** para acertar!

---

## 🕹️ Como Jogar

- Digite palavras de 5 letras por tentativa.
- O jogo valida se a palavra existe no dicionário.
- A cada tentativa, um feedback será mostrado:

| Símbolo | Significado                          |
|:--------:|--------------------------------------|
| `^`      | Letra correta na **posição correta** |
| `!`      | Letra correta na **posição errada**  |
| `x`      | Letra **incorreta**                  |

---

## 📁 Estrutura do Projeto

```
📂 QuaseWordle/
├── main.c            # Código-fonte do jogo
├── dicionario.txt    # Lista de palavras válidas (5 letras)
├── scores.txt        # Registro das partidas vencidas
└── README.md         # Este arquivo
```

---

## ⚙️ Como Compilar

Certifique-se de ter o compilador `gcc` instalado.  
No terminal, execute:

```bash
gcc main.c -o wordle
```

---

## ▶️ Como Rodar

Após a compilação, execute o programa com:

```bash
./wordle
```

---

## 💾 Funcionamento Interno

- ✅ Apenas palavras de 5 letras são consideradas válidas.
- 📚 As palavras são lidas do arquivo `dicionario.txt`.
- 🎯 Uma palavra aleatória é escolhida para cada rodada.
- 📃 Jogadores que acertam têm seus dados registrados em `scores.txt`, incluindo:
  - Nome do jogador
  - Palavra correta
  - Número de tentativas usadas
  - Timestamp

---

## 🧪 Exemplo de Jogo

```text
Bem-vindo ao quase Wordle!

Uma palavra de 5 letras foi escolhida aleatoriamente do dicionário.
Tente adivinhar qual é!

Tentativa 1 de 6: CASAR
Resultado: x^x!x
```

---

## 👨‍💻 Autor

**Gabriel Menezes**  
🔗 [LinkedIn](https://www.linkedin.com/in/gabriel-resende-menezes)  
📧 gabriel.menezes@outlook.com

---

## ⭐ Dê uma estrela

Se curtiu o projeto, deixe uma ⭐ no repositório para apoiar e ajudar na divulgação!
