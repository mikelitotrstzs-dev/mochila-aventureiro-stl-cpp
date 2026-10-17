#include "Personagem.hpp"
#include "Util.hpp"
#include <stdexcept> 
const int Personagem::VIDA_MAXIMA;
Personagem::Personagem() : Personagem("Aventureiro") {}
Personagem::Personagem(const std::string& nome)
    : nome_(aparar(nome)), vida_(50), equipamento_(0), bonus_(0) {
    if (nome_.empty() || nome_.size() > 60)
        throw std::invalid_argument("Nome invalido.");
}
const std::string& Personagem::nome() const { return nome_; }
int Personagem::vida() const { return vida_; }
int Personagem::ataque() const { return 10 + bonus_; }
int Personagem::equipamento() const { return equipamento_; }
bool Personagem::curar(int pontos) {
    if (pontos < 1 || pontos > 100 || vida_ == VIDA_MAXIMA) return false;
    vida_ = limitar<int>(vida_ + pontos, 0, VIDA_MAXIMA);
    return true;
}
bool Personagem::equipar(int codigo, int bonus) {
    if (codigo <= 0 || bonus < 1 || bonus > 100 || codigo == equipamento_)
        return false;
    equipamento_ = codigo;
    bonus_ = bonus;
    return true;
}
