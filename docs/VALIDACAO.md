# Validação executada

Data: 17/10/2026. Comandos executados de fato no ambiente Linux desta sessão.

## Compilação e testes

```bash
g++ -std=c++11 -Wall -Wextra -pedantic src/*.cpp -Iinclude -o sistema
make test
ASAN_OPTIONS=detect_leaks=0 make sanitize
```

Resultado: compilação sem avisos; três suites C++ e três cenários passaram.
AddressSanitizer e UndefinedBehaviorSanitizer não reportaram erros na execução
com detecção de vazamentos desativada. A primeira tentativa com LeakSanitizer
ativo falhou por restrição do ambiente: não conseguiu abrir /proc/.../task.
Portanto **não foi concluída uma verificação de vazamentos**. Isso não equivale
a um erro detectado no gerenciamento de memória do programa.

## Casos verificados

- Construtores válidos e inválidos; nome aparado; getters const.
- Despacho virtual de poção e equipamento por ponteiro da base.
- Cura limitada a 100 e recusa com vida cheia sem consumir.
- Equipar duas vezes não acumula bônus; troca substitui o anterior.
- Código ausente; duplicado inclusive entre classes concretas.
- Inventário, categorias e histórico vazios.
- Peso exatamente 20000 g e rejeição acima disso.
- Quantidade 1000, zero, negativa, acima do limite e INT_MAX.
- Descarte insuficiente e bloqueio de equipamento ativo.
- Remoção da última unidade e reutilização do código.
- Independência entre cópias do inventário.
- Ordem de nome e desempate por código; find com operator==.
- Texto, número com sufixo, número fora da faixa e overflow na leitura.
- Nome vazio e fim de entrada, inclusive durante cadastro parcial.
- Rejeição de personagem inicial equipado com catálogo vazio.
- Falhas de regras não geram histórico; vida cheia não muda o estoque.

Os cenários verificam trechos esperados da saída. As suites C++ verificam os
estados correspondentes. Não há alegação de cobertura exaustiva ou prova formal.

## Organização

`git diff --check` sem erros. Código e documentação em commits de etapas reais.
Artefatos de build são ignorados pelo Git e excluídos do pacote final.
README registra o auxílio real da IA e as pendências de autoria do enunciado.
O sistema não contém inferência de IA nem persistência, que não são requisitos
obrigatórios. Não foi verificado em Windows ou macOS nesta sessão.
