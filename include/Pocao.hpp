#ifndef POCAO_HPP
#define POCAO_HPP
#include "Item.hpp" 
class Pocao : public Item {
private:
    int cura_;
public:
    Pocao(int codigo, const std::string& nome, int peso, int cura);
    std::string categoria() const override;
    bool usar(Personagem& personagem) const override;
    bool consumivel() const override;
};
#endif
