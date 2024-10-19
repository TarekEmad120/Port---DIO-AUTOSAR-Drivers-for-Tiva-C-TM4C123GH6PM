/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Tarek Emad
 ******************************************************************************/
/**
 * @file Port.c
 * @brief Source file for TM4C123GH6PM Microcontroller - Port Driver.
 * @date 21/8/2024
 * @version 1.0
 * @see Port.h
 * @see Port_Cfg.h
 * @see Det.h
 * @see Std_Types.h
 *
 */

#include "Port.h"

#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION) || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION) || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif


/* Global variable to hold the Port status */
static uint8 Port_Status = PORT_NOT_INITIALIZED;

/*pointer to the configuration structure*/
STATIC const Port_ConfigType *Port_Configurs = NULL_PTR;

/************************************************************************************
 * Service Name: Port_SetupGpioPin
 * Sync/Async: Synchronous
 * service ID[hex]: 0x00
 * Reentrancy: reentrant
 * Parameters (in): ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Setup the pin configuration:
 *              - Setup the pin as Digital GPIO pin
 *              - Setup the direction of the GPIO pin
 *              - Provide initial value for o/p pin
 *              - Setup the internal resistor for i/p pin
 ************************************************************************************/
/**
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
 * 
 */
///@code
void Port_Init(const Port_ConfigType *ConfigPtr)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the input configuration pointer is not a NULL_PTR */
    if (ConfigPtr == NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
    {
        /* No action required */
    }
#endif
    Port_Status = PORT_INITIALIZED;
    Port_Configurs = ConfigPtr;
    uint8 Channel=0;
    boolean error = FALSE;



    while (Channel<PORT_CONFIGURED_PINS)
    {
        /* Check if the pin is configured as changeable */

        volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        switch (ConfigPtr->Channels[Channel].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        default:
            break;
        }

        if (TRUE == error)
        {
            /* No action required */
        }
        else
        {
            SYSCTL_RCGCGPIO_REG |= (1 << ConfigPtr->Channels[Channel].port_num); /* Enable clock for the required port */
            while ((SYSCTL_PRGPIO_REG & (1 << ConfigPtr->Channels[Channel].port_num)) == 0); /* wait until clock is setlled */
        }

        if (((Port_Configurs->Channels[Channel].port_num == 3) && (Port_Configurs->Channels[Channel].pin_num == 7)) ||
        ((Port_Configurs->Channels[Channel].port_num == 5) && (Port_Configurs->Channels[Channel].pin_num == 0)))
        {
            if (TRUE == error)
            {
                /* No action required */
            }
            else
            {
                /*
                    * Unlock the GPIOCR register by providing the correct value
                    * for each port before making any changes
                */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;

                /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num);
            }
        }
        else if ((Port_Configurs->Channels[Channel].port_num == 2) && (Port_Configurs->Channels[Channel].pin_num <= 3))
        {
            if (TRUE == error)
            {
                /* No action required */
            }
            else
            {
                /* Do Nothing
                 * This is jtag pins */
                continue;
            }
        }
        else
        {
            /* Do Nothing */
        }

        if (Port_Configurs->Channels[Channel].initial_mode == PORT_PIN_MODE_DIO)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Channel].pin_num * 4)); /* Clear the PMCx bits for this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        }
        else
        {
            /* Do Nothing */
        }

        if (Port_Configurs->Channels[Channel].initial_mode==PORT_PIN_MODE_ADC)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this pin */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Channel].pin_num * 4)); /* Clear the PMCx bits for this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        }
        else
        {
            /* Do Nothing */
        }

        if (((Port_Configurs->Channels[Channel].initial_mode>=PORT_PIN_MODE_ALT1)&&(Port_Configurs->Channels[Channel].initial_mode<=PORT_PIN_MODE_ALT9))||
         (Port_Configurs->Channels[Channel].initial_mode==PORT_PIN_MODE_ALT14) || (Port_Configurs->Channels[Channel].initial_mode==PORT_PIN_MODE_ALT15))
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Channel].pin_num * 4)); /* Clear the PMCx bits for this pin */
        }
        else
        {
            /* Do Nothing */
        }

        if (Port_Configurs->Channels[Channel].direction==OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }

        if (Port_Configurs->Channels[Channel].resistor==PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIOPUR register to enable the internal pull-up pin */
        }
        else{
            /* Do Nothing */
        }


        if (Port_Configurs->Channels[Channel].resistor==PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIOPDR register to enable the internal pull-down pin */
        }
        else
        {
            /* Do Nothing */
        }


        if (Port_Configurs->Channels[Channel].initial_value==STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
        Channel++;
    }
}
/**
 * @endcode
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
 ************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/** 
 * @fn void Port_SetPinDirection(Port_PinType Pin, Port_PinDirection Direction);
 * @brief Function to Set the port pin direction.
 * 
 * This function sets the direction of the specified port pin as input or output.
 * 
 * @param[in] Pin - Port Pin ID number
 * 
 * @param[in] Direction - Port Pin Direction
 * 
 * @return void
 * 
 * 
 * 
*/
///@code
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirection Direction)
{
    boolean error = FALSE;
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    if (Port_Status == PORT_NOT_INITIALIZED)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (Pin >= PORT_CONFIGURED_PINS)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (Port_Configurs->Channels[Pin].pin_dir_changeable == STD_OFF)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
#endif

        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (TRUE == error)
    {
        /* No action required */
    }
    else
    {
        switch (Port_Configurs->Channels[Pin].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        default:
            break;
        }

        //checking for jtag pins
        if ((Port_Configurs->Channels[Pin].port_num == 2) && (Port_Configurs->Channels[Pin].pin_num <= 3))
        {
            
             /* This is jtag pins */
            return;
        }
        else
        {
            /* Do Nothing */
        }

        if (Direction == OUTPUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
    }

}

///@endcode

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
 ************************************************************************************/

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

///@code
void Port_RefreshPortDirection(void)
{
    boolean error = FALSE;
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    uint8 Channel;
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (TRUE == error)
    {
        /* No action required */
    }
    else
    {
        for (Channel = 0; Channel <(uint8)PORT_CONFIGURED_PINS; Channel++)
        {
            switch (Port_Configurs->Channels[Channel].port_num)
            {
            case 0:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                break;
            case 1:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                break;
            case 2:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                break;
            case 3:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                break;
            case 4:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                break;
            case 5:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                break;
            default:
                break;
            }
            //checking for jtag pins
            if ((Port_Configurs->Channels[Channel].port_num == 2) && (Port_Configurs->Channels[Channel].pin_num <= 3))
            {
                /* This is jtag pins */
                continue;
            }
            else
            {
                /* Do Nothing */
            }

            if (Port_Configurs->Channels[Channel].direction == OUTPUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Configurs->Channels[Channel].pin_num); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            }
        }
    }

}
///@endcode
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
 ************************************************************************************/

#if (PORT_VERSION_INFO_API == STD_ON)

///@code
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
    boolean error = FALSE;

    if (versioninfo == NULL_PTR)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (TRUE == error)
    {
        /* No action required */
    }
    else
    {
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }

}
///@endcode
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Sync/Async: Synchronous
 * Service ID[hex]: 0x04
 * Reentrancy: reentrant
 * Parameters (in): Pin - Port Pin ID number
 *                 Mode - New Port Pin mode to be set on the port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Set the port pin mode
 ************************************************************************************/
///@code
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    boolean error = FALSE;
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */

    if (Port_Status == PORT_NOT_INITIALIZED)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (Pin >= PORT_CONFIGURED_PINS)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (Port_Configurs->Channels[Pin].pin_mode_changeable == STD_OFF)
    {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
#endif
        error = TRUE;
    }
    else
    {
        /* No action required */
    }

    if (TRUE == error)
    {
        /* No action required */
    }
    else
    {
        switch (Port_Configurs->Channels[Pin].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
        default:
            break;
        }

        if (Mode == PORT_PIN_MODE_ADC)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this pin */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Pin].pin_num * 4)); /* Clear the PMCx bits for this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
        }
        else
        {
            /* Do Nothing */
        }

        if (Mode == PORT_PIN_MODE_DIO)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */

            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Pin].pin_num * 4)); /* Clear the PMCx bits for this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else
        {
            /* Do Nothing */
        }

        if (((Mode >= PORT_PIN_MODE_ALT1) && (Mode <= PORT_PIN_MODE_ALT9)) || (Mode == PORT_PIN_MODE_ALT14) || (Mode == PORT_PIN_MODE_ALT15))
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Clear the corresponding bit in the GPIOAMSEL register to disable digital functionality on this pin */

            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Configurs->Channels[Pin].pin_num); /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Configurs->Channels[Pin].pin_num * 4)); /* Clear the PMCx bits for this pin */
        }
        else
        {
            /* Do Nothing */
        }
    }
}
///@endcode

