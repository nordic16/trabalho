/*************************
 * Constantes simb�licas *
 *************************/

#define NR_PONTOS_PASSAGEM 24
#define NR_ATLETAS 2687
#define TAMANHO_MAX_NOME_ATLETA 40
#define TAMANHO_MAX_NOME_EQUIPA 110
#define MAX_COLS_FICH_STARTERS 140
#define MAX_COLS_FICH_FINAL 170
#define MAX_COLS_FICH_PROGRESS 320

/*********
 * Tipos *
 *********/

/**
 * Data-hora-minuto absoluto e tempo decorrido em prova
 *
 * diaDaSemana � um de entre {"Fri.", "Sat.", "Sun."};
 * 0 <= horaDoDia <= 23 (hora que um rel�gio normal mostra);
 * 0 <= minutoAposHoraDoDia <= 59 (minuto que um rel�gio normal mostra);
 * horasRelativas e minutosRelativos s�o contados a partir de Fri. 18:00;
 � 0 <= horasAposInicio <= 53 (ou 46, respeitando o tempo limite de 46:30);
 * 0 <= minutosAposHorasAposInicio <= 59
 */
typedef struct {
  char diaDaSemana[5];
  int horaDoDia;
  int minutoAposHoraDoDia;
  int horasAposInicio;
  int minutosAposHorasAposInicio;
} Tempo;

/**
 * Detalhes de um atleta
 *
 * dorsal > 0;
 * nacionalidade � uma string contendo 3 letras mai�sculas, 1 espa�o,
 *   e 2 letras mai�sculas dentro de par�nteses;
 * escalao se masculino: "20-34M", "35-39M", "40-44M", e assim sucessivamente;
 * escalao se feminino: "20-34W", "35-39W", "40-44W", e assim sucessivamente;
 * posicaoFinalEscalao e tempoNaMeta ficam com valores indeterminados caso
 *   o atleta n�o tenha chegado � meta;
 * posicaoFinalAbsoluta fica com o valor 9999 caso o atleta n�o tenha chegado � meta;
 * tempo na meta: {horas desde a partida, minutos, segundos};
 * tempos de passagem medidos em minutos totais ap�s a partida;
 * se o atleta n�o passou num ponto de passagem, tempo de passagem = 10000 a�;
 *   portanto, tempo de passagem = 10000 na meta caso o atleta n�o tenha l� chegado
 */
typedef struct {
  int dorsal;
  char nome[TAMANHO_MAX_NOME_ATLETA + 1];
  char nacionalidade[9];
  char escalao[7];
  int posicaoFinalAbsoluta;
  int posicaoFinalEscalao;
  int tempoNaMeta[3];
  int temposPassagem[24];
} Atleta;

/**
 * Registo simples de passagem de um atleta por um posto de controlo
 *
 * dorsal > 0;
 * tempo de passagem medido em minutos totais ap�s a partida;
 * se o atleta n�o passou neste ponto de passagem, tempo de passagem = -1 aqui
 */
typedef struct {
  int dorsal;
  int tempoPassagem;
} RegistoPassagem;

/***********
 * Fun��es *
 ***********/

/*******************
 * Fun��o auxiliar *
 *******************/

/**
 * Obt�m as horas decorridas em prova a partir da data-hora absoluta
 *
 * Nesta fun��o ignora-se os minutos decorridos em prova.
 * Requires:
 *  diaDaSemana pode ser "Fri.", "Sat." ou "Sun.";
 *  0 <= horaDoDia <= 23
 */
int converteParaHorasAposInicio( const char *diaDaSemana, int horaDoDia );

/*********************************************************
 * Fun��es observadoras (getters) e fun��es de convers�o *
 *********************************************************/

int minutosEmProva( Tempo tempo );

int dorsal( Atleta atleta );
char *nome( Atleta *atletaPtr );
char *nacionalidade( Atleta *atletaPtr );
char *escalao( Atleta *atletaPtr );
int posicaoFinalAbsoluta( Atleta atleta );
int posicaoFinalEscalao( Atleta atleta );
int *tempoNaMeta( Atleta *atletaPtr );
int *temposPassagem( Atleta *atletaPtr );

/**
 * Obt�m o Tempo correspondente a um tempo de passagem em minutos
 *
 * Requires: 0 <= tempoPassagem < 3240 (54 horas)
 */
Tempo tempo( int tempoPassagem );

/******************************************************
 * Fun��es de obten��o de dados a partir de ficheiros *
 ******************************************************/

/**
 * Obt�m os dados de identifica��o dos atletas que iniciaram a prova
 *
 * Requires:
 *   tamanhoLista > 0;
 *   nomeFicheiro � o path de um ficheiro de texto alcan��vel;
 *   o ficheiro est� no formato exemplificado neste projecto
 *     (atletas ordenados por n�mero de dorsal);
 *   o ficheiro cont�m pelo menos 1 atleta
 * Ensures:
 *   inicializa, em cada atleta, os membros
 *     dorsal,
 *     nome,
 *     nacionalidade,
 *     escalao;
 *   inicializa tamb�m, PROVISORIAMENTE, o membro posicaoFinalAbsoluta
 *     com o valor arbitr�rio 9999.
 * Ficam por preencher, nos atletas, todos os dados de desempenho na prova.
 * Esse preenchimento � feito pela fun��o atribuiResultadosNaMeta.
 * Os atletas que n�o tenham chegado � meta ficar�o permanentemente com
 * o valor 9999 de posicaoFinalAbsoluta, e ficar�o com valores indeterminados em
 * posicaoFinalEscalao e tempoNaMeta.
 */
void inicializaAtletas( Atleta listaAtletas[], int tamanhoLista,
                        const char *nomeFicheiro );

/**
 * Preenche os resultados finais dos atletas que terminaram a prova
 *
 * Requires:
 *   tamanhoLista > 0;
 *   nomeFicheiro � o path de um ficheiro de texto alcan��vel;
 *   o ficheiro est� no formato exemplificado neste projecto
 *     (atletas ordenados por n�mero de dorsal);
 *   o ficheiro cont�m pelo menos 1 atleta;
 *   os atletas a preencher t�m de ter o membro dorsal instanciado.
 * Ensures: instancia, em cada atleta, os membros
 *   posicaoFinalAbsoluta,
 *   posicaoFinalEscalao,
 *   tempoNaMeta.
 * Ficam por preencher, nos atletas, os tempos de passagem nos postos de controlo.
 */
void atribuiResultadosNaMeta( Atleta listaAtletas[], int tamanhoLista,
                              const char *nomeFicheiro );

/**
 * Atribui os tempos de passagem a todos os atletas
 *
 * Requires:
 *   tamanhoLista > 0;
 *   nomeFicheiro � o path de um ficheiro de texto alcan��vel;
 *   o ficheiro est� no formato exemplificado neste projecto
 *     (atletas ordenados por n�mero de dorsal);
 *   o ficheiro cont�m pelo menos 1 atleta;
 *   os atletas a preencher t�m de ter o membro dorsal instanciado.
 * Ensures: instancia, em cada atleta, o membro
 *   temposPassagem.
 */
void atribuiTemposPassagem( Atleta listaAtletas[], int tamanhoLista,
                            const char *nomeFicheiro );

/**
 * Preenche uma tabela com registos de passagem dos atletas
 *
 * Cada linha da tabela corresponde a um ponto de passagem, a.k.a. posto
 * de controlo.
 * Assume-se que cada atleta tem temposPassagem[] correctamente preenchido.
 * Requires:
 *   tamanhoLista > 0
 * Ensures:
 *   coloca, em cada linha da tabela, os registos de passagem de todos os
 *     atletas pela mesma ordem em que os atetas est�o em listaAtletas;
 *   os tempos s�o medidos em minutos ap�s a partida.
 */
void preencheTabelaPassagens( Atleta listaAtletas[], int tamanhoLista,
                              RegistoPassagem tabela[][NR_ATLETAS],
                              int nPostos );

/************************
 * Fun��es de ordena��o *
 ************************/

/**
 * Ordena vec por ordem crescente de tempo, entre os �ndices inicio e fim inclusive
 *
 * A ordena��o � pelo membro tempoPassagem de cada vec[i].
 * Requires: 0 <= inicio < fim.
 */
void ordenaPorTempoPassagem( RegistoPassagem vec[], int inicio, int fim );

/**
 * Ordena uma tabela que cont�m registos de passagem dos atletas
 *
 * Cada linha da tabela corresponde a um ponto de passagem, a.k.a. posto
 * de controlo.
 * Assume-se que a tabela est� correctamente preenchida com os tempos de
 * passagem dos atletas em minutos ap�s a partida.
 * Requires:
 *   nAtletas > 0
 * Ensures:
 *   ordena cada linha da tabela por ordem crescente de tempoPassagem.
 */
void ordenaTabelaPassagens( int nAtletas, RegistoPassagem tabela[][NR_ATLETAS],
                            int nPostos );

/**
 * Ordena vec por ordem crescente de posi��o, entre os �ndices inicio e fim inclusive
 *
 * A ordena��o � pelo membro posicaoFinalAbsoluta de cada vec[i].
 * Requires: 0 <= inicio < fim.
 */
void ordenaPorPosicaoFinal( Atleta vec[], int inicio, int fim );

/***********************
 * Fun��es de pesquisa *
 ***********************/

/**
 * Pesquisa um atleta num vector de atletas, por dorsal
 *
 * N�o se pode assumir que o vector est� ordenado por dorsal.
 * Requires:
 *   atletas com o dorsal correctamente instanciado;
 *   tamanho > 0.
 * Ensures:
 �   o �ndice da primeira ocorr�ncia de dorsal, caso exista,
 *   -1, caso n�o ocorra.
 */
int indiceAtleta( Atleta vec[], int tamanho, int dorsal );

/**
 * Devolve um atleta num vector de atletas, por dorsal
 *
 * N�o se pode assumir que o vector est� ordenado por dorsal.
 * Requires:
 *   atletas com o dorsal correctamente instanciado;
 *   tamanho > 0;
 *   existe no vector um atleta com o dorsal indicado.
 * Ensures:
 �   devolve o primeiro atleta com o dorsal indicado.
 */
Atleta getAtleta( Atleta vec[], int tamanho, int dorsal );

/**
 * Pesquisa um RegistoPassagem num vector de RegistoPassagem, por dorsal
 *
 * N�o se pode assumir que o vector est� ordenado por dorsal.
 * Requires:
 *   tamanho > 0.
 * Ensures:
 �   o �ndice da primeira ocorr�ncia de dorsal, caso exista,
 *   -1, caso n�o ocorra.
 */
int indiceRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal );

/**
 * Devolve um RegistoPassagem num vector de RegistoPassagem, por dorsal
 *
 * N�o se pode assumir que o vector est� ordenado por dorsal.
 * Requires:
 *   tamanho > 0;
 *   existe no vector um RegistoPassagem com o dorsal indicado.
 * Ensures:
 �   devolve o primeiro RegistoPassagem com o dorsal indicado.
 */
RegistoPassagem getRegistoPassagem( RegistoPassagem vec[], int tamanho, int dorsal );

/*********************************************
 * Avalia��o de desempenho ao longo da prova *
 *********************************************/

 /**
 * Regista a posi��o de um atleta em cada um dos postos de controlo.
 *
 * Requires:
 *   nAtletas > 0, nPostos > 0;
 *   dorsal ocorre na tabela;
 *   a tabela est� ordenada em cada posto de controlo, por tempo de passagem.
 * Ensures:
 �   preenche o vector posicoes com as posic�es do atleta em cada um dos postos
 *   de controlo.
 */
void registaPosicoesPostos( int nAtletas, RegistoPassagem tabela[][NR_ATLETAS],
                            int nPostos, int dorsal, int posicoes[] );

/**************************************
 * Processamento de resultados finais *
 **************************************/

/**
 * Filtra um vector de atletas por escal�o e/ou nacionalidade.
 *
 * Requires:
 *   0 < tamanhoOrigem (� o tamanho efectivo de vecOrigem);
 *   vecDestino tem de ter tamanho suficiente para guardar os elementos filtrados;
 *   escalao e nacionalidade t�m de ser etiquetas v�lidas, ou a string vazia.
 * Ensures:
 *   copia para vecDestino os elementos de vecOrigem que t�m o escal�o e/ou
 *   a nacionalidade indicados;
 *   � preservada a ordem dos elementos como est� em vecOrigem;
 *   assim, se vecOrigem estiver ordenado (por exemplo, por posicaoFinalAbsoluta),
 *   vecDestino tamb�m o estar�;
 *   se escalao ou nacionalidade forem a string vazia, n�o � aplicado o respectivo
 *   filtro;
 *   devolve o n�mero de elementos copiados para vecDestino.
 */
int filtraEscalaoNacionalidade( Atleta vecOrigem[], Atleta vecDestino[],
                                int tamanhoOrigem,
                                const char *escalao, const char *nacionalidade );

