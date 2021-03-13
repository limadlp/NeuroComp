**Classes em C++**

Para facilitar a utilização e reutilização de vários modelos de neurônios, desenvolvi uma interface computacional com diferentes modelos de redes, dinâmicas neuronais e sinapses.
O núcleo da interface se divide em duas classes: 
* “rede.h”, contendo estruturas de redes; 
* “dinamica.h”, contendo modelos de dinâmica neuronais e sinapses; 

Aqui, temos um esquema exemplos de códigos para as classes da interface:

Na classe “rede.h” temos a rede unidimensional, a rede quadrada e um tipo de rede modular hierárquica. 
Na classe “dinamica.h” temos o modelo de integra-dispara simples, o modelo de Izhikevich (*). e o modelo de Levina-Herrmann-Geisel simplificado. 



(*) O modelo de Izhikevich é uma variação dos modelos de integra-dispara, em que se adiciona uma variável de recuperação ao integra-dispara quadrático. Conseguindo, dessa forma, apresentar uma ampla variedade de comportamentos realísticos, bem como se manter computacionalmente simples.

<img src="https://raw.githubusercontent.com/limadlp/NeuroComp/main/img/izhi.png">
Gráfico do comportamento de atividade autossustentada de dois neurônios acoplados, com sinapses excitatórias modeladas pela função alfa. Os neurônios estão acoplados sem receber input externo de corrente. Como condição inicial, considera-se que o neurônio 1 acabou de disparar, fazendo com que o sistema adote um regime de fase. Parâmetros: k = 0.04, a = 0.02, b = 0.2, c = -65, d = 6.
