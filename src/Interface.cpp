#include "Interface.hpp"
#include "Util.hpp"
#include <sstream>
#include <limits>
#include <stdexcept> 
std::ostream& operator<<(std::ostream& saida, const ResumoItem& item) {
    return saida << item.codigo() << " | " << item.nome() << " | " << item.categoria()
                 << " | " << item.peso() << " g | qtd=" << item.quantidade();
}
Interface::Interface(std::istream& entrada, std::ostream& saida)
    : inventario_(), entrada_(entrada), saida_(saida) {}
bool Interface::lerInteiro(const std::string& rotulo, int minimo, int maximo, int& valor) {
    std::string linha;
    while (true) {
        saida_ << rotulo << ": ";
        if (!std::getline(entrada_, linha)) return false;
        std::istringstream leitor(linha);
        int candidato;
        char sobra;
        // A leitura de 'sobra' ignora espaços mas detecta 12abc ou 1 2.
        if ((leitor >> candidato) && !(leitor >> sobra) &&
            candidato >= minimo && candidato <= maximo) {
            valor = candidato;
            return true;
        }
        saida_ << "Entrada invalida. Use inteiro entre " << minimo << " e " << maximo << ".\n";
    }
}
bool Interface::lerNome(std::string& nome) {
    std::string linha;
    while (true) {
        saida_ << "Nome: ";
        if (!std::getline(entrada_, linha)) return false;
        nome = aparar(linha);
        if (!nome.empty() && nome.size() <= 60) return true;
        saida_ << "Nome invalido. Use de 1 a 60 caracteres.\n";
    }
}
bool Interface::cadastrar(bool pocao) {
    int codigo, peso, efeito;
    std::string nome;
    if (!lerInteiro("Codigo", 1, std::numeric_limits<int>::max(), codigo) ||
        !lerNome(nome) || !lerInteiro("Peso unitario em gramas", 1, 20000, peso) ||
        !lerInteiro(pocao ? "Cura" : "Bonus", 1, 100, efeito)) return false;
    // Todos os campos são lidos antes de criar/modificar o domínio.
    try {
        const Resultado<int> resultado = pocao
            ? inventario_.cadastrar(Pocao(codigo, nome, peso, efeito))
            : inventario_.cadastrar(Equipamento(codigo, nome, peso, efeito));
        saida_ << (resultado.sucesso ? "OK: " : "Erro: ") << resultado.mensagem << "\n";
    } catch (const std::invalid_argument& erro) {
        saida_ << "Erro: " << erro.what() << "\n";
    }
    return true;
}
bool Interface::operar(int opcao) {
    int codigo, quantidade = 1;
    if (!lerInteiro("Codigo", 1, std::numeric_limits<int>::max(), codigo)) return false;
    if (opcao == 7) {
        const Item* item = inventario_.buscar(codigo);
        if (item) saida_ << ResumoItem(*item) << "\n";
        else saida_ << "Codigo inexistente.\n";
        return true;
    }
    if ((opcao == 3 || opcao == 5) &&
        !lerInteiro("Quantidade", 1, 1000, quantidade)) return false;
    Resultado<int> resultado(false, "Opcao invalida.", 0);
    if (opcao == 3) resultado = inventario_.coletar(codigo, quantidade);
    if (opcao == 4) resultado = inventario_.usar(codigo);
    if (opcao == 5) resultado = inventario_.descartar(codigo, quantidade);
    saida_ << (resultado.sucesso ? "OK: " : "Erro: ") << resultado.mensagem << "\n";
    return true;
}
void Interface::listar() const {
    const std::vector<ResumoItem> itens = inventario_.listar();
    if (itens.empty()) saida_ << "Inventario vazio.\n";
    for (const ResumoItem& item : itens) saida_ << item << "\n";
}
void Interface::resumo() const {
    const Personagem& p = inventario_.personagem();
    saida_ << p.nome() << " | Vida: " << p.vida() << "/100 | Ataque: " << p.ataque()
           << " | Peso: " << inventario_.pesoTotal() << "/20000 g\n";
    const std::set<std::string> categorias = inventario_.categorias();
    if (categorias.empty()) saida_ << "Sem categorias.\n";
    for (const std::string& categoria : categorias) saida_ << "Categoria: " << categoria << "\n";
}
void Interface::executar() {
    saida_ << "Mochila do Aventureiro\n";
    int opcao;
    bool continuar = true;
    while (continuar) {
        saida_ << "\n1 Pocao | 2 Equipamento | 3 Coletar | 4 Usar | 5 Descartar\n"
               << "6 Listar | 7 Buscar | 8 Resumo | 9 Historico | 0 Sair\n";
        if (!lerInteiro("Opcao", 0, 9, opcao) || opcao == 0) break;
        if (opcao == 1 || opcao == 2) continuar = cadastrar(opcao == 1);
        else if (opcao == 3 || opcao == 4 || opcao == 5 || opcao == 7)
            continuar = operar(opcao);
        else if (opcao == 6) listar();
        else if (opcao == 8) resumo();
        else if (opcao == 9) {
            if (inventario_.historico().empty()) saida_ << "Historico vazio.\n";
            for (const std::string& evento : inventario_.historico()) saida_ << evento << "\n";
        }
    }
    saida_ << "Encerrado.\n";
}
