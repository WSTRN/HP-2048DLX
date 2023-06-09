//& *** (c) 2006-2011 The HPGCC3 Team ***
//& Claudio Lapilli
//& Ingo Blank
//&
//& This file is licensed under the terms and conditions of the
//& HPGCC3 license that is included with the source distribution.
//& *** (c) 2006-2011 The HPGCC3 Team ***


// $Header: sddriver.h,r42 2006-02-18 04:23:47 ingo $

// SD DRIVER HEADER



#define CLKREG 0x07200000
#define SDREG  0x07e00000
#define IOPORT 0x07a00000

#define HWREG(base,off) ( (volatile unsigned int *) (((int)base+(int)off)))


#define GPD(a) HWREG(IOPORT,0x30+a)
#define GPE(a) HWREG(IOPORT,0x40+a)
#define GPF(a) HWREG(IOPORT,0x50+a)

#define SDICON HWREG(SDREG,0)
#define SDIPRE HWREG(SDREG,0X4)
#define SDICARG HWREG(SDREG,0x8)
#define SDICCON HWREG(SDREG,0xc)
#define SDICSTA HWREG(SDREG,0x10)
#define SDIRSP0 HWREG(SDREG,0x14)
#define SDIRSP1 HWREG(SDREG,0x18)
#define SDIRSP2 HWREG(SDREG,0x1c)
#define SDIRSP3 HWREG(SDREG,0x20)
#define SDIDTIMER HWREG(SDREG,0x24)
#define SDIBSIZE HWREG(SDREG,0x28)
#define SDIDCON HWREG(SDREG,0x2c)
#define SDIDCNT HWREG(SDREG,0x30)
#define SDIDSTA HWREG(SDREG,0x34)
#define SDIFSTA HWREG(SDREG,0x38)
#define SDIDAT HWREG(SDREG,0x3c)
#define SDIIMSK HWREG(SDREG,0x40)



#define CON 0
#define DAT 4
#define PULLUP 8


typedef struct {
int SystemFlags;			// 1=SDIO interface setup, 2=SDCard initialized, 4=Valid RCA obtained, 8=Bus configured OK
int Rca;
int BusWidth;
int MaxBlockLen;
int WriteBlockLen;
int CurrentBLen;
int CardSize;
unsigned int CID[4];
} SD_CARD;


int SDIOSetup(SD_CARD *card,int shutdown);
int SDCardInserted();
int GetPCLK();
int SDSetFastPCLK();
void SDRestorePCLK(int original);
void SDSetClock(int sdclk);
int SDGetClock();
void SDPowerDown();
void SDPowerUp();
int SDSlowDown();
int SDWaitResp(int mask);
int SDSendCmd(int cmdnum,int arg,int cmdmsk,int mask);
int SDSendACmd(int rca,int cmdnum,int arg,int cmdmsk,int mask);
int SDSendCmdNoResp(int cmdnum,int arg);
int SDSendCmdShortResp(int cmdnum,int arg,int *response);
int SDSendCmdLongResp(int cmdnum,int arg,int *response);
int SDSendACmdShortResp(int rca,int cmdnum,int arg,int *response);
int SDSendACmdLongResp(int rca,int cmdnum,int arg,int *response);
void SDIOReset();
int SDSelect(int RCA);
int SDInit(SD_CARD *card);
int SDGetNewRCA(int *_CID);
void SDDResetFIFO();
int SDDStop();
int SDDSetBlockLen(SD_CARD *card,int bitlen);
int SDDInTransfer(SD_CARD *card);
int SDDRead(int SDAddr,int NumBytes,char *buffer, SD_CARD *card);
int SDCardInit(SD_CARD * card);
int SDDWrite(int SDAddr,int NumBytes,char *buffer, SD_CARD *card);

