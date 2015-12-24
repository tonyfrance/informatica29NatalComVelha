/*ex29 - Jogo da Velha 
AUTORES:
        Antonio Francelino
        Hericles Escoteiro
        Priscila de Sousa Silva
        Thiago Rodrigo

ORIENTADOR:
        Prof. Ruben Carlo Benante
OBS: Esse programa e protegido pela GNU LICENSE V2.0, para maiores informacoes consulte o arquivo LICENSE*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>

#define TAMTAB 3 /*tamanho da tabela para o jogo*/

/* Bordas UTF 8 */

#define WUL L'\u2518' /* ^VU2518 ┘ */
#define WDL L'\u2510' /* ^VU2510 ┐ */
#define WDR L'\u250c' /* ^VU250c ┌ */
#define WUR L'\u2514' /* ^VU2514 └ */
#define WVH L'\u253c' /* ^VU253c ┼ */
#define WHH L'\u2500' /* ^VU2500 ─ */
#define WVR L'\u251c' /* ^VU251c ├ */
#define WVL L'\u2524' /* ^VU2524 ┤ */
#define WUH L'\u2534' /* ^VU2534 ┴ */
#define WDF L'\u252c' /* ^VU252c ┬ */
#define WVV L'\u2502' /* ^VU2502 │ */
#define WGL L'\u2571' /* ^VU2571 ╱ */
#define WGR L'\u2572' /* ^VU2572 ╲ */
#define WGX L'\u2573' /* ^VU2573 ╳ */
#define PRINTGRAF_ON ;
#define PRINTGRAF_OFF ;

/* Prototipos */
void inicio(int tab[3][3]); /* zera o tabuleiro */
int nivelfacil(int tab[3][3]); /* funcao do nivel facil */
int nivelmedio(int tab[3][3]); /* funcao do nivel medio */
int niveldificil(int tab[3][3]); /* funcao do nivel dificil */
int imprimetab(void); /* imprime tabuleiro de jogo da velha */
int imprimemenunivel(int nivel); /* imprime o menu de selecao de nivel */
int imprimemenu(void); /* imprime o menu principal */
int humanoVShumano(void); /*chama a funcao multiplayer*/
int humanoVSpc(void); /*chama a funcao humano contra o computador*/
int pcVSpc(void); /*chama a funcao computador contra o computador*/
int vence(void);/*chama a funcao q determinara o final do jogo*/
int entrada(void);/*chama a funcao de entrada de dados do usuario(jogador)*/
char start(void);/*chama a funcao qm ira fazer a primeira jogada*/

int main(void)
{
    int tab[3][3],jogada=0,x,nivel;
    vez=-1;
    srand(time(NULL));
    incio(tab);
    imprimemenu();
    imprimetab();

    /*do
    {
        vez*=-1;
        if(vez==1)   vez do X 
        {
            switch(opt)
            {
                case 1:
                    humanoVShumano();
                    break;
                case 2:
                    humanoVSpc();
                    break;
                case 3:
                    pcVSpc();
                    break;
                default:
                    printf("ERRO. Obrigado por jogar!\n");
                    return 0;
            }
            jogada++;
            x=vence();
            if(x==1)
                vez++;   se X ganhar, vez recebe 2 
        }
        if(vez==-1)    vez do O 
        {
            switch(opt)
            {
                case 1:
                    humanoVShumano();
                    break;
                case 2:
                    humanoVSpc();
                    break;
                case 3:
                    pcVSpc();
                    break;
                default:
                    printf("ERRO. Obrigado por jogar!\n");
                    return 0;
            }
            jogada++;
            x=vence();
            if(x==1)
                vez++;  se O ganhar, vez recebe 0 
        }
        if(jogada==9 && x==0)  se o contador de jogadas for 9, sai do laço e testa empate 
            vez=3;
    }while(vez==1 || vez==-1);

    switch(vez)
    {
        case 0:
            printf("O ganhou\n");
            break;
        case 2:
            printf("X ganhou\n");
            break;
        case 3:
            printf("DEU VELHA\n");
            break;
        default:
            break;
    }*/
    printf("Obrigado por jogar o Jogo da Velha\n");


    return EXIT_SUCCESS;
}

void inicio(int tab[3][3])
{
    int i,j;

    for(i=0;i<TAMTAB;i++)      /*faz todas as casas receberem 0 para deixar o tabuleiro em branco */
        for(j=0;j<TAMTAB;j++)
            tab[i][j]=0;
    return 0;
}

int imprimemenunivel(int nivel)
{
    printf("Escolha um nivel de dificuldade: \n");
    printf("1-facil \n2-medio \n3-dificil\n");
    scanf("%d", &nivel);
    switch(nivel)
    {
        case 1:
            printf("nivel facil\n");
            /*nivelfacil();*/
            break;
        case 2:
            printf("nivel medio\n");
            /*nivelmedio();*/
            break;
        case 3:
            printf("nivel dificil\n");
            /*niveldificil();*/
            break;
        default:
            printf("ERRO.\nObrigado por jogar\n");
            break;
    }

    return 0;
}


int imprimetab(void)
{
    /* Lembrar de implementar UTF-8 depois */
    int linha, coluna;
    putchar('\n');

    for(linha=0; linha<TAMTAB; linha++)
    {
        for(coluna=0; coluna<TAMTAB; coluna++)
        {
            if(d.tab[linha][coluna] == 0)
                printf("    ");
            else
                if(d.tab[linha][coluna] == 1)
                    printf("  X ");
                else
                    printf("  O ");

            if(coluna!=(TAMTAB-1))
                printf("|");
        }
        putchar('\n');
        if(linha<TAMTAB-1)
            printf(" ---+----+---\n");
    }
    putchar('\n');
    return 0;
}
int vence(void)/*Determina como finalizara o jogo*/
{
    int n1;
    for(n1=0; n1<3; n1++)/* Analisa se tem linha completa */
    {
        if((d.tab[n1][0] == vez && d.tab[n1][1] == vez) && d.tab[n1][2] == vez)
            return 1;
    }
    for(n1=0; n1<3; n1++)/* Analisa se tem coluna completa */
    {
        if((d.tab[0][n1] == vez && d.tab[1][n1] == vez) && d.tab[2][n1] == vez)
            return 1;  
    }
    if((d.tab[0][0] == vez && d.tab[1][1] == vez) && d.tab[2][2])
        return 1;
    else if((d.tab[0][2] == vez && d.tab[1][1] == vez) && d.tab[2][0])
        return 1;
    return 0;
}

int entrada(void)/*Determina a entrada de dados do jogador por tecla para cada espaço livre no #*/
{
    int numero,linha,coluna,x;
    do
    {
        printf("Escolha valores entre 0 e 8\n");
        for(linha=0; linha<TAMTAB; linha++)
            {
                for(coluna=0; coluna<TAMTAB; coluna++)
                    {
                        x++;
                        if(d.tab[linha][coluna] == 0)
                        printf("%d",x);
                    }
            }
                                                         
        scanf("%d",&numero);
        switch(numero)
        {
            case 1:
                if(d.tab[0][0]==0)
                    d.tab[0][0]=vez;     
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 2:
                if(d.tab[0][1]==0)
                    d.tab[0][1]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 3:
                if(d.tab[0][2]==0)
                    d.tab[0][2]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 4:
                if(d.tab[1][0]==0)
                    d.tab[1][0]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 5:
                if(d.tab[1][1]==0)
                    d.tab[1][1]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 6:
                if(d.tab[1][2]==0)
                    d.tab[1][2]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 7:
                if(d.tab[2][0]==0)
                    d.tab[2][0]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 8:
                if(d.tab[2][1]==0)
                    d.tab[2][1]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            case 9:
                if(d.tab[2][2]==0)
                    d.tab[2][2]=vez;
                else
                {
                    printf("Opcao invalida...escolha uma opcao valida!!!\n");
                    numero=11;
                }
                break;
            default:
                printf("Opcao invalida...escolha uma opcao valida!!!\n");
                break;
        }          
    }while(numero>0 || numero<10);
}

/*int humanojoga(void)
{
    int numero, vez;
    do
    {
        imprimetab();
        numero=entrada();
    }while(0==0); coloque uma condicao aqui

}*/

int imprimemenu(void)/*imprime menu*/
{
    
    printf("Bem vindo ao jogo da velha de NATAL!\n");
    printf("Escolha seu tipo de jogo: ");
    printf("\n1-Player vs Player \n2-Player vs PC \n3-PC vs PC\n");
    scanf("%d", &opt);
    switch(opt)/*opcoes para modo de jogo*/
    {
        case 1:
            printf("Player vs Player\n");
            humanoVShumano();
            break;
        case 2:
            printf("Player vs PC\n");
            humanoVSpc();
            break;
        case 3:
            printf("PC vs PC\n");
            pcVSpc();
            break;
        default:
            printf("ERRO. Obrigado por jogar!\n");
            
    }
    return 0;
}

char start(void)/*Seleciona qm ira fazer a primeira jogada*/
{
    char r,x;

    printf("\nVoce quer começar jogando?\n s-sim\nn-nao\n");
    do
    {
        r=getchar();
        if(r=='s')
            x=3;
        else if(r=='n')
            x=3;
        else               
            x=2;
    }while(x==2);
    
    return r;
}

int humanoVShumano(void)
{
    printf("O primeiro Player sera X e o segundo Player sera O\n");
}

int humanoVSpc(void)
{
    imprimemenunivel();
    start();
    printf("O primeiro Player sera X e o segundo Player sera O\n");    
}

int pcVSpc(void)/*modo de jogo pc vs pc*/
{
    int x,y,r=1,jogada=0;

    imprimemenunivel();
    printf("O primeiro Player sera X e o segundo Player sera O\n");

    do
    {
        if(vez==1)
        {
            printf("\nJogador 1:\n");
            x=rand()%3;
            y=rand()%3;
            if(d.tab[x][y]==0)
                d.tab[x][y] = 1;
            jogada=jogada+1;
        }
        else
        {
            printf("\nJogador 2:\n");
            x=rand()%3;
            y=rand()%3;
            if(d.tab[x][y]==0)
                d.tab[x][y] = 2;
            jogada=jogada+1;
        }
        vez=vez*-1;
        imprimetab();

    }while(jogada<9);

    return 0;
}


