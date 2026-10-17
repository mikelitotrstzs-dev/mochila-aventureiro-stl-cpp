#include "Inventario.hpp"
#include <algorithm>
#include <stdexcept> 
const int Inventario::CAPACIDADE;
const int Inventario::MAX_QUANTIDADE;
Inventario::Inventario() : personagem_() {}
Inventario::Inventario(const Personagem& personagem) : personagem_(personagem) {
    if (personagem.equipamento() != 0)
        throw std::invalid_argument("Personagem inicial deve estar sem equipamento.");
}
const Item* Inventario::buscar(int codigo) const {
    std::map<int, Pocao>::const_iterator p = pocoes_.find(codigo);
    if (p != pocoes_.end()) return &p->second;
    std::map<int, Equipamento>::const_iterator e = equipamentos_.find(codigo);
    if (e != equipamentos_.end()) return &e->second;
    return nullptr;
}
Item* Inventario::buscarMutavel(int codigo) {
    std::map<int, Pocao>::iterator p = pocoes_.find(codigo);
    if (p != pocoes_.end()) return &p->second;
    std::map<int, Equipamento>::iterator e = equipamentos_.find(codigo);
    if (e != equipamentos_.end()) return &e->second;
    return nullptr;
}
int Inventario::pesoTotal() const {
    int peso = 0;
    for (const auto& par : pocoes_) peso += par.second.peso() * par.second.quantidade();
    for (const auto& par : equipamentos_) peso += par.second.peso() * par.second.quantidade();
    return peso;
}
bool Inventario::cabe(int peso, int quantidade) const {
    // Dividir antes de multiplicar evita overflow e mantém limite exato.
    return quantidade > 0 && quantidade <= MAX_QUANTIDADE &&
           peso > 0 && quantidade <= (CAPACIDADE - pesoTotal()) / peso;
}
Resultado<int> Inventario::registrar(const std::string& acao, int codigo, int quantidade) {
    const std::string texto = acao + " codigo=" + std::to_string(codigo) +
                              " quantidade=" + std::to_string(quantidade);
    historico_.push_back(texto);
    return Resultado<int>(true, texto, quantidade);
}
Resultado<int> Inventario::cadastrar(const Pocao& item) {
    if (buscar(item.codigo())) return Resultado<int>(false, "Codigo duplicado.", 0);
    // Um objeto copiado de outro inventário pode carregar quantidade maior que 1.
    if (!cabe(item.peso(), 1)) return Resultado<int>(false, "Capacidade excedida.", 0);
    Pocao copia = item;
    copia.definirQuantidade(1);
    pocoes_.insert(std::make_pair(item.codigo(), copia));
    return registrar("Cadastro", item.codigo(), 1);
}
Resultado<int> Inventario::cadastrar(const Equipamento& item) {
    if (buscar(item.codigo())) return Resultado<int>(false, "Codigo duplicado.", 0);
    if (!cabe(item.peso(), 1)) return Resultado<int>(false, "Capacidade excedida.", 0);
    Equipamento copia = item;
    copia.definirQuantidade(1);
    equipamentos_.insert(std::make_pair(item.codigo(), copia));
    return registrar("Cadastro", item.codigo(), 1);
}
Resultado<int> Inventario::coletar(int codigo, int quantidade) {
    Item* item = buscarMutavel(codigo);
    if (!item) return Resultado<int>(false, "Codigo inexistente.", 0);
    if (quantidade < 1 || quantidade > MAX_QUANTIDADE - item->quantidade())
        return Resultado<int>(false, "Quantidade invalida ou limite de 1000 excedido.", 0);
    if (!cabe(item->peso(), quantidade))
        return Resultado<int>(false, "Capacidade excedida.", 0);
    item->definirQuantidade(item->quantidade() + quantidade);
    return registrar("Coleta", codigo, quantidade);
}
Resultado<int> Inventario::usar(int codigo) {
    Item* item = buscarMutavel(codigo);
    if (!item) return Resultado<int>(false, "Codigo inexistente.", 0);
    // Despacho virtual: a regra depende do tipo real, não do ponteiro Item*.
    if (!item->usar(personagem_))
        return Resultado<int>(false, "Sem efeito: vida cheia ou equipamento ja ativo.", 0);
    if (item->consumivel()) {
        const int restante = item->quantidade() - 1;
        if (restante == 0) pocoes_.erase(codigo);
        else item->definirQuantidade(restante);
        // Após erase, o ponteiro emprestado não deve mais ser utilizado.
    }
    return registrar("Uso", codigo, 1);
}
Resultado<int> Inventario::descartar(int codigo, int quantidade) {
    Item* item = buscarMutavel(codigo);
    if (!item) return Resultado<int>(false, "Codigo inexistente.", 0);
    if (quantidade < 1 || quantidade > item->quantidade())
        return Resultado<int>(false, "Quantidade invalida ou insuficiente.", 0);
    if (personagem_.equipamento() == codigo)
        return Resultado<int>(false, "Equipamento ativo: troque antes de descartar.", 0);
    const int restante = item->quantidade() - quantidade;
    if (restante > 0) item->definirQuantidade(restante);
    else {
        pocoes_.erase(codigo);
        equipamentos_.erase(codigo);
    }
    return registrar("Descarte", codigo, quantidade);
}
std::vector<ResumoItem> Inventario::listar() const {
    std::vector<ResumoItem> itens;
    for (const auto& par : pocoes_) itens.push_back(ResumoItem(par.second));
    for (const auto& par : equipamentos_) itens.push_back(ResumoItem(par.second));
    std::sort(itens.begin(), itens.end()); // Usa ResumoItem::operator<.
    return itens;
}
std::set<std::string> Inventario::categorias() const {
    std::set<std::string> resultado;
    for (const auto& par : pocoes_) resultado.insert(par.second.categoria());
    for (const auto& par : equipamentos_) resultado.insert(par.second.categoria());
    return resultado;
}
const std::list<std::string>& Inventario::historico() const { return historico_; }
const Personagem& Inventario::personagem() const { return personagem_; }
