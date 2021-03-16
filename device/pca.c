
#include	"pca.h"

#ifdef USING_PCA0
bit		B_Capture0;
uint8_t		PCA0_mode;
uint16_t		CCAP0_tmp,PCA_Timer0;
uint16_t	PWM0_low;	//PWM����͵�ƽ��PCAʱ���������, �û��㲻�ɼ���
static pca_interrupt_cb_t PCA0_Callback=NULL;
#endif
#ifdef USING_PCA1
bit		B_Capture1;
uint8_t		PCA1_mode;
uint16_t		CCAP1_tmp,PCA_Timer1;
uint16_t	PWM1_low;	//PWM����͵�ƽ��PCAʱ���������, �û��㲻�ɼ���
static pca_interrupt_cb_t PCA1_Callback=NULL;
#endif
#ifdef USING_PCA2
bit		B_Capture2;
uint8_t		PCA2_mode;
uint16_t		CCAP2_tmp,PCA_Timer2;
uint16_t	PWM2_low;	//PWM����͵�ƽ��PCAʱ���������, �û��㲻�ɼ���
static pca_interrupt_cb_t PCA2_Callback=NULL;
#endif





//========================================================================
// ����: void PWMn_SetHighReg(unsigned int high)
// ����: ����ռ�ձ����ݡ�
// ����: high: 	ռ�ձ����ݣ���PWM����ߵ�ƽ��PCAʱ�����������
// ����: ��
//========================================================================
void PWMn_Update(uint8_t PCA_id, uint16_t high)
{
    #ifdef USING_PCA0
	if(PCA_id == PCA0)
	{
        if(PCA0_mode == PCA_Mode_HighPulseOutput)
        {
            if(high > PWM0_HIGH_MAX)	high = PWM0_HIGH_MAX;	//���д��������ռ�ձ����ݣ�ǿ��Ϊ���ռ�ձȡ�
            if(high < PWM0_HIGH_MIN)	high = PWM0_HIGH_MIN;	//���д��С����Сռ�ձ����ݣ��򷵻ش������2��
            CR = 0;							//ֹͣPCA��
            PCA_Timer0 = high;				//��������ȷ��Χ����װ��ռ�ձȼĴ�����
            PWM0_low = PWM0_DUTY - high;	//���㲢����PWM����͵�ƽ��PCAʱ�����������
            CR = 1;							//����PCA��
        }
        else if(PCA0_mode == PCA_Mode_PWM)
        {
            CCAP0H = high;
        }
	}
    #endif
    #ifdef USING_PCA1
	if(PCA_id == PCA1)
	{
        if(PCA1_mode == PCA_Mode_HighPulseOutput)
        {
            if(high > PWM1_HIGH_MAX)	high = PWM1_HIGH_MAX;	//���д��������ռ�ձ����ݣ�ǿ��Ϊ���ռ�ձȡ�
            if(high < PWM1_HIGH_MIN)	high = PWM1_HIGH_MIN;	//���д��С����Сռ�ձ����ݣ��򷵻ش������2��
            CR = 0;							//ֹͣPCA��
            PCA_Timer1 = high;				//��������ȷ��Χ����װ��ռ�ձȼĴ�����
            PWM1_low = PWM1_DUTY - high;	//���㲢����PWM����͵�ƽ��PCAʱ�����������
            CR = 1;							//����PCA��
        }
        else if(PCA1_mode == PCA_Mode_PWM)
        {
            CCAP1H = high;
        }
	}
    #endif
    #ifdef USING_PCA2
	else if(PCA_id == PCA2)
	{
        if(PCA2_mode == PCA_Mode_HighPulseOutput)
        {
            if(high > PWM2_HIGH_MAX)		high = PWM2_HIGH_MAX;	//���д��������ռ�ձ����ݣ�ǿ��Ϊ���ռ�ձȡ�
            if(high < PWM2_HIGH_MIN)		high = PWM2_HIGH_MIN;	//���д��С����Сռ�ձ����ݣ��򷵻ش������2��
            CR = 0;						//ֹͣPCA��
            PCA_Timer2 = high;						//��������ȷ��Χ����װ��ռ�ձȼĴ�����
            PWM2_low = PWM2_DUTY - high;				//���㲢����PWM����͵�ƽ��PCAʱ�����������
            CR = 1;						//����PCA��
        }
        else if(PCA2_mode == PCA_Mode_PWM)
        {
            CCAP2H = high;
        }
	}
    #endif
}


//========================================================================
// ����: void	PCA_Init(PCA_id, PCA_InitTypeDef *PCAx)
// ����: PCA��ʼ������.
// ����: PCA_id: PCA���. ȡֵ PCA0,PCA1,PCA2,PCA_Counter
//		 PCAx: �ṹ����,��ο�PCA.h��Ķ���.
// ����: none.
//========================================================================
void	PCA_Init(uint8_t PCA_id, PCA_InitTypeDef *PCAx)
{
	if(PCA_id > PCA_Counter)	return;		//id����

	if(PCA_id == PCA_Counter)			//���ù���Counter
	{
		CR = 0;
		CH = 0;
		CL = 0;
		AUXR1 = (AUXR1 & ~(3<<4)) | PCAx->PCA_IoUse;			//�л�IO��
		CMOD  = (CMOD  & ~(7<<1)) | PCAx->PCA_Clock;			//ѡ��ʱ��Դ
		CMOD  = (CMOD  & ~1) | (PCAx->PCA_Interrupt_Mode & 1);	//ECF
		if(PCAx->PCA_Polity == PolityHigh)		PPCA = 1;	//�����ȼ��ж�
		else									PPCA = 0;	//�����ȼ��ж�
		CR = 1;
		return;
	}

	PCAx->PCA_Interrupt_Mode &= (3<<4) + 1;
	if(PCAx->PCA_Mode >= PCA_Mode_SoftTimer)	PCAx->PCA_Interrupt_Mode &= ~(3<<4);

    #ifdef USING_PCA0
	if(PCA_id == PCA0)
	{
		CCAPM0    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;	//����ģʽ, �ж�ģʽ
		PCA_PWM0  = (PCA_PWM0 & ~(3<<6)) | PCAx->PCA_PWM_Wide;	//PWM���

		PCA_Timer0 = PCAx->PCA_Value;
		B_Capture0 = 0;
		PCA0_mode = PCAx->PCA_Mode;
		CCAP0_tmp = PCA_Timer0;
		CCAP0L = (uint8_t)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP0H = (uint8_t)(CCAP0_tmp >> 8);	//��дCCAP0H
        PCA0_Callback = PCAx->PCA_Callback;
        return;
	}
    #endif
    #ifdef USING_PCA1
	if(PCA_id == PCA1)
	{
		CCAPM1    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM1  = (PCA_PWM1 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer1 = PCAx->PCA_Value;
		B_Capture1 = 0;
		PCA1_mode = PCAx->PCA_Mode;
		CCAP1_tmp = PCA_Timer1;
		CCAP1L = (uint8_t)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP1H = (uint8_t)(CCAP1_tmp >> 8);	//��дCCAP0H
        PCA1_Callback = PCAx->PCA_Callback;
        return;
	}
    #endif
    #ifdef USING_PCA2
	if(PCA_id == PCA2)
	{
		CCAPM2    = PCAx->PCA_Mode | PCAx->PCA_Interrupt_Mode;
		PCA_PWM2  = (PCA_PWM2 & ~(3<<6)) | PCAx->PCA_PWM_Wide;

		PCA_Timer2 = PCAx->PCA_Value;
		B_Capture2 = 0;
		PCA2_mode = PCAx->PCA_Mode;
		CCAP2_tmp = PCA_Timer2;
		CCAP2L = (uint8_t)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
		CCAP2H = (uint8_t)(CCAP2_tmp >> 8);	//��дCCAP0H
        PCA2_Callback = PCAx->PCA_Callback;
        return;
	}
    #endif
}


//========================================================================
// ����: void	PCA_Handler (void) interrupt PCA_VECTOR
// ����: PCA�жϴ������.
// ����: None
// ����: none.
//========================================================================
void	PCA_Handler (void) interrupt PCA_VECTOR
{
     

    #ifdef USING_PCA0
	if(CCF0) 		//PCAģ��0�ж�
	{
		CCF0 = 0;		//��PCAģ��0�жϱ�־
        if(PCA0_mode == PCA_Mode_HighPulseOutput)
        {
            if(((AUXR1>>4) & 0x03) == PCA_P24_P25_P26_P27)
            {
                if(P25)	CCAP0_tmp += PCA_Timer0;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP0_tmp += PWM0_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            else if(((AUXR1>>4) & 0x03) == PCA_P34_P35_P36_P37)
            {
                if(P35)	CCAP0_tmp += PCA_Timer0;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP0_tmp += PWM0_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            else if(((AUXR1>>4) & 0x03) == PCA_P12_P11_P10_P37)
            {
                if(P11)	CCAP0_tmp += PCA_Timer0;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP0_tmp += PWM0_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            
            CCAP0L = (uint8_t)CCAP0_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
            CCAP0H = (uint8_t)(CCAP0_tmp >> 8);	//��дCCAP0H
        }
        else if(PCA0_Callback)
        {
            PCA0_Callback(PCA0,CCAP0L+(((uint16_t)CCAP0H)<<8));
        }
	}
    #endif
    #ifdef USING_PCA1
	if(CCF1)	//PCAģ��1�ж�
	{
		CCF1 = 0;		//��PCAģ��1�жϱ�־
        if(PCA1_mode == PCA_Mode_HighPulseOutput)
        {
            if(((AUXR1>>4) & 0x03) == PCA_P24_P25_P26_P27)
            {
                if(P26)	CCAP1_tmp += PCA_Timer1;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP1_tmp += PWM1_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            else if(((AUXR1>>4) & 0x03) == PCA_P34_P35_P36_P37)
            {
                if(P36)	CCAP1_tmp += PCA_Timer1;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP1_tmp += PWM1_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            else if(((AUXR1>>4) & 0x03) == PCA_P12_P11_P10_P37)
            {
                if(P10)	CCAP1_tmp += PCA_Timer1;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP1_tmp += PWM1_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            CCAP1L = (uint8_t)CCAP1_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
            CCAP1H = (uint8_t)(CCAP1_tmp >> 8);	//��дCCAP0H
        }
        else if(PCA1_Callback)
        {
            PCA1_Callback(PCA1,CCAP1L+(((uint16_t)CCAP1H)<<8));
        }
        
	}
    #endif
    #ifdef USING_PCA2
	if(CCF2 && PCA2_mode == PCA_Mode_HighPulseOutput)	//PCAģ��2�ж�
	{
		CCF2 = 0;		//��PCAģ��2�жϱ�־
        if(PCA2_mode == PCA_Mode_HighPulseOutput)
        {
            if(((AUXR1>>4) & 0x03) == PCA_P24_P25_P26_P27)
            {
                if(P27)	CCAP2_tmp += PCA_Timer2;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP2_tmp += PWM2_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            else
            {
                if(P37)	CCAP2_tmp += PCA_Timer2;	//���Ϊ�ߵ�ƽ�����Ӱ��Ĵ���װ�ظߵ�ƽʱ�䳤��
                else	CCAP2_tmp += PWM2_low;	//���Ϊ�͵�ƽ�����Ӱ��Ĵ���װ�ص͵�ƽʱ�䳤��
            }
            CCAP2L = (uint8_t)CCAP2_tmp;			//��Ӱ��Ĵ���д�벶��Ĵ�������дCCAP0L
            CCAP2H = (uint8_t)(CCAP2_tmp >> 8);	//��дCCAP0H
        }
        else if(PCA2_Callback)
        {
            PCA2_Callback(PCA2,CCAP2L+(((uint16_t)CCAP2H)<<8));
        }
	}
    #endif

	if(CF)	//PCA����ж�
	{
        
		CF = 0;			//��PCA����жϱ�־
        #ifdef USING_PCA0
        if(PCA0_Callback && PCA0_mode == PCA_Mode_Capture)
        {
            PCA0_Callback(PCA_Counter,CL+(((uint16_t)CH)<<8));
        }
        #endif
        #ifdef USING_PCA1
        if(PCA1_Callback && PCA1_mode == PCA_Mode_Capture)
        {
            PCA1_Callback(PCA_Counter,CL+(((uint16_t)CH)<<8));
        }
        #endif
        #ifdef USING_PCA2
        if(PCA2_Callback && PCA2_mode == PCA_Mode_Capture)
        {
            PCA2_Callback(PCA_Counter,CL+(((uint16_t)CH)<<8));
        }
        #endif
	}
    
}
