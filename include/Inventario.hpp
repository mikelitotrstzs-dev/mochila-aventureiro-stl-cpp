#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP 
#include <map>
#include <set>
#include <list>
#include <vector>
#include "Pocao.hpp"
#include "Equipamento.hpp"
#include "ResumoItem.hpp"
#include "Resultado.hpp"
class Inventario {
private:
    std::map<int, Pocao> pocoes_;
    std::map<int, Equipamento> equipamentos_;
    std::list<std::string> historico_;
    Personagem personagem_;
    Item* buscarMutavel(int codigo);
    bool cabe(int peso, int quantidade) const;
    Resultado<int> registrar(const std::string& acao, int codigo, int quantidade);
public:
    static const int CAPACIDADE = 20000;
    static const int MAX_QUANTIDADE = 1000;
    Inventario();
    explicit Inventario(const Personagem& personagem);
    // Sobrecargas preservam o tipo concreto no respectivo map.
    Resultado<int> cadastrar(const Pocao& item);
    Resultado<int> cadastrar(const Equipamento& item);
    Resultado<int> coletar(int codigo, int quantidade);
    Resultado<int> usar(int codigo);
    Resultado<int> descartar(int codigo, int quantidade);
    // Retorno não proprietário: não liberar; inválido ao remover o item/dono.
    const Item* buscar(int codigo) const;
    std::vector<ResumoItem> listar() const;
    std::set<std::string> categorias() const;
    const std::list<std::string>& historico() const;
    const Personagem& personagem() const;
    int pesoTotal() const;
};
#endif
