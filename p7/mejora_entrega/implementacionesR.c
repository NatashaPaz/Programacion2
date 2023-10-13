/*
>gcc -o actividad1209_RankingLista actividad1209_RankingLista.c implementacionesR.c
este comando me compilo todo
*/

#include "actividad1209_RankingLista.h"


// declaraciones funciones utilitarias

void mostrarTicket(nodoTicket* lT);

nodoTicket* borrarTicket(nodoTicket* lT);

void generarTicket(nodoProductos* lP,
							nodoTicket* lT,
							nodoRanking* lR);

nodoProductos* buscar(nodoProductos* lP, int id, nodoProductos* pElemL);

void agregar(nodoTicket* lT, int id, int cant, nodoProductos* pElemL);

void descontar(nodoProductos* lP, int id, int cant);

void actualizarRanking(nodoRanking* lR, int id, int cant);

void mostrarNodoProd(nodoProductos* pElemL);

float calcularTotal(nodoTicket* lT, float* monto);


// funciones a implementar

void mostrarNodoProd(nodoProductos* pElemL) {
	if (pElemL != NULL) {
		printf("\nRegistro encontrado:\n");
		printf("\nid:\t%d", pElemL->id);
		printf("\nnombre:\t%s", pElemL->nombre);
		printf("\nprecio:\t%.2f", pElemL->precio);
		printf("\nstock:\t%d", pElemL->cantidad);
		printf("\n\nFin Registro encontrado\n");
	}
}

void mostrarListaProductos(nodoProductos* lP) {
	if (lP->sig != NULL) {	// si los hicieramos en conjunto en vez de secuencial, romperia la recursion
		printf("\n");
		printf("\nId:\t\t%d", lP->id);
		printf("\nProducto:\t%s", lP->nombre);
		printf("\nPrecio:\t\t%.2f", lP->precio);
		printf("\nCantidad:\t\t%d", lP->cantidad);
		printf("\n");
	}
	mostrarListaProductos(lP->sig);
	return;
}


void cargarProductos(nodoProductos* lP) {
	int codigo;
	char nombre[30];

	printf("\nIngrese el codigo de un producto, 0 para terminar: ");

	// validar_codigo() que no se repita el id
	scanf("%d", &codigo);
	while (codigo < 0) {
		printf("\nCodigo Invalido.\n");
		printf("\nIngrese el codigo de un producto, 0 para terminar: ");
		scanf("%d", &codigo);
	}	// si lo hiciese todo recursivo, en vez de una estructura while
		// para validar tendria que hacer una funcion recursiva nueva
	// validar_codigo()
	// adentro de la validaci�n deber�a ir la no-duplicacion de la clave

	if (codigo != 0) {
		lP->id = codigo;

		printf("\nIngrese el nombre del producto: ");
		fflush(stdin);
		scanf("%[^\n]", nombre);
		
		while (strlen(nombre) > 29) {
			printf("El nombre debe ser mas corto.");
			printf("\nIngrese el nombre del producto: ");
			fflush(stdin);
			scanf("%[^\n]", nombre);
		}
		strcpy((lP->nombre),nombre);
		fflush(stdin);

		printf("\nIngrese el precio del producto: ");
		scanf("%f", &lP->precio);

		printf("\nIngrese la cantidad en stock del producto: ");
		scanf("%d", &lP->cantidad);

		nodoProductos* nuevoNodo = (nodoProductos*)malloc(sizeof(nodoProductos));
		lP->sig = nuevoNodo;
		cargarProductos(lP->sig);
	}
	else {
		//crea el "nodo final"
		lP->sig = NULL;
	}

	return;

}


nodoTicket* atenderCliente(int* contadorClientes,
							nodoProductos* lP,
							nodoTicket* lT,
							nodoRanking* lR)
{
	float monto = 0.0;
	int nro_cliente; // podria estar vinculado a una BBDD

	*contadorClientes = *contadorClientes + 1;
	if (*contadorClientes <= 10) {
		printf("\n\nIngrese el numero de cliente: ");
		scanf("%d", &nro_cliente);
	}
	else{
		printf("\nmaximo de clientes diarios alcanzado.\n");
	}
	if (nro_cliente != 0 && *contadorClientes <= 10) {
		printf("\nAgregando al ticket:\n");
		lT->sig = NULL;
		generarTicket(lP,lT,lR);
		printf("\n*********************************************\n");
		printf("\nNro. cliente: %d\n\nTicket:\n", nro_cliente);
		mostrarTicket(lT);
		monto = calcularTotal(lT, &monto);
		printf("\nMonto total: %.2f\n", monto);
		printf("\nFin ticket\n");
		printf("\n*********************************************\n");
		//almacenar ticket en BBDD
		//aplicar descuentos y beneficios al nro de cliente (fidelizacion)
		lT = borrarTicket(lT); // hacer el borrado mas eficiente
		mostrarTicket(lT); //ticket vacio
		atenderCliente(contadorClientes, lP, lT, lR);
	}
	
}

void mostrarTicket(nodoTicket* lT) {
	if (lT->sig != NULL) {	// si los hicieramos en conjunto en vez de secuencial, romperia la recursion
			printf("\nId:\t\t%d", lT->id);
			printf("\nProducto:\t%s", lT->nombre);
			printf("\nPrecio:\t\t%.2f", lT->precio);
			printf("\nCantidad:\t%d", lT->cantidad);
			printf("\nTotal:\t\t%f", lT->total);
			printf("\n");
			mostrarTicket(lT->sig);
		}
		
	return;
}

float calcularTotal(nodoTicket* lT, float* monto) {
	//// precond: monto cero para el primer llamado
	if (lT->sig != NULL) {
		*monto = *monto + lT->total;
		calcularTotal(lT->sig, monto);
	}
	return *monto;
}

nodoTicket* borrarTicket(nodoTicket* lT) {
	nodoTicket* aux = NULL;
	if (lT->sig != NULL) {
		aux = lT->sig;
		free(lT);
		lT = aux;
		borrarTicket(lT);
	} else { 
	return lT;
	}
}



void generarTicket(nodoProductos* lP,
				nodoTicket* lT,
				nodoRanking* lR)
{
	printf("\nEntro a generar\n");
	nodoProductos* pElemL = NULL;
	int existe;
	int id;
	int cant;


	printf("\nIngrese ID del producto, 0 para terminar: ");
	scanf("%d", &id);
	if (id != 0){
		pElemL = buscar(lP, id, pElemL);
		mostrarNodoProd(pElemL);

		if (pElemL != NULL && (pElemL->cantidad) > 0) {	//tiene q ser en este orden pq sino falla si es null
			printf("\nIngrese cantidad a llevar: ");
			scanf("%d", &cant);
			while (cant > pElemL->cantidad) {
				printf("\nNo hay stock para esa cantidad.\nLleve hasta %d.", pElemL->cantidad);
				printf("\nIngrese cantidad a llevar: ");
				scanf("%d", &cant);
			}
			
			agregar(lT, id, cant, pElemL);
			descontar(lP, id, cant);
			actualizarRanking(lR, id, cant);
			generarTicket(lP, lT, lR);
		}
		else
		{
			printf("producto no disponible");
			generarTicket(lP, lT, lR);
		}
	}
	return;	
}




nodoProductos* buscar(nodoProductos* lP, int id, nodoProductos* pElemL) {
	if (lP->sig != NULL) {
		if (id == lP->id) {
			pElemL = lP;	//apuntan a lo mismo, NO es una copia
		}
		else {
			pElemL = buscar(lP->sig, id, pElemL);	//esto era clave
		}
	}
	return pElemL;
}

void agregar(nodoTicket* lT, int id, int cant, nodoProductos* pElemL) {

	if (lT->sig != NULL) {
		if (lT->id == id) {
			lT->precio = pElemL->precio;
			lT->cantidad = lT->cantidad + cant;
			lT->total = lT->precio * lT->cantidad;
		}else{
			agregar(lT->sig, id, cant, pElemL);
		}
	}
	else { //estaba vacia y creamos nuevo registro
		lT->id = pElemL->id;
		strcpy(lT->nombre, pElemL->nombre);
		lT->precio = pElemL->precio;
		lT->cantidad = cant;
		lT->total = lT->precio * lT->cantidad;
		nodoTicket* nuevoNodo = (nodoTicket*)malloc(sizeof(nodoTicket));
		nuevoNodo->sig = NULL;
		lT->sig = nuevoNodo;
	}
	return;
}




void descontar(nodoProductos* lP, int id, int cant) {

}

void actualizarRanking(nodoRanking* lR, int id, int cant) {

}


void mostrarDisponibles(nodoProductos* lP) {
	
	if (lP->sig != NULL) {	// si los hicieramos en conjunto en vez de secuencial, romperia la recursion
		if (lP->cantidad > 0) {
			printf("\n");
			printf("\nId:\t\t%d", lP->id);
			printf("\nProducto:\t%s", lP->nombre);
			printf("\nPrecio:\t\t%.2f", lP->precio);
			printf("\nStock:\t\t%d", lP->cantidad);
			printf("\n");
		}
		mostrarDisponibles(lP->sig);
	}
	return;
}



nodoRanking* buscarMasVendido(nodoRanking* lR) {
	nodoRanking* masVendido = (nodoRanking*)malloc(sizeof(nodoRanking));
	return masVendido;
}


void ordenarLista(nodoRanking* lR) {
	return;
}

void inicializarRanking(nodoRanking* lR) {

	return;
}