# Revisão prévia de ambiguidades

Decisões da IA para tornar o rascunho executável; ainda dependem de revisão autoral.

| Questão | Decisão |
| --- | --- |
| Peso decimal? | Inteiros em gramas evitam arredondamento. |
| Equipamento é consumido? | Não; apenas poções são consumidas. |
| Quantidade zero? | Apagar entrada; código pode ser reutilizado. |
| Texto com espaços? | Remover espaços nas extremidades; preservar os internos. |
| Nome duplicado? | Permitido; identidade é o código. |
| Vida cheia? | Rejeitar poção sem consumir. |
| Mesmo equipamento? | Rejeitar sem acumular bônus. |
| Falha de leitura? | Repetir campo; EOF encerra sem mutação parcial. |
| Memória dinâmica manual? | Não é necessária: mapas de tipos concretos preservam polimorfismo. |

Não houve rodada de perguntas respondidas pelo estudante. As decisões acima
são propostas explícitas, não respostas atribuídas a ele.
