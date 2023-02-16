import random
from Posicao import Posicao
from QuebraCabeca import QuebraCabeca

class QuebraCabecaImp(QuebraCabeca):
    tabGabarito = [[1, 2, 3], [4, QuebraCabeca.VAZIO, 5], [6, 7, 8]]

    # Construtor que inicia o quebra-cabeça com posicoes aleatorias
    def __init__(self):
        aux_tab = [1, 2, 3, 4, 5, 6, 7, 8, QuebraCabeca.VAZIO]
        random.shuffle(aux_tab)
        self.tab = [aux_tab[0:3], aux_tab[3:6], aux_tab[6:9]]

    # Metodo que retorna uma copia do array interno de posicoes (-1 = vazio)
    # @return int[][] - um array 3x3 de inteiros
    def getTab(self):
        aux = []
        for i in range(0, 3):
            aux.append([])
            for j in range(0, 3):
                aux[i].append(self.tab[i][j])
        return aux

    # Metodo define o arranjo de pecas segundo o array passado por parametro
    # @param  aux - um array 3x3 de inteiros (-1 = vazio)
    # @throws Exception se o array nao e compativel
    def setTab(self, aux):
        if(aux is None):
            raise Exception("Array vazio!")
        if(len(aux) != 3 or len(aux[0]) != 3 or len(aux[1]) != 3 or len(aux[2]) != 3):
            raise Exception("Tamanho incompativel!")
        self.tab = []
        for i in range(0, 3):
            self.tab.append([])
            for j in range(0, 3):
                self.tab[i].append(aux[i][j])
        #self.tab = aux.copy()

    # Move o vazio da posicao linha1, col1 para linha2,  col2
    # @param  linha1 - linha do vazio
    # @param  col1 - coluna do vazio
    # @param  linha2 - linha do destino
    # @param  col2 - coluna do destino
    # @throws Exception se a posição é invalida
    def move(self, linha1, col1, linha2, col2):
        if(linha1 < 0 or linha1 > 2):
            raise Exception("Fora de dimensao!")
        if(linha2 < 0 or linha2 > 2):
            raise Exception("Fora de dimensao!")
        if(col1 < 0 or col1 > 2):
            raise Exception("Fora de dimensao!")
        if(col2 < 0 or col2 > 2):
            raise Exception("Fora de dimensao!")
        if(self.tab[linha1][col1] != QuebraCabeca.VAZIO):            
            raise Exception("Nao eh a posicao do vazio!")
        if(linha2 != linha1 and col2 != col1):
            raise Exception("Movimento na diagonal!")
        if(abs(linha2 - linha1) > 1 or abs(col2 - col1) > 1):
            raise Exception("Movimento longo!")
        self.tab[linha1][col1] = self.tab[linha2][col2]
        self.tab[linha2][col2] = QuebraCabeca.VAZIO

    # Verifica se Quebra-Cabeca esta ordenado
    # @return true se esta' ordenado
    def isOrdenado(self):
        return self.tab == QuebraCabecaImp.tabGabarito

    # retorna a posicao do vazio
    # @return objeto Posicao com as coordenadas da posicao vazia
    def getPosVazio(self):
        for i in range(0, 3):
            for j in range(0, 3):
                if(self.tab[i][j] == QuebraCabeca.VAZIO):
                    pos = Posicao(i, j)
                    return pos
        return None

    # retorna o valor do quebra-cabeca segundo uma heuristica (implementada a distancia quarterao)
    # @return valor do quebra-cabeca
    def getValor(self):
        valor = 0
        for i in range(0, 3):
            for j in range(0, 3):
                if(self.tab[i][j] != QuebraCabecaImp.tabGabarito[i][j] and self.tab[i][j] != QuebraCabeca.VAZIO):
                    pos = QuebraCabecaImp.getPos(self.tab[i][j], QuebraCabecaImp.tabGabarito)
                    valor = valor + (abs(pos.getLinha()-i) + abs(pos.getColuna()-j))
        return valor

    # retorna a posicao de um valor em relacao a um array
    # @param valor
    # @param tab array a ser investigado
    # @return a posicao
    def getPos(valor, tab):
        for i in range(0, 3):
            for j in range(0, 3):
                if(tab[i][j] == valor):
                    return Posicao(i, j)
        return None

    # retorna uma lista de posições de movimentos possiveis
    # @return Lista de posicoes
    def getMovePossiveis(self):
        lista = []
        posv = self.getPosVazio()
        if(posv.getLinha() > 0):
            lista.append(Posicao(posv.getLinha()-1, posv.getColuna()))
        if(posv.getLinha() < 2):
            lista.append(Posicao(posv.getLinha()+1, posv.getColuna()))
        if(posv.getColuna() > 0):
            lista.append(Posicao(posv.getLinha(), posv.getColuna()-1))
        if(posv.getColuna() < 2):
            lista.append(Posicao(posv.getLinha(), posv.getColuna()+1))

        return lista

    # retorna o Quebra-cabeca na forma de String para a impressao
    # @return quebra-cabeca na forma de String
    def toString(self):
        buf = ''
        for i in range(0, 3):
            for j in range(0, 3):
                if(self.tab[i][j] == QuebraCabeca.VAZIO):
                    buf = buf + '  '
                else:
                    buf = buf + str(self.tab[i][j]) + ' '
            buf = buf + '\n'
        return buf

    # Verifica se dois quebra-cabecas sao iguais
    # @param qc - quebra-cabeca
    # @return true se sao iguais
    def equals(self, qc):
        tabaux = qc.getTab()
        for i in range(0, 3):
            for j in range(0, 3):
                if(self.tab[i][j] != tabaux[i][j]):
                    return False                
        return True

    # Retorna um codigo hash para este quebra-cabeca
    # @return codigo hash
    def hashCode(self):
        codigo = 0
        exp = 0

        for i in range(0, 3):
            for j in range(0, 3):
                if(self.tab[i][j] != QuebraCabeca.VAZIO):
                    codigo = codigo + self.tab[i][j] * 10**exp
                else:
                    codigo = codigo + 9 * 10**exp
                exp = exp + 1
        return codigo

''' #para testes..
qq = QuebraCabecaImp()
print(qq.tab)
pos = qq.getPosVazio()
print(pos.getLinha())
print(pos.getColuna())
print(qq.isOrdenado())
print(qq.toString())
qq.setTab(QuebraCabecaImp.tabGabarito)
print(qq.toString())
'''

