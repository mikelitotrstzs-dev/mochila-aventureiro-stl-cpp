# Relação entre aulas e implementação 

As aulas contêm exemplos e exercícios de treino. Aplicar seus conceitos não
significa copiar todos esses exercícios ou adicionar operadores sem significado.
Esta matriz cobre os temas estruturantes dos seis PDFs.

| Material fornecido | Conceito | Aplicação verificável |
| --- | --- | --- |
| aula_classes_cpp | Classes, atributos, instâncias, métodos, parâmetros e retorno | Personagem guarda estado; curar recebe pontos e retorna bool; testes criam objetos independentes. |
| aula_construtores_cpp | Construtores, sobrecarga e inicialização | Personagem() delega ao construtor com nome; Inventario tem dois construtores; listas de inicialização em todas as entidades. |
| aula_construtores_cpp | Destrutores, estáticos, valor e referência | Item tem destrutor virtual; VIDA_MAXIMA, CAPACIDADE e MAX_QUANTIDADE são constantes estáticas; containers possuem os valores; parâmetros const& evitam cópia. |
| aula_heranca_polimorfismo_cpp | Encapsulamento e validação | Atributos privados; getters const; mutações verificadas por métodos; construtores rejeitam objetos inválidos. |
| aula_heranca_polimorfismo_cpp | protected, herança e construção da base | Item tem construtor protected; Pocao/Equipamento inicializam a base e especializam o comportamento. |
| aula_heranca_polimorfismo_cpp | Abstração, métodos virtuais puros e override | Item define usar/categoria/consumivel; Inventario chama usar por Item*, com despacho dinâmico. |
| aula_ponteiros_modularizacao_cpp | Ponteiro para base, nullptr e tempo de vida | buscar retorna const Item* ou nullptr; os mapas são donos. A interface testa nulidade antes de desreferenciar. |
| aula_ponteiros_modularizacao_cpp | Memória dinâmica e destrutor virtual | O destrutor virtual está aplicado. new/delete não são necessários: containers liberam automaticamente seus elementos. É uma escolha deliberada de gerenciamento seguro. |
| aula_ponteiros_modularizacao_cpp | Modularização, include guards e Makefile | Pares include/src, headers protegidos e regras de compilação/teste/limpeza. |
| aula_sobrecarga_templates_cpp | Operadores de comparação e saída | ResumoItem::operator< ordena; operator== permite find; operator<< fica na interface para apresentar linhas. |
| aula_sobrecarga_templates_cpp | Sobrecarga de funções | Inventario::cadastrar(Pocao) e cadastrar(Equipamento) escolhem o map apropriado. |
| aula_sobrecarga_templates_cpp | Templates de função e classe | limitar<T> limita cura; Resultado<T> transporta retorno tipado; map<K,V> exemplifica template com mais de um parâmetro. |
| aula_stl_cpp | vector, list, set, map, iteradores | Coleções nas consultas, histórico e armazenamento; percursos com const auto& e buscas com iteradores explícitos. |
| aula_stl_cpp | Algoritmos sobre objetos próprios | sort usa ResumoItem::operator<; find é exercitado em teste com operator==. |

## Por que dois mapas?
Um `map<int,Item>` não pode instanciar a base abstrata. Se a base fosse concreta,
armazenar derivados como valores Item perderia sua parte específica (fatiamento).
Os mapas separados preservam tipos e são uma alternativa simples ao vector de
ponteiros proprietários apresentado na aula. A busca unifica ambos como Item*.

## Quem libera a memória?
Os mapas destroem seus elementos quando Inventario sai de escopo. Os ponteiros
retornados por buscar apenas apontam para esses elementos: o chamador nunca
aplica delete. Eles deixam de valer quando o elemento é apagado ou o inventário
é destruído; não devem ser guardados além dessa validade.

## Limites da aplicação das aulas
Não há sobrecarga de ++/-- ou aritmética de itens: essas operações não têm uma
semântica clara aqui. Construtores de cópia e destrutores padrão dos containers
são suficientes; não implementamos cópia manual ou um contador global mutável.
Templates ficam integralmente nos headers, uma exceção técnica ao par de
arquivos usado nas classes comuns. Não há demonstração artificial de new/delete.
