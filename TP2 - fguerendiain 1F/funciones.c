#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "string.h"
#include "../ownLibraries/userInputOutput.h"
#include "../ownLibraries/screenSystemShow.h"

#define MAXTRIES 3
#define STRINGBUFFER 4000
#define EPEOPLELENGTH 20

#define ADD 1
#define ERREASE 2
#define PRINTLIST 3
#define PRINTGRAPHIC 4
#define EXIT 5

/** \brief ejecuta la opcion elegida por el usuario
 * \param (option) recibe opcion ingresada por el usuario
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 * \return (0 = finaliza el programa | 1 = continua ejecutando)
 */

int runFunctionMenu(int option, Epeople *person, long int personLenght)
{
    int exit = 1;

    switch(option)
    {
        case ADD:   //opcion 1 para la carga de personas
            cleanScreen();
            addNewPerson(person,personLenght);
          break;

        case ERREASE:   //opcion 2 para borrar personas cargadas
            cleanScreen();
            delPerson(person,personLenght);
        break;

        case PRINTLIST: //opcion 3 para imprimir un listado de las personas cargadas
            cleanScreen();
            printListOfPeople(person,personLenght);
        break;

        case PRINTGRAPHIC:  //opcion 4 para imprimir el grafico
            cleanScreen();
            definePercentageOfAges(person,personLenght);
        break;

        case EXIT: //opcion 5 para salir del programa
            exit = 0;
        break;
    }
    return exit;
}

/** \brief realiza el alta de una nueva persona validando disponibilidad
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 * \return 0 se realizo la carga, -1 no se pudo realizar la carga, -2 el usuario ingreso mal un dato
 *
 */

int addNewPerson(Epeople *person, long int personLenght)
{
    long int index;
    int checkName;
    int checkLastName;
    int checkAge;
    int checkDni;
    int flagString = 0;
    int i;


    index=searchFreeIndex(person,personLenght); //Busca la primer posicion libre del array de personas

    if (index!= -1)
    {
        checkName = getUserInputString(person[index].name,3,30,"Ingrese el nombre de la persona:\n","Por favor ingrese un nombre valido:\n",STRINGBUFFER,MAXTRIES);
        if (checkName != 0) //valida el ingreso del string bajo los parametros establecidos
        {
            printf("\nNombre invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
        }
        else //valida que dentro del string no se hayan ingresado numeros
        {
            for(i=0; person[index].name[i]!='\0'; i++)
            {
                if( person[index].name[i] >= '0' && person[index].name[i] <='9' )
                {
                    flagString = 1;
                }
            }

            if(flagString)
            {
            printf("\nNombre invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
            }
        }

        checkLastName = getUserInputString(person[index].lastName,3,30,"Ingrese el apellido de la persona:\n","Por favor ingrese un apellido valido:\n",STRINGBUFFER,MAXTRIES);
        if (checkLastName != 0)     //valida el ingreso del string bajo los parametros establecidos
        {
            printf("\nApellido invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
        }
        else
        {
            for(i=0; person[index].lastName[i]!='\0'; i++) //valida que dentro del string no se hayan ingresado numeros
            {
                if( person[index].lastName[i] >= '0' && person[index].lastName[i] <='9' )
                {
                    flagString = 1;
                }
            }

            if(flagString)
            {
            printf("\nNombre invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
            }
        }

        checkAge = getUserInputShortInt(&person[index].age,0,120,"Ingrese la edad de la persona:\n","Por favor ingrese una edad valida:\n",MAXTRIES);
        if (checkAge != 0) //valida el ingreso de un int bajo los parametros establecidos
        {
            printf("\nEdad invalida, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
        }
        checkDni = getUserInputString(person[index].dni,7,8,"Ingrese el DNI de la persona (solo numeros):\n","Por favor ingrese DNI valido (solo numeros):\n",STRINGBUFFER,MAXTRIES);
        if(checkDni != 0)   //valida el ingreso del string bajo los parametros establecidos
        {
            printf("\nDNI invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
        }
        else if(checkDni = 0)
        {
            for(i=0; person[index].dni[i]!='\0'; i++)   //valida que dentro del string se hayan ingresado solo numeros
            {
                if( !(person[index].dni[i] >= '0' && person[index].dni[i] <='9') )
                {
                    flagString = 1;
                }
            }

            if(flagString)
            {
            printf("\nNombre invalido, por favor vuelva a intentarlo\n");
            erradicateStdin();
            pauseScreen();
            return -2;
            }
        }
        else // al ser la ultima instancia de carga se determina la carga correcta de todos los campos
        {
            person[index].state = 1;
            printf("\nLos datos se cargaron correctamente\n");
            erradicateStdin();
            pauseScreen();
        }
    }
    else
    {
        printf("No existen posiciones libres,\npor favor borre alguna para poder ingresar nuevos datos\n\n");
        erradicateStdin();
        pauseScreen();
        return -1;
    }
    return 0;
}

/** \brief busca el primer indice libre
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 * \return devuelve el numero del indice o -1 en caso que no haya posiciones libres
 *
 */

long searchFreeIndex(Epeople *person, long int personLenght)
{
    long int i;

    for(i=0; i < personLenght; i++)
    {
        if(person[i].state == 0)
            return i;
    }
    return -1;
}

/** \brief inicializa en '0' y '\0' los campos del array person
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 *
 */

void intializeArrayState(Epeople *person, long int personLenght)
{
    long int i;
    long int j;
    long int k;

    for(i=0; i < personLenght; i++)
    {
        person[i].state = 0;
        person[i].age = 0;

        for(j=0; j<31; j++)
        {
            person[i].name[j] = '\0';
            person[i].lastName[j] = '\0';

            for(k=0;k<11; k++)
            {
                person[i].dni[k] = '\0';
            }
        }
    }
}

/** \brief borrado logido de un elemento de la estructura person
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 *
 */

void delPerson(Epeople *person, long int personLenght)
{
    long int index;

    getUserInputLongInt(&index,0,personLenght,"Ingrese la posicion a eliminar:\n","Por favor, ingrese una posicion valida:\n",MAXTRIES);

    if(person[index].state != 0)
    {
        person[index].state = 0;
        printf("Se eliminaron los datos de la posicion %ld\n", index);
        pauseScreen();
    }
    else
    {
        printf("La posicion %ld se encuentra libre\n", index);
        pauseScreen();
    }
}

/** \brief imprime todos los elementos de person con state en 1
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 *
 */

void printListOfPeople(Epeople *person, long int personLenght)
{
    long int i;

    sortArrayByName(person,personLenght);

    printf("INDICE\t\tNOMBRE\t\tAPELLIDO\t\tEDAD\t\tDNI\n");

    for(i=0 ; i< personLenght; i++)
    {
            if(person[i].state != 0)
            {
                stringSetCase(person[i].name,3);
                stringSetCase(person[i].lastName,3);

                printf("%ld\t\t%s\t\t%s\t\t%hi\t\t%s\n",i,person[i].name,person[i].lastName,person[i].age,person[i].dni);
            }
    }
    pauseScreen();
}

/** \brief Ordena los elementos alfabeticamente por nombre de persona
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 *
 */

void sortArrayByName(Epeople *person, long int personLenght)
{
    long i;
    long j;
    Epeople auxPerson;

    for(i=0; i<personLenght-1; i++)
    {
        for(j=i+1; j<personLenght; j++)
        {
            if(strcmp(person[i].name,person[j].name)>0)
            {
                auxPerson = person[i];
                person[i] = person[j];
                person[j] = auxPerson;
            }
        }
    }
}

/** \brief grafica el porcentaje de las edades <18 19-35 >35
 * \param (person) recibe la estructura persona
 * \param (personLenght) recibe el tamaño del array persona
 *
 */

void definePercentageOfAges(Epeople *person, long int personLenght)
{
    long int i;
    int under18Count = 0;
    int between19_35Count = 0;
    int more35Count = 0;
    char graficSpace[3][EPEOPLELENGTH];
    int flagNoData = 0;

    for(i=0; i<personLenght; i++)
    {
        if(person[i].state != 0)
        {
            flagNoData = 1;
        }
    }

    if(flagNoData == 0)
    {
        cleanScreen();
        printf("Por favor ingrese al menos una persona\n");
        pauseScreen();
    }
    else
    {
        for(i=0; i<personLenght; i++)
        {
            if(person[i].state != 0)
            {
                if(person[i].age < 18)
                {
                    under18Count++;
                }
                else if(person[i].age >35)
                {
                    more35Count++;
                }
                else
                {
                    between19_35Count++;
                }
            }
        }

        for(i = 0; i < EPEOPLELENGTH;i++)
        {
            if(i < under18Count)
            {
                graficSpace[0][i] = '*';
            }
            else
            {
                graficSpace[0][i] = ' ';
            }

            if(i < between19_35Count)
            {
                graficSpace[1][i] = '*';
            }
            else
            {
                graficSpace[1][i] = ' ';
            }
            if(i < more35Count)
            {
                graficSpace[2][i] = '*';
            }
            else
            {
                graficSpace[2][i] = ' ';
            }
        }

        for(i=EPEOPLELENGTH-1; i >= 0; i--)
        {
            printf("%c\t  %c  \t%c\n",graficSpace[0][i],graficSpace[1][i],graficSpace[2][i]);
        }
        printf("<18\t19-35\t>35\n");
        pauseScreen();
    }
}


