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
