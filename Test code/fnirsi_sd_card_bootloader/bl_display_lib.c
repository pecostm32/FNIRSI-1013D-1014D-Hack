//----------------------------------------------------------------------------------------------------------------------------------

//Need some screen buffer system where it is possible to build up an image without disturbing the actual screen

//So function for copying a full screen
//A function for copying a partial screen
//A function for animating a menu

//Needed functions
//display_fill_arc            //Two possible modes: fill a pie section (lines from origin to the angles) or a slice section (straight line from start angle to end angle)

//Need to think about line widths or dot size


//----------------------------------------------------------------------------------------------------------------------------------

#include "bl_display_lib.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_dimensions(uint32 width, uint32 height)
{
  //Adjust for zero being part of the display
  displaydata.width  = width - 1;
  displaydata.height = height - 1;
  displaydata.pixelsperline = width;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_font(PFONTDATA font)
{
  displaydata.font = font;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_fg_color(uint32 color)
{
  displaydata.fg_color = (color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5 | (color & 0x000000F8) >> 3;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_screen_buffer(uint16 *buffer)
{
  displaydata.screenbuffer = buffer;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_line(uint32 xstart, uint32 ystart, uint32 xend, uint32 yend)
{
  register uint16 *ptr;
  register int32  x, xs, xe, y, ys, ye, dx;
  register int32  yacc;
  register int32  ystep;
  
  //Determine the lowest x for start point
  if(xstart < xend)
  {
    //Use the coordinates as is
    xs = xstart;
    xe = xend;
    ys = ystart;
    ye = yend;
  }
  else
  {
    //Swap start and end
    xs = xend;
    xe = xstart;
    ys = yend;
    ye = ystart;
  }
  
  //Check if the line is vertical
  if(xstart == xend)
  {
    //If so use 1 for delta x to calculate the y segment length
    dx = 1;
  }
  else
  {
    //Not vertical then calculate delta x.
    dx = (xe - xs) + 1;
  }
  
  //Calculate the y segment length
  ystep = ((ye - ys) << 16) / dx;
  
  //Initialize the y accumulator for broken pixel accounting
  yacc = ys << 16;
  
  //Handle all the x positions
  for(x=xs;x<=xe;x++)
  {
    //Calculate the y end of this segment
    yacc += ystep;
    ye = yacc >> 16;

    //Check if line is going down or up    
    if(ystep >= 0)
    {
      //Going down so add to y
      for(y=ys;y<=ye;y++)
      {
        //Check on screen bounds
        if((x >= 0) && (x < displaydata.width) && (y >= 0) && (y < displaydata.height))
        {
          //Point to the pixel in the screen buffer
          ptr = displaydata.screenbuffer + ((y * displaydata.pixelsperline) + x);

          //Fill the dot
          *ptr = displaydata.fg_color;
        }
      }
    }
    else
    {
      //Going up so subtract from y
      for(y=ys;y>=ye;y--)
      {
        //Check on screen bounds
        if((x >= 0) && (x < displaydata.width) && (y >= 0) && (y < displaydata.height))
        {
          //Point to the pixel in the screen buffer
          ptr = displaydata.screenbuffer + ((y * displaydata.pixelsperline) + x);

          //Fill the dot
          *ptr = displaydata.fg_color;
        }
      }
    }
    
    //Set y start of next segment
    ys = ye;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_horz_line(uint32 ypos, uint32 xstart, uint32 xend)
{
  register uint16 *ptr;
  register uint32 x, xs, xe;
  
  //Check if the line is on the screen
  if(ypos > displaydata.height)
  {
    //Outside the y range so do nothing
    return;
  }
    
  //Determine the lowest x for start point
  if(xstart < xend)
  {
    //Use the coordinates as is
    xs = xstart;
    xe = xend;
  }
  else
  {
    //Swap start and end
    xs = xend;
    xe = xstart;
  }
  
  //Check if the end of the line is on the screen
  if(xe > displaydata.width)
  {
    //Outside so limit to the end of the screen
    xe = displaydata.width;
  }

  //Point to where the line needs to be drawn
  ptr = displaydata.screenbuffer + ((ypos * displaydata.pixelsperline) + xs);
  
  //Draw the dots
  for(x=xs;x<=xe;x++)
  {
    //Fill the dot
    *ptr++ = displaydata.fg_color;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_vert_line(uint32 xpos, uint32 ystart, uint32 yend)
{
  register uint16 *ptr;
  register uint32 y, ys, ye;
  register uint32 pixels = displaydata.pixelsperline;
  
  //Check if the line is on the screen
  if(xpos > displaydata.width)
  {
    //Outside the x range so do nothing
    return;
  }
    
  //Determine the lowest y for start point
  if(ystart < yend)
  {
    //Use the coordinates as is
    ys = ystart;
    ye = yend;
  }
  else
  {
    //Swap start and end
    ys = yend;
    ye = ystart;
  }
  
  //Check if the end of the line is on the screen
  if(ye > displaydata.height)
  {
    //Outside so limit to the end of the screen
    ye = displaydata.height;
  }

  //Point to where the line needs to be drawn
  ptr = displaydata.screenbuffer + ((ys * pixels) + xpos);
  
  //Draw the dots
  for(y=ys;y<=ye;y++)
  {
    //Fill the dot
    *ptr = displaydata.fg_color;
    
    //Point to the next dot
    ptr += pixels;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_rect(uint32 xpos, uint32 ypos, uint32 width, uint32 height)
{
  //Compensate for the last pixel
  width--;
  height--;
  
  uint32 xe = xpos + width;
  uint32 ye = ypos + height;
  
  //Just draw the needed lines
  display_draw_horz_line(ypos, xpos, xe);
  display_draw_horz_line(ye, xpos, xe);
  display_draw_vert_line(xpos, ypos, ye);
  display_draw_vert_line(xe, ypos, ye);
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(uint32 xpos, uint32 ypos, uint32 width, uint32 height)
{
  uint16 *ptr;
  uint32  y;
  uint32  x;

  //Calculate the last x and y position to compare against
  width += xpos;
  height += ypos;

  //Check on x bound
  if(width > displaydata.width)
  {
    width = displaydata.width;
  }
  
  //Check on y bound
  if(height > displaydata.height)
  {
    height = displaydata.height;
  }
  
  //Draw all the pixels
  for(y=ypos;y<height;y++)
  {
    //Point to the first pixel of this line in the screen buffer
    ptr = displaydata.screenbuffer + ((y * displaydata.pixelsperline) + xpos);

    //Draw the pixels on the line
    for(x=xpos;x<width;x++)
    {
      //Set the current screen buffer pixel with the requested color
      *ptr++ = displaydata.fg_color;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 printhexnibble(uint8 nibble)
{
  //Check if needs to be converted to A-F character
  if(nibble > 9)
  {
    //To make alpha add 55. (55 = 'A' - 10)
    nibble += 55;
  }
  else
  {
    //To make digit add '0'
    nibble += '0';
  }

  return(nibble);
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_hex(uint32 xpos, uint32 ypos, uint32 digits, int32 value)
{
  int8  b[13];
  int32 i;
  int32 shifter;
    
  //Limit to 8 digits
  if(digits > 8)
  {
    digits = 8;
  }
  
  //Set the starting shifter
  shifter = (digits * 4) - 4;
  
  //Put in the hexadecimal leader
  memcpy(b, "0x", 2);
  
  //Compensate for the leader
  digits += 2;
  
  //Put in the digits after the leader
  for(i=2;i<digits;i++)
  {
    //Add the current digit to the string
    b[i] = printhexnibble((value >> shifter) & 0x0F);
    
    //Adjust the shifter
    shifter -= 4;
  }
  
  //Terminate the string
  b[i] = 0;
  
  //Display the result
  display_text(xpos, ypos, b);
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_decimal(uint32 xpos, uint32 ypos, int32 value)
{
  char   b[13];
  uint32 u = value;
  uint32 i = 12;

  if(value == 0)
  {
    //Value is zero so just display a 0 character
    display_text(xpos, ypos, "0");
  }
  else
  {
    //Terminate the string for displaying
    b[12] = 0;

    //Check if negative value
    if(value < 0)
    {
      //Negate if so
      u = -value;
    }

    //Process the digits
    while(u)
    {
      //Set current digit to decreased index
      b[--i] = (u % 10) + '0';

      //Take of the current digit
      u /= 10;
    }

    //Check if negative value for adding the sign
    if(value < 0)
    {
      //If so put minus character in the buffer
      b[--i] = '-';
    }
    
    display_text(xpos, ypos, &b[i]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_character(uint32 xpos, uint32 ypos, int8 text)
{
  //Set the positions for drawing the text
  displaydata.xpos = xpos;
  displaydata.ypos = ypos;
  
  //Check on the type of font for the correct handling function
  if(displaydata.font->type == VARIABLE_WIDTH_FONT)
  {
    //Draw this character in the screen buffer
    draw_vw_character((uint16)text);
  }
  else
  {
    //Draw this character in the screen buffer
    draw_fw_character((uint16)text);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_text(uint32 xpos, uint32 ypos, const char *text)
{
  //Set the positions for drawing
  displaydata.xpos = xpos;
  displaydata.ypos = ypos;
  
  //Check on the type of font for the correct handling function
  if(displaydata.font->type == VARIABLE_WIDTH_FONT)
  {
    //Process all the characters
    while(*text)
    {
      //Draw this character in the screen buffer
      draw_vw_character((uint16)*text);
      
      //Skip to the next character
      text++;
    }
  }
  else if(displaydata.font->type == FIXED_WIDTH_FONT)
  {
    //Process all the characters
    while(*text)
    {
      //Draw this character in the screen buffer
      draw_fw_character((uint16)*text);
      
      //Skip to the next character
      text++;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void draw_vw_character(uint16 character)
{
  //Get the font information for this character
  PFONTDATA        font = displaydata.font;
  PFONTINFORMATION info = check_char_in_vw_font(font->fontinformation, character);
  PFONTMETRICS     metrics;
  
  uint16 *ptr;
  int32   idx;
  uint32  height;
  uint32  y;
  uint32  pixel;
  uint32  pixeldata;
  
  //Check if character is valid
  if(info)
  {
    //Get the metrics data for this character
    metrics = &info->fontmetrics[character - info->first_char];

    //Get the actual metrics for drawing the character
    height = font->height;
    
    //Add bounds limiting here for both height and pixels

    //Draw all the pixels
    for(y=0;y<height;y++)
    {
      idx = y * metrics->bytes;
      pixeldata = metrics->data[idx];

      //Point to the first pixel on this line in the screen buffer
      ptr = displaydata.screenbuffer + (((displaydata.ypos + y) * displaydata.pixelsperline) + displaydata.xpos);

      for(pixel=0;pixel<metrics->pixels;)
      {
        //Select the pixel to check
        pixeldata <<= 1;

        //Check if the pixel is set and print it if so
        if(pixeldata & 0x0100)
        {
          //Set the current screen buffer pixel with the requested color
          *ptr = displaydata.fg_color;
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

    displaydata.xpos += metrics->width;
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
//Fixed width characters can be made up by overlaying two characters

void draw_fw_character(uint16 character)
{
  //Get the font information for this character
  PFONTDATA           font = displaydata.font;
  PFONTFIXEDWIDTHINFO info = font->fontinformation;
  
  uint16 char1 = 0xFFFF;
  uint16 char2 = 0xFFFF;
  uint32 idx;
  
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
    render_fw_character(char1);
  }

  //Check if second character is valid
  if(char2 != 0xFFFF)
  {
    //Draw the second on top of the first
    render_fw_character(char2);
  }
  
  //Check if either character is valid for x position update
  if((char1 != 0xFFFF) || (char2 != 0xFFFF))
  {
    displaydata.xpos += info->width;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void render_fw_character(uint16 character)
{
  //Get the font information for this character
  PFONTDATA           font = displaydata.font;
  PFONTFIXEDWIDTHINFO info = font->fontinformation;
  
  uint8  *data;
  uint16 *ptr;
  int32   idx;
  uint32  height;
  uint32  y;
  uint32  pixel;
  uint32  pixeldata;
  
  //Get the actual metrics for drawing the character
  height = font->height;
  
  //Point to the first byte of the pixel data
  data = info->data + (character * font->height * info->bytes);

  //Add bounds limiting here for both height and pixels
  
  
  //Draw all the pixels
  for(y=0;y<height;y++)
  {
    idx = y * info->bytes;
    pixeldata = data[idx];

    //Point to the first pixel on this line in the screen buffer
    ptr = displaydata.screenbuffer + (((displaydata.ypos + y) * displaydata.pixelsperline) + displaydata.xpos);

    for(pixel=0;pixel<info->pixels;)
    {
      //Select the pixel to check
      pixeldata <<= 1;

      //Check if the pixel is set and print it if so
      if(pixeldata & 0x0100)
      {
        //Set the current screen buffer pixel with the requested color
        *ptr = displaydata.fg_color;
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
