#include "principal.h"


void print_menu_principal (WINDOW *wins, dados_janela win1){

	mvwprintw(wins, win1.starty, (win1.comprimento/2)-5,"Cine-IFB");
	mvwprintw(wins, win1.starty+2, win1.startx,"Selecione uma opcao:");
	mvwprintw(wins, win1.cursor, win1.startx,"->");
	mvwprintw(wins, win1.starty+4, win1.startx+3,"Cliente");
	mvwprintw(wins, win1.starty+5, win1.startx+3,"Funcionario");
	mvwprintw(wins, win1.starty+7, win1.startx+3,"Encerrar programa");
	
}

void menu(WINDOW *wins[], dados_janela win1,int opcao,PANEL *panels[]){
  switch(opcao){
    case 0:
      hide_panel(panels[1]);
      hide_panel(panels[2]);
      print_menu_principal(wins[0],win1);
      show_panel(panels[0]);
      break;
    case 1:
      hide_panel(panels[0]);
      hide_panel(panels[2]);
      print_menu_cliente(wins[1],win1);
      show_panel(panels[1]);
      break;
    case 2:
      hide_panel(panels[0]);
      hide_panel(panels[1]);
      print_menu_funcionario(wins[2],win1);
      show_panel(panels[2]);
      break;
  }
  update_panels();
  doupdate();
}

