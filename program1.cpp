#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

/* Kuyruk yap�s�n�n d���m yap�s� */
typedef struct node{
    int no; /* M��teri numaras� */
    int processTime; /* M��terinin i�lem s�resini tutan de�i�ken */
    struct node* next; /* Kendinden sonra s�raya gelen m��teriyi g�steren pointer */
}Node;

/* Kuyruk yap�s� */
typedef struct queue{
    Node* head;
    Node* last; /* Kuyru�un ba��n� ve sonunu g�steren pointerlar */
    int processTimeSum; /* Kuyrukta m��terilerin harcad��� toplam i�lem s�resi */
    int no; /* Genel m��teri numaras� */
}Queue;

int randProcessTime(void);
Node* newNode(void);
Queue* newQueue(void);
bool emptyQueue(Queue*);
void addNodeToQueue(Node*,Queue*);
Node* popNodeFromQueue(Queue*);
void clearQueue(Queue*);
void averageOfProcessTime(Queue*);

int main(void){
    int select;
    int n;
    Queue* newQueuex=newQueue();
    Node* newNodex;
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
                    newNodex=newNode();
                    for(int i=0;i<600000000;i++); /* Bu sat�r randomize sayinin �retilebilmesi i�in zaman ge�iriyor */
                    addNodeToQueue(newNodex,newQueuex);
                    n--;
                }
                break;
            case 2:
                clearQueue(newQueuex);
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
    newNode->no=0;
    newNode->processTime=0;
    newNode->next=NULL;
    return newNode;
}

/* Kuyruk yap�s� olu�turma fonksiyonu */
Queue* newQueue(void){
    Queue* newQueue=(Queue*)malloc(sizeof(Queue));
    newQueue->head=NULL;
    newQueue->last=NULL;
    newQueue->no=0;
    newQueue->processTimeSum=0;
    return newQueue;
}

/* Kuyru�un bo� olup olmad���n� kontrol eden fonksiyon */
bool emptyQueue(Queue* queue){
    if(queue->head==NULL)
        return true;
    else
        return false;
}

/* Kuyruk yap�s�na yeni bir d���m ekleme fonksiyonu */
void addNodeToQueue(Node* newNode,Queue* queue){
    queue->no+=1; /* Genel m��teri numaras�n�n bir arttt�r�lmas� */
    if(emptyQueue(queue)){
        queue->head=newNode; /* E�er kuyruk bo� ise kuyru�un ba��na yeni eleman�n adresinin atanmas� */
    }
    else{
        queue->last->next=newNode; /* Kuyru�un son m��terisinden sonra gelecek m��terinin adresinin atanmas� */
    }
    queue->last=newNode; /* Kuyru�un sonuna son gelen m��teri atanmas� */
    newNode->no=queue->no; /* M��teri numaras�n�n atanmas� */
    newNode->processTime=randProcessTime(); /* M��terinin i�lem s�resi hesaplanmas� */
    if(queue->no==1){
        queue->processTimeSum+=newNode->processTime;
        return;
    }
    queue->processTimeSum+=newNode->processTime; /* Toplam kuyrukta ge�irilen vaktin hesaplanmas� */
    newNode->processTime=queue->processTimeSum; /* Yeni m��terinin i�lem s�resi dahil kuyrukta ge�irdi�i s�renin hesaplanmas� */
}

/* Kuyruktan eleman ��karma ve ��kar�lan eleman� d�nd�ren fonksiyon */
Node* popNodeFromQueue(Queue* queue){
    Node* returnNode;
    if(emptyQueue(queue)){ /* E�er kuyruk bo�sa i�lem yap�lmadan null d�ner */
        printf("Queue is empty!\n");
        return NULL;
    }
    returnNode=queue->head;
    queue->head=queue->head->next; /* Listenin ba��na kuyrukta i�i biten m��terinden sonra gelen m��terinin atanmas� */
    return returnNode;
}

/* Kuyru�u bo�altan ve her bir m��terinin kuyrukta harcad�klar� s�reyi g�steren fonksiyon */
void clearQueue(Queue* queue){
    if(emptyQueue(queue)){
        printf("Queue is empty already!\n\n");
        return;
    }
    Node* temp;
    while(!emptyQueue(queue)){
        temp=popNodeFromQueue(queue);
        printf("The time the %d. customer spent in the queue: %d second.\n",temp->no,temp->processTime);
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
