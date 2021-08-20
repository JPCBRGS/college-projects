import datetime
from Posicao import Posicao
from AEstrelaImp import AEstrelaImp
from QuebraCabecaImp import QuebraCabecaImp

def main():
    qc = QuebraCabecaImp()
    instance = AEstrelaImp()

    tab = [[7, 2, 1], [3, 4, 8], [6, QuebraCabecaImp.VAZIO, 5]]
    #tab = [[7, 2, 4], [5, QuebraCabecaImp.VAZIO, 6], [8, 3, 1]]
    #tab = [[8, 1, 2], [QuebraCabecaImp.VAZIO, 4, 3], [7, 6, 5]] # Exemplo sem solução (Not Solvable). Ref: https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/    
    qc.setTab(tab)

    tempo = datetime.datetime.now()
    result = instance.getSolucao(qc)

    print("Tempo decorrido: " + str(int((datetime.datetime.now() - tempo).total_seconds()*100)) + " centesimos de segundos")

    print("Tabuleiro inicial:")
    qc.setTab(tab)
    print(qc.toString())
       
    print("Movimentos")
    for pos in result:
        print("Linha: " + str(pos.getLinha()) + " - Coluna: " + str(pos.getColuna()))

main()
