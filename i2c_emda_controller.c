//#include "i2c.h"
//#include "psc.h"
//#include "edma.h"
//#include "interrupt.h"
//#include "edma_event.h"
//#include "soc_C6748.h"
//#include "hw_psc_C6748.h"
//#include "lcdkC6748.h"
//#include "hw_types.h"
//#include "hw_edma3cc.h"
//#include "uartStdio.h"
//
//unsigned char rx_buffer = 0;
//
//static void EdmaConfigTX(unsigned int address)
//{
//    EDMA3CCPaRAMEntry paramSet;
//
//    paramSet.srcAddr    = address;
//    paramSet.destAddr   = (SOC_I2C_0_REGS + I2C_ICDXR);
//
//    /*
//    ** I2C generates one EDMA event whenever I2CXSR is empty.There is space
//    ** for only one byte of data in I2CXSR.There is no fifo.Hence per event
//    ** one bytes needs to be transfered.Thus EDMA is configured in ASYNC mode
//    ** with acount = 1, bcount = total_numbytes, ccount = 1.BSRC index should
//    ** be 1 since memory pointer needs to incremented one after every byte
//    ** transfer by EDMA.BDST index should be zero since the destination address
//    ** is in constant adrressing mode(hardware register).
//    **
//    */
//    paramSet.srcBIdx    = 0x01;
//    paramSet.srcCIdx    = 0x00;
//    paramSet.destBIdx   = 0x00;
//    paramSet.destCIdx   = 0x00;
//    paramSet.aCnt       = 0x01;
//    paramSet.bCnt       = 0x02;
//    paramSet.cCnt       = 0x01;
//    paramSet.bCntReload = 0x00;
//    paramSet.linkAddr   = 0xffff;
//    paramSet.opt        = 0;
//
//    /* Program the TCC */
//    paramSet.opt |= ((EDMA3_CHA_I2C0_TX << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);
//
//    /* Transmission complition interrupt enable */
//    paramSet.opt |= (1 << EDMA3CC_OPT_TCINTEN_SHIFT);
//
//    /* configure PaRAM Set */
//    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS,  EDMA3_CHA_I2C0_TX, &paramSet);
//
//    /* Enable the transfet */
//    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS,  EDMA3_CHA_I2C0_TX, EDMA3_TRIG_MODE_EVENT);
//}
//
//
//
//
//static void SetupEdma(void)
//{
//    volatile unsigned int evtQ = 0;
//    EDMA3CCPaRAMEntry paramSet;
//
//    /* Enabling the PSC for EDMA3CC_0.*/
//    PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_CC0, PSC_POWERDOMAIN_ALWAYS_ON,
//             PSC_MDCTL_NEXT_ENABLE);
//
//    /* Enabling the PSC for EDMA3TC_0.*/
//    PSCModuleControl(SOC_PSC_0_REGS, HW_PSC_TC0, PSC_POWERDOMAIN_ALWAYS_ON,
//             PSC_MDCTL_NEXT_ENABLE);
//
//    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA ,
//                       EDMA3_CHA_I2C0_TX , EDMA3_CHA_I2C0_TX , evtQ);
//    EDMA3RequestChannel(SOC_EDMA31CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA ,
//                       EDMA3_CHA_I2C0_RX , EDMA3_CHA_I2C0_RX , evtQ);
//
//
//    /*
//    ** Enable AINTC to handle interrupts. Also enable IRQ interrupt in ARM
//    ** processor.
//    */
//    SetupInt();
//
//    /* Intialize the Edma */
//    EDMA3Init(SOC_EDMA30CC_0_REGS, evtQ);
//
//    /* Register required edma interrupts */
//    RegisterEdma3Interrupts();
//
//    /* on i2c reset both tx and rx events are enabled.
//     * Both rx and tx events are disabled by this API
//     */
//    I2CDMATxRxEventDisable(SOC_I2C_0_REGS);
//}
//
//
//static void SetupInt(void)
//{
//    // Initialize DSP interrupts
//    IntDSPINTCInit();
//
//    // Enable DSP interrupts globally
//    IntGlobalEnable();
//}
//
//static void RegisterEdma3Interrupts(void)
//{
//    //Register Interrupts in vector table
//    IntRegister(C674X_MASK_INT4, I2CEdmaIsr);
//    IntRegister(C674X_MASK_INT5, I2CEdmaErrIsr);
//
//    // Map system interrupts to DSP maskable interrupts
//    IntEventMap(C674X_MASK_INT4, SYS_INT_EDMA3_0_CC0_INT1);
//    IntEventMap(C674X_MASK_INT5, SYS_INT_EDMA3_0_CC0_ERRINT);
//    IntEventMap(C674X_MASK_INT6, SYS_INT_EDMA3_0_CC0_INT2);
//
//    // Enable DSP maskable interrupts
//    IntEnable(C674X_MASK_INT4);
//    IntEnable(C674X_MASK_INT5);
//}
//
