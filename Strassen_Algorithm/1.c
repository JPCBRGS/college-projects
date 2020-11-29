#include <stdlib.h>
#include <stdio.h>

//protótipos das funções que serão usadas:

long int **ALLOC_Matrix(long int n);                                                //função para alocar a matriz
long int **DEALLOC_Matrix(long int n, long int **mat);                              //função para desalocar matriz
void Matrix_Prod(long int n, long int **mat_a, long int **mat_b, long int **mat_C); //função para calcular a matriz produto

// *** INÍCIO DA FUNÇÃO MAIN ***
void main()
{

    long int n;          //número de linhas e colunas das matrizes
    long int **matrix_A; //criação da matriz A
    long int **matrix_B; //criação da matriz B
    long int **matrix_C; //criação da matriz produto das matrizes A e B
    long int i, j;       //variáveis auxiliares

    //inserção de n (número de colunas e linhas)
    scanf("%li", &n);

    //chamada da função para alocar dinamicamente as matrizes
    matrix_A = ALLOC_Matrix(n);
    matrix_B = ALLOC_Matrix(n);
    matrix_C = ALLOC_Matrix(n);

    //entrada com os valores da primeira matriz
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%li", &matrix_A[i][j]);
        }
    }

    //entrada com os valores da segunda matriz
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%li", &matrix_B[i][j]);
        }
    }

    //chamada da função para calcular o produto das matrizes A e B
    Matrix_Prod(n, matrix_A, matrix_B, matrix_C);

    //exposição da matriz produto C
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%li", matrix_C[i][j]);
            if (j < n - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    //desalocando a memória para as três matrizes
    matrix_A = DEALLOC_Matrix(n, matrix_A);
    matrix_B = DEALLOC_Matrix(n, matrix_B);
    matrix_C = DEALLOC_Matrix(n, matrix_C);
}
// *** FIM DA FUNÇÃO MAIN ***

//corpo da função que aloca a matriz
long int **ALLOC_Matrix(long int n)
{

    long int **mat; //ponteiro para a matriz

    //caso de entrada menor que 1
    if (n < 1)
    {
        exit(0);
    }

    mat = (long int **)malloc(n * sizeof(long int *)); //alocação das linhas da matriz

    if (!mat)
    {
        exit(0);
    }

    long int i; //variável auxiliar

    for (i = 0; i < n; i++)
    {
        mat[i] = (long int *)malloc(n * sizeof(long int));

        if (!mat[i]) //checagem quanto ao armazenamento
        {
            exit(0);
        }
    }
    return mat;
}

//corpo da função que multiplica as matrizes
void Matrix_Prod(long int n, long int **mat_a, long int **mat_b, long int **mat_c)
{

    long int i, j, k; //variáveis auxiliares
    long int soma;    //armazena as multiplicações entre linhas e colunas de A e B

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            soma = 0;
            for (k = 0; k < n; k++)
            {
                soma = soma + mat_a[i][k] * mat_b[k][j];
            }
            mat_c[i][j] = soma;
        }
    }
}

//corpo da função que desaloca a matriz
long int **DEALLOC_Matrix(long int n, long int **mat)
{

    long int i; //auxiliar

    for (i = 0; i < n; i++)
    {
        free(mat[i]);
    }

    free(mat);
    return (NULL);
}