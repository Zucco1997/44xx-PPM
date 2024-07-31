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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ramp_vector.h"

/**
 * @def N_BORDAS
 * @brief Define o número de bordas utilizadas no PPM.
 */
#define N_BORDAS 2

/**
 * @def PULSO_INICIAL_CCR
 * @brief Define o valor inicial do pulso CCR baseado no primeiro valor de Ramp_SoftStarter.
 */
#define PULSO_INICIAL_CCR (uint32_t)(Ramp_SoftStarter[0])

/**
 * @def LARGURA_PULSO_CCR
 * @brief Define a largura do pulso CCR.
 */
#define LARGURA_PULSO_CCR (uint32_t)(540U)

/**
 * @brief bordasPPM
 * @brief Enumeração que define os tipos de bordas no PPM.
 * 
 * @typedef borda_t
 */
typedef enum bordasPPM
{ 
  SUBIDA              = (uint8_t)(0u), /**< Borda de subida */
  DESCIDA             = (uint8_t)(1u)  /**< Borda de descida */
} borda_t;

/**
 *  @addtogroup M4F_application
 *  @{
 *  @addtogroup M4F_Timer Timer
 *  @{
 * 
 *  @title{Module: Timer}
 *  @brief This module provides functionalities for managing timers, including configuration, 
 *  starting, stopping, and handling interrupts. It abstracts the hardware details 
 *  and provides a high-level API for timer operations.
 *
 *  @brief          Timer Module
 *  @headerfile     M4F_timer.h
 *  @author         Rafael V. Volkmer
 */

#ifndef PWM_LIB_H_
#define PWM_LIB_H_

/* ****************
 * INCLUDED FILES *
 * ****************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* *********************************
 * DEFINITION OF PUBLIC STRUCTURES *
 * *********************************/

/**
 * @brief setGet
 * @brief Enumeração que define as operações de set e get.
 * 
 * @typedef operacao_t
 */
typedef enum setGet
{
    GET               = (uint8_t)(0u), /**< Operação de obtenção de valor */
    SET               = (uint8_t)(1u)  /**< Operação de definição de valor */
} operacao_t;

/**
 * @brief parametrosPPM
 * @brief Enumeração que define os parâmetros do PPM.
 * 
 * @typedef parametro_t
 */
typedef enum parametrosPPM
{
    BORDA             = (uint8_t)(0u), /**< Parâmetro de borda */
    PULSO_1           = (uint8_t)(1u), /**< Parâmetro de pulso 1 */
    PULSO_2           = (uint8_t)(2u), /**< Parâmetro de pulso 2 */
    ANGULO_ITERADOR   = (uint8_t)(3u)  /**< Parâmetro de ângulo iterador */
} parametro_t;

/**
 * @brief parametrosPulso
 * @brief Estrutura que define os parâmetros do pulso no PPM.
 * 
 * @typedef pulso_parametros_t
 */
typedef struct parametrosPulso
{
  borda_t   borda;                      /**< Tipo de borda (subida ou descida) */
  uint32_t  pulso[N_BORDAS];            /**< Array de pulsos */
  uint16_t  angulo_iterador;            /**< Ângulo iterador */
} pulso_parametros_t;

/* *********************************
 * PROTOTYPES OF PRIVATE FUNCTIONS *
 * *********************************/

/**
 * @title{PPM - PARAM_setAndGet}
 *
 * @brief   Esta função define ou obtém um valor de parâmetro na estrutura estática `pulso_parametros_t`.
 *          A função encapsula o acesso a esta estrutura, garantindo operações seguras.
 *
 * @param   param [in] : Enumeração que especifica o parâmetro a ser acessado ou modificado.
 * @param   op    [in] : Operação a ser realizada (GET ou SET).
 * @param   value [in] : Ponteiro para o valor a ser definido (usado apenas se a operação for SET).
 *
 * @return  Ponteiro para o valor do parâmetro:
 *              - Não NULL : Ponteiro válido para o valor do parâmetro.
 *              - NULL     : Operação ou parâmetro inválido especificado.
 */
void* PARAM_setAndGet(parametro_t param, operacao_t op, void* value);

/**
 * @title{PPM - PARAM_get_borda}
 *
 * @brief   Esta função retorna o valor de `borda` da estrutura estática `pulso_parametros_t`.
 *
 * @return  O valor de `borda`.
 */
inline borda_t PARAM_get_borda();

/**
 * @title{PPM - PARAM_set_borda}
 *
 * @brief   Esta função define o valor de `borda` na estrutura estática `pulso_parametros_t`.
 *
 * @param   value [in] : O valor de `borda` a ser definido.
 */
inline void PARAM_set_borda(borda_t value);

/**
 * @title{PPM - PARAM_get_pulso}
 *
 * @brief   Esta função retorna o valor de `pulso` para o índice especificado da estrutura estática `pulso_parametros_t`.
 *
 * @param   index [in] : O índice do array `pulso`.
 *
 * @return  O valor de `pulso`.
 */
inline uint32_t PARAM_get_pulso(int index);

/**
 * @title{PPM - PARAM_set_pulso}
 *
 * @brief   Esta função define o valor de `pulso` para o índice especificado na estrutura estática `pulso_parametros_t`.
 *
 * @param   index [in] : O índice do array `pulso`.
 * @param   value [in] : O valor de `pulso` a ser definido.
 */
inline void PARAM_set_pulso(int index, uint32_t value);

/**
 * @title{PPM - PARAM_get_angulo_iterador}
 *
 * @brief   Esta função retorna o valor de `angulo_iterador` da estrutura estática `pulso_parametros_t`.
 *
 * @return  O valor de `angulo_iterador`.
 */
inline uint16_t PARAM_get_angulo_iterador();

/**
 * @title{PPM - PARAM_set_angulo_iterador}
 *
 * @brief   Esta função define o valor de `angulo_iterador` na estrutura estática `pulso_parametros_t`.
 *
 * @param   value [in] : O valor de `angulo_iterador` a ser definido.
 */
inline void PARAM_set_angulo_iterador(uint16_t value);


#endif /* #ifndef M4F_TIMER_H_ */
/**@}*/
/**@}*/
