# 💻 Trabalho 1
Repositório contendo as especificações e implementação do Trabalho 1 da disciplina de LP1

# 📄 Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1X3VDW6EBE_ZRDHCoRNwqva17R1EZMpwDunRgDg9N4HU/edit?usp=sharing). Preencha o [author.md](author.md) com as informações relativas ao grupo/autor.

# ⚙️ Como compilar

1. Faça o download deste repositório para sua máquina
2. Entre na pasta do repositório
3. Execute o seguinte comando no seu terminal, informando os arquivos de palavras e scores:
```
mkdir bin && \
cd bin && \
cmake .. && \
cmake --build . && \
./forca <seu arquivo de palavras> <seu arquivo de scores>
```

Você pode usar os arquivos da pasta `arquivos` para testar o programa também.
