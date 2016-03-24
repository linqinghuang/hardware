#define GPBCON      (*(volatile unsigned long *)0x56000010)
#define GPBDAT      (*(volatile unsigned long *)0x56000014)

#define GPFCON      (*(volatile unsigned long *)0x56000050)
#define GPFDAT      (*(volatile unsigned long *)0x56000054)

#define GPGCON      (*(volatile unsigned long *)0x56000060)
#define GPGDAT      (*(volatile unsigned long *)0x56000064)

/*
 * LED1-4��ӦGPB5��GPB6��GPB7��GPB8
 */
#define GPB5_out        (1<<(5*2))
#define GPB6_out        (1<<(6*2))
#define GPB7_out        (1<<(7*2))
#define GPB8_out        (1<<(8*2))

/*
 * K1-K4��ӦGPG11��GPG3��GPF2��GPF0
 */
#define GPG11_in    ~(3<<(11*2))
#define GPG3_in     ~(3<<(3*2))
#define GPF2_in     ~(3<<(2*2))
#define GPF0_in     ~(3<<(0*2))

int main()
{
        unsigned long dwDat;
        // LED1-LED4��Ӧ��4��������Ϊ���
        GPBCON = GPB5_out | GPB6_out | GPB7_out | GPB8_out ;

        // K1-K2��Ӧ��2��������Ϊ����
        GPGCON = GPG11_in & GPG3_in ;
        
        // K3-K4��Ӧ��2��������Ϊ����
        GPFCON = GPF2_in & GPF0_in ;

        while(1){
            //��KnΪ0(��ʾ����)������LEDnΪ0(��ʾ����)
            dwDat = GPGDAT;             // ��ȡGPG�ܽŵ�ƽ״̬
        
            if (dwDat & (1<<11))        // K1û�а���
                GPBDAT |= (1<<5);       // LED1Ϩ��
            else    
                GPBDAT &= ~(1<<5);      // LED1����
                
            if (dwDat & (1<<3))         // K2û�а���
                GPBDAT |= (1<<6);       // LED2Ϩ��
            else    
                GPBDAT &= ~(1<<6);      // LED2����
    
            dwDat = GPFDAT;             // ��ȡGPF�ܽŵ�ƽ״̬
            
            if (dwDat & (1<<2))         // K3û�а���
                GPBDAT |= (1<<7);       // LED3Ϩ��
            else    
                GPBDAT &= ~(1<<7);      // LED3����
    
            if (dwDat & (1<<0))         // K4û�а���
                GPBDAT |= (1<<8);       // LED4Ϩ��
            else    
                GPBDAT &= ~(1<<8);      // LED4����
    }

    return 0;
}
