

class TObject{

    private:
        int posx;
        int posy;
        int height;
        int width;
        int color;

    public:
        TObject();
        ~TObject();
        void SetPosx(int aPosx){posx = aPosx;};
        int GetPosx(){return posx;};

        void SetPosy(int aPosy){posy = aPosy;};
        int GetPosy(){return posy;};

        void SetWidth(int aWidth){width = aWidth;};
        int GetWidth(){return width;};

        void SetHeight(int aHeight){height = aHeight;};
        int GetHeight(){return height;};

};

TObject::TObject(){
    posx = 0;
    posy = 0;
    height = 1;
    width = 10;
}