# Descrição do sistema

> Rascunho elaborado por IA a pedido do solicitante. O enunciado exige esta
> descrição escrita sem IA: o estudante precisa produzir sua versão autoral
> antes de considerar a entrega integralmente conforme. Este histórico não
> representa uma descrição escrita independentemente pelo estudante.

## Nome e ideia
Mochila do Aventureiro controla o inventário de um personagem fictício de RPG.
Permite cadastrar poções e equipamentos, coletar, usar, descartar e consultar itens.

## O que o sistema guarda
Personagem com nome, vida de 0 a 100, ataque base 10 e um equipamento ativo.
Itens com código inteiro positivo único, nome, peso unitário em gramas e quantidade.
Poções têm cura; equipamentos têm bônus de ataque. A mochila suporta 20000 gramas.
Os dados existem apenas durante a execução; não há persistência nem serviço externo.

## O que dá para fazer
1. Cadastrar poção: código, nome, peso, cura; adiciona uma unidade.
2. Cadastrar equipamento: código, nome, peso, bônus; adiciona uma unidade.
3. Coletar: código e quantidade; acumula unidades de um item existente.
4. Usar: código; poção cura e consome uma unidade, equipamento torna-se ativo.
5. Descartar: código e quantidade; remove unidades e apaga o item quando zerar.
6. Listar: itens em ordem de nome, com código como desempate.
7. Buscar: código; mostra um item ou informa ausência.
8. Resumo: vida, ataque, peso e categorias únicas presentes.
9. Histórico: operações bem-sucedidas na ordem em que ocorreram.
0. Sair. Fim da entrada também encerra sem travar.

## Regras
O personagem começa com 50 de vida. A cura e o bônus variam de 1 a 100.
Peso de 1 a 20000 gramas. Quantidades de 1 a 1000; máximo 1000 por código.
Nomes têm de 1 a 60 caracteres após remover espaços das extremidades.
Códigos não podem repetir, inclusive entre tipos diferentes. Nomes podem repetir.
Poção não é consumida se a vida já está cheia. Cura nunca ultrapassa 100.
Equipamento aumenta o ataque base; trocar substitui o bônus, não o acumula.
Não é possível descartar qualquer unidade do equipamento ativo; é preciso trocar.
Equipar novamente o mesmo código não altera estado nem histórico.
Erros nunca alteram o estado ou entram no histórico.

## Quando algo dá errado
Código ausente, repetição, valor fora da faixa, excesso de peso ou quantidade
insuficiente geram mensagem clara. Listagens vazias dizem que não há dados.
Texto em campo numérico ou números com sufixo são rejeitados e o campo é pedido
novamente. Fim da entrada durante cadastro cancela a operação e encerra.

## Classes que eu imagino
- Item: base abstrata, dados comuns e contrato virtual de uso.
- Pocao: cura e consumo.
- Equipamento: troca de bônus ativo.
- Personagem: estado e validação de vida/equipamento.
- ResumoItem: projeção por valor para consulta e ordenação.
- Inventario: coleções, limites, operações e histórico.
- Interface: entrada e saída; recebe streams para permitir testes.
- Resultado<T>: retorno genérico com sucesso, mensagem e valor.

## Exemplo de uso
Cadastrar poção 1, "Pocao pequena", peso 100, cura 30: sucesso.
Coletar 2 unidades de 1: quantidade 3, peso 300 g.
Usar 1: vida 80, quantidade 2, peso 200 g.
Cadastrar espada 2, peso 2000, bônus 15 e usar 2: ataque 25.
Descartar 2: rejeitado porque está equipado.
