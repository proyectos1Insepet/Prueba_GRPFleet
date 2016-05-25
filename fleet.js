/*
*********************************************************************************************************
*                                           CODIGO GRP700-FLEET
*
*                             (c) Copyright 2015; Sistemas Insepet LTDA
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                             INCLUDE LIB
*********************************************************************************************************
*/

var sprintf         = require("sprintf").sprintf;
var sp              = require("serialport");
var sp2             = require("serialport");
var pg              = require('pg');
/*
*********************************************************************************************************
*                                    DECLARACION DE VARIABLES
*********************************************************************************************************
*/
var port_mux          = '/dev/ttyO4';
var config_port_mux   = {baudrate: 9600, parser: sp.parsers.readline("*")};
var muxport           = new sp.SerialPort(port_mux,config_port_mux,abrir);

var port_print        = '/dev/ttyO1';
var config_port_print = {baudrate: 115200, parser: sp2.parsers.readline("*")};// 115200
var printport           = new sp2.SerialPort(port_print,config_port_print, printer);
     
var conString         = "postgrest://db_admin:12345@localhost:5432/grpfleet";

/**************Variables para productos****************************/
var man1;
var man2;
var man3;
var nombre_producto;
var nproducto1;
var nproducto2;
var nproducto3;

/**************Variables para la venta*****************************/
var dineroDia;
var dineroMes;
var dineroSema;
var nombreCuenta;
var placa;
var saldo;
var visitasDia;
var visitasMes;
var visitasSema;
var volDia;
var volMes;
var volSema;
var total_vol_p1;
var total_vol_p2;
var total_vol_p3;
var productos;
var linea1;
var linea2;
var id_tax;
var tel;
var dir;
var footer;
var sim_vol;
var moneda;
var vol_vendido;
var dinero_vendido;

/********************Arreglos**************************************/            
var serial      = Buffer(16); /*global serial*/
precio          = new Buffer(5);  /*global precio*/
preset          = new Buffer(7);  /*global preset*/
km              = new Buffer(7);  /*global km*/
idestacion      = new Buffer(4);  /*global idestacion*/
volumen         = new Buffer(7);  /*global volumen*/
dinero          = new Buffer(7);  /*global dinero*/
var id_venta        = new Buffer(7);
var producto1       = new Buffer(12);
var producto2       = new Buffer(12);
var producto3       = new Buffer(12);

/**************Variables para la autorizacion***********************/
var cantidadAutorizada;
var codigoRetorno;
var idproducto;
var cara;
var numeroAutorizacion;
var retorno;
var tipoConvenio;
var tipoRetorno;
var trama;
var valorConvenio;
var fecha;
var error_local;
var imp;

/*
*********************************************************************************************************
*                                     INICIALIZACIÓN DEL MÓDULO                                         *
*                                                                                                       *
*   Lee la base de datos para determinar si hay ventas sin cerrar e inicializar los nombres de los      *
*   productos seg?n la ?ltima configuraci?n y ultima venta                                              *
*********************************************************************************************************
*/
    
function reinicio(error){
     if (error){
       console.log(error);
     }else{
         pg.connect(conString, function(err, client, done){
         if(err){
             return console.error('Error de conexion 1', err);
         }else{
                client.query("SELECT linea1, linea2, id_tax, tel, dir, vol, moneda,footer FROM recibo;", function(err,result){
                    done();
                    if(err){
                        return console.error('error de conexion', err);
                    }else{
                        linea1  = result.rows[0].linea1;
                        linea2  = result.rows[0].linea2;
                        id_tax  = result.rows[0].id_tax;
                        tel     = result.rows[0].tel;
                        dir     = result.rows[0].dir;
                        sim_vol = result.rows[0].vol;
                        moneda  = result.rows[0].moneda;
                        footer  = result.rows[0].footer;
                    }
                });
                //Ingresar c?digo para  reinicio de mux, caso de los productos
                client.query("SELECT man1, man2, man3 FROM mangueras; ",function(err,result){
                    done();
                    if(err){
                    return console.error('Error de conexion', err);
                    }else{
                        man1 = result.rows[0].man1;  //Carga identificadores de manguera
                        man2 = result.rows[0].man2;
                        man3 = result.rows[0].man3;
                        client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man1 ),function(err,result){
                            done();
                                if(err){
                                return console.error('Error de conexion', err);
                                }else{
                                    console.log(result.rows[0].descripcion);
                                    nproducto1 = result.rows[0].descripcion;  //Carga nombre de producto primera manguera
                                }
                        });
                                
                        client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man2 ),function(err,result){
                            done();
                            if(err){
                                return console.error('Error de conexion', err);
                            }else{
                                console.log(result.rows[0].descripcion);
                                nproducto2 = result.rows[0].descripcion;  //Carga nombre de producto segunda manguera
                             }
                        });
                                
                        client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man3 ),function(err,result){
                            done();
                            if(err){
                                return console.error('Error de conexion', err);
                            }else{
                                console.log(result.rows[0].descripcion);
                                nproducto3 = result.rows[0].descripcion;  //Carga nombre de producto tercera manguera
                            }
                        });
                    }
                });
            }   
        });
    }
}

/*
*********************************************************************************************************
*                                    function abrir(error)
*
* Description : Abre el puerto serial para la comunicacion con el mux
*               
*********************************************************************************************************
*/
function abrir(error){
   if (error){
       console.log('Error de puerto: '+error);
   } else{
       console.log('Abierto '+port_mux);
       muxport.on('data',rx_data_mux);
       reinicio();
   }
}

/*
*********************************************************************************************************
*                                    abrir_print(error)(error)
*
* Description : Abre el puerto serial para la comunicacion con la impresora
*               
*********************************************************************************************************
*/
function printer(error){
   if (error){
       console.log('Error puerto Imp.: '+error);
   } else{
       console.log('Abierto '+port_print);
   }
}

/*
*********************************************************************************************************
*                                function rx_data_mux(data)
*
* Description : Se activa cada vez que llega una trama valida del mux y ejecuta el caso segun el comando
*               
*********************************************************************************************************
*/

function rx_data_mux(data){
    if((data[0]==='M') && (data[1]==='U') && (data[2]==='X')){
        console.log('>>'+data);
        console.log('>>'+data.length);
        caso    = data[3];  /*global caso*/
        switch(caso){
            case '0':
                for(var i=19; i>=4; i--){                                       //Serial
                    serial[19-i] = data.charCodeAt(i); 
                }
                console.log('Serial: '+serial); 
                idproducto = data[20];                                          //Id Producto
                console.log('Id Producto: '+idproducto);
                for(i=21; i<25; i++){                                           //Id Estacion
                    idestacion[i-21] = data.charCodeAt(i); 
                }
                console.log('Id Estacion: '+idestacion);
                for(i=25; i<30; i++){                                           //Precio
                    precio[i-25] = data.charCodeAt(i); 
                }  
                console.log('Precio: '+precio);
                tipopreset = data[30];                                          /*global tipopreset*/             //Tipo preset
                console.log('Tipo Preset: '+tipopreset);
                for(i=31; i<38; i++){                                           //Preset
                    preset[i-31] = data.charCodeAt(i); 
                }  
                console.log('Preset: '+preset);  
                for(i=44; i>=38; i--){                                          //km
                    km[44-i] = data.charCodeAt(i); 
                } 
                console.log('Km: '+km);                 
                cara = data[45];
                console.log('Cara: '+cara);
                consulta_dato();
            break; 
            
             case '1':                                                           //Caso Guardar Venta   
                muxport.write('BBB');
                muxport.write('E');
                muxport.write(String(cara));
                muxport.write('2');                         //Gracias por su compra
                muxport.write('*');
                cara = data[4];                                                 //Cara
                console.log('Cara: '+cara);
                idproducto = data[5];                                           //Id Producto
                console.log('Id Producto: '+idproducto); 
                for(i=6; i<13; i++){                                            //Volumen
                    volumen[i-6] = data.charCodeAt(i);
                }
                volumen[3]=46;
                vol_vendido = parseFloat(volumen);
                console.log('Volumen: '+volumen);
                console.log('Volumen F:'+vol_vendido);
                for(i=13; i<20; i++){                                           //Dinero
                    dinero[i-13] = data.charCodeAt(i); 
                }  
                dinero_vendido = parseFloat(dinero);
                console.log('Dinero: '+dinero);
                console.log('Dinero F:'+dinero_vendido);
                for(i=20; i<25; i++){                                           //Precio
                    precio[i-20] = data.charCodeAt(i); 
                }  
                console.log('Precio: '+precio); 
                for(i=58; i>=52; i--){                                          //km
                    km[58-i] = data.charCodeAt(i); 
                }  
                console.log('Km: '+km); 
                guardar_venta();                
            break;
            
            case '4':
                man1 = data[4];
                man2 = data[5];
                man3 = data[6];
                pg.connect(conString, function(err, client, done){
                    if(err){
                        return console.error('Error de conexion 1', err);
                    }else{
                        client.query(sprintf("UPDATE mangueras SET man1='%1$s', man2 = '%2$s', man3 = '%3$s'", man1,man2,man3 ),function(err,result){
                            done();
                            if(err){
                                return console.error('Error de conexion', err);
                            }else{
                                console.log("Dato Insertado");
                                client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man1 ),function(err,result){
                                    done();
                                    if(err){
                                        return console.error('Error de conexion', err);
                                    }else{
                                        console.log(result.rows[0].descripcion);
                                        nproducto1 = result.rows[0].descripcion;  //Carga nombre de producto primera manguera
                                    }
                                });
                                
                                client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man2 ),function(err,result){
                                    done();
                                    if(err){
                                        return console.error('Error de conexion', err);
                                    }else{
                                        console.log(result.rows[0].descripcion);
                                        nproducto2 = result.rows[0].descripcion;  //Carga nombre de producto segunda manguera
                                    }
                                });
                                
                                client.query(sprintf("SELECT descripcion FROM producto WHERE id_producto = '%1$s' ",man3 ),function(err,result){
                                    done();
                                    if(err){
                                        return console.error('Error de conexion', err);
                                    }else{
                                        console.log(result.rows[0].descripcion);
                                        nproducto3 = result.rows[0].descripcion;  //Carga nombre de producto tercera manguera
                                    }
                                });
                                
                            } 
                        });
                    }
                });
                
                
            break;
            
            case '5':
                for(i=19; i>=4; i--){                                       //Serial
                    serial[19-i] = data.charCodeAt(i); 
                }
                console.log('Serial: '+serial); 
                printport.write("PARA INSERTAR EL VEHICULO\n");
                printport.write("EN UNA CUENTA, DIGITE\n");
                printport.write("EL SERIAL NUMERO:\n");
                printport.write(serial+"\n");
                printport.write("EN EL CAMPO INDICADO:\n\n\n\n\n");
            
            break;
            
            case 'E':
                if(data[4] == '0'){
                    muxport.write('BBB');
                    muxport.write('1');
                    muxport.write(cara);
                    if(data[5] == '1'){
                        console.log('\n\nEl Equipo no cambio precio.\nerror: 1.\n');            //No cambio el precio
                    }else if(data[5] == '2'){
                        console.log('\n\nEl Equipo no recibio preset.\nerror: 2.\n');           //No recibio el preset
                    }
                    muxport.write('*'); 
                }
            break;
        }
        
        
        
        
    }
}


/*
*********************************************************************************************************
*                                function consulta_dato()
*
* Description : LLama el servicio Web para pedir la autorizacion de una venta
*               
*********************************************************************************************************
*/

function consulta_dato(){
    pg.connect(conString, function(err, client, done){
        if(err){
            return console.error('Error de conexion', err);
        }else{
            console.log("Serial AUTO:" + serial);
            client.query(sprintf("select v.estado_bloqueo,v.id_cliente, c.estado_cuenta, c.id_cliente from vehiculo v inner join cuenta c on v.id_cliente = c.id_cliente where serial = '%1$s'",serial), function(err,result){        //consulto maximo id de venta
                done();
                if(err){
                    return console.error('error de conexion', err);
                }else{
                    var estado;
                    var estado_cliente;
                    if(result.rows[0] == null){
                        estado = false;   
                    }else{
                        estado = result.rows[0].estado_bloqueo;
                        estado_cliente = result.rows[0].estado_cuenta;
                        console.log("Estado bloqueo: " +estado_cliente);
                    }
                    console.log("Estado bloqueo: " +estado);
                    if (estado == false || estado == null || estado_cliente == false || estado_cliente == null){
                        muxport.write('BBB');           //En caso de venta incompleta
                        muxport.write('E');             // No permite autorizar
                        muxport.write(String(cara));
                        muxport.write('1');             //Limpia estado del mux e inicia pantalla
                        muxport.write('*');
                        printport.write('Vehiculo Bloqueado \n');
                        printport.write('O vehiculo no existe \n');
                        printport.write('Serial:' +serial +'\n\n\n\n\n\n\n');
                    }else{
                        autorizaMux();
                    }
                }
                });
            }
        });
}

/*
*********************************************************************************************************
*                                function guardar_venta()
*
* Description : LLama el servicio Web para pedir la autorizacion de una venta
*               
*********************************************************************************************************
*/
function guardar_venta(){
    var f = new Date();
    fecha = f.getDate() + "-" + (f.getMonth() +1) + "-" + f.getFullYear() + ' ' + f.getHours() + ':' + f.getMinutes();
    pg.connect(conString, function(err, client, done){
        if(err){
            return console.error('Error de conexion', err);
        }else{
             client.query("SELECT MAX(id) FROM venta;", function(err,result){        //consulto maximo id de venta
                done();
                if(err){
                    return console.error('error de conexion', err);
                }else{
                    if(result.rows[0].max ==null){
                        var last_id = 0;
                    }else{
                        last_id = result.rows[0].max;    
                    }
                    console.log('Ultima venta:'+result.rows[0].max);
                    console.log('Serial'+serial);
                    client.query(sprintf("SELECT id_cliente, placa from vehiculo WHERE serial = '%1$s'", serial), function(err, result) {
                        done();
                        if(err){
                             return console.error('error de conexion', err);
                        }else{
                            var id_cliente = result.rows[0].id_cliente;
                            placa = result.rows[0].placa;
                            console.log('MAX:'+last_id);
                            client.query(sprintf("SELECT tipo_transaccion from cuenta WHERE id_cliente = '%1$s'",id_cliente), function(err, result) {
		                        done();
		                        if(err){
			                        return console.error('Error de conexion', err);
		                        }else{
		                            var transaccion = result.rows[0].tipo_transaccion;
			                        client.query(sprintf("INSERT INTO venta VALUES('%1$s','%2$s','%3$s','%4$s','%5$s','%6$s')", (last_id+1),id_cliente,fecha, transaccion,dinero_vendido,vol_vendido ),function(err,result){
				                        done();
				                        if(err){
				                            return console.error('Error de conexion', err);
				                        }else{
				                            console.log('Venta guardada');
				                            client.query(sprintf("INSERT INTO venta_detalle VALUES('%1$s','%2$s','%3$s','%4$s','%5$s','%6$s','%7$s','%8$s','%9$s','%10$s')", (last_id+1),placa,km, idproducto,precio,cara,man1,1,dinero_vendido,vol_vendido),function(err,result){
				                                done();
				                                if(err){
				                                return console.error('Error de conexion', err);
				                                }else{
				                                console.log('Venta guardada');
				                                imprimir_venta();
			                                    }
			                                 });
				                            
				                            
			                            }
			                        });
	                        	}
		
                             });
                            
                            
                            
                            
                            
                        } 
                    });
                }
             });
             
             
              
             
        }
    });
    
}

/*
*********************************************************************************************************
*                                function imprimir_venta()
*
* Description : LLama el servicio Web para pedir la autorizacion de una venta
*               
*********************************************************************************************************
*/

function imprimir_venta(){
    
     pg.connect(conString, function(err, client, done){
        if(err){
            return console.error('Error de conexion', err);
        }else{
            client.query(sprintf("SELECT descripcion FROM producto where id_producto ='%1$s' ",parseInt(idproducto)), function(err,result){        //consulto maximo id de venta
                done();
                if(err){
                    return console.error('error de conexion', err);
                }else{
                    nombre_producto = result.rows[0].descripcion;
                    console.log(">>"+nombre_producto);
                }
          
            console.log("IMPRIMIENDO");
            printport.write('   '+linea1 +'\n');
            printport.write('      '+linea2 +'\n');
            printport.write('       '+id_tax+'\n');
            printport.write('       Tel: '+tel+'\n');
            printport.write('     '+dir+ '\n\n');
            var f = new Date();
	        printport.write('Fecha:' + String(f.getDate() + "-" + (f.getMonth() + 1) + "-" + f.getFullYear() + ' ' + f.getHours() + ':' + f.getMinutes()) + '\n\n');                                                      
            printport.write('Serial:\n');
            printport.write(serial + '\n');
            printport.write('Placa: ' + placa +'\n');
            printport.write('Km   : ' + parseInt(km) +'\n');
            printport.write('Posicion: ' + cara + '\n');
            printport.write('Producto: ' +nombre_producto+ '\n');
            var precio1 = parseFloat(precio);
            printport.write('PPU     : $' + String(precio1) + '\n');
            volumen[3]=46;
            var volumen1 = parseFloat(volumen);
            printport.write('Volumen : G' + volumen1 + '\n');
            var dinero1 = parseFloat(dinero);
            printport.write('Dinero  : $' + String(dinero1) + '\n\n\n');
            printport.write('Firma :'+ '\n\n');
            printport.write('       --------------------'+ '\n\n');
            printport.write('Cedula:' + '\n');
            printport.write('       --------------------'+ '\n\n');
            printport.write(footer+ '\n');
            printport.write('\n\n\n\n\n');  
            });
        }
    });
}

/*
*********************************************************************************************************
*                                function autorizaMux()
*
* Description : Envia los datos para autorizar el surtidor
*               
*********************************************************************************************************
*/
function autorizaMux(){
    console.log('Entra a autorizar');
    muxport.write('BBB');                                       //Encabezado
    console.log("BBB");
    muxport.write('0');                                         //Envia para autorizar
    console.log("Envia datos de autorizacion");
    muxport.write(String(cara));                                //Cara
    console.log("Cara: "+cara);
    muxport.write(String(idproducto));                          //Identificador de producto
    console.log("Id Producto: "+idproducto);
    console.log("Precio: ");                                   //Precio
    for(var i=1; i<=4; i++){                                
        muxport.write('0');                                    //Mismo precio EDS
        console.log('0');
    }
    muxport.write('F'); 
    console.log('F');
    if (tipopreset == 1 || tipopreset ==2){
        muxport.write(preset);
        console.log('>>'+preset);
    }else{
        muxport.write('990000');    
        console.log('Cantidad Autorizada: 990000');
    }
    muxport.write(String(tipopreset));
    console.log('Tipo de Preset: '+tipopreset);
    muxport.write('*');
}



/*
*********************************************************************************************************
*                                function watchful()
*
* Description : Revisa los estados del Beagle para realizar reintentos o peticiones al MUX
*               
*********************************************************************************************************
*/
function watchful(){
    console.log("Vigilando");
}



/*
*********************************************************************************************************
*                                    Metodos Principales
*********************************************************************************************************
*/
//setInterval(watchful, 50);           //Revisa el estado de las banderas
