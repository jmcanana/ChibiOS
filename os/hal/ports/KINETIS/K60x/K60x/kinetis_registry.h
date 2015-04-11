/*
    ChibiOS/HAL - Copyright (C) 2014 Derek Mulcahy

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    kinetis_registry.h
 * @brief   K60x capabilities registry.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _KINETIS_REGISTRY_H_
#define _KINETIS_REGISTRY_H_

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

/**
 * @name    K60x capabilities
 * @{
 */
/* EXT attributes.*/

#define KINETIS_PORTA_IRQ_VECTOR    Vector19C
#define KINETIS_PORTB_IRQ_VECTOR    Vector1A0
#define KINETIS_PORTC_IRQ_VECTOR    Vector1A4
#define KINETIS_PORTD_IRQ_VECTOR    Vector1A8
#define KINETIS_PORTE_IRQ_VECTOR    Vector1AC
#define KINETIS_PORTF_IRQ_VECTOR    Vector1B0

/* ADC attributes.*/
#define KINETIS_HAS_ADC0            TRUE
#define KINETIS_ADC0_IRC_VECTOR     Vector124
#define KINETIS_ADC1_IRC_VECTOR     Vector128

/* I2C attributes.*/
#define KINETIS_I2C0_IRQ_VECTOR     VectorA0
#define KINETIS_I2C1_IRQ_VECTOR     VectorA4

/** @} */

#endif /* _KINETIS_REGISTRY_H_ */

/** @} */
