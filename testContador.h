#include <16F88.h>
#device adc=8

#FUSES NOWDT                 	//No Watch Dog Timer
#FUSES RC                    	//Resistor/Capacitor Osc with CLKOUT
#FUSES NOPUT                 	//No Power Up Timer
#FUSES MCLR                  	//Master Clear pin enabled
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                 	//No EE protection
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NODEBUG               	//No Debug mode for ICD
#FUSES NOPROTECT             	//Code not protected from reading
#FUSES FCMEN                 	//Fail-safe clock monitor enabled
#FUSES IESO                  	//Internal External Switch Over mode enabled

#use delay(clock=8000000)
#use rs232(baud=9600,parity=N,xmit=PIN_A1,rcv=PIN_A2,bits=8)

#define led0 pin_A0
#define b_mas pin_a3
#define b_men pin_a4
