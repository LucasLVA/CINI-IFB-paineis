#include <string.h>
#include "funcionario.h"
#include "principal.h"
#include "funcoesgerais.h"
#include "struct.h"

void print_menu_funcionario (WINDOW *wins, dados_janela win1){

	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
	mvwprintw(wins, win1.starty+2, win1.startx,"Selecione uma opcao:");
	mvwprintw(wins, win1.cursor, win1.startx,"->");
	mvwprintw(wins, win1.starty+4, win1.startx+3,"Cadastrar filme");
	mvwprintw(wins, win1.starty+5, win1.startx+3,"Remover filme");
	mvwprintw(wins, win1.starty+6, win1.startx+3,"Visualizar salas");
	mvwprintw(wins, win1.starty+8, win1.startx+3,"Sair");

}
/*Seleciona a sala a ser consultada*/
void print_menu_salas (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas){
  int posicao_filme = win1.starty+4;
	
  wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
  if(salas_ocupadas != 0){
    mvwprintw(wins, win1.starty+2, win1.startx,"Qual sala sera consultada:");
    mvwprintw(wins, (win1.cursor = win1.starty+4), win1.startx,"->");
    for(int i = 0; i < NUM_SALAS; i++){
      if(filmes[i][0] != '\0'){
        mvwprintw(wins, posicao_filme, win1.startx+3,"Sala %d - %s", i+1, filmes[i]);
        posicao_filme++;
      }
    }
    posicao_filme++;
		mvwprintw(wins, posicao_filme, win1.startx+3,"Sair");
	}
	else{
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Nenhum filme em Cartaz!")/2)),"Nenhum filme em Cartaz!");
	}
	update_panels();
  doupdate();

}

void print_menu_remove_filme (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas){
  int posicao_filme = win1.starty+4;
	
  wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
  if(salas_ocupadas != 0){
    mvwprintw(wins, win1.starty+2, win1.startx,"Selecione o filme a ser removido:");
    mvwprintw(wins, win1.cursor, win1.startx,"->");
    for(int i = 0; i < NUM_SALAS; i++){
      if(filmes[i][0] != '\0'){
        mvwprintw(wins, posicao_filme, win1.startx+3, "%s (Sala %d)", filmes[i], i+1);
        posicao_filme++;
      }
    }
    posicao_filme++;
		mvwprintw(wins, posicao_filme, win1.startx+3,"Sair");
	}
	else{
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Nenhum filme em Cartaz!")/2)),"Nenhum filme em Cartaz!");
	}

}

void cadastrar_filme(int *salas, char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1, int ch){
	int opcao;
	int auxSala=0;

	if(*salas == 5){
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Todas as salas ja estão ocupadas!")/2)),"Todas as salas ja estão ocupadas!");	
		update_panels();
  	doupdate();

		sleep(DELAY);
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);

	  return;
		

	}
	
	else{
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
		mvwprintw(wins, win1.starty+3, win1.startx+3,"Sala: ");
		echo();
		wscanw(wins,"%d", &auxSala);
		noecho();
		if(auxSala > 5){ // caso fosse cadastrar filme em sala maior q 5 (numero maximo de salas)
			wclear(wins);
			box(wins, ACS_VLINE, ACS_HLINE);
			mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Sala Inexistente!")/2)),"Sala Inexistente!");
			mvwprintw(wins, win1.altura/2+2, ((win1.comprimento/2)-(strlen("Digite uma sala entre 1-5")/2)),"Digite uma sala entre 1-5");
			update_panels();
			doupdate();
			sleep(DELAY);	
			
			wclear(wins);
			box(wins, ACS_VLINE, ACS_HLINE);
		}

		else if(filmes[auxSala-1][0] != '\0'){
			wclear(wins);
			box(wins, ACS_VLINE, ACS_HLINE);
			mvwprintw(wins, win1.altura/2, (win1.comprimento/2)-3,"Sala ocupada!");
			update_panels();
			doupdate();
			sleep(DELAY);	
			
			wclear(wins);
			box(wins, ACS_VLINE, ACS_HLINE);
			
		}
		else{
			mvwprintw(wins, win1.starty+7, win1.startx+3,"Nome do filme: ");
			echo();
			wgetstr(wins, filmes[auxSala-1]);

			cbreak();
			noecho();
			
			wclear(wins);
			box(wins, ACS_VLINE, ACS_HLINE);
			mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Filme Cadastrado com sucesso!")/2)),"Filme Cadastrado com sucesso!");	
			*salas = *salas +1;

			update_panels();
			doupdate();
			sleep(DELAY);	

			wclear(wins);
		}
	}
	
}

void remove_filme(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,int *salas){
	int opcao = 0;
	int ch;
	int salas_ocupadas = 0;
	int posicao_salas[NUM_SALAS]= {-1};
	int posicao_atual = 0;
	for(int i = 0;i < 5;i++){
    if(filmes[i][0] != '\0'){
      salas_ocupadas++;
			posicao_salas[posicao_atual] = i;
			posicao_atual++;
    }
  }

	print_menu_remove_filme(wins, win1, filmes,salas_ocupadas);
	update_panels();
	doupdate();
	if(salas_ocupadas == 0){
		sleep(DELAY);
		wclear(wins);
		return;
	}
	else{
		while(opcao != -1){
			ch = getch();
			if (ch != 10){
				mvwprintw(wins, win1.cursor, win1.startx,"  ");
				opcao = escolhe_opcao(ch, opcao, &win1,salas_ocupadas);
				mvwprintw(wins, win1.cursor, win1.startx,"->");
				update_panels();
				doupdate();
			}
			if(ch == 10){
				if(opcao == salas_ocupadas){
					mvwprintw(wins, win1.cursor, win1.startx,"  ");	
				}
				else{
					filmes [posicao_salas[opcao]][0] = '\0';
					wclear(wins);
					box(wins, ACS_VLINE, ACS_HLINE);
					mvwprintw(wins, win1.altura/2, (win1.comprimento/2)-(strlen("Filme removido com sucesso!")/2) ,"Filme removido com sucesso!");
					update_panels();
					doupdate();
					sleep(DELAY);
				}
				wclear(wins);
				box(wins, ACS_VLINE, ACS_HLINE);
				return;
			}

		}
	}


}


void visualiza_sala(dados_janela win1, WINDOW *wins, int *salas, char filme[SIZE_NAME],char sala_cinema[LETRAS][COLUNAS], int venda_ingressos, cliente clientes[MAX_CLIENTE], int indice_filme){
	int ch= 0,opcao = 0;
	
	/*Printa a a 2ª parte do menu de visualização de salas com mapa da sala do filme escolhido e as 2 outras opções*/
	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
	mvwprintw(wins, win1.starty+1, (win1.comprimento/2)-(strlen(filme)/2),"%s", filme);
	
	print_salas(sala_cinema, wins,(win1.altura/2) - 5 ,(win1.comprimento/2)-(9));
	
	mvwprintw(wins, (win1.cursor = win1.altura - 4), win1.startx,"->");
	mvwprintw(wins, win1.altura-4, win1.startx+3,"Exibir clientes");
	mvwprintw(wins, win1.altura-2, win1.startx+3,"Voltar");
	update_panels();
	doupdate();
	while(ch != -1){
		ch = getch();
		if(ch != 10){
			mvwprintw(wins, win1.cursor, win1.startx,"  ");
			opcao = escolhe_opcao(ch, opcao, &win1, 1);
			mvwprintw(wins, win1.cursor, win1.startx,"->");
			update_panels();
			doupdate();		
		}
		if(ch == 10){
			if (opcao == 0){
				/*Printa o cabeçalho com o título do filme escolhido e a opção de voltar no final da janela*/
				wclear(wins);
				box(wins, ACS_VLINE, ACS_HLINE);
				mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
				mvwprintw(wins, win1.starty+1, (win1.comprimento/2)-(strlen(filme)/2),"%s", filme);
				mvwprintw(wins, win1.starty+3, win1.startx,"Clientes:");
				mvwprintw(wins, win1.altura - 2, win1.startx,"->");
				mvwprintw(wins, win1.altura-2, win1.startx+3,"Voltar");
				/*Esse  primeiro "do" mantem o print até que todos os ingressos comprados sejam colocados na tela*/
				for(int linha = 0; linha<venda_ingressos;linha++){
					/*Se o cliente comprou ingresso para o filme escolhido*/
					if(clientes[linha].filme == indice_filme){
						/*Printa os lugares dos ingressos comprados com vírgulas*/
						for(int j = 0;j < clientes[linha].numIngressos; j++ ){
							if(j < (clientes[linha].numIngressos)-1){
								mvwprintw(wins,win1.starty+5+linha, (win1.startx+3)+(j*4), "%s, ", clientes[linha].lugares[j]);
							}
							else{
								mvwprintw(wins,win1.starty+5+linha, (win1.startx+3)+(j*4), "%s - %s", clientes[linha].lugares[j],clientes[linha].nome);	
							}
						}
					}
				}
				update_panels();
				doupdate();
				do{
				}while((ch = getch()) != 10);
				return;
			}
			else{
				ch=-1;
			}
		}
	}
}

void menu_salas (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME],char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int venda_ingressos, cliente clientes[MAX_CLIENTE]){
	int opcao = 0, i=0,j=0 , linha=4;
	int ch;
	int salas_ocupadas = 0;
	int posicao_salas[NUM_SALAS]= {-1};
	int posicao_atual = 0;
	/*Posociona o cursor*/
	win1.cursor = win1.starty+4;
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Funcionario");
	/*Esse for verifica em quais salas tem  os fimes e as coloca em ordem na matriz posição salas para facilitar o print*/
	for(int i = 0;i < 5;i++){
    if(filmes[i][0] != '\0'){
      salas_ocupadas++;
			posicao_salas[posicao_atual] = i;
			posicao_atual++;
    }
  }
	/*Printa a 1ª parte do menu com os filmes em cartaz e a opção voltar*/
	print_menu_salas (wins,win1, filmes,salas_ocupadas);
	update_panels();
	doupdate();
	/*Se não houver filmes em cartaz esse if encerra o processo e manda a menssagem de erro*/
	if(salas_ocupadas == 0){
		sleep(DELAY);
		wclear(wins);
		return;
	}
	/*Se houver filmes cadastrados o else leva para a seleção do filme que a sala vai ser visualizada*/
	else{
		/*O while mantem no loop até que uma opcao seja selecionada na 1ª parte do menu*/
		while(opcao != -1){
			ch = getch();
			/*O if mantém a leitura com a função de escolher opcao para a 1ª parte do menu*/
			if (ch != 10){
				mvwprintw(wins, win1.cursor, win1.startx,"  ");
				opcao = escolhe_opcao(ch, opcao, &win1,salas_ocupadas);
				mvwprintw(wins, win1.cursor, win1.startx,"->");
				update_panels();
				doupdate();
			}
			/*Se for usado o enter o else é ativado e realiza a ação segundo a opcao selecionada no menu parte 1*/
			else{
				/*Se a opcao selecionada for o número de salas tem-se a opção de voltar selecionada*/
				if(opcao == salas_ocupadas){
					mvwprintw(wins, win1.cursor, win1.startx,"  ");
					wclear(wins);
					box(wins, ACS_VLINE, ACS_HLINE);
					opcao = -1;
					//return;		
				}
				else{
					visualiza_sala(win1,wins,salas,filmes[posicao_salas[opcao]],salas_cinema[posicao_salas[opcao]],venda_ingressos, clientes,posicao_salas[opcao]);
					win1.cursor = win1.starty+4;
					opcao=0;
					print_menu_salas (wins,win1, filmes,salas_ocupadas);
					
					
				}
			}
		}
		return;
	}
}

/*void visualizar_sala(dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME],char salas_cinema[NUM_SALAS][LETRAS][COLUNAS]){	
		
		menu_salas (win1, wins, *salas, filmes[NUM_SALAS][SIZE_NAME], salas_cinema[NUM_SALAS][LETRAS][COLUNAS]);
}*/

/*Analiza o valor da opção e leva a função que executa a ação desejada*/
void menu_funcionario (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME],char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int venda_ingressos, cliente clientes[MAX_CLIENTE]){
	int opcao = 0;
	int ch;

	while(opcao != -1){
		ch = getch();
		if (ch != 10){
			mvwprintw(wins, win1.cursor, win1.startx,"  ");
			opcao = escolhe_opcao(ch, opcao, &win1,3);
			mvwprintw(wins, win1.cursor, win1.startx,"->");
			update_panels();
			doupdate();
		}
		if(ch == 10){
			  switch(opcao){
          case 0:
            win1.cursor = win1.starty+4; //zera o cursor
            cadastrar_filme(salas, filmes, wins, win1, ch);
            break;
          case  1:
            win1.cursor = win1.starty+4; //zera o cursor
            remove_filme(filmes, wins, win1, salas);
            break;
          case 2:
            /*win1.cursor = win1.starty+4; *///zera o cursor
						/*wclear(wins);*///Limpando os resquissios das salas q fiucavam
						win1.cursor = win1.starty+4;
						menu_salas (win1, wins, salas, filmes, salas_cinema, venda_ingressos, clientes);
						win1.cursor = win1.starty+4;
            break;
          case 3:
            mvwprintw(wins, win1.cursor, win1.startx,"  ");

            return;		           
        }
        opcao = 0;
				print_menu_funcionario(wins,win1);
				update_panels();
				doupdate();
		}

	}



}