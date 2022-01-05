#ifndef STRUCT_H
#define STRUCT_H

#define NUM_SALAS 5
#define SIZE_NAME 100
#define LETRAS 8
#define COLUNAS 10
#define MAX_CLIENTE 80
#define MAX_INGRESSO 3

/*o DELAY foi escolhido pois a função halfdelay pega X decimos de segundo*/
#define DELAY 3

/*Tem a função de verificar se um painel está escondido*/
typedef struct {
	bool hide;
} panel_data;

/*Ar*/
typedef struct {

	float max_x, max_y;
	int startx, starty;
	float comprimento, altura;
	int cursor;

}dados_janela;

typedef struct {
	char nome[SIZE_NAME];
	int numIngressos;
	char lugares[MAX_INGRESSO][3];
	int filme;
}cliente;

/*void win(){
	dados_janela win1;
}*/

#endif