//----------------------------------------------------------------------------------------------------------------------------------

//Need some screen buffer system where it is possible to build up an image without disturbing the actual screen

//So function for copying a full screen
//A function for copying a partial screen
//A function for animating a menu


//A function for filling a rect
//xpos, ypos, width, height, color, destination

//A function for drawing a line


//Function for displaying text
//*text, xpos, ypos, font, color, destination

//Within the font info needs to be set about the type and use different handling if needed

//Needed functions
//set_fg_color
//set_bg_color
//set_font

//fill_rect


//Need a display struct to hold information
//fg_color
//bg_color
//font
//screen_buffer



//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "display_lib.h"

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_position(PDISPLAYDATA display, uint16 xpos, uint16 ypos)
{
  display->xpos = xpos;
  display->ypos = ypos;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_font(PDISPLAYDATA display, PFONTDATA font)
{
  display->font = font;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_fg_color(PDISPLAYDATA display, uint32 color)
{
  display->fg_color = (color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5 | (color & 0x000000F8) >> 3;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_bg_color(PDISPLAYDATA display, uint32 color)
{
  display->bg_color = (color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5 | (color & 0x000000F8) >> 3;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_screen_buffer(PDISPLAYDATA display, uint16 *screen)
{
  display->screenbuffer = screen;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height)
{
  uint16 *ptr;
  uint16  y;
  uint16  x;

  //Calculate the last y position to compare against
  height += ypos;
  
  //Draw all the pixels
  for(y=ypos;y<height;y++)
  {
    //Point to the first pixel of this line in the screen buffer
    ptr = display->screenbuffer + ((y * 800) + xpos);

    //Draw the pixels on the line
    for(x=0;x<width;x++)
    {
      //Set the current screen buffer pixel with the requested color
      *ptr++ = display->fg_color;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_text(PDISPLAYDATA display, uint16 xpos, uint16 ypos, int8 *text)
{
  //Set the positions for drawing
  display->xpos = xpos;
  display->ypos = ypos;
  
  //Check on the type of font for the correct handling function
  if(display->font->type == VARIABLE_WIDTH_FONT)
  {
    //Process all the characters
    while(*text)
    {
      //Draw this character in the screen buffer
      draw_vw_character(display, (uint16)*text);
      
      //Skip to the next character
      text++;
    }
  }
  else if(display->font->type == FIXED_WIDTH_FONT)
  {
    //Process all the characters
    while(*text)
    {
      //Draw this character in the screen buffer
      draw_fw_character(display, (uint16)*text);
      
      //Skip to the next character
      text++;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void draw_vw_character(PDISPLAYDATA display, uint16 character)
{
  //Get the font information for this character
  PFONTDATA        font = display->font;
  PFONTINFORMATION info = check_char_in_vw_font(font->fontinformation, character);
  PFONTMETRICS     metrics;
  
  uint16 *ptr;
  int16   idx;
  uint8   height;
  uint8   y;
  uint8   pixel;
  uint16  pixeldata;
  
  //Check if character is valid
  if(info)
  {
    //Get the metrics data for this character
    metrics = &info->fontmetrics[character - info->first_char];

    //Get the actual metrics for drawing the character
    height = font->height;

    //Draw all the pixels
    for(y=0;y<height;y++)
    {
      idx = y * metrics->bytes;
      pixeldata = metrics->data[idx];

      //Point to the first pixel on this line in the screen buffer
      ptr = display->screenbuffer + (((display->ypos + y) * 800) + display->xpos);

      for(pixel=0;pixel<metrics->pixels;)
      {
        //Select the pixel to check
        pixeldata <<= 1;

        //Check if the pixel is set and print it if so
        if(pixeldata & 0x0100)
        {
          //Set the current screen buffer pixel with the requested color
          *ptr = display->fg_color;
        }

        //Select next pixel count and point to next screen buffer pixel
        pixel++;
        ptr++;

        //Check if pixel on multiple of 8 for next byte select
        if((pixel & 0x07) == 0)
        {
          //Point to the next byte
          idx++;

          //Get the actual data for it
          pixeldata = metrics->data[idx];
        }
      }
    }

    display->xpos += metrics->width;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

PFONTINFORMATION check_char_in_vw_font(PFONTINFORMATION info, uint16 character)
{
  //Check if the character is in this information range 
  if((character >= info->first_char) && (character <= info->last_char))
  {
    //If so signal character is found
    return(info);
  }
  
  //Else check if there are no more font information ranges
  if(info->next_info == 0)
  {
    //Signal character invalid
    return(0);
  }
  
  //Else go and check the next information set
  return(check_char_in_vw_font(info->next_info, character));
}

//----------------------------------------------------------------------------------------------------------------------------------

void draw_fw_character(PDISPLAYDATA display, uint16 character)
{
  //Get the font information for this character
  PFONTDATA           font = display->font;
  PFONTFIXEDWIDTHINFO info = font->fontinformation;
  
  uint16 char1 = 0xFFFF;
  uint16 char2 = 0xFFFF;
  uint16 idx;
  
  //Check if the character is in the main information set
  if((character >= info->first_char) && (character <= info->last_char))
  {
    //If so signal character is found
    char1 = character - info->first_char;
  }
  else
  {
    //Get the extended information set
    PFONTEXTENDEDINFO extended = info->extended_info;
    
    //Check if the character is in the extended information set
    if((character >= extended->first_char) && (character <= extended->last_char))
    {
      //Get the translation table if needed
      PFONTTANSLATIONTABLE trans = extended->data;
      
      //Get the index into the translation table
      idx = character - extended->first_char;
      
      //Get the two characters from the translation table
      char1 = trans[idx].char1;
      char2 = trans[idx].char2;
    }
  }
  
  //Check if first character is valid
  if(char1 != 0xFFFF)
  {
    //Draw it if so
    render_fw_character(display, char1);
  }

  //Check if second character is valid
  if(char2 != 0xFFFF)
  {
    //Draw the second on top of the first
    render_fw_character(display, char2);
  }
  
  //Check if either character is valid for x position update
  if((char1 != 0xFFFF) || (char2 != 0xFFFF))
  {
    display->xpos += info->width;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void render_fw_character(PDISPLAYDATA display, uint16 character)
{
  //Get the font information for this character
  PFONTDATA           font = display->font;
  PFONTFIXEDWIDTHINFO info = font->fontinformation;
  
  uint8  *data;
  uint16 *ptr;
  int16   idx;
  uint8   height;
  uint8   y;
  uint8   pixel;
  uint16  pixeldata;
  
  //Get the actual metrics for drawing the character
  height = font->height;
  
  //Point to the first byte of the pixel data
  data = info->data + (character * font->height * info->bytes);

  //Draw all the pixels
  for(y=0;y<height;y++)
  {
    idx = y * info->bytes;
    pixeldata = data[idx];

    //Point to the first pixel on this line in the screen buffer
    ptr = display->screenbuffer + (((display->ypos + y) * 800) + display->xpos);

    for(pixel=0;pixel<info->pixels;)
    {
      //Select the pixel to check
      pixeldata <<= 1;

      //Check if the pixel is set and print it if so
      if(pixeldata & 0x0100)
      {
        //Set the current screen buffer pixel with the requested color
        *ptr = display->fg_color;
      }

      //Select next pixel count and point to next screen buffer pixel
      pixel++;
      ptr++;

      //Check if pixel on multiple of 8 for next byte select
      if((pixel & 0x07) == 0)
      {
        //Point to the next byte
        idx++;

        //Get the actual data for it
        pixeldata = data[idx];
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
