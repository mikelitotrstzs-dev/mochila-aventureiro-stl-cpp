# Plano de implementação

Ler DESCRICAO.md e AGENTS.md antes de cada alteração. Cada etapa termina em
compilação e validação antes do commit. Sem lambdas ou bibliotecas externas.

1. **Domínio:** Item abstrato, Pocao, Equipamento e Personagem em pares
   include/*.hpp e src/*.cpp. Resultado<T> e limitar<T> em headers: templates
   precisam ter definições visíveis no ponto de instanciação. Testar cura,
   polimorfismo, operadores e construtores sem console no domínio.
2. **Inventário:** Inventario e ResumoItem. map<int,Pocao> e
   map<int,Equipamento> guardam objetos concretos sem fatiamento; set<string>
   resume categorias; list<string> mantém histórico; vector<ResumoItem> recebe
   sort via operator<. Buscar devolve const Item* emprestado ou nullptr.
   Testar cada regra e garantir que falhas preservem estado.
3. **Interface:** Interface recebe istream e ostream por referência; main
   apenas instancia e executa. Ler linhas completas e validar números com
   istringstream. Adicionar exemplos com resultados esperados e testes do menu.
4. **Entrega:** Makefile, matriz das aulas, guia de defesa e README com comandos
   reproduzíveis. Rodar testes, cenários e sanitizadores. Revisar arquivos
   rastreados; nenhum binário ou objeto entra no Git.

Mensagens de commit descritivas com prefixos chore/docs/feat/test. O enunciado
não define Conventional Commits; estes prefixos são uma escolha de organização.
Os commits mostram etapas reais e não simulam participação independente do aluno.
