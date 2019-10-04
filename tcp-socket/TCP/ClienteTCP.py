# --------------------------- IMPORTAÇÕES ----------------------------------

from socket import *
from threading import Thread
import time


# ----------------------------- FUNÇÕES ------------------------------------

'''
Função executada em thread, resposável por receber dados do servidor
e imprimir na tela do client
'''
def onClient(sockobj, serverHost = 'localhost', serverPort = 50007):

    sockobj.connect((serverHost, serverPort)) # Utilizando socket para conexão

    # Menu de instruções rápidas para o client
    print('\033[36mConexão estabelecida.{bold} ChatHK 0.1{none}\n'
          '{green}USO:{none} [comando] mensagem <ENTER>\n'
          '{green}ONDE:{none}\n'
          '\t{bold}<ENTER>{none}{t4}:tecla enter\n'
          '\t{bold}mensagem{none}{t4}:texto que pretende enviar\n'
          '{green}COMANDO:{none}\n'
          '\t{bold}!lu{none}{t4}:lista todos usuário conectados\n'
          '\t{bold}!pm [idUser]{none}\t:envia mensagem privada para usuário informado\n'
          '\t{bold}!q{none}{t4}:encerra conexão\n'
          .format(bold='\033[1m', green='\033[32m', none='\033[0;0m', t2='\t'*2, t4='\t'*4))

    # Recebe a mensagem, decodifica e imprimi na tela
    try:
        while True:
            message = sockobj.recv(1024)
            message = message.decode()
            if message == '!q':
                print('\033[36mEncerrando conexão.\033[0;0m')
                break
            print(message)
    except:
        pass
'''
end-onClient
'''


# ------------------------------ MAIN -------------------------------------

serverHost = 'localhost'
serverPort = 50007

try:
    # Recebendo dados p/conexão do usuário
    #serverHost = input('Informe o servidor: ')
    #serverPort = int(input('Informe a porta: '))

    # Criando socket e designando processo para thread
    sockobj = socket(AF_INET, SOCK_STREAM)
    process = Thread(target = onClient, args = (sockobj, serverHost, serverPort))
    process.start()

    # Temporizador para conexão
    time.sleep(0.5)

    # Envio do codinome de usuário
    message = input('\033[1mDigite seu codenome: \033[0;0m')
    sockobj.send(message.encode())

    # Envio de mensagem/comandos ao servidor !q é comando de encerrar conexão
    while message != '!q':
        message = input()
        if not message: continue # Ignora mensagem vazia
        sockobj.send(message.encode())

    process.join()
    sockobj.close()

except IndentationError:
    print('\033[31mPorta em uso, tente novamente!\033[0;0m')
except KeyboardInterrupt:
    print('\033[31mConexão encerrou de forma inesperada.\033[0;0m')
except ConnectionRefusedError:
    print('\033[31mConexão recusada.\033[0;0m')
except OverflowError:
    print('\033[31mPorta incorreta. Informe a porta no intervalo 0-65535\033[0;0m')
except OSError:
    print('\033[31mServidor/Porta inválidas\033[0;0m')
except:
    print('\033[31mErro inesperado, entre em contato com suporte!\033[0;0m')