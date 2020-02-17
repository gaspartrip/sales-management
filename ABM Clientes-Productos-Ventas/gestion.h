#ifndef GESTION_H_INCLUDED
#define GESTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion.h"

typedef struct
{
    int id;
    int dni;
    char nombre[20];
    char apellido[20];
    char telefono[20];
    char domicilio[30];
    char baja; //‘s’ o ‘n’
} Cliente;

typedef struct
{
    int id;
    char producto[20];
    int stock;
    float costo;
    float pvp;
    char baja; //‘s’ o ‘n’
} Producto;

typedef struct
{
    int id;
    int idCliente;
    int idProducto;
    int cantidad;
    int dia;
    int mes;
    int anio;
    char pagado;
    char anular; //‘a’
} Venta;

void menuPrincipal ();
void menuClientes ();
void menuProductos ();
void menuVentas ();
void crearArchivos (char[],char[],char[]);
//-Funciones Clientes-
Cliente cargarCliente (Cliente);
int buscarClienteYaCargadoEnArchivo (Cliente,char[]);
void cargarClientesEnArchivo (char[]);
int buscarClienteADarDeBajaEnArchivo (int,char[]);
Cliente darDeBajaCliente (int,char[]);
void darDeBajaClientesEnArchivo (char[]);
int buscarClienteAModificarEnArchivo (int,char[]);
void modificarClientesEnArchivo (char[]);
void mostrarCliente (Cliente);
void listarClientesEnArchivo (char[]);
//-Funciones Productos-
Producto cargarProducto (Producto);
int buscarProductoYaCargadoEnArchivo (Producto,char[]);
void cargarProductosEnArchivo (char[]);
int buscarProductoADarDeBajaEnArchivo (char[],char[]);
Producto darDeBajaProducto (int,char[]);
void darDeBajaProductosEnArchivo (char[]);
int buscarProductoAModificarEnArchivo (char[],char[]);
void modificarProductosEnArchivo (char[]);
void mostrarProducto (Producto);
void listarProductosEnArchivo (char[]);
//-Funciones Ventas-
Venta cargarVenta (Venta);
int validarFechaVenta (Venta);
int validarClienteVenta (Venta,char[]);
int validarProductoVenta (Venta,char[]);
void cargarVentasEnArchivo (char[],char[],char[]);
void escribirVentaAnulada (char[],Venta,int);
void anularVenta (char[]);
int comprobarVentaEnArchivoProductos (Venta,char[]);
void mostrarVentaCliente (Venta,char[]);
void mostrarVentasPorIdCliente (char[],char[],int);
void listarVentasPorClienteEnArchivo (char[],char[],char[]);
void mostrarVentasPorMes (char[],char[],int,int);
void listarVentasPorMesEnArchivo (char[],char[]);
void mostrarMatrizVentasDiarias(int[][7]);
int obtenerVentasDiarias (char[],int,int,int);
void mostrarVentasPromedioPorMes (char[],int,int);
int validarMuestraMensualVentas (char[],char[],int,int);
void promedioMensualVentas (char[],char[]);
//-Funcion Principal-
void funcionPrincipal ();

#endif // GESTION_H_INCLUDED
