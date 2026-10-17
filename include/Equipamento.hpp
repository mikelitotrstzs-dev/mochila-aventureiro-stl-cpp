#ifndef EQUIPAMENTO_HPP
#define EQUIPAMENTO_HPP
#include "Item.hpp"
class Equipamento : public Item {
private:
    int bonus_;
public:
    Equipamento(int codigo, const std::string& nome, int peso, int bonus);
    std::string categoria() const override;
    bool usar(Personagem& personagem) const override;
    bool consumivel() const override;
};
#endif
