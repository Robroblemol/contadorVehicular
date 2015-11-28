#include <testContador.h>

int  countEnt,//Almacena la cantidad de entradas 
     countSal,//Almacena la cantidad de salidas   
     datoPuerto; //declaroo variable para almacenar lo presente en el puerto
boolean flag_ent,//indica si se realizó una entrada 
        flag_sal; //indica si se realizó una salida
#int_RB
RB_isr() {
  datoPuerto= input_b();// leo el puerto b
   if(bit_test(datoPuerto,4)==1&&bit_test(datoPuerto ,5)==0) flag_ent=true;
   if(bit_test(datoPuerto,6)==1&&bit_test(datoPuerto,7)==0) flag_sal=true;
}



void main()
{

   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_spi(FALSE);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   setup_oscillator(False);

  while (true){
   if(flag_ent==true&&bit_test(datoPuerto,5)==true) countEnt++;
   if (flag_sal==true&&bit_test(datoPuerto,7)==true)countSal++;
  }
}
