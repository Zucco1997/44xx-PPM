#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "softstarter_rampa.h"

#define N_BORDAS 2

#define PULSO_INICIAL_CCR (uint32_t)(17400U)
#define LARGURA_PULSO_CCR (uint32_t)(540U)

typedef enum bordasPPM
{ 
  SUBIDA              = (uint8_t)(0u),
  DESCIDA             = (uint8_t)(1u)
}borda_t;

typedef enum setGet
{
    GET               = (uint8_t)(0u),
    SET               = (uint8_t)(1u)
} operacao_t;

typedef enum parametrosPPM
{
    BORDA             = (uint8_t)(0u),
    PULSO_1           = (uint8_t)(1u),
    PULSO_2           = (uint8_t)(2u),
    ANGULO_ITERADOR   = (uint8_t)(3u)
} parametro_t;

typedef struct parametrosPulso
{
  borda_t   borda;
  uint32_t  pulso[N_BORDAS];
  uint16_t  angulo_iterador;
} pulso_parametros_t;
