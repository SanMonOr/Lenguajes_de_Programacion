#include <stdio.h>
#include <string.h>
#define N_ESTUDIANTES 3

struct Profesor
{
    int id;
    char password[12];
    char nombre[35];
};

struct Estudiante
{
    int id;
    char password[12];
    char nombre[35];
    float notas[3];
};

void clearBuffer();
void menuPrincipal();
void menuProfesor(struct Estudiante *, const char *);
void menuEstudiante(const struct Estudiante);
int autenticarProfesor(const int, const char *);
int autenticarEstudiante(const struct Estudiante *);
int autenticarIdEstudiante(const struct Estudiante *);
void consultarNotas(const float *);
void consultarPromedio(const float *);
void consultarValorAlto(const float *);

int main()
{
    int op, keeper = 1, index;
    struct Profesor profesor = {100, "1234", "Geovanny Poveda"};
    struct Estudiante estudiantes[N_ESTUDIANTES] = { {1, "1234", "Santiago Monsalve", {0.0f, 0.0f, 0.0f}},
                                        {2, "2345", "Daniela Silva", {0.0f, 0.0f, 0.0f}},
                                        {3, "3456", "Sebastian Zambrano", {0.0f, 0.0f, 0.0f}} };
    
    do{
        op = 0;

        menuPrincipal();
        scanf("%d", &op);
        clearBuffer();

        switch (op)
        {
            case 1:
                index = autenticarEstudiante(estudiantes);

                if (index)
                {
                    index -= 1;
                    menuEstudiante(estudiantes[index]);
                }
                break;
            
            case 2:
                if (autenticarProfesor(profesor.id, profesor.password))
                {                
                    menuProfesor(estudiantes, profesor.nombre);
                }
                break;
            
            case 3:
                keeper = 0;
                break;

            default:
                break;
        }
    } while (keeper);
    
    return 0;
}

void menuPrincipal()
{
    printf("--------- SERVICIO ACADÉMICO COLEGIO CASITA AZUL ---------\n\n"
            "¿Quién eres?\n"
            "1. Estudiante\n"
            "2. Profesor\n"
            "3. Salir\n"
            "\n: ");
}

int autenticarProfesor(const int _id, const char *_psw)
{
    int id, keeper = 1, op, retorno = 0;
    char psw[12];
    
    do {
        op = 0;

        printf("Ingrese su id: ");
        scanf("%i", &id);
        clearBuffer();
        printf("Ingrese su clave: ");
        scanf("%s", psw);
        clearBuffer();
        
        // printf("%s - %s", psw, _psw);
        
        if (id == _id)
        {
            if (strcmp(psw, _psw) == 0)
            {
                retorno = 1;
                keeper = 0;
            }
        }
        
        if (retorno != 1)
        {
            printf("\n\n¡ERROR: id o clave incorrecta!\n\n");
            
            do{
                printf("¿Que desea hacer:\n"
                        "1. Seguir intentando\n"
                        "2. Regresar al menu principal\n"
                        "\n: ");
                scanf("%i", &op);
                clearBuffer();
                
            } while (op != 1 && op != 2);
            
            if (op == 2)
            {
                keeper = 0;
            }
        }
        
    } while (keeper);
    
    printf("\n");
    
    return retorno;
}

int autenticarEstudiante(const struct Estudiante *_estudiantes)
{
    int id, keeper = 1, op, retorno = 0;
    char psw[12];
    
    do {
        op = 0;

        printf("Ingrese su id: ");
        scanf("%i", &id);
        clearBuffer();
        printf("Ingrese su clave: ");
        scanf("%s", psw);
        clearBuffer();
        
        for (int i = 0; i < N_ESTUDIANTES; i++)
        {
            // printf("id: %i clave dada: %s - clave original: %s\n", i+1, psw, _estudiantes[i].password);
            
            if (_estudiantes[i].id == id)
            {
                if (strcmp(_estudiantes[i].password, psw) == 0)
                {
                    retorno = i + 1;
                    keeper = 0;
                }
            }
        }
        
        if (retorno == 0)
        {
            printf("\n\n¡ERROR: id o clave incorrecta!\n\n");
            
            do{
                printf("¿Que desea hacer:\n"
                        "1. Seguir intentando\n"
                        "2. Regresar al menu principal\n"
                        "\n: ");
                scanf("%i", &op);
                clearBuffer();
                
            } while (op != 1 && op != 2);
            
            if (op == 2)
            {
                keeper = 0;
            }
        }        
    } while (keeper);
    
    printf("\n");
    
    return retorno;
}

int autenticarIdEstudiante(const struct Estudiante *_estudiantes)
{
    int op, id;
    
    do
    {
        op = 0;

        printf("\nIngrese el id del estudiante: ");
        scanf("%i", &id);
        clearBuffer();
            
        for (int i = 0; i < 3; i++)
        {
            if (id == _estudiantes[i].id)
                return i;
        }
            
        printf("\nError: id de estudiante no encontrado\n\n");
        
        do 
        {
            printf("¿Que desea hacer:\n"
                    "1. Seguir intentando\n"
                    "2. Regresar al menu del profesor\n"
                    "\n: ");
            scanf("%i", &op);
            clearBuffer();
            
            if (op == 1)
            {
                break;
            }
            else if (op == 2)
            {
                printf("\n");
                return -1;
            }
            
        } while (1);
        
        
    } while (1);
}

void menuProfesor(struct Estudiante *_estudiantes, const char *_nombre)
{
    int keeper = 1, op, op2, error01 = 0;
    float nota;

    do
    {
        op = 0;
        printf("Bienvenido profesor %s \n\n"
                "¿Qué desea hacer?\n"
                "1. Ingresar notas\n"
                "2. Salir\n"
                ": ", _nombre);
        scanf("%i", &op);
        clearBuffer();
        
        if (op == 1)
        {
            op2 = autenticarIdEstudiante(_estudiantes);
            
            if (op2 >= 0)
            {
                for (int j = 0; j < 3; j++)
                {
                    nota = 0;

                    printf("Ingrese la nota %i: ", j + 1);
                    scanf("%f", &nota);
                    clearBuffer();

                    if (nota > 0)
                        _estudiantes[op2].notas[j] = nota; 
                    else    
                    {
                        printf("¡\nError al cargar nota!\n\n");
                        _estudiantes[op2].notas[j] = 0.0f;
                        error01 = 1;
                    }
                }
                if (error01 == 0)
                    printf("\n¡Éxito!\n\n");
            }
        }
        
        else if (op == 2)
            keeper = 0;
        else
            printf("\n¡Ingrese un valor válido!\n\n");
            
    } while (keeper);    
}

void menuEstudiante(const struct Estudiante _estudiante)
{
    int op, keeper = 1;
    
    do{
        op = 0;

        printf("Bienvenido estudiante %s \n\n"
                    "¿Qué desea hacer?\n"
                    "1. Consultar notas\n"
                    "2. Consultar promedio\n"
                    "3. Consultar nota más alta\n"
                    "4. Salir\n"
                    ": ", _estudiante.nombre);
        scanf("%i", &op);
        clearBuffer();
        
        switch (op)
        {
            case 1:
                consultarNotas(_estudiante.notas);
                break;
            case 2:
                consultarPromedio(_estudiante.notas);
                break;
            case 3:
                consultarValorAlto(_estudiante.notas);
                break;
            case 4:
                keeper = 0;
                break;
            default:
                printf("\n¡Ingrese un valor válido!\n\n");
                break;
        }
        
    } while (keeper);
}

void consultarNotas(const float *_notas)
{
    putchar('\n');
    for (int i = 0; i < 3; i++)
    {
        printf("Nota %i: %.2f\n", i + 1, _notas[i]);
    }
    putchar('\n');
}

void consultarPromedio(const float *_notas)
{
    float promedio = 0;
    
    for (int i = 0; i < 3; i++)
    {
        promedio += _notas[i];
    }
    
    printf("\nSu promedio es: %.2f\n\n", promedio / 3);
}

void consultarValorAlto(const float *_notas)
{
    float valorAlto = 0;
    
    for (int i = 0; i < 3; i++)
    {
        if (_notas[i] > valorAlto)
            valorAlto = _notas[i];
    }
    
    printf("\nSu nota más alta actualmente es: %.2f\n\n", valorAlto);
}

void clearBuffer()
{
    while (getchar() != '\n')
        ;
}
