#include <stdio.h>
#include <stdlib.h>

//protótipos das funções que serão usadas:

long int **ALLOC_Matrix(long int n);                                                                                                   //função para alocar a matriz
long int **DEALLOC_Matrix(long int n, long int **mat);                                                                                 //função para desalocar matriz
long int MP2(long int n);                                                                                                              //calcular tamanho das matrizes auxiliares
void matSum(long int n, long int **mat_a, long int **mat_b, long int **mat_c);                                                         //função que soma matrizes
void matSubtract(long int n, long int **mat_a, long int **mat_b, long int **mat_c);                                                    //função que subtrai matrizes
void MatCpy(long int beginline, long int begincolumn, long int maxline, long int maxcolumn, long int **mat_a, long int **mat_destiny); //função que copia matrizes
long int **Strassen(long int n, long int **mat_a, long int **mat_b);                                                                   //função que multiplica as matrizes
void unionMatrix(long int **mat, long int **mat11, long int **mat12, long int **mat21, long int **mat22, int size);                    //função que une matrizes

//Função que expõe matrizes
void matrix_show(long int **mat,int n){

    long int i;
    long int j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%li", mat[i][j]);
            if (j < n - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    
}

int main()
{
    long int n;          //número de linhas e colunas das matrizes
    long int **matrix_A; //criação da matriz A
    long int **matrix_B; //criação da matriz B
    long int **matrix_C;
    long int i, j; //variáveis auxiliares

    //inserção de n (número de colunas e linhas)
    scanf("%li", &n);

    //chamada da função para alocar as matrizes
    matrix_A = ALLOC_Matrix(n);
    matrix_B = ALLOC_Matrix(n);

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

    long int a = MP2(n); //variável auxiliar para guardar a menor potência de 2 maior que N
    if (a > 0)
    { //caso da matriz não ser uma potência de 2

        //criação de todas as matrizes auxiliares
        long int **matrix_AAUX;
        long int **matrix_BAUX;
        long int **matrix_CAUX;

        matrix_AAUX = ALLOC_Matrix(a);
        matrix_BAUX = ALLOC_Matrix(a);
        
        matrix_C = ALLOC_Matrix(n);
        for (i = 0; i < a; i++)
        {
            for (j = 0; j < a; j++)
            {
                if (i >= n || j >= n)
                {
                    matrix_AAUX[i][j] = 0;
                    matrix_BAUX[i][j] = 0;
                }
                else
                {
                    matrix_AAUX[i][j] = matrix_A[i][j];
                    matrix_BAUX[i][j] = matrix_B[i][j];
                }
            }
        }

        matrix_CAUX = Strassen(a, matrix_AAUX, matrix_BAUX);

        
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                matrix_C[i][j] = matrix_CAUX[i][j]; //transferindo valores da matriz produto auxiliar para a real
            }
        }
        matrix_show(matrix_C,n);
        
        //desalocando matrizes auxiliares
        matrix_AAUX = DEALLOC_Matrix(a, matrix_AAUX);
        matrix_BAUX = DEALLOC_Matrix(a, matrix_BAUX);
        matrix_CAUX = DEALLOC_Matrix(a, matrix_CAUX);
        
    }
    else
    { //caso de n ser uma potência de 2 (dispensa uso de matrizes auxiliares)
        matrix_C = Strassen(n, matrix_A, matrix_B);
    }
    
    //Desalocando matrizes
    matrix_A = DEALLOC_Matrix(n, matrix_A);
    matrix_B = DEALLOC_Matrix(n, matrix_B);
    matrix_C = DEALLOC_Matrix(n, matrix_C);
}

long int **ALLOC_Matrix(long int n) //função que aloca as matrizes
{

    long int **mat; //ponteiro para a matriz

    //caso de entrada menor que 1
    if (n < 1)
    {
        exit(0);
    }

    mat = (long int **)calloc(n, sizeof(long int *)); //alocação das linhas da matriz

    if (!mat)
    {
        exit(0);
    }

    long int i; //variável auxiliar

    for (i = 0; i < n; i++)
    {
        mat[i] = (long int *)calloc(n, sizeof(long int));

        if (!mat[i]) //checagem quanto ao armazenamento
        {
            exit(0);
        }
    }
    return mat;
}

long int MP2(long int n) //corpo da função para calcular o tamanho das matrizes auxiliares
{
    long int a = 1;

    while (a < n)
    {
        a = a << 1;

        if (a == n)
        {
            return 0;
        }
    }
    return a;
}

long int **Strassen(long int n, long int **mat_a, long int **mat_b)
{
    long int **mat_c;
    mat_c = ALLOC_Matrix(n);

    if (n == 1)
    {
        mat_c[0][0] = mat_a[0][0] * mat_b[0][0];
        return mat_c;
    }

    long int **A11;
    long int **A12;
    long int **A21;
    long int **A22;
    long int **B11;
    long int **B12;
    long int **B21;
    long int **B22;

    long int mid = n / 2;

    A11 = ALLOC_Matrix(mid);
    A12 = ALLOC_Matrix(mid);
    A21 = ALLOC_Matrix(mid);
    A22 = ALLOC_Matrix(mid);
    B11 = ALLOC_Matrix(mid);
    B12 = ALLOC_Matrix(mid);
    B21 = ALLOC_Matrix(mid);
    B22 = ALLOC_Matrix(mid);

    MatCpy(0, 0, mid, mid, mat_a, A11);
    MatCpy(0, mid, mid, n, mat_a, A12);
    MatCpy(mid, 0, n, mid, mat_a, A21);
    MatCpy(mid, mid, n, n, mat_a, A22);
    MatCpy(0, 0, mid, mid, mat_b, B11);
    MatCpy(0, mid, mid, n, mat_b, B12);
    MatCpy(mid, 0, n, mid, mat_b, B21);
    MatCpy(mid, mid, n, n, mat_b, B22);

    long int **M1;
    long int **M2;
    long int **M3;
    long int **M4;
    long int **M5;
    long int **M6;
    long int **M7;


    //Matrizes auxiliares de soma
    long int **MatAux;
    long int **MatAux2;
    MatAux = ALLOC_Matrix(mid);
    MatAux2 = ALLOC_Matrix(mid);

    //Calculando M1 a M7
    matSum(mid, A11, A22, MatAux);
    matSum(mid, B11, B22, MatAux2);
    M1 = Strassen(mid, MatAux, MatAux2);

    matSum(mid, A21, A22, MatAux);
    M2 = Strassen(mid, MatAux, B11);

    matSubtract(mid, B12, B22, MatAux);
    M3 = Strassen(mid, A11, MatAux);

    matSubtract(mid, B21, B11, MatAux);
    M4 = Strassen(mid, A22, MatAux);

    matSum(mid, A11, A12, MatAux);
    M5 = Strassen(mid, MatAux, B22);


    matSubtract(mid, A21, A11, MatAux);
    matSum(mid, B11, B12, MatAux2);
    M6 = Strassen(mid, MatAux, MatAux2);

    matSubtract(mid, A12, A22, MatAux);

    matSum(mid, B21, B22, MatAux2);
    M7 = Strassen(mid, MatAux, MatAux2);

    //criando submatrizes C
    long int **C11;
    long int **C12;
    long int **C21;
    long int **C22;

    //alocando submatrizes de C
    C11 = ALLOC_Matrix(mid);
    C12 = ALLOC_Matrix(mid);
    C21 = ALLOC_Matrix(mid);
    C22 = ALLOC_Matrix(mid);

    //atribuindo valores as submatrizes de C

    //C1,1
    matSum(mid, M1, M4, C11);
    matSubtract(mid, C11, M5, C11);
    matSum(mid, C11, M7, C11);

    //C1,2
    matSum(mid, M3, M5, C12);

    //C2,1
    matSum(mid, M2, M4, C21);

    //C2,2
    matSubtract(mid, M1, M2, C22);
    matSum(mid, C22, M3, C22);
    matSum(mid, C22, M6, C22);



    unionMatrix(mat_c, C11, C12, C21, C22, mid);


    A11 = DEALLOC_Matrix(mid, A11);
    A12 = DEALLOC_Matrix(mid, A12);
    A21 = DEALLOC_Matrix(mid, A21);
    A22 = DEALLOC_Matrix(mid, A22);
    B11 = DEALLOC_Matrix(mid, B11);
    B12 = DEALLOC_Matrix(mid, B12);
    B21 = DEALLOC_Matrix(mid, B21);
    B22 = DEALLOC_Matrix(mid, B22);
    M1 = DEALLOC_Matrix(mid, M1);
    M2 = DEALLOC_Matrix(mid, M2);
    M3 = DEALLOC_Matrix(mid, M3);
    M4 = DEALLOC_Matrix(mid, M4);
    M5 = DEALLOC_Matrix(mid, M5);
    M6 = DEALLOC_Matrix(mid, M6);
    M7 = DEALLOC_Matrix(mid, M7);
    C11 = DEALLOC_Matrix(mid, C11);
    C12 = DEALLOC_Matrix(mid, C12);
    C21 = DEALLOC_Matrix(mid, C21);
    C22 = DEALLOC_Matrix(mid, C22);
    MatAux = DEALLOC_Matrix(mid,MatAux);
    MatAux2 = DEALLOC_Matrix(mid,MatAux2);
    return mat_c;
}

//corpo da função que soma matrizes
void matSum(long int n, long int **mat_a, long int **mat_b, long int **mat_c)
{

    long int i;
    long int j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat_c[i][j] = mat_a[i][j] + mat_b[i][j];
        }
    }
}

void matSubtract(long int n, long int **mat_a, long int **mat_b, long int **mat_c)
{

    long int i;
    long int j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat_c[i][j] = mat_a[i][j] - mat_b[i][j];
        }
    }
}

//corpo da função que copia matrizes
void MatCpy(long int beginline, long int begincolumn, long int maxline, long int maxcolumn, long int **mat_a, long int **mat_destiny)
{
    int i = 0;
    int j = 0;

    int deltaLine = maxline - beginline;
    int deltaCol = maxcolumn - begincolumn;

    for (i = 0; i < deltaLine; i++)
    {
        for (j = 0; j < deltaCol; j++)
        {
            mat_destiny[i][j] = mat_a[beginline + i][begincolumn + j];
        }
    }
}

//recebe 4 matrizes de tamanho size x size, e faz a união de todas em uma única matriz de tamanho (size * 2) x (size * 2)
void unionMatrix(long int **mat, long int **mat11, long int **mat12, long int **mat21, long int **mat22, int size)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < size * 2; i++)
    {
        for (j = 0; j < size * 2; j++)
        {
            if (i < size && j < size)
            { //Quadrante superior esquerdo (11)
                mat[i][j] = mat11[i][j];
            }
            else if (i < size && j >= size)
            { //quadrante superior direita (12)
                mat[i][j] = mat12[i][j - size];
            }
            else if (i >= size && j < size)
            { //inferior esquerda (21)
                mat[i][j] = mat21[i - size][j];
            }
            else
            { //inferior direito (22)
                mat[i][j] = mat22[i - size][j - size];
            }
        }
    }
}

//corpo da função que desaloca a matriz
long int **DEALLOC_Matrix(long int n, long int **mat) //função que desaloca as matrizes
{

    long int i; //auxiliar

    for (i = 0; i < n; i++)
    {
        free(mat[i]);
    }

    free(mat);
    return (NULL);
}