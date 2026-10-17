#include "ResumoItem.hpp" 
ResumoItem::ResumoItem(const Item& item)
    : codigo_(item.codigo()), nome_(item.nome()), categoria_(item.categoria()),
      peso_(item.peso()), quantidade_(item.quantidade()) {}
int ResumoItem::codigo() const { return codigo_; }
const std::string& ResumoItem::nome() const { return nome_; }
const std::string& ResumoItem::categoria() const { return categoria_; }
int ResumoItem::peso() const { return peso_; }
int ResumoItem::quantidade() const { return quantidade_; }
bool ResumoItem::operator<(const ResumoItem& outro) const {
    if (nome_ != outro.nome_) return nome_ < outro.nome_;
    return codigo_ < outro.codigo_;
}
bool ResumoItem::operator==(const ResumoItem& outro) const {
    return codigo_ == outro.codigo_;
}
