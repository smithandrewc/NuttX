/************************************************************************************
 * arch/arm/src/sama5/sam_ethernet.h
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_SAMA5_SAM_ETHERNET_H
#define __ARCH_ARM_SRC_SAMA5_SAM_ETHERNET_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include "chip.h"
#include "chip/sam_emac.h"
#include "chip/sam_gmac.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Definitions for use with sam_phy_boardinitialize */

#define GMAC_INTF 0
#define EMAC_INTF 1

/* Which is ETH0 and which is ETH1? */

#ifndef CONFIG_SAMA5_GMAC
#  undef CONFIG_SAMA5_GMAC_ISETH0
#endif

#ifndef CONFIG_SAMA5_EMAC
#  undef CONFIG_SAMA5_EMAC_ISETH0
#endif

#if defined(CONFIG_SAMA5_GMAC_ISETH0) && defined(CONFIG_SAMA5_EMAC_ISETH0)
#  error GMAC and EMAC cannot both be ETH0
#endif

#if defined(CONFIG_SAMA5_GMAC_ISETH0)
#  if defined(CONFIG_ETH0_PHY_DM9161)
#    define SAMA5_GMAC_PHY_DM9161 1
#  elif defined(CONFIG_ETH0_PHY_LAN8700)
#    define SAMA5_GMAC_PHY_LAN8700 1
#  elif defined(CONFIG_ETH0_PHY_KSZ8051)
#    define SAMA5_GMAC_PHY_KSZ8051 1
#  elif defined(CONFIG_ETH0_PHY_KSZ90x1)
#    define SAMA5_GMAC_PHY_KSZ90x1 1
#  else
#    error ETH0 PHY unrecognized
#  endif
#elif defined(CONFIG_SAMA5_GMAC)
#  if defined(CONFIG_ETH1_PHY_DM9161)
#    define SAMA5_GMAC_PHY_DM9161 1
#  elif defined(CONFIG_ETH1_PHY_LAN8700)
#    define SAMA5_GMAC_PHY_LAN8700 1
#  elif defined(CONFIG_ETH1_PHY_KSZ8051)
#    define SAMA5_GMAC_PHY_KSZ8051 1
#  elif defined(CONFIG_ETH1_PHY_KSZ90x1)
#    define SAMA5_GMAC_PHY_KSZ90x1 1
#  else
#    error ETH1 PHY unrecognized
#  endif
#endif

#if defined(CONFIG_SAMA5_EMAC_ISETH0)
#  if defined(CONFIG_ETH0_PHY_DM9161)
#    define SAMA5_EMAC_PHY_DM9161 1
#  elif defined(CONFIG_ETH0_PHY_LAN8700)
#    define SAMA5_EMAC_PHY_LAN8700 1
#  elif defined(CONFIG_ETH0_PHY_KSZ8051)
#    define SAMA5_EMAC_PHY_KSZ8051 1
#  elif defined(CONFIG_ETH0_PHY_KSZ90x1)
#    define SAMA5_EMAC_PHY_KSZ90x1 1
#  else
#    error ETH0 PHY unrecognized
#  endif
#elif defined(CONFIG_SAMA5_EMAC)
#  if defined(CONFIG_ETH1_PHY_DM9161)
#    define SAMA5_EMAC_PHY_DM9161 1
#  elif defined(CONFIG_ETH1_PHY_LAN8700)
#    define SAMA5_EMAC_PHY_LAN8700 1
#  elif defined(CONFIG_ETH1_PHY_KSZ8051)
#    define SAMA5_EMAC_PHY_KSZ8051 1
#  elif defined(CONFIG_ETH1_PHY_KSZ90x1)
#    define SAMA5_EMAC_PHY_KSZ90x1 1
#  else
#    error ETH1 PHY unrecognized
#  endif
#endif
/************************************************************************************
 * Public Functions
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Function: sam_gmac_initialize
 *
 * Description:
 *   Initialize the GMAC driver.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 * Assumptions:
 *   Called very early in the initialization sequence.
 *
 ****************************************************************************/

#ifdef CONFIG_SAMA5_GMAC
int sam_gmac_initialize(void);
#endif

/****************************************************************************
 * Function: sam_emac_initialize
 *
 * Description:
 *   Initialize the EMAC driver.
 *
 * Input Parameters:
 *   None
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 * Assumptions:
 *   Called very early in the initialization sequence.
 *
 ****************************************************************************/

#ifdef CONFIG_SAMA5_EMAC
int sam_emac_initialize(void);
#endif

/************************************************************************************
 * Function: sam_phy_boardinitialize
 *
 * Description:
 *   Some boards require specialized initialization of the PHY before it can be used.
 *   This may include such things as configuring GPIOs, resetting the PHY, etc.  If
 *   CONFIG_SAMA5_PHYINIT is defined in the configuration then the board specific
 *   logic must provide sam_phyinitialize();  The SAMA5 Ethernet driver will call
 *   this function one time before it first uses the PHY.
 *
 * Parameters:
 *   intf - Always zero for now.
 *
 * Returned Value:
 *   OK on success; Negated errno on failure.
 *
 * Assumptions:
 *
 ************************************************************************************/

#ifdef CONFIG_SAMA5_PHYINIT
int sam_phy_boardinitialize(int intf);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __ARCH_ARM_SRC_SAMA5_SAM_ETHERNET_H */

