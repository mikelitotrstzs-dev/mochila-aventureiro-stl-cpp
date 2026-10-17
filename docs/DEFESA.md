# Guia de estudo para a conversa de avaliação

Leia o código e execute os exemplos antes de responder com suas palavras.
Não apresente este guia como um relato de decisões que você tomou sozinho.

## Roteiro de cinco minutos
1. Explique o problema: mochila com capacidade, poções consumíveis e um equipamento.
2. Mostre DESCRICAO.md, depois PLANO.md e `git log --oneline --reverse`.
3. Execute cenário 1 e confira vida 80, ataque 25 e peso 2200 g.
4. Abra Inventario::usar e explique a chamada virtual e a remoção da poção.
5. Abra Inventario::listar e ResumoItem::operator< para justificar o sort.

## Inventario::usar, passo a passo
- buscarMutavel procura nos mapas e devolve um ponteiro emprestado.
- Se veio nullptr, retorna erro sem alterar nada.
- item->usar(personagem_) executa Pocao::usar ou Equipamento::usar.
- Se o tipo recusa o uso, nada é consumido e não se registra evento.
- Uma poção usada perde uma unidade; quando zera, sua entrada é apagada.
- Depois de erase, não se usa o ponteiro antigo.
- registrar acrescenta o evento ao histórico e devolve Resultado<int>.

## Perguntas úteis
- Por que map e não vector? Identidade por código e consulta por chave.
- map ordena a listagem por nome? Não; suas chaves são códigos. Por isso a
  consulta monta um vector e chama sort, que conhece operator< de ResumoItem.
- Por que não sort na list? sort exige acesso aleatório; list tem seu próprio
  método sort, mas o histórico não deve ser reordenado.
- O que faz const? Impede alteração por aquele acesso e documenta consulta.
- O que acontece com texto em campo numérico? getline lê a linha inteira;
  istringstream exige inteiro sem sufixo. O campo é repetido.
- Por que template no header? O compilador precisa ver a definição quando
  cria a versão para um tipo, por exemplo Resultado<int>.
- Herança e polimorfismo são a mesma coisa? Herança compartilha o contrato;
  polimorfismo escolhe o comportamento do tipo real numa chamada virtual.
- Como funciona uma cópia do inventário? Mapas, lista e personagem são copiados
  por valor; alterar a cópia não altera a origem. O teste verifica isso.

## Pendências pessoais exigidas pelo enunciado
Produzir sua descrição sem IA e redigir Onde uso a STL com suas palavras.
Preencher a reflexão sobre IA só com fatos vivenciados. Não inventar conversas,
recusas ou um histórico anterior ao trabalho realizado nesta sessão.
