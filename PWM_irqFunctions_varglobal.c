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
