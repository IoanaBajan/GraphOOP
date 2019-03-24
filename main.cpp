#include "graf.h"

int main()
{

    graf *G1=new graf(9);
        //cin>>*G1;
    G1->adaugareMuchie(2,1);
   G1->adaugareMuchie(1,0);
    cout<<G1->nrMuchii();
    cout<<"\n";

    //graf *G2=new graf(G1);
    graf *G2=new graf(9);
    G2->adaugareMuchie(1,2);
    G2->adaugareMuchie(1,9);
    G2->adaugareMuchie(3,4);
    G2->adaugareMuchie(3,5);
    G2->adaugareMuchie(3,6);
    G2->adaugareMuchie(3,9);
    G2->adaugareMuchie(5,8);
    G2->adaugareMuchie(6,7);
    G2->adaugareMuchie(7,8);
    G2->adaugareMuchie(9,7);
    //G2->adaugareMuchie(9,10);
//    G2->afisare();
//    cout<<"\n";
//    cout<<"\n";
//
//    if(G1<G2) cout<<"G1 mai mic decat G2"; else cout <<"G2 mai mic decat G1";
//    cout<<"\n supraincarcare operator[]";
//    cout << (*G2)[1];
//
//    for(int i=0;i<G2->nrNoduri();i++)
//        cout<<(*G2)[2]<<" ";
//    G1=G2;
//    cout<<"\nafisare G2\n SUPRAINCARCARE OPERATOR <<";
//    cout<<*G2;
    int output[20];
    cout<<"parcurgere dfs pentru graful G2\n";
    G2->parcurgDFS(1,output);
    for(int i=0;i<G2->nrNoduri();i++)
        cout<<output[i]<<" ";

    cout<<"parcurgere bfs pentru graful G2\n";
    G2->parcurgBFS(1);
    cout<<"nr componente conexe  "<<G2->componente_conexe()<<"\n";      //fara muchia (1,9) vor fi 2 componente conexe
    G2->verificare_arbore();
    cout<<endl;
    cout<<endl;
    cout<<endl;
     G2->dist_nod2(1,3);

//cout<<"numarul de muchii este"<<(*G).nrMuchii()<<"\n numarul de noduri este"<<(*G).nrNoduri();
}
