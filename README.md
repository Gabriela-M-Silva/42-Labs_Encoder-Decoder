# 42-Labs_Encoder-Decoder

Obs.: 

É necessário:
- Organizar funções e arquivos [ ]; 
- Resolver caso de teste para chars repetidos (ex yyyyyyyy) [ ];
- Formatar e melhorar READme [ ];
- Organizar norma dentro do necessário (retirar comentários de teste e resolver/remover obs) [ ];

-------------------
Teste para o Labs em janeiro/2023

Este projeto consistiu na criação de dois programas, o encoder e o decoder.

O encoder com o propósito de comprimir os dados, repassar as informações necessárias para o decoder (optei por enviar a tabela de frequência de caracteres e a string comprimida) e receber de volta as informações de descompressão.
Já o decoder tem o propósito de descomprimir a string a partir dos dados enviados pelo encoder e, por sua vez, enviar ao encoder os dados dessa descompressão (string descomprimida, bytes de ambas e o tempo de descompressão).

Fluxograma que montei para visualizar a ideia inicial:


![Captura de Tela (265)](https://user-images.githubusercontent.com/90937264/212558634-d5d8c30b-6c33-44fd-8b62-91cf0ab7cddb.png)


Depois das considerações básicas, foquei em aprender os conteúdos necessários para o desenvolvimento.
São eles: Algoritmo de Huffman e memória compartilhada.

O Algoritmo de Huffman utiliza diversas estruturas de dados, como lista, árvore de huffman e dicionário.
Cada uma delas necessária para construir a próxima.
Obtendo o dicionário (através do caminho de cada folha na árvore), foi possível realizar a tradução de cada char.
Concatenando esses caracteres, temos a string codificada.
No entanto, isso não a torna comprimida (pelo contrário, ocupa ainda mais espaço, pois cada 0 e 1 está sendo tratado como char).
Nesse caso, devemos realizar operações até que conjuntos de 8 em 8 sejam representados em novos chars.
E por fim, concatenar esses chars em uma nova string (agora possuindo de fato um tamanho menor, pois os caminhos da árvore, a nível de bit, são menores que sua representação normal em binário). 
Para descomprimir, o decoder criará novamente a árvore e irá percorrer os caminhos (até cada folha) através do padrão de bits dos caracteres da string comprimida. Como cada folha salva um caracter, cada vez que chegarmos até uma, significa que percorremos o código que é sua representação. Dessa forma, montamos a string original novamente.

A memória compartilhada é uma forma de fazer ambos os programas "conversarem" entre si, pois podem acessar os dados que o outro salvou naquele ambiente.
A função shmget cria o segmento de memória compartilhado.
Já a shmat vincula a variável com o segmento de memória.
Além disso, a função shmdt desvincula a variável e a shmctl remove o segmento de memória compartilhada. 

Um conhecimento que pude aprofundar foi o bitwise, pois precisei usar as seguintes operações:
  - Deslocamento a esquerda (<<) para criar máscaras;
  - Operador AND (&) para testar se o bit está ligado;
  - E o Operador OR (|) para ativar um bit desligado.
<br>Foram necessárias no procedimento de compressão e/ou descompressão.
