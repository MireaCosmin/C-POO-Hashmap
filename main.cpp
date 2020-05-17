#include <iostream>
#include <vector>




/*
Am folosit in implementare clasele Nod, Lista si HashMap
Operatiile de adaugare, stergere si cautare le-am facut in lista cu care apoi am construit hashmap-ul
*/



using namespace std;

template <class K, class V>
class Nod
{
    K key;
    V value;
    Nod* next;
public:
    Nod();
    Nod(K,V,Nod*);
    void setKey(K);
    K getKey();
    void setValue(V);
    V getValue();
    void setNext(Nod*);
    Nod* getNext();
};
template <class K, class V>
Nod<K,V> :: Nod() : key(0),value(""),next(0)
{
}

template <class K, class V>
Nod<K,V> :: Nod(K key, V value, Nod* next) : key(key),value(value),next(next)
{
}

template <class K, class V>
void Nod<K,V> :: setKey(K key)
{
    this->key=key;
}

template <class K, class V>
K Nod<K,V> :: getKey()
{
    return key;
}

template <class K, class V>
void Nod<K,V> :: setValue(V value)
{
    this->value=value;
}

template <class K, class V>
V Nod<K,V> :: getValue()
{
    return value;
}

template <class K, class V>
void Nod<K,V> :: setNext(Nod* next)
{
    this->next=next;
}

template <class K, class V>
Nod<K,V>* Nod<K,V> :: getNext()
{
    return next;
};

template <class K, class V>
class Lista
{
    Nod<K,V>* start;
    Nod<K,V>* finish;
    int list_size;
public:
    Lista();
    void adaugare(K,V);
    void ordonare();
    int getKeyDistincte();
    int getSize();
    void show_list();
    int getNrMaxValuesForAKey();
    Nod<K,V>* getStart();
    Nod<K,V>* getFinish();
    int getMax();
    int cautare(K,V);
    void sterge(K,V);
};

template <class K, class V>
Lista<K,V> :: Lista() : start(0),finish(0),list_size(0)
{
   cout<<"Lista constructor fara parametri"<<endl;
}


template <class K, class V>
void Lista<K,V> :: adaugare(K key, V value)
{
    if(list_size==0)
        {
            start=finish=new Nod<K,V>(key,value,NULL);
            list_size=1;
        }
    else
        {
            finish->setNext(new Nod<K,V>(key, value, NULL));
            list_size=list_size+1;
            finish=finish->getNext();
        }
    ordonare();
    cout<<"Element adaugat"<<endl;
}

//am ordonat elementele ca sa imi fie mai usor cand construiesc hashmap-ul
template <class K, class V>
void Lista<K,V> :: ordonare()
{
    Nod<K,V>* c;
    int ord;
    K aux_key;
    V aux_value;

    do
    {c=start;
     ord=1;
     while(c->getNext())
            {if(c->getKey() > c->getNext()->getKey())
                    {aux_key=c->getKey();
                     aux_value=c->getValue();
                     c->setKey(c->getNext()->getKey());
                     c->setValue(c->getNext()->getValue());
                     c->getNext()->setKey(aux_key);
                     c->getNext()->setValue(aux_value);
                     ord=0;
                    }
              c=c->getNext();
            }
    }
    while(ord==0);
    cout<<"Ordonare efectuata"<<endl;
}

//metoda pentru obtinerea numarului de chei distincte din HashMap
template <class K, class V>
int Lista<K,V> :: getKeyDistincte()
{
    int key_nr;
    if(list_size==0)
        key_nr=0;
    else
    {
        key_nr=1;
        Nod<K,V>*q=start;
        for(int i=0;i<list_size-1;i++)
        {
            if(q->getKey()!=q->getNext()->getKey())
            key_nr=key_nr+1;
            q=q->getNext();
        }
    }
    return key_nr;
}

template <class K, class V>
int Lista<K,V> :: getSize()
{
    return list_size;
}

template <class K, class V>
void Lista<K,V> :: show_list()
{
    Nod<K,V>* q=start;
    for(int i=0;i<list_size;i++)
        {
            cout<<"(key: "<<q->getKey()<<", "<<"value: "<<q->getValue()<<"); ";
            q=q->getNext();
        }
    cout<<endl;
}

//acesta va reprezenta numarul de coloane din hashmap
template <class K, class V>
int Lista<K,V> :: getNrMaxValuesForAKey()
    {
        int nr_max_values;
        if(list_size==0)
            nr_max_values=0;
        else
            {
            nr_max_values=1;
            int maxim=1;
            Nod<K,V>* q=start;
            for(int i=0;i<list_size-1;i++)
            {
            if(q->getKey()==q->getNext()->getKey())
                maxim=maxim+1;
            else
                {
                if(nr_max_values<maxim)
                    nr_max_values=maxim;
                maxim=1;
                }
                q=q->getNext();
            }
            }

        return nr_max_values;
    }

template <class K, class V>
Nod<K,V>* Lista<K,V> :: getStart()
{
    return start;
}

//acesta va reprezenta numarul de linii din hashmap
template <class K, class V>
int Lista<K,V> :: getMax()
{
    int key_max;
    key_max=-1;
    Nod<K,V>*q=start;
    for(int i=0;i<list_size;i++)
    {
        if(q->getKey()>key_max)
                key_max=q->getKey();
        q=q->getNext();
    }

    return key_max;
}

template <class K, class V>
int Lista<K,V> :: cautare(K key, V value)
{
    int gasit=0;
    Nod<K,V>* p=start;
    for(int i=0;i<list_size;i++)
    {
        if(p->getKey()==key&&p->getValue()==value)
        {
            gasit=1;
            break;
        }
        else
            p=p->getNext();
    }
    return gasit;
}

template <class K, class V>
void Lista<K,V> :: sterge(K key, V value)
    {
        if(cautare(key,value)==1)
        {
            Nod<K,V>* p=start;
            for(int i=0;i<list_size-1;i++)
            {
                if(p->getKey()==key && p->getValue()==value && i==0)
                {
                start=start->getNext();
                delete p;
                list_size=list_size-1;
                break;
                }
                else if(p->getNext()->getKey()==key && p->getNext()->getValue()==value)
                {
                    Nod<K,V>* q=p->getNext();
                    p->setNext(q->getNext());
                    delete q;
                    list_size=list_size-1;
                    break;
                }
                else
                    p=p->getNext();
            }
            cout<<"Elementul a fost sters cu succes"<<endl;
        }
        else
            cout<<"Elementul nu exista in hash map"<<endl;
    }



template <class K, class V>
class HashMap
{
    V **table;
    int table_rows;
    int table_columns;
public:
    HashMap();
    void create_table(Lista<K,V>);
    void table_show();
    void getVectorKey(K);
    V operator[] (K);
    friend ostream& operator<<(ostream&,const HashMap<K,V> h);
};

template<class K, class V>
HashMap<K,V> :: HashMap() : table_rows(0), table_columns(0)
{
    table= new V* [table_rows];
    for(int i=0;i<table_rows;i++)
        table[i]=new V [table_columns];
    cout<<"Hashtable constructor fara parametri"<<endl;
}

//citesc un element din lista, il adaug in hashmap iar daca urmatorul are aceeasi cheie, cresc numarul coloanei si il adaug,
//altfel trec la linie noua iar numarul coloanei devine 0
template<class K, class V>
void HashMap<K,V> :: create_table(Lista<K,V> lista)
{
    int i,j;
        table_rows=lista.getMax();
        table_columns=lista.getNrMaxValuesForAKey();
        table=new V*[table_rows];
        for( i=0;i<table_rows;i++)
            table[i]=new V[table_columns];

        int coloana=-1;

        Nod<K,V>*p=lista.getStart();
        if(lista.getSize()==1)
            {
                coloana=coloana+1;
                table[p->getKey()-1][coloana]=p->getValue();
            }
        else
            for(int i=0;i<lista.getSize()-1;i++)
            {
                if(p->getKey()!=p->getNext()->getKey()&&p->getNext()->getNext()==NULL)
                {
                    coloana=coloana+1;
                    table[p->getKey()-1][coloana]=p->getValue();
                    coloana=0;
                    table[p->getNext()->getKey()-1][coloana]=p->getNext()->getValue();
                }

                else if(p->getKey()==p->getNext()->getKey()&&p->getNext()->getNext()==NULL)
                {
                    coloana=coloana+1;
                    table[p->getKey()-1][coloana]=p->getValue();
                    coloana=coloana+1;
                    table[p->getNext()->getKey()-1][coloana]=p->getNext()->getValue();
                }

                else if(p->getKey()==p->getNext()->getKey())
                {
                    coloana=coloana+1;
                    table[p->getKey()-1][coloana]=p->getValue();
                }

                else if(p->getKey()!=p->getNext()->getKey())
                {
                    coloana=coloana+1;
                    table[p->getKey()-1][coloana]=p->getValue();
                    coloana=-1;
                }

                p=p->getNext();
            }
    cout<<"Hashtable creare"<<endl;
}

template <class K, class V>
void HashMap<K,V> :: table_show()
{
    if(table_rows==0)
        cout<<"HashMap gol"<<endl;
    else
    for(int i=0;i<table_rows;i++)
    {
        cout<<i+1<<": ";
        for(int j=0;j<table_columns;j++)
            cout<<table[i][j]<<' ';
        cout<<endl;
    }
    cout<<"Numarul de linii "<<table_rows<<" numarul de coloane "<<table_columns<<endl;
}

//metoda ce ıntoarce un vector (STL) cu valorile cunoscute pentru o anumita cheie
template <class K, class V>
void HashMap<K,V> :: getVectorKey(K key)
{
    vector<V> v;
    for(int i=0;i<table_columns;i++)
        v.push_back(table[key][i]);
    for(int i =0;i<v.size();i++)
        cout<<v[i]<<' ';
    cout<<endl;
}

//supraıncarcarea operatorului [] care ıntoarce prima valoare cunoscuta pentru o cheie
template <class K, class V>
V HashMap<K,V> :: operator[](K key)
{
    if(table[key][0]==" ")
        return 0;
    return table[key][0];
}

//supraıncarcarea operatorului de afisare
template <class K, class V>
ostream& operator<< (ostream& out,const HashMap<K,V> h)
{
    for(int i=0;i<h.table_rows;i++)
    {
        for(int j=0;j<h.table_columns;j++)
        {
            cout << h.table[i][j] << ' ';
        }
        cout << endl;
    }
    return out;
}

int main()
{
int cheie;
string valoare;
Lista<int,string> lista;
HashMap<int,string> hashmap;
int operatie;
cout<<"1.Adaugare\n2.Cautare\n3.Stergere\n4.Vector de valori ale unei chei\n5.Numar chei distincte\n6.Prima valoare a unei chei\n7.Afisare\n8.Exit"<<endl;
while(1<2)
{
    cout<<"Alegeti o operatie: ";
    cin>>operatie;
    if(operatie==1)
    {
        cout<<"Adaugati:\nCheie: ";
        cin>>cheie;
        cout<<"Valoare: ";
        cin>>valoare;
        lista.adaugare(cheie,valoare);
    }
    else if(operatie==2)
    {
        cout<<"Cautati:\nCheia: ";
        cin>>cheie;
        cout<<"Valoare: ";
        cin>>valoare;
        if(lista.cautare(cheie,valoare)==1)
            cout<<"Element gasit!"<<endl;
        else
            cout<<"Nu s-a gasit!"<<endl;
    }
    else if(operatie==3)
    {
        cout<<"Stergeti:\nCheia: ";
        cin>>cheie;
        cout<<"Valoare: ";
        cin>>valoare;
        lista.sterge(cheie,valoare);
    }
    else if(operatie==4)
    {
        cout<<"Vector de valori pentru cheia: ";
        cin>>cheie;
        cout<<"Vector pentru cheia "<<cheie<<" : ";
        hashmap.getVectorKey(cheie-1);

    }
    else if(operatie==5)
    {
        cout<<"Numarul de chei distincte: "<<lista.getKeyDistincte()<<endl;
    }
    else if(operatie==6)
    {
        cout<<"Prima valoare pentru cheia: ";
        cin>>cheie;
        cout<<"Prima valoare pentru cheia "<<cheie<<" este: "<<hashmap[cheie-1]<<endl;

    }
    else if(operatie==7)
    {
        hashmap.create_table(lista);
        hashmap.table_show();
        //cout <<"Hashmap:\n" << hashmap;
    }
    else if(operatie==8)
    {
        cout<<"La revedere!"<<endl;
        break;
    }
}
cout<<"Iesire din program"<<endl;
    return 0;
}



