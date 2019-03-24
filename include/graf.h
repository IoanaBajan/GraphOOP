#ifndef GRAF_H
#define GRAF_H
#include <iostream>
using namespace std;
struct nod{

        int nod_info;
        nod *next;
        };

class graf
{
    public:
        graf();
        graf(int n);
        ~graf();
        graf(graf*);
        void adaugareMuchie(int , int );
        void afisare();
        int nrMuchii();
        int nrNoduri();
        friend bool operator< (const graf &grafA, const graf &grafB);
        friend bool operator> (const graf &grafA, const graf &grafB);
        int operator[] (int);
        graf operator =(graf grafA);
        friend istream& operator>>(istream&, graf&);
        friend ostream& operator<<(ostream&, graf&);
        void parcurgDFS(int nod_start,int *output);
        void parcurgBFS(int nod_start);
        void distanta_noduri(int nod1,int nod2);
        void verificare_arbore();
        void dist_nod2(int nod1,int nod2);
        int componente_conexe();
    protected:

    private:
        int nr_noduri;
        int nr_muchii;


    nod** ListaAdj;

};

#endif // GRAF_H
