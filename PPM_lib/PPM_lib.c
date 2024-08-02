/**
 *  @ingroup PPM_aplication
 *  @addtogroup PPM_source PPM
 *  @{
 *
 *  @title{Módulo: PPM}
 *  @brief   Este módulo fornece funções para manipular parâmetros PPM como `borda`, `pulso` e `angulo_iterador`.
 *           Inclui funções para definir e obter esses parâmetros, encapsulando o acesso a uma instância estática de `pulso_parametros_t`.
 *
 *  @file    PPM_lib.c
 *  @autor   Rafael V. Volkmer
 */

/* ****************
 * ARQUIVOS INCLUÍDOS *
 * ****************/

/* Dependencias: */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* implementações: */
#include "PPM_lib.h"

/* *********************************
 * DEFINIÇÃO DE FUNÇÕES PRIVADAS *
 * *********************************/

/**
 * @title{PPM - PARAM_setAndGet}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
void* PARAM_setAndGet(parametro_t param, operacao_t op, void* value)
{
    void* saida = NULL;

   static pulso_parametros_t parametros =
  { 
        .borda           = DESCIDA, 
        .pulso           = {PULSO_INICIAL_CCR, PULSO_INICIAL_CCR + LARGURA_PULSO_CCR}, 
        .angulo_iterador = 0u
    };

    if( (op == SET && value == NULL) )
    {
      goto error_case;
    }

    switch (param)
    {
        case BORDA:
            saida = &parametros.borda;
            parametros.borda = (op == SET) ? *(borda_t*)value : (parametros.borda);
            break;
      
        case PULSO_1:
            saida = &parametros.pulso[DESCIDA];
            parametros.pulso[DESCIDA] = (op == SET) ? *(uint32_t*)value : (parametros.pulso[DESCIDA]);
            break;
      
        case PULSO_2:
            saida = &parametros.pulso[SUBIDA];
            parametros.pulso[SUBIDA] = (op == SET) ? *(uint32_t*)value : (parametros.pulso[SUBIDA]);
            break;
      
        case ANGULO_ITERADOR:
            saida = &parametros.angulo_iterador;
            parametros.angulo_iterador = (op == SET) ? *(uint16_t*)value : (parametros.angulo_iterador);
            break;
      
        default:
          error_case:
          saida = NULL;
            break;
    }

    return saida;
}

/**
 * @title{PPM - PARAM_get_borda}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline borda_t PARAM_get_borda()
{
    borda_t saida = 0;
  
    saida = *(borda_t*)PARAM_setAndGet(BORDA, GET, NULL);
  
    return saida;
}

/**
 * @title{PPM - PARAM_set_borda}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline void PARAM_set_borda(borda_t value)
{
    PARAM_setAndGet(BORDA, SET, &value);
}

/**
 * @title{PPM - PARAM_get_pulso}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline uint32_t PARAM_get_pulso(int index)
{
    uint32_t saida = 0;
  
    if (index >= 0 && index < N_BORDAS) 
    {
        saida = *(uint32_t*)PARAM_setAndGet(index == DESCIDA ? PULSO_1 : PULSO_2, GET, NULL);
    }
  
    return saida;
}

/**
 * @title{PPM - PARAM_set_pulsos}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline void PARAM_set_pulso(int index, uint32_t value)
{
    if (index >= 0 && index < N_BORDAS) 
    {
        PARAM_setAndGet(index == DESCIDA ? PULSO_1 : PULSO_2, SET, &value);
    }
}

/**
 * @title{PPM - PARAM_get_angulo_iterador}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline uint16_t PARAM_get_angulo_iterador()
{
    uint16_t saida = 0;
  
    saida = *(uint16_t*)PARAM_setAndGet(ANGULO_ITERADOR, GET, NULL);
  
    return saida;
}

/**
 * @title{PPM - PARAM_set_angulo_iterador}
 *
 * TODO: Nada até agora. A função funciona perfeitamente (adicione aqui uma possível solução se ocorrer um bug).
 *  
 **/
inline void PARAM_set_angulo_iterador(uint16_t value)
{
    PARAM_setAndGet(ANGULO_ITERADOR, SET, &value);
}

/*** end of file ***/
