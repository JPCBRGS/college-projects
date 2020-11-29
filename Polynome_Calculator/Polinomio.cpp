#include <iostream>
#include <cmath>
#include <cstring>
#include "Polinomio.h"

using namespace std;

// métodos a serem implementados

/* construtores e destrutores */

// construtor padrão. Deve representar o número 0
Polinomio::Polinomio()
{
    v = new double[1];
    v[0] = 0;
    g = 0;
}

// Cria um Polinomio a partir de um número inteiro (positivo ou negativo)
Polinomio::Polinomio(const int num)
{
    v = new double[1];
    v[0] = num;
    g = 0;
}

// Cria um Polinomio a partir de um vetor de coeficientes. Os coeficientes
		// deverão ser os coeficientes do polinômio (Posição 0 será a_0, posição 1 será a_1, ...). 
		// O primeiro parâmetro representa o grau do polinômio.
Polinomio::Polinomio(unsigned int n, double *a)
{
    v = new double[n+1];
    g = n;
    for (int i = 0; i < n+1; i++)
        this->v[i] = a[i];
    
}

// Construtor de cópia
Polinomio::Polinomio(const Polinomio &obj)
{
    v = new double[obj.g+1];
    g = obj.g;
    for (int i = 0; i < g+1; i++)
        this->v[i] = obj.v[i];
}

// destrutor
Polinomio::~Polinomio()
{
    delete[] v;
}

/* Operadores */

// atribuição
Polinomio &Polinomio::operator=(const Polinomio &obj)
{
    if (this == &obj)
        return *this;
    delete[] this->v;
    v = new double[obj.g+1];
    g = obj.g;
    for (int i = 0; i < obj.g+1; i++)
        v[i] = obj.v[i];

    return *this;
}

// soma
Polinomio Polinomio::operator+(const Polinomio &obj) const
{
    // Acha o maior e menor polinômio
    const Polinomio &maiorP = (g >= obj.g ? *this : obj);
    const Polinomio &menorP = (g < obj.g ? *this : obj);

    // Cria polinômio que será retornado
    Polinomio p = maiorP;
    // Soma os atributos do menor ao menor
    for (int i = 0; i < menorP.g+1; i++)
        p.v[i] = menorP.v[i] + p.v[i];
    //p.removerZeros();
    return p;
}
Polinomio Polinomio::operator+(const double &num) const
{
    Polinomio p = *this;
    p.v[0] = p.v[0] + num;
    p.removerZeros();
    return p;
}

Polinomio operator+(double val, Polinomio &obj){
    return obj+val;
}

Polinomio &Polinomio::operator+=(const Polinomio &obj)
{
    // Acha o polinômio de menor tamanho
    int maiorTam = (g > obj.g ? g : obj.g);

    // Caso o elemento da esquerda seja menor
    // Cria um vetor auxiliar de tamanhho do elemento da direita
    // Copia o vetor this->v para esse auxiliar
    if (g < maiorTam)
    {
        double *t = new double[maiorTam+1];
        for (int i = 0; i < g+1; i++)
            t[i] = v[i];

        for (int i = g; i < maiorTam+1; i++)
            t[i] = 0;

        delete[] v;
        v = t;
        g = maiorTam;
    }

    // Soma os elementos de
    for (int i = 0; i < maiorTam+1; i++)
        this->v[i] += obj.v[i];
    
    this->removerZeros();
    return *this;
}
Polinomio &Polinomio::operator+=(const double &num)
{
    v[0] += num;
    this->removerZeros();
    return *this;
}

// subtração (segue o mesmo padrão da adição)
Polinomio Polinomio::operator-(const Polinomio &obj) const
{
    // Acha o maior e menor polinômio
    const Polinomio &maiorP = (g >= obj.g ? *this : obj);
    const Polinomio &menorP = (g < obj.g ? *this : obj);

    // Cria polinômio que será retornado
    Polinomio p = maiorP;
    // Soma os atributos do menor ao menor
    for (int i = 0; i < menorP.g+1; i++)
        p.v[i] = menorP.v[i] - p.v[i];
    //p.removerZeros();
    return p;

}
Polinomio Polinomio::operator-(const double &num) const
{
    Polinomio p = *this;
    p.v[0] = p.v[0] - num;
    p.removerZeros();
    return p;
    
}

Polinomio operator-(double num, Polinomio &obj)
{
    return (obj*-1)+num;
}

Polinomio &Polinomio::operator-=(const Polinomio &obj)
{
        // Acha o polinômio de menor tamanho
    int maiorTam = (g > obj.g ? g : obj.g);

    // Caso o elemento da esquerda seja menor
    // Cria um vetor auxiliar de tamanhho do elemento da direita
    // Copia o vetor this->v para esse auxiliar
    if (g < maiorTam)
    {
        double *t = new double[maiorTam+1];
        for (int i = 0; i < g+1; i++)
            t[i] = v[i];

        for (int i = g; i < maiorTam+1; i++)
            t[i] = 0;

        delete[] v;
        v = t;
        g = maiorTam;
    }

    // Soma os elementos de
    for (int i = 0; i < maiorTam+1; i++)
        this->v[i] -= obj.v[i];
    
    this->removerZeros();
    return *this;
}
Polinomio &Polinomio::operator-=(const double &num)
{
    v[0] -= num;
    return *this;
}

// multiplicação
// TODO: você também deve implementar a multiplicação por um número à esquerda
Polinomio Polinomio::operator*(const Polinomio &obj)const
{
   double vaux[(obj.g +1)*(g +1)-(obj.g*g)] = {0};
	Polinomio p((obj.g +1)*(g +1)-(obj.g*g)-1, vaux);
	
	for(int i=0; i<g + 1; i++){
		for(int k=0; k< obj.g + 1; k++)
			p.v[i+k] += v[i] * obj.v[k];
	}
	return p;
}
Polinomio Polinomio::operator*(const double &num)const
{
   Polinomio p = *this;
    for(int i=0; i<g+1; i++)
		{
		p.v[i] *= num;	
		}
    return p;
}

Polinomio operator *(double num, Polinomio &obj){
    return obj*num;
}

Polinomio &Polinomio::operator*=(const Polinomio &obj)
{
    double vaux[(obj.g +1)*(g +1)-(obj.g*g)] = {0};
	
	for(int i=0; i< g + 1; i++){
		for(int k=0; k< obj.g + 1; k++)
			vaux[i+k] += v[i] * obj.v[k];
	}
	
	g= (obj.g +1)*(g +1)-(obj.g*g)-1;
	
	this -> v = (double *) realloc(v, sizeof(double)*((obj.g +1)*(g +1)-(obj.g*g)));
	for(int i=0; i<(obj.g +1)*(g +1)-(obj.g*g); i++)
	{
		this -> v[i]=vaux[i];
	}
	
	return *this;

}
Polinomio &Polinomio::operator*=(const double &num)
{
    for(int i=0; i<g+1; i++)
		{
		this -> v[i] *= num;	
		}
	return *this;

}

// divisão por um polinômio de grau 1 da forma (x - a)
// deve lançar 'ArgumentoInvalidoExcept' se o denominador não for da forma especificada acima
// Sugestão: https://pt.wikipedia.org/wiki/Algoritmo_de_Briot-Ruffini
// TODO Lancaçar exceção divisão por 0
Polinomio Polinomio::operator/(const Polinomio &obj) const
{
    // verifica se ele tem grau 1
    if(obj.g!=1){
        // TODO Throw Exception
        ArgumentoInvalidoExcept e("O polinômio não está na forma (x-a)");
        throw e;
    }
    double *t = new double[g];
    double a = obj.v[0]*-1; // Termo independente
    // transforma na forma (x-a)
    double aux = v[g]*a;
    t[g-1]=v[g];
    
    for(int i=g-1;i>0;i--){
        t[i-1] = v[i]+aux;
        aux = (v[i]+aux)*a;
    }
    Polinomio p(g-1,t);
    delete[]t;
    return p;
}
Polinomio &Polinomio::operator/=(const Polinomio &obj)
{
    // verifica se ele tem grau 1
    if(obj.g!=1){
        ArgumentoInvalidoExcept e("Error");
        throw e;
    }

    // transforma na forma (x-a)
    double a = obj.v[0]*-1; // Termo independente
    double *t = new double[g];
    double aux = v[g]*a;
    t[g-1]=v[g];
    for(int i=g-1;i>0;i--){
        t[i-1] = v[i]+aux;
        aux = (v[i]+aux)*a;
    }
    delete[]v;
    this->v = t;
    g-=1;
    return *this;
}

// divide os coeficiente por um número
Polinomio Polinomio::operator/(const int &num) const
{
    Polinomio p = *this;
    for(int i = 0; i<=g; i++){
        p.v[i] = p.v[i]/num;
    }
    return p;
}
Polinomio &Polinomio::operator/=(const int &num)
{
    for(int i = 0; i<=g; i++){
        v[i] = v[i]/num;
    }
    return *this;
}

// resto da divisão por um polinômio de grau 1 da forma (x - 1)
// deve lançar 'ArgumentoInvalidoExcept' se o denominador não for da forma especificada acima
// Sugestão: https://pt.wikipedia.org/wiki/Algoritmo_de_Briot-Ruffini
Polinomio Polinomio::operator%(const Polinomio &obj) const
{
    // verifica se ele tem grau 1
    if(obj.g!=1){
        // TODO Throw Exception
        ArgumentoInvalidoExcept e("O polinômio não está na forma (x-a)");
        throw e;
    }
    double *t = new double[g+1];
    for(int r=0; r<g+1; r++){
        t[r] = 0;
    }
    double a = obj.v[0]*-1; // Termo independente
    // transforma na forma (x-a)
    double aux = v[g]*a;
    t[g-1]=v[g];
    
    for(int i=g;i>0;i--){
        t[i-1] = v[i]+aux;
        aux = (v[i]+aux)*a;
    }
    Polinomio p(g,t);
    p.removerZeros();
    delete[]t;
    return p;
}
Polinomio &Polinomio::operator%=(const Polinomio &obj)
{
    // verifica se ele tem grau 1
    if(obj.g!=1){
        // TODO Throw Exception
        ArgumentoInvalidoExcept e("O polinômio não está na forma (x-a)");
        throw e;
    }
    double *t = new double[g+1];
    for(int r=0; r<g+1; r++){
        t[r] = 0;
    }
    double a = obj.v[0]*-1; // Termo independente
    // transforma na forma (x-a)
    double aux = v[g]*a;
    t[g-1]=v[g];
    
    for(int i=g;i>0;i--){
        t[i-1] = v[i]+aux;
        aux = (v[i]+aux)*a;
    }
    delete[]this->v;
    this->v = t;
    this->g = g;
    this->removerZeros();
    return *this;
}

// Retorna i-ésimo coeficiente
// Deve lançar 'PosicaoInvalidaExcept' se houver tentativa de acessar um bit não existente
// Posição 0 indica o coeficiente do termo constante
double Polinomio::operator[](int i) const
{
    //Verifica se é valido
    if (i > g || i < 0)
    {
        PosicaoInvalidaExcept e("Bit nao existente\n");
        throw e;
    }
    return v[i];
}

// incrementos (adicionar 1 ou subtrair 1) ao termo constante
Polinomio &Polinomio::operator++()
{
    ++v[0];
    return *this;
}    
Polinomio Polinomio::operator++(int)
{
   Polinomio temp = *this;  
    ++*this;  
    return temp; 
}

Polinomio Polinomio::operator--()
{
    v[0]--;
    return *this;
}    
Polinomio Polinomio::operator--(int)
{
    Polinomio p(*this);
    p.v[0]-=1;
    return p;
}

/* Comparação */

// igualdade
// Verificar se dois polinômios tem o mesmo grau e mesmos coeficientes
bool Polinomio::operator==(const Polinomio &obj) const
{
    Polinomio p = *this;
	
	if(g!=obj.g) return false;
	for(int i=0; i<g+1; i++)
	{
		if(v[i]!=obj.v[i]) return false;
	}
	return true;
}


/* Entrada Saída */
		
// lê/imprime de streams de entrada e saída

istream& operator>>(istream &, Polinomio &obj){
    int n;
    cin>>n;
    double *t = new double[n+1];
    for(int i=0;i<n+1;i++){
        cin>>t[i];
    }
    obj.g = n;
    delete[]obj.v;
    obj.v = t;
}
ostream& operator<<(ostream &, const Polinomio &p){
    for (int i = p.g; i >0 ; i--){
        cout<<p.v[i]<<"x";
        p.imprimeNumeroSuperEscrito(i);
        cout<<" + ";
    }
    cout<<p.v[0];
}


/* Operações (sem operadores) */

// retorna a derivada do polinômio
Polinomio Polinomio::derivada() const{
    double *t = new double[g];

    for(int i=1;i<this->g+1;i++){
        t[i-1] = this->v[i]*i;
    }
    Polinomio p(g-1,t);
    delete[]t;
    return p;
}
// retorna a integral do polinomio
Polinomio Polinomio::integral() const{
    double *t = new double[g+2];

    for(int i=1;i<this->g+2;i++)
        t[i] = this->v[i-1]/(i);

    t[0] = 0;

    Polinomio p(g+1,t);
    delete[] t;
    return p;
}
// retorna a integral definida de a ate b
double Polinomio::integral_definida(double a, double b) const{
    Polinomio p = this->integral();
    double v = p.avalia(a) - p.avalia(b);
    return v;
}
// avalia.
// Dado um número 'a', calcula P(a)
// sugestão https://en.wikipedia.org/wiki/Horner%27s_method
double Polinomio::avalia(double val) const{
    
    double soma = 0;
    for(int i=0;i<g+1;i++){
        soma+=v[i]*pow(val,i);
    }
    return soma;
}

// resolve P(x) = 0. Encontra as raízes reais do polinômio
// o parâmetro inteiro é o número de raízes encontradas
// Se não encontrar raízes, deve lançar uma exceção
// sugestão: use o método de Newton para encontrar uma raiz, 
// use o algoritmo de divisão para simplificar o polinômio...
double * Polinomio::resolve(int &val) const{
    // Suponhe algum valor
    double xn = 100;

    // Obtém Polinomio e sua derivada
    Polinomio poli = *this;
    Polinomio derpoli = poli.derivada();
    double fxn, fxnl;
    // TODO REVISAR g-1
    double auxRaizes[g-1];
    int nRaizes = 0;
    
    // Criando polinômio inicial
    double t[] = {0,1};
    Polinomio paux(1,t);
    
    // Fazendo método de Newton val vezes
    for(int i=0;i<val ;i++){
        fxn = poli.avalia(xn);
        fxnl = derpoli.avalia(xn);
        
        xn = (xn - (fxn/fxnl));
        
        double avaliado = poli.avalia(xn);
        double epsylom = 0.0000000000002;
        if(avaliado<epsylom && avaliado>=0){
            paux.v[0]=xn*-1;
            poli=poli/paux;
            derpoli = poli.derivada();
            auxRaizes[nRaizes] = xn;
            nRaizes++;
            xn = 3;
        }
    }
    
    // Lança exceção se não encotra nenhuma raiz
    if(nRaizes == 0){
        RaizesNaoEncontradasExcept e("Nenhuma raiz real foi encontrada ");
        throw e;
    }

    // Retorna raizes encontradas
    double *raizes = new double[nRaizes];
    for(int i=0;i<nRaizes;i++){
        raizes[i] = auxRaizes[i];
    }
    
    return raizes;
}

ArgumentoInvalidoExcept::ArgumentoInvalidoExcept(const char*message){
    this->message = message;
}
const char* ArgumentoInvalidoExcept::what() const throw(){
    return message;
}

ArgumentoInvalidoExcept::~ArgumentoInvalidoExcept(){
    //delete[]message;
}

RaizesNaoEncontradasExcept::RaizesNaoEncontradasExcept(const char*message){
    this->message = (char*) message;
}

RaizesNaoEncontradasExcept::~RaizesNaoEncontradasExcept(){
    //delete[]this->message;
}

const char* RaizesNaoEncontradasExcept::what() const throw(){
    return message;
}

PosicaoInvalidaExcept::PosicaoInvalidaExcept(const char *message)
{
    //this->message = message;
}
PosicaoInvalidaExcept::~PosicaoInvalidaExcept()
{
    delete[]this->message;
}
const char *PosicaoInvalidaExcept::what() const throw()
{
    return message;
}

void Polinomio::removerZeros()
{
    for(int i=g;i>0;i--){
        if(v[i]!=0){
            double *t = new double[i+1];
            for(int j=0;j<i+1;j++)
                t[j] = this->v[j];
            delete[]this->v;
            this->v = t;
            g = i;
            return;
        }
    }
    double *t = new double[1];
    t[0] = 0;
    delete[]v;
    v = t;
    g = 0;
}



void Polinomio::imprimeNumeroSuperEscrito(int val) const{
    int nAlgarismos = log10(val);
    for(int i=0;i<nAlgarismos+1;i++){
        int n = val%10;
        if(n==0) cout<<"⁰";
        if(n==1) cout<<"¹";
        if(n==2) cout<<"²";
        if(n==3) cout<<"³";
        if(n==4) cout<<"⁴";
        if(n==5) cout<<"⁵";
        if(n==6) cout<<"⁶";
        if(n==7) cout<<"⁷";
        if(n==8) cout<<"⁸";
        if(n==9) cout<<"⁹";
        val/=10;
    }
}

