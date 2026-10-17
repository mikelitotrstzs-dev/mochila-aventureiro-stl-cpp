#include "Interface.hpp"
#include <cassert> 
#include <sstream>
#include <string>
std::string executar(const std::string& roteiro) {
    std::istringstream entrada(roteiro);
    std::ostringstream saida;
    Interface interface(entrada, saida);
    interface.executar();
    return saida.str();
}
int main() {
    const std::string erros = executar("abc\n1abc\n2147483648\n-1\n6\n9\n7\n99\n0\n");
    assert(erros.find("Entrada invalida.") != std::string::npos);
    assert(erros.find("Inventario vazio.") != std::string::npos);
    assert(erros.find("Historico vazio.") != std::string::npos);
    assert(erros.find("Codigo inexistente.") != std::string::npos);
    assert(executar("").find("Encerrado.") != std::string::npos);
    const std::string parcial = executar("1\n1\nPocao\n");
    assert(parcial.find("Cadastro codigo=") == std::string::npos);
    assert(parcial.find("Encerrado.") != std::string::npos);
    const std::string feliz = executar("1\n1\n   \nPocao pequena\n100\n30\n3\n1\n2\n4\n1\n8\n6\n0\n");
    assert(feliz.find("Nome invalido.") != std::string::npos);
    assert(feliz.find("Vida: 80/100 | Ataque: 10 | Peso: 200/20000 g") != std::string::npos);
    assert(feliz.find("1 | Pocao pequena | Pocao | 100 g | qtd=2") != std::string::npos);
}
