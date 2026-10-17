#include "Item.hpp"
#include "Util.hpp"
#include <stdexcept>
Item::Item(int codigo, const std::string& nome, int peso)
    : codigo_(codigo), nome_(aparar(nome)), peso_(peso), quantidade_(1) {
    if (codigo <= 0 || nome_.empty() || nome_.size() > 60 || peso < 1 || peso > 20000)
        throw std::invalid_argument("Codigo, nome ou peso invalido.");
}
Item::~Item() {} // Virtual: mantém a base segura para uso polimórfico.
int Item::codigo() const { return codigo_; }
const std::string& Item::nome() const { return nome_; }
int Item::peso() const { return peso_; }
int Item::quantidade() const { return quantidade_; }
void Item::definirQuantidade(int quantidade) { quantidade_ = quantidade; }
bool Item::operator==(const Item& outro) const { return codigo_ == outro.codigo_; }
