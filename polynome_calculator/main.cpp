#include"Polinomio.h"
#include<iostream>
using namespace std;

//função que preenche vetor com números aleatórios
Polinomio vecfill(int n)
{
    int num = n + 1;
    double vetor[num];

    for (int r = 0; r < num; r++)
    {
        vetor[r] = rand() % 100;
    }
    Polinomio p(n, vetor);

    return p;
}
void test_construtores_destrutores()
{
    cout << " ## DEMONSTRAÇÃO DA INICIALIZAÇÃO DOS CONSTRUTORES ## ";

    cout << "\n-> Construtor vazio:" << endl;
    Polinomio p1;
    cout << p1;
    cout << endl;

    cout << "\n-> Construtor passando número:" << endl;
    Polinomio p2(10);
    cout << p2;
    cout << endl;

    cout << "\n-> Construtor passando número e vetor:" << endl;
    Polinomio p3 = vecfill(7);
    cout << p3;
    cout << endl;
}

void test_operacao_atribuicao()
{
}

void test_operacao_soma()
{
    cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;

    cout << "## SOMA DE POLINôMIOS ##" << endl;
    int randg = rand() % 4 + 3; //variável que gera grau aleatŕoio no range de 3-7
    Polinomio p1 = vecfill(randg + 2);
    Polinomio p2 = vecfill(randg);
    cout << "\nDois polinômios criados: " << endl;
    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    cout << "\n-> Resultado da soma de P1 e P2:" << endl;
    cout << p1 + p2;
    cout << endl
         << endl;

    cout << "\n>> SOMANDO POLINôMIOS OPOSTOS <<" << endl;
    randg = rand() % 4 + 3;
    Polinomio p3 = vecfill(randg);
    Polinomio p4 = p3 * -1;

    cout << "\nDois polinômios opostos criados: " << endl;
    cout << "P3: " << p3 << endl;
    cout << "P4: " << p4 << endl;

    cout << "\n-> Somando os opostos (P3 e P4): " << endl;
    cout << p3 << " + " << p4 << " = ";
    p3 += p4;
    cout << p3 << endl;
    cout << endl;

    cout << ">> SOMANDO DOUBLE ALEATÓRIO A POLINÔMIOS (ESQUERDA E DIREITA) <<";
    randg = rand() % 4 + 3;
    Polinomio p5 = vecfill(randg);
    cout << "\n\nPolinomio P5 criado para próximos testes: " << p5 << endl;
    double n5 = rand() % 1000;
    n5 = n5 / (rand() % 10);
    cout << "Double sorteado: " << n5 << endl;
    cout << "\n-> Somando a esquerda: " << endl;
    cout << n5 << " + " << p5 << " = " << n5 + p5 << endl;
    cout << endl;

    // Somando double a um Polinomio a direita
    cout << "-> Somando a direita" << endl;
    cout << p5 << " + " << n5 << " = " << p5 + n5;
    cout << endl;
}

void test_operacao_subtracao()
{
    cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;

    cout << "## SUBTRAÇÃO DE POLINÔMIOS ##" << endl;
    int randg = rand() % 4 + 3; //variável que gera grau aleatŕoio no range de 3-7
    Polinomio p1 = vecfill(randg + 2);
    Polinomio p2 = vecfill(randg);
    cout << "\nDois polinômios criados: " << endl;
    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    cout << "\n-> Resultado da subtração de P1 por P2:" << endl;
    cout << p1 - p2;
    cout << endl
         << endl;

    cout << "\n>> SUBTRAINDO POLINôMIOS IGUAIS <<" << endl;
    randg = rand() % 4 + 3;
    Polinomio p3 = vecfill(randg);
    Polinomio p4 = p3;

    cout << "\nDois polinômios iguais criados: " << endl;
    cout << "P3: " << p3 << endl;
    cout << "P4: " << p4 << endl;

    cout << "\n-> Subtração de P3 e P4: " << endl;
    cout << p3 << " - " << p4 << " = ";
    p4 -= p3;
    cout << p4 << endl;
    cout << endl;

    cout << ">> SUBTRAINDO DOUBLE ALEATÓRIO DE POLINÔMIOS (ESQUERDA E DIREITA) <<";
    randg = rand() % 4 + 3;
    Polinomio p5 = vecfill(randg);
    cout << "\n\nPolinomio P5 criado para próximos testes: " << p5 << endl;
    double n5 = (rand() % 1000) / (1+(rand() % 10));
    cout << "Double sorteado: " << n5 << endl;
    cout << "\n-> Subtraindo a esquerda: " << endl;
    cout << n5 << " - " << p5 << " = " << n5 - p5 << endl;
    cout << endl;

    // Somando double a um Polinomio a direita
    cout << "-> Subtraindo a direita" << endl;
    cout << p5 << " - " << n5 << " = " << p5 - n5;
    cout << endl;
}

void test_operacao_multiplicacao()
{
    cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## MULTIPLICAÇÃO DE POLINÔMIOS ##" << endl;

    Polinomio p1 = vecfill(4);
    Polinomio p2 = vecfill(4);
    

    cout << "\nPolinômio P1 selecionado: ";
    cout << p1 << endl;
    cout << "Polinômio P2 selecionado: ";
    cout << p2 << endl;
    cout << "\n-> Resultado da multiplicação de P1 e P2: ";
    cout << p1 * p2;

    double n5 = (rand() % 400)/(1+(rand()%10));
    cout << "\n\nDouble sorteado: " << n5 << endl;
    cout << "\nMultiplicando P1 por double a esquerda: " << endl;
    cout << n5 << "*(" << p1 << ")" << " = " << n5*p1 << endl;
    cout << "\nMultiplicando P1 por double a direita: " << endl;
    cout << "(" << p1 << ")*" << n5 << " = " << p1*n5 << endl;
}

void test_operacao_divisao()
{
        cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## DIVISÃO DE POLINÔMIOS ##" << endl;
    double v2[] = {1, 4};
    Polinomio p1 = vecfill(4);
    Polinomio p2(1, v2);
    int randint = (rand()%100)+1;

    cout << "\nPolinômios que serão usados para divisão: " << endl;
    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;
    cout << "Resultado da divisão de P1 por P2: " << p1/p2 << endl; //usando apenas o operator /
    //o operator /= para polinômios também funciona, apenas não colocamos no teste para evitar redundância
    cout << "\nDividindo os polinômios por um número aleatório: " << endl;
    cout << "Número aleatório escolhido: " << randint << endl;
    cout << "\nDivisão de P1 pelo número aleatório: " << p1/randint << endl;
    p2/=randint; //usando o operator /=
    cout << "Divisão de P2 pelo número aleatório: " << p2 << endl;

    cout<<"\nUsando como denominador polinômio de forma diferente de (x-a)"<<endl;
    Polinomio p3 = vecfill(3);
    Polinomio p4 = vecfill(3);
    cout << "P3: " << p3 << endl;
    cout << "P4: " << p4 << endl;
    try{
        cout<<(p3/p4)<<endl;
    }catch(ArgumentoInvalidoExcept e){
        cout << e.what();
    }
    
    
}

void test_operacao_resto_divisao(){
        cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## CALCULA RESTO DA DIVISÃO DE POLINÔMIOS (OPERATOR %) ##" << endl;
    double t1[] = {1,3,1,1};
    double t2[] = {1,1};
    Polinomio p1(3,t1);
    Polinomio p2(1,t2);

    cout << "\nP1: " << p1 << endl;
    cout << "P2: " << p2 << endl;
    cout << "Resto da divisão: " << (p1%p2);

    cout << "\n\nAgora com operador %= : " << endl;

    cout << "Resto da divisão: ";
    p1%=p2;
    cout << p1 << endl;
}

void test_operacao_return_coeficiente(){
        cout << endl
         << "----------------------------------------------------------------------------------------------------------" << endl;

    cout << "## TESTANDO COEFICIENTES (operador []) ##" << endl;
    double t1[] = {6, 4, 1};
    Polinomio p1(2, t1);
    cout<< p1 << endl;
    try
    {
        cout << "Coeficiente de grau zero: " << p1[0] << endl;
        cout << "Coeficiente de grau um: " << p1[1] << endl;
        cout << "Coeficiente de grau dois: " << p1[2] << endl;
    }
    catch (PosicaoInvalidaExcept e)
    {
        cout << e.what();
    }
}

void test_operacao_increment()
{
    cout << endl
         << "\n----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## INCREMENTO E DECREMENTO DE POLINÔMIOS (operador ++ pós e pré fixado) ##" << endl;
    Polinomio p1 = vecfill(4);
    cout << "\nPolinômio selecionado: " << p1 << endl;
    //operador pós fixado
    cout << "Incremento com operador pós fixado: " << p1++ << endl;
    ++p1;
    cout << "Incremento com operador pré fixado: " << ++p1 << endl;
    cout << "Decremento com operador pós fixado: " << p1-- << endl;
    --p1;
    cout << "Decremento com operador pré fixado: " << --p1 << endl;
}

void test_comparacao_igualdade()
{
        cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## CHECANDO IGUALDADES ##" << endl;
    Polinomio p1 = vecfill(5);
    Polinomio p2 = vecfill(5);
    Polinomio p3 = p2; 

    cout << "Serão comparados três polinômios: " << endl;
    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;
    cout << "P3: " << p3 << endl;
    cout << "\nSerá impresso SIM para polinômios iguais e NÃO para polinômios diferentes" << endl;

    cout << "P1 e P2: ";
    if(p1 == p2) cout << "SIM" << endl;
    else cout << "NÃO" << endl;
    
    cout << "P1 e P3: ";
    if(p1 == p3) cout << "SIM" << endl;
    else cout << "NÃO" << endl;
    
    cout << "P2 e P3: ";
    if(p2 == p3) cout << "SIM" << endl;
    else cout << "NÃO" << endl;
}

void test_entrada_saida(){
            cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## TESTANDO OPERADORES DE ENTRADA E SAÍDA ##" << endl;
    cout << "Para testar a entrada e saída, digite o grau seguido das constantes do polinômio (de menor para maior grau): " << endl;
    Polinomio p;
    cin >> p;
    cout << "Seu polinômio: " << p << endl;
}


void test_operacao_derivada()
{
        cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## CÁLCULO DE DERIVADA ##" << endl;
    Polinomio p1 = vecfill(5);
    cout << "Vetor cuja derivada será calculada: " << p1 << endl;
    cout << "Resultado da derivada: " << p1.derivada() << endl;
}

void test_operacao_integral(){
    cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## CÁLCULO DE INTEGRAL INDEFINIDA, SENDO C = 0 ##" << endl;
    Polinomio p1 = vecfill(3);
    cout << "P1: " << p1 << endl;
    cout << "Integral(P1): " << p1.integral() << endl;

}
void test_operacao_integral_definida(){
    cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## CÁLCULO DE INTEGRAL DEFINIDA ##" << endl;
    
    Polinomio p1 = vecfill(3);
    double li = (rand() % 1000)/(1+(rand() % 10));
    double ls = (rand() % 1000)/(1+(rand() % 10));
    cout << "P1: " << p1 << endl;
    cout << "Limite inferior: "<<li<<endl;
    cout << "Limite superior: "<<ls<<endl;
    cout << "Integral indefinida(FX): "<< p1.integral()<<endl;
    cout << "Integral F("<<li<<"): "<<p1.integral().avalia(li)<<endl;
    cout << "Integral F("<<ls<<"): "<<p1.integral().avalia(ls)<<endl;
    cout << "Integral definida: " << p1.integral_definida(ls,li) << endl;
}
void test_operacao_avalia()
{
        cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## AVALIANDO POLINÔMIO PARA UM VALOR ALEATÓRIO DE X ##" << endl;
    Polinomio p1 = vecfill(5);
    int valorx = (rand()%100)+1;

    cout << "Polinômio que será avaliado: " << p1 << endl;
    cout << "Valor de X selecionado: " << valorx << endl;
    cout << "Resultado: " << p1.avalia(valorx) << endl;
}

void test_operacao_resolve()
{
        cout << endl
        << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "## RESOLVENDO POLINÔMIO (CALCULANDO RAIZES - Método de Newton) ##" << endl;
    
    Polinomio p1 = vecfill(2);
    double vetor[] = {-6, -1, 1};
    Polinomio p2(2, vetor);
    int tentativas = 1000000;
    cout << "Polinômios cujas raizes serão calculadas:" << endl;
    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    cout << "\nVamos supor 1 milhão de tentativas para o método.\n" << endl;
    double *rootvector;
    try{
        rootvector = p1.resolve(tentativas);
        int rootcount = sizeof(rootvector)/sizeof(rootvector[0])+1;
        cout << "Raízes de P1: ";
        for(int i = 0; i < rootcount; i++){
            cout << rootvector[i] << " ";
        }
        delete []rootvector;
    }
    catch(RaizesNaoEncontradasExcept e){
        cerr << e.what() << "para P1 :( " << endl;;
    }
    cout << endl;

    
    try{
        rootvector = p2.resolve(tentativas);
        int rootcount = sizeof(rootvector)/sizeof(rootvector[0])+1;
        cout << "Raízes de P2: ";
        for(int i = 0; i < rootcount; i++){
            cout << rootvector[i] << " ";
        }
        delete []rootvector;
    }
    catch(RaizesNaoEncontradasExcept e){
        cerr << e.what() << "para P2 :( " << endl;
    }
    cout << endl;
}

int main()
{
    test_construtores_destrutores();
    test_operacao_soma();
    test_operacao_subtracao();
    test_operacao_multiplicacao();
    test_operacao_divisao();
    test_operacao_resto_divisao();
    test_operacao_increment();
    test_operacao_return_coeficiente();
    test_comparacao_igualdade();
    test_operacao_derivada();
    test_operacao_avalia();
    test_operacao_resolve();
    test_operacao_integral();
    test_operacao_integral_definida();
    test_entrada_saida();

    
}
