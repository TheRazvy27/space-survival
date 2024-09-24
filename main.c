#include <stdio.h>
#include "graphTe.h"
#include <time.h>
#include <stdlib.h>
float deltaTime;
int point=0;
char points[100];
typedef struct {float x;float y;int hitboxx;int hitboxy;}entity;
entity player;
#define enemycount 64
entity enemys[enemycount];
void start()
{
    player.x=250;
    player.y=750;
    player.hitboxx=33;
    player.hitboxy=66;
    for(int i=0;i<enemycount;i++) {
        enemys[i].hitboxx = 6;
        enemys[i].hitboxy = 2;
        srand(clock()*time(0)*i);
        if(i%2==0)
            enemys[i].x=-50*(i+1);
        else
        enemys[i].x=800+((i+1)*50);
        int ypos=800;
        while(ypos>700)
            ypos=rand()%(800-enemys[i].hitboxx);
        enemys[i].y=ypos;
        for(int j=0;j<enemycount;j++)
        {
            if(enemys[i].x<enemys[j].x+enemys[j].hitboxx && enemys[i].x+enemys[i].hitboxx>enemys[j].x && enemys[i].y<enemys[j].y+enemys[j].hitboxy && enemys[i].y+enemys[i].hitboxy>enemys[j].y && i != j)
            {
                enemys[i].y=-1000*(i+1);
                enemys[i].x=-1000*(i+1);
            }
        }
    }
}
void render()
{
    fill(rgb(0,0,0));
    for(int i=0;i<enemycount;i++)
        transparentImage(enemys[i].x, enemys[i].y, enemys[i].hitboxx, enemys[i].hitboxy, "resources/dot.bmp", rgb(118, 118, 118));
    transparentImage(player.x,player.y,player.hitboxx,player.hitboxy,"resources/racheta.bmp",rgb(0,0,0));
    sprintf(points,"%d",point);
    text(285,725,points,rgb(255,255,255));
    display();
}
void senemy(int i)
{
    srand(clock()*time(0)*i);
        if(i%2==0)
            enemys[i].x=-50*(i+1);
        else
        enemys[i].x=800+((i+1)*50);
        int ypos=800;
        while(ypos>700)
            ypos=rand()%(800-enemys[i].hitboxx);
        enemys[i].y=ypos;
        for(int j=0;j<enemycount;j++)
        {
            if(enemys[i].x<enemys[j].x+enemys[j].hitboxx && enemys[i].x+enemys[i].hitboxx>enemys[j].x && enemys[i].y<enemys[j].y+enemys[j].hitboxy && enemys[i].y+enemys[i].hitboxy>enemys[j].y && i != j)
            {
                enemys[i].y=-1000*(i+1);
                enemys[i].x=-1000*(i+1);
            }
        }
}
void movement()
{
    deltaTime=(clock()-deltaTime);
    deltaTime=(float)deltaTime/CLOCKS_PER_SEC;
    if(checkKeyLiveInput(VK_UP))
    {
        player.y-=(deltaTime*500)*0.7;
        if(player.y<0)
        {
            player.y+=deltaTime*500;
             point++;
             player.y=750;
        }
    }
    else if(checkKeyLiveInput(VK_DOWN))
    {
        player.y+=(deltaTime*500)*0.7;
        if(player.y>800)
            player.y-=deltaTime*500;
    }
    for(int i=0;i<enemycount;i=i+2)
    {
        enemys[i].x+=0.2*(deltaTime*1000);
        if(enemys[i].x>600)
            senemy(i);
    }
    for(int i=1;i<enemycount;i=i+2)
    {
        enemys[i].x-=0.2*(deltaTime*1000);
        if(enemys[i].x<1)
            senemy(i);
    }
    deltaTime=clock();
    for(int i=0;i<enemycount;i++)
    {
        if(enemys[i].x<player.x+player.hitboxx && enemys[i].x+enemys[i].hitboxx>player.x && enemys[i].y<player.y+player.hitboxy && enemys[i].y+enemys[i].hitboxy>player.y)
        {
            image(0,0,600,800,"resources/gameover.bmp");
            sprintf(points,"%d",point);
            text(285,725,points,rgb(255,255,255));
            display();
            Sleep(10000);
                exit(0);
        }
    }
}
int main()
{
    initHost();
    setWindowTitle("Space Survival");
    setWindowSize(600,800);
    update();
    image(0,0,600,800,"resources/start.bmp");
    display();
    forceInput();
    start();
    while(1<2) {
        movement();
    render();
    }
    releaseHost();
}