#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <conio2.h>

#define JUGADOR_X 0
#define JUGADOR_O 1

#define CASILLERO_DE_X 0
#define CASILLERO_DE_O 1
#define CASILLERO_VACIO 9

#define LOGRO_JUGAR 1
#define NO_JUGO 0

#define GANO_JUGADOR_X 0
#define GANO_JUGADOR_O 1
#define EMPATE -1
#define CONTINUA_JUEGO 5
#define TABLERO_LLENO 9

#define TODO_OK 0
#define ERROR 1

#define REINICIAR 8
#define SALIR 9

void Mostrar_Matriz(int[3][3]);
int Colocar_Ficha (int[3][3],int,int,int);
int Gano_Alguien (int[3][3],int);
int jugada_ganadora_perdedora (int[3][3],int,int);
int jugada_esquina (int[3][3],int,int);
int jugada_centro (int[3][3],int);
int jugada_borde (int[3][3],int);
void EstrategiaPCEmpezando (int [3][3],int,int,int);
void EstrategiaPCSegunda (int [3][3],int,int,int);
void Mostrar_Resultado(int);
void Error (int);

int main(void)
{
    int matriz_tateti[3][3];
    int fila;
    int columna;
	char jugar_otra_vez;
    char computadora;
    char tecla;
    int jugador_PC;
    int jugador_humano;
    int casillero_equivocado;
    int hay_tateti;
    int jugador_actual;
    int Cantidad_de_Jugadas;

	Reinicia:               //Vuelve acá si el usuario presionó 8 en algun momento
    jugar_otra_vez ='S';
    while (jugar_otra_vez == 'S'|| jugar_otra_vez == 's')
	{
        //inicializo variables
         Cantidad_de_Jugadas = 0;
         jugador_actual = JUGADOR_X;
         hay_tateti = CONTINUA_JUEGO;

        //inicializo la matriz
        for(int j = 0; j < 3; j ++)
        {
            for(int i = 0; i < 3; i ++)
            {
                matriz_tateti[i][j] = CASILLERO_VACIO;
            }
        }
        //textcolor(RED);
        printf("TA");
        //textcolor(GREEN);
        printf(" TE");
        //textcolor(YELLOW);
        printf(" TI\n");
        //textcolor(WHITE);

        printf("\nPresione 9 en cualquier momento para salir o 8 para reiniciar.\n");
        printf("\nDesea jugar contra la computadora? (S/N): ");
        fflush(stdin);   //Para que no falle scanf %c
        scanf("%c", &computadora);
        if (computadora == 'S' || computadora == 's')
        {
            printf("\nDesea que comience la PC? (S/N): ");
            fflush(stdin);   //Para que no falle scanf %c
            scanf("%c", &tecla);
            if (tecla == 'S' || tecla == 's')   //juega primero PC
            {
                jugador_PC = JUGADOR_X;
                jugador_humano =JUGADOR_O;

            }
            else  //Juega primero el humano
            {
                jugador_PC = JUGADOR_O;
                jugador_humano =JUGADOR_X;
            }
        }

        //El juego se ejecuta mientras tateti sea == 1, es decir que si alguien gana o empatan tateti pasa a ser 0
        while(hay_tateti == CONTINUA_JUEGO)
        {
            casillero_equivocado = TODO_OK;
            if (jugador_actual == JUGADOR_X)
            {
                printf("\nEs el turno de el jugador X:\n");
            }
            else //JUGADOR_O
            {
                printf("\nEs el turno de el jugador O:\n");
            }
            if ((computadora == 'S' || computadora == 's') && jugador_actual == jugador_PC) //si juega contra PC y es su turno
            {
                if (jugador_PC == JUGADOR_X)  // Estrategia si PC empieza
                {
                    EstrategiaPCEmpezando (matriz_tateti,jugador_PC,jugador_humano,Cantidad_de_Jugadas);
                }
                else  //Estrategia PC empezando segundo
                {
                     EstrategiaPCSegunda (matriz_tateti,jugador_PC,jugador_humano,Cantidad_de_Jugadas);
                }
            }
            else
            {
                fila = 4;
                while (fila >3 ||fila <1)  //Hasta que no ponga un número correcto seguirá pidiendoselo una y otra vez
                {
                    printf("Fila deseada (1-3):");
                    scanf("%d", &fila);
                    if (fila == REINICIAR)
                    {
                        printf("\n\n-----------------------------------------------------------------------------------\n\n");
                        goto Reinicia;  //va a arriba de todo
                    }
                    Error (fila);
                }
                columna = 4;
                while (columna >3 ||columna <1)  //Hasta que no ponga un número correcto seguirá pidiendoselo una y otra vez
                {
                    printf("Columna deseada (0-2):");
                    scanf("%d", &columna);
                    if (columna == REINICIAR)
                    {
                        printf("\n\n----------------------------------------------------------------------------------\n\n");
                        goto Reinicia;
                    }
                    Error (columna);
                }
                casillero_equivocado = Colocar_Ficha(matriz_tateti,fila-1,columna-1, jugador_actual); //coloca la ficha
            }
            Mostrar_Matriz(matriz_tateti);

            hay_tateti = Gano_Alguien(matriz_tateti,Cantidad_de_Jugadas);

            Mostrar_Resultado(hay_tateti);

            if(casillero_equivocado == TODO_OK)       // Si "TODO_OK" le toca al siguiente jugador
            {
                if(jugador_actual == JUGADOR_X)
                {
                    jugador_actual = JUGADOR_O;
                }
                else //jugador_actual O
                {
                    jugador_actual = JUGADOR_X;
                }
                Cantidad_de_Jugadas = Cantidad_de_Jugadas + 1; //Sumo uno a la cantidad de jugadas
            }

            //Si hubo un error se lanza este mensaje y el jugador no cambia
            else
            {
                printf("El casillero esta ocupado, vuelva a ingresar uno nuevo\n");
            }

        }
        fflush(stdin);
        printf("\nDesea jugar nuevamente? (S/N)\n"); //si es "S", VUELVE A EMPEZAR EL JUEGO POR EL WHILE
        scanf("%c", &jugar_otra_vez);
        printf("\n\n\n\n");
	}

	return 0;
}

void Mostrar_Matriz(int matriz[3][3])
{
    int i,j;
	printf("\n-------------\n");
	for(int j = 0; j <=2 ; j ++)
    {
        for(int i = 0; i < 3; i ++)
        {
            if(matriz[j][i] == CASILLERO_DE_X)
            {
                printf("| ");
                //textcolor(BLUE);
                printf("x ");
                //textcolor(WHITE);
            }
            else if(matriz[j][i] == CASILLERO_DE_O)
            {
                printf("| ");
                //textcolor(RED);
                printf("O ");
                //textcolor(WHITE);
            }
            else
            {
                printf("| - ");
            }
        }
        printf("|\n");
        printf("-------------\n");
    }
}

int Colocar_Ficha (int matriz[3][3], int fila, int columna, int jugador)
{
	if(matriz[fila][columna] == CASILLERO_VACIO)
    {
		if(jugador == JUGADOR_X)
        {
			matriz[fila][columna] = CASILLERO_DE_X;
		}
		else //JUGADOR O
		{
			matriz[fila][columna] = CASILLERO_DE_O;
		}
		return TODO_OK;
	}
	else //CASILLERO USADO
    {
		return ERROR;
	}
}

int Gano_Alguien(int matriz[3][3], int Cantidad_de_Jugadas)
{
	//filas
	int primera_fila = matriz[0][0] + matriz[0][1] + matriz[0][2];
	int segunda_fila = matriz[1][0] + matriz[1][1] + matriz[1][2];
	int tercera_fila = matriz[2][0] + matriz[2][1] + matriz[2][2];
	//columnas
	int primera_columna = matriz[0][0] + matriz[1][0] + matriz[2][0];
	int segunda_columna = matriz[0][1] + matriz[1][1] + matriz[2][1];
	int tercera_columna = matriz[0][2] + matriz[1][2] + matriz[2][2];
	//Diagonales
	int primera_diagonal = matriz[0][0] + matriz[1][1] + matriz[2][2];
	int segunda_diagonal = matriz[2][0] + matriz[1][1] + matriz[0][2];

	if(primera_fila == 0 || segunda_fila == 0 || tercera_fila == 0 || primera_columna == 0 || segunda_columna == 0 || tercera_columna == 0 || primera_diagonal == 0 || segunda_diagonal == 0)
    {
		return GANO_JUGADOR_X;
	}
	if(primera_fila == 3 || segunda_fila == 3 || tercera_fila == 3 || primera_columna == 3 || segunda_columna == 3 || tercera_columna == 3 || primera_diagonal == 3 || segunda_diagonal == 3)
	{
		return GANO_JUGADOR_O;
	}

	if(Cantidad_de_Jugadas == TABLERO_LLENO)
    {
		return EMPATE;
	}
	return CONTINUA_JUEGO;
}

int jugada_ganadora_perdedora (int matriz[3][3], int jugador_PC, int jugador_humano)
{
    int i,j,x;
    x=jugador_PC;
    for (j=1; j<=2; j++)    //primero busco jugadas ganadoras , luego jugadas perdedoras
    {
        for (i=0;i<=2;i++)  //verifica filas
        {
            if(matriz[i][0] == x && matriz[i][1] == x && matriz[i][2] == CASILLERO_VACIO)
            {
                matriz[i][2] = jugador_PC;
                return LOGRO_JUGAR;
            }
            if(matriz[i][0] == x && matriz[i][1] == CASILLERO_VACIO && matriz[i][2] == x)
            {
                matriz[i][1] = jugador_PC;
                return LOGRO_JUGAR;
            }
            if(matriz[i][0] == CASILLERO_VACIO && matriz[i][1] == x && matriz[i][2] == x)
            {
                matriz[i][0] = jugador_PC;
                return LOGRO_JUGAR;
            }
        }
        for (i=0;i<=2;i++)  //verifica columnas
        {
            if(matriz[0][i] == x && matriz[1][i] == x && matriz[2][i] == CASILLERO_VACIO)
            {
                matriz[2][i] = jugador_PC;
                return LOGRO_JUGAR;
            }
            if(matriz[0][i] == x && matriz[1][i] == CASILLERO_VACIO && matriz[2][i] == x)
            {
                matriz[1][i] = jugador_PC;
                return LOGRO_JUGAR;
            }
            if(matriz[0][i] == CASILLERO_VACIO && matriz[1][i] == x && matriz[2][i] == x)
            {
                matriz[0][i] = jugador_PC;
                return LOGRO_JUGAR;
            }
        }
        if(matriz[0][0] == x && matriz[1][1] == x && matriz[2][2] == CASILLERO_VACIO)
        {
            matriz[2][2] = jugador_PC;
            return LOGRO_JUGAR;
        }
        if(matriz[0][0] == x && matriz[1][1] == CASILLERO_VACIO && matriz[2][2] == x)
        {
            matriz[1][1] = jugador_PC;
            return LOGRO_JUGAR;
        }
        if(matriz[0][0] == CASILLERO_VACIO && matriz[1][1] == x && matriz[2][2]== x)
        {
            matriz[0][0] = jugador_PC;
            return LOGRO_JUGAR;
        }
        if(matriz[0][2] == x && matriz[1][1] == x && matriz[2][0] == CASILLERO_VACIO)
        {
            matriz[2][0] = jugador_PC;
            return LOGRO_JUGAR;
        }
        if(matriz[0][2] == x && matriz[1][1] == CASILLERO_VACIO && matriz[2][0] == x)
        {
            matriz[1][1] = jugador_PC;
            return LOGRO_JUGAR;
        }
        if(matriz[0][2] == CASILLERO_VACIO && matriz[1][1] == x && matriz[2][0] == x)
        {
            matriz[0][2] = jugador_PC;
            return LOGRO_JUGAR;
        }
        x=jugador_humano;   //ahora busco jugadas perdedoras
    }
    return NO_JUGO;
}

int jugada_esquina (int matriz[3][3],int Cantidad_de_Jugadas,int jugador_PC)
{
    if (matriz [0][0]==CASILLERO_VACIO)
    {
        matriz[0][0] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [0][2]== CASILLERO_VACIO && (Cantidad_de_Jugadas != 2 || matriz[0][1] == jugador_PC || matriz[0][1] == CASILLERO_VACIO)) // si el oponente puso matriz[0][1] en su primer jugada no conviene llenar ahora matriz [0][2]
    {
        matriz[0][2] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [2][0]== CASILLERO_VACIO)
    {
        matriz[2][0] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [2][2]== CASILLERO_VACIO)
    {
        matriz[2][2] = jugador_PC;
        return LOGRO_JUGAR;
    }
    return NO_JUGO;
}

int jugada_centro (int matriz[3][3],int jugador_PC)
{
    if (matriz [1][1]== CASILLERO_VACIO)
    {
        matriz[1][1] = jugador_PC;
        return LOGRO_JUGAR;
    }
    return NO_JUGO;
}

int jugada_borde (int matriz[3][3],int jugador_PC)
{
    if (matriz [0][1]== CASILLERO_VACIO)
    {
        matriz[0][1] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [1][0]== CASILLERO_VACIO)
    {
        matriz[1][0] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [1][2]== CASILLERO_VACIO)
    {
        matriz[1][2] = jugador_PC;
        return LOGRO_JUGAR;
    }
    if (matriz [2][1]== CASILLERO_VACIO)
    {
        matriz[2][1] = jugador_PC;
        return LOGRO_JUGAR;
    }
    return NO_JUGO;
}

void EstrategiaPCEmpezando (int matriz_tateti[3][3],int jugador_PC,int jugador_humano, int cant) // Estrategia si PC empieza
{
    if (jugada_ganadora_perdedora (matriz_tateti,jugador_PC,jugador_humano)== NO_JUGO) // si puedo ganar o perder juego esa opcion
    {
        if (cant == 4 && matriz_tateti[0][1] + matriz_tateti[1][0] + matriz_tateti[1][2] + matriz_tateti[2][1]== 20) // 9+9+1+1 si el oponente jugo dos bordes y PC dos esquinas, conviene jugar al centro
        {
            jugada_centro (matriz_tateti,jugador_PC);
        }
        else
        {
            if (jugada_esquina (matriz_tateti,cant,jugador_PC)== NO_JUGO)        // si no juego esquina
            {
                if (jugada_centro (matriz_tateti,jugador_PC)== NO_JUGO)         // si no juego centro
                {
                    jugada_borde (matriz_tateti,jugador_PC);             // si no juego borde
                }
            }
        }

    }
}

void EstrategiaPCSegunda (int matriz_tateti[3][3],int jugador_PC,int jugador_humano, int cant)   //Estrategia PC empezando segundo
{
    if (jugada_ganadora_perdedora (matriz_tateti,jugador_PC,jugador_humano)==NO_JUGO) // si puedo ganar o perder juego esa opcion
    {
        if (jugada_centro (matriz_tateti,jugador_PC)== NO_JUGO)            //trato de empezar con el centro
        {
            if (cant == 3 && (matriz_tateti[0][1] + matriz_tateti[1][0] + matriz_tateti[1][2] + matriz_tateti[2][1]== 27 ||matriz_tateti[0][1] + matriz_tateti[1][0] + matriz_tateti[1][2] + matriz_tateti[2][1]== 18 ))
            {
                if (matriz_tateti[0][1] + matriz_tateti[1][0] == jugador_humano)  //caso particular: si dos bordes son del humano tapar esa esquina
                {
                    matriz_tateti[0][0] = jugador_PC;
                }
                else if (matriz_tateti[1][0] + matriz_tateti[2][1] == jugador_humano)
                {
                    matriz_tateti[2][0] = jugador_PC;
                }
                else if (matriz_tateti[0][1] + matriz_tateti[1][2] == jugador_humano)
                {
                    matriz_tateti[0][2] = jugador_PC;
                }
                else if (matriz_tateti[2][1] + matriz_tateti[1][2] == jugador_humano)
                {
                    matriz_tateti[2][2] = jugador_PC;
                }
                else
                {
                    jugada_esquina (matriz_tateti,cant,jugador_PC); // Si el jugador puso en dos bordes o en borde y esquina
                }
             }
            else if (matriz_tateti[1][1] == jugador_humano) //Si el humano tomo el centro ir a las esquinas en primer lugar
            {
                if (jugada_esquina (matriz_tateti,cant,jugador_PC)== NO_JUGO)  // si no juego esquina
                {
                    jugada_borde (matriz_tateti,jugador_PC);            //si no juego borde
                }
            }
            else
            {
                if (jugada_borde (matriz_tateti,jugador_PC)== NO_JUGO)         // si no juego borde
                {
                    jugada_esquina (matriz_tateti,cant,jugador_PC);     //si no juego esquina
                }
            }
        }

    }
}

void Mostrar_Resultado(int resultado)
{
	if(resultado == GANO_JUGADOR_X)
    {
		printf("El ganador es el jugador X\n");
	}
	if(resultado == GANO_JUGADOR_O)
	{
		printf("El ganador es el jugador O\n");
	}
	if(resultado == EMPATE)
	{
		printf("Los jugadores empataron\n");
	}
}

void Error (int tecla)
{
    if (tecla>3 || tecla<0)
    {
        if (tecla == SALIR)
        {
            printf("\nHasta la proxima!\n");
            exit(0); //Termina el Programa
        }
        printf("\nERROR. Ingrese 1,2 o 3.\n");
    }
}
