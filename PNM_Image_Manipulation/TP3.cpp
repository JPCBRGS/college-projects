#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>

#define MAXALTURA 500
#define MAXLARGURA 500

using namespace std;

int main(){
    unsigned char imagem[MAXALTURA][MAXLARGURA];    //a imagem propriamente dita
    unsigned char colorida [MAXALTURA][MAXLARGURA][3];
    unsigned char aux [MAXALTURA][MAXLARGURA];
    unsigned char auxc [MAXALTURA][MAXALTURA][3];
    int largura, altura;                            //dimensoes da imagem
    char tipo[4];                                   //tipo da imagem
    ifstream arqentrada;                            //arquivo que contem a imagem original
    ofstream arqsaida;                              //arquivo que contera a imagem gerada
    char comentario[200], c;                        //auxiliares
    int i, j, z, v,n, gy, gx, f, valor;                                //auxiliares

    char entrada [500], saida [500];
//*** LEITURA DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte

    //*** Abertura do arquivo ***//
    cout <<"Digite o nome da imagem com a extencao: ";
    cin.getline(entrada, 500);
    cout <<"Digite o nome do novo arquivo: ";
    cin.getline(saida, 500);

    arqentrada.open(entrada,ios::in); //Abre arquivo para leitura
    //***************************//

    //*** Leitura do cabecalho ***//
    arqentrada >> tipo;  //Le o tipo de arquivo
    arqentrada.get();    //Le e descarta o \n do final da 1a. linha

    if (strcmp(tipo,"P3")==0) {
      cout << "Imagem colorida\n";
    }
    else if (strcmp(tipo,"P2")==0) {
      cout << "Imagem em tons de cinza\n";
    }
    else if (strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
      cout << "Imagem no formato RAW\n";
      cout << "Desculpe, mas nao trabalho com esse tipo de imagem.\n";
      arqentrada.close();
      return 0;
    }


    while((c = arqentrada.get()) == '#')   //Enquanto for comentario
       arqentrada.getline(comentario,200); //Le e descarta a linha "inteira"

    arqentrada.putback(c);  /* Devolve o caractere lido para a entrada, pois como
                            nao era comentario, era o primeiro digito da largura*/

    arqentrada >> largura >> altura;  //Le o numero de pixels da horizontal e vertical
    cout << "Tamanho: " << largura << " x " << altura << endl;

    arqentrada >> valor;    //Valor maximo do pixel (temos que ler, mas nao sera usado)
    


    //*** Leitura dos pixels da imagem ***//
   if (strcmp(tipo, "P2") == 0){
    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++) {
        arqentrada >> valor;
        imagem[i][j] = (unsigned char)valor;
      }
   }
   else if (strcmp(tipo, "P3") == 0){
    for (i=0; i<altura; i++)
        for (j=0; j<largura; j++)
            for (f=0; f<3; f++){
            arqentrada >>valor;
            colorida [i][j][f] = (unsigned char)valor;
    }
   }
    //************************************//

    arqentrada.close();

//*** FIM DA LEITURA DA IMAGEM ***//




//*** TRATAMENTO DA IMAGEM ***//
//MENU INICIAL
    if (strcmp(tipo, "P2") == 0){

    cout << endl << "O que deve ser realizado? " << endl;
    cout << endl;
    cout << "1- Escurecer a imagem " << endl;
    cout << "2- Clarear a imagem " << endl;
    cout << "3- Espelhar a imagem "  << endl;
    cout << "4- Efetuar o negativo da imagem " << endl;
    cout << "5- Filtro de Sobel " << endl;
    cout << "6- Acrescentar brilho a imagem" << endl;

    cout << endl;
    cout << "Selecao: ";
    cin >> v;

    int fator;
    //Caso Digite um modo inválido.
    if (v<1 || v>6){
        cout << "Invalido" << endl;
        return 0;
    }
        //*** Escurece a imagem ***//
    if (v == 1){
    cout << "Qual o fator de escurecimento (1-100) ? ";
    cin >> fator;
    //*** Escurece a imagem ***//
    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++) {
        valor = (int)imagem[i][j];   
        valor -= fator;              
        if (valor<0)
          valor = 0;
        imagem[i][j] = (unsigned char)valor;   //modifica o pixel
      }
    }
     if (v == 2){
    //*** Clareia a imagem ***//
    cout << "Qual o fator de clareamento (1-100) ? ";
    cin >> fator;

    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++) {
        valor = (int)imagem[i][j];   
        valor += fator;            
        if (valor>255)               
          valor = 255;
        imagem[i][j] = (unsigned char)valor;   
      }
    }
    else if (v == 3){
    //*** Espelha a imagem ***//
        for (i=0; i<altura; i++)
            for (j=0, z=largura-1; j<largura; j++, z--)
               aux [i][z] = imagem[i][j];

        for(i=0;i<altura;i++)
            for(j=0;j<largura;j++)
               imagem [i][j] = aux[i][j];

    }
    else if (v == 4){
    //*** Negativo da imagem ***//
        for(int i=0;i<altura;i++)
            for(int j=0;j<largura;j++){
                valor = (int)imagem[i][j];
                valor = 255 - imagem[i][j];
                if (valor<0)
                valor = 0;
                imagem[i][j] = (unsigned char)valor;
    }
    }
    else if (v == 5){
        //*** Filtro sobel ***//
            gy = 0;
            gx = 0;
        for (i = 0; i<altura; i++){
            for (j =0; j<largura; j++){
                if (i-1 >= 0 && j-1 >= 0){
                    gy += (int) imagem[i-1][j-1]*(1);
                    gx += (int) imagem[i-1][j-1]*(1);
                }
                if (i-1 >=0 && j+1 <largura){
                    gy += (int) imagem [i-1][j+1]*(1);
                    gx += (int) imagem [i-1][j+1]*(-1);
                }
                if (i-1 >=0 && j<largura){
                    gy += (int) imagem [i-1][j]*(2);
                }
                if (i<altura && j-1>=0){
                    gx += (int) imagem [i][j-1]*(2);
                }
                if (i<altura && j+1<largura){
                    gx += (int) imagem [i][j+1]*(-2);
                }
                if (i+1<altura && j-1 >=0 ){
                    gy += (int) imagem [i+1][j-1]*(-1);
                    gx += (int) imagem [i+1][j-1]*(1);
                }
                if (i+1 <altura && j<largura){
                    gy += (int) imagem [i+1][j]*(-2);
                }
                if (i+1 <altura && j+1<largura){
                    gy += (int) imagem [i+1][j+1]*(-1);
                    gx += (int) imagem [i+1][j+1]*(-1);
                }
            if (gy < 0)
                gy = 0;
            if (gy > 255)
                gy = 255;
            if (gx < 0)
                gx = 0;
            if (gx > 255)
                gx = 255;
            valor = (gy+gx)/2;
            if (valor<0)
                valor = 0;
            if (valor>255)
                valor = 255;

            aux [i][j] = (unsigned char) valor;

            gy = 0;
            gx = 0;
            }
    }
    for (i=0; i<altura; i++)
        for (j=0; j<largura; j++)
            imagem [i][j] = aux [i][j];
    }
    else if (v == 6){
            //*** Brilho ***//
        n=0;
            while(n<1 || n>255){
        cout<<"Qual a intensidade do brilho? (1(maior) - 255(menor))"; cin >> n;
            }
    for(i=0; i<altura; i++){
        for(j=0; j<largura; j++){
            valor = ((int)imagem[i][j]*(int)imagem[i][j])/n;
            if (valor > 255)
                valor = 255;
            if (valor < 0)
                valor = 0;
            aux[i][j] = (unsigned char)valor;
            }

        } for(i=0;i<altura;i++)
            for(j=0;j<largura;j++)
               imagem [i][j] = aux[i][j];
    }
    //*************************//

//*** FIM DO TRATAMENTO DA IMAGEM ***//



//*** GRAVACAO DA IMAGEM ***//
//inicialmente nao sera necessario entender nem mudar nada nesta parte


    //*** Grava a nova imagem ***//
    arqsaida.open(saida, ios::out); 

    arqsaida << tipo << endl;                           
    arqsaida << "# TP3 - INF110 <> Joao Pedro Clemente - 95654 <> Vitor Camargo - 95691\n"; 
    arqsaida << largura << " " << altura << endl;        
    arqsaida << 255 << endl;                             
    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++)
        arqsaida << (int)imagem[i][j] << endl;          

    arqsaida.close();  //fecha o arquivo
    }
    else if (strcmp(tipo, "P3") == 0){

    cout << endl << "O deve ser realizado? " <<endl;
    cout << endl;
    cout << "1- Escurecer a imagem " << endl;
    cout << "2- Clarear a imagem " << endl;
    cout << "3- Espelhar a imagem " << endl;
    cout << "4- Efetuar o negativo da imagem " << endl;
    cout << "5- Filtro de Sobel " << endl;
    cout << "6- Transformar a Imagem Colorida em Tons de Cinza " << endl;
    cout << "7- Aumentar o brilho da imagem " << endl;

    cout << endl;
    cout << "Selecao: ";
    cin >> v;

    int fator;
    if (v == 1){
    //*** Escurece a imagem ***//
    cout << "Qual o fator de escurecimento (1-100) ? ";
    cin >> fator;

    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++)
        for (f=0; f<3; f++){
        valor = (int)colorida[i][j][f];   //pega o valor do pixel
        valor -= fator;              //escurece o pixel
        if (valor<0)                 //se der negativo, deixa preto
            valor = 0;
            colorida[i][j][f] = (unsigned char)valor;   //modifica o pixel
      }
    }
      else  if (v == 2){
   //*** Clareia a imagem ***//
   cout << "Qual o fator de clareamento (1-100) ? ";
    cin >> fator;

    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++)
        for (f=0; f<3; f++){
        valor = (int)colorida[i][j][f];   //pega o valor do pixel
        valor += fator;              //escurece o pixel
        if (valor>255)                 //se der negativo, deixa preto
            valor = 255;
            colorida[i][j][f] = (unsigned char)valor;   //modifica o pixel
      }
    }
    else if (v == 3){
    //*** Espelha a imagem ***//
        for (i=0; i<altura; i++)
            for (j=0, z=largura-1; j<largura; j++, z--)
                for (f=0; f<3; f++)
                auxc [i][z][f] = colorida[i][j][f];

        for(i=0;i<altura;i++)
            for(j=0;j<largura;j++)
                for (f=0; f<3; f++)
                colorida [i][j][f] = auxc [i][j][f];

    }
    else if (v == 4){
            //*** Negativo da imagem ***//
            valor = 0;
        for(int i=0;i<altura;i++)
            for(int j=0;j<largura;j++)
                for (f=0; f<3; f++){
                    valor = 255 - (int)colorida[i][j][f];
                        if (valor<0)
                        valor = 0;
                        colorida[i][j][f] = (unsigned char)valor;
    }
    }

     else if (v == 5){
            //*** Filtro Sobel ***//
            gy = 0;
            gx = 0;
        for (i = 0; i<altura; i++){
            for (j =0; j<largura; j++)
                for (f=0; f<3; f++){
                if (i-1 >= 0 && j-1 >= 0){
                    gy += (int) colorida[i-1][j-1][f]*(1);
                    gx += (int) colorida[i-1][j-1][f]*(1);
                }
                if (i-1 >=0 && j+1 <largura){
                    gy += (int) colorida [i-1][j+1][f]*(1);
                    gx += (int) colorida [i-1][j+1][f]*(-1);
                }
                if (i-1 >=0 && j<largura){
                    gy += (int) colorida [i-1][j][f]*(2);
                }
                if (i<altura && j-1>=0){
                    gx += (int) colorida [i][j-1][f]*(2);
                }
                if (i<altura && j+1<largura){
                    gx += (int) colorida [i][j+1][f]*(-2);
                }
                if (i+1<altura && j-1 >=0 ){
                    gy += (int) colorida [i+1][j-1][f]*(-1);
                    gx += (int) colorida [i+1][j-1][f]*(1);
                }
                if (i+1 <altura && j<largura){
                    gy += (int) colorida [i+1][j][f]*(-2);
                }
                if (i+1 <altura && j+1<largura){
                    gy += (int) colorida [i+1][j+1][f]*(-1);
                    gx += (int) colorida [i+1][j+1][f]*(-1);
                }

            if (gy < 0)
                gy = 0;
            if (gy > 255)
                gy = 255;
            if (gx < 0)
                gx = 0;
            if (gx > 255)
                gx = 255;
            valor = (gy+gx)/2;
            if (valor<0)
                valor = 0;
            if (valor>255)
                valor = 255;

            auxc [i][j][f] = (unsigned char) valor;

            gy = 0;
            gx = 0;
            }
    }
    for(int i=0;i<altura;i++)
            for(int j=0;j<largura;j++)
                for (f=0; f<3; f++)
                    colorida[i][j][f] = auxc [i][j][f];
     }
     else if (v == 6){
            //*** Transforma a imagem colorida em tons de cinza ***//
            valor = 0;
        for (i = 0; i<altura; i++)
            for (j=0; j<largura; j++){
                for(f=0; f<3; f++){
                    valor += (int)colorida [i][j][f];
                }
                valor /= 3;
                aux [i][j] = (unsigned char)valor;
                valor = 0;
        }
    }
    else if (v == 7){
            //*** Brilho ***//
            n=0;
            while(n<1 || n>255){
        cout<<"Qual a intensidade do brilho de 1 a 255? (1(maior) - 255(menor))"; cin >> n;
            }
        for(i=0; i<altura; i++){
            for(j=0; j<largura; j++){
                    for(f=0; f<3; f++){
                valor = ((int)colorida [i][j][f]*(int)colorida [i][j][f])/n;
                if (valor > 255)
                    valor = 255;
                if (valor < 0)
                    valor = 0;
                auxc [i][j][f] = (unsigned char)valor;
            }
        }
        } for(i=0;i<altura;i++)
            for(j=0;j<largura;j++)
                for(f=0;f<3;f++)
               colorida [i][j][f] = auxc [i][j][f];
    }

    if (v == 6){
            

    arqsaida.open(saida, ios::out);  //Abre arquivo para escrita
    strcpy(tipo, "P2");
    arqsaida << tipo << endl;                           
    arqsaida << "# TP3 - INF110 <> Joao Pedro Clemente - 95654 <> Vitor Camargo - 95691\n";  
    arqsaida << largura << " " << altura << endl;        
    arqsaida << 255 << endl;                             
    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++)
        arqsaida << (int)aux[i][j] << endl;        

    arqsaida.close();

    }
    if (v != 6){
    arqsaida.open(saida, ios::out); 

    arqsaida << tipo << endl;                           
    arqsaida << "# TP3 - INF110 <> Joao Pedro Clemente - 95654 <> Vitor Camargo - 95691\n";  
    arqsaida << largura << " " << altura <<endl;        
    arqsaida << 255 << endl;                             
    for(i=0;i<altura;i++)
      for(j=0;j<largura;j++)
        for (f=0; f<3; f++)
        arqsaida << (int)colorida[i][j][f] << endl;           

    arqsaida.close();  

    }
    }



    return 0;
}
