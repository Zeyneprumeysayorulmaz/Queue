/*
Her bir dizi eleman� kendi i�lem s�relerini tutmaktad�r.
Kuyrukta tan�mlanan no de�i�keni dizinin indexlerine ula�makta kullan�lmaktad�r.
clearQueue() fonksiyonundan sonra dizi varsay�lan de�erlerine d�nd�r�lm�� ve tekrar kullan�ma haz�r hale gelmi�tir.
MAX sabiti dizinin boyutunu belirlemekle beraber arzulara ba�l� daha uzun veya daha k�sa kuyruklar olu�turulabilinir.
*/

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

#define MAX 5

/* Kuyruk yap�s�n�n d���m yap�s� */
typedef struct node{
    int array[MAX];
}Node;

/* Kuyruk yap�s� */
typedef struct queue{
    int head; /* Kuyru�un ilk eleman�n�n numaras�n� tutan de�i�ken */
    int last;
    int processTimeSum; /* Kuyrukta ge�irilen toplam i�lem s�resi */
    int no; /* Kuyruk �zerinde dola�mam�z� sa�layan de�i�ken */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Queue* queue,Node* node);
int popNodeFromQueue(Queue* queue,Node* node);
void clearQueue(Queue* queue,Node* node);
void averageOfProcessTime(Queue* queue);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex=newNode();
    printf("Welcome to Bank");
    while(1){
        printf("\n\n1: Add \"n\" customer\n2: The time the customers spend on the queue\n3: Average process time\n\nPlease select your process: ");
        scanf("%d",&select);
        printf("\n\n");
        switch(select){
            case 1:
                printf("How many customer in the queue?\nChoose: ");
                scanf("%d",&n);
                while(n>0){
                    for(int i=0;i<600000000;i++); /* Bu sat�r randomize sayinin �retilebilmesi i�in zaman ge�iriyor */
                    addNodeToQueue(newQueuex,newNodex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex,newNodex);
                break;
            case 3:
                averageOfProcessTime(newQueuex);
                break;
            default :
                printf("Wrong choose!\n");
                break;
        }
    }
    return 0;
}

/* Rastgele i�lem s�resini hesaplayan fonksiyon */
int randProcessTime(void){
    srand(time(NULL));
    int x=rand()%270+30;
    return x;
}

/* Dugum olu�turma fonksiyonu */
Node* newNode(void){
    Node* newNode=(Node*)malloc(sizeof(Node));
    int n=0;
    while(n<MAX){ /* Dizideki elemanlara varsay�lan 0 de�eri atand� */
        newNode->array[n]=0;
        n++;
    }
    return newNode;
}

/* Kuyruk yap�s� olu�turma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=-1;
    newQueue->last=-1;
    newQueue->processTimeSum=0;
    newQueue->no=-1;
    return newQueue;
}

/* Kuyru�un bo� olup olmad���n� kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(!(queue->head>=-1 && queue->head<5))
    return true;
    else
    return false;
}

/* Kuyruk yap�s�na yeni bir d���m ekleme fonksiyonu */
void addNodeToQueue(Queue* queue,Node* node){
    queue->no++;
    if(queue->no==MAX){ /* Kuyru�un full olma durumu */
        printf("Queue is full, the transaction has not been approved!\n");
        queue->no--;
        return;
    }
    if(queue->no==0){
        queue->head=queue->no;
    }
    queue->last=queue->no;
    node->array[queue->no]=randProcessTime();
    if(queue->no==0){ /* Kuyru�a eklenen ilk elemana �zel s�re� */
        queue->processTimeSum+=node->array[queue->no];
        return;
    }
    queue->processTimeSum+=node->array[queue->no];
    node->array[queue->no]=queue->processTimeSum;
}

/* Kuyruktan eleman ��karma ve ��kar�lan eleman�n i�lem s�resini d�nd�ren fonksiyon */
int popNodeFromQueue(Queue* queue,Node* node){
    if(emptyQueue(queue)){ /* E�er kuyruk bo�sa i�lem yap�lmadan -1 d�ner */
        printf("Queue is empty!\n");
        return -1;
    }
    int data=node->array[queue->head];
    queue->head++;
    return data;
}

/* Kuyru�u bo�altan ve her bir m��terinin kuyrukta harcad�klar� s�reyi g�steren fonksiyon */
void clearQueue(Queue* queue,Node* node){
    int temp;
    while(!(queue->head==MAX+1)){
        temp=popNodeFromQueue(queue,node);
        if(temp==-1){ /* D�nen de�er -1 ise kuyruk bo�alt�lm��t�r fonksiyondan ��k�lacakt�r */
            queue->head=-1;
            queue->last=-1;
            queue->no=-1;
            queue->processTimeSum=0;
            return;
        }
        printf("The time the %d. customer spent in the queue: %d second.\n",queue->head,temp);
    }
}

/* Kuyrukta ge�irilen ortalama i�lem s�resini g�steren fonskiyon */
void averageOfProcessTime(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty!\n\n");
        return;
    }
    int average=queue->processTimeSum/queue->no;
    printf("Avarege process time in the queue: %d second.\n",average);
}
