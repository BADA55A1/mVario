#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>

#include "hardware/uart/uart.h"
#include "hardware/i2cmaster/i2cmaster.h"
#include "hardware/bme280/bme280.h"
#include "hardware/ssd1306/SSD1306.h"
#include "hardware/toneAC/toneAC.h"
#include "hardware/battery/battery.h"
#include "hardware/buttons/buttons.h"


int main(void) {
    //PORTC = (1<<PC5)|(1<<PC4);

    uart_init();
    i2c_init();

    toneAC(880);
    _delay_us(100000);
    toneAC(1760);
    _delay_us(100000);
    noToneAC();
    
    printf("BAT_V: %d (?)\n", get_battery_voltage());


    BME280 sensor;
    if(sensor.deviceOK()) printf("BME280: OK\n");

	float pressure, temperature, humidity;

    sensor.setPressureSampling(BME280::SAMPLING_X2);
    sensor.setTemperatureSampling(BME280::SAMPLING_X1);
    sensor.setHumiditySampling(BME280::SAMPLING_X1);
    sensor.setFilter(BME280::FILTER_X2);
    //printf("applySettings: %d (?)\n", sensor.applySettings());

    for(int i = 0; i < 1; i++) 
    {
        sensor.measure(&pressure, &temperature, &humidity);
        printf("p: %f\n", pressure);
	    printf("t: %f\n", temperature);
	    printf("h: %f\n", humidity);
        printf("alt_: %f\n", BME280calcAltitude(pressure));
        printf("alt+: %f\n", BME280calcAltitude(pressure, temperature));
	    printf("---\n");
        _delay_ms(200);
    }

    btn_init();

	BTNstatus btn { .raw= 0};
	for(;;)
	{
		btn = btn_read();
		if(btn.raw)
		{
			if(btn.btn_a) printf("a, ");
			if(btn.btn_b) printf("b, ");
			if(btn.btn_c) printf("c, ");
			printf("\n");
		}
		_delay_ms(20);
	}

    uint8_t buffer[1024];
    for(int i = 0; i < 1024; i++) buffer[i] = 0x00;

    SSD1306 myDisplay;
    myDisplay.sendFramebuffer(buffer);

    // myDisplay.invert(1);
    // myDisplay.invert(0);


    // if (0 == i2c_start(0x76)) {
    //     printf("Found device: 0x76!\n");
    // }
    // if (0 == i2c_start(0x3C)) {
    //     printf("Found device: 0x3C!\n");
    // }

    // for (uint8_t adr = 0; adr < 128; adr++) {
    //     printf("Scan: 0x%x (%x)\n", adr, (adr<<1 | I2C_READ));
    //     if (0 == i2c_start(adr<<1)) {
    //         printf("Found device: 0x%x!\n", adr);
    //         i2c_stop();
    //     }
    //     _delay_ms(100);
    // }

    puts("Hi!\n");
    
    char input;
    int i = 0;
    while(1) {
        input = getchar();
        printf("%c", input);        
        buffer[i] = input;
        myDisplay.sendFramebuffer(buffer);
        i++;
    }
        
    return 0;
}