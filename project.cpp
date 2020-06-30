#include <stdio.h> 
#include <limits.h>     
#define V 14

int dist[V]; //���ͽ�Ʈ�� �̿�� �迭 ���� 
int src, loc, nel; //�������� ���� 


int graph[V][V] = {
	{0,4,0,0,0,0,0,0,0,4,0,0,0,1}, 
   {4,0,2,0,0,0,0,0,0,3,0,0,0,0},
   {0,2,0,2,0,0,0,0,0,0,0,0,0,0},
   {0,0,2,0,1,0,0,0,0,0,0,0,0,0},
   {0,0,0,1,0,1,0,0,4,0,0,0,0,0},
   {0,0,0,0,1,0,1,0,0,0,0,0,0,0},
   {0,0,0,0,0,1,0,2,0,0,0,0,0,0},
   {0,0,0,0,0,0,2,0,3,0,0,0,0,0},
   {0,0,0,0,4,0,0,3,0,4,0,0,0,0},
   {4,3,0,0,0,0,0,0,4,0,2,0,2,0},
   {0,0,0,0,0,0,0,0,0,2,0,1,0,0},
   {0,0,0,0,0,0,0,0,0,0,1,0,1,0},
   {0,0,0,0,0,0,0,0,0,2,0,1,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,1,0}
                     };  
	//�� ������ �ʱⰪ 

int minDistance(int dist[], bool sptSet[]);
void oneday(int graph[V][V], int dist[]);
void otday(int graph[V][V], int dist[], int nel);
void ttday(int graph[V][V], int dist[]);
void dijkstra(int graph[V][V], int src);
void minfind(int graph[V][V], int dist[]);
void reco(int nel);
void recloc(int nel);
//�Լ����� 

int main() 
{   
	int day;
   printf("\n\n1.���� 2.���� 3. ���� 4. ����\n\n5.��� 6. ���� 7. �뿵 8. �λ�\n\n9.�뱸 10.�ܾ� 11.���� 12.����\n\n13.��õ 14.����\n\n");
   printf("���� ��ġ�� �Է��ϼ���(���� �� ���� ����� ���� ����) : ");
   scanf("%d",&loc); //���� ��ġ ���� 
   printf("\n"); 
   
   if(loc > 14) { //�Է��� 14 �̻� �ϸ� �ٽ� �Է��ϵ��� ���� 
   	printf("�ٽ� �Է��ϼ���. \n");
   	printf("\n");
   	printf("���� ��ġ�� �Է��ϼ���(���� �� ���� ����� ���� ����) : ");
   	scanf("%d",&loc);
   	printf("\n");
   }
   
   printf("1. ����ġ�� 2. 1��2�� 3. 2��3��\n\n");
   printf("���Ͻô� ����Ⱓ�� �Է��ϼ���: ");
   scanf("%d",&day); //���ϴ� ����Ⱓ ����
   printf("\n"); 
   
   if(day > 3) { //�Է��� 3 �̻��̸� �ٽ� �Է��ϵ��� ���� 
   	printf("�ٽ� �Է��ϼ���. \n");
   	printf("\n");
   	printf("���Ͻô� ����Ⱓ�� �Է��ϼ���: ");
   	scanf("%d",&day);
   	printf("\n");
   }
   
   if(day==1) oneday(graph,dist); //����ġ�� ���ý� oneday �Լ��� �Ѿ 
   else if(day==2) otday(graph,dist,nel); //1�� 2�� ���ý� otday �Լ��� �Ѿ 
   else if(day==3) ttday(graph,dist); //2�� 3�� ���ý� ttday �Լ��� �Ѿ 


    return 0; 
} 

int minDistance(int dist[], bool sptSet[]) //�ּҰŸ��� ���� �ε����� ���ϴ� �Լ� 
{ 
  
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) //�湮���� �ʾҰ�, �迭�� ���� min������ ������� 
         min = dist[v], min_index = v;  //�湮�� ���� min ���� �ǰ�, �湮�� ���� index�� min_index 
   
   return min_index; //min_index ��ȯ 
} 

void minfind(int graph[V][V], int dist[]){ //1��2�Ͽ� �̿�� ���� ����� ����Ž�� �Լ� 
	
	int min = dist[0];
	int i,k;
	
	for(i = 1; i<V ; i++){
		if((dist[i] < min) && (dist[i]>0)){ //�ּҰŸ��� 0�ΰ��� ���õ� �����̱� ������ 0�̻��� ���� �� �ּҰ� 
			min = dist[i]; 
			k = i+1;  
		}
	}
	
	printf("\n���� ��õ ����(�Ÿ� ����): ");
	recloc(k); 
	reco(k); //���� ����� ������ ��õ�ڽ� �ҷ��� 
	
}

void oneday(int graph[V][V], int dist[]){ //����ġ�� �Լ� 
   
   dijkstra(graph, loc-1); //������������ ���������� �ּҰŸ� ���ϱ� 
    
   for(int i=0; i<V; i++)
      if(dist[i]==2) //���� �������� �ּҰŸ� 2�� �� ��õ 
         nel = i;
   
   printf("��õ ����: ");
   recloc(nel+1); //dist�� 0���� �����ϰ� �������� 1���� �����ϱ� ������ +1�� �ؼ� �ҷ��� 
    printf("\n"); 
   reco(nel+1);
   printf("\n"); 
}

void otday(int graph[V][V], int dist[], int nel) //1�� 2�� �Լ� 
{ 	
	dijkstra(graph, loc-1); //dijkstra ȣ�� �� ���� �������� �ּ� �Ÿ� ���� 
	
	for(int i=0; i<V; i++){
		if(dist[i] == 3){ //���� ������ �ּҰŸ��� 3�� �Ÿ��� ��� 
			nel = i;
		}
	}
	
	printf("��õ ����: ");
	recloc(nel+1);	//dist�� 0���� �����ϰ� �������� 1���� �����ϱ� ������ +1�� �ؼ� �ҷ��� 
	reco(nel+1);
	printf("\n"); 
	
	dijkstra(graph, nel);	//��õ������ ���� �������� ���� �� ��õ�������� dijkstra ȣ�� 
	printf("\n"); 
	minfind(graph, dist); //���� �������� ����� ���� ã�� 

} 
void ttday(int graph[V][V], int dist[]){ // 2��3���� �� ���� �Լ� 
   
   int num, sty, els; // ���� ���� (num:��õ���� �� ���� �����ϴ� ����, sty:�׸��� ���� ����, els:  
   int count=0; // count ���� 0���� ���� 
   int itemp=0; // itemp ���� 0���� ����  
   int thm[V]={1,1,1,2,2,3,3,2,3,3,2,1,2,3}; //�׸��� ��Ÿ���� �Լ� (1: ������ ����, 2: ������ ����, 3:��Ƽ��Ƽ�� ����) 
   
   printf("1.���� 2.���� 3.��Ƽ��Ƽ\n\n"); // �׸� ���� ��� 
   printf("���ེŸ���� �Է��ϼ���: ");  
   scanf("%d",&sty); // ���� �׸� �Է� 
   printf("\n"); 
   dijkstra(graph, loc-1); // ���ͽ�Ʈ�� �Լ��� �̿��Ͽ� ���� ��ġ�� �ٸ� ���������� �Ÿ� ���� 
   
   if(sty==1){ // �׸��� 1�� �������� ������ ��� 
         for(int i=0;i<V;i++){ // for���� �̿��Ͽ� i�� 0���� V���� ������Ŵ 
           if(thm[i]==2||thm[i]==3){ // �׸��� 2�������̰ų� 3����Ƽ��Ƽ�� ��� 
               thm[i]=itemp; // �׸��� 2or 3�̸� thm���� 0���� ���� 
               dist[i]=thm[i]; // �� ���������� �Ÿ����� ����,��Ƽ��Ƽ �����̸� 0���� ���� 
             }
         }
         for(int i=0;i<V;i++){ // for���� �̿��Ͽ� i�� 0���� V���� ������Ŵ 
           if(dist[i]>=5){ // ����� dist�迭���� 5�̻��� ��� 
              printf("��õ ����: (%d��) ",i+1); // �� ġ�� ��� 
              els=i; 
            recloc(i+1); // ��õ������ ��Ÿ���� �Լ� reloc�� �θ� 
            reco(i+1); // ��õ�ڽ��� ���³��� �Լ� reco�� �θ�
			printf("\n\n");   
            count++; //count�� 1 ������Ŵ 
            }
        }
      
      if(count>=2){ // count�� ���� 2 �̻��̸� (count ���� 1�� ��� ���� �ϳ��� ���ͼ� ��������) 
         printf("\n���ϴ� ������ �Է��ϼ���: "); 
            scanf("%d",&num); // ��õ���� ������ �� ���ϴ� ���� ���� 
            dijkstra(graph,num-1); // ���ϴ� ������ �� ������ �Ÿ��� ����  
            minfind(graph,dist); // ���� ����� ���� ����
			printf("\n");  
      }
      else{
         dijkstra(graph,els+1); //��õ ������ 1����� �� �������� �ٷ� ���ͽ�Ʈ�� ȣ�� 
         minfind(graph,dist); // ���� ����� ���� ���� 
      }
      
      
   }
   
   else if(sty ==2 ){ // �׸��� 2�� �������� ������ ��� 
      
      for(int i=0;i<V;i++){ //for���� �̿��Ͽ� i�� 0���� V���� ������Ŵ 
         if(thm[i]==1||thm[i]==3){ // �׸��� 1�������̰ų� 3����Ƽ��Ƽ�� ���
            thm[i]=itemp; // �׸��� 1or 3�̸� thm���� 0���� ���� 
            dist[i]=thm[i]; // �� ���������� �Ÿ����� ����,��Ƽ��Ƽ �����̸� 0���� ����
            }     
      }
      for(int i=0;i<V;i++){ // sty 1�� ���� 
         if(dist[i]>=6){
            printf("��õ ����: (%d��) ",i+1);
          recloc(i+1);
          reco(i+1);
          els=i;
		  printf("\n\n");   
          count++;
          
       }
      }   
      if(count>=2){ // sty 1�� ���� 
         printf("���ϴ� ������ �Է��ϼ���: "); 
            scanf("%d",&num);
            dijkstra(graph,num-1);
            minfind(graph,dist);
            printf("\n");  
      }
      else{
         dijkstra(graph,els);
         minfind(graph,dist);
      }
   }
   
   else if(sty==3){ // �׸��� 3�� ��Ƽ��Ƽ�� ������ ��� 
      for(int i=0;i<V;i++){ //for���� �̿��Ͽ� i�� 0���� V���� ������Ŵ 
      if(thm[i]==1||thm[i]==2){ // �׸��� 1�������̰ų� 2������ ���
         thm[i]=itemp; // �׸��� 1or 3�̸� thm���� 0���� ���� 
            dist[i]=thm[i]; // �� ���������� �Ÿ����� ����,��Ƽ��Ƽ �����̸� 0���� ����
         }
      }
   for(int i=0;i<V;i++){ // sty 1�� ���� 
      if(dist[i]>=6){
            printf("��õ ����: (%d��) ",i+1);
          recloc(i+1);
          reco(i+1);
          els=i;
          printf("\n\n");  
          count++;
      }
   }
      if(count>=2){ // sty 1�� ���� 
         printf("���ϴ� ������ �Է��ϼ���: "); 
            scanf("%d",&num);
            dijkstra(graph,num-1);
            minfind(graph,dist);
            printf("\n");  
      }
      else{
         dijkstra(graph,els);
         minfind(graph,dist);
      }
   }
}
void recloc(int nel){ //��õ ������ �� �Լ����� ȣ�� �Ҽ��ֵ��� �Լ��� ���� ����� �� 
	switch(nel) {
		case 1 : printf("����\n"); break;
		case 2 : printf("����\n"); break;
		case 3 : printf("����\n"); break;
		case 4 : printf("����\n"); break;
		case 5 : printf("���\n"); break;
		case 6 : printf("����\n"); break;
		case 7 : printf("�뿵\n"); break;
		case 8 : printf("�λ�\n"); break;
		case 9 : printf("�뱸\n"); break;
		case 10 : printf("�ܾ�\n"); break;
		case 11 : printf("����\n"); break;
		case 12 : printf("����\n"); break;
		case 13 : printf("��õ\n"); break;
		case 14 : printf("����\n"); break; 
		
		default : printf("�ٽ� �Է��ϼ���. \n"); break;
	}
}

void reco(int nel){ //��õ �ڽ��� �� �Լ����� ȣ�� �Ҽ� �ֵ��� �̸� ����� �� 
	printf("\n"); 
	switch(nel) {
		case 1 : printf("��õ �ڽ�1 : ��ȭ ���з� - �λ絿 ������ - ���� �ѿ����� - �溹�� - �Ѱ�����\n\n��õ �ڽ�2: �Ե�����-����Ѱ�����\n"); break;
		case 2 : printf("��õ �ڽ�: �ѹ����� - ������ �̼��� - ���ɴ�ζ�� - ���ɴ� - ������Į����\n"); break;
		case 3 : printf("��õ �ڽ�: �ѿ����� - �������� - û��� - ���ν��� \n"); break;
		case 4 : printf("��õ �ڽ�: ����극�Ϲ���ũ - ��ϸ��� - �����ϴø��� - ����������\n"); break;
		case 5 : printf("��õ �ڽ�: �����Ÿ� - �׳�� - �������� - ��Ÿ�����̾�� - ��Ÿ���ι潺\n"); break;
		case 6 : printf("��õ �ڽ�: �ػ����̺�ī - ������ - ����Ƹ��� - õ�纮ȭ���� - ���������Ÿ�\n"); break;
		case 7 : printf("��õ �ڽ�1 : ���Ƕ���ȭ���� - ��ī�̶��� ���� - ��庥óŸ��\n\n��õ �ڽ�2: ������\n"); break;
		case 8 : printf("��õ �ڽ�: ��õ��ȭ���� - �����򿩿�� - ����߽��� - ���ȴ뱳 - �ؿ��\n"); break;
		case 9 : printf("��õ �ڽ�1 : �뱸�̿���-��â�Ÿ�\n\n��õ �ڽ�2: �豤���Ÿ� - �ٴ빮ȭ��� - �����߽���\n"); break;
		case 10 : printf("��õ �ڽ�: �з��۶��̵� - ������ - �̳��ͳ�\n"); break;
		case 11 : printf("��õ �ڽ�: ������- �����غ� - ������ - ����ɾ綼���� - �ȸ��غ�Ŀ�ǰŸ� - �߾ӽ���\n"); break;
		case 12 : printf("��õ �ڽ�: ����ȣ - �����߾ӽ��� - ������ - �ƹ��� ���� - ���� �ؼ����� - ����ī����\n"); break;
		case 13 : printf("��õ �ڽ�: �Ҿ簭��ī�̿�ũ - ���丮�� - ������������ - �߰�����\n"); break;
		case 14 : printf("��õ �ڽ�1: ���̼� - ���̵尡������\n\n��õ �ڽ�2: ķ������Ϸ���\n"); break; 
		
		default : printf("�ٽ� �Է��ϼ���. \n"); break;
	}
}
void dijkstra(int graph[V][V], int src) //���ͽ�Ʈ�� �ִܰŸ� ���ϴ� �Լ� 
{  
   
     bool sptSet[V];  
     
     for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; //�ʱⰪ ���� 
     dist[src] = 0;    //���ڷ� ���� src�� dist �� 0���� ���� 
     
	 for (int count = 0; count < V-1; count++){  
       int u = minDistance(dist, sptSet); //u�� �ּҰŸ��� ���� �ε���  
       sptSet[u] = true; //�湮�� ���� �湮�� ������ ǥ�� 
       
       for (int v = 0; v < V; v++) 
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]) //graph[u][v]�� �湮���� �ʾҰ�, MAX ���� �ƴ� dist[u]��, �Ÿ��� �� ª���� 
            dist[v] = dist[u] + graph[u][v]; //���� �Ÿ��� �ּ� �Ÿ��� ���� 
     } 
}


