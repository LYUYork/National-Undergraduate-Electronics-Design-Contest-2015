/*-----------------------------------------------.H??-----------------------------------------*/ 
#include<reg52.h>
#ifndef __RC522_H_ 
#define __RC522_H_  
#define uint unsigned int 
#define nop() nop_()
#define uint unsigned int 
///////////////////////////////////////////////////////////////////// 
//MF522???  
/////////////////////////////////////////////////////////////////////  
#define PCD_IDLE              0x00               //?????? 
#define PCD_AUTHENT           0x0E               //???? 
#define PCD_RECEIVE           0x08               //???? 
#define PCD_TRANSMIT          0x04               //????  
#define PCD_TRANSCEIVE        0x0C               //??????? 
#define PCD_RESETPHASE        0x0F               //?? 
#define PCD_CALCCRC           0x03               //CRC??   
/////////////////////////////////////////////////////////////////////  
//Mifare_One?????  
/////////////////////////////////////////////////////////////////////  
#define PICC_REQIDL           0x26               //???????????? 
#define PICC_REQALL           0x52               //???????? 
#define PICC_ANTICOLL1        0x93               //??? 
#define PICC_ANTICOLL2        0x95               //???  
#define PICC_AUTHENT1A        0x60               //??A?? 
#define PICC_AUTHENT1B        0x61               //??B?? 
#define PICC_READ             0x30               //?? 
#define PICC_WRITE            0xA0               //?? 
#define PICC_DECREMENT        0xC0               //?? 
#define PICC_INCREMENT        0xC1               //??  
#define PICC_RESTORE          0xC2               //???????? 
#define PICC_TRANSFER         0xB0               //???????? 
#define PICC_HALT             0x50               //??   
///////////////////////////////////////////////////////////////////// 
//MF522 FIFO????  
/////////////////////////////////////////////////////////////////////  
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte 
#define MAXRLEN  18   
///////////////////////////////////////////////////////////////////// 
//MF522????? 
/////////////////////////////////////////////////////////////////////
// PAGE 0 
#define     RFU00                 0x00     
#define     CommandReg            0x01 
#define     ComIEnReg             0x02   
#define     DivlEnReg             0x03   
#define     ComIrqReg             0x04   
#define     DivIrqReg             0x05  
#define     ErrorReg              0x06    
#define     Status1Reg            0x07     
#define     Status2Reg            0x08     
#define     FIFODataReg           0x09 
#define     FIFOLevelReg          0x0A 
#define     WaterLevelReg         0x0B 
#define     ControlReg            0x0C 
#define     BitFramingReg         0x0D 
#define     CollReg               0x0E 
#define     RFU0F                 0x0F 
// PAGE 1      
#define     RFU10                 0x10 
#define     ModeReg               0x11 
#define     TxModeReg             0x12 
#define     RxModeReg             0x13 
#define     TxControlReg          0x14 
#define     TxAutoReg             0x15 
#define     TxSelReg              0x16 
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18 
#define     DemodReg              0x19 
#define     RFU1A                 0x1A 
#define     RFU1B                 0x1B 
#define     MifareReg             0x1C 
#define     RFU1D                 0x1D 
#define     RFU1E                 0x1E 
#define     SerialSpeedReg        0x1F 
// PAGE 2     
#define     RFU20                 0x20 
#define     CRCResultRegM         0x21 
#define     CRCResultRegL         0x22 
#define     RFU23                 0x23 
#define     ModWidthReg           0x24 
#define     RFU25                 0x25 
#define     RFCfgReg              0x26 
#define     GsNReg                0x27 
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29 
#define     TModeReg              0x2A 
#define     TPrescalerReg         0x2B 
#define     TReloadRegH           0x2C 
#define     TReloadRegL           0x2D 
#define     TCounterValueRegH     0x2E 
#define     TCounterValueRegL     0x2F 
// PAGE 3      
#define     RFU30                 0x30 
#define     TestSel1Reg           0x31 
#define     TestSel2Reg           0x32 
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34 
#define     TestBusReg            0x35
#define     AutoTestReg           0x36 
#define     VersionReg            0x37 
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39   
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F        0x3F 
/////////////////////////////////////////////////////////////////////
//?MF522?????????? 
///////////////////////////////////////////////////////////////////// 
#define  MI_OK                 0 
#define  MI_NOTAGERR           (-1) 
#define  MI_ERR                (-2)  
#define SHAQU1 0X01
#define KUAI4 0X04 
#define KUAI7 0X07 
#define REGCARD 0xa1
#define CONSUME 0xa2 
#define READCARD 0xa3 
#define ADDMONEY 0xa4   
//void delay_ns(uint16 ns); 
void delay10us();
void delay1ms();
unsigned int SPIReadByte(); 
void SPIWriteByte(uint SPIData);  
unsigned char PcdRequest(uint req_code,uint *pTagType); 
unsigned char PcdAnticoll(uint *pSnr); 
unsigned char PcdSelect(unsigned char *pSnr); 
unsigned char PcdAuthState(uint auth_mode,uint addr,uint *pKey,uint *pSnr); 
unsigned char PcdRead(uint addr,uint *pData); 
unsigned char PcdWrite(uint addr,uint *pData); 
unsigned char PcdHalt(); 
void CalulateCRC(uint *pIndata,uint len,uint *pOutData); 
unsigned char PcdReset(); 
unsigned char M500PcdConfigISOType(uint type);
unsigned int  ReadRawRC(uint Address); 
void WriteRawRC(uint Address, uint value); 
void SetBitMask(uint reg,uint mask);
void ClearBitMask(uint reg,uint mask); 
unsigned char PcdComMF522(uint Command,uint *pInData,uint InLenByte,uint *pOutData,uint *pOutLenBit); 
void PcdAntennaOn(); 
void PcdAntennaOff(); 
void InitRc522();  
void delay1ms500us();  
sbit  SPI_CS   = P1^3; 
sbit  SPI_CK   = P1^4;
sbit  SPI_MOSI = P1^5; 
sbit  SPI_MISO = P1^6; 
sbit  SPI_RST  = P1^7;   
#define SET_SPI_CS  SPI_CS=1 
#define CLR_SPI_CS  SPI_CS=0   
#define SET_SPI_CK  SPI_CK=1
#define CLR_SPI_CK  SPI_CK=0  
#define SET_SPI_MOSI  SPI_MOSI=1 
#define CLR_SPI_MOSI  SPI_MOSI=0  
#define SET_SPI_MISO  SPI_MISO   
#define SET_RC522RST  SPI_RST=1 
#define CLR_RC522RST  SPI_RST=0
#endif

