#include "body.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class PhysicsSolver{
    public :
        void PhysicsStep(vector<body> &a ,float dt)
        {
            for(auto& i : a)
            {
                if(i.isDestroyed) continue;
                i.prev_dxa = i.dxa;
                i.prev_dya = i.dya;
                i.x += (i.dxv*dt) + (0.5f*i.dxa*dt*dt);
                i.y += (i.dyv*dt) + (0.5*i.dya*dt*dt);
                i.dxa = 0;
                i.dya = 0;
            }
            for(auto& i : a)
            {
                if (i.isDestroyed) continue;
                float x_force = 0;
                float y_force = 0;
                for(auto& j : a)
                {
                    if(&i == &j || j.isDestroyed) continue;
                    float force = 0;
                    float dis = pow(abs(j.x - i.x),2) + pow(abs(j.y - i.y),2);
                    if (dis == 0)continue;
                    if(sqrt(dis) <= i.r + j.r) continue;
                    force = (i.m*j.m)/dis;
                    x_force += force*(j.x - i.x)/sqrt(dis);
                    y_force += force*(j.y - i.y)/sqrt(dis);
                }
                i.applyForce(x_force,y_force);
            }
            for(auto& i : a) 
            {
                if(!i.isDestroyed)
                {
                    i.dxv += 0.5f*(i.prev_dxa + i.dxa)*dt;
                    i.dyv += 0.5f*(i.prev_dya + i.dya)*dt; 
                } 
            }

            for(size_t i = 0; i<a.size();i++)
            {
                if(a[i].isDestroyed) continue;
                for(size_t j = i+1 ; j< a.size();j++)
                {
                    if(a[j].isDestroyed) continue;
                    float dx = a[j].x - a[i].x;
                    float dy = a[j].y - a[i].y;
                    float dis = sqrt((dx*dx) + (dy*dy));
                    if(dis <= a[i].r + a[j].r)
                    {
                        float new_m = a[i].m + a[j].m;
                        a[i].dxv = ((a[i].m*a[i].dxv) + (a[j].m*a[j].dxv))/new_m;
                        a[i].dyv = ((a[i].m*a[i].dyv) + (a[j].m*a[j].dyv))/new_m;
                        a[i].m = new_m;
                        a[i].r = sqrt(pow(a[i].r,2) + pow(a[j].r,2));
                        a[j].isDestroyed = true;
                        a[j].m = 0;
                    }
                }
            }
           a.erase(remove_if(a.begin(), a.end(), [](const body& b) {
            return b.isDestroyed;
            }), a.end());
        }
};