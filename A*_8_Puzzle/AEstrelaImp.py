from Posicao import Posicao
from AEstrela import AEstrela
from QuebraCabeca import QuebraCabeca
from QuebraCabecaImp import QuebraCabecaImp
import math
import queue
import heapq
from random import gammavariate, shuffle

def manhattan(dest_i, dest_j, gab_origin, current_table):
        curr_i = 0
        curr_j = 0 
        for i in range(0, 3):
            for j in range(0, 3):
                if current_table[i][j] == gab_origin:
                    curr_i = i
                    curr_j = j
        first_abs = abs(curr_i - dest_i)
        second_abs = abs(curr_j - dest_j)
        sum_abs = first_abs + second_abs
        return sum_abs

def get_H(node):
        gab_table = node.tabGabarito
        current_table = node.getTab()
        h_value = 0
        for i in range(0, 3):
            for j in range(0, 3):
                if gab_table[i][j] != current_table[i][j]:
                    h_value += manhattan(i,j, gab_table[i][j], current_table)                  
        return h_value

class AEstrelaImp(AEstrela):

    def getSolucao(self, qc):
        checkedHashes = set() #set para armazenar hashes de diferentes tabelas (não se mover para duplicatas)
        checkedHashes.add(qc.hashCode()) #adiciona hash code da tabela raiz
        G_Function = 1

        #caso a tabela inicial seja o resultado objetivo (gabarito) a função retorna um iterador vazio (sem movimentos)
        if(qc.getTab() == qc.tabGabarito): return iter([])


        #lista que será retornada com cada iteração (posição atual do vazio no quebra-cabeça, será retornada para main)
        voidSpaceList = [] #aqui ela adiciona o local do vazio na tabela inicial e outras tabelas futuras
        
        #lista que será utilizada para armazenar cada tabela derivada da tabela inicial
        tableList = [[(get_H(qc) + G_Function), G_Function, qc.getTab()]] #adiciona a tabela base com 3 parâmetros X, Y e Z:
        #X = F = (Get_H(qc) + G_Function), ou seja, a heurística mais o grau do nodo (tabela analisada)
        #Y = Grau na árvore (utilizado em cálculos futuros para decidir o melhor caminho com base no valor F (G+H))
        #Z = A tabela em si daquele quebra-cabeça
        
        
        
        while True:
            availableMoves = qc.getMovePossiveis() #essa lista irá armazenar os movimentos possíveis do quebra-cabeça atual pela função do QuebraCabeçaImp
            pos_vazio = qc.getPosVazio() #essa variável armazena a posição do vazio no quebra-cabeça atual

            for movimento in availableMoves:   
                aux_table = qc.getTab() #essa variável armazena a tabela inicial desse loop, para retornar a ela sempre que um novo movimento for adicionado a pilha
                qc.move(pos_vazio.getLinha(), pos_vazio.getColuna(), movimento.getLinha(), movimento.getColuna()) #realiza um movimento sob a tabela inicial do loop
                
                if qc.hashCode() not in checkedHashes: #checa se a nova tabela após o movimento está inserida na variável que armazena todas as tabelas já testadas anteriormente (utilizando da hash única)
                    checkedHashes.add(qc.hashCode()) #se não tiver armazena ela na lista de hashes únicas
                    tableList.append([(get_H(qc) + G_Function + 1), tableList[0][1] + 1, qc.getTab()]) #adiciona a nova tabela 

                qc.setTab(aux_table) #após analisar um movimento retorna a tabela inicial antes dos movimentos (para verificar outras possibilidades a partir daquela tabela)

            tableList.pop(0) #ao sair do loop que analisa todos os movimentos possíveis, remove o primeiro elemento da lista (aquela tabela que estava sendo analisada)
            tableList.sort() #ordena novamente a lista

            qc.setTab(tableList[0][2]) #após excluir o antigo primeiro elemento da lista, o próximo é a tabela com menor F (foi ordenada com base no X da lista TableList)
            voidSpaceList.append(qc.getPosVazio()) #adiciona a lista de locais do espaço vazio a posição do vazio após mover ele de lugar, para colocar esses resultados na main
            print(qc.toString())
            if qc.getTab() == qc.tabGabarito: break #checa se a próxima tabela que seria analisada é o gabarito, se for sai do loop, senão, repete o processo com a nova tabela de menor F
         
        return voidSpaceList #retorna a lista de movimentos com o espaço vazio que será printada na main