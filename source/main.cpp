
#include "forca.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::pair;
using std::string;
using std::system;

int main(int argc, char *argv[]) {
    Forca forca = Forca(argv[1], argv[2]);

    pair<bool, string> teste = forca.EhValido();
    if (not teste.first) {
        // system("clear");
        cout << "\e[1mERRO:\e[0m " << teste.second << endl;
        return EXIT_FAILURE;
    }

    ifstream arquivo_palavras(argv[1]);
    ifstream arquivo_scores(argv[2]);
    forca.CarregaArquivos();

    while (true) {
        system("clear");

        cout << "\e[1m"
             << "###### ###### ###### ###### ######\n"
                "##     ##  ## ##  ## ##     ##  ##\n"
                "####   ##  ## ####   ##     ######\n"
                "##     ##  ## ## ##  ##     ##  ##\n"
                "##     ###### ##  ## ###### ##  ##\n"
             << "\e[0m" << endl
             << "Por favor, selecione uma opção:" << endl
             << "   (1) Iniciar novo jogo" << endl
             << "   (2) Ver scores anteriores" << endl
             << endl
             << "   Digite qualquer tecla para sair" << endl
             << endl;

        int aux;
        cin >> aux;
        const Forca::Opcao opcao = static_cast<Forca::Opcao>(aux - 1);

        if (opcao == Forca::Opcao::kNovoJogo) {
            int aux = -1;
            while (aux != 1 and aux != 2 and aux != 3) {
                cout << "Por favor, escolha um nível:" << endl
                     << "   1) Fácil" << endl
                     << "   2) Médio" << endl
                     << "   3) Difícil" << endl
                     << endl;
                cin >> aux;
            }

            forca.set_dificuldade(static_cast<Forca::Dificuldade>(aux - 1));
            forca.SortearPalavras();

            while (not forca.get_palavras_sorteadas().empty() and
                   not forca.GameOver()) {
                cout << "Você consegue adivinhar essa palavra?" << endl;
                string palavra_camuflada = forca.ProximaPalavra();
                
                while (not forca.GameOver()) {
                    string aux;
                    cin >> aux;
                    forca.Palpite(aux);
                }
            }
        } else if (opcao == Forca::Opcao::kVerScores) {
            system("clear");

            cout << "\e[1mARQUIVO DE SCORES\e[0m" << endl
                 << endl
                 << arquivo_scores.rdbuf() << endl
                 << endl
                 << "Por favor, selecione uma opção:" << endl
                 << "   (3) Voltar" << endl
                 << endl;

            int aux = -1;
            while (static_cast<Forca::Opcao>(aux) != Forca::Opcao::kVoltar)
                cin >> aux;

            continue;
        } else {
            return EXIT_SUCCESS;
        }
    }
}