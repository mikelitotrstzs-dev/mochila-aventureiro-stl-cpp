#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP 
#include <string>
class Personagem {
private:
    std::string nome_;
    int vida_;
    int equipamento_;
    int bonus_;
public:
    static const int VIDA_MAXIMA = 100;
    Personagem();
    explicit Personagem(const std::string& nome);
    const std::string& nome() const;
    int vida() const;
    int ataque() const;
    int equipamento() const;
    bool curar(int pontos);
    bool equipar(int codigo, int bonus);
};
#endif
