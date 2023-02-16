class Posicao:
    def __init__(self, l, c):
        self.linha = l
        self.coluna = c

    def getLinha(self):
        return self.linha

    def setLinha(self, linha):
        self.linha = linha

    def getColuna(self):
        return self.coluna

    def setColuna(self, coluna):
        self.coluna = coluna;
