#ifndef INICIO_H
#define INICIO_H
	
	struct node{
		struct node* sig;
		int y;
		int* barco;
	};
	
	struct list{
		struct node* list;
		int largo;
	};
	
	void construir(struct list**, int[2][10][10]);
	
	void init(struct list**, struct list**, int[2][10][10], int[2][10][10]);
	
	
#endif //INICIO_H