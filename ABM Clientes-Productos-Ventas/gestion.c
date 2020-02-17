#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion.h"

void menuPrincipal ()
{
    puts(" -----------------------------------\n"
         "|          -MENU PRINCIPAL-         |\n"
         "|                                   |\n"
         "| 1. Clientes                       |\n"
         "| 2. Productos                      |\n"
         "| 3. Ventas                         |\n"
         "| 4. Salir                          |\n"
         "|                                   |\n"
         " -----------------------------------\n");
}

void menuClientes ()
{
    puts(" -----------------------------------\n"
         "|            -CLIENTES-             |\n"
         "|                                   |\n"
         "| 1. Alta de clientes               |\n"
         "| 2. Baja de clientes               |\n"
         "| 3. Modificacion de clientes       |\n"
         "| 4. Listado de clientes            |\n"
         "| 5. Volver al menu principal       |\n"
         "|                                   |\n"
         " -----------------------------------\n");
}

void menuProductos ()
{
    puts(" -----------------------------------\n"
         "|           -PRODUCTOS-             |\n"
         "|                                   |\n"
         "| 1. Alta de productos              |\n"
         "| 2. Baja de productos              |\n"
         "| 3. Modificacion de productos      |\n"
         "| 4. Listado de productos           |\n"
         "| 5. Volver al menu principal       |\n"
         "|                                   |\n"
         " -----------------------------------\n");
}

void menuVentas ()
{
    puts(" -----------------------------------\n"
         "|             -VENTAS-              |\n"
         "|                                   |\n"
         "| 1. Alta de ventas                 |\n"
         "| 2. Anulacion de venta             |\n"
         "| 3. Listado de ventas por cliente  |\n"
         "| 4. Listado de ventas por mes      |\n"
         "| 5. Promedio de ventas por mes     |\n"
         "| 6. Volver al menu principal       |\n"
         "|                                   |\n"
         " -----------------------------------\n");
}

//--Creacion de un archivo para cada tarea desde cero; la funcion solo se llama una vez en todo el programa (al principio)--

void crearArchivos (char nombreArchivoClientes[],char nombreArchivoProductos[],char nombreArchivoVentas[])
{
    FILE *archiClientes;
    archiClientes=fopen(nombreArchivoClientes,"wb");
    if (archiClientes!=NULL)
    {
        fclose(archiClientes);
    }
    FILE *archiProductos;
    archiProductos=fopen(nombreArchivoProductos,"wb");
    if (archiProductos!=NULL)
    {
        fclose(archiProductos);
    }
    FILE *archiVentas;
    archiVentas=fopen(nombreArchivoVentas,"wb");
    if (archiVentas!=NULL)
    {
        fclose(archiVentas);
    }
}

//--Clientes--

//Alta de clientes

Cliente cargarCliente (Cliente miCliente)
{
    puts("\n------------------------------------\n"
         "          -CARGA CLIENTE-\n");
    printf("1. ID: ");
    scanf("%i",&miCliente.id);
    printf("2. DNI: ");
    scanf("%i",&miCliente.dni);
    printf("3. Nombre: ");
    fflush(stdin);
    scanf("%s",miCliente.nombre);
    printf("4. Apellido: ");
    fflush(stdin);
    scanf("%s",miCliente.apellido);
    printf("5. Telefono: ");
    fflush(stdin);
    scanf("%s",miCliente.telefono);
    printf("6. Domicilio: ");
    fflush(stdin);
    fgets(miCliente.domicilio,30,stdin);
    printf("7. Dado de baja [s/n]: ");
    fflush(stdin);
    scanf("%c",&miCliente.baja);
    printf("------------------------------------\n");
    return miCliente;
}

int buscarClienteYaCargadoEnArchivo (Cliente miCliente,char nombreArchivoClientes[])
{
    int busqueda=0;
    Cliente miClienteAux;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    while (!feof(archi) && busqueda!=1)
    {
        fread(&miClienteAux,sizeof(Cliente),1,archi);
        if (!feof(archi))
        {
            if (miClienteAux.dni==miCliente.dni)
            {
                busqueda=1; //Si el cliente ya esta cargado, retorna valor 1, de lo contrario retorna 0
            }
        }
    }
    fclose(archi);
    return busqueda;
}

void cargarClientesEnArchivo (char nombreArchivoClientes[])
{
    char control='s';
    int busqueda;
    Cliente miCliente;
    while (control=='s')
    {
        miCliente=cargarCliente(miCliente);
        busqueda=buscarClienteYaCargadoEnArchivo(miCliente,nombreArchivoClientes);
        if (busqueda==0)
        {
            FILE *archi;
            archi=fopen(nombreArchivoClientes,"ab");
            fwrite(&miCliente,sizeof(Cliente),1,archi);
            fclose(archi);
        }
        else
        {
            printf("\n>>>Error: El cliente que desea ingresar ya esta cargado (se encontro su DNI)<<<\n");
        }
        printf("\nSeguir ingresando clientes? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Baja de clientes

int buscarClienteADarDeBajaEnArchivo (int dniABuscar,char nombreArchivoClientes[])
{
    int resultadoBusqueda=0,contadorRegistros=0;
    Cliente miCliente;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    while (!feof(archi) && resultadoBusqueda==0)
    {
        fread(&miCliente,sizeof(Cliente),1,archi);
        contadorRegistros++;
        if (!feof(archi))
        {
            if (miCliente.dni==dniABuscar && miCliente.baja=='n')
            {
                resultadoBusqueda=1;
            }
        }
    }
    if (resultadoBusqueda==1)
    {
        return contadorRegistros;
    }
    else
    {
        return -1;
    }
    fclose(archi);
}

Cliente darDeBajaCliente (int posicionCliente,char nombreArchivoClientes[])
{
    Cliente miCliente;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    fseek(archi,sizeof(Cliente)*posicionCliente,SEEK_SET);
    fread(&miCliente,sizeof(Cliente),1,archi);
    miCliente.baja='s';
    fclose(archi);
    return miCliente;
}

void darDeBajaClientesEnArchivo (char nombreArchivoClientes[])
{
    char control='s';
    int dniABuscar,posicionCliente;
    Cliente miCliente;
    while (control=='s')
    {
        printf("\nIngrese el DNI del cliente a dar de baja: ");
        scanf("%i",&dniABuscar);
        posicionCliente=buscarClienteADarDeBajaEnArchivo(dniABuscar,nombreArchivoClientes);
        if (posicionCliente==-1)
        {
            printf("\n>>>Error: El cliente que desea dar de baja no se encuentra en el archivo o ya esta dado de baja<<<\n");
        }
        else
        {
            posicionCliente--;
            miCliente=darDeBajaCliente(posicionCliente,nombreArchivoClientes);
            FILE *archi;
            archi=fopen(nombreArchivoClientes,"r+b");
            fseek(archi,sizeof(Cliente)*posicionCliente,SEEK_SET);
            fwrite(&miCliente,sizeof(Cliente),1,archi);
            fclose(archi);
            printf("\n>>>Cliente dado de baja con exito<<<\n");
        }
        printf("\nSeguir dando de baja clientes? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Modificacion de clientes

int buscarClienteAModificarEnArchivo (int dniABuscar,char nombreArchivoClientes[])
{
    int resultadoBusqueda=0,contadorRegistros=0;
    Cliente miCliente;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    while (!feof(archi) && resultadoBusqueda==0)
    {
        fread(&miCliente,sizeof(Cliente),1,archi);
        contadorRegistros++;
        if (!feof(archi))
        {
            if (miCliente.dni==dniABuscar)
            {
                resultadoBusqueda=1;
            }
        }
    }
    if (resultadoBusqueda==1)
    {
        return contadorRegistros;
    }
    else
    {
        return -1;
    }
    fclose(archi);
}

void modificarClientesEnArchivo (char nombreArchivoClientes[])
{
    char control='s';
    int dniABuscar,posicionCliente;
    Cliente miCliente;
    while (control=='s')
    {
        printf("\nIngrese el DNI del cliente a modificar: ");
        scanf("%i",&dniABuscar);
        posicionCliente=buscarClienteAModificarEnArchivo(dniABuscar,nombreArchivoClientes);
        if (posicionCliente==-1)
        {
            printf("\n>>>Error: El cliente que desea modificar no se encuentra en el archivo<<<\n");
        }
        else
        {
            posicionCliente--;
            miCliente=cargarCliente(miCliente); //Carga de los datos del cliente a modificar
            FILE *archi;
            archi=fopen(nombreArchivoClientes,"r+b");
            fseek(archi,sizeof(Cliente)*posicionCliente,SEEK_SET);
            fwrite(&miCliente,sizeof(Cliente),1,archi);
            fclose(archi);
        }
        printf("\nSeguir modificando clientes? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Listar clientes

void mostrarCliente (Cliente miCliente)
{
    puts("\n------------------------------------\n"
         "             -CLIENTE-\n");
    printf("1. ID: %i",miCliente.id);
    printf("\n2. DNI: %i",miCliente.dni);
    printf("\n3. Nombre: %s",miCliente.nombre);
    printf("\n4. Apellido: %s",miCliente.apellido);
    printf("\n5. Telefono: %s",miCliente.telefono);
    printf("\n6. Domicilio: %s",miCliente.domicilio);
    printf("7. Dado de baja: %c",miCliente.baja);
    printf("\n------------------------------------\n");
}

void listarClientesEnArchivo (char nombreArchivoClientes[])
{
    char volverAlMenu[20];
    Cliente miCliente;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    printf("\n>LISTADO CLIENTES:\n\n");
    while (!feof(archi))
    {
        fread(&miCliente,sizeof(Cliente),1,archi);
        if (!feof(archi))
        {
            mostrarCliente(miCliente);
        }
    }
    fclose(archi);
    printf("\n\nIngrese una tecla para volver al menu de clientes: ");
    fflush(stdin);
    fgets(volverAlMenu,20,stdin);
}

//--Productos--

//Alta de productos

Producto cargarProducto (Producto miProducto)
{
    puts("\n------------------------------------\n"
         "          -CARGA PRODUCTO-\n");
    printf("1. ID: ");
    scanf("%i",&miProducto.id);
    printf("2. Producto: ");
    fflush(stdin);
    scanf("%s",miProducto.producto);
    printf("3. Stock: ");
    scanf("%i",&miProducto.stock);
    printf("4. Costo: ");
    scanf("%f",&miProducto.costo);
    printf("5. Precio de venta al publico: ");
    scanf("%f",&miProducto.pvp);
    printf("6. Dado de baja [s/n]: ");
    fflush(stdin);
    scanf("%c",&miProducto.baja);
    printf("------------------------------------\n");
    return miProducto;
}

int buscarProductoYaCargadoEnArchivo (Producto miProducto,char nombreArchivoProductos[])
{
    int busqueda=0;
    Producto miProductoAux;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"rb");
    while (!feof(archi) && busqueda!=1)
    {
        fread(&miProductoAux,sizeof(Producto),1,archi);
        if (!feof(archi))
        {
            if (strcmp(miProducto.producto,miProductoAux.producto)==0)
            {
                busqueda=1;
            }
        }
    }
    fclose(archi);
    return busqueda;
}

void cargarProductosEnArchivo (char nombreArchivoProductos[])
{
    char control='s';
    int busqueda;
    Producto miProducto;
    while (control=='s')
    {
        miProducto=cargarProducto(miProducto);
        busqueda=buscarProductoYaCargadoEnArchivo(miProducto,nombreArchivoProductos);
        if (busqueda==0)
        {
            FILE *archi;
            archi=fopen(nombreArchivoProductos,"ab");
            fwrite(&miProducto,sizeof(Producto),1,archi);
            fclose(archi);
        }
        else
        {
            printf("\n>>>Error: El producto que desea ingresar ya esta cargado<<<\n");
        }
        printf("\nSeguir ingresando productos? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Baja de productos

int buscarProductoADarDeBajaEnArchivo (char productoABuscar[],char nombreArchivoProductos[])
{
    int resultadoBusqueda=0,contadorRegistros=0,comparacion;
    Producto miProducto;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"rb");
    while (!feof(archi) && resultadoBusqueda==0)
    {
        fread(&miProducto,sizeof(Producto),1,archi);
        contadorRegistros++;
        if (!feof(archi))
        {
            comparacion=strcmp(miProducto.producto,productoABuscar);
            if  (comparacion==0 && miProducto.baja=='n')
            {
                resultadoBusqueda=1;
            }
        }
    }
    if (resultadoBusqueda==1)
    {
        return contadorRegistros;
    }
    else
    {
        return -1;
    }
    fclose(archi);
}

Producto darDeBajaProducto (int posicionProducto,char nombreArchivoProductos[])
{
    Producto miProducto;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"rb");
    fseek(archi,sizeof(Producto)*posicionProducto,SEEK_SET);
    fread(&miProducto,sizeof(Producto),1,archi);
    miProducto.baja='s';
    fclose(archi);
    return miProducto;
}

void darDeBajaProductosEnArchivo (char nombreArchivoProductos[])
{
    char control='s',productoABuscar[20];
    int posicionProducto;
    Producto miProducto;
    while (control=='s')
    {
        printf("\nIngrese el nombre del producto a dar de baja: ");
        fflush(stdin);
        scanf("%s",productoABuscar);
        posicionProducto=buscarProductoADarDeBajaEnArchivo(productoABuscar,nombreArchivoProductos);
        if (posicionProducto==-1)
        {
            printf("\n>>>Error: El producto que desea dar de baja no se encuentra en el archivo o ya esta dado de baja<<<\n");
        }
        else
        {
            posicionProducto--;
            miProducto=darDeBajaProducto(posicionProducto,nombreArchivoProductos);
            FILE *archi;
            archi=fopen(nombreArchivoProductos,"r+b");
            fseek(archi,sizeof(Producto)*posicionProducto,SEEK_SET);
            fwrite(&miProducto,sizeof(Producto),1,archi);
            fclose(archi);
            printf("\n>>>Producto dado de baja con exito<<<\n");
        }
        printf("\nSeguir dando de baja productos? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Modificacion de productos

int buscarProductoAModificarEnArchivo (char productoABuscar[],char nombreArchivoProductos[])
{
    int resultadoBusqueda=0,contadorRegistros=0;
    Producto miProducto;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"rb");
    while (!feof(archi) && resultadoBusqueda==0)
    {
        fread(&miProducto,sizeof(Producto),1,archi);
        contadorRegistros++;
        if (!feof(archi))
        {
            if (strcmp(productoABuscar,miProducto.producto)==0)
            {
                resultadoBusqueda=1;
            }
        }
    }
    if (resultadoBusqueda==1)
    {
        return contadorRegistros;
    }
    else
    {
        return -1;
    }
    fclose(archi);
}

void modificarProductosEnArchivo (char nombreArchivoProductos[])
{
    char control='s',productoABuscar[20];
    int posicionProducto;
    Producto miProducto;
    while (control=='s')
    {
        printf("\nIngrese el nombre del producto a modificar: ");
        scanf("%s",productoABuscar);
        posicionProducto=buscarProductoAModificarEnArchivo(productoABuscar,nombreArchivoProductos);
        if (posicionProducto==-1)
        {
            printf("\n>>>Error: El producto que desea modificar no se encuentra en el archivo<<<\n");
        }
        else
        {
            posicionProducto--;
            miProducto=cargarProducto(miProducto); //Carga de los datos del producto a modificar
            FILE *archi;
            archi=fopen(nombreArchivoProductos,"r+b");
            fseek(archi,sizeof(Producto)*posicionProducto,SEEK_SET);
            fwrite(&miProducto,sizeof(Producto),1,archi);
            fclose(archi);
        }
        printf("\nSeguir modificando productos? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Listado de productos

void mostrarProducto (Producto miProducto)
{
    puts("\n------------------------------------\n"
         "              -PRODUCTO-\n");
    printf("\n1. ID: %i",miProducto.id);
    printf("\n2. Nombre: %s",miProducto.producto);
    printf("\n3. Stock: %i unidades",miProducto.stock);
    printf("\n4. Costo: $%0.2f",miProducto.costo);
    printf("\n5. Precio de venta al publico: $%0.2f",miProducto.pvp);
    printf("\n6. Dado de baja: %c",miProducto.baja);
    printf("\n------------------------------------\n");
}

void listarProductosEnArchivo (char nombreArchivoProductos[])
{
    char volverAlMenu[20];
    Producto miProducto;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"rb");
    printf("\n>LISTADO PRODUCTOS:\n\n");
    while (!feof(archi))
    {
        fread(&miProducto,sizeof(Producto),1,archi);
        if (!feof(archi))
        {
            mostrarProducto(miProducto);
        }
    }
    fclose(archi);
    printf("\n\nIngrese una tecla para volver al menu de productos: ");
    fflush(stdin);
    fgets(volverAlMenu,20,stdin);
}

//--Ventas--

//Alta de ventas

Venta cargarVenta (Venta miVenta)
{
    puts("\n------------------------------------\n"
         "           -CARGA VENTA-\n");
    printf("1. ID: ");
    scanf("%i",&miVenta.id);
    printf("2. ID del cliente: ");
    scanf("%i",&miVenta.idCliente);
    printf("3. ID del producto: ");
    scanf("%i",&miVenta.idProducto);
    printf("4. Cantidad: ");
    scanf("%i",&miVenta.cantidad);
    printf("5. Dia: ");
    scanf("%i",&miVenta.dia);
    printf("6. Mes: ");
    scanf("%i",&miVenta.mes);
    printf("7. Anio: ");
    scanf("%i",&miVenta.anio);
    miVenta.pagado='n';
    miVenta.anular='n';
    printf("------------------------------------\n");
    return miVenta;
}

int validarFechaVenta (Venta miVenta)
{
    int x,validacion=0;
    if ((miVenta.anio%4==0 && miVenta.anio%100!=0) || (miVenta.anio%400==0))
    {
        if ((miVenta.mes>=1) && (miVenta.mes<=12))
        {
            switch (miVenta.mes)
            {
            case 1:
                x=31;
                break;
            case 2:
                x=29;
                break;
            case 3:
                x=31;
                break;
            case 4:
                x=30;
                break;
            case 5:
                x=31;
                break;
            case 6:
                x=30;
                break;
            case 7:
                x=31;
                break;
            case 8:
                x=31;
                break;
            case 9:
                x=30;
                break;
            case 10:
                x=31;
                break;
            case 11:
                x=30;
                break;
            case 12:
                x=31;
                break;
            }
            if (miVenta.dia>=1 && miVenta.dia<=x)
            {
                validacion=1;
            }
        }
    }
    else
    {
        if (miVenta.mes>=1 && miVenta.mes<=12)
        {
            switch (miVenta.mes)
            {
            case 1:
                x=31;
                break;
            case 2:
                x=28;
                break;
            case 3:
                x=31;
                break;
            case 4:
                x=30;
                break;
            case 5:
                x=31;
                break;
            case 6:
                x=30;
                break;
            case 7:
                x=31;
                break;
            case 8:
                x=31;
                break;
            case 9:
                x=30;
                break;
            case 10:
                x=31;
                break;
            case 11:
                x=30;
                break;
            case 12:
                x=31;
                break;
            }
            if (miVenta.dia>=1 && miVenta.dia<=x)
            {
                validacion=1;
            }
        }
    }
    return validacion;
}

int validarClienteVenta (Venta miVenta,char nombreArchivoClientes[])
{
    int bandera=0,idCliente=miVenta.idCliente;
    Cliente miCliente;
    FILE *archi;
    archi=fopen(nombreArchivoClientes,"rb");
    while (!feof(archi) && bandera==0)
    {
        fread(&miCliente,sizeof(Cliente),1,archi);
        if (idCliente==miCliente.id)
        {
            bandera=1;
        }
    }
    if (bandera==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(archi);
}

int validarProductoVenta (Venta miVenta,char nombreArchivoProductos[])
{
    int bandera=0;
    Producto miProducto;
    FILE *archi;
    archi=fopen(nombreArchivoProductos,"r+b");
    while (!feof(archi) && bandera==0)
    {
        fread(&miProducto,sizeof(Producto),1,archi);
        if (miVenta.idProducto==miProducto.id && miVenta.cantidad<=miProducto.stock)
        {
            miProducto.stock=miProducto.stock-miVenta.cantidad;
            fseek(archi,sizeof(Producto)*-1,SEEK_CUR);
            fwrite(&miProducto,sizeof(Producto),1,archi);
            bandera=1;
        }
    }
    fclose(archi);
    if (bandera==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cargarVentasEnArchivo (char nombreArchivoVentas[],char nombreArchivoClientes[],char nombreArchivoProductos[])
{
    char control='s';
    int validacionFecha,validacionCliente,validacionProducto;
    Venta miVenta;
    while (control=='s')
    {
        miVenta=cargarVenta(miVenta);
        validacionFecha=validarFechaVenta(miVenta);
        if (validacionFecha==1)
        {
            validacionCliente=validarClienteVenta(miVenta,nombreArchivoClientes);
            if (validacionCliente==1)
            {
                validacionProducto=validarProductoVenta(miVenta,nombreArchivoProductos);
                if (validacionProducto==1)
                {
                    FILE *archi;
                    archi=fopen(nombreArchivoVentas,"ab");
                    miVenta.pagado='s'; //Se da de alta la venta
                    fwrite(&miVenta,sizeof(Venta),1,archi);
                    fclose(archi);
                }
                else
                {
                    printf("\n>>>Error: No se encuentra el ID del producto o no hay suficiente stock del producto<<<\n");
                }
            }
            else
            {
                printf("\n>>>Error: No se encuentra el ID del cliente<<<\n");
            }
        }
        else
        {
            printf("\n>>>Error: La fecha de la venta es erronea<<<\n");
        }

        printf("\nSeguir ingresando ventas? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Anulacion de venta

int anularVentaEnArchivo (int idVentaAAnular,char nombreArchivoVentas[])
{
    Venta miVenta;
    int busqueda=0,resultado;
    FILE *archi;
    archi=fopen(nombreArchivoVentas,"r+b");
    while (!feof(archi) && busqueda==0)
    {
        fread(&miVenta,sizeof(Venta),1,archi);
        if (!feof(archi) && miVenta.id==idVentaAAnular)
        {
            if (miVenta.anular=='a')
            {
                busqueda=1;
                resultado=2;
            }
            else
            {
                busqueda=1;
                resultado=1;
                miVenta.anular='a';
                fseek(archi,sizeof(Venta)*-1,SEEK_CUR);
                fwrite(&miVenta,sizeof(Venta),1,archi);
            }
        }
    }
    fclose(archi);
    if (resultado==1)
    {
        return 1;
    }
    if (resultado==2)
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

void anularVenta (char nombreArchivoVentas[])
{
    char volverAlMenu;
    int idVentaAAnular,resultado;
    printf("\nIngrese el ID de la venta a anular: ");
    scanf("%d",&idVentaAAnular);
    resultado=anularVentaEnArchivo(idVentaAAnular,nombreArchivoVentas);
    if (resultado==1)
    {
        printf("\n>>>Venta anulada con exito<<<\n");
        printf("\nIngrese una tecla para volver al menu de ventas: ");
        fflush(stdin);
        scanf("%c",&volverAlMenu);

    }
    else if (resultado==2)
    {
        printf("\n>>>Error: La venta ya se encuentra anulada<<<\n");
        printf("\nIngrese una tecla para volver al menu de ventas: ");
        fflush(stdin);
        scanf("%c",&volverAlMenu);
    }
    else
    {
        printf("\n>>>Error: No se encuentra el ID de la venta<<<\n");
        printf("\nIngrese una tecla para volver al menu de ventas: ");
        fflush(stdin);
        scanf("%c",&volverAlMenu);
    }
}

//Listar ventas por cliente

int comprobarVentaEnArchivoProductos (Venta miVenta,char nombreArchivoProductos[])
{
    Producto miProducto;
    int bandera=0,validacion=0;
    FILE *archi2;
    archi2=fopen(nombreArchivoProductos,"rb");
    while (!feof(archi2) && bandera==0)
    {
        fread(&miProducto,sizeof(Producto),1,archi2);
        if (!feof(archi2) && miVenta.idProducto==miProducto.id)
        {
            if (miProducto.stock>0)
            {
                validacion=1;
                bandera=1;
            }
        }
    }
    fclose(archi2);
    return validacion;
}

void mostrarVentaCliente (Venta miVenta,char nombreArchivoVentas[])
{
    puts("\n------------------------------------\n"
         "              -VENTA-\n");
    printf("\n1. ID Venta: %i",miVenta.id);
    printf("\n2. ID Cliente: %i",miVenta.idCliente);
    printf("\n3. ID Producto: %i",miVenta.idProducto);
    printf("\n4. Cantidad: %i",miVenta.cantidad);
    printf("\n5. Dia: %i",miVenta.dia);
    printf("\n6. Mes: %i",miVenta.mes);
    printf("\n7. Anio: %i",miVenta.anio);
    printf("\n8. Pagado: %c",miVenta.pagado);
    printf("\n9. Anulado: %c",miVenta.anular);
    printf("\n------------------------------------\n");
}

void mostrarVentasPorIdCliente (char nombreArchivoProductos[],char nombreArchivoVentas[],int idCliente)
{
    Venta miVenta;
    FILE *archi;
    archi=fopen(nombreArchivoVentas,"rb");
    while (!feof(archi))
    {
        fread(&miVenta,sizeof(Venta),1,archi);
        if (miVenta.idCliente==idCliente && !feof(archi))
        {
            if (comprobarVentaEnArchivoProductos(miVenta,nombreArchivoProductos)==1)
            {
                mostrarVentaCliente(miVenta,nombreArchivoVentas);
            }
            else
            {
                printf("\n>>>Error: La venta ID: %i no se pudo mostrar ya que el stock del producto asociado a esa venta es 0<<<\n",miVenta.id);
            }
        }
    }
    fclose(archi);
}

void listarVentasPorClienteEnArchivo (char nombreArchivoVentas[],char nombreArchivoClientes[],char nombreArchivoProductos[])
{
    int idCliente;
    char control='s';
    while (control=='s')
    {
        printf("\nIngrese el ID del cliente para mostrar las ventas asociadas al mismo: ");
        scanf("%i",&idCliente);
        mostrarVentasPorIdCliente(nombreArchivoProductos,nombreArchivoVentas,idCliente);
        printf("\nSeguir listando ventas por cliente? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Listar ventas del mes

void mostrarVentasPorMes (char nombreArchivoVentas[],char nombreArchivoProductos[],int mes,int anio)
{
    Venta miVenta;
    FILE *archi;
    archi=fopen(nombreArchivoVentas,"rb");
    while (!feof(archi))
    {
        fread(&miVenta,sizeof(Venta),1,archi);
        if (miVenta.mes==mes && miVenta.anio==anio && !feof(archi))
        {
            if (comprobarVentaEnArchivoProductos(miVenta,nombreArchivoProductos)==1)
            {
                mostrarVentaCliente(miVenta,nombreArchivoVentas);
            }
            else
            {
                printf("\n>>>Error: La venta ID: %i no se pudo mostrar ya que el stock del producto asociado a esa venta es 0<<<\n",miVenta.id);
            }
        }
    }
    fclose(archi);
}

void listarVentasPorMesEnArchivo (char nombreArchivoVentas[],char nombreArchivoProductos[])
{
    int mes,anio;
    char control='s';
    while (control=='s')
    {
        printf("\nIngrese un mes [1-12] para mostrar las ventas asociadas al mismo: ");
        scanf("%i",&mes);
        printf("\nIngrese el anio del mes: ");
        scanf("%i",&anio);
        mostrarVentasPorMes(nombreArchivoVentas,nombreArchivoProductos,mes,anio);
        printf("\nSeguir listando ventas por mes? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//Mostrar promedio de ventas del mes (utilizar matrices)

void mostrarMatrizVentasDiarias(int matrizPromedioDiarioDelMes[][7])
{
    int i,j;
    float promedioVentasMensual,acumulador=0;
    printf("\nCalendario de 28 dias del mes ingresado con las ventas diarias: \n");
    for (i=0; i<4; i++)
    {
        for (j=0; j<7; j++)
        {
            printf("[%i]",matrizPromedioDiarioDelMes[i][j]);
            acumulador=acumulador+matrizPromedioDiarioDelMes[i][j];
        }
        printf("\n");
    }
    promedioVentasMensual=acumulador/28;
    printf("\nEl promedio de ventas mensual del mes ingresado es de %0.2f\n",promedioVentasMensual);
}

int obtenerVentasDiarias (char nombreArchivoVentas[],int dia,int mes,int anio)
{
    int contador=0;
    Venta miVenta;
    FILE *archi;
    archi=fopen(nombreArchivoVentas,"rb");
    while (!feof(archi))
    {
        fread(&miVenta,sizeof(Venta),1,archi);
        if (!feof(archi) && miVenta.dia==dia && miVenta.mes==mes &&miVenta.anio==anio)
        {
            contador=contador+1;
        }
    }
    fclose(archi);
    return contador;
}

void mostrarVentasPromedioPorMes (char nombreArchivoVentas[],int mes,int anio)
{
    int matrizPromedioDiarioDelMes [4][7],ventasDiarias;
    int i,j,dia=1;
    for (i=0; i<4; i++)
    {
        for (j=0; j<7; j++)
        {
            ventasDiarias=obtenerVentasDiarias(nombreArchivoVentas,dia,mes,anio);
            matrizPromedioDiarioDelMes[i][j]=ventasDiarias;
            dia++;
        }
    }
    mostrarMatrizVentasDiarias(matrizPromedioDiarioDelMes);
}

int validarMuestraMensualVentas (char nombreArchivoVentas[],char nombreArchivoProductos[],int mes,int anio)
{
    int validacion,bandera=0;
    Venta miVenta;
    FILE *archi2;
    archi2=fopen(nombreArchivoVentas,"rb");
    while (!feof(archi2) && bandera==0)
    {
        fread(&miVenta,sizeof(Venta),1,archi2);
        if (!feof(archi2) && miVenta.anio==anio && miVenta.mes==mes)
        {
            validacion=comprobarVentaEnArchivoProductos(miVenta,nombreArchivoProductos);
            if (validacion==0)
            {
                bandera=1;
            }
        }
    }
    fclose(archi2);
    return validacion;
}

void promedioMensualVentas (char nombreArchivoVentas[],char nombreArchivoProductos[])
{
    int mes,anio,validacion;
    char control='s';
    while (control=='s')
    {
        printf("\nIngrese un mes [1-12] para mostrar el promedio de ventas del mismo: ");
        scanf("%i",&mes);
        printf("\nIngrese el anio del mes: ");
        scanf("%i",&anio);
        validacion=validarMuestraMensualVentas(nombreArchivoVentas,nombreArchivoProductos,mes,anio);
        if (validacion==0)
        {
            printf("\n>>>El stock de algun/nos producto/s es 0<<<\n");
        }
        else
        {
            mostrarVentasPromedioPorMes(nombreArchivoVentas,mes,anio);
        }
        printf("\nSeguir listando ventas por mes? [s para seguir/otra tecla para terminar]: ");
        fflush(stdin);
        scanf("%c",&control);
    }
}

//--Funcion Principal--

void funcionPrincipal ()
{
    char control='s',nombreArchivoClientes[30]= {"clientes.bin"},nombreArchivoProductos[30]= {"productos.bin"},nombreArchivoVentas[30]= {"ventas.bin"};
    int opcion;
    crearArchivos(nombreArchivoClientes,nombreArchivoProductos,nombreArchivoVentas);
    while (control=='s')
    {
        menuPrincipal();
        printf("Ingrese una opcion [1-4]: ");
        scanf("%d",&opcion);
        system("cls");
        switch (opcion)
        {
        case 1:
            while (control=='s')
            {
                menuClientes();
                printf("Ingrese una opcion [1-5]: ");
                scanf("%d",&opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    cargarClientesEnArchivo(nombreArchivoClientes);
                    break;
                case 2:
                    darDeBajaClientesEnArchivo(nombreArchivoClientes);
                    break;
                case 3:
                    modificarClientesEnArchivo(nombreArchivoClientes);
                    break;
                case 4:
                    listarClientesEnArchivo(nombreArchivoClientes);
                    break;
                case 5:
                    control='n';
                    break;
                }
                system("cls");
            }
            control='s';
            break;
        case 2:
            while (control=='s')
            {
                menuProductos();
                printf("Ingrese una opcion [1-5]: ");
                scanf("%d",&opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    cargarProductosEnArchivo(nombreArchivoProductos);
                    break;
                case 2:
                    darDeBajaProductosEnArchivo(nombreArchivoProductos);
                    break;
                case 3:
                    modificarProductosEnArchivo(nombreArchivoProductos);
                    break;
                case 4:
                    listarProductosEnArchivo(nombreArchivoProductos);
                    break;
                case 5:
                    control='n';
                    break;
                }
                system("cls");
            }
            control='s';
            break;
        case 3:
            while (control=='s')
            {
                menuVentas();
                printf("Ingrese una opcion [1-6]: ");
                scanf("%d",&opcion);
                system("cls");
                switch (opcion)
                {
                case 1:
                    cargarVentasEnArchivo(nombreArchivoVentas,nombreArchivoClientes,nombreArchivoProductos);
                    break;
                case 2:
                    anularVenta(nombreArchivoVentas);
                    break;
                case 3:
                    listarVentasPorClienteEnArchivo(nombreArchivoVentas,nombreArchivoClientes,nombreArchivoProductos);
                    break;
                case 4:
                    listarVentasPorMesEnArchivo(nombreArchivoVentas,nombreArchivoProductos);
                    break;
                case 5:
                    promedioMensualVentas(nombreArchivoVentas,nombreArchivoProductos);
                    break;
                case 6:
                    control='n';
                    break;
                }
                system("cls");
            }
            control='s';
            break;
        case 4:
            control='n';
            break;
        }
    }
}
