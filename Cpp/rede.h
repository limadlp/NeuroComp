//Contém rede unidimensional, rede quadrada e uma rede do tipo modular hierárquica. 
//Autor Dangeles Lima
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;
class Network{
	public:
	int N, L, iseed;
	vector <vector<int>> listaviz;
	vector <vector<double>> weights;
	Network(int tamanho, int tamanho2, int semente = 1){
		iseed = semente;
		L = tamanho;
		N = tamanho2;
		listaviz.resize(N);
		weights.resize(N);
	}
	vector<vector<int>> RingLattice(bool);
	vector<vector<int>> SquareLattice(bool);
	void HMNTree(int orientacao, int& iseed, int iseed2);
	vector<vector<double>> InitWeights(double, double);
	template <class T>
	void printarray(vector<vector<T>>);
};
vector<vector<int>> Network::RingLattice(bool periodic = true){
	//[0] left 	//[1] right
	for(int i = 0; i < N; ++i){
		listaviz[i].resize(2);
		listaviz[i][0] = i - 1;
		listaviz[i][1] = i + 1;
		if (periodic == true){
			//periodic boundary conditions
			if (i == 0) listaviz[i][0] = N - 1;
			if (i == (N - 1)) listaviz[i][1] = 0;
		}
		if (periodic == false){
			if (i == (N-1)) listaviz[i].pop_back();
			if (i == 0) { listaviz[i][0] = listaviz[i].back(); listaviz[i].pop_back();} 
		}
	}
	return listaviz;
}
vector<vector<int>> Network::SquareLattice(bool periodic = true){
	//[0] right  //[1] left  //[2] up //[3] down	
	for(int i = 0; i < L; ++i){
		for (int j = 0; j < L; ++j){
			int x = i + j*L;
			// 4 vizinhos
		    listaviz[x].resize(4);
			listaviz[x][0] = x + 1;
			listaviz[x][1] = x - 1;
			listaviz[x][2] = x - L;
			listaviz[x][3] = x + L;
					
			if (periodic == true){
				// periodic boundary conditions
				if (i == 0) listaviz[x][1] = x - 1 + L;
				if (j == 0) listaviz[x][2] = x + L*L - L;
				if (i == (L-1)) listaviz[x][0] = x - L + 1;
				if (j == (L-1)) listaviz[x][3] = x - L*L + L;
			}
			if (periodic == false){
				
				if (j == (L-1)) {listaviz[x].pop_back(); } 
				if (j == 0) {listaviz[x][2] = listaviz[x].back(); listaviz[x].pop_back(); }
				if (i == 0) {listaviz[x][1] = listaviz[x].back(); listaviz[x].pop_back(); }
				if (i == (L-1)) {listaviz[x][0] = listaviz[x].back(); listaviz[x].pop_back(); } 	
			}
			
		}
	}
	return listaviz;
}
// orientacao 0 grafo sem orientação, 1 orientacao entrando, 2 orientacao saindo
void Network::HMNTree(int orientacao , int& iseed, int iseed2){
    
	srand(iseed2);
    int tree[16][4] = { { 0, 1, 2, 3}, 
					    { 0, 1, 3, 2},
						{ 0, 2, 1, 3},
						{ 0, 2, 3, 1},
						{ 0, 3, 1, 2},
						{ 0, 3, 2, 1},
						{ 1, 0, 2, 3},
						{ 1, 0 ,3, 2},
						{ 1, 2, 0, 3},
						{ 1, 3, 0 ,2},
						{ 3, 1, 0, 2},
						{ 3, 0, 1, 2},
						{ 0, 1, 2, 3},
						{ 1, 0, 2, 3},
						{ 2, 0, 1, 3},
						{ 3, 0, 1, 2},        
					   }; //arvore das 16 possibilidades
    double alfa = 0;   double beta = 0;  int gama = 0;
    int A[4];  
    int T = 0;  
    int N2 = (int)(N/4. - 1.);
    // gera as conexoes no primeiro nível
    for (int k = 0; k <= N2; k++){
       T = (int) (gerador(iseed)*16);   
    
       if (T > 11){
            for( int i = 1; i <= 3; i++){
               if (orientacao == 1){
 					listaviz[tree[T][0] + 4*k].push_back(tree[T][i] + 4*k);
			   }
               else if (orientacao == 2){
					listaviz[tree[T][i] + 4*k].push_back(tree[T][0] + 4*k);
			   }
               else if (orientacao == 0){
					listaviz[tree[T][0] + 4*k].push_back(tree[T][i] + 4*k);
					listaviz[tree[T][i] + 4*k].push_back(tree[T][0] + 4*k);
               }  }
        }
        else if (T <= 11){
             for(int i = 0; i < 3; i++){
                if (orientacao == 1){
					listaviz[tree[T][i]+4*k].push_back(tree[T][i+1] +4*k);
				}
                else if (orientacao == 2){
					listaviz[tree[T][i+1] +4*k].push_back(tree[T][i] +4*k);
				}
                else if (orientacao == 0){
					listaviz[tree[T][i]+4*k].push_back(tree[T][i+1] +4*k);
					listaviz[tree[T][i+1] +4*k].push_back(tree[T][i] +4*k);
                }   }   }
    }
    //gera as conexoes de ordem superior
    for (int l = 2; l <= L; l++){ // para todas hierarquias
        for (int k = 0; k <= 3; k++){
            T = (int) (gerador(iseed)*16); // escolher uma tree das 16 possíveis
			// conexão dos nós
			if (T > 11){
				for( int i = 1; i <= 3; i++){
				   
				   alfa = (tree[T][0])*pow(4, l-1);
				   beta = (tree[T][0] + 1)*pow(4, l-1) - 1; 
				   gama = (int) (beta + 1 - alfa);
				   A[0] =   rand()%gama + (int)alfa;
		
				   alfa = (tree[T][i])*pow(4, l-1);
				   beta = (tree[T][i] + 1)*pow(4, l-1) - 1; 
				   gama = (int) (beta + 1 - alfa);

				   A[i] =  rand()%gama + (int)alfa;	   
				   if (orientacao == 1){
						listaviz[A[0] + k*(int)pow(4, l)].push_back(A[i] + k*(int)pow(4, l));
				   }  
				   else if (orientacao == 2){
						listaviz[A[i] + k*(int)pow(4, l)].push_back(A[0] + k*(int)pow(4, l));				   
				   }
				   else if (orientacao == 0){
						listaviz[A[0] + k*(int)pow(4, l)].push_back(A[i] + k*(int)pow(4, l));
						listaviz[A[i] + k*(int)pow(4, l)].push_back(A[0] + k*(int)pow(4, l));
				   }
				}
			}
			else if (T <= 11){
				for(int i = 0; i < 3; i++){
						 
					alfa = (tree[T][i])*pow(4, l-1);
					beta = (tree[T][i] + 1)*pow(4, l-1) - 1; 
					gama = (int)(beta + 1 - alfa);
					A[i] =  rand()%gama + (int)alfa;
					alfa = (tree[T][i+1])*pow(4, l-1);
					beta = (tree[T][i+1] + 1)*pow(4, l-1) - 1;
					gama = (int)(beta + 1 - alfa);
					A[i+1] = rand()%gama + (int)alfa;
					if (orientacao == 1){
						listaviz[A[i] + k*(int)pow(4, l)].push_back(A[i+1] + k*(int)pow(4, l));
					}
					else if (orientacao == 2){
						listaviz[A[i+1] + k*(int)pow(4, l)].push_back(A[i] + k*(int)pow(4, l));
					}
					else if (orientacao == 0){
							listaviz[A[i] + k*(int)pow(4, l)].push_back(A[i+1] + k*(int)pow(4, l));
							listaviz[A[i+1] + k*(int)pow(4, l)].push_back(A[i] + k*(int)pow(4, l));
					}
				}//for 
			}//elseif
			if (l == L) break;
        }//for
   
    }//for
}
vector<vector<double>> Network::InitWeights(double mean, double stddev){

	for (int i = 0; i < weights.size(); ++i){
		weights[i].resize(listaviz[i].size());
		for (int vizinho = 0; vizinho < weights[i].size(); ++vizinho){
			weights[i][vizinho] = rand_normal(mean, stddev);//gerador(iseed);
		}
	}
	return weights;
}
template<class T>
void Network::printarray(vector<vector<T>> vetor){ // imprime matriz
    ofstream arquivo;
    arquivo.open("rede.txt");
     for (int i =0; i < N; i++){
		 arquivo << i << " ";
         for (int j = 0; j < vetor[i].size(); j++){
               if (vetor[i][j] < 10) {
                   arquivo << " " << vetor[i][j] << " ";
               }
               else arquivo << vetor[i][j] << " ";
         }
         arquivo << endl;
     } 
    arquivo.close();  
}