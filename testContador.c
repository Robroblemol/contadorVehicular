#include <testContador.h>

// comandos para compilar desde la linea de comandos de ccs
/* ccsc para llamar al compilador
    +df opcion para crear el .cof (archivo simulacion)
    +p mantiene la centana del compilador abierta (sirve para ver errores)
    +pe para mantener la ventana abierta si hay un error en la compilacion
    ejemplo: ccsc +df +p testContador // compila el preoyecto
*/
int const totalPlaza =10;//cantidad total de plazas
signed long countTot = 10;//la cantidad inicial de plazas disponibles
int  countEnt,//Almacena la cantidad de entradas
     countSal,//Almacena la cantidad de salidas
     datoPuerto; //declaro variable para almacenar lo presente en el puerto
boolean flag_ent=false,//indica si se realizó una entrada
        flag_sal=false; //indica si se realizó una salida
#int_RB
void RB_isr(void) {
  output_toggle (led0);
  datoPuerto= input_b();// leo el puerto b
   if(bit_test(datoPuerto,4)==1&&bit_test(datoPuerto ,5)==0) flag_ent=true;
   if(bit_test(datoPuerto,6)==1&&bit_test(datoPuerto,7)==0) flag_sal=true;
}

 void plazas_disponibles(boolean flag_count) {
  //calculamos la cantidad de vehiculos disponibles
  if(flag_count == false) countTot--;
  else countTot++;
  if (countTot>=totalPlaza)countTot=10;
  if(countTot<=0)countTot=0;
  printf("Plazas disponibles = %u\r\n",countTot);

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
    datoPuerto= input_b();// leo el puerto b
   if(flag_ent==true&&bit_test(datoPuerto,5)==true){
     countEnt++;
     printf("Dato contador entrada = %u\r\n",countEnt);
     flag_ent=False;
     plazas_disponibles(false);
   }
   if (flag_sal==true&&bit_test(datoPuerto,7)==true){
     countSal++;
     printf("Dato contador salida = %u\r\n",countSal);
     flag_sal=False;
     plazas_disponibles(true);
   }
  }
}
