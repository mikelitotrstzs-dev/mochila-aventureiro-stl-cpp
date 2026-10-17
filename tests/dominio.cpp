#include "Pocao.hpp"
#include "Equipamento.hpp"
#include "Resultado.hpp"
#include "Util.hpp"
#include <cassert>
#include <stdexcept>
int main() {
    Personagem p;
    Pocao cura(1, " Cura ", 100, 30);
    Equipamento espada(2, "Espada", 2000, 15);
    const Item* item = &cura; // Emprestado: objeto vive até o fim deste escopo.
    assert(item->usar(p) && p.vida() == 80);
    assert(item->usar(p) && p.vida() == 100);
    assert(!item->usar(p));
    item = &espada;
    assert(item->usar(p) && p.ataque() == 25);
    assert(!item->usar(p));
    assert(cura.nome() == "Cura");
    assert(cura == Pocao(1, "Outra", 1, 1));
    assert(limitar<double>(1.5, 0.0, 1.0) == 1.0);
    Resultado<int> resultado(true, "ok", 42);
    assert(resultado.valor == 42);
    bool falhou = false;
    try { Pocao invalida(0, "", 0, 0); }
    catch (const std::invalid_argument&) { falhou = true; }
    assert(falhou);
}
