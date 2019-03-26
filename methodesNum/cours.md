><
# Méthodes Numériques

## 1. Chapitre 1 
## Recherche de racines d'une fonctions
**Objectif:** 

Soit $f$ continue sur $[a; b]$

On cherche : $R \in [a; b], f(R)=0$

* théoreme de valeurs intermédiaires:

soit $f$ continue sur $[A; B]$ si $\begin{Bmatrix}
    f(a)<0 \\
    f(b)>0
\end{Bmatrix}$ il existe $R\in ]a; b[$

Si $\begin{Bmatrix}
    f(a)>0 \\
    f(b)<0 
\end{Bmatrix}$ il existe $R \in [a; b] / f(R)$
* Unicité d'une racine:

Si $x\in \Reals$, et $f$ est strictement monotone alors la racine $R$ est unique

> * Si $f'\geqslant$ sur intervalle alors croissant 
> * Si $f'\leqslant$ un intervalle alors décroissante

## 1.1. Localisation de la racine par Dichotomie

on suppose que $f$ possede une unique racine dans $[a; b]$ et que $f(a)f(b)<0$

1. On pose alors $m=\dfrac{a+b}{2}$ et on calc $f(m)$
2. si $f(m)=0$ alors $R$ a été trouvé
3. Si $f(m)=\not0$, on évalue $f(a)f(m)$
   * si $f(a)f(m)<0$ alors d'aprés le TVI, racine se trouve dans $[a;m]$ et on reprend avec $[a; b]=[a;m]$