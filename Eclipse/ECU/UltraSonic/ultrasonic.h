/******************************************************************************
 *
 * Module: Ultra-Sonic Sensor
 *
 * File Name: ultra.h
 *
 * Created on: Oct 15, 2024
 *
 * Author: Shahd DIPLOMA90
 *
 *******************************************************************************/

#ifndef ECU_ULTRASONIC_ULTRASONIC_H_
#define ECU_ULTRASONIC_ULTRASONIC_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "../../std_types.h"

/*******************************************************************************
 *                                 Macros                                      *
 *******************************************************************************/

/* Ultra-sonic trigger pin configuration */
#define ULTRA_TRIG_PORT     PORTD_ID
#define ULTRA_TRIG_PIN      PIN7_ID

/* Error adjustment for ultra-sonic sensor reading (in ticks) */
#define ULTRA_TICKS_ERROR_ADJUST    95

/* Speed of sound divided by 2 (in cm/us) */
#define ULTRA_SPEED_SOUND_DIV_2_CM_US  0.017

/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

/* Global variable to store the measured distance in centimeters */
extern uint16 g_ultra_distanceCm;

/* Flag to indicate whether the distance measurement is ready */
extern uint8 g_ultra_distance_ready;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/

/**
 * @brief Initializes the ultra-sonic sensor.
 *
 * This function sets up the trigger pin as output and prepares the input
 * capture settings for the ultra-sonic sensor.
 */
void ULTRA_init(void);

/**
 * @brief Handles the input capture edge for ultra-sonic measurements.
 *
 * This function is the input capture interrupt service routine, used to
 * calculate the time taken for the ultra-sonic signal to travel to the object
 * and reflect back.
 */
void ULTRA_edgeHandler(void);

/**
 * @brief Starts the ultra-sonic sensor measurement.
 *
 * Triggers the ultra-sonic sensor to send a pulse and starts the measurement
 * process.
 *
 * @return boolean True if the sensor successfully triggered, false otherwise.
 */
boolean ULTRA_start(void);

/**
 * @brief Reads the calculated distance from the ultra-sonic sensor.
 *
 * This function returns the measured distance in centimeters.
 *
 * @return uint16 The distance in centimeters.
 */
uint16 ULTRA_readDistance(void);

#endif /* ECU_ULTRASONIC_ULTRASONIC_H_ */
