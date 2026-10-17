#include "Equipamento.hpp" 
#include <stdexcept>
Equipamento::Equipamento(int codigo, const std::string& nome, int peso, int bonus)
    : Item(codigo, nome, peso), bonus_(bonus) {
    if (bonus < 1 || bonus > 100) throw std::invalid_argument("Bonus invalido.");
}
std::string Equipamento::categoria() const { return "Equipamento"; }
bool Equipamento::usar(Personagem& personagem) const {
    return personagem.equipar(codigo(), bonus_);
}
bool Equipamento::consumivel() const { return false; }
