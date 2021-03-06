#include <testContador.h>

// comandos para compilar desde la linea de comandos de ccs
/* ccsc para llamar al compilador
    +df opcion para crear el .cof (archivo simulacion)
    +p mantiene la centana del compilador abierta (sirve para ver errores)
    +pe para mantener la ventana abierta si hay un error en la compilacion
    ejemplo: ccsc +df +p testContador // compila el preoyecto


    problemas al inicio de conteo EEPROM vacia igual a 255 lo que hace que el
    valor inicial de las plaza sea 255, para que funcione bien es necesario
    ajustar primero el numero de plazas_disponibles 
*/
int totalPlaza =10;//cantidad total de plazas
signed long countTot;//la cantidad inicial de plazas disponibles
int  countShow,//variable a mostrar
     datoPuerto,//dato actual en el puerto
     datoPAnt; //declaro variable para almacenar lo presente en el puerto
boolean flag_ent=false,//indica si se realizó una entrada
        flag_sal=false, //indica si se realizó una salida
        flag_entS=false,
        flag_salS=false,
        flag_senE=false,
        flag_senS=false;
#int_RB
void RB_isr(void) {
  output_toggle (led0);
  datoPuerto= input_b();// leo el puerto b
  if(bit_test(datoPAnt,4)!=bit_test(datoPuerto,4)||bit_test(datoPAnt,5)!=bit_test(datoPuerto,5)){
     if(bit_test(datoPuerto,4)==1&&bit_test(datoPuerto ,5)==0)
     flag_senE=true;
     if(bit_test(datoPuerto,4)==0&&bit_test(datoPuerto ,5)==1)
     flag_senE=false;
     if(bit_test(datoPuerto,4)==0&&bit_test(datoPuerto ,5)==0&&!flag_senE)
     flag_ent=true;
     if(bit_test(datoPuerto,4)==0&&bit_test(datoPuerto ,5)==0&&flag_senE)
     flag_sal=true;
  }
if(bit_test(datoPAnt,6)!=bit_test(datoPuerto,6)||bit_test(datoPAnt,7)!=bit_test(datoPuerto,7)){
      if(bit_test(datoPuerto,6)==1&&bit_test(datoPuerto,7)==0)
        flag_senS=true;
      if(bit_test(datoPuerto,6)==0&&bit_test(datoPuerto,7)==1)
        flag_senS=false;
      if(bit_test(datoPuerto,6)==0&&bit_test(datoPuerto,7)==0&&!flag_senS)
        flag_entS=true;
      if(bit_test(datoPuerto,6)==0&&bit_test(datoPuerto ,7)==0&&flag_senS)
        flag_salS=true;
 }
   datoPAnt=datoPuerto;
}

 void plazas_disponibles(boolean flag_count) {
  //calculamos la cantidad de vehiculos disponibles
  if(flag_count == false) countTot--;
  else countTot++;
  if (countTot<=totalPlaza)countShow=countTot;
  if(countTot<0)countShow=0;
  if(countTot>totalPlaza)countTot=totalPlaza;
  write_eeprom(l_Pdis,countTot);
  printf("Contador Total = %u\r\n",countTot);
  printf("Plazas disponibles = %u\r\n",countShow);
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

//<<<<<<<<<<<<<<<<<<<<<<<<<<configuracion plazas totales>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  if(!input(b_men)&&!input(b_mas)){
    delay_ms(250);
    output_high (led0);

    while (!input(b_men)&&!input(b_mas)){}

    while (true) {
      if (input(b_men)==0) {
        while(!input(b_men)){}//no ejecuata hasta soltar el boton
        totalPlaza--;
        write_eeprom(Ep_Max,totalPlaza);
        printf("max plazas ajustado a: = %u\r\n",totalPlaza);
      }
      if (input(b_mas)==0) {
        while(!input(b_mas)){}//no ejecuata hasta soltar el boton
        totalPlaza++;
        write_eeprom(Ep_Max,totalPlaza);
        printf("max plazas ajustado a: = %u\r\n",totalPlaza);
      }
    }

  }

  totalPlaza=read_eeprom(Ep_Max);
  countTot=read_eeprom(l_Pdis);
  countShow=read_eeprom(l_Pdis);

  printf("Contador Total = %u\r\n",countTot);
  printf("Plazas disponibles = %u\r\n",countShow);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>bucle principal<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  while (true){
    datoPuerto= input_b();// leo el puerto b
   if(flag_ent==true && bit_test(datoPuerto ,4)==1&&bit_test(datoPuerto ,5)==0){
     //printf("Dato contador entrada = %u\r\n",countEnt);
     flag_ent=False;
     plazas_disponibles(false);
   }
   if (flag_sal==true&&bit_test(datoPuerto ,5)==1&&bit_test(datoPuerto ,4)==0){
     //printf("Dato contador salida = %u\r\n",countSal);
     flag_sal=False;
     plazas_disponibles(true);
   }
//<<<<<<<<<<<<<<<<<<<<<<< carril salida >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   if(flag_entS==true && bit_test(datoPuerto ,6)==1&&bit_test(datoPuerto ,7)==0){
     //printf("Dato contador entrada = %u\r\n",countEnt);
     flag_entS=False;
     plazas_disponibles(true);
   }
   if (flag_salS==true&&bit_test(datoPuerto ,7)==1&&bit_test(datoPuerto ,6)==0){
     //printf("Dato contador salida = %u\r\n",countSal);
     flag_salS=False;
     plazas_disponibles(false);
   }
//<<<<<<<<<<<<<<<<<<<<<<<<< botones de ajuste >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
   if(input(b_mas)==0){
     delay_ms(500);
     plazas_disponibles(false);
   }
   if (input(b_men)==0) {
    delay_ms(500);
    plazas_disponibles(true);
   }
  }
}
