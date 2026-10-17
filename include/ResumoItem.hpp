#ifndef RESUMO_ITEM_HPP
#define RESUMO_ITEM_HPP
#include "Item.hpp"
// Projeção independente para ordenar sem copiar/fatiar uma classe abstrata.
class ResumoItem {
private:
    int codigo_;
    std::string nome_;
    std::string categoria_;
    int peso_;
    int quantidade_;
public:
    explicit ResumoItem(const Item& item);
    int codigo() const;
    const std::string& nome() const;
    const std::string& categoria() const;
    int peso() const;
    int quantidade() const;
    bool operator<(const ResumoItem& outro) const;
    bool operator==(const ResumoItem& outro) const;
};
#endif
