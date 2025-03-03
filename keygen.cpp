#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Music.hpp>

#include <sys/stat.h>
#include <math.h>

const float EPSILON = 0.01;

typedef struct point
{
    float x;
    float y;
}
Point;

typedef struct PicturePosition
{
    int width;
    int height;
    point UL;
    float delta_x;
    float delta_y;
}
PicPos;

void patcher();
void ChangeDirection( PicPos position );

int main()
{
    sf::RenderWindow window(sf::VideoMode( 854, 480 ), "keygen_window");

    //-----------image work----------------------
    bool move_to_right = true;
    sf::Texture texture;
    texture.loadFromFile("trolpic.jpg");
    PicPos position_1 = {};
    position_1.width = 320;
    position_1.height = 180;
    position_1.UL = { 0.0f, 0.0f };
    position_1.delta_x = 2.0f;
    position_1.delta_y = 0.0f;

    sf::Sprite sprite1(texture);
    sprite1.setScale(0.5f, 0.5f);
    // float x_position_1 = 150.0f, y_position_1 = 40.0f;

    bool progress_ready = false;
    sf::Texture progress_frame;
    progress_frame.loadFromFile("frame.png");
    sf::Sprite sprite2(progress_frame);
    sprite2.setScale(1.0f, 1.0f);
    float x_position_2 = 0.0f, y_position_2 = 400.0f;

    sf::Texture progress_bar;
    progress_bar.loadFromFile("bar.png");
    sf::Sprite sprite3(progress_bar);
    float x_position_3 = 148.3f, y_position_3 = 408.0f;
    float x_scale_3 = 0.0f, y_scale_3 = 1.0f;
    sprite3.setScale( x_scale_3, y_scale_3 );
    //-------------------------------------------

    //-------------Text--------------------------
    sf::Font font;
    font.loadFromFile("PixelGame.otf");
    sf::Text text1("your code was cracked =)", font, 40);
    text1.move( 240.0f, 360.0f );

    bool music_is_playing = true;
    sf::Text text2("Space ->  play music\n"
                   "BackSpace -> stop  ", font, 20);
    text2.move( 20.0f, 280.0f );
    //-------------------------------------------

    //---------------Clock-----------------------
    sf::Clock clock;
    window.setFramerateLimit(60);
    //-------------------------------------------

    //---------------Music-----------------------
    sf::Music music;
    music.openFromFile("Cyberpunk_8_bit.mp3");
    //-------------------------------------------

    music.play();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
            
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    if( !music_is_playing )
                    {
                        music.play();
                        music_is_playing = true;
                    }   
                }
                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    music.pause();
                    music_is_playing = false;
                }
                else 
                {
                    printf("key pressed\n");
                }
            }
        }

        //----------moving sprite1----------------
        sprite1.setPosition( position_1.UL.x, position_1.UL.y );

        // if( move_to_right )
        // {
        //     position_1.delta_x = 2.0f;
        // }
        // else 
        // {
        //     position_1.delta_x =-2.0f;      
        // }
        void ChangeDirection( PicPos position );
        position_1.UL.x += position_1.delta_x;
        position_1.UL.y += position_1.delta_y;

        // if( position_1.UL.x >= 350 )
        // {
        //     move_to_right = false;
        // }
        // if( position_1.UL.x <= 150.5 )
        // {
        //     move_to_right = true;
        // }


        //--------------sprite2-------------------
        sprite2.setPosition( x_position_2, y_position_2 );

        //-----------------sprite3----------------
        sprite3.setPosition( x_position_3, y_position_3 );
        sprite3.setScale( x_scale_3, y_scale_3 );

        if( !progress_ready )
        {
            x_scale_3 += 0.001f;    
        }
        if( x_scale_3 >= 0.999f ) 
        {
            progress_ready = true;
            
            patcher();
        }
        //---------------------------------------

        //clear previous frame
        window.clear();

        if( progress_ready )
        {
            window.draw(text1);
        }
        
        //-------draw---------
        window.draw(text2);
        window.draw(sprite2);
        window.draw(sprite3);
        window.draw(sprite1);
        //--------------------
        
        window.display();
    }

    return 0;
}


void ChangeDirection( PicPos position )
{
    float monitor_height = 480.0f;
    float monitor_width = 854.0f;
    
    //Left corner 
    if( position.UL.x < EPSILON )
    {
        position.delta_x = 2.0f; 

        if( position.UL.y < EPSILON )
        {
            position.delta_y = -2.0f;
        }
        else if( fabs( position.UL.y + position.height - monitor_height ) < EPSILON )
        {   
            position.delta_y = 2.0f; 
        }
    }
    //Right corner 
    else if( fabs( position.UL.x + position.width - monitor_width ) < EPSILON )
    {
        position.delta_x = -2.0f;

        if( position.UL.y < EPSILON )
        {
            position.delta_y = -2.0f;
        }
        else if( fabs( position.UL.y + position.height - monitor_height ) < EPSILON )
        {   
            position.delta_y = 2.0f; 
        }
    }
}


void patcher()
{
    FILE* stream = fopen( "CRACKME.com", "rb+" );
    struct stat file_info = {};
    stat("CRACKME.com", &file_info );
    int buffer_size = file_info.st_size;
    if( stream == nullptr )
    {
        printf("No file to patch\n");
        exit(1);
    }
    char* buffer = (char* )malloc( buffer_size );

    fread( buffer, buffer_size, 1, stream );

    *(buffer + 43) = 0x07;

    fseek( stream, 0L, SEEK_SET );

    fwrite( buffer, buffer_size, 1, stream );

    fclose( stream );
}
