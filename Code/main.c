#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "printer.h"
#include "flash.h"
#include "code.h"

//extern void test_message(void);

int main()
{		
//  test_message();
	IntialNormal();	//�����������غ���
//	cleareeprom();
//	IntialOriginal();
//	readalleeprom();	
//	readflash();
//	SCR &= ~SCR_BOOT_MODE_MASK; 
//	SCR |= SCR_BOOT_MODE0_MASK;
//	COPTO=0xFFFF;
//	COPCTL|=COPCTL_CEN_MASK;	//COPʹ��
	while(1)
	{
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;
		switch(STATE)
		{
			
			case(5):	//״̬5����ʱ�����
				{
					RunTimeLocation();
					break;
				}			
			
			case(1):	//״̬1������Ϣ���������棬ȫ�ֱ���State1parameterΪ��ڲ���
						//����ý����ֱ���subback�ж��Ƿ���Ӳ˵����� 	
  						//����Returntype���жϷ���ʱ�Ӻβ˵���ȥ
				{     
					RunMessage(State1parameter);
					break;	
				}
				
			case(11):	//״̬11������Ϣ�����ӽ���
				{
					RunMessageSubmenu();
					break;
				}
				
			case(12):	//״̬12������Ϣ�����ӽ����µ������Ӳ˵�
				{
					RunMessage_LockSubmenu();
					break;
				}
			
			case(13):	//״̬13������Ϣ�����ӽ����µĴ�ӡ�Ӳ˵���ȫ�ֱ���State13parameterΪ��ڲ���
						//����ý������PublicReturn����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
				{
					RunMessage_PrintSubmenu(State13parameter);
					break;
				}
												
			case(14):	//״̬14���������������˵���ȫ�ֱ���State14parameterΪ��ڲ���
						//����ý������subback����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
				{
					RunMessage_OverCapacity(State14parameter);
					break;
				}
						
			case(15):	//״̬15�����ӡ�������
				{   
					RunMessage_PrintError();
					break;
				}

			case(16):	//״̬16�����ӡ�н���
				{
					RunMessage_Printing();
					break;
				}			
			
			case(2):	//�洢������������湫��״̬2��ȫ�ֱ���State2parameterΪ��ڲ���
						//����ý����ֱ���subback�ж��Ƿ���Ӳ˵����� 	
  						//����Returnback�����жϷ���ʱ�Ӻβ˵���ȥ
				{   
				    IntialLCD(0);
					RunSaveMenu(State2parameter);
					break;	
				}
				
			case(20):	//״̬20����洢�����Ӳ˵�
				{
					RunSaveSubMenu();
					break;
				}
				
				
			case(200):	//�洢�˵��´�ӡ��ѡ��������ѡ�˵��Ĺ���״̬200��ȫ�ֱ���State200parameterΪ��ڲ���
						//����ý����ֱ���Selectsubback�ж��Ƿ���Ӳ˵����� 	
  						//����Selectreturn���жϷ���ʱ�Ӻβ˵���ȥ
				{
					RunSaveLockSubMenu(State200parameter);
					break;	
				}				

			case(2000):	//�洢�������˵��µ������ͽ���ȷ�ϵĹ���״̬2000��ȫ�ֱ���State2000parameterΪ��ڲ���

				{
					RunSaveLockSubSure(State2000parameter);
					break;	
				}
	
			case(201):	//״̬201����洢�����Ӳ˵��µĴ�ӡ�Ӳ˵�
				{
					RunSavePrintSubMenu();
					break;	
				}
				
			case(2010):	//״̬2010����洢�����Ӳ˵��µĴ�ӡ�Ӳ˵���������˵�
				{
					RunSavePitchPrint();
					break;	
				}
			case(2011):	//������˵��£��洢��������ӡ�˵�״̬2011��ȫ�ֱ���State2011parameterΪ��ڲ���
						//����ý����ֱ���PitchDAPro�ж��Ǵ�ʲô�˵����� 	
  					
				{
					RunSaveAllMessage();
					break;	
				}
								
			case(202):	//�洢�������������������˵����ý��棬ȫ�ֱ���State202parameterΪ��ڲ���
						//����ý����ֱ���Rankback�ж��ǴӺβ˵����� 	
  						//����Rankback�����жϷ���ʱ�Ӻβ˵���ȥ
				{
					RunSaveRankSubMenu(State202parameter);
					break;	
				}
				
			case(2020):	//�����˵��ʹ洢�˵�������˵����÷�Χѡ��˵���״̬2020
				{
					RunSaveRangeChoose();
					break;
				}
				
			case(2021):	//�����˵��ʹ洢�˵�������˵���Χѡ��ȷ���˵���״̬2021
				{
					RunSaveRanking();
					break;
				}								
															
			case(30):	//״̬30�������������Ӳ˵�
				{
					RunLockSubMenu();
					break;
				}
			case(300):	//�����˵���������ѡ�˵�״̬300��ȫ�ֱ���State300parameterΪ��ڲ���
						//����ý����ֱ���Selectsubback�ж��Ƿ���Ӳ˵����� 	
  						
				{
					RunLockLockSubMenu(State300parameter);
					break;	
				}
								
			case(4)://״̬4�������˵����棬ȫ�ֱ���State4parameterΪ��ڲ���
					//����ý������backpage����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
				
				{			
				    IntialLCD(0);
			  		RunMainMenu(State4parameter);
					break;
				}
				
			case(40):	//״̬40���뷢��̨����
				{
					RunRxstation();
					break;
				}
				
			case(400)://״̬400�����Զ�ģʽ���ý��棬ȫ�ֱ���State400parameterΪ��ڲ���
					  //����ý������subback���жϴӺβ˵�����
				{
					RunAutomode(State400parameter);
					break;
				}
								
			case(401)://״̬401�����ֶ�ģʽ���ý��棬ȫ�ֱ���State401parameterΪ��ڲ���
					  //����ý������subback���жϴӺβ˵�����
				{
					RunManualmode(State401parameter);
					break;
				}
				
			case(4000)://״̬4000����401��402�����ӽ��棬ȫ�ֱ���State4000parameterΪ��ڲ���
					  //����ý������parameter���жϴӺβ˵�����
				{
					RunAutomodeSubmenu(State4000parameter);
					break;
				}								
			
			case(41)://״̬41������Ϣ������ý��棬ȫ�ֱ���State41parameterΪ��ڲ���
				     //����ý������subback���жϴӺβ˵�����
				{
					RunMessagetypemenu(State41parameter);
					break;
				}
				
			case(42):	//״̬42������ʾ���ý���
				{
					RunDisplaySetting();
					break;
				}
			
			case(43):	//״̬43������ջ����ý���
				{
					RunReceiveSetting();
					break;
				}
				
			case(44):	//״̬44����ά�����ý���
				{
					RunMaintain(State44parameter);
					break;
				}
				
			case(440):	//״̬440�����Լ����
				{
					RunSelfDiagnosis();
					break;
				}
				
			case(4400):	//״̬4400�����Լ���־����
				{
					RunDiaglog();
					break;
				}
				
			case(441):	//״̬441������ջ�״̬����
				{
					RunNavtexState();					
					break;
				}						

			case(442):	//״̬442����ָ���������ȷ�ϲ˵�
				{
					RunRecoverFactory();
					break;
				}
							
			case(45):	//״̬45��������ѡ�����
				{
					RunLanguageSetting();
					break;
				}
			default:
				{
					FLAG=0;
					STATE=1;	
					BUFFER[0]=0;
					State1parameter=0;		//Ϊ��ָ������Ϣ������ֱ�ӱ�ʾ�Ӵ洢������� ������DISP���룬�޷��ؼ�����modified@2010-8-17
					CLEAR1();
					break;				
				}					
		}    
	FLAG=1;	
	}   
}
