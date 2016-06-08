/*
*********************************************************************************************************
*                                           GRP550M CODE2
*
*                             (c) Copyright 2013; Sistemas Insepet LTDA
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                               GRP550M CODE
*
*                                             CYPRESS PSoC5LP
*                                                with the
*                                            CY8C5969AXI-LP035
*
* Filename      : main.c
* Version       : V2.00
* Programmer(s) : 
                  
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <device.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Protocolo.h"
#include "VariablesG.h"
#include "Print.h"
#include "LCD.h"
#include "ibutton.h"
#include "i2c.h"

/*
*********************************************************************************************************
*                                             DECLARACION DE FUNCIONES
*********************************************************************************************************
*/
uint8 letras[26]={0x25,0x42,0x31,0x27,0x1D,0x28,0x29,0x2A,0x22,0x2B,0x2C,0x2D,0x35,0x34,0x23,0x24,0x1B,0x1E,0x26,0x1F,0x21,0x32,0x1C,0x30,0x20,0x2F};
uint8 clave_config[5]="02412";
uint8 test[18]="Test de Impresora";
uint16 num_decimal2;
CY_ISR(animacion);
CY_ISR(animacion2);
CY_ISR(modo_mux);
uint8  idaux[8];
uint8  state_rf;
uint16 timeout_autorizacion;
uint8  estado_tanqueando; 
uint8  consulta_sistema=1;
uint8  clave_local[4]={'9','6','3','1'};
uint8  v_digitos_1;
uint8  ppuinicial=0;
uint8  Producto;
uint8  Productos[4];// el buffer es para guardar los tipos de combustible
uint8  producto1=1,producto2=1,producto3=1,producto4=1;
uint8 status1LP,status2LP,status1st,status2st; 


/*
*********************************************************************************************************
*                                         init( void )
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/ 
void init(void){
    timeout_autorizacion=0;
	uint8 x;
    CyGlobalIntEnable;
	PC_Start();
    I2C_1_Start();
    Surtidor_Start();
    LCD_1_Start();
    LCD_2_Start();   	
	EEPROM_Start();

	/***********Iniciacion de variables***************/
	lado1.grado[0][0]=0;
	lado1.grado[1][0]=0;
	lado1.grado[2][0]=0;
	lado2.grado[0][0]=0;
	lado2.grado[1][0]=0;
	lado2.grado[2][0]=0;
    for(x=0; x<=15; x++){
        rventa1.id_ef[x]= 1;
    }

    CyDelay(5);
	/******************Lectura de EEPROM*************/
	
	for(x=13;x<=14;x++){									//Logo
		id_logo[x-13]=EEPROM_ReadByte(x);
	}
	lado1.mangueras=EEPROM_ReadByte(15);					//Numero de grados y codigo de cada uno 1
	lado1.grado[0][0]=EEPROM_ReadByte(16);
	lado1.grado[1][0]=EEPROM_ReadByte(17);
	lado1.grado[2][0]=EEPROM_ReadByte(18);
	
	lado2.mangueras=EEPROM_ReadByte(19);					//Numero de grados y codigo de cada uno 1
	lado2.grado[0][0]=EEPROM_ReadByte(20);
	lado2.grado[1][0]=EEPROM_ReadByte(21);
	lado2.grado[2][0]=EEPROM_ReadByte(22);	
	
	ppux10=EEPROM_ReadByte(23);								//PPU X10

	version[1]=EEPROM_ReadByte(30);							//Version de digitos y decimales
	version[2]=EEPROM_ReadByte(31);
	version[3]=EEPROM_ReadByte(32);
		 
	lado1.dir=EEPROM_ReadByte(26);							//Lado A

	lado2.dir=EEPROM_ReadByte(28);							//Lado B

    lado1.estado=libre;
    lado2.estado=libre;
    estado_tanqueando=0;
	//ppux10=1;//1 estacion autogas prueba version de digitos 6
	lado1.mangueras=3;
//	lado1.grado[0][0]=2;				//1 Diesel 2 Corriente 3 Extra 4 Supreme Diesel
//	lado1.grado[1][0]=3;
//	lado1.grado[2][0]=0;
    //version[1]=6;
	version[2]=0;
	version[3]=3;
    CyDelay(5);	
    
}


/*
*********************************************************************************************************
*                             uint8 verificar_check(uint8 *datos, uint16 size)
*
* Description : calcula el checksum
*               

*********************************************************************************************************
*/
uint8 verificar_check(uint8 *datos, uint16 size){
	uint8 checksum,index;
	uint16 i;
    uint8 table[256] = { 
    0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
    35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
    190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
    70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
    219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
    17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
    50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
    87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};	
	checksum=0;
	for(i=0;i<(size-1);i++){
		index = (uint8)(checksum ^ datos[i]);
		checksum = table[index];				
	}
	return checksum;
}

/*
************************************************************************************************************
*                                         void error_op()
*
* Description : Muestra en la pantalla el mensaje de operación incorrecta y regresa al inicio del Flujo LCD
*               
*
* Argument(s) : uint8 lcd, para elegir cual pantalla entra en esta función
*
* Return(s)   : none
*
* Caller(s)   : Desde cualquier momento de la operacion donde ocurra un error por parte del usuario
*
* Note(s)     : none.
************************************************************************************************************
*/
void error_op(uint8 lcd, uint16 imagen){
	if(lcd==1){
	   set_imagen(1,imagen);
	   flujo_LCD1=100;
	   count_protector=1;
       lado1.estado=libre;       
	   isr_3_StartEx(animacion);  
	   Timer_Animacion_Start();
	}
	else{
	    set_imagen(2,imagen);
	    flujo_LCD2=100;
		count_protector2=1;
	    isr_4_StartEx(animacion2);  
	    Timer_Animacion2_Start();	
	}
}

/*
*********************************************************************************************************
*                                         init_surt( void )
*
* Description : Busca las posiciones del surtidor y las graba en lado.a.dir y lado.b.dir
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : main()
*
* Note(s)     : Falta generar codigo para los casos 1 y 2
*********************************************************************************************************
*/
void init_surt(void){
	uint8 estado, ok=0;
	while(ok!=2){
		ok=0;
		if((lado1.dir==0xFF)||(lado2.dir==0xFF)){
			while(ver_pos()==0){};
		    while(totales(lado1.dir, lado1.mangueras)==0);			
			CyDelay(50);	
			while(totales(lado2.dir, lado2.mangueras)==0);
			CyDelay(50);	
			if(EEPROM_WriteByte(lado1.dir, 26)==CYRET_SUCCESS){
				set_imagen(1,60);								
			}
			else{
				set_imagen(1,85);
			}
			if(EEPROM_WriteByte(lado2.dir, 28)==CYRET_SUCCESS){
				set_imagen(2,60);								
			}
			else{
				set_imagen(2,85);
			}
			flujo_LCD2=0;
			flujo_LCD1=0;			
			ok=2;	
		}
		else{
			estado=get_estado(lado1.dir);										
			switch(estado){
		         case 0:                     
					lado1.dir=0xFF;
				 break;	
			
				case 0x06:
					venta(lado1.dir);
					CyDelay(50);	
					totales(lado1.dir, lado1.mangueras);
					CyDelay(50);	
					flujo_LCD1=0;					
					ok++;
				break;
					
				case 0x07:	
					totales(lado1.dir, lado1.mangueras);
					CyDelay(50);	
					flujo_LCD1=0;					
					ok++;
				break;
				
				case 0x08:
			     	flujo_LCD1=11;
					ok++;
				break;
					
				case 0x09:
			     	flujo_LCD1=11;
					ok++;
				break;
				
		         case 0x0B:                     //Termino venta
					flujo_LCD1=12;
					ok++;
				 break;	
					
		         case 0x0A:						//Termino venta
					flujo_LCD1=12;
					ok++;
				 break;
					
		         case 0x0C:						//Bloqueado por surtiendo al iniciar
			     	flujo_LCD1=11;
				 	set_imagen(1,8);
					ok++;
				 break;					
					
			}
			estado=get_estado(lado2.dir);										
			switch(estado){
		         case 0:                     
					lado2.dir=0xFF;
				 break;	
			
				case 0x06:
					venta(lado2.dir);
					CyDelay(50);		
					totales(lado2.dir, lado2.mangueras);
					CyDelay(50);	
					flujo_LCD2=0;				
					ok++;
				break;
					
				case 0x07:	
					totales(lado2.dir, lado2.mangueras);
					CyDelay(50);	
					flujo_LCD2=0;					
					ok++;
				break;
				
				case 0x08:
			     	flujo_LCD2=11;
				 	set_imagen(2,8);
					ok++;
				break;
					
				case 0x09:
			     	flujo_LCD2=11;
				 	set_imagen(2,8);
					ok++;
				break;
				
		         case 0x0B:                     //Termino venta
					flujo_LCD2=12;
					ok++;
				 break;	
					
		         case 0x0A:						//Termino venta
					flujo_LCD2=12;
					ok++;
				 break;
					
		         case 0x0C:						//Bloqueado por surtiendo al iniciar
			     	flujo_LCD2=11;
				 	set_imagen(2,8);
					ok++;
				 break;										
			}			
		}
	}
}

/*
*********************************************************************************************************
*                                         uint8 polling_rf(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
void polling_rf(void){
	uint16 status1, status2,size,x,t_preset;
	uint8  precio[5],preset[8];
    
	if(PC_GetRxBufferSize()>=3){
		status1=PC_GetRxBufferSize();
		CyDelay(10);
		status2=PC_GetRxBufferSize();
		if(status1==status2){		
			if((PC_rxBuffer[0]=='B')&&(PC_rxBuffer[1]=='B')&&(PC_rxBuffer[2]=='B')){
				ok_datosRF=0;   
				switch(PC_rxBuffer[3]){
					case cautorizar:
                    PC_rxBuffer[3] = 0;
						if(PC_rxBuffer[5]=='N'){			//No autorizo el servidor		
							error_op((PC_rxBuffer[4] & 0x0F),28);
							break;
						}
						if(PC_rxBuffer[10]=='F'){		//Cambia precio
                            precio[0]=lado1.ppu[rventa1.manguera-1][0]&0x0f;	
    						precio[1]=lado1.ppu[rventa1.manguera-1][1]&0x0f;
    						precio[2]=lado1.ppu[rventa1.manguera-1][2]&0x0f;
    						precio[3]=lado1.ppu[rventa1.manguera-1][3]&0x0f;
    						precio[4]=lado1.ppu[rventa1.manguera-1][4]&0x0f;
                        	if(cambiar_precio((lado1.dir & 0x0F),precio,rventa1.manguera)==0){
								rf_mod[0]='M';
								rf_mod[1]='U';
								rf_mod[2]='X';
								rf_mod[3]=creset;
								rf_mod[4]=cautorizar;
								rf_mod[5]=PC_rxBuffer[4];
								rf_mod[6]='1';
								rf_mod[7]='*';
								size=8;
								ok_datosRF=1;
								break;
							}                                                      
  						}
                        else{
							totales(lado1.dir, lado1.mangueras);
                            if(ppux10==1){
    							precio[4]=PC_rxBuffer[9];	
    							precio[3]=PC_rxBuffer[8];
    							precio[2]=PC_rxBuffer[7];
    							precio[1]=PC_rxBuffer[6];
    							precio[0]=0;			
                            }
                            if(ppux10==0){
    							precio[4]=PC_rxBuffer[10];	
    							precio[3]=PC_rxBuffer[9];
    							precio[2]=PC_rxBuffer[8];
    							precio[1]=PC_rxBuffer[7];
    							precio[0]=PC_rxBuffer[6];                            
                            }
							if(cambiar_precio((lado1.dir & 0x0F),precio,rventa1.manguera)==0){
								rf_mod[0]='M';
								rf_mod[1]='U';
								rf_mod[2]='X';
								rf_mod[3]=creset;
								rf_mod[4]=cautorizar;
								rf_mod[5]=PC_rxBuffer[4];
								rf_mod[6]='1';
								rf_mod[7]='*';
								size=8;
								ok_datosRF=1;
								break;
							}
                        }
						preset[1]=PC_rxBuffer[17];				//Preset
						if(PC_rxBuffer[17]!=','){
							preset[1]=PC_rxBuffer[17] & 0x0F;
						}
						preset[2]=PC_rxBuffer[16];
						if(PC_rxBuffer[16]!=','){
							preset[2]=PC_rxBuffer[16] & 0x0F;
						}
						preset[3]=PC_rxBuffer[15];
						if(PC_rxBuffer[15]!=','){
							preset[3]=PC_rxBuffer[15] & 0x0F;
						}
						preset[4]=PC_rxBuffer[14];
						if(PC_rxBuffer[14]!=','){
							preset[4]=PC_rxBuffer[14] & 0x0F;
						}
						preset[5]=PC_rxBuffer[13];
						if(PC_rxBuffer[13]!=','){
							preset[5]=PC_rxBuffer[13] & 0x0F;
						}
						preset[6]=PC_rxBuffer[12];
						if(PC_rxBuffer[12]!=','){
							preset[6]=PC_rxBuffer[12] & 0x0F;
						}
						preset[7]=PC_rxBuffer[11];
						if(PC_rxBuffer[11]!=','){
							preset[7]=PC_rxBuffer[11] & 0x0F;
						}
						t_preset=PC_rxBuffer[18];
						if(t_preset=='1'){
							t_preset=2;
						}
						else{
							t_preset=1;
						}
						if(programar((lado1.dir & 0x0F),rventa1.manguera,preset,t_preset)==1){		//Programar
                            if(ppuinicial==0){                          
//                                for(x=0;x<=4;x++){
//                            	    precio[x]=lado1.ppu[0][x];	    
//                                }
//                                cambiar_precio(lado1.dir,precio,1);    
//                                for(x=0;x<=4;x++){
//                            	    precio[x]=lado1.ppu[1][x];	    
//                                }    
//                                cambiar_precio(lado1.dir,precio,2);
//                                for(x=0;x<=4;x++){
//                            	    precio[x]=lado1.ppu[2][x];	    
//                                }
//                                cambiar_precio(lado1.dir,precio,3);       
                            }
                            CyDelay(10);
							Surtidor_PutChar(0x10|(lado1.dir & 0x0F));							
							lado1.estado=tanqueo;
							flujo_LCD1=8;
							set_imagen(1,8);
						}
						else{
							rf_mod[0]='M';
							rf_mod[1]='U';
							rf_mod[2]='X';
							rf_mod[3]=creset;
							rf_mod[4]=cautorizar;
							rf_mod[5]=PC_rxBuffer[4];
							rf_mod[6]='2';
							rf_mod[7]='*';
							size=8;
							ok_datosRF=1;							
						}
					break;
					
					case cimprimir:
						set_imagen(1,55);
                        if(PC_rxBuffer[5] =='2'){
                            lado1.estado=libre;
    						error_op(1,12);	
                        }											
					break;
					
					case creset:                                   
    						switch(PC_rxBuffer[5]){
    							case '1':														
    								lado1.estado=libre;
    								error_op(1,28);					 //Error de id					
    							break;
    								
    							case '2':
    								lado1.estado=libre;
    								error_op(1,12);					//Gracias por su compra
    							break;
    								
    							case '3':
    								lado1.estado=libre;
    								error_op(1,12);					//Error de Operacion //85
    							break;
    								
    							case '4':
//    								lado1.estado=libre;//
//    								error_op(1,12);		//			//Fin Corte
    							break;								
    								
    						}                        
					break;
				}
				if(ok_datosRF==1){
				    for(x=0;x<size;x++){
					   PC_PutChar(rf_mod[x]);
				    }	               
				}
			}
			PC_ClearRxBuffer();
            Surtidor_ClearRxBuffer();
			status1=0;
			status2=0;			
		}		
	}	
}

/*
*********************************************************************************************************
*                                         uint8 polling_surt(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/

void polling_surt(void){
	         
            
}



/*
*********************************************************************************************************
*                                         void polling_LCD1(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/

void polling_LCD1(void){
    uint8 x,y,aux[10],precio[5],x_1,xaux;
	char numero[8];
	double num_decimal;   
    switch(flujo_LCD1){
        case 0:
         isr_3_StartEx(animacion); 
         Timer_Animacion_Start();
         count_protector=0;
         flujo_LCD1=1;	       
        break;
        
        case 1:
         if(LCD_1_GetRxBufferSize()==8){ 
             isr_3_Stop(); 
             Timer_Animacion_Stop(); 
	         flujo_LCD1 = 2;
	         set_imagen(1,99);				//Muestra imagen de inicio GRP700
             LCD_1_ClearRxBuffer();				
         }
        break;
        
        case 2:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){                    
                    switch(LCD_1_rxBuffer[3]){
	                    case 0x5C:                                  //Venta							
							set_imagen(1,73);
                            flujo_LCD1 = 3;
	                    break;                
	                    
	                    case 0x45:								    //Otras opciones
                            set_imagen(1,114);
                            flujo_LCD1 = 15;
	                    break; 

	                    case 0x59:									//Corte
							set_imagen(1,57);
							rf_mod[0]='M';
							rf_mod[1]='U';
							rf_mod[2]='X';
							rf_mod[3]='2';
                			totales(lado1.dir, lado1.mangueras);
                			CyDelay(50);  
                            x_1=4;
                            for(x=0;x<=11;x++){     //volumen_pro1 
                                rf_mod[x_1]=(lado1.totales[0][x]&0X0F)+48;
                                x_1++;
                            }
                            for(x=12;x<=23;x++){    //dinero_pro1
                                rf_mod[x_1]=(lado1.totales[0][x]&0X0F)+48;
                                x_1++;
                            }           
                            for(x=0;x<=11;x++){     //volumen_pro2     
                                rf_mod[x_1]=(lado1.totales[1][x]&0X0F)+48;
                                x_1++;
                            }
                            for(x=12;x<=23;x++){    //dinero_pro2    
                                rf_mod[x_1]=(lado1.totales[1][x]&0X0F)+48;
                                x_1++;
                            }           
                            for(x=0;x<=11;x++){     //volumen_pro3   
                                rf_mod[x_1]=(lado1.totales[2][x]&0X0F)+48;
                                x_1++;
                            }
                            for(x=12;x<=23;x++){    //dinero_pro3    
                                rf_mod[x_1]=(lado1.totales[2][x]&0X0F)+48;
                                x_1++;
                            }
                            rf_mod[75]='*';                            
                            PC_ClearRxBuffer();
						    for(x=0;x<=75;x++){
							   PC_PutChar(rf_mod[x]);
						    }                                 
							CyDelay(250);                
							if(PC_GetRxBufferSize()>=2){

 							        set_imagen(1,74);
							        flujo_LCD1=0;
							        lado1.estado=libre;     //Fin de reimpresion                                         
                     
							}    
							PC_ClearRxBuffer();                                                                              
	                    break;					
						
	                    case 0x7E:									//ir a menu
						  set_imagen(1,74);	
	                      flujo_LCD1=0;     
	                    break;					
	                }
	            }
	            CyDelay(100);
	            LCD_1_ClearRxBuffer();
	        }				
		break;
            
         case 3:     
         if(LCD_1_GetRxBufferSize()==8){
            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
                switch(LCD_1_rxBuffer[3]){
                    case 0x5F:							//Sin ID	                                                                              
                      set_imagen(1,5);                 //Pasa a pantalla de tipo de venta 
                      tipo_venta = 0;
                      flujo_LCD1 = 4; 
                    break;
                    
                    case 0x5E:  						//Con ID                                         
                      set_imagen(1,18);
                      tipo_venta = 1;
                      flujo_LCD1 = 11;
                      id_teclado1 = 0;
                    break;	

                    case 0x7E:						    //ir a menu
					  set_imagen(1,74);	
                      flujo_LCD1 = 0;     
                    break;	
                    
                    case 0x94:
                        set_imagen(1,99); //Regreso a pantalla de opcion de venta
                        flujo_LCD1 = 1;
                    break;
                }
            }
            CyDelay(100);
            LCD_1_ClearRxBuffer();
        }        
        break;    
            
        case 4:
         if(LCD_1_GetRxBufferSize()==8){
            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
                switch(LCD_1_rxBuffer[3]){
                    case 0x0F:                               	//$
					  for(x=0;x<=7;x++){
					 	rventa1.preset[x]=0;
					  }					                      
					  count_teclas1=0;							//Inicia el contador de teclas	
					  id_teclado1=1;
					  id_coma1=',';	
                      teclas1=version[1]; 						//cantidad de teclas q puede digitar
					  rventa1.preset[0]=1;
                      comas1=0;									
                      set_imagen(1,6); 
					  posx1=4;
					  posy1=3;
					  sizeletra1=1;	
					  write_LCD(1,'$', 3, 4, 1);
                      flujo_LCD1 = 12; 
                    break;
                    
                    case 0x10: 									//G 
					  for(x=0;x<=7;x++){
					 	rventa1.preset[x]=0;
					  }						                      
					  count_teclas1=0;							//Inicia el contador de teclas	
					  id_teclado1=1;
					  id_coma1=',';	
                      teclas1=version[1]; 
					  rventa1.preset[0]=2;
                      comas1=0;									
                      set_imagen(1,13); 
					  posx1=4;
					  posy1=3;
					  sizeletra1=1;					
					  write_LCD(1,'G', 3, 4, 1);
                      flujo_LCD1=12; 
                    break;
                    
                    case 0x43:  								//Full 
					  for(x=0;x<=7;x++){
					 	rventa1.preset[x]=0;
					  }
                      rventa1.preset[0]=3;					
					  for(x=5;x<=7;x++){
						rventa1.preset[x]=9;		
					  }								                                     
		              set_imagen(1,7);
					  lado1.estado=espera;
                      flujo_LCD1 = 6;  
                    break;
                    
                    case 0x3B:                                //Cancel                     
                      flujo_LCD1=0;
                    break;     
                    
                    case 0x7E:                                //Símbolo de inicio                                        
                        set_imagen(1,74);	
                        flujo_LCD1=0;
                    break;
                }
            }
            CyDelay(100);            
            LCD_1_ClearRxBuffer();
         } 
        break;
        
        case 5:
		 CyDelay(50);
         if(LCD_1_GetRxBufferSize()==8){
            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
                if(LCD_1_rxBuffer[3]==0x7E){					//Cancel
					flujo_LCD1=0;
                }												
			}                       
            LCD_1_ClearRxBuffer();
			break;
		 }
         x=get_estado(lado1.dir);
         if(x==7){								//Espera a que este en listo el equipo	
			flujo_LCD1=6;
            CyDelay(50);
         }
         else if(x==0){
			CyDelay(50);
			programar(lado1.dir,1,aux,2);
         }
         else if(x==0x0C){
            error_op(1,85);
         }
		 else if(x==0x0B){                   //Termino venta
			flujo_LCD1=13;
         }						
		 else if(x==0x0A){					//Termino venta
			flujo_LCD1=13;
		 }        
        break;
        
        case 6:
		 CyDelay(10);
		 rventa1.manguera=estado_ex(lado1.dir);
		 if(rventa1.manguera!=0){			 
            CyDelay(20);            
		    if(get_estado(lado1.dir)==7){     			    
                timeout_autorizacion=0;
			    lado1.estado=listo;
                set_imagen(1,57);                                
                flujo_LCD1 = 9;
		    }
		 }
		break;
        
        case 8:        
		 CyDelay(50);
		 switch(get_estado(lado1.dir)){
	         case 0x0B:                     //Termino venta
				CyDelay(100);
				for(x=0;x<=8;x++){
					rventa1.dinero[x]=0;
					rventa1.volumen[x]=0;
				}					
				if(venta(lado1.dir)==1){
					flujo_LCD1 = 13;
					set_imagen(1,57);
				}	
			 break;	
				
	         case 0x0A:						//Termino venta
				for(x=0;x<=8;x++){
					rventa1.dinero[x]=0;
					rventa1.volumen[x]=0;
				}				
				if(venta(lado1.dir)==1){
					flujo_LCD1 = 13;
					set_imagen(1,57);
				}	
			 break;

	         case 0x06:                     //No hizo venta
				for(x=0;x<=8;x++){
					rventa1.dinero[x]=0;
					rventa1.volumen[x]=0;
				}
				for(x=0;x<=4;x++){
					rventa1.ppu[x]=0;
				}				
				flujo_LCD1 = 13;
				set_imagen(1,57);		
			 break;				 	
         }		 	
		break;
        
        case 9:
			rf_mod[0]='M';
			rf_mod[1]='U';
			rf_mod[2]='X';
			rf_mod[3]='0';
            if (tipo_venta == 1){
			    for(x=0;x<=15;x++){						//Serial				
				    y=(rventa1.id[x/2]>>4)&0x0F;
				    if((x%2)==0){
					    y=rventa1.id[x/2]&0x0F;
				    }
				    rf_mod[x+4] = y+48;
				    if(y>9){
					    rf_mod[x+4] = y+55;
				    }
			    }
            }
            if(tipo_venta == 0){
                for(x=0;x<=15;x++){						//Serial efectivo				
				    y=(rventa1.id_ef[x])&0x0F;
                    rf_mod[x+4] = y+48;
				    if((x%2)==0){
					    y=rventa1.id_ef[x]&0x0F;
				    }				    
				    if(y>9){
					    rf_mod[x+4] = y+55;
				    }
                }
            }
			rf_mod[20]=(lado1.grado[rventa1.manguera-1][0])+48;			//Id Producto					
			rf_mod[21]= id_estacion[4];								    //Id Estación
			rf_mod[22]= id_estacion[3];
			rf_mod[23]= id_estacion[2];
			rf_mod[24]= id_estacion[1];        			
            if(ppux10==0){
    			rf_mod[25]=(lado1.ppu[rventa1.manguera-1][4]&0x0F)+0x30;		//PPU
    			rf_mod[26]=(lado1.ppu[rventa1.manguera-1][3]&0x0F)+0x30;
    			rf_mod[27]=(lado1.ppu[rventa1.manguera-1][2]&0x0F)+0x30;
    			rf_mod[28]=(lado1.ppu[rventa1.manguera-1][1]&0x0F)+0x30;
    			rf_mod[29]=(lado1.ppu[rventa1.manguera-1][0]&0x0F)+0x30;
            }
            if(ppux10==1){
    			rf_mod[25]=(lado1.ppu[rventa1.manguera-1][3]&0x0F)+0x30;		//PPUx10
    			rf_mod[26]=(lado1.ppu[rventa1.manguera-1][2]&0x0F)+0x30;
    			rf_mod[27]=(lado1.ppu[rventa1.manguera-1][1]&0x0F)+0x30;
    			rf_mod[28]=(lado1.ppu[rventa1.manguera-1][0]&0x0F)+0x30;
    			rf_mod[29]=0x30;   
            }
			rf_mod[30]=(rventa1.preset[0]+48);								//Tipo de Preset
			rf_mod[31]=rventa1.preset[7];									//Preset
			if(rventa1.preset[7]<10){				
				rf_mod[31]=rventa1.preset[7]+0x30;							
			}
			rf_mod[32]=rventa1.preset[6];
			if(rventa1.preset[6]<10){				
				rf_mod[32]=rventa1.preset[6]+0x30;
			}
			rf_mod[33]=rventa1.preset[5];
			if(rventa1.preset[5]<10){				
				rf_mod[33]=rventa1.preset[5]+0x30;
			}
			rf_mod[34]=rventa1.preset[4];
			if(rventa1.preset[4]<10){				
				rf_mod[34]=rventa1.preset[4]+0x30;
			}
			rf_mod[35]=rventa1.preset[3];
			if(rventa1.preset[3]<10){				
				rf_mod[35]=rventa1.preset[3]+0x30;
			}
			rf_mod[36]=rventa1.preset[2];
			if(rventa1.preset[2]<10){				
				rf_mod[36]=rventa1.preset[2]+0x30;
			}
			rf_mod[37]=rventa1.preset[1];
			if(rventa1.preset[1]<10){				
				rf_mod[37]=rventa1.preset[1]+0x30;
			}
			for(x=0;x<=6;x++){
				rf_mod[38+x]=rventa1.km[x+1] + 48;
			}
			rf_mod[45]=0x31;
			rf_mod[46]='*';
			PC_ClearRxBuffer();				
		    for(x=0;x<=46;x++){
			   PC_PutChar(rf_mod[x]);
		    }	            
			CyDelay(350);			
            PC_ClearTxBuffer();
		break;
            
        
            
        case 11:         
            if(touch_present(1)==1){
                if(touch_write(1,0x33)){
	                for(x=0;x<=7;x++){
	                    rventa1.id[x]=touch_read_byte(1);
	                }
				    crc_total=0;
				    for(x=0;x<7;x++){
				 	    crc_total=crc_check(crc_total,rventa1.id[x]);
				    }					
				    if(crc_total==rventa1.id[7]){
		                set_imagen(1,19);
		                CyDelay(500);					 				 
					    count_teclas1=0;							//Inicia el contador de teclas						    
					    teclas1=10;
					    posx1=2;
					    posy1=3;
					    sizeletra1=1;	                        
                        if(id_teclado1 ==10){
                            set_imagen(1,19);
                            flujo_LCD1 = 19;
                        }else{
                            id_teclado1=2;
                            set_imagen(1,14);
                            flujo_LCD1=12;
                        }
					    	
				    }
                }
            }        
            if(LCD_1_GetRxBufferSize()==8){
                if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
                    switch(LCD_1_rxBuffer[3]){
                        case 0x3B:
                            flujo_LCD1=0; 
                        break; 
                    }
                }
                CyDelay(100);            
                LCD_1_ClearRxBuffer();            
        }		
		break;
        
        
        case 12: 
         if(LCD_1_GetRxBufferSize()==8){
            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
				count_protector=0;
                if(count_teclas1<teclas1){									
                    if(LCD_1_rxBuffer[3]<=9){								//Numero de 1-9
                        count_teclas1++;
                        Buffer_LCD1[count_teclas1]=LCD_1_rxBuffer[3];
                        write_LCD(1,(LCD_1_rxBuffer[3]+0x30), posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
                    }
                    if(LCD_1_rxBuffer[3]==0x0A){            				//Comando de 0
						if((id_teclado1==1)&&(count_teclas1==1)&&(Buffer_LCD1[1]==0)){
						}
						else{
	                        count_teclas1++;
	                        Buffer_LCD1[count_teclas1]=0;
							write_LCD(1,0x30, posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
						}
                    }  
                    if(LCD_1_rxBuffer[3]==0x51){            	 			//Comando de Coma
                        if(count_teclas1>=1 && comas1==0){
                            count_teclas1++;
                            Buffer_LCD1[count_teclas1]=id_coma1;
							write_LCD(1,id_coma1, posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
                            comas1=1;
                        }
                    }                    
                }
                if(LCD_1_rxBuffer[3]==0x0B){								//Cancel
                    if(count_teclas1==0){
						switch(id_teclado1){
							case 1:
							set_imagen(1,5);
							flujo_LCD1=4;
							break;
							case 2:
	                        flujo_LCD1=0;	
							break;
							case 3:
							set_imagen(1,0);
							flujo_LCD1=0;
							lado1.estado=libre;
							break;
							case 4:
							set_imagen(1,0);
							flujo_LCD1=0;
							lado1.estado=libre;
							break;
                            case 5:
							set_imagen(1,0);
							flujo_LCD1=0;
							lado1.estado=libre;                            
                            break;
                            case 6:
							set_imagen(1,0);
							flujo_LCD1=0;
							lado1.estado=libre;                            
                            break;  
                            case 8:
							set_imagen(1,0);
							flujo_LCD1 = 0;
							lado1.estado=libre;                            
                            break;                             
						}
                    }
                    else{
						write_LCD(1,0x20, posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
                        if(Buffer_LCD1[count_teclas1]==id_coma1){
                            comas1=0;
                        }
						Buffer_LCD1[count_teclas1]=0;
                        count_teclas1--;
                    }
                }
                if(LCD_1_rxBuffer[3]==0x0C){								//Enter
					switch(id_teclado1){
						case 1:
							for(x=0;x<=7;x++){
								numero[x]=0;
							}						
							if((count_teclas1>=1)&&(Buffer_LCD1[count_teclas1]!=',')){
								for(x=1;x<=count_teclas1;x++){
									if(Buffer_LCD1[x]!=','){
										numero[x-1]=Buffer_LCD1[x]+48;
									}
									else{
										numero[x-1]=Buffer_LCD1[x];
									}
								}
								num_decimal=atof(numero);
								if(((rventa1.preset[0]==1)&&(num_decimal>=800))||((rventa1.preset[0]==2)&&(num_decimal<=900)&&(num_decimal>0))){
									for(x=count_teclas1;x>=1;x--){
										rventa1.preset[x]=Buffer_LCD1[(count_teclas1-x)+1];
									}
									flujo_LCD1=5;								
                         			lado1.estado=espera;
						            set_imagen(1,7);
								}
							}
						break;
						case 2:	
                            set_imagen(1,5);
                            for(x=0;x<=10;x++){
                              rventa1.km[x]=0;
                            }
							for(x=count_teclas1;x>=1;x--){
								rventa1.km[x]=Buffer_LCD1[(count_teclas1-x)+1];
							}
	                        flujo_LCD1=4;		                        
						break;
						case 3:
							for(x=count_teclas1;x>=1;x--){
								rventa1.cedula[x]=Buffer_LCD1[(count_teclas1-x)+1]+48;
							}
                        	flujo_LCD1=2;	
                        	set_imagen(1,5);
							count_teclas1=0;
							id_teclado1=4;
							teclas1=10;
							posx1=2;
							posy1=3;
							sizeletra1=1;								
						break;
						case 4:
							for(x=count_teclas1;x>=1;x--){
								rventa1.password[x]=Buffer_LCD1[(count_teclas1-x)+1]+48;
							}
                        	flujo_LCD1=102;	
                        	set_imagen(1,57);
							lado1.estado=16;
						break;	
                        case 5:
							for(x=count_teclas1;x>=1;x--){
								rventa1.password_local[x]=Buffer_LCD1[(count_teclas1-x)+1]+48;
							}
                            if(clave_local[0]==rventa1.password_local[4] && clave_local[1]==rventa1.password_local[3] && clave_local[2]==rventa1.password_local[2] && clave_local[3]==rventa1.password_local[1]){                        	    	
                        	    set_imagen(1,38); 
                                CyDelay(200);
							    set_imagen(1,70);  
                                flujo_LCD1 = 16;
                            }else{
                        	    flujo_LCD1=0;	
                        	    set_imagen(1,39); 
							    lado1.estado=libre;                                 
                                CyDelay(200);
							    set_imagen(1,0);                                 
                            }
                        break; 
                        case 6:                        
						    EEPROM_WriteByte(Buffer_LCD1[count_teclas1],30);
                        	flujo_LCD1 = 0;	
                        	set_imagen(1,60);
                            CyDelay(200);
							lado1.estado=libre;                                                     
                        break;   
                        case 7:
                            flujo_LCD1=18;
                            set_imagen(1,88);
                            switch(Producto){
                                case 1:// 1=diesel, siempre para Autogas, 
                                    Productos[0]=Buffer_LCD1[1]+48;//para la estacion seria el digitado por ellos
                                    switch(Productos[0]){
                                        case '1':
                                        lado1.grado[0][0]=1;                                        
                                        break;
                                        case '2':
                                        lado1.grado[1][0]=1;                                        
                                        break;
                                        case '3':
                                        lado1.grado[2][0]=1;                                        
                                        break;                    
                                        default:
                                        producto1 = 0;
                                        break;
                                    }                                   
                                break;
                                case 2:// 2=corriente, siempre para Autogas,
                                    Productos[1]=Buffer_LCD1[1]+48;
                                    switch(Productos[1]){
                                        case '1':
                                        lado1.grado[0][0]=2;                                        
                                        break;
                                        case '2':
                                        lado1.grado[1][0]=2;                                        
                                        break;
                                        case '3':
                                        lado1.grado[2][0]=2;                                        
                                        break; 
                                        default:
                                        producto2=0;
                                        break;                                        
                                    }                                      
                                break;
                                case 3:// 3=extra, siempre para Autogas,
                                    Productos[2]=Buffer_LCD1[1]+48;
                                    switch(Productos[2]){
                                        case '1':
                                        lado1.grado[0][0]=3;                                        
                                        break;
                                        case '2':
                                        lado1.grado[1][0]=3;                                        
                                        break;
                                        case '3':
                                        lado1.grado[2][0]=3;                                        
                                        break; 
                                        default:
                                        producto3=0;
                                        break;                                        
                                    }                                      
                                break;
                                case 4:// 4=supreme diesel, siempre para Autogas,
                                    Productos[3]=Buffer_LCD1[1]+48;
                                    switch(Productos[3]){
                                        case '1':
                                        lado1.grado[0][0]=4;                                        
                                        break;
                                        case '2':
                                        lado1.grado[1][0]=4;                                        
                                        break;
                                        case '3':
                                        lado1.grado[2][0]=4;                                        
                                        break;
                                        default:
                                        producto4=0;
                                        break;                                      
                                    }                                      
                                break;                                    
                            }
                            write_LCD(1,Productos[0], 7, 44, 1);
                            write_LCD(1,Productos[1], 14, 44, 1); 
                            write_LCD(1,Productos[2], 19, 44, 1);
                            write_LCD(1,Productos[3], 25, 44, 1); 
							lado1.estado=libre;                                 
                            CyDelay(200);                             
                        break;          
                        case 8:
                            for(x=1;x<=4;x++){
                              id_estacion[x]=0;
                            }
                            id_estacion[0]=4;
							for(x=count_teclas1;x>=1;x--){
								id_estacion[x]=Buffer_LCD1[(count_teclas1-x)+1]+0X30;
							}                            
                            if(id_estacion[1]>=0x30 && id_estacion[2]<0x30 && id_estacion[3]<0x30 && id_estacion[4]<0x30){
                                id_estacion[2]='0';
                                id_estacion[3]='0';
                                id_estacion[4]='0';                                
                            }
                            if(id_estacion[1]>=0x30 && id_estacion[2]>=0x30 && id_estacion[3]<0x30 && id_estacion[4]<0x30){
                                id_estacion[3]='0';
                                id_estacion[4]='0';                             
                            }  
                            if(id_estacion[1]>=0x30 && id_estacion[2]>=0x30 && id_estacion[3]>=0x30 && id_estacion[4]<0x30){
                                id_estacion[4]='0';                              
                            }
                    		for(x=8;x<=12;x++){	
                    			EEPROM_WriteByte(id_estacion[x-8], x);
                    		}   
                        	flujo_LCD1 = 0;	
                        	set_imagen(1,60);
                            CyDelay(200);
							lado1.estado=libre;                                    
                        break;
					}					
                }
            }
            //CyDelay(100);            
            LCD_1_ClearRxBuffer();
         }
//		 if((count_protector>=30)&&(rventa1.tipo_venta==0)&&(id_teclado1==2)){
//			count_teclas1=0;
//			teclas1=7;
//			posx1=4;
//			posy1=3;
//			sizeletra1=1;				
//			set_imagen(1,10);
//			flujo_LCD1=13;
//			count_protector=0;
//		 }		
        break;	
            
        case 13:      
			rf_mod[0]='M';
			rf_mod[1]='U';
			rf_mod[2]='X';
			rf_mod[3]='1';
			rf_mod[4]=1 + 48;								//Cara
			rf_mod[5]=(lado1.grado[rventa1.producto-1][0] + 48);	//Id Producto	
			rf_mod[6]=rventa1.volumen[5] + 48;						//Volumen
			rf_mod[7]=rventa1.volumen[4] + 48;
			rf_mod[8]=rventa1.volumen[3] + 48;
			rf_mod[9]=',';
			rf_mod[10]=rventa1.volumen[2] + 48;
			rf_mod[11]=rventa1.volumen[1] + 48;
			rf_mod[12]=rventa1.volumen[0] + 48;
			if(version[1]==7){
				rf_mod[13]=rventa1.dinero[7] + 48;	//Dinero 7 digitos
				rf_mod[14]=rventa1.dinero[6] + 48;
				rf_mod[15]=rventa1.dinero[5] + 48;
				rf_mod[16]=rventa1.dinero[4] + 48;
				rf_mod[17]=rventa1.dinero[3] + 48;
				rf_mod[18]=rventa1.dinero[2] + 48;
				rf_mod[19]=rventa1.dinero[1] + 48;					
			}
			else{
				rf_mod[13]=rventa1.dinero[6] + 48;	//Dinero 6 digitos 
				rf_mod[14]=rventa1.dinero[5] + 48;
				rf_mod[15]=rventa1.dinero[4] + 48;
				rf_mod[16]=rventa1.dinero[3] + 48;
				rf_mod[17]=rventa1.dinero[2] + 48;
				rf_mod[18]=rventa1.dinero[1] + 48;					
				rf_mod[19]=rventa1.dinero[0] + 48;
			}
            if(ppux10==0){
    			rf_mod[20]=rventa1.ppu[4] + 48;			//PPU
    			rf_mod[21]=rventa1.ppu[3] + 48;
    			rf_mod[22]=rventa1.ppu[2] + 48;
    			rf_mod[23]=rventa1.ppu[1] + 48;
    			rf_mod[24]=rventa1.ppu[0] + 48;
            }
            if(ppux10==1){
    			rf_mod[20]=rventa1.ppu[3] + 48;			//PPU x10
    			rf_mod[21]=rventa1.ppu[2] + 48;
    			rf_mod[22]=rventa1.ppu[1] + 48;
    			rf_mod[23]=rventa1.ppu[0] + 48;
    			rf_mod[24]=48;
            }
			rf_mod[25]=id_estacion[4];				//Id Estacion	
			rf_mod[26]=id_estacion[3];
			rf_mod[27]=id_estacion[2];
			rf_mod[28]=id_estacion[1];
			
            if(tipo_venta == 1){
                for(x=0;x<=15;x++){						//Serial				
				    y=(rventa1.id[x/2]>>4)&0x0F;
				    if((x%2)==0){
					    y=rventa1.id[x/2]&0x0F;
				    }
				    rf_mod[x+29] = y+48;
				    if(y>9){
					    rf_mod[x+29] = y+55;
				    }
			    }
            }else{
                for(x=0;x<=15;x++){						//Serial efectivo				
				    y=(rventa1.id[x])&0x0F;
				    if((x%2)==0){
					    y=rventa1.id[x]&0x0F;
				    }
				    rf_mod[x+29] = y+48;
				    if(y>9){
					    rf_mod[x+29] = y+55;
				    }
			    }                
            }
			num_decimal2++;
			id_venta[4]=(num_decimal2/1000)+48;
			id_venta[3]=((num_decimal2%1000)/100)+48;
			id_venta[2]=(((num_decimal2%1000)%100)/10)+48;
			id_venta[1]=(((num_decimal2%1000)%100)%10)+48; 
			for(x=1;x<=7;x++){						//Id de Venta
				rf_mod[44+x]=id_venta[x];
			}
			for(x=1;x<=4;x++){						//Guarda Id venta
				EEPROM_WriteByte(id_venta[x],x);
			}
			for(x=0;x<=6;x++){						//Km
				rf_mod[52+x]=rventa1.km[x+1] + 48;
			}				
			rf_mod[59]='*';
			PC_ClearRxBuffer();				
		    for(x=0;x<=59;x++){
			   PC_PutChar(rf_mod[x]);
		    }            
            PC_ClearRxBuffer();
			CyDelay(300);
            PC_ClearTxBuffer();
//			if(PC_GetRxBufferSize()>=2){
//				if((PC_rxBuffer[0]=='B') && (PC_rxBuffer[1]=='B')){
//					lado1.estado=espera;				
            estado_tanqueando=0;
            //
//				}
				
				precio[0]=lado1.ppu[rventa1.producto-1][0];
				precio[1]=lado1.ppu[rventa1.producto-1][1];
				precio[2]=lado1.ppu[rventa1.producto-1][2];
				precio[3]=lado1.ppu[rventa1.producto-1][3];
				precio[4]=lado1.ppu[rventa1.producto-1][4];
				cambiar_precio(lado1.dir,precio,rventa1.producto);
//			}  
		break;
         
        case 14:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
	                if(count_teclas1<teclas1){
	                    if(LCD_1_rxBuffer[3]<=9){
	                        rventa1.password[count_teclas1+1]=LCD_1_rxBuffer[3]+0x30;
	                        write_LCD(1,'*', posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
	                        count_teclas1++;                        
	                    }
	                    if(LCD_1_rxBuffer[3]==0x0A){            //Comando de 0
	                        rventa1.password[count_teclas1+1]=0x30;
	                        write_LCD(1,'*', posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
	                        count_teclas1++;                        
	                    }                    
	                }
	                if(LCD_1_rxBuffer[3]==0x0B){                //Cancelar      
	                    if(teclas1==0){
	                        flujo_LCD1=0;
	                    }
	                    else{
	                        count_teclas1--;                                        
	                        write_LCD(1,0x20, posy1, ((count_teclas1*(sizeletra1+1))+posx1), sizeletra1);
	                    }
	                }
	                if(LCD_1_rxBuffer[3]==0x0C){                //Enter
	                    if(count_teclas1>=1){
	                        rventa1.password[0]=count_teclas1;
							y=0;
							if(rventa1.password[0]==4){
								for(x=1;x<=4;x++){
									if(rventa1.password[x]==clave_config[x]){
										y++;
									}
								}
								if(y==4){
			                        flujo_LCD1=15;
			                        set_imagen(1,93);								
								}
								else{
			                        flujo_LCD1=0;							
								}
							}
							else{
		                        flujo_LCD1=0;						
							}
	                    }
	                }
	            }
	            CyDelay(100);            
	            LCD_1_ClearRxBuffer();
	        }         			
		break;
            
        case 15:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
	                switch(LCD_1_rxBuffer[3]){
                        case 0xB9: //Reimpresion
                        	rf_mod[0]='M';
			                rf_mod[1]='U';
			                rf_mod[2]='X';
			                rf_mod[3]='3';
                            rf_mod[4]='*';
							PC_ClearRxBuffer();				
						    for(x=0;x<=4;x++){
							   PC_PutChar(rf_mod[x]);
						    }
                            CyDelay(150);  
							set_imagen(1,0);
							flujo_LCD1=0;
							lado1.estado=libre;     //Fin de reimpresion                                                                                                        
                        break;
                            
                        case 0xBA:                                       //Configuracion inicial                             
                            set_imagen(1,47);
                            id_teclado1=5;
					        count_teclas1=0;							 //Inicia el contador de teclas	
					        id_coma1=',';	
                            teclas1=4;              						//cantidad de teclas q puede digitar                      comas1=0;									
					        posx1=4;
					        posy1=3;
					        sizeletra1 = 1;	    
                            flujo_LCD1 = 12;
                        break;    
                            
	                    case 0x7E:					//ir a menu
						  set_imagen(1,74);	
	                      flujo_LCD1=0;     
	                    break;		                            
                    }
                }
            }
        break;
              
        case 16:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
	                switch(LCD_1_rxBuffer[3]){
                        case 0x7F:      //configurar productos                            
                            set_imagen(1,88);                            
                            flujo_LCD1 = 18;
                        break;
                        case 0x80:      //configurar version de digitos                             
                            set_imagen(1,100);
                            id_teclado1 = 6;
					        count_teclas1 = 0;							    //Inicia el contador de teclas	
					        id_coma1=',';	
                            teclas1=1;              						//cantidad de teclas q puede digitar                      comas1=0;									
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;  
                            flujo_LCD1 = 12;
                        break;
                        case 0x81:      //configurar ppux10,ppux1
                            flujo_LCD1 = 17;
                            set_imagen(1,109);                        
                        break;
                        case 0xC2:      //id estacion   ahora datos ibutton                         
                            set_imagen(1,110);                                
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;            
                            flujo_LCD1 = 11;
                            id_teclado1 = 10;
                        break;                             
	                    case 0x7E:		//ir a menu
						  set_imagen(1,74);	
	                      flujo_LCD1=0;     
	                    break;                                   
                    }
                }
                CyDelay(100);            
	            LCD_1_ClearRxBuffer();
            }            
        break;    
            
        case 17:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
	                switch(LCD_1_rxBuffer[3]){
                        case 0x8f:  //X1
						    EEPROM_WriteByte(0x00,23);
                        	flujo_LCD1 = 0;	
                        	set_imagen(1,60);
                            CyDelay(200);
							lado1.estado=libre;                          
                        break;
                        case 0x90:  //X10
						    EEPROM_WriteByte(0x01,23);
                        	flujo_LCD1=0;	
                        	set_imagen(1,60);
                            CyDelay(200);
							lado1.estado=libre;                           
                        break;
	                    case 0x7E:	//ir a menu
						  set_imagen(1,74);	
	                      flujo_LCD1=0;     
	                    break;                         
                    }
                }
                CyDelay(100);            
	            LCD_1_ClearRxBuffer();
            }              
        break;    
          
        case 18:
	        if(LCD_1_GetRxBufferSize()==8){
	            if((LCD_1_rxBuffer[0]==0xAA) && (LCD_1_rxBuffer[6]==0xC3) && (LCD_1_rxBuffer[7]==0x3C)){
	                switch(LCD_1_rxBuffer[3]){
                        case 0x80:  //Producto 1
                            Producto=1;                                                    
                            set_imagen(1,6);  
                            id_teclado1=7;
					        count_teclas1=0;							    //Inicia el contador de teclas	
					        id_coma1=',';	
                            teclas1=1;              						//cantidad de teclas q puede digitar                      comas1=0;									
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;  
                            flujo_LCD1 = 12;
                        break;
                        case 0x81:  //Producto 2
                            Producto=2;                                                    
                            set_imagen(1,6);  
                            id_teclado1=7;
					        count_teclas1=0;							    	
					        id_coma1=',';	
                            teclas1=1;              															
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;  
                            flujo_LCD1 = 12;
                        break;                            
                        case 0x7F:  //Producto 3
                            Producto=3;                                                    
                            set_imagen(1,6);  
                            id_teclado1=7;
					        count_teclas1=0;							    
					        id_coma1=',';	
                            teclas1=1;              													
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;                      
                            flujo_LCD1 = 12;
                        break;                            
                        case 0x82:  //Producto 4
                            Producto=4;                                                   
                            set_imagen(1,6);  
                            id_teclado1=7;
					        count_teclas1=0;							    	
					        id_coma1=',';	
                            teclas1=1;              														
					        posx1=4;
					        posy1=3;
					        sizeletra1=1;        
                            flujo_LCD1 = 12;
                        break;                     
	                    case 0x7E:	//Envía datos al Beagle de productos 
                        	rf_mod[0]='M';
			                rf_mod[1]='U';
			                rf_mod[2]='X';
			                rf_mod[3]='4'; 
                            y=4;
                            for(x=0;x<=2;x++){
                                switch(lado1.grado[x][0]){
                                	case 1:
                                		rf_mod[y]='1';//Diesel
                                	break;
                                	case 2:
                                		rf_mod[y]='2';//Corriente
                                	break;
                                	case 3:
                                		rf_mod[y]='3';//Extra
                                	break;
                                	case 4:
                                		rf_mod[y]='4';//Supremo diesel
                                	break;
                                    default:
                                        rf_mod[y]='0';
                                    break;
                                }                                                 
                                y++;                                
                            }  
                            if(producto1==0){
                                y=0;                                    
                                for(x=4;x<=6;x++){
                                    if(rf_mod[x]=='1'){
                                       rf_mod[x]='0';     
                                        lado1.grado[y][0]=0;                                        
                                    }
                                    y++;
                                }
                            }        
                            if(producto2==0){
                                y=0;                                    
                                for(x=4;x<=6;x++){
                                    if(rf_mod[x]=='2'){
                                       rf_mod[x]='0';     
                                        lado1.grado[y][0]=0;                                        
                                    }
                                    y++;
                                }
                            }     
                            if(producto3==0){
                                y=0;                                    
                                for(x=4;x<=6;x++){
                                    if(rf_mod[x]=='3'){
                                       rf_mod[x]='0';     
                                        lado1.grado[y][0]=0;                                        
                                    }
                                    y++;
                                }
                            }
                            if(producto4==0){
                                y=0;                                    
                                for(x=4;x<=6;x++){
                                    if(rf_mod[x]=='4'){
                                       rf_mod[x]='0';     
                                        lado1.grado[y][0]=0;                                        
                                    }
                                    y++;
                                }
                            }                                                                                                         
                            rf_mod[7]='*';
							PC_ClearRxBuffer();				
						    for(x=0;x<=7;x++){
							   PC_PutChar(rf_mod[x]);
						    }                      
                            producto1=1;
                            producto2=1;
                            producto3=1;
                            producto4=1;                                
                            EEPROM_WriteByte(lado1.grado[0][0],16);
                            EEPROM_WriteByte(lado1.grado[1][0],17);
                            EEPROM_WriteByte(lado1.grado[2][0],18);
						    set_imagen(1,74);	
	                        flujo_LCD1 = 0;    
							lado1.estado=libre;  
	                    break;                         
                    }
                }
                CyDelay(100);            
	            LCD_1_ClearRxBuffer();
            }         
        break;
            
        case 19:
			rf_mod[0]='M';
			rf_mod[1]='U';
			rf_mod[2]='X';
			rf_mod[3]='5';            
			    for(x=0;x<=15;x++){						//Serial				
				    y=(rventa1.id[x/2]>>4)&0x0F;
				    if((x%2)==0){
					    y=rventa1.id[x/2]&0x0F;
				    }
				    rf_mod[x+4] = y+48;
				    if(y>9){
					    rf_mod[x+4] = y+55;
				    }
			}            
			rf_mod[20]='*';					
			PC_ClearRxBuffer();
            for(x=0;x<=20;x++){
			    PC_PutChar(rf_mod[x]);
			}
            set_imagen(1,0);	
	        flujo_LCD1 = 0;    
			lado1.estado=libre;            
            
		break;    
        
            
        case 102:
            
            
        break;
            
        case 100:  
         if(count_protector>=4){
            flujo_LCD1=0;
            isr_3_Stop(); 
            Timer_Animacion_Stop(); 
            count_protector=0;
         }            
        break;
            
            
            
    }
    }



/*
*********************************************************************************************************
*                                         void polling_LCD2(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/

void polling_LCD2(void){ 
    
    
}

/*
*********************************************************************************************************
*                                        void polling_wd(void)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
void polling_wd(void){

}

/*
*********************************************************************************************************
*                                         CY_ISR(animacion)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
CY_ISR(animacion){
    Timer_Animacion_ReadStatusRegister();
    if(flujo_LCD1==1){
        if(count_protector<=6){
            count_protector++;
            set_imagen(1,(iprotector5+count_protector));  
        }
        else{
           count_protector=0; 
           set_imagen(1,(iprotector5+count_protector));  
        }
    }
    else{
        count_protector++;
    }
}

/*
*********************************************************************************************************
*                                         CY_ISR(animacion)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
CY_ISR(animacion2){
    Timer_Animacion2_ReadStatusRegister();
    if(flujo_LCD2==1){
        if(count_protector2<=6){
            count_protector2++;
            set_imagen(2,(iprotector5+count_protector2));  
        }
        else{
           count_protector2=0; 
           set_imagen(2,(iprotector5+count_protector2));  
        }
    }
    else{
        count_protector2++;
    }
}

/*
*********************************************************************************************************
*                                        CY_ISR(modo_mux)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
CY_ISR(modo_mux){
	Timer_Modo_ReadStatusRegister();
	state_rf++;
	if(state_rf==15){
		if((rventa1.autorizado!=100)&&(rventa2.autorizado!=100)){
			rventa1.autorizado=0;
			rventa2.autorizado=0;
		}	
		state_rf=0;
	}
}

/*
*********************************************************************************************************
*                                        insert_ppuInit(modo_init)
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
void insert_ppuInit(void){
    
    //uint8 precio_mod[5];    
    int x;    
    
  uint8 precio_mod[5];    
	precio_mod[0]=0;	
	precio_mod[1]=0;
	precio_mod[2]=0;
	precio_mod[3]=2;
    precio_mod[4]=0;
    cambiar_precio(lado1.dir,precio_mod,1);                   
}

/*
*********************************************************************************************************
*                                         main( void )
*
* Description : 
*               
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : 
*
* Note(s)     : none.
*********************************************************************************************************
*/
int main(){ 
    
    init();
    init_surt();    
    CyWdtStart(CYWDT_1024_TICKS,CYWDT_LPMODE_NOCHANGE);    
    //insert_ppuInit();// 
    for(;;){
         //sin el sistema Mux Advance              		
    		CyWdtClear();        
           	polling_LCD1();
    		CyWdtClear();        
            polling_rf();
         
    }

}





