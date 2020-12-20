#Jogo da velha para dois jogadores
#Gustavo Vieira

def printa_tabu(tabu):  #imprime o tabuleiro no monitor
    print(tabu[1]+' | '+tabu[2]+' | '+tabu[3])
    print(tabu[4]+' | '+tabu[5]+' | '+tabu[6])
    print(tabu[7]+' | '+tabu[8]+' | '+tabu[9])

def esc_simbolo():  #função para atribuir um síbolo ao jogador 1
    simbolo = ''
    while simbolo not in ['x','o']:
        simbolo = input('Escolha \'x\' ou \'o\': ')
    jog1 = simbolo
    if jog1 == 'x':
        jog2 = 'o'
    else:
        jog2 = 'x'
    return (jog1,jog2)

def pos_simbolo(tabu, simbolo, pos):  #função para posicionar o símbolo em um dos espaços do tabuleiro
    tabu[pos] = simbolo

def checa_vit(tabu, simb):  #função que checa se alguma condição de vitória foi atingida
    return(tabu[7] == tabu[8] == tabu[9] == simb) or\
    (tabu[4] == tabu[5] == tabu[6] == simb) or\
    (tabu[1] == tabu[2] == tabu[3] == simb) or\
    (tabu[7] == tabu[4] == tabu[1] == simb) or\
    (tabu[8] == tabu[5] == tabu[2] == simb) or\
    (tabu[9] == tabu[6] == tabu[3] == simb) or\
    (tabu[7] == tabu[5] == tabu[3] == simb) or\
    (tabu[9] == tabu[5] == tabu[1] == simb)

import random
def esc_aleat():  #função que define qual jogador inicia o jogo
    resultado = random.randint(0,999)  #inteiro de 0 a 999
    if resultado % 2 == 0:             #se par, jogador 2 começa
        print('Jogador 2 começa!')
        return 'Jogador 2'
    else:                           #se ímpar, jogador 1 começa
        print('Jogador 1 começa!')
        return 'Jogador 1'

def checa_esp(tabu, pos):  #função que checa se o espaço no tabuleiro está vazio
    return tabu[pos] == ' '

def checa_tabu(tabu):  #função que checa se o tabuleiro está completamente cheio para atribuição de empate
    for i in range(1,10):
        if checa_esp(tabu,i):
            return False
        else:
            pass
    return True

def esc_esp(tabu):  #função para atribuição de um símbolo a um espaço escolhido pelo jogador
    pos = 0
    while pos not in [1,2,3,4,5,6,7,8,9] or not checa_esp(tabu,pos):
        pos = int(input("Escolha um espaço: "))
        if checa_esp(tabu,pos) == False:
            print("Escolha outro espaço.")
    return pos

print("O jogo da velha vai começar!")
jogo_ativo = True
tabuleiro = [' '] * 10
jog1_simb, jog2_simb = esc_simbolo()
turno = esc_aleat()

while jogo_ativo:

    if turno == "Jogador 1":

        printa_tabu(tabuleiro)
        pos = esc_esp(tabuleiro)
        pos_simbolo(tabuleiro, jog1_simb, pos)

        if checa_vit(tabuleiro, jog1_simb):
            printa_tabu(tabuleiro)
            print("Jogador 1 ganhou!")
            jogo_ativo = False
        else:
            if checa_tabu(tabuleiro):
                printa_tabu(tabuleiro)
                print("Empatou!")
                jogo_ativo = False
                break
            else:
                turno = "Jogador 2"
    else:

        printa_tabu(tabuleiro)
        pos = esc_esp(tabuleiro)
        pos_simbolo(tabuleiro, jog2_simb, pos)

        if checa_vit(tabuleiro, jog2_simb):
            printa_tabu(tabuleiro)
            print("Jogador 2 ganhou!")
            jogo_ativo = False
        else:
            if checa_tabu(tabuleiro):
                printa_tabu(tabuleiro)
                print("Empatou!")
                jogo_ativo = False
                break
            else:
                turno = "Jogador 1"
