#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //�Լ��ӵĹ���FPGA��д





void LcdDisplay();
void LcdDisplay()
{
	switch(STATE)
	{
		
		case(5):	//״̬5����ʱ�����
			{
				if(G_Key == MENU) 
				{
					CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
				}
				
				else if(G_Key == DISP) 
				{
					CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
				}
				break;
			}			
		
		
		case(1):	//״̬1������Ϣ���������棬ȫ�ֱ���State1parameterΪ��ڲ���
					//����ý����ֱ���subback�ж��Ƿ���Ӳ˵����� 	
					//����Returntype���жϷ���ʱ�Ӻβ˵���ȥ
			{
/*				if(G_Key==LEFT||G_Key==RIGHT)
				{
					if (G_Key==LEFT)				//��һ����Ϣ����
					{
						if(Messagenownumber>0)		//���Խ����Ϸ���Ϣ
						{
							CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
						}
					}
					
					else if (G_Key==RIGHT&&(Returntype==1||Returntype==0||Returntype==3))		//�洢��Ϣ������·���Ϣ����
					{
						if(Messagenownumber<Messageinfo.savenumber[0]-1) 	//���Խ����·�����
						{
							CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
						}
					}
				
					else if (G_Key==RIGHT&&(Returntype==2||Returntype==4))						//������Ϣ������·���Ϣ����
					{
						if(Messagenownumber<Messageinfo.locknumber[0]-1) 	//���Խ����·�����
						{
							CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
						}			
					}
				}
				
				if (G_Key==STAR)
				{	
					ProtectData();
					CLEAR2();		//�����Ӳ˵������������
				}*/
				
				
				if (G_Key==MENU||G_Key==DISP||(G_Key==CLR&&Returntype!=0))	//��ת����MainMenu���棬��ڲ���0
				{
					if(now_printing==0)	
						CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
				}
					

				break;	
			}
			



		case(10):	//״̬10��������Ϣ���ݽ��棬ȫ�ֱ���State10parameterΪ��ڲ���
					//����ý������PublicReturn����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
			{
				if(G_Key==ENT)
				{
					CLEAR2();		//�����Ӳ˵������������
				}
				break;
			}
		
		case(11):	//״̬11������Ϣ�����ӽ���
			{
				if (G_Key==CLR/*||G_Key==LEFT*/||G_Key==ENT)
				{
					CLEAR2();		//�����Ӳ˵������������
				}

				break;
			}
			
		case(12):	//״̬12������Ϣ�����ӽ����µ������Ӳ˵�
			{
			
				if (G_Key==ENT)
				{
					if(BUFFER2[0]==0&&Messagesavetop[Messagetoprank[Messagenownumber]].lock==1)
						CLEAR1();
					else
					{
						CLEAR2();
					}
				}
				break;
			}
		
			
		case(13):	//״̬13������Ϣ�����ӽ����µĴ�ӡ�Ӳ˵���ȫ�ֱ���State13parameterΪ��ڲ���
					//����ý������PublicReturn����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}
											
		case(14):	//״̬14���������������˵���ȫ�ֱ���State14parameterΪ��ڲ���
					//����ý������subback����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}
					
		case(15):	//״̬15�����ӡ�������
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}

		case(16):	//״̬16�����ӡ�н���
			{
				
				break;
			}			
		
		case(2):	//�洢������������湫��״̬2��ȫ�ֱ���State2parameterΪ��ڲ���
					//����ý����ֱ���subback�ж��Ƿ���Ӳ˵����� 	
					//����Returnback�����жϷ���ʱ�Ӻβ˵���ȥ
			{
				if(G_Key == STAR&&Messagenumber) 
				{
					ProtectData();				
					CLEAR2();	
				}
				else if(G_Key == DISP||G_Key == MENU) CLEAR1();
				else if(G_Key == ENT&&Messagenumber!=0) CLEAR1();
				break;	
			}
			
		case(20):	//״̬20����洢�����Ӳ˵�
			{
				if(/*G_Key == LEFT ||*/ G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER1[0]==1)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER1[0]!=1)
				CLEAR2();
				
				break;
			}
			
			
		case(200):	//�洢�˵��´�ӡ��ѡ��������ѡ�˵��Ĺ���״̬200��ȫ�ֱ���State200parameterΪ��ڲ���
					//����ý����ֱ���Selectsubback�ж��Ƿ���Ӳ˵����� 	
					//����Selectreturn���жϷ���ʱ�Ӻβ˵���ȥ
			{
				if(G_Key == CLR) CLEAR1();
//				else if(BUFFERSELECT[Messagesavetop[Messagetoprank[Mulnownumber]].frequency]>Maxlocknum&&Selectreturn==0)
//				{
//					ProtectData();
//					CLEAR2();
//				}
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}			
				break;	
			}				

		case(2000):	//�洢�������˵��µ������ͽ���ȷ�ϵĹ���״̬2000��ȫ�ֱ���State2000parameterΪ��ڲ���

			{
				if(G_Key == ENT&&BUFFER3[0] == 0)
				CLEAR1();
				else if(G_Key == ENT&&BUFFER3[0] == 1)
				CLEAR2();
				break;	
			}

		case(201):	//״̬201����洢�����Ӳ˵��µĴ�ӡ�Ӳ˵�
			{
				if(/*G_Key == LEFT || */G_Key == ENT || G_Key == CLR)
				CLEAR2();
				break;	
			}
		case(2010):	//״̬2010����洢�����Ӳ˵��µĴ�ӡ�Ӳ˵���������˵�
			{
				if(/*G_Key == LEFT || */G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER3[0]==2)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER3[0]!=2)
				CLEAR2();				
				break;	
			}
		case(2011):	//������˵��£��洢��������ӡ�˵�״̬2011��ȫ�ֱ���State2011parameterΪ��ڲ���
					//����ý����ֱ���PitchDAPro�ж��Ǵ�ʲô�˵����� 	
				
			{
				if(G_Key == ENT&&(BUFFER4[0]==3||BUFFER4[0]==4))
				CLEAR2();
				break;	
			}
						
				
		case(202):	//�洢�������������������˵����ý��棬ȫ�ֱ���State202parameterΪ��ڲ���
					//����ý����ֱ���Rankback�ж��ǴӺβ˵����� 	
					//����Rankback�����жϷ���ʱ�Ӻβ˵���ȥ
			{
				if(/*G_Key == LEFT || */G_Key == CLR || G_Key == ENT)
				CLEAR2();
				break;	
			}
			
		case(2020):	//�����˵��ʹ洢�˵�������˵����÷�Χѡ��˵���״̬2020
			{
				if(/*G_Key == LEFT || */G_Key == CLR || G_Key == ENT)
				CLEAR2();
				break;
			}
			
														
		case(30):	//״̬30�������������Ӳ˵�
			{
				if(/*G_Key == LEFT || */G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER1[0]==1)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER1[0]!=1)
				CLEAR2();	
				break;
			}
		case(300):	//�����˵���������ѡ�˵�״̬300��ȫ�ֱ���State300parameterΪ��ڲ���
					//����ý����ֱ���Selectsubback�ж��Ƿ���Ӳ˵����� 	
			{
				if(G_Key == CLR) CLEAR1();
				if(G_Key == STAR) 
				{
					ProtectData();
					CLEAR2();
				}
				break;	
			}
			
			
							
		case(4)://״̬4�������˵����棬ȫ�ֱ���State4parameterΪ��ڲ���
				//����ý������backpage����ʾ �����жϷ���ʱ�Ӻβ˵���ȥ
			
			{
				if(G_Key == DISP || G_Key == CLR || G_Key == ENT)
				CLEAR1();
				break;
			}
			
			
		case(40):	//״̬40���뷢��̨����
			{
				if (G_Key == CLR)
				CLEAR1();
				else if(G_Key == ENT&&(BUFFER1[0] == 2||BUFFER1[0] == 3))
				CLEAR1();
				break;
			}
			
		case(400)://״̬400�����Զ�ģʽ���ý��棬ȫ�ֱ���State400parameterΪ��ڲ���
				  //����ý������subback���жϴӺβ˵�����
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				} 
				break;
			}
							
		case(401)://״̬401�����ֶ�ģʽ���ý��棬ȫ�ֱ���State401parameterΪ��ڲ���
				  //����ý������subback���жϴӺβ˵�����
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}
				break;
			}
			
		case(4000)://״̬4000����401��402�����ӽ��棬ȫ�ֱ���State4000parameterΪ��ڲ���
				  //����ý������parameter���жϴӺβ˵�����
			{
				if(G_Key==ENT) CLEAR2();
				break;
			}								
		
		case(41)://״̬41������Ϣ������ý��棬ȫ�ֱ���State41parameterΪ��ڲ���
			     //����ý������subback���жϴӺβ˵�����
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}
				break;
			}
			
		case(42):	//״̬42������ʾ���ý���
			{
				if (G_Key==CLR&&BUFFER1[0]<5) CLEAR1(); 
				break;
			}
		
		
		case(43):	//״̬43������ջ����ý���
			{
				if(G_Key==CLR&&(BUFFER1[0]==0||BUFFER1[0]==1||BUFFER1[0]==6))
				CLEAR1();	
				break;
			}
			
		case(44):	//״̬44����ά�����ý���
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==ENT&&(BUFFER1[0]==0||BUFFER1[0]==2))
				{
					CLEAR1();
				}
				else if(G_Key==ENT&&BUFFER1[0]==1)
				{
					ProtectData();
					CLEAR2();
				}

				break;
			}
			
		case(440):	//״̬440�����Լ����
			{
				if (G_Key==CLR||(G_Key==ENT&&BUFFER2[0]==2))
				CLEAR1();
				break;
			}
			
		case(4400):	//״̬4400�����Լ���־����
			{
				if (G_Key==CLR) CLEAR1();
				break;
			}
			
		case(441):	//״̬441������ջ�״̬����
			{
				if (G_Key==CLR) CLEAR1();				
				break;
			}						

		case(442):	//״̬442����ָ���������ȷ�ϲ˵�
			{
				if (G_Key==ENT&&BUFFER2[0]==1) CLEAR2();	
				break;
			}
						
		case(45):	//״̬45��������ѡ�����
			{
				if(G_Key==ENT||G_Key==CLR/*||G_Key==LEFT*/)	CLEAR1();
				break;
			}				
	}
	
}