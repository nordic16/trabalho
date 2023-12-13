#include <string.h>

#include "graficos.h"

#include "pbPlots.h"
#include "supportLib.h"

#define DIMENSAO_NOME_FICHEIRO 75

double maximoDoArray( double vector[], int tamanho );
double minimoDoArray( double vector[], int tamanho );

int desenhaSerieTemporal( double xs[], double ys[], int tamanhoSerie,
                          double larguraImagem, double alturaImagem,
                          char *nomeFicheiroImagem )
{
  int success;
  int i;
  char nomeFicheiroImagemComExtensao[DIMENSAO_NOME_FICHEIRO];

  /* encontrar os limites de x e de y para o grafico */
  double xMaximo = maximoDoArray( xs, tamanhoSerie );
  double xMinimo = minimoDoArray( xs, tamanhoSerie );
  double yMaximo = maximoDoArray( ys, tamanhoSerie );
  double yMinimo = minimoDoArray( ys, tamanhoSerie );

  RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
  StringReference *errorMessage = CreateStringReference( L"", 0 );

  StartArenaAllocator();

  ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
  series->xs = xs;
  series->xsLength = tamanhoSerie;
  series->ys = ys;
  series->ysLength = tamanhoSerie;
  series->linearInterpolation = true;
  series->pointType = L"dotlinetoxaxis";
  series->pointTypeLength = wcslen(series->pointType);
  series->lineThickness = 2;
  series->color = CreateRGBColor(1, 0, 0);

  ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
  settings->width = larguraImagem;
  settings->height = alturaImagem;
  settings->autoBoundaries = false;
  settings->xMax = xMaximo;
  settings->xMin = xMinimo;
  settings->yMax = yMaximo;
  settings->yMin = yMinimo;
  settings->autoPadding = true;
  settings->xPadding = 0.0;
  settings->yPadding = 0.0;
  settings->title = L"";
  settings->titleLength = wcslen(settings->title);
  settings->xLabel = L"";
  settings->xLabelLength = wcslen(settings->xLabel);
  settings->yLabel = L"";
  settings->yLabelLength = wcslen(settings->yLabel);
  settings->xAxisAuto = true;
  settings->xAxisTop = false;
  settings->xAxisBottom = false;
  settings->yAxisAuto = true;
  settings->yAxisLeft = false;
  settings->yAxisRight = false;
  ScatterPlotSeries *s [] = {series}; /* aqui eh possivel colocar mais series */
  settings->scatterPlotSeries = s;
  settings->scatterPlotSeriesLength = 1;

  success = DrawScatterPlotFromSettings( canvasReference, settings, errorMessage);

  if ( success )
  {
    ByteArray *pngdata = ConvertToPNG( canvasReference->image );
    strcpy( nomeFicheiroImagemComExtensao, nomeFicheiroImagem );
    strcat( nomeFicheiroImagemComExtensao, ".png" );
    WriteToFile( pngdata, nomeFicheiroImagemComExtensao );
    DeleteImage( canvasReference->image );
  }
  else
  {
    fprintf( stderr, "Error: " );
    for( i = 0; i < errorMessage->stringLength; i++ )
    {
      fprintf( stderr, "%c", errorMessage->string[i] );
    }
    fprintf( stderr, "\n" );
  }

  FreeAllocations();

  return success ? 0 : 1;
}

int comparaSeriesTemporais( double xsPrimeira[], double ysPrimeira[],
                            int tamanhoPrimeira,
                            double xsSegunda[], double ysSegunda[],
                            int tamanhoSegunda,
                            double larguraImagem, double alturaImagem,
                            char *nomeFicheiroImagem )
{
  int success;
  int i;
  char nomeFicheiroImagemComExtensao[DIMENSAO_NOME_FICHEIRO];

  /* encontrar os limites de x e de y para o grafico */
  double xMaximo = maximoDoArray( xsPrimeira, tamanhoPrimeira );
  double xMinimo = minimoDoArray( xsPrimeira, tamanhoPrimeira );
  double yMaximo = maximoDoArray( ysPrimeira, tamanhoPrimeira );
  double yMinimo = minimoDoArray( ysPrimeira, tamanhoPrimeira );

  double xMaximoNovo = maximoDoArray( xsSegunda, tamanhoSegunda );
  if ( xMaximoNovo > xMaximo )
    xMaximo = xMaximoNovo;
  double xMinimoNovo = minimoDoArray( xsSegunda, tamanhoSegunda );
  if ( xMinimoNovo < xMinimo )
    xMinimo = xMinimoNovo;
  double yMaximoNovo = maximoDoArray( ysSegunda, tamanhoSegunda );
  if ( yMaximoNovo > yMaximo )
    yMaximo = yMaximoNovo;
  double yMinimoNovo = minimoDoArray( ysSegunda, tamanhoSegunda );
  if ( yMinimoNovo < yMinimo )
    yMinimo = yMinimoNovo;

  RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
  StringReference *errorMessage = CreateStringReference( L"", 0 );

  StartArenaAllocator();

  ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
  series->xs = xsPrimeira;
  series->xsLength = tamanhoPrimeira;
  series->ys = ysPrimeira;
  series->ysLength = tamanhoPrimeira;
  series->linearInterpolation = true;
  series->pointType = L"dotlinetoxaxis";
  series->pointTypeLength = wcslen(series->pointType);
  series->lineThickness = 2;
  series->color = CreateRGBColor(1, 0, 0);

  ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
  series2->xs = xsSegunda;
  series2->xsLength = tamanhoSegunda;
  series2->ys = ysSegunda;
  series2->ysLength = tamanhoSegunda;
  series2->linearInterpolation = true;
  series2->pointType = L"dotlinetoxaxis";
  series2->pointTypeLength = wcslen(series->pointType);
  series2->lineThickness = 2;
  series2->color = CreateRGBColor(0, 0, 1);

  ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
  settings->width = larguraImagem;
  settings->height = alturaImagem;
  settings->autoBoundaries = false;
  settings->xMax = xMaximo;
  settings->xMin = xMinimo;
  settings->yMax = yMaximo;
  settings->yMin = yMinimo;
  settings->autoPadding = true;
  settings->xPadding = 0.0;
  settings->yPadding = 0.0;
  settings->title = L"";
  settings->titleLength = wcslen(settings->title);
  settings->xLabel = L"";
  settings->xLabelLength = wcslen(settings->xLabel);
  settings->yLabel = L"";
  settings->yLabelLength = wcslen(settings->yLabel);
  settings->xAxisAuto = true;
  settings->xAxisTop = false;
  settings->xAxisBottom = false;
  settings->yAxisAuto = true;
  settings->yAxisLeft = false;
  settings->yAxisRight = false;
  ScatterPlotSeries *s [] = { series, series2 };
  settings->scatterPlotSeries = s;
  settings->scatterPlotSeriesLength = 2;

  success = DrawScatterPlotFromSettings( canvasReference, settings, errorMessage);

  if ( success )
  {
    ByteArray *pngdata = ConvertToPNG( canvasReference->image );
    strcpy( nomeFicheiroImagemComExtensao, nomeFicheiroImagem );
    strcat( nomeFicheiroImagemComExtensao, ".png" );
    WriteToFile( pngdata, nomeFicheiroImagemComExtensao );
    DeleteImage( canvasReference->image );
  }
  else
  {
    fprintf( stderr, "Error: " );
    for( i = 0; i < errorMessage->stringLength; i++ )
    {
      fprintf( stderr, "%c", errorMessage->string[i] );
    }
    fprintf( stderr, "\n" );
  }

  FreeAllocations();

  return success ? 0 : 1;
}

double maximoDoArray( double vector[], int tamanho )
{
   int i;
   double max = vector[0];
   for ( i = 1; i < tamanho; i++ )
     if (vector[i] > max)
       max = vector[i];
   return max;
}

double minimoDoArray( double vector[], int tamanho )
{
   int i;
   double min = vector[0];
   for ( i = 1; i < tamanho; i++ )
     if (vector[i] < min)
       min = vector[i];
   return min;
}

