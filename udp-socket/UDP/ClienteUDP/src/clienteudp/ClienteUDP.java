package clienteudp;

import java.io.IOException;
import static java.lang.System.exit;
import java.net.BindException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ClienteUDP {

    private static final String NOME_SERVIDOR = "172.020.010.006"; //colocar o nome ou ip do computador que vai ser o servidor
    private static final int PORTA = 1234;

    public static void main(String[] args) {
        boolean fimDoLaco = false;
        String linha, comando, mensagem, mensagemRecebida;
        Scanner teclado = new Scanner(System.in);

        while (!fimDoLaco) {
            System.out.print("Informe o comando: ");
            linha = teclado.nextLine();

            if (linha.contains("post")) {
                comando = linha.substring(0, 4);

                if (!comando.equals("post")) {
                    System.out.println("\nComando invalido\n");
                } else {
                    mensagem = linha.substring(5);
                    enviarMensagem(comando, NOME_SERVIDOR, PORTA, mensagem);
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ex) {
                        Logger.getLogger(ClienteUDP.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    mensagemRecebida = receberMensagem();

                    if (!mensagemRecebida.isEmpty()) {
                        System.out.println(mensagemRecebida);
                        System.out.println();
                    }
                }
            } else if (linha.contains("get")) {
                comando = linha.substring(0, 3);

                if (!comando.equals("get")) {
                    System.out.println("\nComando invalido\n");
                } else {
                    mensagem = linha.substring(4);
                    enviarMensagem(comando, NOME_SERVIDOR, PORTA, mensagem);
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ex) {
                        Logger.getLogger(ClienteUDP.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    mensagemRecebida = receberMensagem();

                    if (!mensagemRecebida.isEmpty()) {
                        System.out.println(mensagemRecebida);
                    }
                }
            } else if (linha.contains("broadcast")) {
                comando = linha.substring(0, 9);

                if (!comando.equals("broadcast")) {
                    System.out.println("\nComando invalido\n");
                } else {
                    enviarMensagem(comando, NOME_SERVIDOR, PORTA, "");
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ex) {
                        Logger.getLogger(ClienteUDP.class.getName()).log(Level.SEVERE, null, ex);
                    }
                    mensagemRecebida = receberMensagem();

                    if (!mensagemRecebida.isEmpty()) {
                        System.out.println(mensagemRecebida);
                    }
                }
            } else if (linha.contains("exit")) {
                comando = linha.substring(0, 4);

                if (!comando.equals("exit")) {
                    System.out.println("\nComando invalido\n");
                } else {
                    fimDoLaco = true;
                }
            } else {
                System.out.println("\nComando invalido\n");
            }
        }
    }

    private static void enviarMensagem(String metodo, String nomeServidor, int porta, String msg) {
        InetAddress endereco, enderecoLocal;
        String mensagemParaEnvio;
        byte[] mensagem;
        DatagramPacket pacote;
        DatagramSocket datagrama;

        try {
            endereco = InetAddress.getByName(nomeServidor);
            enderecoLocal = InetAddress.getLocalHost();
            mensagemParaEnvio = "".concat(metodo + " " + enderecoLocal.getHostAddress() + " " + msg);
            mensagem = mensagemParaEnvio.getBytes();

            pacote = new DatagramPacket(mensagem, mensagem.length, endereco, porta);
            datagrama = new DatagramSocket();
            datagrama.send(pacote);

            System.out.println();
            //System.out.println("Mensagem enviada para: " + endereco.getHostAddress() + "\n" + "Porta: " + porta + "\n" + "Mensagem: " + msg);

            datagrama.close();
        } catch (IOException ioe) {
            System.out.println("Não foi possivel conectar ao servidor");
            System.out.println();
        }
    }

    private static String receberMensagem() {
        DatagramSocket datagrama;
        String mensagemRecebida = "";
        byte[] mensagem;
        DatagramPacket pacote;

        try {
            datagrama = new DatagramSocket(PORTA);
            datagrama.setSoTimeout(10000);
            mensagem = new byte[256];
            pacote = new DatagramPacket(mensagem, mensagem.length);
            datagrama.receive(pacote);
            mensagemRecebida = new String(pacote.getData());
            datagrama.close();
        } catch (BindException ioe) {
            System.out.println("Porta em uso");
            exit(0);
        } catch (IOException ioe) {
            System.out.println("Servidor demorou para responder");
            System.out.println();
        }

        return mensagemRecebida;
    }
}
