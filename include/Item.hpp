#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
#include "Personagem.hpp"
class Inventario;
class Item {
private:
    int codigo_;
    std::string nome_;
    int peso_;
    int quantidade_;
    // Somente o inventário altera estoque depois de verificar seus limites.
    friend class Inventario;
    void definirQuantidade(int quantidade);
protected:
    Item(int codigo, const std::string& nome, int peso);
public:
    virtual ~Item();
    int codigo() const;
    const std::string& nome() const;
    int peso() const;
    int quantidade() const;
    virtual std::string categoria() const = 0;
    virtual bool usar(Personagem& personagem) const = 0;
    virtual bool consumivel() const = 0;
    bool operator==(const Item& outro) const;
};
#endif
