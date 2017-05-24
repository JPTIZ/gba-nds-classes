C++: Aritmética de Ponteiros
============================

Apesar de **dever** ser evitada, em C e C++ é possível somar e subtrair um
ponteiro por um número inteiro qualquer. Isso fará com que caminhemos pela
memória a partir do endereço guardado pelo ponteiro.

Exemplo de aritmética de ponteiros:

```c++
auto pointer = (std::uint16_t*)0; // Aponta para o endereço 0 como um inteiro sem sinal de 16 bits (2 bytes)
auto another = pointer + 5; // another = 0 + 5 índices * 2 bytes = endereço 10
auto some_other = (std::uint64_t*)pointer + 5; // 0 + 5 índices * 4 bytes = endereço 20

struct A {
    int a, b;
};

auto a = (A*)0; // Um ponteiro para algo do tipo `A`
a += 5; // a = 0 + 5 * sizeof(A)
```

Utilidade em vetores
--------------------

Aritmética de ponteiros pode ser útil para iterar por vetores **apesar de que você não deve**:

O código abaixo zera todos os elementos do vetor:
```c++
int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
for (auto it = array; it != array + 10; ++it) { // `it` possui o endereço inicial de array,
                                                // assim, incrementar `it` faz com que caminhe
                                                // pelo array
    *it = 0;
}
```

Da mesma forma, podemos utilizar para acessar um elemento específico do array:

```c++
int* array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
*(array + 3) = 42; // array[3] = 42
```

O código abaixo é exatamente equivalente a:
```c++
int* array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
array[3] = 42;
```

Isso será útil quando acessando elementos que são **conceitualmente** um vetor, como por exemplo a VRAM:

```c++
unsigned short* vram = (unsigned short*)0x6000000;
vram[0] = 0x3ff; // Pixel (0, 0) = amarelo
vram[4 + 240 * 3] = 0x1f; // Pixel (4, 3) = vermelho
```

sizeof(...)
-----------

Perceba o uso da função `sizeof` no último exemplo anterior. `sizeof(algo)`
retorna quantos bytes tem o tipo (ou variável/constante) `algo`.

```c++
sizeof(char)  // 1 (em arm7, x86, x86_64)
sizeof(short) // 2 (em arm7, x86, x86_64)
sizeof(int)   // 4 (em arm7, x86, x86_64)
sizeof(long)  // 4 (em arm7, x86) ou
              // 8 (em x86_64)

sizeof(long long) // 8 (em arm7, x86, x86_64)
```
