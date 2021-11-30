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

# Avaliação

## Código | Funcionalidades
1. Classe forca 5/10
- Vou considerar 50% do trabalho uma vez que boa parte dos métodos está adiantados

2. Interface textual 5/10
- A interface inicial está ok, acho que poderia ter tido um esforço maior pra desenhar pelo menos a forca =).

3. Execução completa do jogo 3/15
- Menus iniciais funcionando, mas o restante não.

4. Validação dos arquivos de texto 5/5
- ficou bom =0

5. Arquivos de teste de validação dos casos de erro 0/5
- A ideia aqui era fazer um conjunto de arquivos de teste que pudessem ser usados para mostrar a validação

6. Arquivos de teste de validação dos níveis de dificuldade 1/5
- A ideia aqui era vc prover alguns arquivos que ajudassem a testar os níveis de dificuldade, princpialmente
o gameover quando todas as palavras para aquela dificuldade acabam.

7. Observações gerais
- Como te falei o código está num nível muito bom, sugiro que procure uma dupla nesse segundo trabalho para dividir
um pouco as atividades.

## Código | Boas práticas

1. Documentação do código e readme 5/10
- Não foram documentadas as novas constantes ou métodos criados

2. Organização e indentação 10/10

3. Compilação automatizada 5/5

