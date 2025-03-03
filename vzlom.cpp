#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* stream = fopen( "mod.com", "rb+" );
    char* buffer = (char* )malloc( 200 );

    fread( buffer, 200, 1, stream );

    *(buffer + 43) = 0x07;

    fseek( stream, 0L, SEEK_SET );

    fwrite( buffer, 200, 1, stream );

    fclose( stream );

    return 0;
}
    