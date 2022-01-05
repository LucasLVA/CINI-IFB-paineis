#include "funcoesgerais.h"

/*Funções de incialização*/
void inicializa_matriz (char filmes[NUM_SALAS][SIZE_NAME]){
	int linha;

	for (linha = 0 ; linha < NUM_SALAS; linha++){
		
		filmes[linha][0] = '\0';
	
	}
}

void inicializa_salas (char salas_cinema[NUM_SALAS][LETRAS][COLUNAS]){
	int sala,fileira,coluna,espacos;

	for (sala = 0 ; sala < NUM_SALAS; sala++){
    for (fileira = 0; fileira < LETRAS; fileira++){
      for (coluna = 0; coluna < COLUNAS; coluna++){
				salas_cinema[sala][fileira][coluna] = ' ';
      }
    }
	}
	
  for (sala = 0 ; sala < NUM_SALAS; sala++){
    // a cada duas fileiras aumenta um espaco, fileira / 2 = espacos?
    for (fileira = 0; fileira < LETRAS; fileira++){
      if(fileira < 6){
				espacos = fileira/2;
			}
      if(fileira > 5){
				espacos = fileira-3; 
      }
      for (coluna = (0 + espacos); coluna < (COLUNAS - espacos); coluna++){
				
				salas_cinema[sala][fileira][coluna] = '@';
				
      }
    }
	}
}

void print_salas(char sala_cinema[LETRAS][COLUNAS], WINDOW *wins, int posicaoy,int posicaox){
  int fileira,coluna,espacos;

	mvwprintw(wins, posicaoy, posicaox,"  ");
  for (coluna = 0; coluna < COLUNAS; coluna++){
			mvwprintw(wins, posicaoy, posicaox+2*(coluna+1),"%d", coluna);
  }
  for (fileira = 0; fileira < LETRAS; fileira++){
    mvwprintw(wins, posicaoy+(fileira+1), posicaox,"%c", fileira+65); // 65 = A, 66 = B
    for (coluna = 0; coluna < COLUNAS; coluna++){
			mvwprintw(wins, posicaoy+(fileira+1), posicaox+2*(coluna+1),"%c", sala_cinema[fileira][coluna]);
    }
	}

}

void int_parametros_win (dados_janela *win1){

	getmaxyx(stdscr, win1->max_y, win1->max_x);
	getbegyx(stdscr, win1->startx, win1->starty);
	win1->startx = win1->startx+2;
	win1->starty = win1->starty+2;
	win1->comprimento = (win1->max_x)-5;
	win1->altura = (win1->max_y)-3;
	win1->cursor = win1->starty+4;

}

void criar_janelas (dados_janela win1, WINDOW **wins){
	int i;

	for(i=0; i<3; i++){
		if(i == 0){
			wins[i] = newwin(win1.altura, win1.comprimento, win1.starty, win1.startx);
			i++;
		}
		wins[i] = newwin(win1.altura, win1.comprimento, win1.starty, win1.startx);
	}

}

void criar_borda(WINDOW **wins){
	int i;

	for(i=0; i<3; i++){
		box(wins[i], ACS_VLINE, ACS_HLINE);
	}
}

int escolhe_opcao(int ch,int opcao, dados_janela *win1, int qtdOpcao){
	
	switch(ch){
			case KEY_UP:
				if(opcao != 0){
					if(opcao == qtdOpcao){
						win1->cursor-=2;
					}
					else{
						win1->cursor--;
					}
					opcao--;
				}
				break;
			case KEY_DOWN:
				if(opcao != qtdOpcao){
					if(opcao == qtdOpcao-1){
						win1->cursor+=2;
					}
					else{
						win1->cursor++;
					}
					opcao++;
				}
				break;
	}
	return opcao;

}

void imprime_alerta(WINDOW *wins,dados_janela win1, char mensagem[500]){

	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
	mvwprintw(wins, win1.altura/2, (win1.comprimento/2 - (strlen(mensagem)/2)),mensagem);
	update_panels();
	doupdate();
	sleep(DELAY);
	wclear(wins);
	box(wins, ACS_VLINE, ACS_HLINE);
}