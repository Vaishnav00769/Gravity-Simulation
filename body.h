#pragma once
class body{
    public :
        float x,y,dxa,dya,dxv,dyv,m,r,prev_dxa,prev_dya;
        bool isDestroyed = false;
        body(float m,float r, float x , float y){
            this->m = m;
            this->r = r;
            this->x = x;
            this->y =y;
            this->dxv = 0;
            this->dyv = 0;
            this->dxa = 0;
            this->dya = 0;
            this->prev_dxa = 0;
            this->prev_dya = 0;
            this -> isDestroyed = false;
        }
        void applyForce(float xforce,float yforce)
        {
            this->dxa = xforce/this->m;
            this->dya = yforce/this->m;
        }
};