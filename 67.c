//Riccardo Cavasin

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int getch(){
	struct termios oldattr,newattr;
	int ch;
	tcgetattr(STDIN_FILENO,&oldattr);
	newattr=oldattr;
	newattr.c_lflag&=~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,&newattr);
	ch=getchar();
	tcsetattr(STDIN_FILENO,TCSANOW,&oldattr);
return ch;
}

char mscanf(int ste);
void render(int t[][9],int vn[],int misc[],int ste);//  ╠╗
int check(int t[][9]);								//   ║
int load(int t[][9],int vn[],int vs[],int dif,int ste);		//  misc
void move(int t[][9],int vn[],int misc[],int ste);	//  ╠╝
void preload(int sil[],int ste);
int silect(int sil[],int t[][9],int ste);
void printslot(int sil[]);
int hazel(int sil[],int t[][9],int in);

int main(int argv, char**argc){

	int t[9][9],vn[170],vs[243],misc[3]={-1,-1,-1};
	int p,n,scr=0;
	int sil[455];
	srand(time(NULL));

	system("clear");
	printf("\n    (         ╔═══════════════════════════════════════════╗         )\n   / (        ║  )\\         O_._._._A_._._._O         /(  ║        ) \\\n  ) ( \\   ⓛⓤⓒ ║   \\`--.___,'=================`.___,--'/   ║ⓘⓓⓔ    / ) (\n  \\(_)/   ⓢⓣⓔ ║    \\`--._.__                 __._,--'/    ║ⓛⓛⓐ    \\(_)/\n   <─> ╔══════╝      \\  ,. l`~~~~~~~~~~~~~~~'l ,.  /      ╚══════╗ <─>\n   / \\ ║ __            \\||(_)!_!_!_.-._!_!_!(_)||/            __ ║ / \\\n   \\ / ║ \\\\`-.__        ||_|____!!_|;|_!!____|_||        __,-'// ║ \\ /\n   / \\ ║  \\\\    `==---='-----------'='-----------`=---=='    //  ║ / \\\n   \\ / ║  | `--.     ◅ press any key to continue ▻       ,--' |  ║ \\ /\n   / \\ ║   \\  ,.`~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~',.  /   ║ / \\\n   \\ / ║     \\||  ____,-------._,-------._,-------.____  ||/     ║ \\ /\n   /_\\ ║      ||\\|___!`=======\"!`=======\"!`=======\"!___|/||      ║ /_\\\n ╔═════╝      || |---||--------||-| | |-!!--------||---| ||      ╚═════╗\n ║  __O_____O_ll_lO_____O_____O|| |'|'| ||O_____O_____Ol_ll_O_____O__  ║\n ║  o H o o H o o H o o H o o |-----------| o o H o o H o o H o o H o  ║\n ║ ___H_____H_____H_____H____O =========== O____H_____H_____H_____H___ ║\n ║  .--.    ┆_______ _     _ ______   _____  _     _ _     _┆    .--.  ║\n ║:::::.\\:::┆|______ |     | |     \\ |     | |____/  |     |┆:::/.:::::║\n ║'      `--┆______| |_____| |_____/ |_____| |    \\_ |_____|┆--'      '║\n ╚═════════╡╰┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄╯╞═════════╝\n");
	preload(sil,0);
	getch();
	do{
		system("clear");
		printf("\n    (         ╔═══════════════════════════════════════════╗         )\n   / (        ║(o_    _______ ______ __   _ _     _    _o)║        ) \\\n  ) ( \\   ⓛⓤⓒ ║//\\    |  |  | |_____ | \\  | |     |    /\\\\║ⓘⓓⓔ    / ) (\n  \\(_)/   ⓢⓣⓔ ║V_/_   |  |  | |_____ |  \\_| |_____|   _\\_V║ⓛⓛⓐ    \\(_)/\n   <─> ╔══════╝───────────────────────────────────────────╚══════╗ <─>\n   / \\ ║score: ");
		if(scr>1000)
			printf("1000+");
		else{
			printf("%d",scr);
			p=scr;
			n=5;
			do{
				n=n-1;
				p=p/10;
			}while(p>0);
			for(;n>0;printf(" "),n=n-1);
		}
		printf("          ◅ INSERISCI ▻                      ║ / \\\n   \\ / ║                                                         ║ \\ /\n   / \\ ║   ①      ...per cominciare una nuova partita...     ①   ║ / \\\n   \\ / ║                                                         ║ \\ /\n   / \\ ║   ②  per creare o eliminare uno slot di salvataggio ②   ║ / \\\n   \\ / ║                                                         ║ \\ /\n   /_\\ ║   ③         ...per leggere le istruzioni...         ③   ║ /_\\\n ╔═════╝                                                         ╚═════╗\n ║         ④           ...per salvare e uscire...            ④         ║\n ║                                                                     ║\n ║          ╭───────────────────────────────────────────────╮          ║\n ║  .--.    │_______ _     _ ______   _____  _     _ _     _│    .--.  ║\n ║:::::.\\:::│|______ |     | |     \\ |     | |____/  |     |│:::/.:::::║\n ║'      `--│______| |_____| |_____/ |_____| |    \\_ |_____|│--'      '║\n ╚═════════╗╰───────────────────────────────────────────────╯╞═════════╝\n           ╚╡☛ ");
		p=mscanf(0);
		switch(p){
			case 1:
				p=silect(sil,t,0);
				if(p==1){
					do{
						system("clear");
						printf("\n    (         ╔═══════════════════════════════════════════╗         )\n   / (        ║(o_    _______ ______ __   _ _     _    _o)║        ) \\\n  ) ( \\   ⓛⓤⓒ ║//\\    |  |  | |_____ | \\  | |     |    /\\\\║ⓘⓓⓔ    / ) (\n  \\(_)/   ⓢⓣⓔ ║V_/_   |  |  | |_____ |  \\_| |_____|   _\\_V║ⓛⓛⓐ    \\(_)/\n   <─> ╔══════╝───────────────────────────────────────────╚══════╗ <─>\n   / \\ ║                ◅ SCEGLI UNA DIFFICOLTÀ ▻                ║ / \\\n   \\ / ║        ①         ┆        ②          ┆        ③         ║ \\ /\n   / \\ ║      FACILE      │       MEDIA       │     DIFFICILE    ║ / \\\n   \\ / ║  Ogni aiuto ti   │   Ogni aiuto ti   │   Ogni aiuto ti  ║ \\ /\n   / \\ ║ costerà 10 punti,│ costerà 20 punti, │ costerà 50 punti,║ / \\\n   \\ / ║ la traccia potrà │ la traccia potrà  │ la traccia potrà ║ \\ /\n   /_\\ ║  completare al   │   completare al   │  completare al   ║ /_\\\n ╔═════╝massimo il 29%% del│massimo il 21%% del │massimo il 15%% del╚═════╗\n ║           sudoku       ┆      sudoku       ┆      sudoku            ║\n ║                     ◅ Inserisci ⓪  per uscire ▻                     ║\n ║          ╭───────────────────────────────────────────────╮          ║\n ║  .--.    │_______ _     _ ______   _____  _     _ _     _│    .--.  ║\n ║:::::.\\:::│|______ |     | |     \\ |     | |____/  |     |│:::/.:::::║\n ║'      `--│______| |_____| |_____/ |_____| |    \\_ |_____|│--'      '║\n ╚═════════╗╰───────────────────────────────────────────────╯╞═════════╝\n           ╚╡☛ ");
						p=mscanf(0);
					}while(p<0||p>3);
					if(p!=0){
						misc[0]=p*p-8*p+17;
						misc[1]=100;
						load(t,vn,vs,(p+2),0);
						p=10*p*p-20*p+20;
						do{
							move(t,vn,misc,1);
							if(check(t)==1){
								scr=scr+misc[1];
								render(t,vn,misc,1);
								printf(" │                ◅ HAI VINTO ▻                  │\n │ ...Premi un tasto qualsiasi per continuare... │\n ╰───────────────────────────────────────────────╯\n");
								misc[0]=-1;
								n='x';
								getch();
							}
							else{
								render(t,vn,misc,1);
								printf(" │           ◬ Il sudoku è scorretto◬            │\n │ Premi di nuovo Ⓧ  per uscire, Ⓗ  per usare un │\n │  aiuto, qualsiasi altro tasto per continuare  │\n ╰───────────────────────────────────────────────╯\n");
								n=mscanf(1);
								if(n=='h'){
									load(t,vn,vs,0,1);
									misc[0]=misc[0]-1;
									misc[1]=misc[1]-p;
								}
								if(n=='x')
									misc[0]=-1;
							}
						}while(misc[0]>=0);
						if(n!='x'){
							misc[0]=0;
							misc[1]=0;
							for(p=1;p==1;p=load(t,vn,vs,0,1));
							render(t,vn,misc,1);
							printf(" │                ◅ HAI PERSO ▻                  │\n │ ...Premi un tasto qualsiasi per continuare... │\n ╰───────────────────────────────────────────────╯\n");
							getch();
						}
					}
				}
			break;
			
			case 2:
				do{
					printslot(sil);
					printf("       ║                                                         ║\n       ║  Inserisci:          ①  per eliminare uno slot,         ║\n       ║                      ②  per riempire uno slot vuoto,    ║\n       ║                      ⓪  per uscire                      ║\n       ║                                                         ║\n ╔═════╝    ╭───────────────────────────────────────────────╮    ╚═════╗\n ║  .--.    │_______ _     _ ______   _____  _     _ _     _│    .--.  ║\n ║:::::.\\:::│|______ |     | |     \\ |     | |____/  |     |│:::/.:::::║\n ║'      `--│______| |_____| |_____/ |_____| |    \\_ |_____|│--'      '║\n ╚═════════╗╰───────────────────────────────────────────────╯╞═════════╝\n           ╚╡☛ ");
					p=mscanf(0);
					switch(p){
						case 1:
							silect(sil,t,1);
						break;
						case 2:
							silect(sil,t,2);
						break;
					}
				}while(p!=0);
			break;
			
			case 3:
				system("clear");
				printf("\n    (         ╔═══════════════════════════════════════════╗         )\n   / (        ║(o_    _______ ______ __   _ _     _    _o)║        ) \\\n  ) ( \\   ⓛⓤⓒ ║//\\    |  |  | |_____ | \\  | |     |    /\\\\║ⓘⓓⓔ    / ) (\n  \\(_)/   ⓢⓣⓔ ║V_/_   |  |  | |_____ |  \\_| |_____|   _\\_V║ⓛⓛⓐ    \\(_)/\n   <─> ╔══════╝───────────────────────────────────────────╚══════╗ <─>\n   / \\ ║                     ◅ ISTRUZIONI ▻                      ║ / \\\n   \\ / ║                                                         ║ \\ /\n   / \\ ║   Lo scopo del gioco è completare la griglia con dei    ║ / \\\n   \\ / ║   numeri in modo tale che ogni colonna, ogni riga, e    ║ \\ /\n   / \\ ║    ciascuno dei riquadri più piccoli contenga tutti     ║ / \\\n   \\ / ║                   i numeri da 1 a 9.                    ║ \\ /\n   /_\\ ║    Ogni volta che chiedi un aiuto, il tuo punteggio     ║ /_\\\n ╔═════╝  sarà diminuito in base al grado di difficoltà scelta.  ╚═════╗\n ║ Puoi anche salvare un tuo modello di sudoku, il programma genererà  ║\n ║            automaticamente nuove tracce basate su quello.           ║\n ║          ╭───────────────────────────────────────────────╮          ║\n ║  .--.    │_______ _     _ ______   _____  _     _ _     _│    .--.  ║\n ║:::::.\\:::│|______ |     | |     \\ |     | |____/  |     |│:::/.:::::║\n ║'      `--│______| |_____| |_____/ |_____| |    \\_ |_____|│--'      '║\n ╚═════════╡╰───────────────────────────────────────────────╯╞═════════╝\n");
				getch();
			break;

			case 4:
				preload(sil,1);
			break;
		}
	}while(p!=4);
	system("clear");

return 0;
}

char mscanf(int ste){
	char let;
	if(ste==0){
		let=getchar();
		while(getchar()!='\n');
	}
	else
		let=getch();
	if(let>47&&let<58)
		let=let-48;
return let;
}

void render(int t[][9],int vn[],int misc[],int ste){
	int x,y,i;

	system("clear");
	printf(" ╭───────────────────────────────────────────────╮\n │_______ _     _ ______   _____  _     _ _     _│\n │|______ |     | |     \\ |     | |____/  |     |│\n │______| |_____| |_____/ |_____| |    \\_ |_____|│\n ╰───────────────────────┰───────────────────────╯\n       ┏━━━┯━━━┯━━━┳━━━┯━┻━┯━━━┳━━━┯━━━┯━━━┓\n");
	if(ste==0){
		for(y=0;y<9;y=y+1){
			printf("       ");
			for(x=0;x<9;x=x+1){
				if(x%3<1)
					printf("┃");
				else
					printf("│");
				if(t[x][y]==0)
					printf("   ");
				if(t[x][y]==10)
					printf(" # ");
				if(t[x][y]>0&&t[x][y]<10)
					printf(" %d ",t[x][y]);
			}
			if(y<8){
				if((y+1)%3<1)
					printf("┃\n       ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫\n");
				else
					printf("┃\n       ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨\n");
			}
		}
		printf("┃\n       ┗━━━┷━━━┷━━━┻━━━┷━┳━┷━━━┻━━━┷━━━┷━━━┛\n ╭───────────────────────┸───────────────────────╮\n │  Premi Ⓦ  per salire, Ⓢ  per scendere Ⓐ  per  │\n │ scorrere a sinistra, Ⓓ  per scorrere a destra │\n │            Premi Ⓧ  per confermare            │\n");
	}	
	else{
		for(y=0;y<9;y=y+1){
			printf("       ");
			for(x=0;x<9;x=x+1){
				if(x%3<1)
					printf("┃");
				else
					printf("│");
				if(t[x][y]==0)
					printf("   ");
				if(t[x][y]==10)
					printf(" # ");
				if(t[x][y]>0&&t[x][y]<10)
					printf(" %d ",t[x][y]);
			}
			if(y<8){
				if((y%3)>1)
					printf("┃\n       ┣━");
				else
					printf("┃\n       ┠─");
			}
			else
				printf("┃\n       ┗━");
			for(x=0;x<9;x=x+1){
				for(i=0;(vn[i]!=x||vn[i+1]!=y)&&i<170;i=i+2);
				if(i==170){
					if((y%3)>1){
						if(x==4&&y==8)
							printf("┳");
						else
							printf("━");
					}
					else
						printf("─");
				}
				else{
					if((y%3)>1){
						if(x==4&&y==8)
							printf("╈");
						else
							printf("┷");
					}
					else
						printf("┴");
					}
				if(x<8){
					if(y<8){
						if(x%3>1){
							if((y%3)>1)
								printf("━╋━");
							else
								printf("─╂─");
						}
						else{
							if((y%3)>1)
								printf("━┿━");
							else
								printf("─┼─");
						}
					}
					else{
						if(x%3>1)
							printf("━┻━");
						else
							printf("━┷━");
					}
				}
			}
			if(y<8){
				if((y%3)>1)
					printf("━┫\n");
				else
					printf("─┨\n");
			}
			else
				printf("━┛\n");
		}
		printf(" ╭───────────────────────┸───────────────────────╮\n │Il tuo punteggio è [%d], ",misc[1]);
		if(misc[1]<100)
			printf(" ");
		if(misc[1]<10)
			printf(" ");
		printf("Hai ancora [");
		if(misc[0]<10)
			printf("0");
		printf("%d] aiuti│\n │ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯   │\n",misc[0]);
	}
}

int check(int t[][9]){
	int x,y,f,tx,ty,ok=1;
	
	for(y=0;y<9&&ok==1;y=y+1){
		for(f=1;f<10&&ok==1;f=f+1){
			for(x=0;x<9&&t[x][y]!=f;x=x+1);
				if(x==9)
					ok=0;
		}
	}
	for(x=0;x<9&&ok==1;x=x+1){
		for(f=1;f<10&&ok==1;f=f+1){
			for(y=0;y<9&&t[x][y]!=f;y=y+1);
				if(y==9)
					ok=0;
		}
	}
	for(ty=0;ty<9&&ok==1;ty=ty+3){
		for(tx=0;tx<9&&ok==1;tx=tx+3){
			for(f=1;f<10&&ok==1;f=f+1){
				for(y=ty;y<(ty+3);y=y+1){
					for(x=tx;x<(tx+3)&&t[x][y]!=f;x=x+1);
						if(x<(tx+3))
							y=(ty+2);
				}
				if(x==(tx+3))
					ok=0;
			}
		}
	}
return ok;
}

int load(int t[][9],int vn[],int vs[],int dif,int ste){
	int x,y,i,s=0;
	if(ste==0){
		for(y=0;y<9;y=y+1){
			for(i=0;i<(rand()%3)+dif;i=i+1){
				do{
					x=rand()%9;
				}while(t[x][y]==0);
				vs[s]=x;
				vs[s+1]=y;
				vs[s+2]=t[x][y];
				s=s+3;
				t[x][y]=0;
			}
		}
		for(;s<243;vs[s]=-1,s=s+1);
		for(y=0,i=0;y<9;y=y+1){
			for(x=0;x<9;x=x+1){
				if(t[x][y]!=0){
					vn[i]=x;
					vn[i+1]=y;
					i=i+2;
				}
			}
		}
		for(;i<170;vn[i]=-1,i=i+1);
	}
	else{
		for(;vs[s]!=-1;s=s+1);
		if(s>0){
			i=(3*(rand()%(s/3)+1))-3;
			x=vs[i];
			y=vs[i+1];
			t[x][y]=vs[i+2];
			for(;i<240;vs[i]=vs[i+3],i=i+1);
			for(i=0;vn[i]!=-1;i=i+1);
			vn[i]=x;
			vn[i+1]=y;
			/**/s=1;
		}
		else
			s=0;
	}
return s;
}

void move(int t[][9],int vn[],int misc[],int ste){
	int x=0,y=0,i,temp,in;

	temp=t[x][y];
	t[x][y]=10;
	do{
		render(t,vn,misc,ste);
		if(ste==1)
			printf(" │  Premi Ⓦ  per salire, Ⓢ  per scendere Ⓐ  per  │\n │ scorrere a sinistra, Ⓓ  per scorrere a destra │\n │       Premi Ⓧ  per confermare o uscire        │\n");
		printf(" ╰───────────────────────────────────────────────╯\n");
		in=mscanf(1);

		if(in>(-1+ste)&&in<10){
			if(ste==1){
				for(i=0;(vn[i]!=x||vn[i+1]!=y)&&i<170;i=i+2);
				if(i==170){
					temp=in;
					t[x][y]=in;
				}
			}
			else{
				temp=in;
				t[x][y]=in;
			}
		}
		else{
			switch(in){
				case 119:	//w
					t[x][y]=temp;
					y=((y+8)%9);
					temp=t[x][y];
					t[x][y]=10;
					break;
				case 115: 	//s
					t[x][y]=temp;
					y=((y+1)%9);
					temp=t[x][y];
					t[x][y]=10;
					break;
				case 97:	//a
					t[x][y]=temp;
					x=((x+8)%9);
					temp=t[x][y];
					t[x][y]=10;
					break;
				case 100:	//d
					t[x][y]=temp;
					x=((x+1)%9);
					temp=t[x][y];
					t[x][y]=10;
					break;
			}
		}
	}while(in!='x');
	t[x][y]=temp;
}

void preload(int sil[],int ste){
	int i;
	FILE *rf;
	
	if(ste==0){
		rf=fopen("f1.txt","r");
		for(i=0;i<455;i=i+1)
			fscanf(rf,"%d",&sil[i]);
		fclose(rf);
	}
	else{
		rf=fopen("f1.txt","w");
		for(i=0;i<455;i=i+1)
			fprintf(rf,"%d ",sil[i]);
		fclose(rf);
	}
}

int silect(int sil[],int t[][9],int ste){
	int x,y,i=1,s=0,temp;

	for(y=0;y<9;y=y+1){
		for(x=0;x<9;x=x+1,i=i+1)
			t[x][y]=0;
	}
	do{
		printslot(sil);
		switch(ste){
			case 0:
				printf("       ║                                                         ║\n       ║     Inserisci il numero dello slot che vuoi aprire,     ║\n       ║                o inserisci ⓪  per uscire                ║\n");
			break;
			case 1:
				printf("       ║                                                         ║\n       ║   Inserisci il numero dello slot che vuoi cancellare,   ║\n       ║                o inserisci ⓪  per uscire                ║\n");
			break;
			case 2:
				printf("       ║                                                         ║\n       ║    Inserisci il numero dello slot che vuoi riempire,    ║\n       ║                o inserisci ⓪  per uscire                ║\n");
			break;
		}
		if(s==1){
			switch(ste){
				case 0:
					printf("       ║             ◬ lo slot selezionato è vuoto◬              ║\n");
				break;
				case 2:
					printf("       ║           ◬ lo slot selezionato è già in uso◬           ║\n");
				break;
			}
		}
		else
			printf("       ║                                                         ║\n");
		printf("       ║                                                         ║\n ╔═════╝    ╭───────────────────────────────────────────────╮    ╚═════╗\n ║  .--.    │_______ _     _ ______   _____  _     _ _     _│    .--.  ║\n ║:::::.\\:::│|______ |     | |     \\ |     | |____/  |     |│:::/.:::::║\n ║'      `--│______| |_____| |_____/ |_____| |    \\_ |_____|│--'      '║\n ╚═════════╗╰───────────────────────────────────────────────╯╞═════════╝\n           ╚╡☛ ");
		s=mscanf(0);
		if(s>0&&s<6){
			switch(ste){
				case 0:
					i=(91*s)-81;	//((s-1)*81)+(s*10)
					if(sil[i]!=-1){
						for(y=0;y<9;y=y+1){
							for(x=0;x<9;x=x+1,i=i+1)
								t[x][y]=sil[i];
						}
						i=1;
					}
					else
						i=0;
				break;
				case 1:
					i=91*(s-1);
					for(s=i;s<(i+91);s=s+1)
						sil[s]=-1;
					i=1;
				break;
				case 2:
					i=91*(s-1);
					temp=i;
					if(sil[i]==-1){
						do{
							move(t,0,0,0);
							i=/*1;*/check(t);
							if(i==0){
								render(t,0,0,0);
								printf(" │ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯   │\n │           ◬ Il sudoku è scorretto◬            │\n │  Premi di nuovo Ⓧ  per uscire, o qualsiasi    │\n │          altro tasto per continuare           │\n ╰───────────────────────────────────────────────╯\n");
								s=mscanf(1);
								if(s==120)
									i=1;
							}
						}while(i==0);
						if(s!=120){
							i=hazel(sil,t,temp);
							for(y=0;y<9;y=y+1){
								for(x=0;x<9;x=x+1,i=i+1)
									sil[i]=t[x][y];
							}
						}
						i=1;
					}
					else
						i=0;
				break;
			}
			s=1;
		}
		else{
			if(s==0)
				i=1;
			else
				i=0;
			s=0;
		}
	}while(i==0);
return s;
}

void printslot(int sil[]){
	int i,s,x=0;

	system("clear");
	do{
		if(x==0)
			printf("\n       ╔═════════════════════════════════════════════════════════╗\n       ║         ╭──────────╮ ╭──────────╮ ╭──────────╮          ║\n       ║         │ :slot 1: │ │ :slot 2: │ │ :slot 3: │          ║\n       ║         ");
		else
			printf("       ║               ╭──────────╮ ╭──────────╮                 ║\n       ║               │ :slot 4: │ │ :slot 5: │                 ║\n       ║               ");
		for(i=x;i<=(2*x/3)+182;i=i+91){
			if(sil[i]==-1){
				printf("│*vuoto*   │ ");
			}
			else{
				printf("│");
				for(s=i;s<(i+10)&&sil[s]!=-1;s=s+1)
					printf("%c",sil[s]);
				for(;s<(i+10);s=s+1)
					printf(" ");
				printf("│ ");
			}
		}
		if(x==0){
			printf("         ║\n       ║         ╰──────────╯ ╰──────────╯ ╰──────────╯          ║\n");
			x=273;
		}	
		else{
			printf("                ║\n       ║               ╰──────────╯ ╰──────────╯                 ║\n       ╟┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄╢\n");
			x=0;
		}
	}while(x!=0);
}

int hazel(int sil[],int t[][9],int in){
	char c,n[11];
	int i;

	do{
		render(t,0,0,0);
		printf(" │ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯   │\n │   ◅ Inserisci un nome da dare allo slot ▻     │\n │                                               │\n │ ◸     il nome non deve contenere spazi     ◹  │\n │ ◺ il nome non deve superere i ⑩  caratteri ◿  │\n ╰──┬────────────────────────────────────────────╯\n    ╰☛ ");
		scanf("%10s",n);
		c=getchar();
		i=1;
		if(c!='\n'){
			while(getchar()!='\n');
				i=0;
		}
		if(i!=0){
			do{
				render(t,0,0,0);
				printf(" │ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯ ⋯   │\n │  Il nome immesso è ◅ %s ▻  confermi?",n);
				for(i=1;i<10&&n[i]!='\0';i=i+1);
				for(;i<10;i=i+1)
					printf(" ");
				printf("  │\n │                                               │\n │   Premi Ⓢ  per confermare, Ⓝ  per anullare    │\n ╰───────────────────────────────────────────────╯\n");
				c=mscanf(1);
				if(c=='n')
					i=0;
			}while(c!='s'&&c!='n');

		}
	}while(i==0);
	for(i=0;i<10&&n[i]!='\0';sil[in]=n[i],in=in+1,i=i+1);
	for(;i<10;sil[in]=-1,in=in+1,i=i+1);
return in;
}
