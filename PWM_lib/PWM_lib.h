#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ramp_vector.h"

#define N_BORDAS 0

#define PULSO_INICIAL_CCR (uint32_t)(Ramp_SoftStarter[0])
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

void* PARAM_setAndGet(parametro_t param, operacao_t op, void* value);

inline borda_t PARAM_get_borda();

inline void PARAM_set_borda(borda_t value);

inline uint32_t PARAM_get_pulso(int index);

inline void PARAM_set_pulso(int index, uint32_t value);

inline uint16_t PARAM_get_angulo_iterador();

inline void PARAM_set_angulo_iterador(uint16_t value);
