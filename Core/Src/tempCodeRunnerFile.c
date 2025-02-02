d);

	int adc_value = HAL_ADC_GetValue(&hadc1);

	float adc_vol	= (adc_value / 4095.0) * 3.3;

	sprintf(adc_out, "ADC: %d, %fV", adc_value, adc_vol);

	HAL_UART_Transmit_DMA(&huart3, (uint8_t*)adc_out, strlen(adc_out));

	HAL_Delay(500);