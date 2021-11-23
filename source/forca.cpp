#include "forca.hpp"

using std::count;
using std::default_random_engine;
using std::find;
using std::find_if;
using std::ifstream;
using std::isdigit;
using std::mt19937;
using std::pair;
using std::random_device;
using std::regex_replace;
using std::sample;
using std::shuffle;
using std::regex;
using std::sort;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;

Forca::Forca(const string &nome_arquivo_palavras,
             const string &nome_arquivo_scores)
    : nome_arquivo_palavras_(nome_arquivo_palavras),
      nome_arquivo_scores_(nome_arquivo_scores),
      dificuldade_(kDificuldadePadrao),
      tentativas_restantes_(kTentativasRestantesPadrao) {}

pair<bool, string> Forca::EhValido() const {
    ifstream arquivo_palavras(nome_arquivo_palavras_);
    ifstream arquivo_scores(nome_arquivo_scores_);

    if (not arquivo_palavras.is_open() and not arquivo_scores.is_open())
        return pair<bool, string>{false,
                                  "Um dos arquivos não pode ser aberto."};

    string linha;

    while (getline(arquivo_palavras, linha)) {
        stringstream ss;
        string palavra;
        string ocorrencias;

        ss << linha;
        ss >> palavra;
        ss >> ocorrencias;

        Erro erro = kSemErro;

        if (not all_of(palavra.begin(), palavra.end(), [](const char &c) {
                return ('A' <= c and c <= 'Z') or ('a' <= c and c <= 'z') or
                       (c == '-');
            }))
            erro = kCaracterInvalido;

        if (ocorrencias.empty() or
            any_of(ocorrencias.begin(), ocorrencias.end(),
                   [](const char &c) { return not isdigit(c); }) or
            ocorrencias[0] == '-')
            erro = kFrequenciaInvalida;

        if (palavra.length() < kTamanhoMinimoPalavra)
            erro = kTamanhoPalavraInvalido;

        if (erro != kSemErro)
            return pair<bool, string>{false, kMensagensErros[erro]};
    }

    while (getline(arquivo_scores, linha)) {
        Erro erro = kSemErro;

        if (count(linha.begin(), linha.end(), ';') > kNumMaxPontoVirgula)
            erro = kPontoVirgula;

        vector<string> campos(4);

        string campo;
        stringstream ss;
        ss << linha;

        for (int i = 0; getline(ss, campo, ';'); i++) {
            campo = regex_replace(campo, regex("^ +| +$|( ) +"), "$1");

            if (campo.empty()) {
                switch (static_cast<Forca::Erro>(i)) {
                    case kDificuldade:
                        erro = kSemDificuldade;
                    case kNome:
                        erro = kSemNome;
                    case kPontuacao:
                        erro = kSemPontuacao;
                }
            }
        }

        std::cout << erro << std::endl;

        if (erro != kSemErro)
            return pair<bool, string>{false, kMensagensErros[erro]};
    }

    arquivo_palavras.close();
    arquivo_scores.close();

    return pair<bool, string>{true, ""};
}

void Forca::CarregaArquivos() {
    ifstream arquivo_palavras(nome_arquivo_palavras_);

    string linha;
    double soma = 0;
    while (getline(arquivo_palavras, linha)) {
        stringstream ss;
        string palavra;
        int ocorrencias;

        ss << linha;
        ss >> palavra;
        ss >> ocorrencias;

        palavras_ocorrencias_.push_back(
            pair<string, int>{palavra, ocorrencias});

        soma += ocorrencias;
    }

    double freq_media = soma / palavras_ocorrencias_.size();

    for (const auto &po : palavras_ocorrencias_) {
        if (po.second <= freq_media)
            palavras_faceis_.push_back(po.first);
        else
            palavras_dificeis_.push_back(po.first);
    }
}

void Forca::set_dificuldade(const Dificuldade &dificuldade) {
    dificuldade_ = dificuldade;
}

string Forca::ProximaPalavra() {
    palavra_atual_ = palavras_sorteadas_.front();
    palavras_sorteadas_.erase(palavras_sorteadas_.begin());
    
    string consoantes = "bcdfghjklmnpqrstvxwyz";

    string palavra_camuflada = palavra_atual_;
    if (dificuldade_ == kFacil)
        palavra_camuflada = regex_replace(palavra_camuflada, regex("b|c|d|f|g|h|j|k|l|m|n|p|q|r|s|t|v|x|w|y|z"), "_");
    else if (dificuldade_ == kMedio)
    else if (dificuldade_ == kDificil)

    

    return palavra_atual_;
}

void Forca::SortearPalavras() {
    if (dificuldade_ == kFacil) {
        palavras_sorteadas_ = palavras_faceis_;
        shuffle(palavras_sorteadas_.begin(), palavras_sorteadas_.end(),
                default_random_engine{random_device()});
    } else if (dificuldade_ == kMedio) {
        vector<string> palavras_sorteadas;
        vector<string> palavras_faceis = palavras_faceis_;

        shuffle(palavras_dificeis_.begin(), palavras_dificeis_.end(),
                default_random_engine{random_device()});

        for_each(palavras_dificeis_.begin(), palavras_dificeis_.end(),
                 [&palavras_sorteadas, &palavras_faceis](const string &p) {
                     palavras_sorteadas.push_back(p);

                     for (int i = 0; i < 2; i++) {
                         string complemento;
                         sample(palavras_faceis.begin(), palavras_faceis.end(),
                                complemento, 1, mt19937{random_device{}()});
                         palavras_sorteadas.push_back(complemento);
                         palavras_faceis.erase(find(palavras_faceis.begin(),
                                                    palavras_faceis.end(),
                                                    complemento));
                     }
                 });

        palavras_sorteadas_ = palavras_sorteadas;
    } else if (dificuldade_ == kDificil) {
        palavras_sorteadas_ = palavras_dificeis_;
        shuffle(palavras_sorteadas_.begin(), palavras_sorteadas_.end(),
                default_random_engine{random_device()});
    }
}

string Forca::get_palavra_atual() const { return palavra_atual_; }

bool Forca::Palpite(const string &palpite) {
    if (palavra_atual_.find(palpite) == string::npos) {
        tentativas_restantes_--;
        return false;
    }

    return true;
}

bool Forca::GameOver() const {
    return (tentativas_restantes_ == 0 ? true : false);
}

void Forca::set_tentativas_restantes(const int &tentativas) {
    tentativas_restantes_ = tentativas;
}

int Forca::get_tentativas_restantes() const { return tentativas_restantes_; }

vector<string> Forca::get_palavras_sorteadas() const {
    return palavras_sorteadas_;
}