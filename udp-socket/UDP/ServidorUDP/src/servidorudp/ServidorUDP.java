package servidorudp;

import java.io.IOException;
import static java.lang.System.exit;
import java.net.BindException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ServidorUDP {

    private static final ArrayList<String> listaDeMensagens = new ArrayList();
    private static final int PORTA = 1234;

    public static void main(String[] args) {
        boolean fimDoLaco = false;
        String mensagemRecebida, mensagemParaEnvio = "", comando, endereco = "", mensagem = "", enderecoAux = "", mensagemAux;
        char c;
        int i, j;

        while (!fimDoLaco) {
            mensagemRecebida = receberMensagem();

            if (mensagemRecebida.contains("post")) {
                comando = mensagemRecebida.substring(0, 4);

                if (!comando.equals("post")) {
                    System.out.println("Comando invalido");
                } else {

                    i = 5;
                    while ((c = mensagemRecebida.charAt(i)) != ' ') {
                        endereco = endereco.concat(c + "");
                        i++;
                    }

                    i++;
                    while ((c = mensagemRecebida.charAt(i)) != '\0') {
                        mensagem = mensagem.concat(c + "");
                        i++;
                    }

                    System.out.println("Mensagem: " + mensagem + " Recebido de: " + endereco);
                    listaDeMensagens.add(endereco + " " + mensagem);
                    enviarMensagem(endereco, PORTA, "" + (listaDeMensagens.size() - 1));
                }
            } else if (mensagemRecebida.contains("get")) {
                comando = mensagemRecebida.substring(0, 3);

                if (!comando.equals("get")) {
                    System.out.println("Comando invalido");
                } else {
                    i = 4;
                    while ((c = mensagemRecebida.charAt(i)) != ' ') {
                        endereco = endereco.concat(c + "");
                        i++;
                    }

                    i++;
                    while ((c = mensagemRecebida.charAt(i)) != '\0') {
                        mensagem = mensagem.concat(c + "");
                        i++;
                    }

                    if (!mensagem.contains(".")) {
                        try {
                            mensagemAux = listaDeMensagens.get(Integer.parseInt(mensagem));

                            i = 0;
                            while ((c = mensagemAux.charAt(i)) != ' ') {
                                enderecoAux = enderecoAux.concat(c + "");
                                i++;
                            }

                            i++;
                            while (i < mensagemAux.length()) {
                                c = mensagemAux.charAt(i);
                                mensagemParaEnvio = mensagemParaEnvio.concat(c + "");
                                i++;
                            }

                            mensagemParaEnvio = mensagemParaEnvio.concat("\n");
                        } catch (NumberFormatException | IndexOutOfBoundsException ioe) {
                            mensagemParaEnvio = "Dado nao encontrado\n";
                        }
                    } else {
                        j = 0;
                        while (j < listaDeMensagens.size()) {
                            mensagemAux = listaDeMensagens.get(j);

                            i = 0;
                            while ((c = mensagemAux.charAt(i)) != ' ') {
                                enderecoAux = enderecoAux.concat(c + "");
                                i++;
                            }

                            if (enderecoAux.equals(mensagem)) {
                                i++;
                                while (i < mensagemAux.length()) {
                                    c = mensagemAux.charAt(i);
                                    mensagemParaEnvio = mensagemParaEnvio.concat(c + "");
                                    i++;
                                }

                                mensagemParaEnvio = mensagemParaEnvio.concat("\n");
                            }

                            enderecoAux = "";
                            j++;
                        }

                        if (mensagemParaEnvio.isEmpty()) {
                            mensagemParaEnvio = "Dado nao encontrado\n";
                        }
                    }

                    enviarMensagem(endereco, PORTA, mensagemParaEnvio);
                }
            } else if (mensagemRecebida.contains("broadcast")) {
                comando = mensagemRecebida.substring(0, 9);

                if (!comando.equals("broadcast")) {
                    System.out.println("Comando invalido");
                } else {
                    i = 10;
                    while ((c = mensagemRecebida.charAt(i)) != ' ') {
                        endereco = endereco.concat(c + "");
                        i++;
                    }

                    i = 0;

                    while (i < listaDeMensagens.size()) {
                        mensagemParaEnvio = mensagemParaEnvio.concat(listaDeMensagens.get(i) + '\n');
                        i++;
                    }

                    if (mensagemParaEnvio.isEmpty()) {
                        mensagemParaEnvio = "Nao existe dados cadastrados\n";
                    }

                    enviarMensagem(endereco, PORTA, mensagemParaEnvio);
                }
            } else {
                System.out.println("Comando invalido");
            }

            mensagemParaEnvio = "";
            endereco = "";
            mensagem = "";
            enderecoAux = "";
        }
    }

    private static void enviarMensagem(String enderecoDestino, int porta, String msg) {
        InetAddress endereco;
        byte[] mensagem;
        DatagramPacket pacote;
        DatagramSocket datagrama;

        try {
            Thread.sleep(250);
            endereco = InetAddress.getByName(enderecoDestino);
            mensagem = msg.getBytes();

            pacote = new DatagramPacket(mensagem, mensagem.length, endereco, porta);
            datagrama = new DatagramSocket();
            datagrama.send(pacote);

            if (msg.contains("\n")) {
                System.out.println("Lista de mensagens enviado para: " + endereco.getHostAddress());
            } else {
                System.out.println("Mensagem: " + msg + " Enviado para: " + endereco.getHostAddress());
            }

            datagrama.close();
            Thread.sleep(250);
        } catch (IOException ioe) {
        } catch (InterruptedException ex) {
            Logger.getLogger(ServidorUDP.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private static String receberMensagem() {
        DatagramSocket datagrama;
        String mensagemRecebida = "";
        byte[] mensagem;
        DatagramPacket pacote;

        try {
            datagrama = new DatagramSocket(PORTA);
            System.out.println("Ouvindo a porta: " + PORTA);
            mensagem = new byte[256];
            pacote = new DatagramPacket(mensagem, mensagem.length);
            datagrama.receive(pacote);
            mensagemRecebida = new String(pacote.getData());
            datagrama.close();
        } catch (BindException ioe) {
            System.out.println("Porta em uso");
            exit(0);
        } catch (IOException ioe) {
        }

        return mensagemRecebida;
    }
}
