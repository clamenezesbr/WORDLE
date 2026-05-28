# Atualizações Recentes

Este arquivo documenta as novas funcionalidades adicionadas ao projeto após a versão original em C.

---

## Interface Web Cyberpunk (`index.html`)

O jogo ganhou uma versão web completa, acessível direto no navegador, sem necessidade de compilar código C.

### Como rodar

**Recomendado — com o servidor Node.js (salva no `scores.txt`):**

```bash
node server.js
# ou
npm start
```

**Alternativa — sem salvar no arquivo:**

```bash
python3 -m http.server 8080
```

Acesse `http://localhost:8080` no navegador. O jogo carrega o `dicionario.txt` automaticamente.

---

## Servidor local (`server.js`)

Servidor HTTP simples em Node.js, sem dependências externas, que integra o front-end com o `scores.txt`.

### Endpoints

| Método | Rota           | Descrição                                      |
|--------|----------------|------------------------------------------------|
| GET    | `/api/scores`  | Retorna todas as partidas do `scores.txt` em JSON, ordenadas por tentativas |
| POST   | `/api/scores`  | Adiciona uma nova entrada ao `scores.txt`       |
| GET    | `/*`           | Serve arquivos estáticos da pasta do projeto   |

### Formato do `scores.txt`

Compatível com a versão C. Cada linha representa uma vitória:

```
NOME PALAVRA TENTATIVAS TIMESTAMP
```

Exemplo:
```
GABRIEL CAMPO 3 1748000000
```

---

## Funcionalidades do jogo web

- **Dicionário original** — carrega o mesmo `dicionario.txt` da versão C, filtrando palavras de 5 letras
- **Lógica fiel** — mesma mecânica de avaliação: letra correta na posição, letra na posição errada, letra ausente
- **Teclado virtual** — suporte a clique e teclado físico, incluindo `Ç`
- **Animações** — flip nas letras ao revelar, shake em tentativa inválida, bounce ao vencer
- **Fallback** — sem servidor, usa `localStorage` automaticamente

---

## Sistema de Pontos

Pontos são concedidos apenas ao vencer. Quanto menos tentativas, mais pontos.

| Tentativa | Pontos base |
|:---------:|:-----------:|
| 1ª        | 1000        |
| 2ª        | 850         |
| 3ª        | 700         |
| 4ª        | 500         |
| 5ª        | 300         |
| 6ª        | 150         |

**Multiplicador de streak:** cada vitória consecutiva aumenta o multiplicador em +0.15 (máximo ×2.5). Perder zera o streak.

Exemplo: 3ª tentativa com streak de 4 → `700 × (1 + 4×0.15) = 700 × 1.60 = 1120 pts`

---

## Header HUD

Barra fixa no topo com informações em tempo real. O nome do jogador é clicável para alteração.

| Campo   | Descrição                                          |
|---------|----------------------------------------------------|
| JOGADOR | Nome do operador — clique para alterar             |
| PONTOS  | Score acumulado da sessão                          |
| STREAK  | Vitórias consecutivas atuais                       |
| RECORDE | Maior pontuação já atingida                        |
| V/D     | Proporção de vitórias e derrotas                   |
| PLACAR  | Abre o placar geral com todas as partidas do arquivo |
| AJUDA   | Abre as instruções do jogo                         |

---

## Bugs corrigidos

| Problema | Correção |
|----------|----------|
| Streak exibido incorretamente no modal de vitória | O streak anterior à vitória é salvo antes do incremento e usado no cálculo do multiplicador |
| Teclado disparando durante modais ou antes do jogo iniciar | Flag `_modalOpen` e verificação de `S.word` bloqueiam input fora de hora |
| Teclas do modal vazavam para o jogo | Listener ignora eventos quando o foco está em um `<input>` |

---

## Estrutura de arquivos atualizada

```
WORDLE/
├── main.c            # Versão original em C (terminal)
├── index.html        # Versão web — jogo completo no navegador
├── server.js         # Servidor Node.js — integra front-end com scores.txt
├── package.json      # Script "start": node server.js
├── dicionario.txt    # Dicionário compartilhado entre as duas versões
├── scores.txt        # Registro de partidas (versão C e versão web)
├── README.md         # Documentação original
└── README2.md        # Este arquivo
```

---

## Autor

**Gabriel Menezes**
