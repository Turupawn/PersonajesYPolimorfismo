//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include "Enemigo.h"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 572;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *up = NULL;
SDL_Surface *down = NULL;
SDL_Surface *left = NULL;
SDL_Surface *right = NULL;
SDL_Surface *mina = NULL;
SDL_Surface *screen = NULL;

//Sound
Mix_Chunk *sound = NULL;


//The event structure
SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;



    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    return loadedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }


    //Iniciando SDL_Mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "Endless Run/backmountain.png" );

    //Cargando sound
    sound = Mix_LoadWAV("select.wav");



    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 72 );

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    if(sound == NULL)
    {
        return false;
    }


    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( up );
    SDL_FreeSurface( down );
    SDL_FreeSurface( left );
    SDL_FreeSurface( right );

    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();
}

class Punto
{
public:
    int x;
    int y;

    Punto(int x, int y)
    {
        this->x = x;
        this->y = y;

    }

    Punto()
    {

    }

};

class Rectangulo
{

public:
    Punto p;
    int w;
    int h;
    Rectangulo(Punto p, int w, int h)
    {
        this->p = p;
        this->w = w;
        this->h = h;

    }

};

bool puntodentrorect(Punto p, Rectangulo r)
{
    if(p.x>=r.p.x && p.x<=r.p.x+r.w && p.y>=r.p.y &&p.y<=r.p.y+r.h)
    {
        return true;
    }
    return false;

}


bool colision(int x1 , int y1 , int w1, int h1,int x2, int y2 , int w2, int h2)
{
    if(puntodentrorect(Punto(x2, y2), Rectangulo(Punto(x1,y1),w1,h1)))
    {
        return true;
    }
    if(puntodentrorect(Punto(x2+w2, y2), Rectangulo(Punto(x1,y1),w1,h1)))
    {
        return true;
    }
    if(puntodentrorect(Punto(x2, y2+h2), Rectangulo(Punto(x1,y1),w1,h1)))
    {
        return true;
    }
    if(puntodentrorect(Punto(x2+w2, y2+h2), Rectangulo(Punto(x1,y1),w1,h1)))
    {
        return true;
    }

    return false;


}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Render the text
    up = TTF_RenderText_Solid( font, "Up", textColor );
    down = TTF_RenderText_Solid( font, "Down", textColor );
    left = TTF_RenderText_Solid( font, "Left", textColor );
    right = TTF_RenderText_Solid( font, "Right", textColor );


    SDL_Surface *personaje[4];
    personaje[0]= load_image("Endless Run/run01.png");
    personaje[1]= load_image("Endless Run/run02.png");
    personaje[2]= load_image("Endless Run/run03.png");
    personaje[3]= load_image("Endless Run/run04.png");

    SDL_Surface *ghost[3];
    ghost[0]= load_image("Endless Run/volador01.png");
    ghost[1]= load_image("Endless Run/volador02.png");
    ghost[2]= load_image("Endless Run/volador03.png");

    Enemigo bomba(800,250,load_image("Endless Run/bomba01.png"));
    int bombax = 700;
    int bombay = 250;



    SDL_Surface *jump = load_image("Endless Run/jump.png");

    SDL_Surface *montanas = load_image("Endless Run/mountains.png");
    int i = 0;
    int frame = 0;
    int frames = 0;
    int pospersonajey = 250;
    int pospersonajex = 0;
    int posghosty = 280;
    int posghostx = 400;
    int flote = 1000;



    int velocidady = 0;
    int accy = 2;
    int altura = 30;

    int mountainpos = 0;

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Apply the background
        apply_surface( 0, 0, background, screen );



        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState( NULL);

        pospersonajey+= velocidady;
        velocidady+=accy;

        if(pospersonajey>= 250)
        {
            pospersonajey = 250;
        }

        if(keystates[SDLK_SPACE])
        {
            Mix_PlayChannel( -1, sound, 0 );
            Mix_VolumeChunk(sound, 40);
            if(pospersonajey==250)
                velocidady= -altura;

        }



        apply_surface(mountainpos , 0, montanas, screen);

        bomba.avanzar();
        bomba.imprimir(screen);


        apply_surface(flote, posghosty, ghost[frames], screen);

        if(pospersonajey == 250)
            apply_surface(pospersonajex,pospersonajey,personaje[frame], screen);
        else
            apply_surface(pospersonajex,pospersonajey,jump, screen);

        mountainpos-=5;
        flote-=8;
        posghosty-=0.5;
        bombax -= 8;
        if(bombax < -bomba->w)
        {
            bombax = 700;
        }

        int px = pospersonajex;
        int py = pospersonajey;
        int pw = personaje[frame]->w;
        int ph = personaje[frame]->h;

        int bx = bombax;
        int by = bombay;
        int bw = bomba->w;
        int bh = bomba->h;

        if(colision(px+pw/6, py+ph/6, pw/4,ph/4, bx+bw/6, by+bh/6, bw/4, bh/4))
        {

            exit(0);

        }


        if(mountainpos <-1726)
        {
            mountainpos =0;
            flote = 1000;
            posghosty = 280;
        }


        i++;
        if(i%20 == 0)
        {
            frames++;
            frame++;
            if(frame>3)
                frame = 0;

            if(frames>2)
                frames = 0;

        }


        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}
