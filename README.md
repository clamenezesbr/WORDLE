Perfeito! Abaixo está a versão ideal do `README.md` para ser usada diretamente no GitHub, com formatação Markdown completa, emojis para destacar e instruções claras:

---

```markdown
# 🟩 Quase Wordle em C

Um mini-clone do clássico jogo **Wordle**, escrito em linguagem C para rodar no terminal.  
Ideal para praticar lógica, manipulação de arquivos e strings!  

---

## 🎯 Objetivo

Adivinhar uma **palavra de 5 letras** escolhida aleatoriamente entre várias disponíveis no `dicionario.txt`. Você tem **6 tentativas** para acertar!

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

````

---

## ⚙️ Como Compilar

1. Certifique-se de ter o GCC instalado.
2. Execute o seguinte comando no terminal:

```bash
gcc main.c -o wordle
````

---

## ▶️ Como Rodar

```bash
./wordle
```

---

## 💾 Funcionamento Interno

* ✅ Apenas palavras de 5 letras são consideradas válidas.
* 📚 As palavras são lidas do arquivo `dicionario.txt`.
* 🎯 Uma palavra aleatória é escolhida para a rodada.
* 📃 Jogadores que acertam têm seus dados salvos em `scores.txt`:

  * Nome
  * Palavra correta
  * Número de tentativas
  * Timestamp da vitória

---

## 🧪 Exemplo de Jogo

```
Bem-vindo ao quase Wordle!

Uma palavra de 5 letras foi escolhida aleatoriamente do dicionário.
Tente adivinhar qual é!

Tentativa 1 de 6: CASAR
Resultado: x^x!x
```

---

## 🙋‍♂️ Autor

**Gabriel Menezes**
🔗 [LinkedIn](https://www.linkedin.com/in/gabriel-resende-menezes/)
📧 [gabriel.menezes@outlook.com](mailto:gabriel.menezes@outlook.com)

---

## ⭐ Dê uma estrela

Se curtiu o projeto, deixe uma ⭐ no repositório para apoiar!

---

```

Se quiser, posso te ajudar a:
- Criar os arquivos `dicionario.txt` e `scores.txt` vazios para upload.
- Criar os badges de status (como linguagem, licença, etc).
- Colocar uma imagem demonstrativa ou GIF no terminal com exemplo do jogo.

É só falar!
```
