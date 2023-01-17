# 42 Labs 4º Edição - Compressor de dados
O desafio proposto pela [42 São Paulo](https://www.42sp.org.br/) na 4º edição do Labs foi desenvolver duas aplicações para compressão (`encoder`) e descompressão (`decoder`) de dados usando o **Algortimo de Huffman** e **Memória Compartilhada**, dadas as seguintes [instruções](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/INSTRUCTIONS.md).

<div align="center">

![Exibição do projeto](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/img/data_compressor.gif)  

</div>

## Sumário

- [Conceitos aplicados](#conceitos-aplicados)
    - [Algoritmo de Huffman](#algoritmo-de-huffman)
        - [Criação de uma Ávore de Huffman](#criação-de-uma-árvore-de-huffman)
        - [Referências](#referências)
    - [Memória compartilhada](#memória-compartilhada)
        - [Referências](#referc3aancias-1)
- [Visão geral do projeto](#visão-geral-do-projeto)
- [Setup](#setup)
- [Considerações finais](#considerações-finais)

## Conceitos aplicados

### Algoritmo de Huffman
David A. Huffman foi um estudante de engenharia elétrica no Instituto de Tecnologia de Massachusetts (MIT) durante os anos 1950, que para ser aprovado em sua disciplina de Teoria de Informação escreveu seu trabalho de conclusão de curso com uma solução à seguinte problemática, *"Dada uma coleção de letras, números e outros símbolos, encontre o método mais eficiente de representá-los usando um código binário"*.

Huffman resolveu sem saber, na época, que este era o problema básico da compressão de dados que não havia sido resolvido até então.

<div align="center">

![Esquema de rede de comunição](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/img/rede_de_comunicacao.png)  

</div>

A solução proposta ao problema ficou conhecida como Algoritmo de Huffman, e se tornou popular ao atender os requisitos abaixo.

- Cada carácter é representado por apenas um código binário;
- A mensagem original deve ser igual a mensagem recebida, não há perda de dados;
- Decodificação única, não há ambiguidade entras as mensagens;

A técnica desenvolvida por Huffman funciona através da criação de uma [árvore binária](https://en.wikipedia.org/wiki/Binary_tree), onde cada nó pode ser um nó folha (*leaf*) ou um nó interno. Inicialmente todos os nós são folhas, que contém um carácter (*c*) e o peso deste carácter (frequência de aparição). Nós internos contém o peso do carácter e referência a dois nós filhos. Por convenção os nós da esquerda são representados por `0`, enquanto `1` representa os nós da direita.

Para construir a árvore binária usada neste projeto utilizei uma [fila de prioridade](https://en.wikipedia.org/wiki/Priority_queue), é a através desta estrutura que a frequência de cada carácter é calculada.

#### Criação de uma árvore de Huffman

Considere o seguinte texto:

```sh
ADBADEDBBDD
```

Ao calcular a frequência de cada carácter temos:
| Carácter | Frequência  |
|  :---:   |    :---:    |
|    E     | 1/11 = 0.09 |
|    A     | 2/11 = 0.18 |
|    B     | 3/11 = 0.29 |
|    D     | 5/11 = 0.45 |

A contrução dá árvore é iniciada com seus menores valores, neste caso **E(1)** e **A(2)**, da seguinte forma.

<div align="center">

![Representação dos dois menores nós de uma árvore de Huffman](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/img/huffman_tree_1.png)  

</div>

O nó **B(3)** é o próximo nó incluído à árvore, acima dos nós **E(1)** e **A(2)**.

<div align="center">

![Representação de uma árvore de Huffman contendo três nós](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/img/huffman_tree_2.png)  

</div>

Por fim o maior nó, **D(5)**, é adicionado à estrutura abaixo da raiz da árvore.

<div align="center">

![Representação de uma árvore de Huffman de quatro nós](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/img/huffman_tree_3.png)  

</div>

#### Referências
- [Huffman Codes: An Information Theory Perspective](https://www.youtube.com/watch?v=B3y0RsVCyrw)
- [Techie Delight: Huffman Coding Compression Algorithm](https://www.techiedelight.com/huffman-coding/)
- [Brilliant: Huffman Code](https://brilliant.org/wiki/huffman-encoding/)
- [University of Virgina: Data Compression](http://www.ece.virginia.edu/~ffh8x/moi/compression.html)
- [Huffman's A Method ofr the Construction of Minimum Redundancy Code](http://compression.ru/download/articles/huff/huffman_1952_minimum-redundancy-codes.pdf)
- [Innas Pivkina's Discovery of Huffman Codes](https://www.maa.org/sites/default/files/images/upload_library/46/Pengelley_projects/Project-14/Huffman.pdf)
- [Data Compression](https://www.ibm.com/docs/en/cmofz/10.1.0?topic=overview-data-compression)

---

### Memória compartilhada
Memória compartilhada é uma maneira eficiente de transmitir dados entre programas. Um programa cria uma porção de memória que outros processos, dadas as devidas permissões, podem acessar.

Há duas formas de implementar uma memória compartilhada, `shmget()` e `mmap()`, sendo a segunda mais atual.

#### Referências

- [Memory sharing in Linux with MMAP](https://blog.minhazav.dev/memory-sharing-in-linux/)
- [Sharing Memory Between Processes](https://techpubs.jurassic.nl/manuals/0630/developer/T_IRIX_Prog/sgi_html/ch03.html)
- [Wikipedia: Shared memory](https://en.wikipedia.org/wiki/Shared_memory)
- [Use shmget to Allocate Shared Memory in C](https://www.delftstack.com/howto/c/shmget-example-in-c/)
- [Stack Overflow](https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c)
- [IPC through Shared Memory](https://www.javatpoint.com/ipc-through-shared-memory)


## Visão geral do projeto
Para me auxiliar durante o desenvolvimento desenhei os processos executados pelos programas `encoder` e `decoder`, ambos podem ser conferidos em formato `.xml` no diretório [bpmn](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/bpmn).

<div align="center">

![Representação dos programa ./encoder em notação BPMN](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/bpmn/bpmn_encoder.svg)  

![Representação dos programa ./decoder em notação BPMN](https://github.com/42sp/42labs-selection-process-v4-humbertoarndt/blob/master/bpmn/bpmn_decoder.svg)  

</div>

## Setup
- Clonar o projeto em seu ambiente.
```sh
git clone https://github.com/42sp/42labs-selection-process-v4-humbertoarndt.git
```

- Compilar o projeto através do Makefile para gerar os programas `encoder` e `decoder`.

```sh
make
```

- Regras disponíveis no Makefile:
    - `all` regra padrão de compilação;
    - `clean` deleta objetos criados durante a compilação;
    - `fclean` deleta arquivos binários executáveis;
    - `re` deleta objetos, binários executáveis e re-compila o projeto;

- Crie um arquivo que contenha dados.

```sh
echo > <file_name> <your_text>
```

- Execute o `encoder` com o arquivo criado para gerar um arquivo comprimido `.huff`.

```sh
./encoder <file_name>
```

- Execute o `decoder` com o arquivo `.huff` para descomprimí-lo, e gerar um arquivo `_copy`

```sh
./decoder <file_name.huff>
```

## Considerações finais
Participar do processo seletivo do Labs é uma oportunidade bem valiosa, dado seu prazo curto é legal ver a comunidade se unir para combater um inimigo em comum.

Da maneira que me organizei acabei não tendo muito tempo para explorar mais como funciona **memória compartilhada**, ou para ajudar mais os demais cadetes, então senti falta de mais tempo durante o processo.

Ao meu ver o ponto mais forte do Labs é a ênfase em produzir uma documentação mínima do projeto entregue. Durante o currículo este ponto não aparece muito, fica a cargo do estudante documentar ou não seu projeto. Dou bastante importância a este aspecto por saber o quanto isso ajuda a compartilhar conhecimento.

Pude aprender coisas novas durante o projeto, e me aprofundar ou tentar coisas novas com conceitos que já havia mexido, como manuseio de arquivo por exemplo. Por fim, saio da experiência do Labs com o saldo positivo, apesar de não entregar tudo que foi solicitado, estou contente com o trabalho realizado, e ansioso pelos resultados.
