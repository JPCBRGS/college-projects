import abc


class AEstrela(metaclass=abc.ABCMeta):

    # Recebe um quebra-cabeca e retorna uma lista de posições que representa os movimentos necessarios para chegar a solucao.
    # @param qc - Quebra-cabeca com o estado inicial
    # @return lista com os movimentos a serem realizados
    @abc.abstractmethod
    def getSolucao(self, qc):
        return
