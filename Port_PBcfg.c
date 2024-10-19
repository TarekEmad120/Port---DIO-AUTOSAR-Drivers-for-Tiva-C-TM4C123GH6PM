/*******************************************************************************************
* File Name: Port_PBcfg.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
*
* Author: Tarek Emad
*******************************************************************************************/
/**
 * @file Port_PBcfg.c
 * @brief Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver.
 * @date 21/7/2024
 * @version 1.0.0
 * @see Port_PBcfg.h
 * @see Port.h
 * @see Port.c
 * @see Dio.h
 * @see Dio.c
 * @see Port_Cfg.h
 */

#include "Port.h"

/*
* Module Version 1.0.0
*/

#define PORT_PBCFG_SW_MAJOR_VERSION      (1U)
#define PORT_PBCFG_SW_MINOR_VERSION      (0U)
#define PORT_PBCFG_SW_PATCH_VERSION      (0U)

/*
* AUTOSAR Version 4.0.3
*/
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/* checking Autosar  version in both Port.h and Port_PBcfg.c*/
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBcfg.c does not match the expected version"
#endif


/*checking software version in both Port.h and Port_PBcfg.c*/
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBcfg.c does not match the expected version"
#endif



/* Array of structure contains the configuration of the pins */
/**
 * @brief 
 * 
 * this array of structure contains the configuration of the pins
 * 
 * 
 * 
 */
extern const Port_ConfigType Port_Configuration = {
  
    PortConf_LED1_PORT_NUM,
    PortConf_LED1_PIN_NUM ,
    OUTPUT,
    OFF,
    STD_HIGH,
    PORT_PIN_MODE_DIO,
    STD_ON,
    STD_ON,
  
  
    PortConf_SW1_PORT_NUM,
    PortConf_SW1_PIN_NUM,
    INPUT,
    PULL_UP,
    STD_LOW,
    PORT_PIN_MODE_DIO,
    STD_ON,
    STD_ON,
  
};

