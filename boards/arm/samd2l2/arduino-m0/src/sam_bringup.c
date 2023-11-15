/****************************************************************************
 * boards/arm/samd2l2/arduino-m0/src/sam_bringup.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <debug.h>
#include <errno.h>

#include <nuttx/board.h>

#include "sam_config.h"
#include "arduino_m0.h"

#ifdef CONFIG_WS2812_HAS_WHITE
#define HAS_WHITE true
#else /* CONFIG_WS2812_HAS_WHITE */
#define HAS_WHITE false
#endif /* CONFIG_WS2812_HAS_WHITE */
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: sam_bringup
 *
 * Description:
 *   Bring up board features
 *
 ****************************************************************************/

int sam_bringup(void)
{
  int ret = OK;

  /* Configure the ADC driver */

#ifdef CONFIG_SAMD2L2_ADC
  ret = sam_adc_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize the ADC driver: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_WS2812
  /* Configure and initialize the WS2812 LEDs. */
#pragma message ("Configure and initialize the WS2812 LEDs with spi driver")

  ret = board_ws2812_initialize(0, WS2812_SPI, CONFIG_WS2812_LED_COUNT);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: board_ws2812_initialize() failed: %d\n", ret);
    }
#endif   

  return ret;
}
