#include "keygen.h"

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
