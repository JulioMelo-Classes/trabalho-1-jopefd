#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Forca {
   public:
    enum Dificuldade { kFacil, kMedio, kDificil };
    const Dificuldade kDificuldadePadrao = Dificuldade::kFacil;
    const int kTentativasRestantesPadrao = 6;

   private:
    // TODO: armazenar os scores?

    std::vector<std::pair<std::string, int>> palavras_ocorrencias_;
    std::vector<std::string> scores_;
    std::string nome_arquivo_scores_;
    std::string nome_arquivo_palavras_;
    Dificuldade dificuldade_;
    std::string palavra_atual_;
    int tentativas_restantes_;

   public:
    /**
     * Construtor padrão
     */
    Forca();

    /**
     * Cria a classe Forca
     *
     * O construtor pode ou não validar os arquivos de entrada, no entanto,
     * mesmo com os arquivos inválidos o objeto deve ser construído. Para o caso
     * de arquivos de palavras ou scores inválidos, use o método EhValido.
     *
     * \param palavras o arquivo que contém as palavras
     * \param scores o nome do arquivo que contém os scores
     *
     * \see EhValido
     */
    Forca(const std::string &nome_arquivo_palavras,
          const std::string &nome_arquivo_scores);

    /**
     * Valida os arquivos de entrada de acordo com as especificações.
     * Ao validar os arquivos, no caso de arquivos inválidos, este método deve
     * retornar a razão correspondente de acordo com as especificações.
     *
     * \return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso
     * contrário.
     */
    std::pair<bool, std::string> EhValido() const;

    /**
     * Carrega os arquivos de scores e palavras preenchendo **ao menos** a
     * estrutura palavras_
     */
    void CarregaArquivos();

    /**
     * Modifica a dificuldade do jogo.
     * De acordo com a dificuldade configurada, o método proxima_palavra
     * retornará palavras diferentes.
     *
     * \param d a dificuldade desejada
     * \see proxima_palavra
     */
    void set_dificuldade(const Dificuldade &d);

    /**
     * Retorna a próxima palavra de acordo com a dificuldade atual.
     * Este método deve atualizar o atributo palavra_atual_ e retornar a
     * palavra um texto no formato
     * "_ _ _ _ ... _" dependendo do tamanho de palavra_atual_. O método também
     * deve sortear as letras que devem aparecer dependendo do nível de
     * dificuldade.
     *
     * \return a próxima palavra do conjunto de palavras disponível de acordo
     * com a dificuldade atual.
     */
    std::string ProximaPalavra();

    /**
     * Retorna a palavra atual que está sendo jogada.
     *
     * \return o valor do atributo palavra_atual_.
     */
    std::string get_palavra_atual() const;

    /**
     * Testa se uma letra pertence á palavra atual, retorna T se a letra
     * pertence. Este método testa se uma letra pertence à palavra atual e
     * retorna True caso pertença. Caso contrário, o método deve atualizar o
     * atributo tentativas_restantes_, decrementando em 1, e retornar False.
     *
     * \param palpite uma letra, que deve ser testada se pertence à palavra.
     * \return T se a palpite pertence à palavra, F caso contrário.
     */
    bool Palpite(const std::string &palpite);

    /**
     * Em caso de Game Over este método deve retornar T.
     * \return T caso o tentativas_restantes_ do jogo esteja igual a 0, F caso
     * contrário.
     */
    bool GameOver() const;

    /**
     * Atualiza o número de tentativas restantes.
     * Este método é útil no caso do jogador escolher continuar o jogo.
     *
     * \param tentativas atualiza o valor da variável tentativas_restantes_.
     */
    void set_tentativas_restantes(const int &tentativas);

    /**
     * Retorna a quantidade de tentativas restantes.
     *
     * \return a quantidade de tentativas restantes.
     */
    int get_tentativas_restantes() const;
};
