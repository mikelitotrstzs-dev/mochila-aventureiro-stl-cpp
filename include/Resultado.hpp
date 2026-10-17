#ifndef RESULTADO_HPP
#define RESULTADO_HPP 
#include <string>
// Template definido no header: cada unidade precisa enxergar sua implementação.
template <typename T> class Resultado {
public:
    bool sucesso;
    std::string mensagem;
    T valor;
    Resultado(bool ok, const std::string& texto, const T& dado)
        : sucesso(ok), mensagem(texto), valor(dado) {}
};
#endif
