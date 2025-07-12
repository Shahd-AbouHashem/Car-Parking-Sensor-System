/******************************************************************************
 *
 * File Name: main.c
 *
 * Created on: Oct 15, 2024
 *
 * Author: Shahd DIPLOMA90
 *
 *******************************************************************************/

#include "ECU/Buzzer/buzzer.h"
#include <util/delay.h>
#include "ECU/LCD/LCD.h"
#include "ECU/LED/LED.h"
#include "ECU/UltraSonic/ultrasonic.h"


static inline void DisplayDistance(void);
static inline void TriggerStopWarning(void);
static inline void AdjustLEDs(void);


int main(void) {
  /* Initialize all peripherals: ultrasonic sensor, buzzer, LCD, and LEDs */
  ULTRA_init();
  BUZZER_init(&g_buzzer1);
  LCD_init();
  LED_init(&g_ledRed);
  LED_init(&g_ledGreen);
  LED_init(&g_ledBlue);

  /* Activate global interrupts */
  __asm__("SEI");

  /* Begin ultrasonic distance measurement */
  ULTRA_start();

  /* Wait until the first distance reading becomes available */
  while (g_ultra_distance_ready == 0)
    ;

  /* Show the initial distance label on the LCD */
  LCD_displayString("Distance =   cm");

  for (;;) { /* Continuous loop */
    /* Verify if a new distance reading is available */
    if (TRUE == g_ultra_distance_ready) {
      /* Clear the distance ready flag and update the display */
      g_ultra_distance_ready = FALSE;
      DisplayDistance();
      /* Restart the ultrasonic sensor */
      ULTRA_start();
    }

    /* If an object is detected within 5 cm, activate the stop alert */
    if (5 >= g_ultra_distanceCm) {
      TriggerStopWarning();
    }
    else {
      /* Clear the stop alert from the LCD */
      LCD_moveCursor(1, 0);
      LCD_displayString("                         ");

      /* Update LED status based on the measured distance */
      AdjustLEDs();
    }
  }
}

static inline void DisplayDistance(void) {
  /* Move cursor to the position for distance and display the value */
  LCD_moveCursor(0, 10);
  LCD_displayNumber(ULTRA_readDistance());
  LCD_displayCharacter(' ');
}

static inline void TriggerStopWarning(void) {
  /* Display a stop message, activate the buzzer, and turn on all LEDs */
  LCD_moveCursor(1, 0);
  LCD_displayString("      STOP!!      ");
  BUZZER_turnOn(&g_buzzer1);
  LED_turnOn(&g_ledRed);
  LED_turnOn(&g_ledGreen);
  LED_turnOn(&g_ledBlue);

  /* Wait briefly, then deactivate buzzer and LEDs */
  _delay_ms(250);
  BUZZER_turnOff(&g_buzzer1);
  LED_turnOff(&g_ledRed);
  LED_turnOff(&g_ledGreen);
  LED_turnOff(&g_ledBlue);
  _delay_ms(250);
}

static inline void AdjustLEDs(void) {
  /* Control LED behavior based on how far the object is */
  if (10 >= g_ultra_distanceCm) {
    LED_turnOn(&g_ledRed);
    LED_turnOn(&g_ledGreen);
    LED_turnOn(&g_ledBlue);
  }
  else if (15 >= g_ultra_distanceCm) {
    LED_turnOn(&g_ledRed);
    LED_turnOn(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
  else if (20 >= g_ultra_distanceCm) {
    LED_turnOn(&g_ledRed);
    LED_turnOff(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
  else {
    /* Turn off all LEDs if the object is beyond 20 cm */
    LED_turnOff(&g_ledRed);
    LED_turnOff(&g_ledGreen);
    LED_turnOff(&g_ledBlue);
  }
}
