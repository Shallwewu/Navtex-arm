#ifndef __MessageDeal_H
#define __MessageDeal_H

//void isrTimer0Compare ();
void NewMsg_Save(void);
void MsgLock(short int num);
void MsgUnlock(short int);
void Msgdel(short int numtoprank);
void MsgFromFpga(void);
void deleteoldmess(void);
void mesdeletelook(void);
void DISABLEIRQB(void);
void DISABLEIRQA(void);
void ENABLEIRQB(void);
void ENABLEIRQA(void);
#endif
