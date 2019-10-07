/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.UIManager;

/**
 *
 * @author Patrick
 */
public class InterfaceGrafica extends JPanel implements ActionListener{
    
    
    //Atributos
    private final int[] cLinhaBotao = new int[JogoPCruzadas.MAX_LINHA+1];//coordenada da linha do botao
    private final int[] cColunaBotao = new int[JogoPCruzadas.MAX_COLUNA+1];//coordenada da coluna do botao
    private final Jogador[] JOGADOR = new Jogador[2];//Determinando no max 2 jogadores
    private final JButton[] bt_SelecionaPalavra = new JButton[JogoPCruzadas.MAX_LINHA+1];//Botões de identificação presente na matriz
    private final JTextField[][] tf_Jogo = new JTextField[JogoPCruzadas.MAX_LINHA][JogoPCruzadas.MAX_COLUNA];//TextField para a cruzadinha
    private final JLabel lb_Desenvolvedor = new JLabel("Desenvolvido por: Patrick Ferraz e Maxwel Santos   |Versão: 1.0|", (int) CENTER_ALIGNMENT);
    private char[][] cruzadas = new char[JogoPCruzadas.MAX_LINHA][JogoPCruzadas.MAX_COLUNA];//Cruzadinha que será utilizada para o preenchimento do Textfield
    private int indiceJogador = 0;//Indice do jogador, quem começa é o Jogador[0]
    private double numeroJogadas = 1.0;//Double para sorteio de quem é a vez
    private String dificuldade, palpite;//Dificuldade e String palpite para verificar a cruzada
    private List dicas = new ArrayList();//Array com todas dicas da matriz
    private List palavras = new ArrayList();//Array com todas palavras da matriz
    private JFrame f_Principal, f_Secundario;//Frame com a exibição inicial e janelas secundárias
    private JLabel lb_ProxJogada;//Label para informar de quem é a proxima jogada
    private JTextField tf_Jogador1, tf_Jogador2;//TextField para digitar nome de ambos jogadores
    private JRadioButton rb_VsPlay, rb_VsMaquina, rb_Facil, rb_Medio, rb_Dificil;//Radio button para evitar seleções multiplas
    private JButton bt_Jogar, bt_Iniciar, bt_Score, bt_Instrucoes, bt_FecharPrincipal,//Botões para add as ações
            bt_FecharSecundario, bt_FecharJogo, bt_Atualizar, bt_DeletaScore, bt_Finalizar;
    //Fim atributos
    
    
    
    //Construtor
    private InterfaceGrafica(){
        //Altera a nomeclatura da caixa de dialogo e inicia o jogo
        UIManager.put("OptionPane.okButtonText", "Confirmar");
        UIManager.put("OptionPane.cancelButtonText", "Passar");
        menuPrincipal();
    }
    
    
    
    //Metodo para exibir o menu principal
    private void menuPrincipal(){
               
        //Botões do frame Principal e add ao ActionListener
        bt_Jogar = new JButton("Jogar");
        bt_Jogar.addActionListener(this);
        bt_Score = new JButton("Recordes");
        bt_Score.addActionListener(this);
        bt_Instrucoes = new JButton("Instruções");
        bt_Instrucoes.addActionListener(this);
        bt_FecharPrincipal = new JButton("Fechar");
        bt_FecharPrincipal.addActionListener(this);
        
        //Painel dos botões e adição dos botões
        JPanel pn_Botoes = new JPanel(new GridLayout(1,4));
        pn_Botoes.add(bt_Jogar);
        pn_Botoes.add(bt_Score);
        pn_Botoes.add(bt_Instrucoes);
        pn_Botoes.add(bt_FecharPrincipal);
        
        //Painel inferior do frame e sua adições
        JPanel pn_Inferior = new JPanel(new GridLayout(2, 1));
        JLabel lb_DesenvolvedorPrincipal = new JLabel("Desenvolvido por: Patrick Ferraz e Maxwel Santos   |Versão: 1.0|", (int) CENTER_ALIGNMENT);
        pn_Inferior.add(pn_Botoes);
        pn_Inferior.add(lb_DesenvolvedorPrincipal);
        
        //Imagem de logo para adicionar ao centro do frame
        JLabel lb_Imagem = new JLabel(new ImageIcon("pcruzadas.png"));
        
        //Adições ao frame Principal do jogo
        f_Principal = new JFrame("Palavras Cruzadas");
        f_Principal.setLayout(new BorderLayout());
        f_Principal.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f_Principal.add(BorderLayout.CENTER, lb_Imagem);
        f_Principal.add(BorderLayout.SOUTH, pn_Inferior);
        
        //Empacotando o frame e exibindo
        f_Principal.pack();
        f_Principal.setVisible(true);    
    }
    //Fim metodo menuPrincial
    
    
    
    //Metodo para exibir o menu do jogo
    public void menuJogo(){
        
        //TextField para digitar os nomes dos jogadores
        tf_Jogador1 = new JTextField(15);
        tf_Jogador2 = new JTextField(15);
        tf_Jogador1.setBorder(javax.swing.BorderFactory.createTitledBorder("Jogador 1"));
        tf_Jogador2.setBorder(javax.swing.BorderFactory.createTitledBorder("Jogador 2"));
        
        //Painel para adicionar os TextField
        JPanel pn_NomeJogadores = new JPanel(new GridLayout(1, 2));
        pn_NomeJogadores.add(tf_Jogador1);
        pn_NomeJogadores.add(tf_Jogador2);
        
        //Botões para o painel de botões
        bt_Iniciar = new JButton("Iniciar");
        bt_Iniciar.setEnabled(false);
        bt_Iniciar.addActionListener(this);
        bt_FecharSecundario = new JButton("Voltar");
        bt_FecharSecundario.addActionListener(this);
        bt_Atualizar = new JButton("Atualizar");
        bt_Atualizar.addActionListener(this);
        
        //Painel com os botões
        JPanel pn_Botoes = new JPanel(new GridLayout(1, 3));
        pn_Botoes.add(bt_Iniciar);
        pn_Botoes.add(bt_Atualizar);
        pn_Botoes.add(bt_FecharSecundario);
        
        //Botões de radio e suas adições ao ActionListerner, dificuldade inicia selecionada no fácil
        rb_Facil = new JRadioButton("Fácil", true);
        rb_Medio = new JRadioButton("Médio", false);
        rb_Dificil = new JRadioButton("Difícil", false);
        rb_Facil.addActionListener(this);
        rb_Medio.addActionListener(this);
        rb_Dificil.addActionListener(this);
        dificuldade = "facil";
        
        //Grupo de botões para adicionar os Botões de radio, evitando seleções multiplas
        ButtonGroup bg_BotoesDificuldade = new ButtonGroup();        
        bg_BotoesDificuldade.add(rb_Facil);
        bg_BotoesDificuldade.add(rb_Medio);
        bg_BotoesDificuldade.add(rb_Dificil);
        
        //Painel onde será adicionado os botões de dificuldade
        JPanel pn_Dificuldade = new JPanel(new GridLayout(1, 3));
        pn_Dificuldade.setBorder(javax.swing.BorderFactory.createTitledBorder("Dificuldade"));
        pn_Dificuldade.add(rb_Facil);
        pn_Dificuldade.add(rb_Medio);
        pn_Dificuldade.add(rb_Dificil);        
        
        //Botões de radio e suas adições ao ActionListerner
        rb_VsPlay = new JRadioButton("Play Vs Play", true);
        rb_VsMaquina = new JRadioButton("Play Vs Máquina", false);
        rb_VsPlay.addActionListener(this);
        rb_VsMaquina.addActionListener(this);
        
        //Grupo de botões para adicionar os Botões de radio, evitando seleções multiplas
        ButtonGroup bg_BotoesModo = new ButtonGroup();        
        bg_BotoesModo.add(rb_VsPlay);
        bg_BotoesModo.add(rb_VsMaquina);
        
        //Painel onde será adicionado os botões de modo
        JPanel pn_Modo = new JPanel(new GridLayout(1, 2));
        pn_Modo.setBorder(javax.swing.BorderFactory.createTitledBorder("Modo"));
        pn_Modo.add(rb_VsPlay);
        pn_Modo.add(rb_VsMaquina);
        
        //Painel para adicionar os paineis com botões de dificuldade e modo
        JPanel pn_Selecao = new JPanel(new GridLayout(1, 2));
        pn_Selecao.add(pn_Dificuldade);
        pn_Selecao.add(pn_Modo);
        
        //Painel inferior do frame e sua adições
        JPanel pn_Inferior = new JPanel(new GridLayout(4, 1));
        pn_Inferior.add(pn_Selecao);
        pn_Inferior.add(pn_NomeJogadores);
        pn_Inferior.add(pn_Botoes);
        pn_Inferior.add(lb_Desenvolvedor);
        
        //Imagem de logo para adicionar ao centro do frame
        JLabel lb_Imagem = new JLabel(new ImageIcon("pcruzadas.png"));
        
        //Adições ao frame Secundario do jogo
        f_Secundario = new JFrame("Palavras Cruzadas");
        f_Secundario.setLayout(new BorderLayout());
        f_Secundario.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f_Secundario.add(lb_Imagem, BorderLayout.CENTER);
        f_Secundario.add(BorderLayout.PAGE_END, pn_Inferior);
        
        //Empacotando o frame e exibindo, oculta o frame principal
        f_Secundario.pack();
        f_Secundario.setVisible(true);
        f_Principal.setVisible(false);
    }
    //Fim metodo menuJogo
    
    
    
    //Metodo para exibir o painel dos recordes
    public void painelScore(){
        
        //Text Area para adicionar os recordes
        JTextArea ta_Score = new JTextArea("\nJogador\tPontos\tDificuldade\tData\tHora\n\n");
        //String[] para separar os recordes cocatenados com ";"
        String[] recorde = Score.getScore().split(";");        

        //Verifica se existem recordes e adicionam ao text Area, senão adiciona "NÃO HÁ RECORDES"
        if(!recorde[0].equals(""))
            for (String r : recorde)
                ta_Score.setText(ta_Score.getText()+r+"\n");        
        else
            ta_Score.setText("\n\t\tNÃO HÁ RECORDES");
        
        //Desabilita e pinta o textArea para evitar edição e melhorar visualização
        ta_Score.setEnabled(false);
        ta_Score.setBackground(Color.DARK_GRAY);
        
        //Cria uma ScrollPane[Espaço c/ barra de rolagem] para adicionar o textArea
        JScrollPane sp_Score = new JScrollPane(ta_Score);
        sp_Score.setPreferredSize(new Dimension(420, 400));
        
        //Botões e suas add ao ActionListener
        bt_FecharSecundario = new JButton("Voltar");
        bt_FecharSecundario.addActionListener(this);
        bt_DeletaScore = new JButton("Deletar");
        bt_DeletaScore.addActionListener(this);
        
        //Painel de botões e suas adições
        JPanel pn_Botoes = new JPanel(new GridLayout(1, 2));
        pn_Botoes.add(bt_DeletaScore);
        pn_Botoes.add(bt_FecharSecundario);
        
        //Criação do painel inferior e adição do painel botões e label desenvolvedor
        JPanel pn_Inferior = new JPanel(new GridLayout(2, 1));
        pn_Inferior.add(pn_Botoes);
        pn_Inferior.add(lb_Desenvolvedor);
        
        //Adições ao frame Secundario do jogo
        f_Secundario = new JFrame("Recordes");
        f_Secundario.setLayout(new BorderLayout());
        f_Secundario.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f_Secundario.add(BorderLayout.CENTER, sp_Score);
        f_Secundario.add(BorderLayout.SOUTH, pn_Inferior);
        
        //Empacotando o frame e exibindo, oculta o frame principal
        f_Secundario.pack();
        f_Secundario.setVisible(true);
        f_Principal.setVisible(false);
    }
    //Fim metodo painelScore
    
    
    
    //Metodo para exibir o painel de instruções
    public void painelInstrucoes(){
        
        //Text Area para adicionar as instruções
        JTextArea ta_Instrucoes = new JTextArea("\n");
        //String[] para separar as linhas das instruções cocatenados com ";"
        String[] linha = LeitorInstrucoes.getInstrucoes().split(";");
        
        //Percorre toda String e se a linha não for null, adiciona no textArea
        for (String l : linha)            
            if(!l.equals("null"))
                ta_Instrucoes.setText(ta_Instrucoes.getText()+l+"\n");
        
        //Desabilita e pinta o textArea para evitar edição e melhorar visualização
        ta_Instrucoes.setEnabled(false);
        ta_Instrucoes.setBackground(Color.DARK_GRAY);
        
        //Cria uma ScrollPane[Espaço c/ barra de rolagem] para adicionar o textArea
        JScrollPane sp_Score = new JScrollPane(ta_Instrucoes);
        sp_Score.setPreferredSize(new Dimension(420, 400));
        
        //Botão e adição ao actionListener
        bt_FecharSecundario = new JButton("Voltar");
        bt_FecharSecundario.addActionListener(this);
        
        //Criação do painel inferior e adição do botão fechar e label desenvolvedor
        JPanel pn_Inferior = new JPanel(new GridLayout(2, 1));
        pn_Inferior.add(bt_FecharSecundario);
        pn_Inferior.add(lb_Desenvolvedor);        
        
        //Adições ao frame Secundario do jogo
        f_Secundario = new JFrame("Instruções");
        f_Secundario.setLayout(new BorderLayout());
        f_Secundario.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f_Secundario.add(BorderLayout.CENTER, sp_Score);
        f_Secundario.add(BorderLayout.SOUTH, pn_Inferior);
        
        //Empacotando o frame e exibindo, oculta o frame principal
        f_Secundario.pack();
        f_Secundario.setVisible(true);
        f_Principal.setVisible(false);        
    }
    //Fim metodo painelInstrucoes
    
    
    
    //Metodo que constroe exibe o frame com o jogo
    public void inicioJogo(){
        
        //Instancia o jogo para criar os cruzamentos e listar as dicas e palavras
        JogoPCruzadas jogoPCruzadas = new JogoPCruzadas(dificuldade);
        dicas = jogoPCruzadas.getDicas();
        palavras = jogoPCruzadas.getPalavras();               
        
        //Painel para montar a matriz e sua criação
        JPanel pn_Jogo = new JPanel(new GridLayout(JogoPCruzadas.MAX_LINHA, JogoPCruzadas.MAX_COLUNA));
        cruzadas = jogoPCruzadas.constroeCruzada();
        
        //Inicio do for
        //Preenche o painel com a matriz e os botões identificadores
        for(int linha = 0, i = 0; linha < JogoPCruzadas.MAX_LINHA; linha++)
            for(int coluna = 0; coluna < JogoPCruzadas.MAX_COLUNA; coluna++){
                
                //Verifica se no indice possui char '1' para adicionar um botão
                if(cruzadas[linha][coluna] == 1){
                    //Pega as coordenadas do botao, e adiciona o botao na matriz do painel
                    cLinhaBotao[i] = linha;
                    cColunaBotao[i] = coluna;
                    bt_SelecionaPalavra[i] = new JButton(Integer.toString(i+1));
                    bt_SelecionaPalavra[i].addActionListener(this);
                    //Adiciona a dica ao botão para ser exibida quando o cursor do mause estiver sobre o mesmo
                    bt_SelecionaPalavra[i].setToolTipText((String) dicas.get(i));
                    pn_Jogo.add(bt_SelecionaPalavra[i]);
                    i++;
                    continue;
                }
                
                //Se o espaço não é botão nem vazio, adiciona a cruzada textField, senão deixa o indice vazio
                if(cruzadas[linha][coluna] != 0 && cruzadas[linha][coluna] != 1){
                    tf_Jogo[linha][coluna] = new JTextField();
                    tf_Jogo[linha][coluna].setEnabled(false);
                    pn_Jogo.add(tf_Jogo[linha][coluna]);
                }else
                    pn_Jogo.add(new JPanel());
            }
        //Fim do for
        
        //Botões e suas add ao actionListener
        bt_Finalizar = new JButton("Finalizar");
        bt_Finalizar.addActionListener(this);
        bt_FecharJogo = new JButton("Voltar");
        bt_FecharJogo.addActionListener(this);
        
        //Painel dos botões
        JPanel pn_Botoes = new JPanel(new GridLayout(1, 2));
        pn_Botoes.add(bt_Finalizar);
        pn_Botoes.add(bt_FecharJogo);
        
        //Painel inferior e suas adições
        JPanel pn_Inferior = new JPanel(new GridLayout(3, 1));
        lb_ProxJogada = new JLabel(JOGADOR[indiceJogador].getNome(), (int) CENTER_ALIGNMENT);
        lb_ProxJogada.setBorder(javax.swing.BorderFactory.createTitledBorder("Quem joga é:"));
        pn_Inferior.add(lb_ProxJogada);
        pn_Inferior.add(pn_Botoes);
        pn_Inferior.add(lb_Desenvolvedor);
        
        //Painel superior e suas adições
        JPanel pn_Superior = new JPanel(new GridLayout(2, 1));
        JLabel lb_Informacao = new JLabel("PALAVRAS COM ACENTO DIFEREM", (int) CENTER_ALIGNMENT);
        JLabel lb_Informacao2 = new JLabel("PASSE O MAUSE SOBRE O NÚMERO PARA OBTER A DICA", (int) CENTER_ALIGNMENT);
        pn_Superior.add(lb_Informacao);
        pn_Superior.add(lb_Informacao2);
        pn_Superior.setBorder(javax.swing.BorderFactory.createTitledBorder("ATENÇÃO:"));
        
        //Fecha o frame secundario anterior e cria um novo para o jogo        
        f_Secundario.dispose();
        f_Secundario = new JFrame("Palavras Cruzadas");
        f_Secundario.setLayout(new BorderLayout());
        f_Secundario.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f_Secundario.add(BorderLayout.NORTH, pn_Superior);
        f_Secundario.add(BorderLayout.CENTER, pn_Jogo);
        f_Secundario.add(BorderLayout.SOUTH, pn_Inferior);
        
        //Empacota o frame e exibi
        f_Secundario.pack();
        f_Secundario.setVisible(true);        
    }
    //Fim metodo inicioJogo
    
    
    
    /**
     * Metodo realiza as funções de ação do botão iniciar, verifica se o 
     * preenchimento do menuJogo está correto, em caso afirmativo inicializa
     * os jogadores e inicia o jogo, senão informa que faltam dados a serem 
     * preenchidos
     */
    public void funcaoBotaoIniciar(){
        
        //Inicio do if/else
        //Verifica se os campos estão devidamente preenchidos
        if/**/((!tf_Jogador1.getText().equals("") && !tf_Jogador2.getText().equals("") && rb_VsPlay.isSelected())
                || (!tf_Jogador1.getText().equals("") && rb_VsMaquina.isSelected()))/**/{

            //Criação dos jogadores
            if(rb_VsMaquina.isSelected()){
                JOGADOR[0] = new JogadorReal(tf_Jogador1.getText(), dificuldade);
                JOGADOR[1] = new JogadorVirtual(dificuldade);
            }else{
                JOGADOR[0] = new JogadorReal(tf_Jogador1.getText(), dificuldade);
                JOGADOR[1] = new JogadorReal(tf_Jogador2.getText(), dificuldade);
            }
            
            //inicia o jogo
            inicioJogo();

        }else{
            //Se tiver campos faltando, desabilita o botão iniciare informar para preencher os campos
            bt_Iniciar.setEnabled(false);
            JOptionPane.showMessageDialog(null, "Preencha os dados corretamente", "ATENÇÃO", JOptionPane.ERROR_MESSAGE);
        }
        //Fim do if/else
    }
    //Fim metodo funcaoBotaoIniciar
    
    
    
    //Metodo realiza as funções de ação dos botões fechar ou voltar, presente nos frames
    public void funcaoBotaoFechar(){
        
        //Fecha frame atual e exibe o principal
        f_Secundario.dispose();
        f_Principal.setVisible(true);
    }
    //Fim metodo funcaoBotaoFechar
    
    
    
    //Metodo realiza as funções de ação do botão finalizar jogo, quando o mesmo estiver terminado
    public void funcaoBotaoFinalizar(){
        
        //Supõe inicialmente que o jogo realmente terminou
        boolean teste = true;
        
        //Verifica se a matriz está completamente preenchida(Se o jogo terminou)
        for(int linha = 0; linha < JogoPCruzadas.MAX_LINHA; linha++)
            for(int coluna = 0; coluna < JogoPCruzadas.MAX_COLUNA; coluna++)
                
                //Se encontrar algum campo que não está preenchido, para a operação para informar que não terminou
                if/**/(cruzadas[linha][coluna] != 1 && cruzadas[linha][coluna] != 0 && 
                    !tf_Jogo[linha][coluna].getText().equals(Character.toString(cruzadas[linha][coluna])))/**/{
                    teste = false;
                    break;
                }
        
        //Se encontrou campo sem preencher, informa que não terminou, senão, finaliza o jogo e salva os dados
        if(teste == false)
            JOptionPane.showMessageDialog(this, "JOGO AINDA NÃO TERMINOU");
        else{
            JOGADOR[0].fimJogador(teste);
            JOGADOR[1].fimJogador(teste);
            funcaoBotaoFechar();
            JOptionPane.showMessageDialog(this, "OBRIGADO POR JOGAR");
        }
    }
    //Fim metodo funcaoBotaoFinalizar
    
    
    
    /**
     * Metodo realiza as funções dos botões da matriz
     * 
     * @param i indice do botão clicado passado por paramentro
     */
    public void funcaoBotoesMatriz(int i){
        
        //Variaveis locais
        Random r = new Random();//Sorteio utilizado nas dificuldades(medio, dificil), para a dica do JVirtual
        String palavra;//String recebe a palavra do array para sortear o indice de um char da string
        int indice;//Indice = indice do char em String palavra, para a dica do JVirtual, se atender a dificuldade escolhida
        
        //Tratamento utilizado para quando o botão cancelar do dialogo for selecionado
        try{
            palpite = JOptionPane.showInputDialog(this, "Digite o chute:", "Escolheu a dica "+(i+1), JOptionPane.QUESTION_MESSAGE).toUpperCase();
        }catch(NullPointerException e){
            palpite = "";
        }
        
        //Testa se o palpite está correto
        if(testaPalpite(palpite, i)){
            
            //Inicio do if/else
            //Verifica se o prox jogador é uma instancia de JVirtual
            if(JOGADOR[indiceJogador] instanceof JogadorVirtual){
                
                //Variaveis locais
                int b;//indice do botão escolhido para o palpite
                boolean teste = true;//teste se todas palavras já foram desvendadas
                
                //Inicio do for
                //Procura uma palavra que não foi desvendada através do seu respectivo botao
                for(b = 0; bt_SelecionaPalavra[b] != null; b++)
                    
                    //Se o botão está ativo, da o palpite nessa cruzada, senão informa que não existe cruzada até prox laço
                    if(bt_SelecionaPalavra[b].isEnabled()){
                        
                        //Pega as dica da cruzada selecionada para o JVirtual e utiliza se a dificuldade for (medio, dificil)
                        palavra = palavras.get(b).toString();
                        indice = r.nextInt(palavra.length());
                        palpite = ((JogadorVirtual)JOGADOR[indiceJogador]).palpite(Character.toString(palavra.charAt(indice))+indice, palavra.length());
                        
                        testaPalpite(palpite, b);
                        teste = true;
                        break;
                    
                    }else
                        teste = false;
                //Fim do for
                
                //Verifica se realmente não existem mais cruzadas e pede ao jogador para finalizar o jogo
                if(teste == false)
                    JOptionPane.showMessageDialog(this, "CLIQUE EM FINALIZAR", "O JOGO TERMINOU", JOptionPane.INFORMATION_MESSAGE);
            }                
            //Fim do if/else
        
        //Se o palpite não está correto, verifica se o proxJogador é instancia de JVirtual e da o palpite na mesma cruzada
        }else
            
            //Inicio do if
            if(JOGADOR[indiceJogador] instanceof JogadorVirtual){
                
                //Pega as dica da cruzada selecionada para o JVirtual e utiliza se a dificuldade for (medio, dificil)
                palavra = palavras.get(i).toString();
                indice = r.nextInt(palavra.length());
                palpite = ((JogadorVirtual)JOGADOR[indiceJogador]).palpite(Character.toString(palavra.charAt(indice))+indice, palavra.length());
                
                if(palpite != null)
                    testaPalpite(palpite, i);
                else
                    JOptionPane.showMessageDialog(this, "PASSOU A VEZ", "Jogador: "+JOGADOR[indiceJogador].getNome(), JOptionPane.INFORMATION_MESSAGE);
            }
            //Fim do if
    }
    //Fim metodo funcaoBotoesMatriz
    
    
    
    /**
     * Identifica qual jogador é o proximo e soma ao Score do jogador anterior
     * caso o mesmo tenha pontuado
     * 
     * @param pontuacaoJogadorAnterior 0 se o jogador não pontuou e 50 se pontuou
     * @return 0 para vez do JOGADOR[0] e 1 para vez do JOGADOR[1]
     */
    public int pegaProxESalvaScore(int pontuacaoJogadorAnterior){
        
        //O JOGADOR[0] joga das rodadas pares e o JOGADOR[1] nas impares, numeroJogadas inicia com 1
        if(numeroJogadas%2 == 0.0){
            JOGADOR[1].setScore(pontuacaoJogadorAnterior);
            numeroJogadas+=1;
            lb_ProxJogada.setText(JOGADOR[0].getNome());
            return 0;
        }else{
            JOGADOR[0].setScore(pontuacaoJogadorAnterior);
            numeroJogadas+=1;
            lb_ProxJogada.setText(JOGADOR[1].getNome());
            return 1;
        }
    }
    //Fim metodo pegaProxESalvaScore
    
    
    
    /**
     * Metodo testa o palpite e se caso for o correto, preenche a matriz, adiciona
     * a pontuação e passa a vez ao prox jogador. Senão, se passar a vez ou erra
     * o palpite, não recebe pontuação e passa a vez
     * 
     * @param chute String com o palpite para verificar
     * @param i identificador do botão e sua respectiva palavra
     * @return true se acertou, ou false se errou ou passou a vez
     */
    public boolean testaPalpite(String chute, int i){
        
        //Verifica se passou a vez
        if(chute.equals("")){
            JOptionPane.showMessageDialog(this, "PASSOU A VEZ", "Jogador: "+JOGADOR[indiceJogador].getNome(), JOptionPane.INFORMATION_MESSAGE);
            indiceJogador = pegaProxESalvaScore(0);
            JOptionPane.showMessageDialog(this, JOGADOR[indiceJogador].getNome(), "Agora é a vez de:", JOptionPane.INFORMATION_MESSAGE);
            return false;
        }
        
        //Inicio do if/else
        //Verifica se o palpite está correto e preenche na matriz
        if(chute.equals(palavras.get(i))){
            
            //Informa que jogador atual acertou e oculta o botão para não ser selecionado novamente
            JOptionPane.showMessageDialog(null, chute, "Jogador "+JOGADOR[indiceJogador].getNome()+" acertou", JOptionPane.INFORMATION_MESSAGE);
            bt_SelecionaPalavra[i].setEnabled(false);
            
            //Verifica se a palavra é da vertical ou horizontal para o preenchimento
            if(i == 0)
                for(int linha = cLinhaBotao[i], coluna = cColunaBotao[i], temp = 0; temp <= chute.length(); temp++, linha++){
                    if(cruzadas[linha][coluna] != 1 && cruzadas[linha][coluna] != 0)
                        tf_Jogo[linha][coluna].setText(Character.toString(cruzadas[linha][coluna]));
                }
            else
                for(int linha = cLinhaBotao[i], coluna = cColunaBotao[i], temp = 0; temp <= chute.length(); temp++, coluna++){
                    if(cruzadas[linha][coluna] != 1 && cruzadas[linha][coluna] != 0)
                        tf_Jogo[linha][coluna].setText(Character.toString(cruzadas[linha][coluna]));
                }
            
            //Soma +50 na pontuação, passa a vez e retorna que "acertou"
            indiceJogador = pegaProxESalvaScore(50);
            JOptionPane.showMessageDialog(this, JOGADOR[indiceJogador].getNome(), "Agora é a vez de:", JOptionPane.INFORMATION_MESSAGE);
            return true;
            
        }else{
            //Informa que o jogador errou, passa a vez e retorna que "errou"
            JOptionPane.showMessageDialog(null, chute, "Jogador "+JOGADOR[indiceJogador].getNome()+" errou", JOptionPane.ERROR_MESSAGE);
            indiceJogador = pegaProxESalvaScore(0);
            JOptionPane.showMessageDialog(this, JOGADOR[indiceJogador].getNome(), "Agora é a vez de:", JOptionPane.INFORMATION_MESSAGE);
            return false;
        }
        //Fim do if/else
    }
    //Fim metodo testaPalpite
    
    
    
    /**
     * Metodo das ações dos botões, incluindo os da matriz de cruzadinha
     * 
     * @param evt Informa qual botão foi clicado
     */
    @Override
    public void actionPerformed(ActionEvent evt){
        
        //Ações dos botões de dificuldade
        if(evt.getSource() == rb_Facil)
            dificuldade = "facil";
        else if(evt.getSource() == rb_Medio)
            dificuldade = "medio";
        else if(evt.getSource() == rb_Dificil)
            dificuldade = "dificil";
            
        //Ações dos botões de modo, oculta campos de acordo com a seleção
        else if(evt.getSource() == rb_VsPlay){
            tf_Jogador1.setEnabled(true);
            tf_Jogador2.setEnabled(true);
        }else if(evt.getSource() == rb_VsMaquina){
            tf_Jogador1.setEnabled(true);
            tf_Jogador2.setEnabled(false);
            tf_Jogador2.setText("");
            
        //Ação do botão Atualizar, verifica se o preenchimento está correto e habilita o botão iniciar
        }else if(evt.getSource() == bt_Atualizar){
            if(!tf_Jogador1.getText().equals("") && !tf_Jogador2.getText().equals("")){
                bt_Iniciar.setEnabled(true);
            }else if(!tf_Jogador1.getText().equals("") && rb_VsMaquina.isSelected()){
                bt_Iniciar.setEnabled(true);
            }else
                bt_Iniciar.setEnabled(false);
            
        //Ações dos botões
        }else if(evt.getSource() == bt_Jogar)
            menuJogo();//Abre o menu do jogo
        else if (evt.getSource() == bt_Iniciar)
            funcaoBotaoIniciar();//Executa a ação do botão iniciar
        else if(evt.getSource() == bt_Score)
            painelScore();//Abre o painel de recordes
        else if(evt.getSource() == bt_DeletaScore)
            Score.deleteScore();//Deleta os recordes
        else if(evt.getSource() == bt_Instrucoes)
            painelInstrucoes();//Abre o painel de instruções do jogo
        else if(evt.getSource() == bt_FecharPrincipal)
            System.exit(0);//Fecha o jogo completamente
        else if(evt.getSource() == bt_FecharSecundario)
            funcaoBotaoFechar();//Fecha janela atual e exibi a principal
            
        //Ação do botão presente quando o jogo está em operação, aciona-lo finaliza o jogo perdendo os dados
        else if(evt.getSource() == bt_FecharJogo){
            JOGADOR[0].fimJogador(false);
            JOGADOR[1].fimJogador(false);
            funcaoBotaoFechar();
            
        //Ação do botão presente quando o jogo está em operação, aciona-lo finaliza o jogo se o mesmo já estiver terminado
        }else if(evt.getSource() == bt_Finalizar)
            funcaoBotaoFinalizar();
        
        /**
         * Ação dos botões presentes na matriz do jogo, quando identifica o 
         * botão acionado, envia o indice do mesmo por parametro para o metodo
         * de suas funções
        */
        else
            for (int i = 0, j; i < bt_SelecionaPalavra.length; i++)
                if (evt.getSource() == bt_SelecionaPalavra[i])
                    funcaoBotoesMatriz(i);
    }
    //Fim metodo actionPerformed
    
    
    
    //Main
    public static void main(String[] args){
        InterfaceGrafica interfaceGrafica = new InterfaceGrafica();
    }
}
