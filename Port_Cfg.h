
/******************************************************************************************
 * File Name: Port_Cfg.h
 * 
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 * 
 * Author: Tarek Emad
******************************************************************************************/

/**
 *@file Port_Cfg.h
    *@brief Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver.
    *@date 21/8/2024
    *@version 1.0.0
    *@see Port_PBcfg.h
    *@see Port.h
    *@see Port.c
    *@see Dio.h
    *@see Dio.c
 */
#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
* Module Version 1.0.0
*/

#define PORT_CFG_SW_MAJOR_VERSION      (1U)
#define PORT_CFG_SW_MINOR_VERSION      (0U)
#define PORT_CFG_SW_PATCH_VERSION      (0U)

/*
* AUTOSAR Version 4.0.3
*/

#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/************************************************************************
 *                      Configurations                                  *
 ************************************************************************/

/* precompile option for Development Error Detect */

#define PORT_DEV_ERROR_DETECT            (STD_ON)

/* precompile option for Version Info API */
#define PORT_VERSION_INFO_API            (STD_ON)

/* Number of the configured Port Pins */
#define PORT_CONFIGURED_PINS            (2U)

/*set pin direction api*/
#define PORT_SET_PIN_DIRECTION_API       (STD_ON)

/* Port Pin ID's */

#define PortConf_LED1_PIN_NUM           (Port_PinType)1
#define PortConf_SW1_PIN_NUM            (Port_PinType)4

/* Port ID */
#define PortConf_LED1_PORT_NUM          (Port_PortType)5 /* PORT F */
#define PortConf_SW1_PORT_NUM           (Port_PortType)5 /* PORT F */


#endif
/* PORT_CFG_H */
