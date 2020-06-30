#include <stdio.h> 
#include <limits.h>     
#define V 14

int dist[V]; //다익스트라에 이용될 배열 선언 
int src, loc, nel; //전역변수 선언 


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
	//각 지역별 초기값 

int minDistance(int dist[], bool sptSet[]);
void oneday(int graph[V][V], int dist[]);
void otday(int graph[V][V], int dist[], int nel);
void ttday(int graph[V][V], int dist[]);
void dijkstra(int graph[V][V], int src);
void minfind(int graph[V][V], int dist[]);
void reco(int nel);
void recloc(int nel);
//함수선언 

int main() 
{   
	int day;
   printf("\n\n1.서울 2.대전 3. 전주 4. 광주\n\n5.담양 6. 여수 7. 통영 8. 부산\n\n9.대구 10.단양 11.강릉 12.속초\n\n13.춘천 14.가평\n\n");
   printf("현재 위치를 입력하세요(없을 시 가장 가까운 지역 선택) : ");
   scanf("%d",&loc); //현재 위치 저장 
   printf("\n"); 
   
   if(loc > 14) { //입력을 14 이상 하면 다시 입력하도록 설정 
   	printf("다시 입력하세요. \n");
   	printf("\n");
   	printf("현재 위치를 입력하세요(없을 시 가장 가까운 지역 선택) : ");
   	scanf("%d",&loc);
   	printf("\n");
   }
   
   printf("1. 당일치기 2. 1박2일 3. 2박3일\n\n");
   printf("원하시는 여행기간을 입력하세요: ");
   scanf("%d",&day); //원하는 여행기간 저장
   printf("\n"); 
   
   if(day > 3) { //입력이 3 이상이면 다시 입력하도록 설정 
   	printf("다시 입력하세요. \n");
   	printf("\n");
   	printf("원하시는 여행기간을 입력하세요: ");
   	scanf("%d",&day);
   	printf("\n");
   }
   
   if(day==1) oneday(graph,dist); //당일치기 선택시 oneday 함수로 넘어감 
   else if(day==2) otday(graph,dist,nel); //1박 2일 선택시 otday 함수로 넘어감 
   else if(day==3) ttday(graph,dist); //2박 3일 선택시 ttday 함수로 넘어감 


    return 0; 
} 

int minDistance(int dist[], bool sptSet[]) //최소거리인 곳의 인덱스값 구하는 함수 
{ 
  
   int min = INT_MAX, min_index; 
   
   for (int v = 0; v < V; v++) 
     if (sptSet[v] == false && dist[v] <= min) //방문하지 않았고, 배열의 값이 min값보다 작을경우 
         min = dist[v], min_index = v;  //방문한 곳이 min 값이 되고, 방문한 곳의 index가 min_index 
   
   return min_index; //min_index 반환 
} 

void minfind(int graph[V][V], int dist[]){ //1박2일에 이용될 가장 가까운 지역탐색 함수 
	
	int min = dist[0];
	int i,k;
	
	for(i = 1; i<V ; i++){
		if((dist[i] < min) && (dist[i]>0)){ //최소거리가 0인곳은 선택된 지역이기 때문에 0이상인 지역 중 최소값 
			min = dist[i]; 
			k = i+1;  
		}
	}
	
	printf("\n다음 추천 지역(거리 기준): ");
	recloc(k); 
	reco(k); //가장 가까운 지역의 추천코스 불러옴 
	
}

void oneday(int graph[V][V], int dist[]){ //당일치기 함수 
   
   dijkstra(graph, loc-1); //선택지역에서 각지역까지 최소거리 구하기 
    
   for(int i=0; i<V; i++)
      if(dist[i]==2) //현재 지역에서 최소거리 2인 곳 추천 
         nel = i;
   
   printf("추천 지역: ");
   recloc(nel+1); //dist는 0부터 시작하고 선택지는 1부터 시작하기 때문에 +1을 해서 불러옴 
    printf("\n"); 
   reco(nel+1);
   printf("\n"); 
}

void otday(int graph[V][V], int dist[], int nel) //1박 2일 함수 
{ 	
	dijkstra(graph, loc-1); //dijkstra 호출 후 현재 지역에서 최소 거리 나열 
	
	for(int i=0; i<V; i++){
		if(dist[i] == 3){ //현재 지역과 최소거리가 3인 거리를 출력 
			nel = i;
		}
	}
	
	printf("추천 지역: ");
	recloc(nel+1);	//dist는 0부터 시작하고 선택지는 1부터 시작하기 때문에 +1을 해서 불러옴 
	reco(nel+1);
	printf("\n"); 
	
	dijkstra(graph, nel);	//추천지역을 현재 지역으로 저장 후 추천지역에서 dijkstra 호출 
	printf("\n"); 
	minfind(graph, dist); //현재 지역에서 가까운 지역 찾음 

} 
void ttday(int graph[V][V], int dist[]){ // 2박3일일 때 쓰는 함수 
   
   int num, sty, els; // 변수 선언 (num:추천지역 중 지역 선택하는 변수, sty:테마를 고르는 변수, els:  
   int count=0; // count 값을 0으로 선언 
   int itemp=0; // itemp 값을 0으로 선언  
   int thm[V]={1,1,1,2,2,3,3,2,3,3,2,1,2,3}; //테마를 나타내는 함수 (1: 맛집인 지역, 2: 사진인 지역, 3:액티비티인 지역) 
   
   printf("1.맛집 2.사진 3.액티비티\n\n"); // 테마 선택 출력 
   printf("여행스타일을 입력하세요: ");  
   scanf("%d",&sty); // 여행 테마 입력 
   printf("\n"); 
   dijkstra(graph, loc-1); // 다익스트라 함수를 이용하여 지금 위치와 다른 지역까지의 거리 구함 
   
   if(sty==1){ // 테마를 1번 맛집으로 선택할 경우 
         for(int i=0;i<V;i++){ // for문을 이용하여 i를 0부터 V까지 증가시킴 
           if(thm[i]==2||thm[i]==3){ // 테마가 2번사진이거나 3번액티비티일 경우 
               thm[i]=itemp; // 테마가 2or 3이면 thm값이 0으로 변경 
               dist[i]=thm[i]; // 각 지역까지의 거리에서 맛집,액티비티 지역이면 0으로 변경 
             }
         }
         for(int i=0;i<V;i++){ // for문을 이용하여 i를 0부터 V까지 증가시킴 
           if(dist[i]>=5){ // 변경된 dist배열에서 5이상인 경우 
              printf("추천 지역: (%d번) ",i+1); // 그 치역 출력 
              els=i; 
            recloc(i+1); // 추천지역을 나타내는 함수 reloc을 부름 
            reco(i+1); // 추천코스를 나태나는 함수 reco를 부름
			printf("\n\n");   
            count++; //count값 1 증가시킴 
            }
        }
      
      if(count>=2){ // count의 값이 2 이상이면 (count 값이 1일 경우 지역 하나만 나와서 설정해줌) 
         printf("\n원하는 지역을 입력하세요: "); 
            scanf("%d",&num); // 추천받은 지역들 중 원하는 지역 선택 
            dijkstra(graph,num-1); // 원하는 지역의 각 지역간 거리를 구함  
            minfind(graph,dist); // 가장 가까운 지역 구함
			printf("\n");  
      }
      else{
         dijkstra(graph,els+1); //추천 지역이 1개라면 그 지역에서 바로 다익스트라 호출 
         minfind(graph,dist); // 가장 가까운 지역 구함 
      }
      
      
   }
   
   else if(sty ==2 ){ // 테마를 2번 맛집으로 선택할 경우 
      
      for(int i=0;i<V;i++){ //for문을 이용하여 i를 0부터 V까지 증가시킴 
         if(thm[i]==1||thm[i]==3){ // 테마가 1번맛집이거나 3번액티비티일 경우
            thm[i]=itemp; // 테마가 1or 3이면 thm값이 0으로 변경 
            dist[i]=thm[i]; // 각 지역까지의 거리에서 맛집,액티비티 지역이면 0으로 변경
            }     
      }
      for(int i=0;i<V;i++){ // sty 1과 같음 
         if(dist[i]>=6){
            printf("추천 지역: (%d번) ",i+1);
          recloc(i+1);
          reco(i+1);
          els=i;
		  printf("\n\n");   
          count++;
          
       }
      }   
      if(count>=2){ // sty 1과 같음 
         printf("원하는 지역을 입력하세요: "); 
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
   
   else if(sty==3){ // 테마를 3번 액티비티로 선택할 경우 
      for(int i=0;i<V;i++){ //for문을 이용하여 i를 0부터 V까지 증가시킴 
      if(thm[i]==1||thm[i]==2){ // 테마가 1번맛집이거나 2사진일 경우
         thm[i]=itemp; // 테마가 1or 3이면 thm값이 0으로 변경 
            dist[i]=thm[i]; // 각 지역까지의 거리에서 맛집,액티비티 지역이면 0으로 변경
         }
      }
   for(int i=0;i<V;i++){ // sty 1과 같음 
      if(dist[i]>=6){
            printf("추천 지역: (%d번) ",i+1);
          recloc(i+1);
          reco(i+1);
          els=i;
          printf("\n\n");  
          count++;
      }
   }
      if(count>=2){ // sty 1과 같음 
         printf("원하는 지역을 입력하세요: "); 
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
void recloc(int nel){ //추천 지역을 각 함수에서 호출 할수있도록 함수로 따로 만들어 둠 
	switch(nel) {
		case 1 : printf("서울\n"); break;
		case 2 : printf("대전\n"); break;
		case 3 : printf("전주\n"); break;
		case 4 : printf("광주\n"); break;
		case 5 : printf("담양\n"); break;
		case 6 : printf("여수\n"); break;
		case 7 : printf("통영\n"); break;
		case 8 : printf("부산\n"); break;
		case 9 : printf("대구\n"); break;
		case 10 : printf("단양\n"); break;
		case 11 : printf("강릉\n"); break;
		case 12 : printf("속초\n"); break;
		case 13 : printf("춘천\n"); break;
		case 14 : printf("가평\n"); break; 
		
		default : printf("다시 입력하세요. \n"); break;
	}
}

void reco(int nel){ //추천 코스를 각 함수에서 호출 할수 있도록 미리 만들어 둠 
	printf("\n"); 
	switch(nel) {
		case 1 : printf("추천 코스1 : 혜화 대학로 - 인사동 쌈지길 - 북촌 한옥마을 - 경복궁 - 한강공원\n\n추천 코스2: 롯데월드-잠실한강공원\n"); break;
		case 2 : printf("추천 코스: 한밭수목원 - 이응노 미술관 - 성심당부띠끄 - 성심당 - 오씨네칼국수\n"); break;
		case 3 : printf("추천 코스: 한옥마을 - 전동성당 - 청년몰 - 남부시장 \n"); break;
		case 4 : printf("추천 코스: 무등산레일바이크 - 펭귄마을 - 동명동하늘마당 - 송정역시장\n"); break;
		case 5 : printf("추천 코스: 국수거리 - 죽녹원 - 관방제림 - 메타세콰이어길 - 메타프로방스\n"); break;
		case 6 : printf("추천 코스: 해상케이블카 - 오동도 - 아쿠아리움 - 천사벽화마을 - 낭만포차거리\n"); break;
		case 7 : printf("추천 코스1 : 동피랑벽화마을 - 스카이라인 루지 - 어드벤처타워\n\n추천 코스2: 거제도\n"); break;
		case 8 : printf("추천 코스: 감천문화마을 - 영도흰여울길 - 깡통야시장 - 광안대교 - 해운대\n"); break;
		case 9 : printf("추천 코스1 : 대구이월드-곱창거리\n\n추천 코스2: 김광석거리 - 근대문화골목 - 서문야시장\n"); break;
		case 10 : printf("추천 코스: 패러글라이딩 - 도담삼봉 - 이끼터널\n"); break;
		case 11 : printf("추천 코스: 정동진- 강문해변 - 경포대 - 대관령양떼목장 - 안목해변커피거리 - 중앙시장\n"); break;
		case 12 : printf("추천 코스: 영랑호 - 속초중앙시장 - 영금정 - 아바이 마을 - 속초 해수욕장 - 알파카월드\n"); break;
		case 13 : printf("추천 코스: 소양강스카이워크 - 산토리니 - 구봉산전망대 - 닭갈비골목\n"); break;
		case 14 : printf("추천 코스1: 남이섬 - 제이드가든수목원\n\n추천 코스2: 캠프통아일랜드\n"); break; 
		
		default : printf("다시 입력하세요. \n"); break;
	}
}
void dijkstra(int graph[V][V], int src) //다익스트라 최단거리 구하는 함수 
{  
   
     bool sptSet[V];  
     
     for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; //초기값 설정 
     dist[src] = 0;    //인자로 받은 src의 dist 를 0으로 설정 
     
	 for (int count = 0; count < V-1; count++){  
       int u = minDistance(dist, sptSet); //u는 최소거리인 곳의 인덱스  
       sptSet[u] = true; //방문한 곳을 방문한 것으로 표시 
       
       for (int v = 0; v < V; v++) 
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v]) //graph[u][v]는 방문하지 않았고, MAX 값이 아닌 dist[u]와, 거리가 더 짧으면 
            dist[v] = dist[u] + graph[u][v]; //구한 거리를 최소 거리로 저장 
     } 
}


