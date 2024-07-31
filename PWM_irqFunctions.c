void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    UNUSED(htim);

    borda_t borda;
    uint32_t pulso;

    if ((htim->Instance == TIM3) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
    {
        borda = PARAM_get_borda();
      
        borda = (borda == DESCIDA) ? SUBIDA : DESCIDA;
      
        PARAM_set_borda(borda);

        pulso = PARAM_get_pulso(borda);
      
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulso);
    }
    else
    {
        __NOP();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    UNUSED(htim);

    uint32_t pulso_subida;
    uint32_t pulso_descida;

    if (htim->Instance == TIM2)
    {
        pulso_subida = Ramp_SoftStarter[i];
        pulso_descida = pulso_subida + LARGURA_PULSO_CCR;

        PARAM_set_pulso(SUBIDA, pulso_subida);
        PARAM_set_pulso(DESCIDA, pulso_descida);
    }
    else
    {
        __NOP();
    }
  
}
