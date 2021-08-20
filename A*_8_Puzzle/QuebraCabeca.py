import abc

class QuebraCabeca(metaclass=abc.ABCMeta):
    VAZIO = -1

    # Metodo que retorna uma copia do array interno de posicoes (-1 = vazio)
    # @return int[][] - um array 3x3 de inteiros
    @abc.abstractmethod
    def getTab(self):
        return

    # Metodo define o arranjo de pecas segundo o array passado por parametro
    # @param  aux - um array 3x3 de inteiros (-1 = vazio)
    # @throws Exception se o array nao e compativel
    @abc.abstractmethod
    def setTab(self, aux):
        return

    # Move o vazio da posicao linha1, col1 para linha2,  col2
    # @param  linha1 - linha do vazio
    # @param  col1 - coluna do vazio
    # @param  linha2 - linha do destino
    # @param  col2 - coluna do destino
    # @throws Exception se a posição é invalida
    @abc.abstractmethod
    def move(self, linha1, col1, linha2, col2):
        return

    # Verifica se Quebra-Cabeca esta ordenado
    # @return true se esta' ordenado
    @abc.abstractmethod
    def isOrdenado(self):
        return

    # retorna a posicao do vazio
    # @return objeto Posicao com as coordenadas da posicao vazia
    @abc.abstractmethod
    def getPosVazio(self):
        return

    # retorna o valor do quebra-cabeca segundo uma heuristica (implementada a distancia quarterao)
    # @return valor do quebra-cabeca
    @abc.abstractmethod
    def getValor(self):
        return

    # retorna uma lista de posições de movimentos possiveis
    # @return Lista de posicoes
    @abc.abstractmethod
    def getMovePossiveis(self):
        return

    # retorna o Quebra-cabeca na forma de String para a impressao
    # @return quebra-cabeca na forma de String
    @abc.abstractmethod
    def toString(self):
        return

    # Verifica se dois quebra-cabecas são iguais
    # @param qc - quebra-cabeça
    # @return true se são iguas
    @abc.abstractmethod
    def equals(self, qc):
        return

    # Retorna um codigo hash para este quebra-cabeca
    # @return codigo hash
    @abc.abstractmethod
    def hashCode(self):
        return
