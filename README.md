# Mochila do Aventureiro

Projeto da Unidade 2 de Linguagem de Programação I: inventário de RPG em
**C++11**, com STL, herança e interface de texto. Usa somente a biblioteca padrão.
O auxílio de IA ocorreu no desenvolvimento; o executável não contém modelo de
aprendizado de máquina, não usa API, não requer chave e funciona offline.

## Arquivos

```text
.
├── AGENTS.md              instruções originais do modelo fornecido
├── ENUNCIADO.md           enunciado original da atividade
├── DESCRICAO.md           especificação proposta, anterior ao código
├── PLANO.md               implementação por etapas
├── README.md
├── Makefile
├── include/               declarações das classes e templates
├── src/                   implementação, interface e main
├── exemplos/              entradas e trechos de saída esperada
├── tests/                 testes C++ e execução dos cenários
```

Uma classe comum por par `.hpp`/`.cpp`, com include guards. `Resultado<T>` e
`limitar<T>` têm definições nos headers para permitir instanciação de templates.
Não há `using namespace std` nos headers, lambdas, `unordered_map`, `new` ou `delete`.

## Compilar e executar

Na raiz do projeto, com um compilador C++11:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic src/*.cpp -Iinclude -o sistema
./sistema
./sistema < exemplos/cenario1.txt
```

No Windows com MinGW, use `-o sistema.exe` e execute `.\sistema.exe`.
As mensagens do programa usam caracteres ASCII para simplificar o terminal.
Não é preciso instalar bibliotecas. `make` é uma alternativa de automação:

```bash
make
make test
make clean
```

Em Linux com GCC e os sanitizadores disponíveis:

```bash
make sanitize
```

Esse alvo usa AddressSanitizer e UndefinedBehaviorSanitizer, recompila e roda
os mesmos testes. As opções `-fno-pie -no-pie` estabilizam o mapeamento de memória
no ambiente de execução utilizado; não são requisitos do programa.
Se o LeakSanitizer não puder acessar `/proc` num ambiente restrito, execute
`ASAN_OPTIONS=detect_leaks=0 make sanitize`. Nesse caso a verificação de vazamentos
não ocorre; AddressSanitizer e UndefinedBehaviorSanitizer continuam ativos.

## Menu

| Opção | Ação |
| --- | --- |
| 1 | Cadastrar poção: código, nome, peso em gramas e cura |
| 2 | Cadastrar equipamento: código, nome, peso e bônus |
| 3 | Coletar mais unidades de item existente |
| 4 | Usar poção ou equipar item |
| 5 | Descartar quantidade de um item |
| 6 | Listar por nome e código |
| 7 | Buscar por código |
| 8 | Consultar personagem, peso e categorias presentes |
| 9 | Mostrar histórico das operações bem-sucedidas |
| 0 | Encerrar |

O personagem começa com vida 50/100 e ataque base 10. A capacidade é 20000 g;
quantidades vão de 1 a 1000 por código. Poções são consumidas só quando curam.
Um único equipamento fica ativo, e a troca substitui o bônus. Não se descarta
item ativo. Cadastro duplicado e erros de regra não alteram o estado.
Dados não são salvos entre execuções. Todos os exemplos são fictícios.
Nomes são limitados a 60 bytes de `std::string` (ASCII corresponde a 60 caracteres);
a ordenação é lexicográfica por bytes, sem colação específica do português.

## Onde uso a STL

| Inventario | `map<int,Pocao>` e `map<int,Equipamento>` | Código único e busca O(log n); tipos concretos por valor evitam fatiamento e propriedade manual de memória. |
| Inventario::categorias | `set<string>` | Categorias atuais únicas e ordenadas; derivar do estoque evita categorias obsoletas. |
| Inventario::historico | `list<string>` | Acrescenta eventos ao fim e preserva ordem; aplica a lista da aula. Um vector também seria adequado neste uso apenas sequencial. |
| Inventario::listar | `vector<ResumoItem>` | Projeções por valor com acesso aleatório exigido por sort. |
| Inventario::listar | `std::sort` | Ordena objetos da classe ResumoItem com seu operator<: nome, depois código; O(n log n). |
| Inventario::buscar | `map::find` | Consulta sem criar entrada; diferentemente de operator[]. |
| tests/inventario.cpp | `std::find` | Exercita operator== de ResumoItem; não substitui a busca eficiente por chave no sistema. |

`pesoTotal()` percorre os mapas, O(n). Coleta/cadastro também fazem essa soma
para validar a capacidade. Logo a operação completa é O(n), mesmo que a busca
por código seja O(log n). A geração das categorias é O(n log c), c categorias.
As listagens retornam cópias; não expõem os containers internos para alteração.

## Como usei a IA


- Ferramenta: ChatGPT Work, agente Codex. GPT-6.1 Sol.
- Pedido recebido: desenvolver o projeto, com dica de uso do assunto sobre "STL",
e dica de qual projeto fazer.
- Processo realizado: especificação em rascunho, revisão de ambiguidades, plano,
  domínio, inventário, interface, testes e documentação em commits separados.
- Pedido que deu certo, na experiência do aluno: Formulação do codigo base e implementações
futuras.
- Pedido que deu errado e sua correção: Dificuldades em entender os questionamentos da
IA por conta de dificuldades com o conteúdo, me baseie pelo conteúdo em pdf para poder 
seguir, mas a IA ajudou em grande parte.
- Decisão técnica da IA: objetos concretos por valor e ponteiros emprestados
  dispensam alocação manual. Não atribuir essa decisão ao estudante.

## Verificação e estudo

`make test` executa três suites de testes C++ com assert habilitado e três
cenários de console.  e o histórico mantém descrição antes do código e commits por etapa.
