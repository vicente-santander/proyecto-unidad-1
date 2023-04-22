#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define M 50
#define N 11

typedef struct guardian{
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;
	struct guardian *next;

}guardian;

typedef struct node {
	guardian *data;
	struct node *next;
} node;



void addNode(node **head, guardian *data) {
	node *newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	if (*head == NULL) {
		*head = newNode;
	} else {
		node *current = *head;
		while (current->next != NULL) {
			current = current->next;
	}
	current->next = newNode;
	}

}

void init(node **head){
	
	FILE *fp = fopen("personaje_init.txt", "r");
	if (fp == NULL) {
		printf("Error al abrir el archivo\n");
		return;
	}
	
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;

	while (fscanf(fp, "%s %s %d %d %d", nombre, tipo, &vida, &p_ataque, &p_defensa) == 5) {
	    guardian *g = malloc(sizeof(guardian));
	    
	    strcpy(g->nombre, nombre);
	   
	    strcpy(g->tipo, tipo);
	   
		g->vida = vida;
	   
	    g->p_ataque = p_ataque;
	    
	    g->p_defensa = p_defensa;
	    
	    addNode(head, g);
	}

	fclose(fp);
}
void freePlayerNodes(node *head) { //free
	node *current = head;
	while (head != NULL) {
		head = head->next;
		free(current->data);
		free(current);
		current = head;
	}
}

void addNodeToPlayer(node **playerHead, guardian *selectedGuardian) {
	node *newNode = malloc(sizeof(node));
	newNode->data = selectedGuardian;
	newNode->next = NULL;
	if (*playerHead == NULL) {
		*playerHead = newNode;
	} else {
		node *current = *playerHead;
		while (current->next != NULL) {
			current = current->next;
	}
	current->next = newNode;
	}
}
void printCharacterStatus(node *playerHead) {
	
	node *current = playerHead;
	
	printf("----------------\n");
	printf("Estado del equipo\n");
	while(current != NULL) {
	
		printf("%s (%s) - Vida: %d, Ataque: %d, Defensa: %d\n", current->data->nombre, current->data->tipo, current->data->vida, current->data->p_ataque, current->data->p_defensa);
		
		current = current->next;
	}
	printf("----------------\n");
}


void selectCharacter(node *head, node **playerHead) {
	node *current = head;
	int var = 1;
	while(var == 1){
		int count = 1;
		current = head;
		
		printf("Personajes disponibles:\n");
		while (current != NULL) {
			printf("%d.- %s (%s) - Vida: %d, Ataque: %d, Defensa: %d\n", count, current->data->nombre, current->data->tipo, current->data->vida, current->data->p_ataque, current->data->p_defensa);
			current = current->next;
			count++;
		}
		int selected;
		printf("Seleccione un personaje por su numero en la lista: ");
		scanf("%d", &selected);
		if (selected < 1 || selected >= count) {
			printf("Seleccion no valida\n\n");
		} else {
			current = head;
			int i = 1;
			while (i < selected) {
				current = current->next;
				i++;
		}
		
		addNodeToPlayer(playerHead, current->data);
		
		printf("Personaje seleccionado: %s (%s)\n", current->data->nombre, current->data->tipo);
		
		var++;
		}	
	}
	
	
}

void createCharacter(node **playerHead){	
	int op;
	int validar1 = 1;
	int validar2 = 2;
	char nombre[M];
	srand(time(NULL));
	
	guardian *p = malloc(sizeof(guardian)); // Reservar memoria para el struct guardian
	
	printf("Indique su nombre el nobre que desea para su guardian:\n");
	
	fflush(stdin); // Limpiar el buffer de entrada porque fgets no funcionar?a despu?s del scanf
	
	scanf("%s",&nombre);
	strcpy(p->nombre, nombre);
	
	while(validar2 == 2)
	{
		printf("?Que tipo de guardian desea crear?\n");
		printf("[1] mage \t[2] viking\n");
		printf("[3] beast \t[4] nigromante\n\n");
		printf("Eleccion:");
		scanf("%d",&op);
		
		switch (op)
		{
			case 1 :
				strcpy(p->tipo, "mage"); // Copiar la cadena "mage" en p->tipo
				p->vida = (400+((rand()%10+1)*10));
				p->p_ataque = (150+((rand()%3+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+30);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;
				break;
				
			case 2 :
				strcpy(p->tipo, "viking"); // Copiar la cadena "vikingo" en p->tipo
				p->vida = (500+((rand()%10+1)*10));
				p->p_ataque = (100+((rand()%5+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+70);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			case 3 :
				strcpy(p->tipo, "beast"); // Copiar la cadena "beast" en p->tipo
				p->vida = (350+((rand()%10+1)*10));
				p->p_ataque = (170+((rand()%3+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+25);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			case 4 :
				strcpy(p->tipo, "nigromante"); // Copiar la cadena "nigromante" en p->tipo
				p->vida = (390+((rand()%10+1)*10));
				p->p_ataque = (100+((rand()%4+1)*10));
				p->p_defensa = (((rand()%5+1)*5)+80);
				printf("-%s --vida %d-- ataque %d--def %d\n",p->tipo, p->vida,p->p_ataque, p->p_defensa);
				addNodeToPlayer(playerHead, p);
				validar2++;	
				break;
				
			default :
				printf("opcion invalida\n");
				break;
		}
				
	}

	
}
	
	
int menuOptions(){
	int opt;
	int validar1 = 1;

	//node *head = NULL; // Cabeza de la cola de personajes disponibles del juego
	//init(&head); // Generar la cola de personajes disponibles
	//node *playerHead = NULL; // Cabeza de la cola de personajes seleccionados por el jugador
	
	while(validar1 == 1)
	{
		printf("?Cuantos jugadores participaran?(max.2)\n");//hacer afuera lo de los jugadores 
		scanf("%d",&opt);
		
		switch(opt)
		{
			case 1 :
				
				validar1++;
				return opt;
				break;
				
			case 2 :
				
				validar1++;
				return opt;
				break;
				
			default:
				
				printf("opcion invalida\n");
				break;
		}
		
	}
}

int selectTournament(){

	int mode;
	int i=0;
	while(i==0){
		printf("-----------Modos de juego------------\n");
		printf("[1]Principiante\n[2]Intermedio\n[3]Experto\n");
		printf("indique el modo de juego:");
		scanf("%d",&mode);
		
		switch(mode){
			case 1 :
				i++;
				break;
			case 2 :
				i++;
				break;
			case 3 :
				i++;
				break; 
			default:
				printf("opcion invalida\n");
				break;
		}	
	}
	return mode;	
}

int getRollResult(){
	srand(time(NULL));
	int result;
	
		result = rand()%6+1;
	
	
	return result;
}
int getRollResult2(){
	//srand(time(NULL));
	int result2;
	int c;

	c = rand()%6+1;
	
	printf("||||%d||||",c);
	
	result2 = c;
	
	
	return result2;
}
void startFight(int mode, guardian **enemies, node *playerHead){
	
	node *enemyHead = NULL; // Cabeza de la lista de enemigos
	node *head = NULL; // Cabeza de la lista de personajes disponibles del juego
	node *current = enemyHead;
	node *actual = playerHead;
	int statvida[2];
	int statdefensa[2];
	int vidaex;
	
	
	srand(time(NULL));
	
	int i, j, k;
	int op;
	int valid, result, result2, turno, damage;
	int dadoEn;
	int minDef = 30;
	
	
	
	
	//---------------------------------------------- copia stat inicial
			
			i = 0;
			int vidasjugadores = 0; // vidas segun cuantos jugadores haya
			actual = playerHead;
			while (actual != NULL) {
				
				statvida[i] = actual->data->vida;
				statdefensa[i] = actual->data->p_defensa;
				
				i++;
				vidasjugadores++;
				actual = actual->next;
			}
	
	
	switch(mode){
		case 1 : //3 enemigos
			
			for(i = 0; i < 3; i++){
				
				j = rand()%26; // NUMERO DE ENEMIGOS
				
				if(strcmp(enemies[j]->nombre, "0") == 0){
					i--;
				}
					
				if(strcmp(enemies[j]->nombre, "0") != 0){ // Si el enemigo no ha sido seleccionado antes
					//printf("-%s-",enemies[j]->nombre);
				
					guardian *enemy = malloc(sizeof(guardian));
					
					strcpy(enemy->nombre, enemies[j]->nombre);
					strcpy(enemy->tipo, enemies[j]->tipo);
					enemy->vida = enemies[j]->vida;
					enemy->p_ataque = enemies[j]->p_ataque;
					enemy->p_defensa = enemies[j]->p_defensa;
				
					addNode(&enemyHead, enemy);
					
					strcpy(enemies[j]->nombre, "0");
				}
				
			}
			
			current = enemyHead;
			k=0;
			printf("Lista de enemigos a enfrentar:\n");
			while (current != NULL) {
				
				printf("-%s", current->data->nombre);
				current = current->next;
				k++;
			}
			 printf("\n");
			 
			
			
			
			//---------------------------------------------- Inicio batalla
			printf("---------------------------------------------%d\n",vidasjugadores);
			current = enemyHead;
			while(current != NULL)
			{
				
				actual = playerHead;
					
				while (actual != NULL) {
					turno = 0;
				 	valid = 1;
				 	
				 	
				 	while(valid == 1 && turno < 2 && vidasjugadores != 0){
					 	printf("\nvs %s\n",current->data->nombre);
					 	
					 	if(actual->data->vida <= 0){
							vidasjugadores--;
						}

						if(actual->data->vida > 0){
							printf("\n%s que accion deseas realizar:\n",actual->data->nombre);
							printf("[1]a}Atacar\n[2]Defender\n[3]Mostrar estado del equipo\n");
							scanf("%d",&op);
							
							result = getRollResult();
							printf("Lanzas el dado y obtienes un %d\n",result);
							
							switch(op){
								case 1:
									
									if(result == 1){
										damage = actual->data->p_ataque * 0.8;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 3){
										damage = actual->data->p_ataque * 1;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 5){
										damage = actual->data->p_ataque * 1.3;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									
									if(result == 6){
										if(turno < 1){
											printf("El ataque fue bloqueado\n");
											printf("a obtenido un turno extra\n");
											turno++;
										}else{
											printf("El ataque fue bloqueado\n");
											valid++;
										}
										
									}
									if(result != 1 && result != 3 && result != 5 && result != 6){
										printf("El ataque fue bloqueado\n");
										valid++;
									}
									
									
									break;
									
								case 2: //defender
									
									if(result == 2){
										vidaex = actual->data->p_defensa * 0.5;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										valid++;
									}
									if(result == 4){
										vidaex = actual->data->p_defensa * 1;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										
										valid++;
									}
									if(result == 6){
										if(turno < 1){
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											printf("a obtenido un turno extra\n");
											
											actual->data->vida = actual->data->vida + vidaex;
											turno++;
										}
										else{
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											
											actual->data->vida = actual->data->vida + vidaex;
											valid++;
										}
									}
									if(result != 2 && result != 4 && result != 6){
										if(minDef < actual->data->p_defensa){
											actual->data->p_defensa = actual->data->p_defensa - (actual->data->p_defensa * 0.05);
											if(minDef > actual->data->p_defensa){
												actual->data->p_defensa = 30;
											}
											printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",actual->data->p_defensa);
											valid++;
										}else{
											printf("no paso nada\n");
										}
										
										
									}
								
									break;
									
								case 3:
									printCharacterStatus(playerHead);
									
									break;
									
								default :
									printf("opcion invalida\n");
									break;
							}
						}
					}
					
					turno = 0;
					valid = 1;
					
					while(valid == 1 && turno < 2 && vidasjugadores != 0){
						
						dadoEn = rand()%2+1;
						
						if(dadoEn == 1){ //ataque
						
							printf("\n\n%s decide atacar\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 1){
								damage = current->data->p_ataque * 0.8;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 3){
								damage = current->data->p_ataque * 1;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 5){
								damage = current->data->p_ataque * 1.3;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
								
							if(result2 == 6){
								if(turno < 1){
									printf("El ataque fue bloqueado\n");
									printf("a obtenido un turno extra\n");
									turno++;
								}else{
									printf("El ataque fue bloqueado\n");
									valid++;
								}
								
							}
							if(result2 != 1 && result2 != 3 && result2 != 5 && result2 != 6){
								printf("El ataque fue bloqueado\n");
								valid++;
							}		
						}
						
						if(dadoEn == 2 ){ //defensa
							printf("%s decide defender\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 2){
								vidaex = current->data->p_defensa * 0.5;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
									
								current->data->vida = current->data->vida + vidaex;
								valid++;
							}
							if(result2 == 4){
								vidaex = current->data->p_defensa * 1;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
																	
								current->data->vida = current->data->vida + vidaex;
										
								valid++;
							}
							if(result2 == 6){
								if(turno < 1){
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									turno++;
								}else{
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									valid++;
								}
							}
							if(result2 != 2 && result2 != 4 && result2 != 6){
								if(minDef < current->data->p_defensa){
									current->data->p_defensa = current->data->p_defensa - (current->data->p_defensa * 0.05);
									if(minDef > actual->data->p_defensa){
										current->data->p_defensa = 30;
									}
									printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",current->data->p_defensa);
									valid++;
								}else{
									printf("no paso nada\n");
								}
							}
						}
					}
					
					
					actual = actual->next;
					if(current->data->vida <= 0){
						printf("has derrotado a %s\n",current->data->nombre);
						current = current->next;
					
					}
					if(vidasjugadores == 0){
						
						current = current->next;
					}
					
				}
				
			}
			//printf("-----------------------------------------------------------------HELL YEAH");
			 
			break;
			
		case 2 : //5 ememigos
		
			for(i = 0; i < 5; i++){
				
				j = rand()%26; // NUMERO DE ENEMIGOS
				
				if(strcmp(enemies[j]->nombre, "0") == 0){
					i--;
				}
					
				if(strcmp(enemies[j]->nombre, "0") != 0){ // Si el enemigo no ha sido seleccionado antes
					//printf("-%s-",enemies[j]->nombre);
				
					guardian *enemy = malloc(sizeof(guardian));
					
					strcpy(enemy->nombre, enemies[j]->nombre);
					strcpy(enemy->tipo, enemies[j]->tipo);
					enemy->vida = enemies[j]->vida;
					enemy->p_ataque = enemies[j]->p_ataque;
					enemy->p_defensa = enemies[j]->p_defensa;
				
					addNode(&enemyHead, enemy);
					
					strcpy(enemies[j]->nombre, "0");
				}
			
			}
			
			current = enemyHead;
			k=0;
			printf("Lista de enemigos a enfrentar:\n");
			while (current != NULL) {
				
				printf("-%s", current->data->nombre);
				current = current->next;
				k++;
			}
			 printf("\n");
			 
			
			
			
			//---------------------------------------------- Inicio batalla
			printf("---------------------------------------------%d\n",vidasjugadores);
			current = enemyHead;
			while(current != NULL)
			{
				
				actual = playerHead;
					
				while (actual != NULL) {
					turno = 0;
				 	valid = 1;
				 	
				 	
				 	while(valid == 1 && turno < 2 && vidasjugadores != 0){
					 	printf("\nvs %s\n",current->data->nombre);
					 	
					 	if(actual->data->vida <= 0){
							vidasjugadores--;
						}

						if(actual->data->vida > 0){
							printf("\n%s que accion deseas realizar:\n",actual->data->nombre);
							printf("[1]a}Atacar\n[2]Defender\n[3]Mostrar estado del equipo\n");
							scanf("%d",&op);
							
							result = getRollResult();
							printf("Lanzas el dado y obtienes un %d\n",result);
							
							switch(op){
								case 1:
									
									if(result == 1){
										damage = actual->data->p_ataque * 0.8;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 3){
										damage = actual->data->p_ataque * 1;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 5){
										damage = actual->data->p_ataque * 1.3;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									
									if(result == 6){
										if(turno < 1){
											printf("El ataque fue bloqueado\n");
											printf("a obtenido un turno extra\n");
											turno++;
										}else{
											printf("El ataque fue bloqueado\n");
											valid++;
										}
										
									}
									if(result != 1 && result != 3 && result != 5 && result != 6){
										printf("El ataque fue bloqueado\n");
										valid++;
									}
									
									
									break;
									
								case 2: //defender
									
									if(result == 2){
										vidaex = actual->data->p_defensa * 0.5;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										valid++;
									}
									if(result == 4){
										vidaex = actual->data->p_defensa * 1;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										
										valid++;
									}
									if(result == 6){
										if(turno < 1){
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											printf("a obtenido un turno extra\n");
											
											actual->data->vida = actual->data->vida + vidaex;
											turno++;
										}
										else{
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											
											actual->data->vida = actual->data->vida + vidaex;
											valid++;
										}
									}
									if(result != 2 && result != 4 && result != 6){
										if(minDef < actual->data->p_defensa){
											actual->data->p_defensa = actual->data->p_defensa - (actual->data->p_defensa * 0.05);
											if(minDef > actual->data->p_defensa){
												actual->data->p_defensa = 30;
											}
											printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",actual->data->p_defensa);
											valid++;
										}else{
											printf("no paso nada\n");
										}
									}
								
									break;
									
								case 3:
									printCharacterStatus(playerHead);
									
									break;
									
								default :
									printf("opcion invalida\n");
									break;
							}
						}
					}
					
					turno = 0;
					valid = 1;
					
					while(valid == 1 && turno < 2 && vidasjugadores != 0){
						
						dadoEn = rand()%2+1;
						
						if(dadoEn == 1){ //ataque
						
							printf("\n\n%s decide atacar\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 1){
								damage = current->data->p_ataque * 0.8;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 3){
								damage = current->data->p_ataque * 1;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 5){
								damage = current->data->p_ataque * 1.3;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
								
							if(result2 == 6){
								if(turno < 1){
									printf("El ataque fue bloqueado\n");
									printf("a obtenido un turno extra\n");
									turno++;
								}else{
									printf("El ataque fue bloqueado\n");
									valid++;
								}
								
							}
							if(result2 != 1 && result2 != 3 && result2 != 5 && result2 != 6){
								printf("El ataque fue bloqueado\n");
								valid++;
							}		
						}
						
						if(dadoEn == 2 ){ //defensa
							printf("%s decide defender\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 2){
								vidaex = current->data->p_defensa * 0.5;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
									
								current->data->vida = current->data->vida + vidaex;
								valid++;
							}
							if(result2 == 4){
								vidaex = current->data->p_defensa * 1;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
																	
								current->data->vida = current->data->vida + vidaex;
										
								valid++;
							}
							if(result2 == 6){
								if(turno < 1){
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									turno++;
								}else{
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									valid++;
								}
							}
							if(result2 != 2 && result2 != 4 && result2 != 6){
								if(minDef < current->data->p_defensa){
									current->data->p_defensa = current->data->p_defensa - (current->data->p_defensa * 0.05);
									if(minDef > actual->data->p_defensa){
										current->data->p_defensa = 30;
									}
									printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",current->data->p_defensa);
									valid++;
								}else{
									printf("no paso nada\n");
								}
							}
						}
					}
					
					
					actual = actual->next;
					if(current->data->vida <= 0){
						printf("has derrotado a %s\n",current->data->nombre);
						current = current->next;
					
					}
					if(vidasjugadores == 0){
						
						current = current->next;
					}
					
				}
				
			}
			
			break;
			
		case 3 : //7 ememigos
			
			for(i = 0; i < 7; i++){
				
				j = rand()%26; // NUMERO DE ENEMIGOS
				
				if(strcmp(enemies[j]->nombre, "0") == 0){
					i--;
				}
					
				if(strcmp(enemies[j]->nombre, "0") != 0){ // Si el enemigo no ha sido seleccionado antes
					//printf("-%s-",enemies[j]->nombre);
				
					guardian *enemy = malloc(sizeof(guardian));
					
					strcpy(enemy->nombre, enemies[j]->nombre);
					strcpy(enemy->tipo, enemies[j]->tipo);
					enemy->vida = enemies[j]->vida;
					enemy->p_ataque = enemies[j]->p_ataque;
					enemy->p_defensa = enemies[j]->p_defensa;
				
					addNode(&enemyHead, enemy);
					
					strcpy(enemies[j]->nombre, "0");
				}
			}
				
			current = enemyHead;
			k=0;
			printf("Lista de enemigos a enfrentar:\n");
			while (current != NULL) {
				
				printf("-%s", current->data->nombre);
				current = current->next;
				k++;
			}
			 printf("\n");
			 
			
			
			
			//---------------------------------------------- Inicio batalla
			printf("---------------------------------------------%d\n",vidasjugadores);
			current = enemyHead;
			while(current != NULL)
			{
				
				actual = playerHead;
					
				while (actual != NULL) {
					turno = 0;
				 	valid = 1;
				 	
				 	
				 	while(valid == 1 && turno < 2 && vidasjugadores != 0){
					 	printf("\nvs %s\n",current->data->nombre);
					 	
					 	if(actual->data->vida <= 0){
							vidasjugadores--;
						}

						if(actual->data->vida > 0){
							printf("\n%s que accion deseas realizar:\n",actual->data->nombre);
							printf("[1]a}Atacar\n[2]Defender\n[3]Mostrar estado del equipo\n");
							scanf("%d",&op);
							
							result = getRollResult();
							printf("Lanzas el dado y obtienes un %d\n",result);
							
							switch(op){
								case 1:
									
									if(result == 1){
										damage = actual->data->p_ataque * 0.8;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 3){
										damage = actual->data->p_ataque * 1;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
									}
									if(result == 5){
										damage = actual->data->p_ataque * 1.3;
										printf("Causo %d de daño al guardian %s\n",damage ,current->data->nombre);
										current->data->vida = current->data->vida - damage; //se aplica daño
										printf("vida actual de %s es de %d\n",current->data->nombre ,current->data->vida);
										valid++;
										
									}
									
									if(result == 6){
										if(turno < 1){
											printf("El ataque fue bloqueado\n");
											printf("a obtenido un turno extra\n");
											turno++;
										}else{
											printf("El ataque fue bloqueado\n");
											valid++;
										}
										
									}
									if(result != 1 && result != 3 && result != 5 && result != 6){
										printf("El ataque fue bloqueado\n");
										valid++;
									}
									
									
									break;
									
								case 2: //defender
									
									if(result == 2){
										vidaex = actual->data->p_defensa * 0.5;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										valid++;
									}
									if(result == 4){
										vidaex = actual->data->p_defensa * 1;
										printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
										
										actual->data->vida = actual->data->vida + vidaex;
										
										valid++;
									}
									if(result == 6){
										if(turno < 1){
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											printf("a obtenido un turno extra\n");
											
											actual->data->vida = actual->data->vida + vidaex;
											turno++;
										}
										else{
											vidaex = actual->data->p_defensa * 1.2;
											printf("se curo un %d su vida actual es %d\n",vidaex ,actual->data->vida);
											
											actual->data->vida = actual->data->vida + vidaex;
											valid++;
										}
									}
									if(result != 2 && result != 4 && result != 6){
										if(minDef < actual->data->p_defensa){
											actual->data->p_defensa = actual->data->p_defensa - (actual->data->p_defensa * 0.05);
											if(minDef > actual->data->p_defensa){
												actual->data->p_defensa = 30;
											}
											printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",actual->data->p_defensa);
											valid++;
										}else{
											printf("no paso nada\n");
										}
									}
								
									break;
									
								case 3:
									printCharacterStatus(playerHead);
									
									break;
									
								default :
									printf("opcion invalida\n");
									break;
							}
						}
					}
					
					
					if(current->data->vida <= 0){
						printf("has derrotado a %s\n",current->data->nombre);
						current = current->next;
					
					}
					
					turno = 0;
					valid = 1;
					while(valid == 1 && turno < 2 && vidasjugadores != 0){
						
						dadoEn = rand()%2+1;
						
						if(dadoEn == 1){ //ataque
						
							printf("\n\n%s decide atacar\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 1){
								damage = current->data->p_ataque * 0.8;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 3){
								damage = current->data->p_ataque * 1;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
							if(result2 == 5){
								damage = current->data->p_ataque * 1.3;
								printf("Causo %d de daño al guardian %s\n",damage ,actual->data->nombre);
								actual->data->vida = actual->data->vida - damage; //se aplica daño
								printf("vida actual de %s es de %d\n",actual->data->nombre ,actual->data->vida);
								valid++;
							}
								
							if(result2 == 6){
								if(turno < 1){
									printf("El ataque fue bloqueado\n");
									printf("a obtenido un turno extra\n");
									turno++;
								}else{
									printf("El ataque fue bloqueado\n");
									valid++;
								}
								
							}
							if(result2 != 1 && result2 != 3 && result2 != 5 && result2 != 6){
								printf("El ataque fue bloqueado\n");
								valid++;
							}		
						}
						
						if(dadoEn == 2 ){ //defensa
							printf("%s decide defender\n",current->data->nombre);
							result2 = getRollResult2();
							printf("lanza el dado y obtiene un %d\n",result2);
							
							if(result2 == 2){
								vidaex = current->data->p_defensa * 0.5;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
									
								current->data->vida = current->data->vida + vidaex;
								valid++;
							}
							if(result2 == 4){
								vidaex = current->data->p_defensa * 1;
								printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
																	
								current->data->vida = current->data->vida + vidaex;
										
								valid++;
							}
							if(result2 == 6){
								if(turno < 1){
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									turno++;
								}else{
									vidaex = current->data->p_defensa * 1.2;
									printf("se curo un %d su vida actual es %d\n",vidaex ,current->data->vida);
											
									current->data->vida = current->data->vida + vidaex;
									valid++;
								}
							}
							if(result2 != 2 && result2 != 4 && result2 != 6){
								if(minDef < current->data->p_defensa){
									current->data->p_defensa = current->data->p_defensa - (current->data->p_defensa * 0.05);
									if(minDef > actual->data->p_defensa){
										current->data->p_defensa = 30;
									}
									printf("Se a desgastado la defensa un 5%s la defensa actual es %d\n","%",current->data->p_defensa);
									valid++;
								}else{
									printf("no paso nada\n");
								}
							}
						}
					}
					
				
					actual = actual->next;
					
					if(vidasjugadores == 0){
						
						current = current->next;
					}
					
				}
				
			}	
			 
			break; 
	}
	
	i=0;
	actual = playerHead;
	while (actual != NULL) { 
		
		if(vidasjugadores == 0){
			printf("has perdido\n");
			break;
		}else{						// la opcion continuar solo funciona con 1 jugador
			
			i=0;
			actual->data->vida = statvida[i];
			actual->data->p_defensa = statdefensa[i];
			//printf("%d vida---%d defensa",actual->data->vida ,actual->data->p_defensa);
			i++;
			
			break;
		}
		
	}
	

	actual = playerHead;
	while (actual != NULL) { 
		
		if(vidasjugadores != 0){
			printf("menu\n");
			printf("[1]principiante [2]intermedio [3] experto [0]salir\n");	
			printf("seleccion:");
			scanf("%d",&mode);
			if(mode == 1 || mode == 2 || mode == 3){
				startFight(mode,enemies,playerHead); //funcion volver a empezar
			}else{
				break;
			}
		}else{
			break;
		}
	}
	
	printf("end\n");
}


void initEnemy(guardian **enemies) {
	FILE *fp = fopen("personaje.txt", "r");
	if (fp == NULL) {
		printf("Error al abrir el archivo\n");
		return;
	}
	char nombre[M];
	char tipo[N];
	int vida;
	int p_ataque;
	int p_defensa;
	int i = 0;
	while (fscanf(fp, "%s %s %d %d %d", nombre, tipo, &vida, &p_ataque, &p_defensa) == 5) {
		guardian *e = malloc(sizeof(guardian));
		
		strcpy(e->nombre, nombre);
		strcpy(e->tipo, tipo);
		e->vida = vida;
		e->p_ataque = p_ataque;
		e->p_defensa = p_defensa;
		
		enemies[i] = e;
		
		//printf("%d-(%s)-",i,enemies[i]->tipo);
		
		i++;
	}
	fclose(fp);
}


int main(){
	int mode;
	int opt;
	int validar2 = 2;
	int validar = 0;
	int creation;
	srand(time(NULL));
	
	guardian *enemies[26];
	printf("The Guardians Tournament\n");
	
	
	node *enemyHead = NULL;
	node *head = NULL; // Cabeza de la cola de personajes disponibles del juego
	init(&head); // Generar la cola de personajes disponibles
	node *playerHead = NULL; // Cabeza de la cola de personajes seleccionados por el jugador	
	node *current = enemyHead;
	node *actual = playerHead;

	opt = menuOptions();
	//printf("-------%d--------",opt);

	switch(opt)
	{
		
		case 1 :
			while(validar2 == 2)
				{
				
					printf("Desea crear un personaje o usar uno predeterminado?\n");
					printf("[1] Crear\t[2] Predeterminado\n");
					scanf("%d",&creation);
					
					switch(creation)
					{
						case 1 :
							
							createCharacter(&playerHead);
							validar2++;
							break;
							
						case 2 :
							
							selectCharacter(head, &playerHead);
							validar2++;
							break;
		
						default:
						
							printf("opcion invalida");
							break;
					}	
				}
			break;
			
		case 2 :
			
			while(validar < 2)
			{
				printf("Desea crear un personaje o usar uno predeterminado?\n");
				printf("[1] Crear\t[2] Predeterminado\n");
				scanf("%d",&creation);
						
				switch(creation)
				{
					case 1 :
						
						createCharacter(&playerHead);
						validar++;
						break;
							
					case 2 :
							
						selectCharacter(head, &playerHead);
						validar++;
						break;
		
					default:					
							
						printf("opcion invalida");					
						break;
				}	
				
			}
			break;
	}
	
	printCharacterStatus(playerHead);
	
	mode = selectTournament();
	
	
	initEnemy(enemies); 
	
	startFight(mode,enemies,playerHead);


	actual = playerHead;
	while (actual != NULL) { //liberar la memoria de los que perdieron
		node *temp1 = actual;
		actual = actual->next;
		free(temp1->data);
		free(temp1);
	}
							
	current = enemyHead;
	while (current != NULL) { //liberar la memoria de los enemigos que perdieron
		node *temp = current;
		current = current->next;
		free(temp->data);
		free(temp);
	}
	
	
	printf("adios");
	
	return 0;
}
