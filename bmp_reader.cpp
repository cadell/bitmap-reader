#include <iostream>
#include <fstream>
#include <vector>

/*Pramga pack prevents the compiler from padding the struct.*/
#pragma pack(push,1)
typedef struct 
{
    unsigned short signature;
    unsigned int file_size;
    unsigned int reserved;// might have include reserved 2
    unsigned int datra_offset;
}Header;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct
{
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int image_size;
    unsigned int x_pix_per_m;
    unsigned int y_pix_per_m;
    unsigned int colors_used;
    unsigned int important_colors;
}InfoHeader;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct 
{
    char red;
    char green;
    char blue;
    char reserved;
}ColorTable; //this struct should only be part of the img iff bpp is < 8
#pragma pack(pop)

auto calc_img_size(unsigned int bpp, unsigned int image_width, unsigned int image_height)
{
    auto row_size = ((bpp*image_width)/32)*4;
    auto pixel_array_size = row_size * abs(image_height); 
    return pixel_array_size;

}

int main()
{
    Header header;
    InfoHeader infoheader;
    ColorTable colortable; 
    
   

    std::ifstream input_file("test.bmp",std::ios::binary);
    input_file.read(reinterpret_cast<char *>(&header),sizeof(header));
    input_file.read(reinterpret_cast<char *>(&infoheader),sizeof(infoheader));
    input_file.read(reinterpret_cast<char *>(&colortable),sizeof(colortable));

    auto image_size = calc_img_size(infoheader.bpp, infoheader.width, infoheader.height);
    std::cout << "image data size: " <<image_size<< std::endl;
    char * img_data = new char[image_size];
    
    input_file.read(img_data,image_size);

    return 0;
}

