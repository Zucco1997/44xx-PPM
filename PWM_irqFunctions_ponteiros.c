/**
 *  @brief   Este módulo fornece um exemplo de implementação das funções de callback que regem o PPM (Pulse Position Modulation).
 *           As funções de callback são configuradas para responder a interrupções de comparação de saída e de estouro de período
 *           dos timers configurados no Cube IDE.
 *           Este exemplo mostra como incluir e tratar essas funções no ambiente do Cube IDE, garantindo a manipulação adequada
 *           dos parâmetros PPM, como `borda`, `pulso` e `angulo_iterador`.
 *           Para que este exemplo funcione corretamente, é essencial que o IOC seja configurado adequadamente e que os
 *           registradores necessários sejam inicializados na função `main`.
 *
 *  @autor   Rafael V. Volkmer
 */

/**
 * @brief  Callback de Interrupção de Comparação de Saída do Timer
 *
 * @details Esta função é chamada quando uma interrupção de comparação de saída ocorre no Timer 3, Canal 1.
 *          A interrupção é gatilhada quando o valor do contador do timer atinge o valor do registro de comparação.
 *          A função alterna a borda (de subida para descida ou vice-versa) e atualiza o valor de comparação para a próxima borda.
 *
 * @param   htim [in] : Ponteiro para a estrutura TIM_HandleTypeDef que contém a configuração do timer.
 */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    UNUSED(htim);

    borda_t borda;
    uint32_t pulso;

    // Verifica se a interrupção é do Timer 3, Canal 1
    if ((htim->Instance == TIM3) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
    {
        // Obtém o valor atual da borda
        borda = PARAM_get_borda();
      
        // Alterna a borda (de subida para descida ou vice-versa)
        borda = (borda == DESCIDA) ? SUBIDA : DESCIDA;
      
        // Define a nova borda
        PARAM_set_borda(borda);

        // Obtém o valor do pulso para a borda atual
        pulso = PARAM_get_pulso(borda);
      
        // Atualiza o valor de comparação do Timer 3, Canal 1
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulso);
    }
    else
    {
        // No Operation (nenhuma operação é realizada)
        __NOP();
    }
}

/**
 * @brief  Callback de Interrupção de Período do Timer
 *
 * @details Esta função é chamada quando uma interrupção de estouro de período ocorre no Timer 2.
 *          A interrupção é gatilhada quando o valor do contador do timer atinge o valor máximo e reinicia.
 *          A função atualiza os valores dos pulsos de subida e descida com base nos valores de Ramp_SoftStarter.
 *
 * @param   htim [in] : Ponteiro para a estrutura TIM_HandleTypeDef que contém a configuração do timer.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    UNUSED(htim);

    uint32_t pulso_subida;
    uint32_t pulso_descida;

    // Verifica se a interrupção é do Timer 2
    if (htim->Instance == TIM2)
    {
        // Obtém o valor do pulso de subida a partir de Ramp_SoftStarter
        pulso_subida = Ramp_SoftStarter[i];
        // Calcula o valor do pulso de descida
        pulso_descida = pulso_subida + LARGURA_PULSO_CCR;

        // Define os valores dos pulsos de subida e descida
        PARAM_set_pulso(SUBIDA, pulso_subida);
        PARAM_set_pulso(DESCIDA, pulso_descida);
    }
    else
    {
        // No Operation (nenhuma operação é realizada)
        __NOP();
    }
}
