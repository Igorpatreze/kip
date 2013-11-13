extern "C"{
#include "../src/kip.h"
}
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

#define LEFT   0
#define UP     1
#define RIGHT  2
#define DOWN   3

#define SIZE 20

struct Cor{
public:
    int x, y;
    int xinc[4];
    int yinc[4];
    Cor(int x=0, int y=0)
    {
        this->x = x;
        this->y = y;
        xinc[LEFT] = -1;
        xinc[UP] =  0;
        xinc[RIGHT] =  1;
        xinc[DOWN] =  0;

        yinc[LEFT] = 0;
        yinc[UP]   = -1;
        yinc[RIGHT] = 0;
        yinc[DOWN] = 1;
    }
    Cor move(int dir)
    {
        return Cor(x+xinc[dir], y+yinc[dir]);
    }
};

class Cell{
public:
    bool wall[4];
    bool visited;
    Cor c;
    Cell(): c(0,0){

    }
    void set(int x, int y){
        wall[0]=1;
        wall[1]=1;
        wall[2]=1;
        wall[3]=1;
        visited = 0;
        c = Cor(x,y);
    }
    void draw(char color=' ', int sleep=10)
    {
        if(color != ' ')
        {
            fmt_color(color);
            k_square(c.x + 0.5, c.y + 0.5, fmt_get()->block -10, 1);
            if(sleep!=0)
                k_sleep(sleep);
        }
        fmt_color('K');
        int x = c.x;
        int y = c.y;
        char cor_linha = 'K';
        char cor_fundo = 'w';

        fmt_color(cor_fundo);
        if(!wall[LEFT])
            k_line(x,y,x,y+1);
        if(!wall[UP])
            k_line(x,y,x+1,y);
        if(!wall[RIGHT])
            k_line(x+1,y,x+1,y+1);
        if(!wall[DOWN])
            k_line(x,y+1,x+1,y+1);
        fmt_color(cor_linha);
        if(wall[LEFT])
            k_line(x,y,x,y+1);
        if(wall[UP])
            k_line(x,y,x+1,y);
        if(wall[RIGHT])
            k_line(x+1,y,x+1,y+1);
        if(wall[DOWN])
            k_line(x,y+1,x+1,y+1);
    }

};

class Maze{
private:
    Cell *vec;
    int nl;
    int nc;
public:
    int delay;
    Maze(int nl_, int nc_)
    {

        nc = nc_;
        nl = nl_;
        delay = 10;
        vec = new Cell[nl*nc];
        for(int i = 0; i < nl; i++)
            for(int j = 0; j < nc; j++){
                vec[i*nc+j].set(j,i);
                vec[i*nc+j].draw();
            }
    }
    Cell & get(Cor c){
        return vec[c.y*nc+c.x];
    }

    bool inside(Cor c)
    {
        if(c.x<0 || c.x>=nc)
            return 0;
        if(c.y<0 || c.y>=nl)
            return 0;
        return 1;
    }

    void break_wall(Cor c, int dir)
    {
        if(!inside(c))
            return;
        get(c).wall[dir] = 0;
        get(c).visited   = 1;
    }
    void quebra_dupla(Cor c, int dir){
        break_wall(c, dir);
        break_wall(c.move(dir), (dir+2)%4);
    }
    void draw(){
        fmt_color('w');
        for (int i = 0; i < nl*nc; i++)
            vec[i].draw('w',0);
    }
    bool is_visited(Cor c)
    {
        if(!inside(c))
            return 1;
        return get(c).visited;
    }

    /* Retorna a direcao escolhida ou -1 */
    int select_not_visited(Cor c){
        std::vector<int> vizinhos;
        for(int i = 0;i<4;i++)
            if(! is_visited(c.move(i)))
                vizinhos.push_back(i);
        if(vizinhos.empty())
            return -1;

        return vizinhos[km_rand()%vizinhos.size()];
    }



    void construct(){

        std::stack<Cor> pilha;
        pilha.push(Cor(0,0));
        for(;;)
        {
            Cor c = pilha.top();
            int d = select_not_visited(c);
            if(d == -1)
            {
                get(pilha.top()).draw('w', delay);
                pilha.pop();
                if(pilha.empty())
                    break;
                get(pilha.top()).draw('w', delay);
            }
            else
            {
                Cor p = c.move(d);
                quebra_dupla(c, d);
                pilha.push(p);
                get(p).draw('Y', delay);
            }
        }
    }

    int select_choice(Cor c){
        std::vector<int> vizinhos;
        for(int i = 0;i<4;i++)
            if(!is_visited(c.move(i)) && !get(c).wall[i])
                vizinhos.push_back(i);
        if(vizinhos.empty()){
            return -1;

        }
        return vizinhos[km_rand()%vizinhos.size()];
    }

    void path(Cor b, Cor e)
    {
        get(b).draw('g');
        get(e).draw('r');
        std::stack<Cor> pilha;
        pilha.push(Cor(b));
        for(;;)
        {
            Cor c = pilha.top();
            int d = select_choice(c);
            if(d == -1)
            {
                get(pilha.top()).draw('c', delay);
                pilha.pop();
                if(pilha.empty())
                    break;
                get(pilha.top()).draw('y', delay);
            }
            else
            {
                Cor p = c.move(d);
                if(p.x == e.x && p.y == e.y)
                    break;
                get(p).visited = 1;
                pilha.push(p);
                get(p).draw('Y', delay);
            }
        }
    }
    void clear_visited()
    {
        for(int i=0; i < nc*nl; i++)
            vec[i].visited = 0;
    }
};




int main()
{
    k_open(800, 600, "labirinto");
    fmt_block(10);
    k_clear('w');
    Maze mat(60, 80);
    mat.delay = 0;
    mat.construct();
    mat.delay = 0;
    Cor b, e;
    while(1){
        mat.draw();
        mat.clear_visited();
        k_wait();
        b.x = k_xpos();
        b.y = k_ypos();
        mat.get(b).draw('g');
        k_wait();
        e.x = k_xpos();
        e.y = k_ypos();
        mat.get(e).draw('r');
        mat.path(b,e);
        k_wait();
    }
    //criando um caminho aleatorio
    k_wait();//bloqueia esperando uma acao do usuario
    return 0;
}





