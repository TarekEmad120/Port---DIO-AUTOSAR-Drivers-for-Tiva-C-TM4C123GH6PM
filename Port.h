/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Tarek Emad
 ******************************************************************************/
/**
 * @file Port.h
 * @brief Header file for TM4C123GH6PM Microcontroller - Port Driver.
 * @date 21/8/2024
 * @version 1.0
 * @note This file contains the prototypes of the Port Driver functions.
 * @note This file contains the definitions of the symbolic names of the Port Driver.
 * @note This file contains the definitions of the symbolic names of the Port Driver APIs.
 * @note This file contains the definitions of the symbolic names of the Port Driver DET Error Codes.
 * @see Port_PBcfg.h
 * @see Port_Cfg.h
 * 
 */

#ifndef PORT_H
#define PORT_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "Port_Cfg.h"

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/
/**
 * @def PORT_VENDOR_ID
 * @brief Vendor ID who designed the module.
 * @note 100

 */
#define PORT_VENDOR_ID  (100U)
/**
 * @brief 
 * @def PORT_MODULE_ID
 * @brief Module ID of the Port Module.
 * @note 124
 * 
 */
#define PORT_MODULE_ID  (124U)
/**
 * @brief 
 * @def PORT_INSTANCE_ID
 * @brief Instance ID of the Port Module.
 * @note 0
 * 
 */
#define PORT_INSTANCE_ID  (0U)

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS 0x40004000
#define GPIO_PORTB_BASE_ADDRESS 0x40005000
#define GPIO_PORTC_BASE_ADDRESS 0x40006000
#define GPIO_PORTD_BASE_ADDRESS 0x40007000
#define GPIO_PORTE_BASE_ADDRESS 0x40024000
#define GPIO_PORTF_BASE_ADDRESS 0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET 0x3FC
#define PORT_DIR_REG_OFFSET 0x400
#define PORT_ALT_FUNC_REG_OFFSET 0x420
#define PORT_PULL_UP_REG_OFFSET 0x510
#define PORT_PULL_DOWN_REG_OFFSET 0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET 0x51C
#define PORT_LOCK_REG_OFFSET 0x520
#define PORT_COMMIT_REG_OFFSET 0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET 0x528
#define PORT_CTL_REG_OFFSET 0x52C

/* AUTOSAR Version 4.0.3 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_AR_RELEASE_PATCH_VERSION (3U)

/* Module Version 1.0.0 */
#define PORT_SW_MAJOR_VERSION (1U)
#define PORT_SW_MINOR_VERSION (0U)
#define PORT_SW_PATCH_VERSION (0U)


/*******************************************************************************
 *                    checking the Autosar version in Port_cfg.h                   *
 *******************************************************************************/

#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION) || (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION) || (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/*******************************************************************************
 *                              checking software version in port_cfg.h                    *
 *******************************************************************************/

#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION) || (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION) || (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/*******************************************************************************
 *                              API Services ID Macros                         *
 *******************************************************************************/

/* Service ID for Port_Init API */
#define PORT_INIT_SID (uint8)0x00

/* Service ID for Port_SetPinDirection API */
#define PORT_SET_PIN_DIRECTION_SID (uint8)0x01

/* Service ID for Port_RefreshPortDirection API */
#define PORT_REFRESH_PORT_DIRECTION_SID (uint8)0x02

/* Service ID for Port_GetVersionInfo API */
#define PORT_GET_VERSION_INFO_SID (uint8)0x03

/* Service ID for Port_SetPinMode API */
#define PORT_SET_PIN_MODE_SID (uint8)0x04

/*******************************************************************************
 *                              DET Error Codes                                *
 *******************************************************************************/

/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE (uint8)0x0D

/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE (uint8)0x0E

/* DET code to report API service called without module initialization */
#define PORT_E_UNINIT (uint8)0x0F

/* DET code to report API service called with NULL pointer */
#define PORT_E_PARAM_POINTER (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

typedef uint8 Port_PinType; /* data type for the symbolic name of a port pin. */

typedef uint8 Port_PortType; /* data type for the symbolic name of a port. */

typedef uint8 Port_PinModeType; /* data type for the symbolic name of a port pin mode. */

#define PORT_NOT_INITIALIZED  (0u)
#define PORT_INITIALIZED      (1u)

/* Description: Enum to hold PIN direction */
typedef enum
{
  INPUT,
  OUTPUT
} Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
  OFF,
  PULL_UP,
  PULL_DOWN
} Port_InternalResistor;



/**
 * @brief Enumeration representing the initial modes of a port pin.
 * 
 * This enumeration defines the possible initial modes of a port pin.
 * The initial mode determines the functionality of the pin when it is first initialized.
 * 
 * Possible values are:
 * - PORT_PIN_MODE_ADC: ADC mode
 * - PORT_PIN_MODE_ALT1: Alternate function mode 1
 * - PORT_PIN_MODE_ALT2: Alternate function mode 2
 * - PORT_PIN_MODE_ALT3: Alternate function mode 3
 * - PORT_PIN_MODE_ALT4: Alternate function mode 4
 * - PORT_PIN_MODE_ALT5: Alternate function mode 5
 * - PORT_PIN_MODE_ALT6: Alternate function mode 6
 * - PORT_PIN_MODE_ALT7: Alternate function mode 7
 * - PORT_PIN_MODE_ALT8: Alternate function mode 8
 * - PORT_PIN_MODE_ALT9: Alternate function mode 9
 * - PORT_PIN_MODE_ALT14: Alternate function mode 14
 * - PORT_PIN_MODE_ALT15: Alternate function mode 15
 * - PORT_PIN_MODE_DIO: Digital I/O mode
 */
typedef enum
{
  PORT_PIN_MODE_ADC,
  PORT_PIN_MODE_ALT1,
  PORT_PIN_MODE_ALT2,
  PORT_PIN_MODE_ALT3,
  PORT_PIN_MODE_ALT4,
  PORT_PIN_MODE_ALT5,
  PORT_PIN_MODE_ALT6,
  PORT_PIN_MODE_ALT7,
  PORT_PIN_MODE_ALT8,
  PORT_PIN_MODE_ALT9,
  PORT_PIN_MODE_ALT14,
  PORT_PIN_MODE_ALT15,
  PORT_PIN_MODE_DIO,
} Port_PinInitialMode;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 *     5. the initial value of the pin (STD_HIGH, STD_LOW)
 *    6. the initial mode of the pin (ADC, DIO, ALT1, ALT2, ALT3, ALT4, ALT5, ALT6, ALT7, ALT8, ALT9)
 *   7. the pin direction changeable
 * 8. the pin mode changeable
 */



/**
 * @brief Structure to configure each individual PIN.
 * 
 * This structure is used to configure each individual pin.
 * 
 * The structure contains the following members:
 * - port_num: The port to which the pin belongs. Possible values are 0, 1, 2, 3, 4, or 5.
 * - pin_num: The number of the pin in the port.
 * - direction: The direction of the pin. Possible values are INPUT or OUTPUT.
 * - resistor: The internal resistor of the pin. Possible values are OFF, PULL_UP, or PULL_DOWN.
 * - initial_value: The initial value of the pin. Possible values are STD_HIGH or STD_LOW.
 * - initial_mode: The initial mode of the pin. Possible values are ADC, DIO, ALT1, ALT2, ALT3, ALT4, ALT5, ALT6, ALT7, ALT8, ALT9, ALT14, or ALT15.
 * - pin_dir_changeable: Indicates whether the pin direction is changeable. Possible values are STD_ON or STD_OFF.
 * - pin_mode_changeable: Indicates whether the pin mode is changeable. Possible values are STD_ON or STD_OFF.
 * 
 */
typedef struct
{
  uint8 port_num;
  uint8 pin_num;
  Port_PinDirection direction;
  Port_InternalResistor resistor;
  uint8 initial_value;
  Port_PinInitialMode initial_mode;
  uint8 pin_dir_changeable;
  uint8 pin_mode_changeable;
} Port_ConfigChannel;




/**
 * @brief
 * 
 * This structure contains the configuration of the pins.
 * 
 * The structure contains the following member:
 * 
 * - Channels: Array of structures containing the configuration of the pins.
 * 
 * 
 */
typedef struct
{
  Port_ConfigChannel Channels[PORT_CONFIGURED_PINS];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_SetupGpioPin
* Sync/Async: Synchronous
Service ID[hex]: 0x00
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/



/**
 * @fn void Port_SetupGpioPin(const Port_ConfigType *ConfigPtr)
 * @brief Function to Setup the GPIO pin configuration.
 *
 * This function initializes and configures a GPIO pin as per the provided
 * configuration. It sets up the pin as a Digital GPIO pin, determines the
 * pin direction (input/output), assigns an initial value for the output pin,
 * and configures internal resistors for input pins.
 *
 * @param[in] ConfigPtr Pointer to post-build configuration data.
 * 
 * @details 
 * The function performs the following operations:
 * - Checks for a valid configuration pointer.
 * - Iterates through all configured pins and sets their properties:
 *   - Enables the clock for the required port.
 *   - Sets the pin as a digital GPIO or analog pin.
 *   - Configures the pin's direction and internal resistor type.
 *   - Provides an initial output value for the pin.
 *
 * Reentrancy: Reentrant
 * 
 * Sync/Async: Synchronous
 * 
 * Service ID: 0x00
 * 
 * Errors:
 * - Reports an error if the configuration pointer is NULL.
 * 
 * @return None
 * 
 * @code
 */

void Port_Init(const Port_ConfigType *ConfigPtr);

/** @endcode
 * 
 * 
 */

/************************************************************************************
 * Service Name: Port_SetPinDirection
 * Sync/Async: Synchronous
 * Service ID[hex]: 0x01
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number
 *                 Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin direction
 * ************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/**
 * @fn void Port_SetPinDirection(Port_PinType Pin, Port_PinDirection Direction)
 * @brief
 * 
 * this function sets the direction of the port pin.
 * 
 * Reentrancy: reentrant
 * 
 * Sync/Async: Synchronous
 * 
 * Service ID: 0x01
 * 
 * Errors:
 * - Reports an error if the module is not initialized.
 * - Reports an error if the pin ID is invalid.
 * - Reports an error if the pin direction is unchangeable.
 * 
 * @param[in] Pin - Port Pin ID number
 * 
 * @param[in] Direction - Port Pin Direction
 * 
 * @return void
 * 
 *
 */
///@code
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirection Direction);
/**
 * @endcode
 * 
 */
#endif

/************************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Sync/Async: Synchronous
 * Service ID[hex]: 0x02
 * Reentrancy: reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Refresh the port direction
 * ************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/**
 * @fn void Port_RefreshPortDirection(void)
 * @brief 
 * 
 * this function refreshes the port direction.
 * 
 * Reentrancy: reentrant
 * 
 * Sync/Async: Synchronous
 * 
 * Service ID: 0x02
 * 
 * Errors:
 * - Reports an error if the module is not initialized.
 * 
 * @param[in] None
 * 
 * @param[inout] None
 * 
 * @param[out] None
 * 
 * 
 * 
 * @return * void 
 * 
 */

///@code

void Port_RefreshPortDirection(void);
/**
 * @endcode
 * 
 */
#endif

/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Sync/Async: Synchronous
 * Service ID[hex]: 0x03
 * Reentrancy: non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 * ************************************************************************************/

#if (PORT_VERSION_INFO_API == STD_ON)
/**
 * @fn void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
 * @brief 
 * 
 * this function gets the version information of the module.
 * 
 * Reentrancy: non reentrant
 * 
 * Sync/Async: Synchronous
 * 
 * Service ID: 0x03
 * 
 * Errors:
 * - Reports an error if the versioninfo pointer is NULL.
 * 
 * @param[in] None
 * 
 * @param[inout] None
 * 
 * @param[out] versioninfo - Pointer to where to store the version information of this module.
 * 
 * @return void
 * 


 */
///@code
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo);
/**
 * @endcode
 * 
 */
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Service ID[hex]: 0x04
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number
 *                 Mode - New Port Pin mode to be set on port pin.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin mode
 * ************************************************************************************/

/**
 * @fn void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
 * @brief
 * 
 * this function sets the mode of the port pin.
 * 
 * Reentrancy: reentrant
 * 
 * Sync/Async: Synchronous
 * 
 * Service ID: 0x04
 * 
 * Errors:
 * - Reports an error if the module is not initialized.
 * - Reports an error if the pin ID is invalid.
 * - Reports an error if the pin mode is unchangeable.
 * 
 * @param[in] Pin - Port Pin ID number
 * 
 * @param[in] Mode - New Port Pin mode to be set on port pin.
 * 
 * @return void
 */
///@code
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
/**
 * @endcode
 * 
 */


extern const Port_ConfigType Port_Configuration;


#endif /* PORT_H */
