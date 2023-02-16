import math

TEAM = int(input())  #valor do time - 0 pontua do lado direito, 1 pontua do lado esquerdo

#seleciona a localização do gol de acordo com o ID do time
if TEAM == 1: GOL = [0, 3750]
else: GOL = [16000, 3750]

#classe que armazena entidades e dados gerais do jogo
class Entidades:
    entityType = None  #WIZARD, OPPONENT_WIZARD, SNAFFLE ou BLUDGER 
    entitiesId = None
    x, y = None, None
    vx, vy = None, None
    state = None  #estado igual a 1 se o mago pegou o snaffle, senão igual a zero

    def __init__(main, data):
        main.entitiesId = data[0]
        main.entityType = data[1]
        main.x = data[2]
        main.y = data[3]
        main.vx = data[4]
        main.vy = data[5]
        main.state = data[6]

class Jogador:
    x, y = None, None
    vx, vy = None, None
    state = None

    def __init__(main, data):
        main.entitiesId = data.entitiesId
        main.entityType = data.entityType
        main.x = data.x
        main.y = data.y
        main.vx = data.vx
        main.vy = data.vy
        main.state = data.state

    #calcula distância entre duas entidades utilizando a função hypot
    def getDist(main, target):
        return math.hypot(abs(main.x - target.x), abs(main.y - target.y))

    #método para alcançar snaffle (seleciona snaffle mais próximo do mago parâmetro)
    def getSnaf(main, all_entities):
        snafMin = float('inf')
        snaffle = None
        for target in all_entities:
            if target.entityType != 'SNAFFLE': continue
            if main.getDist(target) <= snafMin:
                snafMin = main.getDist(target)
                snaffle = target
        return snaffle


    #métodos estáticos para jogar o snaffle e mover o mago respectivamente
    @staticmethod
    def throw(x, y, power): print('THROW %s %s %s' % (x, y, power))

    @staticmethod
    def move(x, y, thruster): print('MOVE %s %s %s' % (x, y, thruster))


while True:
    gameEntities = []
    #a função split foi utilizada nos trechos abaixo para partir a string de entrada nos valores necessários para serem armazenados
    myScore, myMagic = input().split()
    opponentScore, opponentMagic = input().split()
    entities = int(input())  #entidades ainda presentes no jogo
    #armazena dados recebidos nas variáveis locais
    for _ in range(entities):
        entityId, entityType, x, y, vx, vy, state = input().split()
        entitie = Entidades([int(entityId), entityType, int(x), int(y), int(vx), int(vy), int(state)])
        gameEntities.append(entitie)

    playerNum = 1
    wiz1, wiz2 = None, None #variáveis que representam os magos    
    
    
    #checa quais entidades das coletadas são magos no vetor gameEntities
    for entitie in gameEntities:
        if entitie.entityType == 'WIZARD':
            if playerNum == 1:
                playerNum += 1
                wiz1 = Jogador(entitie)
            if playerNum == 2: wiz2 = Jogador(entitie)

    #as variáveis nextsnaf recebem o próximo snaffle que deverá ser alcançado pelos magos
    nextsnaf1 = wiz1.getSnaf(all_entities=gameEntities)
    nextsnaf2 = wiz2.getSnaf(all_entities=gameEntities)

    #checa se o mago 1 está no range do snaffle (400 é o range do mago porém coloquei 200 pela margem de erro do movimento), se não estiver, vai para o alcance, se estiver, pega o snaffle
    if wiz1.getDist(nextsnaf1) > 200: wiz1.move(nextsnaf1.x, nextsnaf1.y, thruster=100) #situação em que não está no alcance
    else: wiz1.throw(GOL[0], GOL[1], power=500) #se estiver no alcance pega o snaffle

    #mesmos procedimentos para o mago 2
    if wiz2.getDist(nextsnaf2) > 200: wiz2.move(nextsnaf2.x, nextsnaf2.y, thruster=100)
    else: wiz2.throw(GOL[0], GOL[1], power=500)