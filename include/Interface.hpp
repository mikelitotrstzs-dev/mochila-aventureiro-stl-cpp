#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <istream>
#include <ostream>
#include "Inventario.hpp"
// Apresentação fora do domínio: até operator<< pertence à interface.
std::ostream& operator<<(std::ostream& saida, const ResumoItem& item);
class Interface {
private:
    Inventario inventario_;
    std::istream& entrada_;
    std::ostream& saida_;
    bool lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor);
    bool lerNome(std::string& nome);
    bool cadastrar(bool pocao);
    bool operar(int opcao);
    void listar() const;
    void resumo() const;
public:
    Interface(std::istream& entrada, std::ostream& saida);
    void executar();
};
#endif
