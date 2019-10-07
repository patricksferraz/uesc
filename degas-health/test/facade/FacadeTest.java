package facade;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class FacadeTest {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}
        
        
	@Test
	public void testFacade() {
            Facade facade = new Facade();

            String res;
            
            
//            novo m�dico: Nome, CRM, Sexo, Nacionalidade, Data Nasc., Data Admiss., Data Formatura



            res = facade.novoMedico("Nardelle Moraes","M","97719","Brasil","26/08/1977","29/06/2012","28/01/2007");
            assertEquals("Medico inserido!", res);

            res = facade.novoMedico("Rudine%  Rodrigues","M","46193","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoMedico("Rudinei  R#drigues","M","46193","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoMedico("Rudinei  Rodrigues","M","46193","Br@sil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoMedico("Rudine%  Rodrigues","M","46193","Br@sil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoMedico("Rudinei  R#drigues","M","46193","Br@sil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoMedico("Rudinei  R@drig#es","M","46193","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoMedico("Rudinei  Rodrigues","M","46193","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("Medico inserido!", res);

            res = facade.novoMedico("Rudinei  Rodrigues","M","46193","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! CRM Já existente!", res);

            res = facade.novoMedico("Ailton  Carvalho","M","9614","Brasil","26/07/1970","04/10/1999","02/11/1995");
            assertEquals("Medico inserido!", res);

            res = facade.novoMedico("Tarcila do Amaral","F","9614","Brasil","26/07/1970","04/10/1999","02/11/1995");
            assertEquals("ERRO! CRM Já existente!", res);

            res = facade.novoMedico("Larissa Pereira","F","36311","Brasil","22/01/1977","13/08/2005","07/11/1999");
            assertEquals("Medico inserido!", res);

            /*-------------------------Teste ap�s persist�ncia!------------------------------*/

            facade = new Facade();

            res = facade.novoMedico("Jonelice  Pinto","F","3566","Portugal","07/02/1989","28/9/2017","22/12/2012");
            assertEquals("Medico inserido!", res);

            res = facade.novoMedico("Alvaro Degas","M","3566","Brasil","05/06/1989","28/09/2017","22/12/2012");
            assertEquals("ERRO! CRM Já existente!", res);

            res = facade.novoMedico("Jaqueline  das Neves","F","89673","Brasil","12/02/1984","31/04/2013","05/07/2011");
            assertEquals("ERRO! Data Inválida!", res);

            res = facade.novoMedico("Jaqueline  das Neves","F","89673","Brasil","12/02/1984","30/2/2013","05/07/2011");
            assertEquals("ERRO! Data Inválida!", res);

            res = facade.novoMedico("Jaqueline  das Neves","F","89673","Brasil","12/02/1984","31/3/2011","05/07/2013");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.novoMedico("Jaqueline  das Neves","F","89673","Brasil","12/02/1984","31/05/2013","05/07/2011");
            assertEquals("Medico inserido!", res);

            res = facade.encontraMedico("Nardelle Moraes");
            assertEquals("Nardelle Moraes%M%97719%Brasil%26/08/1977%29/06/2012%28/01/2007", res);

            res = facade.encontraMedico("36311");
            assertEquals("Larissa Pereira%F%36311%Brasil%22/01/1977%13/08/2005%07/11/1999", res);

//            /*-----------------Mais testes ap�s nova persist�ncia-----------------------------*/
//
            facade = new Facade();

            res = facade.alteraMedico("97719","Nome", "Jose Ferreira");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("97719");
            assertEquals("Jose Ferreira%M%97719%Brasil%26/08/1977%29/06/2012%28/01/2007", res);

            res = facade.alteraMedico("46193","Sexo", "F");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("46193");
            assertEquals("Rudinei  Rodrigues%F%46193%Brasil%28/05/1962%22/07/1992%18/11/1988", res);

            res = facade.alteraMedico("9614","Nacionalidade", "Italia");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("9614");
            assertEquals("Ailton  Carvalho%M%9614%Italia%26/07/1970%04/10/1999%02/11/1995", res);

            res = facade.alteraMedico("36311","DtNasc", "31/01/1971");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("36311");
            assertEquals("Larissa Pereira%F%36311%Brasil%31/01/1971%13/08/2005%07/11/1999", res);

            res = facade.alteraMedico("3566","DtAdmiss", "19/07/2002");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraMedico("3566","DtAdmiss", "19/07/2015");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("3566");
            assertEquals("Jonelice  Pinto%F%3566%Portugal%07/02/1989%19/07/2015%22/12/2012", res);

            res = facade.alteraMedico("89673","DtFormatura", "30/03/2014");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraMedico("89673","DtFormatura", "30/03/2010");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraMedico("89673");
            assertEquals("Jaqueline  das Neves%F%89673%Brasil%12/02/1984%31/05/2013%30/03/2010", res);
//
//
//		/*---------------------------------------------------------------------------------------*/
//
//
//             //COREN -> Conselho Regional de Enfermagem
//             //novoEnfermeiro: Nome, Sexo, COREN, Nacionalidade, Data Nasc., Data Admiss., Data Formatura
//
//
            res = facade.novoEnfermeiro("Amadildo Maldonado","M","197719","Brasil","24/08/1969","29/06/2017","28/01/2016");
            assertEquals("Enfermeiro inserido!", res);

            res = facade.novoEnfermeiro("Bruna%  Surfer","F","151329","Brasil","18/04/1972","22/07/1999","18/11/1990");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoEnfermeiro("Carine  R#drigues","F","151329","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoEnfermeiro("Doravante  Alavante","F","151329","Br@sil","24/01/1982","22/7/2012","18/11/2000");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoEnfermeiro("Edilen%e  dos Santos","F","151329","Br@sil","03/12/1991","22/1/2018","18/11/2017");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoEnfermeiro("Fábio  J#nior","M","151329","Br@sil","28/05/1962","23/03/1992","28/12/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoEnfermeiro("Geremilda  L@jot#","F","151329","Brasil","18/05/1962","22/07/1992","18/11/1988");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoEnfermeiro("Horáclides da Hora Certa","M","151329","Brasil","28/05/1962","22/07/1992","18/11/1988");
            assertEquals("Enfermeiro inserido!", res);

            res = facade.novoEnfermeiro("Ítalo  Pinto Vloger","M","151329","Brasil","28/05/1962","22/7/1992","18/11/1988");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoEnfermeiro("Jalapeno Kino","M","19614","Brasil","26/07/1970","04/10/1999","02/11/1995");
            assertEquals("Enfermeiro inserido!", res);

            res = facade.novoEnfermeiro("Larissa de Las Dolores","F","19614","Brasil","26/07/1970","04/10/1999","02/11/1995");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoEnfermeiro("Maria do Bairro","F","136311","Brasil","22/01/1977","13/08/2005","07/11/1999");
            assertEquals("Enfermeiro inserido!", res);
//
//            /*-------------------------Teste ap�s persist�ncia!------------------------------*/
//
            facade = new Facade();

            res = facade.novoEnfermeiro("Alfarroba Cacau","F","1566","Portugal","07/02/1989","28/09/2017","22/12/2012");
            assertEquals("Enfermeiro inserido!", res);

            res = facade.novoEnfermeiro("Olivia Oliveira das Olivas","M","1566","Brasil","05/06/1989","28/09/2017","22/12/2012");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoEnfermeiro("John  de Las Nieves","M","189673","Brasil","12/02/1984","31/04/2013","05/07/2011");
            assertEquals("ERRO! Data Inválida!", res);

            res = facade.novoEnfermeiro("John  Gothic Ranger","M","189673","Brasil","12/02/1984","30/2/2013","05/07/2011");
            assertEquals("ERRO! Data Inválida!", res);

            res = facade.novoEnfermeiro("Jaquelina  das Neves","F","189673","Brasil","12/02/1984","31/3/2011","05/07/2013");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.novoEnfermeiro("Bátima da Silva Sauro","F","189673","Brasil","12/02/1984","31/05/2013","05/07/2011");
            assertEquals("Enfermeiro inserido!", res);

            res = facade.encontraEnfermeiro("Amadildo Maldonado");
            assertEquals("Amadildo Maldonado%M%197719%Brasil%24/08/1969%29/06/2017%28/01/2016", res);

            res = facade.encontraEnfermeiro("151329");
            assertEquals("Horáclides da Hora Certa%M%151329%Brasil%28/05/1962%22/07/1992%18/11/1988", res);
//
//            /*-----------------Mais testes ap�s nova persist�ncia-----------------------------*/
//
            facade = new Facade();

            res = facade.alteraEnfermeiro("197719","Nome", "Arminho Amando Amador Amor Divino");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("197719");
            assertEquals("Arminho Amando Amador Amor Divino%M%197719%Brasil%24/08/1969%29/06/2017%28/01/2016", res);

            res = facade.alteraEnfermeiro("151329","Sexo", "F");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("151329");
            assertEquals("Horáclides da Hora Certa%F%151329%Brasil%28/05/1962%22/07/1992%18/11/1988", res);

            res = facade.alteraEnfermeiro("19614","Nacionalidade", "Italia");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("19614");
            assertEquals("Jalapeno Kino%M%19614%Italia%26/07/1970%04/10/1999%02/11/1995", res);

            res = facade.alteraEnfermeiro("136311","DtNasc", "31/01/1971");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("136311");
            assertEquals("Maria do Bairro%F%136311%Brasil%31/01/1971%13/08/2005%07/11/1999", res);

            res = facade.alteraEnfermeiro("1566","DtAdmiss", "19/02/2002");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraEnfermeiro("1566","DtAdmiss", "19/07/2015");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("1566");
            assertEquals("Alfarroba Cacau%F%1566%Portugal%07/02/1989%19/07/2015%22/12/2012", res);

            res = facade.alteraEnfermeiro("189673","DtFormatura", "30/03/2014");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraEnfermeiro("189673","DtFormatura", "30/03/2010");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraEnfermeiro("189673");
            assertEquals("Bátima da Silva Sauro%F%189673%Brasil%12/02/1984%31/05/2013%30/03/2010", res);
//
//            //COREN -> Conselho Regional de Enfermagem. O mesmo serve para Auxiliar de Enfermagem ou T�cnico de Enfermagem.
//            //novoAuxiliar: Nome, Sexo, COREN, Nacionalidade, Data Nasc., Data Admiss., Data Formatura
//
//
            res = facade.novoAuxiliar("Augusta Rua","M","297719","Brasil","24/02/1969","29/12/2016","28/06/2015");
            assertEquals("Auxiliar/Técnico inserido!", res);

            res = facade.novoAuxiliar("Bárbara%  Leonel","F","251329","Brasil","18/10/1971","22/01/1999","18/05/1990");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoAuxiliar("Cêcharpe L#dligues","M","251329","Brasil","28/11/1961","22/01/1992","18/05/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoAuxiliar("Dalva Branquinha Alves","F","251329","Br@sil","24/06/1981","22/01/2012","18/05/2000");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoAuxiliar("Elie%e  dos Ponteiros","F","251329","Br@sil","03/06/1991","22/06/2017","18/05/2017");
            assertEquals("ERRO! Caracter '%' Invalido!", res);

            res = facade.novoAuxiliar("Fabíola do C#menor","M","251329","Br@sil","28/11/1961","23/09/1991","28/08/1988");
            assertEquals("ERRO! Caracter '#' Invalido!", res);

            res = facade.novoAuxiliar("Galinda C@xaqt#","F","251329","Brasil","18/11/1962","22/01/1992","18/05/1988");
            assertEquals("ERRO! Caracter '@' Invalido!", res);

            res = facade.novoAuxiliar("Hermitío da Gruta Longe","M","251329","Brasil","28/11/1962","22/01/1992","18/05/1988");
            assertEquals("Auxiliar/Técnico inserido!", res);

            res = facade.novoAuxiliar("Ivan da Van Dutch","M","251329","Brasil","28/11/1961","22/01/1992","18/10/1988");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoAuxiliar("Jileno da Lamina Cega","M","29614","Brasil","26/01/1970","04/04/1999","02/05/1995");
            assertEquals("Auxiliar/Técnico inserido!", res);

            res = facade.novoAuxiliar("Lucas Bolseiro","M","29614","Brasil","26/03/1970","04/02/1999","02/10/1995");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoAuxiliar("Maria do Bairro","F","236311","Brasil","22/07/1976","13/08/2005","07/05/1999");
            assertEquals("Auxiliar/Técnico inserido!", res);
//
//            /*-------------------------Teste ap�s persist�ncia!------------------------------*/
//
            facade = new Facade();

            res = facade.novoAuxiliar("Naiara Cinquenta","F","21566","Tchéquia","07/10/1988","28/09/2016","22/06/2012");
            assertEquals("Auxiliar/Técnico inserido!", res);

            res = facade.novoAuxiliar("Olimpo Luz do Panteão Divino ","M","21566","Brasil","05/12/1989","28/03/2017","22/06/2012");
            assertEquals("ERRO! COREN Já existente!", res);

            res = facade.novoAuxiliar("Pablo Bardo da Sofrência Boêmio","M","289673","Brasil","12/10/1984","32/10/2013","05/01/2011"); 
            assertEquals("ERRO! Data Inválida!", res); 

            res = facade.novoAuxiliar("Quincas Borba","M","289673","Brasil","12/10/1983","32/10/2012","05/01/2011");
            assertEquals("ERRO! Data Inválida!", res);

            res = facade.novoAuxiliar("Rubens Paiva","M","289673","Brasil","12/02/1984","31/3/2011","05/07/2013");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.novoAuxiliar("Sábado de Sol Silva","M","289673","Brasil","12/08/1984","30/11/2013","05/01/2011");
            assertEquals("Auxiliar/Técnico inserido!", res);

            res = facade.encontraAuxiliar("Augusta Rua");
            assertEquals("Augusta Rua%M%297719%Brasil%24/02/1969%29/12/2016%28/06/2015", res);

            res = facade.encontraAuxiliar("251329");
            assertEquals("Hermitío da Gruta Longe%M%251329%Brasil%28/11/1962%22/01/1992%18/05/1988", res);
//
//            /*-----------------Mais testes ap�s nova persist�ncia-----------------------------*/
//
            facade = new Facade();

            res = facade.alteraAuxiliar("297719","Nome", "Arsenio Pereira da Produção Eficaz");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("297719");
            assertEquals("Arsenio Pereira da Produção Eficaz%M%297719%Brasil%24/02/1969%29/12/2016%28/06/2015", res);

            res = facade.alteraAuxiliar("251329","Sexo", "F");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("251329");
            assertEquals("Hermitío da Gruta Longe%F%251329%Brasil%28/11/1962%22/01/1992%18/05/1988", res);

            res = facade.alteraAuxiliar("29614","Nacionalidade", "Argentina");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("29614");
            assertEquals("Jileno da Lamina Cega%M%29614%Argentina%26/01/1970%04/04/1999%02/05/1995", res);

            res = facade.alteraAuxiliar("236311","DtNasc", "31/01/1971");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("236311");
            assertEquals("Maria do Bairro%F%236311%Brasil%31/01/1971%13/08/2005%07/05/1999", res);

            res = facade.alteraAuxiliar("21566","DtAdmiss", "19/02/2002");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraAuxiliar("21566","DtAdmiss", "19/07/2015");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("21566");
            assertEquals("Naiara Cinquenta%F%21566%Tchéquia%07/10/1988%19/07/2015%22/06/2012", res);

            res = facade.alteraAuxiliar("289673","DtFormatura", "30/03/2014");
            assertEquals("ERRO! Inconsistencia de datas: Formatura posterior a admissão!", res);

            res = facade.alteraAuxiliar("289673","DtFormatura", "30/03/2010");
            assertEquals("Alteracao executada com sucesso!", res);
            res = facade.encontraAuxiliar("289673");
            assertEquals("Sábado de Sol Silva%M%289673%Brasil%12/08/1984%30/11/2013%30/03/2010", res);
//
///*-------------------------Procedimentos --------------------------------------------*/
//
//            // Procdimento: Codigo, Descri��o, Custo
            facade = new Facade();
            
            res = facade.novoProcedimento("763236","Ponte de Safena","50000");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("763236","Transplante Coração","90000");
            assertEquals("Código de Procedimento Ja Cadastrado", res);
            res = facade.novoProcedimento("377523","Ponte de Safena","90000");
            assertEquals("Descrição de Procedimento Ja Cadastrado", res);
            res = facade.novoProcedimento("377523","Transplante Coração","90000");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("404482","Redução de Fratura","2000.0");
            assertEquals("Erro: valor de custo inválido", res);
            res = facade.novoProcedimento("404482","Redução de Fratura","R2000");
            assertEquals("Erro: valor de custo inválido", res);
            res = facade.novoProcedimento("404482","Redução de Fratura","R$2000");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("894275","Amputação de Membro","$15000,0");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("839530","Curativo","50");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("200752","Nebulização","100");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.novoProcedimento("886244","Cateterismo","10000");
            assertEquals("Procedimento Incluido com Sucesso", res);

            res = facade.encontraProcedimento("404482");
            assertEquals("404482%Redução de Fratura%2000", res);

            res = facade.encontraProcedimento("Cateterismo");
            assertEquals("886244%Cateterismo%10000", res);

            res = facade.encontraProcedimento("12345");
            assertEquals("Procedimento não cadastrado", res);

            res = facade.encontraProcedimento("Obturação");
            assertEquals("Procedimento não cadastrado", res);

            res = facade.alteraProcedimento("894275", "Valor", "12000");
            assertEquals("Procedimento alterado com sucesso", res);

            res = facade.alteraProcedimento("200752", "Descricao", "Respiração Auxiliada");
            assertEquals("Procedimento alterado com sucesso", res);
//
///*-----------------------------Para verificar a persist�ncia ---------------*/		
//
            facade = new Facade();

            res = facade.encontraProcedimento("404482");
            assertEquals("404482%Redução de Fratura%2000", res);

            res = facade.encontraProcedimento("Cateterismo");
            assertEquals("886244%Cateterismo%10000", res);

            res = facade.encontraProcedimento("12345");
            assertEquals("Procedimento não cadastrado", res);
//
///* ------------------ Especialidades M�dicas -----------------------*/
            // Especialidade: c�digo, descri��o
            res = facade.novaEspecialidade("594","Ginecologia");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("594","Urologia");
            assertEquals("Especialidade já cadastrada", res);
            res = facade.novaEspecialidade("166","Urologia");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("531","Ginecologia");
            assertEquals("Especialidade já cadastrada", res);
            res = facade.novaEspecialidade("531","Cardiologia");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("764","Cirurgia Cardíaca");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("251","Ortopedia");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("316","Cirurgia Ortopédica");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.novaEspecialidade("465","Clínica Geral");
            assertEquals("Especialidade Registrada com sucesso", res);

            res = facade.encontraEspecialidade("465");
            assertEquals("465%Clínica Geral", res);

            res = facade.encontraEspecialidade("Cardiologia");
            assertEquals("531%Cardiologia", res);
//
///*---------------------Equipamentos ----------------------------------------------------*/
//            //equipamento: codigo, descricao, valor
            res = facade.novoEquipamento("912","Mesa de Cirurgia","35000");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("885","Maca","4000");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("188","Cadeira","500");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("358","Mesa de Trabalho","800");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("685","Raio X","45000");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("206","Ultrassom","30000");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.novoEquipamento("845","Tomógrafo","800000");
            assertEquals("Equipamento cadastrado com sucesso", res);

            res = facade.tombaEquipamento("912", "MC001");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("912", "MC002");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("912", "MC002");
            assertEquals("Erro: Tombo já existente", res);

            res = facade.tombaEquipamento("912", "MC003");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("885", "MCA001");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("885", "MCA002");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("885", "MCA003");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("885", "MCA004");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("885", "MCA005");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD001");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD002");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD003");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD004");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD005");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD006");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("188", "CAD007");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("358", "MST001");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("358", "MST002");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("358", "MST003");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("358", "MST004");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("685", "RX01");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("685", "RX02");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("206", "US01");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("206", "US02");
            assertEquals("Equipamento tombado com sucesso", res);

            res = facade.tombaEquipamento("845", "TM02");
            assertEquals("Equipamento tombado com sucesso", res);

//            /*-------------------Materiais -----------------------------*/

            res = facade.novoMaterial("2415","Fio de Sutura","2");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("3314","Gaze","2");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("9622","Esparadrapo","3");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("1881","Gesso","5");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("5796","Parafuso de Platina","150");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("4404","Placa de Platina","500");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("5927","Stinter cardíaco","500");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("8996","Antisseptico","15");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("7278","Broncodilatador","20");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("1110","Anestesia Geral","800");
            assertEquals("Material Cadastrado com sucesso", res);

            res = facade.novoMaterial("1111","Anestesia Local","40");
            assertEquals("Material Cadastrado com sucesso", res);

///*-------------------------------------agora fazendo associa��es: procedimentos soncomem materiais e usam equipamentos-----*/

            facade = new Facade();
            res = facade.materialProcedimento("763236","2415"); // Ponte de Safena consome Fio de Sutura
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("763236","5927"); // Ponte de Safena consome Stinter card�aco
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("763236","8996"); // Ponte de Safena consome Antisseptico
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("763236","1110"); // Ponte de Safena consome Anestesia Geral
            assertEquals("Material Incluido com sucesso no procedimento", res);

            res = facade.equipamentoProcedimento("763236","912"); // Ponte de Safena necessita do apoio de Mesa de Cirurgia
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("763236","685"); // Ponte de Safena necessita do apoio de Raio X
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("763236","206"); // Ponte de Safena necessita do apoio de Ultrassom
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);

            res = facade.listMateriaisProcedimento("763236");
            assertEquals("Fio de Sutura%Stinter cardíaco%Antisseptico%Anestesia Geral", res);

            res = facade.listEquipamentosProcedimento("763236");
            assertEquals("Mesa de Cirurgia%Raio X%Ultrassom", res);


            res = facade.materialProcedimento("377523","2415"); // Transplante Cora��o consome Fio de Sutura
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","3314"); // Transplante Cora��o consome Gaze
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","9622"); // Transplante Cora��o consome Esparadrapo
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","5796"); // Transplante Cora��o consome Parafuso de Platina
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","4404"); // Transplante Cora��o consome Placa de Platina
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","8996"); // Transplante Cora��o consome Antisseptico
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("377523","1110"); // Transplante Cora��o consome Anestesia Geral
            assertEquals("Material Incluido com sucesso no procedimento", res);

            res = facade.equipamentoProcedimento("377523","912"); // Transplante Cora��o necessita do apoio de Mesa de Cirurgia
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("377523","188"); // Transplante Cora��o necessita do apoio de Cadeira
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("377523","685"); // Transplante Cora��o necessita do apoio de Raio X
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("377523","206"); // Transplante Cora��o necessita do apoio de Ultrassom
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("377523","845"); // Transplante Cora��o necessita do apoio de Tom�grafo
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);


            res = facade.materialProcedimento("404482","1881"); // Redu��o de Fratura consome Gesso
            assertEquals("Material Incluido com sucesso no procedimento", res);

            res = facade.equipamentoProcedimento("404482","885"); // Redu��o de Fratura necessita do apoio de Maca
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("404482","188"); // Redu��o de Fratura necessita do apoio de Cadeira
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("404482","358"); // Redu��o de Fratura necessita do apoio de Mesa de Trabalho
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);


            res = facade.equipamentoProcedimento("894275","912"); // Amputa��o de Membro necessita do apoio de Mesa de Cirurgia
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("894275","188"); // Amputa��o de Membro necessita do apoio de Cadeira
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("894275","358"); // Amputa��o de Membro necessita do apoio de Mesa de Trabalho
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("894275","685"); // Amputa��o de Membro necessita do apoio de Raio X
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);

            res = facade.materialProcedimento("894275","2415"); // Amputa��o de Membro consome Fio de Sutura
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("894275","3314"); // Amputa��o de Membro consome Gaze
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("894275","9622"); // Amputa��o de Membro consome Esparadrapo
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("894275","8996"); // Amputa��o de Membro consome Antisseptico
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("894275","1110"); // Amputa��o de Membro consome Anestesia Geral
            assertEquals("Material Incluido com sucesso no procedimento", res);
///*--------------------------Checando a persist�ncia ----------------------------------*/

            facade = new Facade(); 

            //transplante de cora��o
            res = facade.listMateriaisProcedimento("377523");
            assertEquals("Fio de Sutura%Gaze%Esparadrapo%Parafuso de Platina%Placa de Platina%Antisseptico%Anestesia Geral", res);

            res = facade.listEquipamentosProcedimento("377523");
            assertEquals("Mesa de Cirurgia%Cadeira%Raio X%Ultrassom%Tomógrafo", res);

            //redu��o de fratura
            res = facade.listMateriaisProcedimento("404482");
            assertEquals("Gesso", res);
            res = facade.listEquipamentosProcedimento("404482");
            assertEquals("Maca%Cadeira%Mesa de Trabalho", res);

            //Amputa��o de Membro
            res = facade.listMateriaisProcedimento("894275");
            assertEquals("Fio de Sutura%Gaze%Esparadrapo%Antisseptico%Anestesia Geral", res);
            res = facade.listEquipamentosProcedimento("894275");
            assertEquals("Mesa de Cirurgia%Cadeira%Mesa de Trabalho%Raio X", res);


/*-------------------------------------prosseguindo os testes---------------------------------------------------*/


            res = facade.equipamentoProcedimento("839530","885"); // Curativo necessita do apoio de Maca
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("839530","188"); // Curativo necessita do apoio de Cadeira
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("839530","358"); // Curativo necessita do apoio de Mesa de Trabalho
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);

            res = facade.materialProcedimento("839530","3314"); // Curativo consome Gaze
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("839530","9622"); // Curativo consome Esparadrapo
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("839530","8996"); // Curativo consome Antisseptico
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("839530","1111"); // Curativo consome Anestesia Local
            assertEquals("Material Incluido com sucesso no procedimento", res);

            //	Curativo
            res = facade.listMateriaisProcedimento("839530");
            assertEquals("Gaze%Esparadrapo%Antisseptico%Anestesia Local", res);
            res = facade.listEquipamentosProcedimento("404482");
            assertEquals("Maca%Cadeira%Mesa de Trabalho", res);


            //Nebuliza��o
            res = facade.materialProcedimento("200752","7278"); // Nebuliza��o consome Broncodilatador
            assertEquals("Material Incluido com sucesso no procedimento", res);


            //	Nebuliza��o
            res = facade.listMateriaisProcedimento("200752");
            assertEquals("Broncodilatador", res);


            res = facade.equipamentoProcedimento("886244","912"); // Cateterismo necessita do apoio de Mesa de Cirurgia
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("886244","188"); // Cateterismo necessita do apoio de Cadeira
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);
            res = facade.equipamentoProcedimento("886244","685"); // Cateterismo necessita do apoio de Raio X
            assertEquals("Equipamento Incluido com sucesso no procedimento", res);


            res = facade.materialProcedimento("886244","8996"); // Cateterismo consome Antisseptico
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("886244","1110"); // Cateterismo consome Anestesia Geral
            assertEquals("Material Incluido com sucesso no procedimento", res);
            res = facade.materialProcedimento("886244","5927"); // Cateterismo consome Stinter card�aco
            assertEquals("Material Incluido com sucesso no procedimento", res);

//---------------------------Mais testes de persist�ncia tamb�m

            facade = new Facade();

            //	Cateterismo
            res = facade.listEquipamentosProcedimento("886244");
            assertEquals("Mesa de Cirurgia%Cadeira%Raio X", res);
            res = facade.listMateriaisProcedimento("886244");
            assertEquals("Antisseptico%Anestesia Geral%Stinter cardíaco", res);
			
	}

}
