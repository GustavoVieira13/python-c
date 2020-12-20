#Blackjack
#Gustavo Vieira

import random
naipes = ("Espadas", "Paus", "Copas", "Ouros")
ranques = ("Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei", "Ás")
valores = {"Dois":2, "Três":3, "Quatro":4, "Cinco":5, "Seis":6, "Sete":7, "Oito":8, "Nove":9, "Dez":10, "Valete":10,
         "Dama":10, "Rei":10, "Ás":11}
jogando = True

class Carta:
    def __init__(self, naipe, ranque):
        self.naipe = naipe
        self.ranque = ranque
    def __str__(self):
        return self.ranque+" de "+self.naipe

class Baralho:
    def __init__(self):
        self.baralho = []  #inicializa com uma lista vazia
        for naipe in naipes:
            for ranque in ranques:
                self.baralho.append(Carta(naipe, ranque))  #cria um baralho de 52 cartas
    def __str__(self):
        baralho_form = ''  #formação inicial do baralho como uma string vazia
        for carta in self.baralho:
            baralho_form += "\n " + carta.__str__()  #adiciona o print de cada string gerada da classe Carta()
        return "O baralho tem" + baralho_form
    def embaralhar(self):
        random.shuffle(self.baralho)
    def dar_as_cartas(self):
        uma_carta = self.baralho.pop()
        return uma_carta

class Mao:
    def __init__(self):
        self.cartas = []  #inicia a mão como uma lista vazia
        self.val = 0  #zero como pontuação inicial
        self.ases = 0  #como o ás pode valer 1 ou 11, é importante criar um atributo particular para ele
    def adic_carta(self, carta):
        self.cartas.append(carta)
        self.val += valores[carta.ranque]  #a medida que as cartas são adicionadas à mão, os respectivos valores também
        if carta.ranque == "Ás":
            self.ases += 1  #flag pra identificação de um ás na mão
    def ajuste_as(self):
        while self.val > 21 and self.ases:
            self.val -= 10
            self.ases -= 1

class Fichas:
    def __init__(self):
        self.total = 100  #valor máximo de fichas pré-estabelecido
        self.aposta = 0
    def vence_aposta(self):
        self.total += self.aposta
    def perde_aposta(self):
        self.total -= self.aposta

def apostar(fichas):
    while True:
        fichas.aposta = int(input("Quantas fichas quer apostar (máx. 100)? "))
        if fichas.aposta < 1:
            print("Valor positivo, por favor.")
            continue
        elif fichas.aposta > fichas.total:
            print("Valor acima do permitido pela mesa. Insira um valor inferior, por favor.")
            continue
        else:
            break

def pedir_carta(baralho, mao):
    uma_carta = baralho.dar_as_cartas()
    mao.adic_carta(uma_carta)
    mao.ajuste_as()

def pedir_ou_ficar(baralho, mao):
    global jogando  #controla o próximo loop de cartas
    while True:
        x = input("Pressione 'p' para pedir ou 'f' para ficar: ")
        if x[0].lower() == 'p':
            pedir_carta(baralho, mao)
        elif x[0].lower() == 'f':
            print("O jogador fica.")
            jogando = False
        else:
            print("Tente novamente.")
            continue
        break

def mostra_1(jogador, croupier):  #configuração de cartas do início do jogo é exibida, ou seja, uma das cartas
    print("\nMão do croupier:")   #do croupier deve ser mantida virada para baixo
    print(" <carta virada>")
    print('', croupier.cartas[1])
    print("\nMão do jogador:", *jogador.cartas, sep='\n ')  #parâmetro separador sep

def mostra_2(jogador, croupier):  #após a finalização da jogada, a carta do croupier é mostrada e valores calculados
    print("\nMão do croupier:", *croupier.cartas, sep='\n ')
    print("Mão do croupier =", croupier.val)
    print("\nSua mão:", *jogador.cartas, sep='\n ')
    print("Sua mão =", jogador.val)

def jogador_ultrapassa(jogador, croupier, fichas):
    print("O valor das suas cartas supera 21 pontos. Você perdeu.")
    fichas.perde_aposta()
    print(f"Total final de fichas: {fichas_jogador.total}. Obrigado por jogar!")

def jogador_vence(jogador, croupier, fichas):
    print("Você ganhou! Meus parabéns!")
    fichas.vence_aposta()
    print(f"Total final de fichas: {fichas_jogador.total}. Obrigado por jogar!")

def croupier_ultrapassa(jogador, croupier, fichas):
    print("O croupier superou os 21 pontos! Você ganhou!")
    fichas.vence_aposta()
    print(f"Total final de fichas: {fichas_jogador.total}. Obrigado por jogar!")

def croupier_vence(jogador, croupier, fichas):
    print("O croupier ganhou.")
    fichas.perde_aposta()
    print(f"Total final de fichas: {fichas_jogador.total}. Obrigado por jogar!")

def empate(jogador, croupier):
    print("Empate!")

while True:
    print("Bem-vindo ao Blackjack!\nO croupier continuará a pedir cartas a menos que atinja o valor 17 ou superior.")
    baralho = Baralho()
    baralho.embaralhar()

    #cria uma mão de cartas para o jogador e croupier
    mao_jogador = Mao()
    mao_jogador.adic_carta(baralho.dar_as_cartas())
    mao_jogador.adic_carta(baralho.dar_as_cartas())
    mao_croupier = Mao()
    mao_croupier.adic_carta(baralho.dar_as_cartas())
    mao_croupier.adic_carta(baralho.dar_as_cartas())

    #aposta de fichas é feita e a mão do jogador e a mão do croupier com uma das cartas viradas pra baixo é mostrada
    fichas_jogador = Fichas()
    apostar(fichas_jogador)
    mostra_1(mao_jogador, mao_croupier)

    #ciclo de pedir mais cartas ou ficar com as que se tem é iniciado
    while jogando:
        pedir_ou_ficar(baralho, mao_jogador)
        mostra_1(mao_jogador, mao_croupier)
        if mao_jogador.val > 21:
            jogador_ultrapassa(mao_jogador, mao_croupier, fichas_jogador)
            break
    #possibilidades de vitória e derrota são exploradas
    if mao_jogador.val <= 21:
        while mao_croupier.val < 17:
            pedir_carta(baralho, mao_croupier)
        mostra_2(mao_jogador, mao_croupier)
        if mao_croupier.val > 21:
            croupier_ultrapassa(mao_jogador, mao_croupier, fichas_jogador)
            break
        elif mao_croupier.val > mao_jogador.val:
            croupier_vence(mao_jogador, mao_croupier, fichas_jogador)
            break
        elif mao_croupier.val < mao_jogador.val:
            jogador_vence(mao_jogador, mao_croupier, fichas_jogador)
            break
        else:
            empate(mao_jogador, mao_croupier)
            break
    break
