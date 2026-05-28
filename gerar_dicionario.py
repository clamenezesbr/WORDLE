import urllib.request
import string

URL = "https://raw.githubusercontent.com/AlfredoFilho/Palavras_PT-BR/master/Palavras_PT-BR.txt"
SAIDA = "dicionario.txt"

print("Baixando wordlist PT-BR...")
try:
    with urllib.request.urlopen(URL, timeout=30) as response:
        conteudo = response.read().decode("utf-8", errors="ignore")
except Exception as e:
    print(f"Erro ao baixar: {e}")
    exit(1)

letras_validas = set(string.ascii_lowercase)

palavras = set()
for linha in conteudo.splitlines():
    palavra = linha.strip().lower()
    if len(palavra) == 5 and all(c in letras_validas for c in palavra):
        palavras.add(palavra)

palavras_ordenadas = sorted(palavras)

with open(SAIDA, "w", encoding="utf-8") as f:
    for palavra in palavras_ordenadas:
        f.write(palavra + "\n")

print(f"{len(palavras_ordenadas)} palavras de 5 letras salvas em '{SAIDA}'.")
