function [] = Visualisation_Call(B,C)
Y=read (B, -1, 1);
Z=read (C, -1, 1);
X=linspace(0,300,length(Y))
X1=linspace(-5,log(3),length(Y))
X1=100*exp(X1)
plot2d(X1',Z,rect=[0,0,350,200],style=5)
plot2d(X',Y,rect=[0,0,350,200],style=2)
legends(['Méthode de Cranck_Nicholson' 'Méthode implicite'],[2,5],2)
title("Visualisation de C(0,s) dans le cas d un call")
endfunction

function [] = Visualisation_Put(B,C)
Y=read (B, -1, 1);
Z=read (C, -1, 1);
X=linspace(0,300,length(Y))
X1=linspace(-5,log(3),length(Y))
X1=100*exp(X1)
plot2d(X1',Z,rect=[0,0,350,100],style=5)
plot2d(X',Y,rect=[0,0,350,100],style=2)
legends(['Méthode de Cranck_Nicholson' 'Méthode implicite'],[2,5],1)
title("Visualisation de C(0,s) dans le cas d un put")
endfunction

function [] = Visualisation(B)
Y=read (B, -1, 1);
X=linspace(0,300,length(Y))
plot2d(X',Y,rect=[0,0,350,140],style=5)
endfunction

function [] = Erreur_call(B,C)
Y=read (B, -1, 1);
Z=read (C, -1, 1);
X=linspace(0,300,length(Y))
X1=linspace(-5,log(3),length(Y))
X1=100*exp(X1)
plot2d(X',Y-Z,rect=[-10,0,350,140],style=5)
title("Visualisation de l erreur pour un call")
endfunction

function [] = Erreur_put(B,C)
Y=read (B, -1, 1);
Z=read (C, -1, 1);
X=linspace(0,300,length(Y))
X1=linspace(-5,log(3),length(Y))
X1=100*exp(X1)
plot2d(X',Y-Z,rect=[-10,0,350,140],style=5)
title("Visualisation de l erreur pour un put")
endfunction

function [] = Visualisation(B)
Y=read (B, -1, 1);
X=linspace(0,300,length(Y))
plot2d(X',Y,rect=[0,0,350,200],style=2)
endfunction

