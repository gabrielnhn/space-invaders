#include "lib_lista.h"
#include "configs.h"
#include "inicializacao.h"
#include "movimentoalien.h"
#include "movimentocanhao.h"
#include "colisoes.h"
#include "tela.h"
#include "processamento.h"

void inicializa_estruturas()
{
	inicializa_configuracoes();
	inicializa_tela(); 
}

int morto(J* jogo)
{
	if (jogo->vivo == 1)
		return 0;
	else
		return 1;
}

int ganhou(J* jogo)
/* o jogador ganha se nao ha aliens restantes */
{
	return (jogo->quantidade_aliens == 0);
}

int alien_chegou(J* jogo)
/* retorna 1 se, para qualquer alien vivo, sua linha e maior/igual que o numero de linhas do tabuleiro */
{
	t_lista* L;
	L = &(jogo->lista);

	inicializa_atual_inicio(L);
	int tam;
	tamanho_lista(&tam, L);

	elemento* e;
	int i;
	for(i = 1; i <= tam; i++)
	{
		consulta_item_atual(&e, L);

		if (e->tipo == alien1 || e->tipo == alien2 || e->tipo == alien3)
		{
			if ( e->i + 2 >= NUM_LINHAS_TABULEIRO )
				return 1;
		}

		incrementa_atual(L);
	}	
	
	return 0;
}

int acabou(J* jogo)
{
	if ( morto(jogo) || alien_chegou(jogo) || ganhou(jogo) )
		return 1;
	else
		return 0;
	
}

int pediu_pra_sair(char input)
/* verifica se o jogador nao quer sair do jogo */
{
	if (input == safeword)
		return 1;
	return 0;
}

void finaliza_estruturas(J* jogo)
{
	destroi_lista( &(jogo->lista) );
}

void game_over()
{
	erase();
	imprime_borda();
	mvprintw( NUM_LINHAS_TABULEIRO/2, NUM_COLUNAS_TABULEIRO/2 - 4, "GAME OVER");
	refresh();
	usleep(2000 * milisec);
}

void parabens()
{
	erase();
	imprime_borda();
	mvprintw(NUM_LINHAS_TABULEIRO/2, NUM_COLUNAS_TABULEIRO/2 - 6, "Boa, Campeao!");
	refresh();
	usleep(2000 * milisec);
}

void space_invaders(J* jogo, int velocidade_inicial)
{
	inicia_jogo(jogo, velocidade_inicial);
	inicializa_configuracoes();
	char input;

	do 
	{
		imprime_tela(jogo);
		input = ler_input();
		processa_lista( jogo, input );

		usleep(15 * milisec);
		jogo->contador_tempo++;

		if ( hora_de_colocar_nave(jogo) )
			colocar_nave(jogo);
	}
	while ( !acabou(jogo) && !pediu_pra_sair(input) );

	finaliza_estruturas(jogo);

	if ( ganhou(jogo) && !pediu_pra_sair(input) )
	{
		parabens();
		space_invaders(jogo, velocidade_inicial + 1);
		/* space invaders recursivo :D */
	}

	else if ( morto(jogo) || alien_chegou(jogo) )
		game_over();
}

void imprime_inicio()
{
	clear();
	imprime_borda();
	mvprintw(NUM_LINHAS_TABULEIRO/2 - 1, NUM_COLUNAS_TABULEIRO/2 - 7, "Space Invaders");
	mvprintw(NUM_LINHAS_TABULEIRO/2, NUM_COLUNAS_TABULEIRO/2 - 22, "Por Gabriel Nascarella Hishida do Nascimento");
	refresh();
	usleep(1500 * milisec);
}

int main()
{
	inicializa_estruturas();

	if ( !terminal_valido() )
	{
		finaliza_tela();
		printf("Tamanho de Terminal Invalido\n");
		return -1;
	}
	
	J estrutura_jogo;
	J* jogo = &estrutura_jogo;
	jogo->score = 0;

	imprime_inicio();
	space_invaders(jogo, 1);
	
	finaliza_tela();
	printf("Score: %ld \n", jogo->score);
	return 0;
}