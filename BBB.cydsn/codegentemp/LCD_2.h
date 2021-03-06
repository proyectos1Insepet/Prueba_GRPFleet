/*******************************************************************************
* File Name: LCD_2.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_LCD_2_H)
#define CY_UART_LCD_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define LCD_2_RX_ENABLED                     (1u)
#define LCD_2_TX_ENABLED                     (1u)
#define LCD_2_HD_ENABLED                     (0u)
#define LCD_2_RX_INTERRUPT_ENABLED           (1u)
#define LCD_2_TX_INTERRUPT_ENABLED           (0u)
#define LCD_2_INTERNAL_CLOCK_USED            (1u)
#define LCD_2_RXHW_ADDRESS_ENABLED           (0u)
#define LCD_2_OVER_SAMPLE_COUNT              (8u)
#define LCD_2_PARITY_TYPE                    (0u)
#define LCD_2_PARITY_TYPE_SW                 (0u)
#define LCD_2_BREAK_DETECT                   (0u)
#define LCD_2_BREAK_BITS_TX                  (13u)
#define LCD_2_BREAK_BITS_RX                  (13u)
#define LCD_2_TXCLKGEN_DP                    (1u)
#define LCD_2_USE23POLLING                   (1u)
#define LCD_2_FLOW_CONTROL                   (0u)
#define LCD_2_CLK_FREQ                       (0u)
#define LCD_2_TX_BUFFER_SIZE                 (4u)
#define LCD_2_RX_BUFFER_SIZE                 (200u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define LCD_2_CONTROL_REG_REMOVED            (0u)
#else
    #define LCD_2_CONTROL_REG_REMOVED            (1u)
#endif /* End LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct LCD_2_backupStruct_
{
    uint8 enableState;

    #if(LCD_2_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End LCD_2_CONTROL_REG_REMOVED */

} LCD_2_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void LCD_2_Start(void) ;
void LCD_2_Stop(void) ;
uint8 LCD_2_ReadControlRegister(void) ;
void LCD_2_WriteControlRegister(uint8 control) ;

void LCD_2_Init(void) ;
void LCD_2_Enable(void) ;
void LCD_2_SaveConfig(void) ;
void LCD_2_RestoreConfig(void) ;
void LCD_2_Sleep(void) ;
void LCD_2_Wakeup(void) ;

/* Only if RX is enabled */
#if( (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) )

    #if (LCD_2_RX_INTERRUPT_ENABLED)
        #define LCD_2_EnableRxInt()  CyIntEnable (LCD_2_RX_VECT_NUM)
        #define LCD_2_DisableRxInt() CyIntDisable(LCD_2_RX_VECT_NUM)
        CY_ISR_PROTO(LCD_2_RXISR);
    #endif /* LCD_2_RX_INTERRUPT_ENABLED */

    void LCD_2_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void LCD_2_SetRxAddress1(uint8 address) ;
    void LCD_2_SetRxAddress2(uint8 address) ;

    void  LCD_2_SetRxInterruptMode(uint8 intSrc) ;
    uint8 LCD_2_ReadRxData(void) ;
    uint8 LCD_2_ReadRxStatus(void) ;
    uint8 LCD_2_GetChar(void) ;
    uint16 LCD_2_GetByte(void) ;
    uint8 LCD_2_GetRxBufferSize(void)
                                                            ;
    void LCD_2_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define LCD_2_GetRxInterruptSource   LCD_2_ReadRxStatus

#endif /* End (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) */

/* Only if TX is enabled */
#if(LCD_2_TX_ENABLED || LCD_2_HD_ENABLED)

    #if(LCD_2_TX_INTERRUPT_ENABLED)
        #define LCD_2_EnableTxInt()  CyIntEnable (LCD_2_TX_VECT_NUM)
        #define LCD_2_DisableTxInt() CyIntDisable(LCD_2_TX_VECT_NUM)
        #define LCD_2_SetPendingTxInt() CyIntSetPending(LCD_2_TX_VECT_NUM)
        #define LCD_2_ClearPendingTxInt() CyIntClearPending(LCD_2_TX_VECT_NUM)
        CY_ISR_PROTO(LCD_2_TXISR);
    #endif /* LCD_2_TX_INTERRUPT_ENABLED */

    void LCD_2_SetTxInterruptMode(uint8 intSrc) ;
    void LCD_2_WriteTxData(uint8 txDataByte) ;
    uint8 LCD_2_ReadTxStatus(void) ;
    void LCD_2_PutChar(uint8 txDataByte) ;
    void LCD_2_PutString(const char8 string[]) ;
    void LCD_2_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void LCD_2_PutCRLF(uint8 txDataByte) ;
    void LCD_2_ClearTxBuffer(void) ;
    void LCD_2_SetTxAddressMode(uint8 addressMode) ;
    void LCD_2_SendBreak(uint8 retMode) ;
    uint8 LCD_2_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define LCD_2_PutStringConst         LCD_2_PutString
    #define LCD_2_PutArrayConst          LCD_2_PutArray
    #define LCD_2_GetTxInterruptSource   LCD_2_ReadTxStatus

#endif /* End LCD_2_TX_ENABLED || LCD_2_HD_ENABLED */

#if(LCD_2_HD_ENABLED)
    void LCD_2_LoadRxConfig(void) ;
    void LCD_2_LoadTxConfig(void) ;
#endif /* End LCD_2_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_2) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    LCD_2_CyBtldrCommStart(void) CYSMALL ;
    void    LCD_2_CyBtldrCommStop(void) CYSMALL ;
    void    LCD_2_CyBtldrCommReset(void) CYSMALL ;
    cystatus LCD_2_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus LCD_2_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_2)
        #define CyBtldrCommStart    LCD_2_CyBtldrCommStart
        #define CyBtldrCommStop     LCD_2_CyBtldrCommStop
        #define CyBtldrCommReset    LCD_2_CyBtldrCommReset
        #define CyBtldrCommWrite    LCD_2_CyBtldrCommWrite
        #define CyBtldrCommRead     LCD_2_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_LCD_2) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define LCD_2_BYTE2BYTE_TIME_OUT (25u)
    #define LCD_2_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define LCD_2_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define LCD_2_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define LCD_2_SET_SPACE      (0x00u)
#define LCD_2_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (LCD_2_TX_ENABLED) || (LCD_2_HD_ENABLED) )
    #if(LCD_2_TX_INTERRUPT_ENABLED)
        #define LCD_2_TX_VECT_NUM            (uint8)LCD_2_TXInternalInterrupt__INTC_NUMBER
        #define LCD_2_TX_PRIOR_NUM           (uint8)LCD_2_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* LCD_2_TX_INTERRUPT_ENABLED */

    #define LCD_2_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define LCD_2_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define LCD_2_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(LCD_2_TX_ENABLED)
        #define LCD_2_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (LCD_2_HD_ENABLED) */
        #define LCD_2_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (LCD_2_TX_ENABLED) */

    #define LCD_2_TX_STS_COMPLETE            (uint8)(0x01u << LCD_2_TX_STS_COMPLETE_SHIFT)
    #define LCD_2_TX_STS_FIFO_EMPTY          (uint8)(0x01u << LCD_2_TX_STS_FIFO_EMPTY_SHIFT)
    #define LCD_2_TX_STS_FIFO_FULL           (uint8)(0x01u << LCD_2_TX_STS_FIFO_FULL_SHIFT)
    #define LCD_2_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << LCD_2_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (LCD_2_TX_ENABLED) || (LCD_2_HD_ENABLED)*/

#if( (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) )
    #if(LCD_2_RX_INTERRUPT_ENABLED)
        #define LCD_2_RX_VECT_NUM            (uint8)LCD_2_RXInternalInterrupt__INTC_NUMBER
        #define LCD_2_RX_PRIOR_NUM           (uint8)LCD_2_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* LCD_2_RX_INTERRUPT_ENABLED */
    #define LCD_2_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define LCD_2_RX_STS_BREAK_SHIFT             (0x01u)
    #define LCD_2_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define LCD_2_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define LCD_2_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define LCD_2_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define LCD_2_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define LCD_2_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define LCD_2_RX_STS_MRKSPC           (uint8)(0x01u << LCD_2_RX_STS_MRKSPC_SHIFT)
    #define LCD_2_RX_STS_BREAK            (uint8)(0x01u << LCD_2_RX_STS_BREAK_SHIFT)
    #define LCD_2_RX_STS_PAR_ERROR        (uint8)(0x01u << LCD_2_RX_STS_PAR_ERROR_SHIFT)
    #define LCD_2_RX_STS_STOP_ERROR       (uint8)(0x01u << LCD_2_RX_STS_STOP_ERROR_SHIFT)
    #define LCD_2_RX_STS_OVERRUN          (uint8)(0x01u << LCD_2_RX_STS_OVERRUN_SHIFT)
    #define LCD_2_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << LCD_2_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define LCD_2_RX_STS_ADDR_MATCH       (uint8)(0x01u << LCD_2_RX_STS_ADDR_MATCH_SHIFT)
    #define LCD_2_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << LCD_2_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define LCD_2_RX_HW_MASK                     (0x7Fu)
#endif /* End (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) */

/* Control Register definitions */
#define LCD_2_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define LCD_2_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define LCD_2_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define LCD_2_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define LCD_2_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define LCD_2_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define LCD_2_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define LCD_2_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define LCD_2_CTRL_HD_SEND               (uint8)(0x01u << LCD_2_CTRL_HD_SEND_SHIFT)
#define LCD_2_CTRL_HD_SEND_BREAK         (uint8)(0x01u << LCD_2_CTRL_HD_SEND_BREAK_SHIFT)
#define LCD_2_CTRL_MARK                  (uint8)(0x01u << LCD_2_CTRL_MARK_SHIFT)
#define LCD_2_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << LCD_2_CTRL_PARITY_TYPE0_SHIFT)
#define LCD_2_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << LCD_2_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define LCD_2_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define LCD_2_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define LCD_2_SEND_BREAK                         (0x00u)
#define LCD_2_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define LCD_2_REINIT                             (0x02u)
#define LCD_2_SEND_WAIT_REINIT                   (0x03u)

#define LCD_2_OVER_SAMPLE_8                      (8u)
#define LCD_2_OVER_SAMPLE_16                     (16u)

#define LCD_2_BIT_CENTER                         (LCD_2_OVER_SAMPLE_COUNT - 2u)

#define LCD_2_FIFO_LENGTH                        (4u)
#define LCD_2_NUMBER_OF_START_BIT                (1u)
#define LCD_2_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define LCD_2_TXBITCTR_BREAKBITS8X   ((LCD_2_BREAK_BITS_TX * LCD_2_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define LCD_2_TXBITCTR_BREAKBITS ((LCD_2_BREAK_BITS_TX * LCD_2_OVER_SAMPLE_COUNT) - 1u)

#define LCD_2_HALF_BIT_COUNT   \
                            (((LCD_2_OVER_SAMPLE_COUNT / 2u) + (LCD_2_USE23POLLING * 1u)) - 2u)
#if (LCD_2_OVER_SAMPLE_COUNT == LCD_2_OVER_SAMPLE_8)
    #define LCD_2_HD_TXBITCTR_INIT   (((LCD_2_BREAK_BITS_TX + \
                            LCD_2_NUMBER_OF_START_BIT) * LCD_2_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define LCD_2_RXBITCTR_INIT  ((((LCD_2_BREAK_BITS_RX + LCD_2_NUMBER_OF_START_BIT) \
                            * LCD_2_OVER_SAMPLE_COUNT) + LCD_2_HALF_BIT_COUNT) - 1u)

#else /* LCD_2_OVER_SAMPLE_COUNT == LCD_2_OVER_SAMPLE_16 */
    #define LCD_2_HD_TXBITCTR_INIT   ((8u * LCD_2_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define LCD_2_RXBITCTR_INIT      (((7u * LCD_2_OVER_SAMPLE_COUNT) - 1u) + \
                                                      LCD_2_HALF_BIT_COUNT)
#endif /* End LCD_2_OVER_SAMPLE_COUNT */

#define LCD_2_HD_RXBITCTR_INIT                   LCD_2_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 LCD_2_initVar;
#if (LCD_2_TX_INTERRUPT_ENABLED && LCD_2_TX_ENABLED)
    extern volatile uint8 LCD_2_txBuffer[LCD_2_TX_BUFFER_SIZE];
    extern volatile uint8 LCD_2_txBufferRead;
    extern uint8 LCD_2_txBufferWrite;
#endif /* (LCD_2_TX_INTERRUPT_ENABLED && LCD_2_TX_ENABLED) */
#if (LCD_2_RX_INTERRUPT_ENABLED && (LCD_2_RX_ENABLED || LCD_2_HD_ENABLED))
    extern uint8 LCD_2_errorStatus;
    extern volatile uint8 LCD_2_rxBuffer[LCD_2_RX_BUFFER_SIZE];
    extern volatile uint8 LCD_2_rxBufferRead;
    extern volatile uint8 LCD_2_rxBufferWrite;
    extern volatile uint8 LCD_2_rxBufferLoopDetect;
    extern volatile uint8 LCD_2_rxBufferOverflow;
    #if (LCD_2_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 LCD_2_rxAddressMode;
        extern volatile uint8 LCD_2_rxAddressDetected;
    #endif /* (LCD_2_RXHW_ADDRESS_ENABLED) */
#endif /* (LCD_2_RX_INTERRUPT_ENABLED && (LCD_2_RX_ENABLED || LCD_2_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define LCD_2__B_UART__AM_SW_BYTE_BYTE 1
#define LCD_2__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define LCD_2__B_UART__AM_HW_BYTE_BY_BYTE 3
#define LCD_2__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define LCD_2__B_UART__AM_NONE 0

#define LCD_2__B_UART__NONE_REVB 0
#define LCD_2__B_UART__EVEN_REVB 1
#define LCD_2__B_UART__ODD_REVB 2
#define LCD_2__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define LCD_2_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define LCD_2_NUMBER_OF_STOP_BITS    (1u)

#if (LCD_2_RXHW_ADDRESS_ENABLED)
    #define LCD_2_RX_ADDRESS_MODE    (0u)
    #define LCD_2_RX_HW_ADDRESS1     (0u)
    #define LCD_2_RX_HW_ADDRESS2     (0u)
#endif /* (LCD_2_RXHW_ADDRESS_ENABLED) */

#define LCD_2_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << LCD_2_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << LCD_2_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << LCD_2_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << LCD_2_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << LCD_2_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << LCD_2_RX_STS_BREAK_SHIFT) \
                                        | (0 << LCD_2_RX_STS_OVERRUN_SHIFT))

#define LCD_2_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << LCD_2_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << LCD_2_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << LCD_2_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << LCD_2_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define LCD_2_CONTROL_REG \
                            (* (reg8 *) LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define LCD_2_CONTROL_PTR \
                            (  (reg8 *) LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(LCD_2_TX_ENABLED)
    #define LCD_2_TXDATA_REG          (* (reg8 *) LCD_2_BUART_sTX_TxShifter_u0__F0_REG)
    #define LCD_2_TXDATA_PTR          (  (reg8 *) LCD_2_BUART_sTX_TxShifter_u0__F0_REG)
    #define LCD_2_TXDATA_AUX_CTL_REG  (* (reg8 *) LCD_2_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define LCD_2_TXDATA_AUX_CTL_PTR  (  (reg8 *) LCD_2_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define LCD_2_TXSTATUS_REG        (* (reg8 *) LCD_2_BUART_sTX_TxSts__STATUS_REG)
    #define LCD_2_TXSTATUS_PTR        (  (reg8 *) LCD_2_BUART_sTX_TxSts__STATUS_REG)
    #define LCD_2_TXSTATUS_MASK_REG   (* (reg8 *) LCD_2_BUART_sTX_TxSts__MASK_REG)
    #define LCD_2_TXSTATUS_MASK_PTR   (  (reg8 *) LCD_2_BUART_sTX_TxSts__MASK_REG)
    #define LCD_2_TXSTATUS_ACTL_REG   (* (reg8 *) LCD_2_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define LCD_2_TXSTATUS_ACTL_PTR   (  (reg8 *) LCD_2_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(LCD_2_TXCLKGEN_DP)
        #define LCD_2_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define LCD_2_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define LCD_2_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define LCD_2_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define LCD_2_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define LCD_2_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define LCD_2_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define LCD_2_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define LCD_2_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define LCD_2_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) LCD_2_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* LCD_2_TXCLKGEN_DP */

#endif /* End LCD_2_TX_ENABLED */

#if(LCD_2_HD_ENABLED)

    #define LCD_2_TXDATA_REG             (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__F1_REG )
    #define LCD_2_TXDATA_PTR             (  (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__F1_REG )
    #define LCD_2_TXDATA_AUX_CTL_REG     (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define LCD_2_TXDATA_AUX_CTL_PTR     (  (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define LCD_2_TXSTATUS_REG           (* (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_REG )
    #define LCD_2_TXSTATUS_PTR           (  (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_REG )
    #define LCD_2_TXSTATUS_MASK_REG      (* (reg8 *) LCD_2_BUART_sRX_RxSts__MASK_REG )
    #define LCD_2_TXSTATUS_MASK_PTR      (  (reg8 *) LCD_2_BUART_sRX_RxSts__MASK_REG )
    #define LCD_2_TXSTATUS_ACTL_REG      (* (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define LCD_2_TXSTATUS_ACTL_PTR      (  (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End LCD_2_HD_ENABLED */

#if( (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) )
    #define LCD_2_RXDATA_REG             (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__F0_REG )
    #define LCD_2_RXDATA_PTR             (  (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__F0_REG )
    #define LCD_2_RXADDRESS1_REG         (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__D0_REG )
    #define LCD_2_RXADDRESS1_PTR         (  (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__D0_REG )
    #define LCD_2_RXADDRESS2_REG         (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__D1_REG )
    #define LCD_2_RXADDRESS2_PTR         (  (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__D1_REG )
    #define LCD_2_RXDATA_AUX_CTL_REG     (* (reg8 *) LCD_2_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define LCD_2_RXBITCTR_PERIOD_REG    (* (reg8 *) LCD_2_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define LCD_2_RXBITCTR_PERIOD_PTR    (  (reg8 *) LCD_2_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define LCD_2_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) LCD_2_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define LCD_2_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) LCD_2_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define LCD_2_RXBITCTR_COUNTER_REG   (* (reg8 *) LCD_2_BUART_sRX_RxBitCounter__COUNT_REG )
    #define LCD_2_RXBITCTR_COUNTER_PTR   (  (reg8 *) LCD_2_BUART_sRX_RxBitCounter__COUNT_REG )

    #define LCD_2_RXSTATUS_REG           (* (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_REG )
    #define LCD_2_RXSTATUS_PTR           (  (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_REG )
    #define LCD_2_RXSTATUS_MASK_REG      (* (reg8 *) LCD_2_BUART_sRX_RxSts__MASK_REG )
    #define LCD_2_RXSTATUS_MASK_PTR      (  (reg8 *) LCD_2_BUART_sRX_RxSts__MASK_REG )
    #define LCD_2_RXSTATUS_ACTL_REG      (* (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define LCD_2_RXSTATUS_ACTL_PTR      (  (reg8 *) LCD_2_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) */

#if(LCD_2_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define LCD_2_INTCLOCK_CLKEN_REG     (* (reg8 *) LCD_2_IntClock__PM_ACT_CFG)
    #define LCD_2_INTCLOCK_CLKEN_PTR     (  (reg8 *) LCD_2_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define LCD_2_INTCLOCK_CLKEN_MASK    LCD_2_IntClock__PM_ACT_MSK
#endif /* End LCD_2_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(LCD_2_TX_ENABLED)
    #define LCD_2_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End LCD_2_TX_ENABLED */

#if(LCD_2_HD_ENABLED)
    #define LCD_2_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End LCD_2_HD_ENABLED */

#if( (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) )
    #define LCD_2_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define LCD_2_WAIT_1_MS      LCD_2_BL_CHK_DELAY_MS   

#define LCD_2_TXBUFFERSIZE   LCD_2_TX_BUFFER_SIZE
#define LCD_2_RXBUFFERSIZE   LCD_2_RX_BUFFER_SIZE

#if (LCD_2_RXHW_ADDRESS_ENABLED)
    #define LCD_2_RXADDRESSMODE  LCD_2_RX_ADDRESS_MODE
    #define LCD_2_RXHWADDRESS1   LCD_2_RX_HW_ADDRESS1
    #define LCD_2_RXHWADDRESS2   LCD_2_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define LCD_2_RXAddressMode  LCD_2_RXADDRESSMODE
#endif /* (LCD_2_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define LCD_2_initvar                    LCD_2_initVar

#define LCD_2_RX_Enabled                 LCD_2_RX_ENABLED
#define LCD_2_TX_Enabled                 LCD_2_TX_ENABLED
#define LCD_2_HD_Enabled                 LCD_2_HD_ENABLED
#define LCD_2_RX_IntInterruptEnabled     LCD_2_RX_INTERRUPT_ENABLED
#define LCD_2_TX_IntInterruptEnabled     LCD_2_TX_INTERRUPT_ENABLED
#define LCD_2_InternalClockUsed          LCD_2_INTERNAL_CLOCK_USED
#define LCD_2_RXHW_Address_Enabled       LCD_2_RXHW_ADDRESS_ENABLED
#define LCD_2_OverSampleCount            LCD_2_OVER_SAMPLE_COUNT
#define LCD_2_ParityType                 LCD_2_PARITY_TYPE

#if( LCD_2_TX_ENABLED && (LCD_2_TXBUFFERSIZE > LCD_2_FIFO_LENGTH))
    #define LCD_2_TXBUFFER               LCD_2_txBuffer
    #define LCD_2_TXBUFFERREAD           LCD_2_txBufferRead
    #define LCD_2_TXBUFFERWRITE          LCD_2_txBufferWrite
#endif /* End LCD_2_TX_ENABLED */
#if( ( LCD_2_RX_ENABLED || LCD_2_HD_ENABLED ) && \
     (LCD_2_RXBUFFERSIZE > LCD_2_FIFO_LENGTH) )
    #define LCD_2_RXBUFFER               LCD_2_rxBuffer
    #define LCD_2_RXBUFFERREAD           LCD_2_rxBufferRead
    #define LCD_2_RXBUFFERWRITE          LCD_2_rxBufferWrite
    #define LCD_2_RXBUFFERLOOPDETECT     LCD_2_rxBufferLoopDetect
    #define LCD_2_RXBUFFER_OVERFLOW      LCD_2_rxBufferOverflow
#endif /* End LCD_2_RX_ENABLED */

#ifdef LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define LCD_2_CONTROL                LCD_2_CONTROL_REG
#endif /* End LCD_2_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(LCD_2_TX_ENABLED)
    #define LCD_2_TXDATA                 LCD_2_TXDATA_REG
    #define LCD_2_TXSTATUS               LCD_2_TXSTATUS_REG
    #define LCD_2_TXSTATUS_MASK          LCD_2_TXSTATUS_MASK_REG
    #define LCD_2_TXSTATUS_ACTL          LCD_2_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(LCD_2_TXCLKGEN_DP)
        #define LCD_2_TXBITCLKGEN_CTR        LCD_2_TXBITCLKGEN_CTR_REG
        #define LCD_2_TXBITCLKTX_COMPLETE    LCD_2_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define LCD_2_TXBITCTR_PERIOD        LCD_2_TXBITCTR_PERIOD_REG
        #define LCD_2_TXBITCTR_CONTROL       LCD_2_TXBITCTR_CONTROL_REG
        #define LCD_2_TXBITCTR_COUNTER       LCD_2_TXBITCTR_COUNTER_REG
    #endif /* LCD_2_TXCLKGEN_DP */
#endif /* End LCD_2_TX_ENABLED */

#if(LCD_2_HD_ENABLED)
    #define LCD_2_TXDATA                 LCD_2_TXDATA_REG
    #define LCD_2_TXSTATUS               LCD_2_TXSTATUS_REG
    #define LCD_2_TXSTATUS_MASK          LCD_2_TXSTATUS_MASK_REG
    #define LCD_2_TXSTATUS_ACTL          LCD_2_TXSTATUS_ACTL_REG
#endif /* End LCD_2_HD_ENABLED */

#if( (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) )
    #define LCD_2_RXDATA                 LCD_2_RXDATA_REG
    #define LCD_2_RXADDRESS1             LCD_2_RXADDRESS1_REG
    #define LCD_2_RXADDRESS2             LCD_2_RXADDRESS2_REG
    #define LCD_2_RXBITCTR_PERIOD        LCD_2_RXBITCTR_PERIOD_REG
    #define LCD_2_RXBITCTR_CONTROL       LCD_2_RXBITCTR_CONTROL_REG
    #define LCD_2_RXBITCTR_COUNTER       LCD_2_RXBITCTR_COUNTER_REG
    #define LCD_2_RXSTATUS               LCD_2_RXSTATUS_REG
    #define LCD_2_RXSTATUS_MASK          LCD_2_RXSTATUS_MASK_REG
    #define LCD_2_RXSTATUS_ACTL          LCD_2_RXSTATUS_ACTL_REG
#endif /* End  (LCD_2_RX_ENABLED) || (LCD_2_HD_ENABLED) */

#if(LCD_2_INTERNAL_CLOCK_USED)
    #define LCD_2_INTCLOCK_CLKEN         LCD_2_INTCLOCK_CLKEN_REG
#endif /* End LCD_2_INTERNAL_CLOCK_USED */

#define LCD_2_WAIT_FOR_COMLETE_REINIT    LCD_2_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_LCD_2_H */


/* [] END OF FILE */
