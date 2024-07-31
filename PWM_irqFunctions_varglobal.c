
/* DEFINES */
#define N_BORDAS 2

#define PULSO_INICIAL_CCR 17400
#define LARGURA_PULSO_CCR 540

/* VARIAVEIS */
typedef enum {SUBIDA = 0, DESCIDA} Borda_t;
static Borda_t Borda = SUBIDA;

static uint16_t novoPulso = PULSO_INICIAL_CCR;
static uint16_t Pulso [N_BORDAS] = {PULSO_INICIAL_CCR, (PULSO_INICIAL_CCR + LARGURA_PULSO_CCR)};

static uint16_t i;
static uint16_t angulo;

/* FUNÇÕES IRQ */
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);

	if( (htim->Instance == TIM3) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) )
	{
		Borda = (Borda == DESCIDA) ? SUBIDA : DESCIDA;

		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (Pulso[Borda]));
	}
	else
	{
		__NOP();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);

	if(htim->Instance == TIM2)
	{
		Pulso[SUBIDA] = Ramp_SoftStarter[i];
		Pulso[DESCIDA] = (Pulso[SUBIDA] + LARGURA_PULSO_CCR);
    	}
    	else
	{
		__NOP();
	}
}
