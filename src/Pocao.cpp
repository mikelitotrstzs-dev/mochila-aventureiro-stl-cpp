#include "Pocao.hpp" 
#include <stdexcept>
Pocao::Pocao(int codigo, const std::string& nome, int peso, int cura)
    : Item(codigo, nome, peso), cura_(cura) {
    if (cura < 1 || cura > 100) throw std::invalid_argument("Cura invalida.");
}
std::string Pocao::categoria() const { return "Pocao"; }
bool Pocao::usar(Personagem& personagem) const { return personagem.curar(cura_); }
bool Pocao::consumivel() const { return true; }
