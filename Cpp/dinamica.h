//Contém modelo integra-dispara leak, modelo de Izhikevich e modelo de LHG simplificado. 
//Autor Dangeles Lima
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;
class dynamics{
public:
	vector <double> V;
	vector <double> V_;
	vector <bool> ativo;
	vector <int> numvizat;
	vector <int> listaativos;
	double dt;
	double time;
	int tmax;
	int num_neurons;
	int iseed;
	vector <vector<int>> listaviz;
	vector <vector<double>> weights;
	int n;
	dynamics(vector<vector<int>> listaviz_, vector<vector<double>> weights_, double TotalTime, int semente){
		iseed = semente;
		listaviz = listaviz_;
		weights = weights_;
		dt = 0.001;
		tmax = (int)TotalTime/dt;
		num_neurons = listaviz_.size();
		V.resize(num_neurons);
		V_.resize(num_neurons);
		ativo.resize(num_neurons);
		numvizat.resize(num_neurons);
		n = 0;
	}
	void SLHG(double J_);
	void LIF(double J_);
	void Izhikevich(double J_);
	double Euler(double&, double&);
};
void dynamics::LIF(double J_){
	double u = 1, J = J_;
	double atividade = 0;
	int num_viz;
	double soma = 0;
	double F, theta, E, Rm, Cm, TAUm, TAUref, I, Isyn, Inoise;
	F = 0;
	E = -70; //potencial de repouso
	theta = -66; //limiar
	Rm = 10;
	Cm = 1;
	TAUm = 10;
	TAUref = 2; //período refratário
	I = 0;
	ofstream arquivo("atividade.txt");
	for(int neuron = 0; neuron < num_neurons; ++neuron){
		V[neuron] = theta;
		V_[neuron] = theta;
		ativo[neuron] = true;
	}
	for (int t = 0; t < tmax; ++t){
		time = t*dt;
		atividade = 0;
		for (int neuron = 0; neuron < num_neurons; ++neuron){
			if (V[neuron] >= theta){
				ativo[neuron] = true;
				atividade++;
				V_[neuron] = E; //reseta
			}
			else{
				ativo[neuron] = false;
				num_viz = listaviz[neuron].size();
				for (int n = 0; n < num_viz; ++n){
					soma += ativo[listaviz[neuron][n]] * weights[neuron][n];
				}
				Isyn = u*J*soma;
				Inoise = 0; //rand_normal(0, 1);
				F = (1/TAUm) * (E - V_[neuron]) + Cm*(I + Isyn + Inoise); //Leak integrate and fire
				V_[neuron] = Euler(V_[neuron], F); //Método de Euler
				soma = 0;
			}
		}
		V = V_; //paralelo
			if (atividade != 0){
				arquivo << time << ' ' << atividade << endl;
				cout << time << ' ' << atividade << endl; 
			}
	}
	arquivo.close();
}
void dynamics::Izhikevich(double J_){
	double ub = 1, J = J_;
	int csi;
	double atividade = 0;
	int num_viz;
	double soma = 0;
	double F = 0, theta = -30, E = -70, I = 0, Isyn;	
	double k = 0.04, a = 0.02,	b = 0.2, c = -65, d = 6; //tonic spiking 
	double Vth = -55, G = 0;
	vector <double> u;
	vector <double> u_;
	u.resize(num_neurons);
	u_.resize(num_neurons);
	ofstream arquivo("atividade.txt");
	for(int neuron = 0; neuron < num_neurons; ++neuron){
		V[neuron] = theta;
		V_[neuron] = theta;
		ativo[neuron] = true;
		u[neuron] = 0;
		u_[neuron] = 0;
	}
    int duracao = 0;
	int avalanches = 0;
	for (int t = 0; t < tmax; ++t){
		time = t*dt;
		atividade = 0;
		for (int neuron = 0; neuron < num_neurons; ++neuron){
			if (V[neuron] >= theta){
				ativo[neuron] = true;
				atividade++;
				V_[neuron] = c;
				u_[neuron] = u_[neuron] + d;
			}
			else{
				ativo[neuron] = false;
				num_viz = listaviz[neuron].size();
				for (int n = 0; n < num_viz; ++n){
					soma += ativo[listaviz[neuron][n]]; 
				}
				Isyn = J*soma;
				F = k*(V_[neuron] - E)*(V_[neuron] - Vth) - u_[neuron] + I + Isyn;
				G = a*(b*(V_[neuron] - E) - u_[neuron]);
				V_[neuron] = Euler(V_[neuron], F); 
				u_[neuron] = Euler(u_[neuron], G); 
				soma = 0;
			}
		}
		V = V_; //paralelo
		u = u_;
		if (atividade != 0){
			arquivo << time << ' ' << atividade << endl;
		}
	}
	arquivo.close();
}
void dynamics::SLHG(double J_){
	double tau = 1;
	double taud = 0;
	double Iext = 0.025; 
	double theta = 1;
	double u = 0.2, J = J_;
	int csi;
	double atividade = 0;
	int num_viz;
	//ofstream arquivo("atividade.txt");
	ofstream duration("duration.txt", ios::app);
	ofstream avalanche("avalanche.txt", ios::app);	
	for(int neuron = 0; neuron < num_neurons; ++neuron){
		V[neuron] = 0;
		V_[neuron] = 0;
		ativo[neuron] = false;
	}
    int duracao = 0;
	int avalanches = 0;
	for (int t = 0; t < tmax; ++t){
		time = t*dt;
		if (atividade <= 0){
			csi = (int)( gerador(iseed) * num_neurons );
			V_[csi] += Iext; //paralelo
			//V[csi] += Iext; //sequencial
		}
		atividade = 0;
		for (int neuron = 0; neuron < num_neurons; ++neuron){
			if (V[neuron] >= theta){
				ativo[neuron] = true;
				atividade++;
				V_[neuron] -= theta; //paralelo
				//V[neuron] -= theta; //sequencial
				for (int n = 0; n < num_neurons; ++n){
					if (n != neuron){
						V_[n] += (u*J)/(num_neurons-1); //paralelo
						//V[n] += (u*J)/(num_neurons-1); //sequencial
					}
				}
			}
			else{
				ativo[neuron] = false;
			}
		}
		V = V_; //paralelo
			if (atividade != 0){
				duracao++;
				avalanches += atividade;
				//arquivo << time << ' ' << atividade << endl;
			}
			if (atividade <= 0){
				if (duracao != 0){
					duration << duracao << endl;
					avalanche << avalanches << endl;
				} 
				duracao = 0;
				avalanches = 0;
			}
	}
	//arquivo.close();
	duration.close();
	avalanche.close();
}
double dynamics::Euler(double& V, double& F){
	V = V + dt*F;
	return V;
}