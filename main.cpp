#include <bits/stdc++.h>
#include <string>
using namespace std;

template <class V, class E>
class Grafo
{
private: 
    map< V , map<V , E>> m_Grafo;
    set<V> tesoros;
    int ** matrix; 
public:
    Grafo() {
    }
    /////////////////////CREAR GRAFO////////////////////////
    void crearGrafo()
    {
        if(!m_Grafo.empty()) m_Grafo.clear();
        cout<<"grafo vacio";
    }
    /////////////////////INSERTAR NODO////////////////////////
    void insertarNodo(V valor , int x)
    {
        if(x) tesoros.insert(valor);
        m_Grafo[valor];  
    }
    /////////////////////INSERTAR ARISTA////////////////////////
    void insertarArista(V a, V b, E arista)
    {
        if(existeNodo(a) && existeNodo(b))
        {
           m_Grafo[a][b] = arista;   
           m_Grafo[b][a] = arista;   
        }
    }
    /////////////////////BORRAR NODO////////////////////////
    void borrarNodo(V x) 
    {
        for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++) {
            if (it->first == x){
                for (auto its = (it->second).begin() ; its != (it->second).end() ; its++){
                    for( auto i= m_Grafo.begin() ; i != m_Grafo.end() ; i++) {
                        if (i->first==its->first){
                            for (auto j = (i->second).begin() ; j != (i->second).end() ; j++){
                                if(j->first==x){
                                    j=(i->second).erase(j);  
                                }
                            } 
                        }
                    }     
                }
                it=m_Grafo.erase(it);  
            }   
        }  
    }
    /////////////////////BORRAR ARISTA////////////////////////
    void borrarArista(V a, V b)
    {
        auto it = m_Grafo.find(a);
        if(it != m_Grafo.end())
        {
            auto to = (it->second).find(b);
            if(to != (it->second).end()) 
            {
                it->second.erase(to);
                auto it = m_Grafo.find(b);
                auto to = (it->second).find(a);
                it->second.erase(to);
            }
        }
    }
    /////////////////////ES VACIO////////////////////////
    bool esVacio()
    {
        if(m_Grafo.empty()) return true;
        return false;
    }
    /////////////////////EXISTE NODO////////////////////////
    bool existeNodo(V a)
    {
        auto it = m_Grafo.find(a);
        if(it != m_Grafo.end()) return true;
        return false;
    }

    /////////////////////SON ADYACENTES////////////////////////
    bool sonAdyacentes(V a, V b) // si existe una arista entre 2 nodos
    {
        if(m_Grafo[a][b]) return true;
        return false;
    }
    /////////////////////VER ADYACENCIAS////////////////////////
    void verAdyacencia() // Imprime lista de adyacencias
    {
        for(auto it = m_Grafo.begin() ; it != m_Grafo.end() ; it++) {
            for (auto its = (it->second).begin() ; its != (it->second).end() ; its++)
                std::cout << it->first<< "->" << its->first << ": "<<its->second<<endl;
            cout<<endl;
        }
    }

    /////////////////////GRAFICAR GRAFO////////////////////////
    void graficar()
    {
        ofstream arch;
        arch.open("D:\\Graphviz\\bin\\graphL10.dot");
        if (arch.is_open())
        {
            arch << "strict graph A { \n";
            for(auto i = m_Grafo.begin() ; i != m_Grafo.end() ; i++) {
               arch<<i->first;
               if(tesoros.find(i->first) != tesoros.end()) arch<<"[color = "<<"red];";
               arch<<endl;
               for (auto j = (i->second).begin() ; j != (i->second).end() ; j++) {
                    arch<<j->first;
                    if(tesoros.find(j->first) != tesoros.end()) arch<<"[color = "<<"red];";
                    arch<<endl;
                    if(m_Grafo[i->first][j->first] == '1') {
                        arch << i->first << "--" <<j->first << "[label=" << m_Grafo[i->first][j->first] << ", ]" << endl;
                    }
                }
            }
            arch << "}\n";
            arch.close();
            system("dot -Tpng D:\\Graphviz\\bin\\graphL10.dot -o D:\\Graphviz\\bin\\graphL10.png ");
            system("D:\\Graphviz\\bin\\graphL10.png ");
        }
        else
        {
            cout << "error al crear archivo";
        }
    }

    /////////////////////BFS////////////////////////
    bool BFS(V inicio)
    {
        map<V, int> visitados;
        visitados[inicio] = 0;
        return BFS(inicio, visitados, 0, 0);
    }

    bool BFS(V inicio, map<V, int> visitados, int i, int pos)
    {
        auto it = m_Grafo.find(visitado(visitados, pos));
        for (auto ito = (it->second).begin(); ito != (it->second).end(); ito++)
        {
            if (visitados.find(ito->first) == visitados.end())
            {
                i++;
                visitados[ito->first] = i;
                visitado(visitados);
                if (tesoros.find(ito->first) != tesoros.end())
                    return true;
            }
        }

        if (pos == i)
            return false;
        else
        {
            int a = pos++;
            return BFS(inicio, visitados, i, pos);
        }
    }
    

    /////////////////////DFS////////////////////////
    bool DFS(int inicio)
    {
        int pos = 0, i = 0;
        auto it = m_Grafo.find(inicio); auto ito = (it->second).begin();
        map<V,int> visitados;
        visitados[it->first] = i;
        while(pos != -1 && tesoros.find(it->first) == tesoros.end())
        {
            while(ito != (it->second).end() && visitados.find(ito->first) == visitados.end())  
            {
                i++;
                visitados[ito->first] = i;
                visitado(visitados);
                it = m_Grafo.find(ito->first);
                ito = (it->second).begin(); 
                pos++;  
            }

            auto aux = ito;
            aux++;
                cout<<"it"<<it->first<<" ";
                cout<<"ito"<<ito->first<<endl;
                if(aux != (it->second).end())  
                {
                    ito++;
                } else {
                    pos--;
                    cout<<"pos: "<<pos<<" "<<visitado(visitados , pos)<<" ";
                    it = m_Grafo.find(visitado(visitados , pos));
                    ito = it->second.begin();
                }
        }
        if(it != m_Grafo.end() && tesoros.find(it->first) != tesoros.end()) return true;
        return false;
    }

   
    void visitado(map<V,int> set)
    {
        
        cout<<"Vector: "<<endl;
        for(auto i = set.begin() ; i != set.end() ; i++ )
        {
            cout<<i->first<<" ";
        }
        cout<<endl;
    }

    int visitado(map<V,int> set , int m)
    {
        
        cout<<"vectorsito"<<endl;
        for(auto i = set.begin() ; i != set.end() ; i++ )
        {
             if(i->second == m) return i->first;
        }
        cout<<endl;
    }

    ~Grafo() {
    }
};

int main()
{
    Grafo<int , char> G;

    // G.insertarNodo(1,0);
    // G.insertarNodo(2,0);
    // G.insertarNodo(3,0); 
    // G.insertarNodo(4,0);
    // G.insertarNodo(5,0);
    // G.insertarNodo(6,0);
    // G.insertarArista(1,3,'1');
    // G.insertarArista(2,3,'1');
    // G.insertarArista(4,3,'1');
    // G.insertarArista(5,3,'1');
    // G.borrarArista(1,3);
    //  G.borrarArista(5,3);
    //   G.borrarArista(4,5);
    int a = 4 ; int b = 3;
    cin>>a>>b;
    char o;
    int car = 1;

    for(int i = 0; i < a ; i++ )
    {
        for(int j = 0; j < b ; j++ )
        {
            cin>>o;
                if(0 != 'X')
                {
                    if(o == '.') {
                    G.insertarNodo(car , 0);
                }else if(o == 't') {
                    G.insertarNodo(car , 1);
                }
                if(j!= 0 && G.existeNodo(car - 1))
                {
                    G.insertarArista(car,car - 1,'1');
                }
                if(i!= 0 && G.existeNodo(car - b))
                {
                    G.insertarArista(car,car - b,'1');
                }
            }
            car++;
        } 
    }

    int y;
    cin>>a>>y;

    if(G.DFS((a-1)*(b) + y)) cout<<"yes";
    else cout<<"No";

    G.verAdyacencia();
    G.graficar();

    
    return 0;
}
