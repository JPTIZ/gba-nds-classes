C++: auto, 0u, &, \*
====================

auto, 0u
--------

A função de `auto` é **inferir o tipo de uma variável**. Por exemplo:

```c++
auto i = 0;    // int
auto i = -1;   // int
auto i = 0u;   // unsigned int
auto i = 2f;   // float
auto i = 0.;   // double
auto i = 3l;   // long
auto i = 2ul;  // unsigned long
auto i = 5ull; // unsigned long long

int foo() {
    return 5;
}

auto i = foo(); // int
```

Perceba que há sufixos para alguns números. Eles servem justamente para
delimitar o tipo do número sem precisar de conversões, sendo `u` de `unsigned`,
`f` de `float`, `l` de `long`, etc. Infelizmente, por padrão, não há sufixos
para os tipos `short` e `char`, mas você pode [criar o seu próprio desde
C++11](http://stackoverflow.com/a/12152296/3326309) (o link direciona para a
resposta do usuário Ken Smith, que dá uma implementação do sufixo).

**Atenção**: O tipo **não** é dinâmico: uma vez que uma variável foi
inicializada como um `int`, ela continuará sendo `int`.


\* (Ponteiro)
-------------

Um tipo de dado bastante comum de se encontrar é o ponteiro. Um ponteiro guarda
um endereço de memória, supondo que o endereço guarda um determinado tipo de
dado.

```c++
auto i = (unsigned short*)0x6000000; // i guarda o endereço de memória para um número de 16 bits sem sinal
auto j = (unsigned char*)0x6000000;  // j guarda o endereço de memória para um número de 8 bits sem sinal
```

Perceba que `i` e `j` guardam o mesmo endereço de memória. O que vai mudar é a
forma como eles interpretam esses endereços. Por exemplo, quando você carrega o
valor no endereço que `i` guarda (denotado por `*i`), o valor retornado é um
número de 16 bits, enquanto que para `*j` o valor é um número de 8 bits:

```c++
auto value_at_i = *i; // unsigned short
auto value_at_j = *j; // unsigned char
```

É possível também ler o endereço de memória de uma variável, por exemplo:

```c++
auto a = 0;
auto address_of_a = &a;
auto same_address = &a == address_of_a; // true
```

Para alterar o valor em um endereço de memória guardado por um ponteiro, basta
**derreferenciá-lo** com o operador `*`:

```c++
auto vram = (unsigned short*)0x6000000;
*vram = 0x3ff; // altera o primeiro pixel para amarelo
```


& (Referência)
--------------

Em C++, é possível guardar uma referência a um outro valor (seja uma constante,
uma variável ou um endereço de memória). Por exemplo:

```c++
auto a = 0;  // a = 0
auto& b = a; // a = 0, b = 0
a = 5;       // a = 5, b = 5
--b;         // a = 4, b = 4
```

Um detalhe: o valor de b não é copiado, o que acontece é que, por debaixo dos
panos, a linguagem implementa referência através de ponteiros. O código acima, por exemplo, funciona exatamente igual a:

```c++
auto a = 0;
auto b = &a; // b é um `unsigned int*`
a = 5;       // a = 5
*b = *b - 1; // a = 4
```

Lembre-se: uma vez que você referencia um objeto, é ele quem você referencia e pronto. No caso:

```c++
auto a = 0;  // a = 0
auto b = 1;  // a = 0, b = 1
auto& c = a; // a = 0, b = 1
c = b;       // a = 1, b = 1 => `a` foi alterado, pois `c` referencia `a`
```
