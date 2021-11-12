#include "forca.hpp"

using std::ifstream;
using std::pair;
using std::string;
using std::stringstream;

Forca::Forca(const string &nome_arquivo_palavras,
             const string &nome_arquivo_scores)
    : nome_arquivo_palavras_(nome_arquivo_palavras),
      nome_arquivo_scores_(nome_arquivo_scores),
      dificuldade_(kDificuldadePadrao),
      tentativas_restantes_(kTentativasRestantesPadrao) {}

pair<bool, string> Forca::EhValido() const {
    ifstream arquivo_palavras(nome_arquivo_palavras_);
    ifstream arquivo_scores(nome_arquivo_scores_);
    bool okay = false;

    if (arquivo_palavras.is_open() and arquivo_scores.is_open()) okay = true;

    arquivo_palavras.close();
    arquivo_scores.close();

    if (okay) return pair<bool, string>{true, ""};
    return pair<bool, string>{false, "Um dos arquivos não pode ser aberto."};
}

void Forca::CarregaArquivos() {
    ifstream arquivo_palavras(nome_arquivo_palavras_);
    ifstream arquivo_scores(nome_arquivo_scores_);

    if (not arquivo_palavras.is_open() and not arquivo_scores.is_open()) return;

    string linha;
    
    while (getline(arquivo_palavras, linha)) {
        stringstream ss;
        string palavra;
        int ocorrencias;

        ss << linha;
        ss >> palavra;
        ss >> ocorrencias;

        palavras_ocorrencias_.push_back(pair<string, int>{palavra, ocorrencias});
    }

    while (getline(arquivo_scores, linha)) {
        
    }

}

void Forca::set_dificuldade(const Dificuldade &dificuldade) {
    dificuldade_ = dificuldade;
}

string Forca::ProximaPalavra() {}

string Forca::get_palavra_atual() const { return palavra_atual_; }

bool Forca::Palpite(const string &palpite) {
    return (palavra_atual_.find(palpite) == string::npos ? false : true);
}

bool Forca::GameOver() const {
    return (tentativas_restantes_ == 0 ? true : false);
}

void Forca::set_tentativas_restantes(const int &tentativas) {
    tentativas_restantes_ = tentativas;
}

int Forca::get_tentativas_restantes() const { return tentativas_restantes_; }