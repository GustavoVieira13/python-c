#Jogo da advinhação
#Gustavo Vieira

print("Bem-vindo ao jogo da advinhação!")
import random  #importa módulo gerador de números pseudo-randômicos
num = random.randint(1, 100) #atribui o número inteiro gerado à variável num
print(num)  #print verificador do número gerado
print("Escolha um número de 1 a 100. Se estiver próximo é quente, senão é frio!")
chutes = [0] #inicia lista para armazenar as tentativas com o valor zero (posição [0])

while True: #pede e assegura um número válido
    chute = int(input("Insira um número de 1 a 100: "))

    if chute < 1 or chute > 100: #define os limites
        print("Fora dos limites. Por favor, insira um número de 1 a 100: ")
        continue
    if chute == num: #identifica que o número chutado corresponde ao gerado pelo random.randint
        print(f"Você acertou em {len(chutes)} chutes!")
        break        #este break corta o append do último chute à lista chutes, porém permite a contagem adequada
                     #do número de items da lista visto que o item zero incluído desde o início já conta como um
    chutes.append(chute) #adiciona cada chute à lista chutes

    if chutes[-2]:
        print(f"Chute anterior: {chutes[-2]}")
        if abs(num - chute) < abs(num - chutes[-2]): #se a diferença entre o número gerado e o chute atual for menor que
            print('Esquentando!')                    #a diferença entre o número gerado e o chute anterior
        else:
            print('Esfriando!')                      #caso contrário
    else:
        if abs(chute - num) <= 10:                   #se a diferença entre o chute atual e o número gerado for menor
            print('Quente')                          #ou igual a 10
        else:
            print('Frio')