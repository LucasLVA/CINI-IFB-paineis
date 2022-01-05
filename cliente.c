#include <string.h>
#include <unistd.h>
#include "cliente.h"
#include "struct.h"
#include "funcoesgerais.h"

void print_menu_cliente (WINDOW *wins, dados_janela win1){

	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-10,"Cine-IFB - Cliente");
	mvwprintw(wins, win1.starty+2, win1.startx,"Selecione uma opcao:");
	mvwprintw(wins, win1.cursor, win1.startx,"->");
	mvwprintw(wins, win1.starty+4, win1.startx+3,"Comprar ingresso");
	mvwprintw(wins, win1.starty+5, win1.startx+3,"Consultar filmes em cartaz");
	mvwprintw(wins, win1.starty+6, win1.startx+3,"Checar ingresso");
	mvwprintw(wins, win1.starty+8, win1.startx+3,"Sair");

}

void print_menu_consulta_cartaz (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME],int salas_ocupadas){
	int posicao_filme = win1.starty+4;

	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, ((win1.comprimento/2)-(strlen("Cine-IFB - Cliente")/2)),"Cine-IFB - Cliente");
  if(salas_ocupadas != 0){
    mvwprintw(wins, win1.starty+2, win1.startx,"Escolha o filme:");
    mvwprintw(wins, win1.cursor, win1.startx,"->");
    for(int i = 0; i < NUM_SALAS; i++){
      if(filmes[i][0] != '\0'){
        mvwprintw(wins, posicao_filme, win1.startx+3,"%s", filmes[i]);
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



int consulta_cartaz(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,int *salas,char salas_cinema[NUM_SALAS][LETRAS][COLUNAS]){
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

	print_menu_consulta_cartaz (wins, win1, filmes,salas_ocupadas);
	update_panels();
	doupdate();	

	if(salas_ocupadas == 0){
		
		sleep(DELAY);
		wclear(wins);
		return -1;
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
					wclear(wins);
					box(wins, ACS_VLINE, ACS_HLINE);
					return -1;		
				}
				else{
					wclear(wins);
					box(wins, ACS_VLINE, ACS_HLINE);
					mvwprintw(wins, win1.starty, (win1.comprimento/2)-((strlen("Cine-IFB - Cliente"))/2),"Cine-IFB - Cliente");
					mvwprintw(wins, win1.starty+1, (win1.comprimento/2)-(strlen(filmes[posicao_salas[opcao]])/2),"%s", filmes[posicao_salas[opcao]]);
					
					update_panels();
					doupdate();
					return posicao_salas[opcao];
				}

			}
		}
	}

	return -1;
}

void verifica_filme_cartaz (WINDOW *wins, dados_janela win1, char filmes[NUM_SALAS][SIZE_NAME], int salas_ocupadas){
  int posicao_filme = win1.starty+4, ch;
	
  wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.starty, (win1.comprimento/2)-12,"Cine-IFB - Cliente");
	mvwprintw(wins, win1.altura - 2, win1.startx,"->");
	mvwprintw(wins, win1.altura-2, win1.startx+3,"Voltar");
  if(salas_ocupadas != 0){
    mvwprintw(wins, win1.starty+2, win1.startx,"Em cartaz:");
    for(int i = 0; i < NUM_SALAS; i++){
      if(filmes[i][0] != '\0'){
        mvwprintw(wins, posicao_filme, win1.startx+3,"%s (Sala %d)", filmes[i], i+1);
        posicao_filme++;
      }
    }
    posicao_filme++;
	}
	else{
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.altura/2, ((win1.comprimento/2)-(strlen("Nenhum filme em Cartaz!")/2)),"Nenhum filme em Cartaz!");
	}
	update_panels();
  doupdate();
	do{
	}while((ch = getch()) != 10);

}

int checar_vagas(char sala_cinema[LETRAS][COLUNAS],int ingressos){
	int vagas = 0;
	for(int i = 0; i < LETRAS; i++){
		for(int j = 0; j < COLUNAS; j++){
			if(sala_cinema[i][j] == '@'){
				vagas++;
			}
		}
	}
	if (ingressos > vagas){
		return 0;
	}
	else{
		return 1;
	}
}

void bloqueia_covid(char sala_cinema[LETRAS][COLUNAS], int i, int j){
	if(sala_cinema[i-1][j] == '@' && i != 0){
		sala_cinema[i-1][j] = '$';
	}
	if(sala_cinema[i][j-1] == '@' && j != 0){
		sala_cinema[i][j-1] = '$';
	}
	if(sala_cinema[i][j+1] == '@' && j != 9){
		sala_cinema[i][j+1] = '$';
	}
	if(sala_cinema[i+1][j] == '@' && i != 7){
		sala_cinema[i+1][j] = '$';
	}
}


void escolhe_acento(char filme[SIZE_NAME],WINDOW *wins,dados_janela win1,cliente *cliente,char sala_cinema[LETRAS][COLUNAS]){
	char assento[3];
	int letra[MAX_INGRESSO], coluna[MAX_INGRESSO];
	int i = 0;
	echo();
	while(i < cliente->numIngressos){
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.starty, (win1.comprimento/2)-((strlen("Cine-IFB - Cliente"))/2),"Cine-IFB - Cliente");
		mvwprintw(wins, win1.starty+1, (win1.comprimento/2)-(strlen(filme)/2),"%s", filme);
		mvwprintw(wins, win1.starty+4, win1.startx + 4,"Digite o %dº lugar: ",i+1);
		print_salas(sala_cinema, wins,(win1.altura/2) - 5 ,(win1.comprimento/2)-(10));
		update_panels();
		doupdate();
		wmove(wins,win1.starty+4, win1.startx + 22);
		wgetstr(wins, assento);
		cbreak();
		letra[i] = assento[0]-65; // 65 = A
		coluna[i] = assento[1]-48; // 48 = 0

		if(sala_cinema[letra[i]][coluna[i]] != '@' ){
			imprime_alerta(wins,win1,"Local inválido!");
		}
		else{
			sala_cinema[letra[i]][coluna[i]] = '#';
			strcpy(cliente->lugares[i],assento);
			i++;
		}
	}
	noecho();
	i = 0;
	while(i < cliente->numIngressos){
		bloqueia_covid(sala_cinema,letra[i],coluna[i]);
		i++;
	}

}

int compra_ingresso(char filmes[NUM_SALAS][SIZE_NAME], WINDOW *wins, dados_janela win1,cliente *cliente,char salas_cinema[NUM_SALAS][LETRAS][COLUNAS],int *salas){
	int sala;
	int ingressos;
	char nome[SIZE_NAME];
	int tem_vaga;

	/*mvwprintw(wins, win1.starty, (win1.comprimento/2)-((strlen("Cine-IFB - Cliente"))/2),"Cine-IFB - Cliente");
	mvwprintw(wins, win1.starty+2, win1.startx,"Escolha o filme");*/
	update_panels();
	doupdate();
	sala = consulta_cartaz(filmes,wins, win1, salas, salas_cinema);
	if(sala != -1){
		echo();
		do{
			mvwprintw(wins, win1.starty+7, win1.startx+3,"Quantos ingressos: ");
			wscanw(wins,"%d", &ingressos);
			if(ingressos < 1 || ingressos > 3){
				imprime_alerta(wins,win1,"Por favor, insira de 1 a 3 ingressos.");
			}
			update_panels();
			doupdate();
			cbreak();
		}while(ingressos < 1 || ingressos > MAX_INGRESSO);
		mvwprintw(wins, win1.starty+8, win1.startx+3,"Nome do Cliente: ");
		wgetstr(wins, nome);
		cbreak();
		noecho();
		tem_vaga = checar_vagas(salas_cinema[sala],ingressos);
		if (tem_vaga){
			cliente->numIngressos = ingressos;
			cliente->filme = sala;
			strcpy(cliente->nome,nome); 
			escolhe_acento(filmes[sala],wins,win1,cliente,salas_cinema[sala]);		 
		}
		else{
			imprime_alerta(wins,win1,"Não ha vagas!");
			return 0;
		}
		cliente->numIngressos = ingressos;
		cliente->filme = sala; 
		//mvwprintw(wins, win1.starty+2, win1.startx,"Quantos ingressos: ");
		return 1;
	}
	else{
		return 0;
	}
}

void checar_ingresso(dados_janela win1, WINDOW *wins, char filmes[NUM_SALAS][SIZE_NAME], cliente clientes[MAX_CLIENTE],int *venda_ingressos,int vendeu){
	char nomeCliente[SIZE_NAME];
	int i,compara,tamanho;
	int ch;
	
	if(vendeu != 0){ // TELA POS VENDA DE INGRESSO
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.starty, (win1.comprimento/2)-((strlen("Cine-IFB - Cliente"))/2),"Cine-IFB - Cliente");
		mvwprintw(wins, win1.starty+2, win1.startx,"Ingressos gerados com sucesso");
		mvwprintw(wins, win1.starty+4, win1.startx,"Filme: %s",filmes[clientes[*venda_ingressos].filme]);
		mvwprintw(wins, win1.starty+5, win1.startx,"Sala: %d",clientes[*venda_ingressos].filme+1);
		mvwprintw(wins, win1.starty+6, win1.startx,"Cliente: %s",clientes[*venda_ingressos].nome);
		mvwprintw(wins, win1.starty+7, win1.startx,"Lugar: ");
		mvwprintw(wins, win1.altura - 2, win1.startx,"->");
		mvwprintw(wins, win1.altura-2, win1.startx+3,"Voltar");
		for(i = 0; i < clientes[*venda_ingressos].numIngressos;i++){
			if(i== (clientes[*venda_ingressos].numIngressos-1)){
				mvwprintw(wins, win1.starty+7, win1.startx+7+i*3,"%s",clientes[*venda_ingressos].lugares[i]);
			}
			else{
				mvwprintw(wins, win1.starty+7, win1.startx+7+i*3,"%s,",clientes[*venda_ingressos].lugares[i]);
			}
		}
		update_panels();
		doupdate();
	}
	else{ // Checar ingresso OPCAO 2 MENU CLIENTE
		wclear(wins);
		box(wins, ACS_VLINE, ACS_HLINE);
		mvwprintw(wins, win1.starty, (win1.comprimento/2)-((strlen("Cine-IFB - Cliente"))/2),"Cine-IFB - Cliente");
		echo();
		mvwprintw(wins, win1.starty+2, win1.startx,"Nome do Cliente: ");
		wgetstr(wins, nomeCliente);
		cbreak();
		noecho();
		i = 0;
		while(strcmp(nomeCliente,clientes[i].nome) != 0 && i < *venda_ingressos){
			i++;
		}
		if(i < *venda_ingressos){
			mvwprintw(wins, win1.starty+4, win1.startx,"Filme: %s",filmes[clientes[i].filme]);
			mvwprintw(wins, win1.starty+5, win1.startx,"Sala: %d",clientes[i].filme+1);
			mvwprintw(wins, win1.starty+6, win1.startx,"Cliente: %s",clientes[i].nome);
			mvwprintw(wins, win1.starty+7, win1.startx,"Lugar: ");
			mvwprintw(wins, win1.altura - 2, win1.startx,"->");
			mvwprintw(wins, win1.altura-2, win1.startx+3,"Voltar");
			for(int j = 0; j < clientes[i].numIngressos;j++){
				if(j== (clientes[i].numIngressos-1)){
					mvwprintw(wins, win1.starty+7, win1.startx+7+j*3,"%s",clientes[i].lugares[j]);
				}
				else{
					mvwprintw(wins, win1.starty+7, win1.startx+7+j*3,"%s,",clientes[i].lugares[j]);
				}
				
			}
			update_panels();
			doupdate();
			do{
			}while((ch = getch()) != 10);
		}
		else{
			imprime_alerta(wins, win1, "Cliente não existe!");
		}
		
	}
}
void menu_cliente (dados_janela win1, WINDOW *wins, int *salas, char filmes[NUM_SALAS][SIZE_NAME], cliente clientes[MAX_CLIENTE], char salas_cinema[NUM_SALAS][LETRAS][COLUNAS], int *venda_ingressos){
	int opcao = 0;
	int ch;
	int vendeu, salas_ocupadas; 

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
			mvwprintw(wins, win1.cursor, win1.startx,"  ");
			switch(opcao){
				case 0:
					win1.cursor = win1.starty+4; //zera o cursor
					vendeu = compra_ingresso(filmes, wins, win1, &clientes[*venda_ingressos], salas_cinema,salas);
					if(vendeu != 0){
						checar_ingresso( win1, wins,filmes,clientes, venda_ingressos,vendeu);
						*venda_ingressos = *venda_ingressos + 1;
					}
					print_menu_cliente (wins, win1);
					update_panels();
					doupdate();
					break;
				case 1:
					verifica_filme_cartaz (wins, win1, filmes, salas_ocupadas);
					print_menu_cliente (wins, win1);
					update_panels();
					doupdate();
					break;
				case 2:
					vendeu=0; // test
					checar_ingresso(win1, wins,filmes, clientes, venda_ingressos, vendeu);
					print_menu_cliente (wins, win1);
					update_panels();
					doupdate();
					break;
				case 3:
					mvwprintw(wins, win1.cursor, win1.startx,"  ");
					update_panels();
					doupdate();
					return;		
					
		
			}
		}
		
	}



}
