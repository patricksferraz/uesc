# --------------------------- IMPORTAÇÕES ----------------------------------

import time, _thread as thread
from socket import *


# ----------------------------- FUNÇÕES ------------------------------------

'''
Função para retornar o datetime
'''
def reportDate(): return time.ctime(time.time())  # Retorna datetime
'''
end-reportDate
'''


'''
Função para conectar cliente a uma thread do servidor
'''
def connectClient(connection, address):

    global client # Identificando o dicionário de clientes

    codename = connection.recv(1024)            # Recebe dados do cliente
    codename = codename.decode()                # Decodificando byte
    client[address[1]] = [codename, connection] # Adiciona o cliente as conexões ativas

    # FeedBack para codinome
    message = '\033[36mCodinome definido como \033[1m%s.\033[0;0m' \
               '\033[36m\nDigite suas mensagens livremente:\033[0;0m' % codename
    connection.send(message.encode())

    # Informando conexão de novo cliente aos usuários
    message = 'O usuário\033[1m %s[%i]\033[32m entrou\033[0;0m' % (codename, address[1])
    broadcast(message, connection)

    # Laço para o servidor responder as mensagens/comandos do usuário
    while True:

        try:

            data = connection.recv(1024)    # Recebe dados do cliente
            if not data: break              # Encerra loop

            # Verifica se a mensagem do client é um comando
            data = data.decode()
            if data[0] == '!':
                data = data.split() # Converte a mensagem em lista
                cmd = data.pop(0)   # Captura o comando (primeiro indice da lista), removendo-o

                # Verifica qual comando foi solicitado
                # !lu retorna todos clientes conectados
                if cmd == '!lu':
                    answer = '\033[36mUsuários conectados:'
                    for i in client:
                        answer += '\n%s:[%i]' % (client[i][0], i)
                    answer += '\033[0;0m'

                # !pm envia mensagem privada através do id de conexão do client
                elif cmd == '!pm':

                    idUserRecip = int(data.pop(0))  # Captura o id do client, antes pertencia ao indice(1)

                    # Verifica se client está conectado
                    if client[idUserRecip]:
                        connectionUserRecip = client[idUserRecip][1]                    # Resgata conexão do id
                        pm = '\033[34mPM: %s[%i]:\033[0;0m ' % (codename, address[1])   # Constroi cabeçalho da mensagem
                        pm += ' '.join(data)                                            # Constroi a mensagem
                        connectionUserRecip.send(pm.encode())                           # Envia a mensagem

                        # FeedBack
                        answer = '\033[36mPM enviada com sucesso para\033[1m %s[%i]\033[0;0m' \
                                 % (client[idUserRecip][0], idUserRecip)

                # !q encera a conexão
                elif cmd == '!q':
                    answer = '!q'
                    connection.send(answer.encode())  # Envia mensagem
                    break

                # ![..] comando inválido
                else:
                    answer = '\033[36mComando inválido\033[0;0m'

                connection.send(answer.encode())  # Envia mensagem

            else:
                # Envia mensagem pública
                data = ''.join(data)
                message = '\033[1m%s[%i]:\033[0;0m %s' % (codename, address[1], data)
                broadcast(message, connection)

                # Eco do usuário
                eco = '\033[1mVocê[%i]:\033[35m %s\033[0;0m' % (address[1], data)
                connection.send(eco.encode())

        except KeyError:
            answer = '\033[36mUsuário não existe ou não está conectado.\033[0;0m'
            connection.send(answer.encode())  # Envia mensagem
        except ValueError:
            answer = '\033[36mId do usuário deve ser um inteiro.\033[0;0m'
            connection.send(answer.encode())  # Envia mensagem
        except IndexError:
            answer = '\033[36mComando incompleto, tente novamente!\033[0;0m'
            connection.send(answer.encode())  # Envia mensagem
        except:
            answer = '\033[36mErro inesperado. Entre em contato com suporte!\033[0;0m'
            connection.send(answer.encode())  # Envia mensagem

    # Informando desconexão do usuário
    message = 'O usuário\033[1m %s[%i]\033[31m saiu\033[0;0m' % (codename, address[1])
    broadcast(message, connection)

    # Exibi as informações da conexão encerrada
    print('Server\033[31m desconectado\033[0;0m por', address, end=' ')
    print('as', reportDate())

    del(client[address[1]]) # Remove o cliente das conexões
    connection.close()      # Encerra conexão
'''
end-connectClient
'''

'''
Função para servidor enviar mensagens em broadcast
'''
def serverSend():

    while True:
        message = input()
        if not message: continue
        message = '\033[36m[Server %s]: %s\033[0;0m' % (reportDate(), message)
        broadcast(message, '')
        print(message)
'''
end-serverSend
'''


'''
Função para enviar mensagem em modo broadcast
'''
def broadcast(message, connection):

    global client

    for cl in client:
        if client[cl][1] != connection:
            try:
                client[cl][1].send(message.encode())
            except:
                answer = 'Erro ao enviar para \033[1m %s[%i] \033[0;0m' % (client[cl][0], cl)
                connection.send(answer.encode())
'''
end-broadcast
'''


'''
Função para ligar servidor
'''
def onServer():

    print('\033[36mServidor conectado!\nOuvindo a porta\033[1m %s\033[0;0m' % port)
    thread.start_new_thread(serverSend, ())

    try:
        while True:
            connection, address = sockobj.accept()  # Aceita conexão

            # Exibi as informações da conexão
            print('Server\033[32m conectado\033[0;0m por', address, end=' ')
            print('as', reportDate())

            # Designa thread para conexão
            thread.start_new_thread(connectClient, (connection, address))
    except KeyboardInterrupt:
        print('\033[31mServidor desligou de forma inesperada\033[0;0m')

'''
end-onServer
'''


# ------------------------------ MAIN -------------------------------------

host = ''       # Host
port = 50007    # Porta
client = {}    # Lista de clientes conectados

try:

    sockobj = socket(AF_INET, SOCK_STREAM)  # Criando socket TCP/IP
    sockobj.bind((host, port))              # Vincula o servidor a uma porta

    sockobj.listen(5)  # Limite de conexões simultâneas
    onServer()         # Liga o servidor

except IndentationError:
    print('\033[31mPorta em uso, tente novamente!\033[0;0m')
except OSError:
    print('\033[31mEndereço em uso.\033[0;0m')
except:
    print('\033[31mErro inesperado. Entre em contato com suporte!\033[0;0m')
