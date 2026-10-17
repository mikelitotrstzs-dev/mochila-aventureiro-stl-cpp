# Cenários e resultados esperados

Cada .txt contém exatamente as respostas ao menu, uma por linha. Os arquivos
.esperado são trechos obrigatórios da saída; os testes C++ verificam estado,
ordenação e ausência de mutação em falhas com mais precisão. 

- cenario1: cadastra poção, coleta duas, usa uma; cadastra/equipa espada.
  Vida 80, ataque 25, peso 2200 g; tentativa de descartar espada é recusada.
- erros: texto, opção fora da faixa, coleções vazias, código ausente,
  duplicação e excesso de peso. Poção de 20000 g é consumida; inventário zera.
- eof_parcial: cadastro interrompido antes do peso; não há cadastro parcial.

`make test` executa os três, além das três suites de testes C++.
