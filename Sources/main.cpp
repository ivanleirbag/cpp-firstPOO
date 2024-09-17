#include <cstring>
#include <ncurses.h>

//g++ -Wall ./main.cpp -o main -lncurses

class TObject{

    private:
        int posx;
        int posy;
        int height;
        int width;
        int color;

    public:
        TObject();

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

class LabelObj : public TObject{
    
    private:
        char text[256] = {0};
        enum TEXT_ALIGN {LEFT = 0, CENTER, RIGHT};
        int align;
        char *str;


    public:
        LabelObj();

        void setTxt(char* str);
        char* getTxt(){return text;};

        void SetAlign(int aAlign) { align = aAlign; }
        int GetAlign() { return align; }
        
        void ShowText();

};

LabelObj::LabelObj() {
    align = LEFT;
}

void LabelObj::setTxt(char* str) {
    strncpy(text, str, sizeof(text) - 1);
    text[sizeof(text) - 1] = '\0';  
}

void LabelObj::ShowText(){
    int y = GetPosy();  
    int x = GetPosx();  
    
    move(y, x);
    
    printw("%s", text);

    refresh();
}



int main(){
    initscr();
    LabelObj lbl;

    lbl.SetPosx(16);
    lbl.SetPosy(1);

    lbl.setTxt("HOLA PROBANDO");

    lbl.ShowText();

    getch();

    endwin();

    return 0;
}