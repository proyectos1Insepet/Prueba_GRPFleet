/*******************************************************************************
* File Name: Impresora_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Impresora.h"


/***************************************
* Local data allocation
***************************************/

static Impresora_BACKUP_STRUCT  Impresora_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Impresora_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the Impresora_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Impresora_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Impresora_SaveConfig(void)
{
    #if(Impresora_CONTROL_REG_REMOVED == 0u)
        Impresora_backup.cr = Impresora_CONTROL_REG;
    #endif /* End Impresora_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Impresora_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Impresora_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling Impresora_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void Impresora_RestoreConfig(void)
{
    #if(Impresora_CONTROL_REG_REMOVED == 0u)
        Impresora_CONTROL_REG = Impresora_backup.cr;
    #endif /* End Impresora_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Impresora_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Impresora_Sleep() API saves the current component state. Then it
*  calls the Impresora_Stop() function and calls 
*  Impresora_SaveConfig() to save the hardware configuration.
*  Call the Impresora_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Impresora_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Impresora_Sleep(void)
{
    #if(Impresora_RX_ENABLED || Impresora_HD_ENABLED)
        if((Impresora_RXSTATUS_ACTL_REG  & Impresora_INT_ENABLE) != 0u)
        {
            Impresora_backup.enableState = 1u;
        }
        else
        {
            Impresora_backup.enableState = 0u;
        }
    #else
        if((Impresora_TXSTATUS_ACTL_REG  & Impresora_INT_ENABLE) !=0u)
        {
            Impresora_backup.enableState = 1u;
        }
        else
        {
            Impresora_backup.enableState = 0u;
        }
    #endif /* End Impresora_RX_ENABLED || Impresora_HD_ENABLED*/

    Impresora_Stop();
    Impresora_SaveConfig();
}


/*******************************************************************************
* Function Name: Impresora_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Impresora_Sleep() was called. The Impresora_Wakeup() function
*  calls the Impresora_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Impresora_Sleep() function was called, the Impresora_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Impresora_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Impresora_Wakeup(void)
{
    Impresora_RestoreConfig();
    #if( (Impresora_RX_ENABLED) || (Impresora_HD_ENABLED) )
        Impresora_ClearRxBuffer();
    #endif /* End (Impresora_RX_ENABLED) || (Impresora_HD_ENABLED) */
    #if(Impresora_TX_ENABLED || Impresora_HD_ENABLED)
        Impresora_ClearTxBuffer();
    #endif /* End Impresora_TX_ENABLED || Impresora_HD_ENABLED */

    if(Impresora_backup.enableState != 0u)
    {
        Impresora_Enable();
    }
}


/* [] END OF FILE */
