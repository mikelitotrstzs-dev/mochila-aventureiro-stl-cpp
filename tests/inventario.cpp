#include "Inventario.hpp"
#include <cassert>
#include <climits>
#include <algorithm>
int main() {
    Inventario mochila;
    assert(mochila.listar().empty() && mochila.categorias().empty());
    assert(mochila.buscar(999) == nullptr);
    assert(!mochila.usar(999).sucesso);
    assert(!mochila.coletar(999, 1).sucesso);
    assert(!mochila.descartar(999, 1).sucesso);
    assert(mochila.historico().empty());
    assert(mochila.cadastrar(Pocao(1, "Z Cura", 100, 30)).sucesso);
    assert(mochila.cadastrar(Equipamento(2, "A Espada", 2000, 15)).sucesso);
    assert(!mochila.cadastrar(Equipamento(1, "Duplicado", 1, 1)).sucesso);
    assert(mochila.coletar(1, 2).sucesso);
    assert(mochila.pesoTotal() == 2300);
    assert(!mochila.coletar(1, INT_MAX).sucesso);
    assert(!mochila.coletar(1, -1).sucesso);
    assert(!mochila.coletar(1, 0).sucesso);
    assert(!mochila.coletar(2, 10).sucesso);
    assert(mochila.usar(1).sucesso && mochila.personagem().vida() == 80);
    assert(mochila.usar(1).sucesso && mochila.personagem().vida() == 100);
    const std::size_t eventos = mochila.historico().size();
    assert(!mochila.usar(1).sucesso && mochila.buscar(1)->quantidade() == 1);
    assert(mochila.historico().size() == eventos);
    assert(mochila.usar(2).sucesso && mochila.personagem().ataque() == 25);
    assert(!mochila.usar(2).sucesso);
    assert(!mochila.descartar(2, 1).sucesso);
    assert(!mochila.descartar(1, 2).sucesso);
    assert(mochila.listar().front().codigo() == 2);
    assert(mochila.categorias().size() == 2);
    std::vector<ResumoItem> itens = mochila.listar();
    assert(std::find(itens.begin(), itens.end(), ResumoItem(*mochila.buscar(1))) != itens.end());
    Inventario copia = mochila; // Containers por valor: cópias independentes.
    assert(copia.descartar(1, 1).sucesso && copia.buscar(1) == nullptr);
    assert(mochila.buscar(1) != nullptr);
    assert(mochila.cadastrar(Equipamento(3, "A Espada", 1000, 5)).sucesso);
    assert(mochila.listar()[1].codigo() == 3); // Desempate por código.
    assert(mochila.usar(3).sucesso && mochila.personagem().ataque() == 15);
    assert(mochila.descartar(2, 1).sucesso);
    assert(mochila.descartar(1, 1).sucesso);
    assert(mochila.categorias().size() == 1);
    assert(mochila.cadastrar(Pocao(1, "Reutilizado", 1, 100)).sucesso);
    Inventario limite;
    assert(limite.cadastrar(Pocao(1, "Pesada", 20000, 100)).sucesso);
    assert(limite.pesoTotal() == Inventario::CAPACIDADE);
    assert(!limite.cadastrar(Pocao(2, "Leve", 1, 1)).sucesso);
    assert(limite.usar(1).sucesso && limite.buscar(1) == nullptr);
    assert(limite.pesoTotal() == 0 && limite.categorias().empty());
    assert(limite.cadastrar(Pocao(1, "Leve", 1, 1)).sucesso);
    assert(limite.coletar(1, 999).sucesso);
    assert(!limite.coletar(1, 1).sucesso);
    assert(limite.buscar(1)->quantidade() == 1000);
}
