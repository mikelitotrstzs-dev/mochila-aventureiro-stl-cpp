#ifndef UTIL_HPP
#define UTIL_HPP
#include <string>
template <typename T> T limitar(T valor, T minimo, T maximo) {
    if (valor < minimo) return minimo;
    if (valor > maximo) return maximo;
    return valor;
}
inline std::string aparar(const std::string& texto) {
    const std::string espacos = " \t\r\n";
    const std::size_t inicio = texto.find_first_not_of(espacos);
    if (inicio == std::string::npos) return "";
    return texto.substr(inicio, texto.find_last_not_of(espacos) - inicio + 1);
}
#endif
