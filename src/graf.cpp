#include "graf.h"
#include<stdlib.h>

graf::graf()
{//constructor
    nr_noduri=0;
    nr_muchii=0;
    cout<<"graf creat";
}

graf::graf(int n)
{//constructor cu parametru
    nr_noduri=n;
    nr_muchii=0;
    ListaAdj = new nod*[nr_noduri];
    for(int i=0;i<nr_noduri;i++)
        ListaAdj[i]=NULL;
}

graf::~graf()
{//destructor
    delete []ListaAdj;

    nr_noduri=0;
    nr_muchii=0;
    cout<<"graf destroyed\n";

}

void graf::afisare()
{//afiseaza lista de adiacenta a grafului
    for(int i=0; i<nr_noduri; i++)
    {nod *c=ListaAdj[i];
       if (c==NULL) {cout<<i<<" nu are vecini!"<<endl;}
        else {
            cout<<"Vecinii lui "<<i<<" sunt: ";
            while (c!=NULL)
            {
            cout<< c->nod_info<<" ";
            c = c->next;
            }
            cout<<endl;
        }
    }
}

graf::graf(graf *copie)
{//copiaza graful copie in graful this
//se parcurge lista de adiacenta a grafului copie
// copiindu-se element cu element in lista grafului this

    this->nr_muchii=copie->nr_muchii;
    this->nr_noduri=copie->nr_noduri;

    this->ListaAdj = new nod*[nr_noduri];
    for(int i=0;i<this->nr_noduri;i++)
        this->ListaAdj[i]=NULL;

    for(int i=0;i<this->nr_noduri;i++)
    {
      nod *c = copie->ListaAdj[i];

    if (!c) this->ListaAdj[i]=NULL;
        else {
            while (c)
            {
              nod *d=new nod;
              d->nod_info=c->nod_info;
              d->next=this->ListaAdj[i];

              this->ListaAdj[i]=d;
                c = c->next;
            }
        }
    }

}

void graf::adaugareMuchie(int n, int m)
{//adauga mai intai nodul m in lista de adiacenta a nodului n
// apoi pe n in lista de adiacenta a lui m

    nod *c1 = new nod;
    c1->nod_info = m;
    c1->next= NULL;

    if(ListaAdj[n] == NULL)
            ListaAdj[n] = c1;
    else {

            c1->next = ListaAdj[n];
            ListaAdj[n] = c1; }

    nod *c2 = new nod;
    c2->nod_info = n;
    c2->next= NULL;

    if(ListaAdj[m] == NULL)
            ListaAdj[m] = c2;
    else {

            c2->next = ListaAdj[m];
            ListaAdj[m] = c2; }

    nr_muchii++;
}

int graf::nrMuchii()
{
    return nr_muchii;
}

int graf::nrNoduri()
{
    return nr_noduri;
}

bool operator< (const graf &grafA, const graf &grafB)
{//supraincarcarea operatorului < ca functie prieten
    if(grafA.nr_noduri==grafB.nr_noduri)
        return (grafA.nr_muchii<grafB.nr_muchii);
    return (grafA.nr_noduri < grafB.nr_noduri);
}

bool operator> (const graf &grafA, const graf &grafB)
{//supraincarcarea operatorului > ca functie prieten

    if(grafA.nr_noduri==grafB.nr_noduri)
        return (grafA.nr_muchii>grafB.nr_muchii);
    return (grafA.nr_noduri > grafB.nr_noduri);
}

int graf::operator[](int vertex)
{
    //supraincarcara operatorului []
    //returneaza lista de adiacenta a nodului "vertex" sub forma de vector

    nod *c=ListaAdj[vertex];
    int Vector[100];
    int i=0;

    while(c)
    {

     //   cout<<c->nod_info<<" ";
        Vector[i]=c->nod_info;
        c=c->next;
        i++;
    }

    for(int j=0;j<i;j++)
        cout<<Vector[j]<<" " ;

}

graf graf::operator=(graf grafA)
//supraincarcarea operatorului = de atribuire
{
    nr_muchii=grafA.nr_muchii;
    nr_noduri=grafA.nr_noduri;

    for(int i=0;i<nr_noduri;i++)
    ListaAdj[i]=grafA.ListaAdj[i];

    return *this;
}

    istream& operator>>(istream& in, graf &grafA)
 {
    //supraincarcarea operatorului de citire
    int n,m;
    cout<<"numarul de noduri:";
    in>>grafA.nr_noduri;

    grafA.ListaAdj=new nod*[grafA.nr_noduri];
    for(int i=0;i<grafA.nr_noduri;i++)
    {
    cout<<"introduceti muchii pentru nodul :"<<i+1;
    in>>n>>m;
    grafA.adaugareMuchie(n,m);

    }
 }

    ostream& operator<<(ostream& in, graf &grafA)
{
    //supraincarcarea operatorului de afisare
    cout<<grafA.nr_noduri;
    for(int i=0; i<grafA.nr_noduri; i++)
        {
            nod *c=grafA.ListaAdj[i];
            if (c==NULL) {cout<<" \n"<<i<<" nu are vecini!"<<endl;}
            else {
                cout<<"\n Vecinii lui "<<i<<" sunt: ";
                while (c!=NULL)
                {
                    cout<< c->nod_info<<" ";
                    c = c->next;
                }
            cout<<endl;
            }
    }
}

void graf::parcurgDFS(int nod_start,int *output)
{
    //transmite prin vectorul output parcurgerea in adancime a unui graf pornind de la nodul nod_start
    int k=0;
    if( nod_start>0 && nod_start<=nr_noduri )
    {
        int visited[nr_noduri+1];
        for(int i=1;i<=nr_noduri;i++)
            visited[i]=0;

        nod *stiva=new nod;             //aloc spatiu pentru stiva
        stiva->nod_info=nod_start;          //ii adaug valoarea primului nod
        stiva->next=NULL;
        visited[nod_start]=1;

        while(stiva)
        {
            int nod_curent;
            nod *nod_pargurgere;
            nod_curent=stiva->nod_info;             //  nod curent= top of stack
            stiva=stiva->next;                      //elimin top of stack

            output[k++]=nod_curent;         //adaug nodul eliminat din stiva la vectorul de afisare
            visited[nod_curent]=1;          //il marchez ca vizitat

            nod_pargurgere=ListaAdj[nod_curent];        //parcurg lista de adiacenta a nodului curent

            //adaug in stiva toate nodurile adiacente nodului curent, nodurile din ListAdj sunt in ordine descrecatoare, in aceasta ordine vor fi adaugate si in stiva
            while(nod_pargurgere)
            {
                if(visited[nod_pargurgere->nod_info]==0)
                {
                    nod *c=new nod;
                    c->nod_info=nod_pargurgere->nod_info;
                    c->next=stiva;
                    stiva=c;
                    visited[nod_pargurgere->nod_info]=1;

                }
                nod_pargurgere=nod_pargurgere->next;
            }
        }

    }

}

void graf::parcurgBFS(int nod_start)
{
    //afiseaza parcurgerea in latime a unui graf pornind de la nodul nod_start
    int output[20];
    int k=0,i;
    if(nod_start>0 && nod_start<=nr_noduri)
    {
        int visited[nr_noduri+1];
        for(i=1;i<=nr_noduri;i++)
            visited[i]=0;       //am intitializat vectorul de noduri vizitate

        nod *coada=new nod;
        coada->nod_info=nod_start;      //am creat coada si am adaugat nodul de start
        coada->next=NULL;
        visited[nod_start]=1;             //am marcat nodul de start ca vizitat

        while(coada)
        {
            int nod_curent;
            nod *nod_parcurgere;
            nod *c;
            nod_curent=coada->nod_info;         //am atribuit nodului curent prima valoare din coada
            coada=coada->next;                  //am sters primul element din coada

            output[k++]=nod_curent;             //am adaugat la vectorul de afisare nodul curent, adica prima valoare din coada
            visited[nod_curent]=1;              //am marcat nodul curent ca vizitat pt a nu il mai adauga niciodata in coada
            nod_parcurgere=ListaAdj[nod_curent];        //Lista de adiacenta a fiecarui nod contine noduri in ordine descrecatoare, asa ca vor fi adaugate in coada in ordinea in care apar
            while(nod_parcurgere)
            {
                if(visited[nod_parcurgere->nod_info]==0)
                {
                    nod *d=new nod;
                    d->nod_info=nod_parcurgere->nod_info;
                    d->next=NULL;
                    c=coada;                //am facut o copie spre inceputul cozii
                    if(!coada)
                    {
                        coada=d;            //daca coada e goala, o egalez cu noul nod
                    }
                    else
                    {
                        while(c->next)          //parcurg coada, pana la sfarsit, dupa care adaug noul nod la capat
                            c=c->next;

                            c->next=d;


                    }
                    visited[nod_parcurgere->nod_info]=1;

                }
                nod_parcurgere=nod_parcurgere->next;        //parcurg lista de adiacenta a nodului curent
            }
        }
    }

for(int i=0;i<k;i++)
        cout<<output[i]<<" ";

}



void graf::distanta_noduri(int nod1,int nod2)
{
    //calculeaza distanta minima dintre 2 noduri folosind parcurgerea in adancime
    cout<<"am intrat in fct distanta_nod";
    int i,j,output[20],x,y,dmin=100,pmin=0;
    for( i=1;i<=nr_noduri;i++)
    {
        parcurgDFS(i,output);       //calculez parcurgerea dfs pt fiecare nod
        cout<<endl;
//        for(int k=0;k<nr_noduri;k++)
//            cout<<output[k];

    int nr=0;
    for(j=1;j<=nr_noduri;j++)
        {
        if(output[j]==nod1)     x=j;        //calculez distanta dintre cele 2 noduri pt fiecare parcurgere
        if(output[j]==nod2)  y=j;
        }
        if(abs(x-y)<dmin)
            {
               dmin=abs(x-y);       //retin in dmin distanta minima dintre noduri, in pmin parcurgerea in care am gasit cele 2 noduri la distanta dmin
               pmin=i;
            }
    }

    cout<<" Distanta minima intre "<<nod1<<" si "<<nod2<<" in parcurgerea cu nodul de start "<<pmin<<" este "<<dmin;
}

void graf::verificare_arbore()
{
    //metoda care verifica daca graful dat este arbore
    int vf[nr_noduri+1],i,output[nr_noduri+1],ok=0,x;
    for(i=0;i<=nr_noduri;i++)
        vf[i]=0;

        parcurgDFS(1,output);
    //verific daca graful este conex, daca toate nodurile grafului apar in parcurgerea dfs
    for(i=0;i<nr_noduri;i++)
        {
            x=output[i];
            vf[x]++;
            }


    for(i=0;i<=nr_noduri;i++)
        {
        if(vf[i]==1) ok=1;
        else ok=0;
        }
        if(ok==1)
            cout<<"\n graf conex";
            else cout<<"\n graf neconex";

            //un arbore are nr_noduri-1 muchii, daca graful are nr_noduri-1 muchii si este conex,atunci este arbore
        if(ok==1 && nr_muchii==nr_noduri-1)
            cout<<"\n graful este arbore";
        else cout<<"\n graful nu este arbore";
}



void graf::dist_nod2(int nod1,int nod2)
{
    int nod_front;
    int dist[nr_noduri];
    int i;
    bool visited[30];

    for(i=1;i<=nr_noduri;i++)
        visited[i]=0;
                //initializez un vector de noduri vizitate
    for(i=1;i<=nr_noduri;i++)
      dist[i]=0;
//initializez un vector de distante, de la nodul dat nod1, la nodul i

      nod *Q=new nod;           //aloc spatiu pt o coada si ii adaug valoare nodului de start nod1
      Q->nod_info=nod1;
      Q->next=NULL;
      dist[nod1]=0;
      visited[nod1]=1;      //marchez primul nod ca vizitat
    while(Q)
    {
        nod_front=Q->nod_info;      //iau front queue, prima valoare din coada
        Q=Q->next;                  //o sterg din coada
        cout<<"nod_front="<<nod_front<<" \n";
        nod *nod_end=new nod;
        nod *vecin;
        vecin=ListaAdj[nod_front];
        while(vecin->next)
        {
        cout<<vecin->nod_info<<" ";
        if(dist[vecin->nod_info]==0 || ( dist[vecin->nod_info]>dist[nod_front]+1) )

            dist[vecin->nod_info]=dist[nod_front]+1;    //pe masura ce parcutg nodurile ,care nu sunt vizitate deja, adaug 1 la distanta
            nod_end=Q;
            if(!Q) Q=vecin;
            else{
                while(nod_end->next)
                    nod_end=nod_end->next;      //adaug toate nodurile adiacente nodului nod_front la coada

                nod_end=vecin;

            }

            visited[vecin->nod_info]=1;         //orice nod pe care l-am parcurs il marchez ca vizitat


            cout<<"visited= "<<visited[vecin->nod_info];
            if(vecin->next==NULL)
              cout<<"NULL";

            cout<<"\n nodul vecin este="<<(vecin->next)->nod_info;

            vecin=vecin->next;
            cout<<" distanta de la" <<nod1<<" la "<<vecin->nod_info<<dist[vecin->nod_info]<<"\n ";

        }
    cout<<"verificare"<<dist[nod2];
    }

    cout<< "DISTANTA:"<<dist[nod2];         //afisez distanta de la nod1 la nod2
}

int graf::componente_conexe()
{
    //calculeaza numarul de componente conexe a unui graf dat numarand ciclurile de adaugare in stiva
    int i;
    int visited[nr_noduri];
    for(i=1;i<=nr_noduri;i++)
    if(ListaAdj[i])
        visited[i]=1;
    else visited[i]=0;
    int nr_componente=0;

    for(i=1;i<=nr_noduri;i++)

        if(visited[i]==1)
       {
        nr_componente++;

        nod *stiva=new nod;        //creez o stiva si adaug in ea toate nodurile grafului
        stiva->nod_info=i;
        stiva->next=NULL;
        visited[i]=0;

        while(stiva)
        {
            int nod_curent;
            nod *nod_parcurgere;

            nod_curent=stiva->nod_info;         //iau primul nod din stiva, top of stack
            stiva=stiva->next;                  //il sterg din stiva

            visited[nod_curent]=0;
           nod_parcurgere=ListaAdj[nod_curent];
        //parcurg lista de adiacenta a nodului curent, le adaug in stiva daca au mai fost vizitate
            while(nod_parcurgere)
            {
                if(visited[nod_parcurgere->nod_info]==1)
                {
                    //daca nod_parcurgere a mai fost vizitat pana acum , este adaugat in stiva
                    nod*c=new nod;
                    c->nod_info=nod_parcurgere->nod_info;
                    c->next=stiva;
                    stiva=c;
                    visited[nod_parcurgere->nod_info]=0;        //actualizez starea pentru a nu fi adaugat de mai multe ori in stiva
                }
                nod_parcurgere=nod_parcurgere->next;
            }
        }
    }
    return nr_componente;
}
