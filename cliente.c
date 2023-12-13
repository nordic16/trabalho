#include <stdio.h>
#include "corrida.h"
#include "graficos.h"

int main( void )
{
  FILE *resultPtr = fopen( "resultadoTestes.txt", "w" );
  int i;  /* contador a usar em ciclos */
  Tempo t;
  int minutos;

  fprintf( resultPtr, "-- Testando converteParaHorasAposInicio()\n" );

  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Fri.", 21 ) );
  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Sat.", 10 ) );
  fprintf( resultPtr, "%d\n", converteParaHorasAposInicio( "Sun.", 7 ) );

  fprintf( resultPtr, "\n-- Testando as funcoes getter e de conversao\n" );

  Tempo primeiraPassagemZeNinguem = { "Fri.", 21, 27, 3, 27 };

  Atleta zeNinguem = { 6666, "Jose Ninguem", "POR (PT)", "40-44M",
                       3000, 30, {46, 29, 59},
                       { 0, 117, 234, 351, 468, 585, 702, 819, 936 , 1053,
                         1117, 1234, 1351, 1468, 1585, 1702, 1819, 1936, 2053,
                         2117, 2234, 2351, 2468, 2790 } };

  Atleta *zeNinguemPtr = &zeNinguem;

  fprintf( resultPtr, "%d\n", minutosEmProva( primeiraPassagemZeNinguem ) );

  fprintf( resultPtr, "%d\n", dorsal( zeNinguem ) );
  fprintf( resultPtr, "%s\n", nome( zeNinguemPtr ) );
  fprintf( resultPtr, "%s\n", nacionalidade( zeNinguemPtr ) );
  fprintf( resultPtr, "%s\n", escalao( zeNinguemPtr ) );
  fprintf( resultPtr, "%d\n", posicaoFinalAbsoluta( zeNinguem ) );
  fprintf( resultPtr, "%d\n", posicaoFinalEscalao( zeNinguem ) );
  fprintf( resultPtr, "%d:%d:%d\n",
                      tempoNaMeta( zeNinguemPtr )[0],
                      tempoNaMeta( zeNinguemPtr )[1],
                      tempoNaMeta( zeNinguemPtr )[2] );
  fprintf( resultPtr, "%d\n", temposPassagem( zeNinguemPtr )[9] );

  primeiraPassagemZeNinguem = tempo( 207 );
  Tempo *primeiraPassagemZeNinguemPtr = &primeiraPassagemZeNinguem;
  fprintf( resultPtr, "%s ", primeiraPassagemZeNinguemPtr->diaDaSemana );
  fprintf( resultPtr, "%d:%d ", primeiraPassagemZeNinguem.horaDoDia,
                      primeiraPassagemZeNinguem.minutoAposHoraDoDia );
  fprintf( resultPtr, "(%d:%d apos o inicio)\n",
                      primeiraPassagemZeNinguem.horasAposInicio,
                      primeiraPassagemZeNinguem.minutosAposHorasAposInicio );

  fprintf( resultPtr, "\n-- Testando inicializaAtletas()\n" );

  Atleta listaAtletas[NR_ATLETAS];

  inicializaAtletas( listaAtletas, NR_ATLETAS, "UTMB_2023-starters.csv" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "        dorsal = %d\n",
                      listaAtletas[1000].dorsal );
  fprintf( resultPtr, "          nome = %s\n",
                      listaAtletas[1000].nome );
  fprintf( resultPtr, " nacionalidade = %s\n",
                      listaAtletas[1000].nacionalidade );
  fprintf( resultPtr, "       escalao = %s\n",
                      listaAtletas[1000].escalao );

  fprintf( resultPtr, "\n-- Testando atribuiResultadosNaMeta()\n" );

  atribuiResultadosNaMeta( listaAtletas, NR_ATLETAS, "UTMB_2023-final.csv" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "  posicaoFinalAbsoluta = %d\n",
                      listaAtletas[1000].posicaoFinalAbsoluta );
  fprintf( resultPtr, "   posicaoFinalEscalao = %d\n",
                      listaAtletas[1000].posicaoFinalEscalao );
  fprintf( resultPtr, "           tempoNaMeta = %2d:%2d:%2d\n",
                      listaAtletas[1000].tempoNaMeta[0],
                      listaAtletas[1000].tempoNaMeta[1],
                      listaAtletas[1000].tempoNaMeta[2] );

  /* na última linha do ficheiro "UTMB_2023-final.csv" */
  fprintf( resultPtr, "Atleta com o indice 2680 na lista de atletas:\n" );
  fprintf( resultPtr, "  posicaoFinalAbsoluta = %d\n",
                      listaAtletas[2680].posicaoFinalAbsoluta );
  fprintf( resultPtr, "   posicaoFinalEscalao = %d\n",
                      listaAtletas[2680].posicaoFinalEscalao );
  fprintf( resultPtr, "           tempoNaMeta = %2d:%2d:%2d\n",
                      listaAtletas[2680].tempoNaMeta[0],
                      listaAtletas[2680].tempoNaMeta[1],
                      listaAtletas[2680].tempoNaMeta[2] );

  fprintf( resultPtr, "\n-- Testando atribuiTemposPassagem()\n" );

  atribuiTemposPassagem( listaAtletas, NR_ATLETAS, "UTMB_2023-progress.csv" );

  fprintf( resultPtr, "Atleta com o indice 1000 na lista de atletas:\n" );
  fprintf( resultPtr, "   tempos de passagem em minutos; \n" );
  for ( i = 0; i < NR_PONTOS_PASSAGEM; i++ )
  {
    fprintf( resultPtr, " %5d", listaAtletas[1000].temposPassagem[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  fprintf( resultPtr, "\n-- Testando preencheTabelaPassagens()\n" );

  RegistoPassagem tabelaPassagens[NR_PONTOS_PASSAGEM][NR_ATLETAS];

  preencheTabelaPassagens( listaAtletas, NR_ATLETAS,
                           tabelaPassagens, NR_PONTOS_PASSAGEM );

  fprintf( resultPtr, "7 dorsais mais baixos, tempos registados na meta\n" );
  for ( i = 0; i < 7; i++ )
    fprintf( resultPtr, " %d |",
             tabelaPassagens[NR_PONTOS_PASSAGEM - 1][i].tempoPassagem );
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "Os mesmos 7, mas no formato de data-hora\n" );
  for ( i = 0; i < 7; i++ )
  {
    minutos = tabelaPassagens[NR_PONTOS_PASSAGEM - 1][i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, " %s %2d:%2d |", t.diaDaSemana,
               t.horaDoDia, t.minutoAposHoraDoDia );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "\n-- Testando ordenaPorTempoPassagem()\n" );

  fprintf( resultPtr, "Ordenando os atletas na meta\n" );

  RegistoPassagem vec[NR_ATLETAS];
  for ( i = 0; i < NR_ATLETAS; i++ )
    vec[i] = tabelaPassagens[NR_PONTOS_PASSAGEM - 1][i];

  ordenaPorTempoPassagem( vec, 0, NR_ATLETAS - 1 );

  fprintf( resultPtr, "Mostrando os 5 primeiros a chegar a meta\n" );
  for ( i = 0; i < 5; i++ )
    fprintf( resultPtr, "%11d |", vec[i].dorsal );
  fprintf( resultPtr, "\n" );
  for ( i = 0; i < 5; i++ )
  {
    minutos = vec[i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, " %s %2d:%2d |", t.diaDaSemana,
               t.horaDoDia, t.minutoAposHoraDoDia );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );
  for ( i = 0; i < 5; i++ )
  {
    minutos = vec[i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, "      %2d:%2d |",
               t.horasAposInicio, t.minutosAposHorasAposInicio );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "Mostrando os 5 ultimos do vector (nenhum chegou a meta)\n" );
  for ( i = NR_ATLETAS - 5; i < NR_ATLETAS; i++ )
    fprintf( resultPtr, "%11d |", vec[i].dorsal );
  fprintf( resultPtr, "\n" );
  for ( i = NR_ATLETAS - 5; i < NR_ATLETAS; i++ )
  {
    minutos = vec[i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, " %s %2d:%2d |", t.diaDaSemana,
               t.horaDoDia, t.minutoAposHoraDoDia );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "\n-- Testando ordenaTabelaPassagens()\n" );

  ordenaTabelaPassagens( NR_ATLETAS, tabelaPassagens, NR_PONTOS_PASSAGEM );

  fprintf( resultPtr, "Atletas a passar em Courmayeur nas posicoes 1001 a 1005\n" );
  for ( i = 1000; i < 1005; i++ )
    fprintf( resultPtr, "%11d |", tabelaPassagens[11][i].dorsal );
  fprintf( resultPtr, "\n" );
  for ( i = 1000; i < 1005; i++ )
  {
    minutos = tabelaPassagens[11][i].tempoPassagem;
    if ( minutos != 10000 )
    {
      t = tempo( minutos );
      fprintf( resultPtr, " %s %2d:%2d |", t.diaDaSemana,
               t.horaDoDia, t.minutoAposHoraDoDia );
    }
    else
      fprintf( resultPtr, " nao passou |" );
  }
  fprintf( resultPtr, "\n" );

  fprintf( resultPtr, "\n-- Testando ordenaPorPosicaoFinal(()\n" );

  Atleta listaAtletasOrdemChegada[NR_ATLETAS];

  for ( i = 0; i < NR_ATLETAS; i++ )
    listaAtletasOrdemChegada[i] = listaAtletas[i];

  ordenaPorPosicaoFinal( listaAtletasOrdemChegada, 0, NR_ATLETAS - 1 );

  fprintf( resultPtr, "Os 10 primeiros atletas a chegarem foram:\n" );
  for ( i = 0; i < 10; i++ )
    fprintf( resultPtr, "%4d %4d %23s  %2d:%2d:%2d\n",
             i + 1,
             listaAtletasOrdemChegada[i].dorsal,
             listaAtletasOrdemChegada[i].nome,
             listaAtletasOrdemChegada[i].tempoNaMeta[0],
             listaAtletasOrdemChegada[i].tempoNaMeta[1],
             listaAtletasOrdemChegada[i].tempoNaMeta[2] );

  fprintf( resultPtr, "\n-- Testando indiceAtleta()\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 surge em listaAtletas"
                      " com o indice %d.\n",
                      indiceAtleta( listaAtletas, NR_ATLETAS, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getAtleta()\n" );

  Atleta devolvido = getAtleta( listaAtletas, NR_ATLETAS, 1000 );
  fprintf( resultPtr, "O atleta com o dorsal 1000 chama-se %s\n",
                      devolvido.nome );

  fprintf( resultPtr, "\n-- Testando indiceRegistoPassagem()\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem passagem registada"
           " em Courmayeur com o indice %d.\n",
           indiceRegistoPassagem( tabelaPassagens[11], NR_ATLETAS, 1000 ) );

  fprintf( resultPtr, "\n-- Testando getRegistoPassagem()\n" );

  fprintf( resultPtr, "O atleta com o dorsal 1000 tem tempo de passagem"
           " em Courmayeur = %d  minutos.\n",
           getRegistoPassagem( tabelaPassagens[11], NR_ATLETAS, 1000 ).tempoPassagem );

  fprintf( resultPtr, "\n-- Testando registaPosicoesPostos()\n" );

  int posicoes1[NR_PONTOS_PASSAGEM];  /* para guardar as posições do atleta 1 */
  registaPosicoesPostos( NR_ATLETAS, tabelaPassagens,
                         NR_PONTOS_PASSAGEM, 1000, posicoes1 );
  fprintf( resultPtr, "As posicoes do atleta com o dorsal 1000 sao\n" );
  for ( i = 0; i < NR_PONTOS_PASSAGEM; i++ )
  {
    fprintf( resultPtr, " %5d", posicoes1[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  int posicoes2[NR_PONTOS_PASSAGEM];  /* para guardar as posições do atleta 2 */
  registaPosicoesPostos( NR_ATLETAS, tabelaPassagens,
                         NR_PONTOS_PASSAGEM, 700, posicoes2 );
  fprintf( resultPtr, "As posicoes do atleta com o dorsal 700 sao\n" );
  for ( i = 0; i < NR_PONTOS_PASSAGEM; i++ )
  {
    fprintf( resultPtr, " %5d", posicoes2[i] );
    if ( ( i + 1 ) % 6 == 0 )
      fprintf( resultPtr, "\n" );
  }

  fprintf( resultPtr, "\n-- Desenhando a serie temporal de posicoes do atleta"
                      " com o dorsal 1000\n"
                      "  -> ver ficheiro atleta1000.png\n" );

  double postos[NR_PONTOS_PASSAGEM];
  double posicoes1double[NR_PONTOS_PASSAGEM];
  for ( i = 0; i < NR_PONTOS_PASSAGEM; i++ )
  {
    postos[i] = i + 1.0;
    posicoes1double[i] = posicoes1[i] * 1.0;
  }

  desenhaSerieTemporal( postos, posicoes1double, NR_PONTOS_PASSAGEM,
                        600, 400, "atleta1000" );

  fprintf( resultPtr, "\n-- Comparando as series temporais de posicoes dos atletas"
                      " com os dorsais 1000 e 700\n"
                      "  -> ver ficheiro atletas_1000_700.png\n" );

  double posicoes2double[NR_PONTOS_PASSAGEM];
  for ( i = 0; i < NR_PONTOS_PASSAGEM; i++ )
  {
    posicoes2double[i] = posicoes2[i] * 1.0;
  }

  comparaSeriesTemporais( postos, posicoes1double, NR_PONTOS_PASSAGEM,
                          postos, posicoes2double, NR_PONTOS_PASSAGEM,
                          600, 400, "atletas_1000_700" );

  fprintf( resultPtr, "\n-- Testando filtraEscalaoNacionalidade()\n" );

  Atleta francesas40_44[NR_ATLETAS / 100];
  int quantasFrancesas40_44 = filtraEscalaoNacionalidade( listaAtletasOrdemChegada,
                                francesas40_44, NR_ATLETAS, "40-44W", "FRA (FR)" );
  fprintf( resultPtr, "Classificacao mulheres francesas 40-44 anos:\n" );
  fprintf( resultPtr, "%5s %7s %6s %23s %13s %8s\n",
           "Escalao", "Geral", "Dorsal", "Nome", "Nacionalidade", "Tempo" );
  for ( i = 0; i < quantasFrancesas40_44; i++ )
    fprintf( resultPtr, "  %5d %7d %6d %23s %13s %2d:%2d:%2d\n",
             francesas40_44[i].posicaoFinalEscalao,
             francesas40_44[i].posicaoFinalAbsoluta,
             francesas40_44[i].dorsal,
             francesas40_44[i].nome,
             francesas40_44[i].nacionalidade,
             francesas40_44[i].tempoNaMeta[0],
             francesas40_44[i].tempoNaMeta[1],
             francesas40_44[i].tempoNaMeta[2] );

  fclose( resultPtr );

  return 0;
}
