//----------------------------------------------------------------------------------------------------------------------------------

//Need some screen buffer system where it is possible to build up an image without disturbing the actual screen

//So function for copying a full screen
//A function for copying a partial screen
//A function for animating a menu

//Needed functions
//display_fill_arc            //Two possible modes: fill a pie section (lines from origin to the angles) or a slice section (straight line from start angle to end angle)

//Need to think about line widths or dot size


//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "display_lib.h"
#include "sin_cos_math.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_position(uint16 xpos, uint16 ypos)
{
  displaydata.xpos = xpos;
  displaydata.ypos = ypos;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_dimensions(uint16 width, uint16 height)
{
  //Adjust for zero being part of the display
  displaydata.width  = width - 1;
  displaydata.height = height - 1;
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

void display_set_bg_color(uint32 color)
{
  displaydata.bg_color = (color & 0x00F80000) >> 8 | (color & 0x0000FC00) >> 5 | (color & 0x000000F8) >> 3;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_screen_buffer(uint16 *screen)
{
  displaydata.screenbuffer = screen;
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_line(uint16 xstart, uint16 ystart, uint16 xend, uint16 yend )
{
  uint16 *ptr;
  uint16 x, xs, xe, y, ys, ye, dx;
  uint32 yacc;
  int32  ystep;
  
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
          ptr = displaydata.screenbuffer + ((y * 800) + x);

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
          ptr = displaydata.screenbuffer + ((y * 800) + x);

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

void display_draw_horz_line(uint16 ypos, uint16 xstart, uint16 xend)
{
  uint16 *ptr;
  uint16 x, xs, xe;
  
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
  ptr = displaydata.screenbuffer + ((ypos * 800) + xs);
  
  //Draw the dots
  for(x=xs;x<=xe;x++)
  {
    //Fill the dot
    *ptr++ = displaydata.fg_color;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_vert_line(uint16 xpos, uint16 ystart, uint16 yend)
{
  uint16 *ptr;
  uint16 y, ys, ye;
  
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
  ptr = displaydata.screenbuffer + ((ys * 800) + xpos);
  
  //Draw the dots
  for(y=ys;y<=ye;y++)
  {
    //Fill the dot
    *ptr = displaydata.fg_color;
    
    //Point to the next dot
    ptr += 800;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height)
{
  uint16 xe = xpos + width;
  uint16 ye = ypos + height;
  
  //Just draw the needed lines
  display_draw_horz_line(ypos, xpos, xe);
  display_draw_horz_line(ye, xpos, xe);
  display_draw_vert_line(xpos, ypos, ye);
  display_draw_vert_line(xe, ypos, ye);
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_rounded_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius)
{
  uint16 xs = xpos + radius;
  uint16 ys = ypos + radius;
  uint16 xe = xpos + width - radius;
  uint16 ye = ypos + height - radius;
  
  //Just draw the needed lines
  display_draw_horz_line(ypos, xs, xe);
  display_draw_horz_line(ypos + height, xs, xe);
  display_draw_vert_line(xpos, ys, ye);
  display_draw_vert_line(xpos + width, ys, ye);
  
  //And the needed arcs
  display_draw_arc(xs, ys, radius, 1800, 2700, 0);
  display_draw_arc(xe, ys, radius, 2700,    0, 0);
  display_draw_arc(xe, ye, radius,    0,  900, 0);
  display_draw_arc(xs, ye, radius,  900, 1800, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------

const uint16 angles[4][2] = { { 0, 900 }, { 900, 1800 }, { 1800, 2700 }, { 2700, 3600 } };

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_arc(uint16 xpos, uint16 ypos, uint16 radius, uint16 startangle, uint16 endangle, uint16 direction)
{
  uint8   startquadrant = (startangle / 900) % 4;
  uint8   endquadrant   = (endangle / 900) % 4;
  uint8   quadrants[4]  = { 0, 0, 0, 0 };
  uint8   quadrant = startquadrant;
  uint16 *ptr;
  int16   x, y;
  uint16  sa;
  uint16  ea;
  uint16  a, step;

  //Determine the angles step fit for the given radius  
  if(radius > 450)
    step = 1;
  else
    step = 450 / radius;
  
  //Flag the quadrants that need to be drawn
  while(quadrant != endquadrant)
  {
    quadrants[quadrant] = 1;
    
    if(direction == DISPLAY_DRAW_CLOCK_WISE)
      quadrant = (quadrant + 1) % 4;
    else
      quadrant = (quadrant - 1) % 4;
  }
  
  //Flag the end quadrant as well
  quadrants[endquadrant] = 1;
  
  //Draw the pixels for each quadrant
  for(quadrant=0;quadrant<4;quadrant++)
  {
    //Check if anything needs to be drawn in this quadrant
    if(quadrants[quadrant])
    {
      //Determine the angles to use based on the quadrant
      if(quadrant == startquadrant)
      {
        //Check on drawing direction
        if(direction == DISPLAY_DRAW_CLOCK_WISE)
        {
          //For clock wise start is from the given angle to the end of the quadrant
          sa = startangle % 3600;
          ea = angles[quadrant][1];
        }
        else
        {
          //For counter clock wise start is from the start of the quadrant to the given start angle
          sa = angles[quadrant][0];
          ea = startangle % 3600;
        }
      }
      else if(quadrant == endquadrant)
      {
        //Check on drawing direction
        if(direction == DISPLAY_DRAW_CLOCK_WISE)
        {
          //For clock wise start is from the starting angle of the quadrant to the given end angle
          sa = angles[quadrant][0];
          ea = endangle % 3600;
        }
        else
        {
          //For counter clock wise start is from the given end angle to the end of the quadrant
          sa = endangle % 3600;
          ea = angles[quadrant][1];
        }
      }
      else
      {
        //For fully drawn quadrant it is always from start to end of the quadrant
        sa = angles[quadrant][0];      
        ea = angles[quadrant][1];
      }

      //Draw the pixels
      for(a=sa;a<ea;)
      {
        //Get the coordinates for the current angle
        x = getxpos(a, xpos, radius);
        y = getypos(a, ypos, radius);

        //Check on screen bounds
        if((x >= 0) && (x <= displaydata.width) && (y >= 0) && (y <= displaydata.height))
        {
          //Point to the pixel in the screen buffer
          ptr = displaydata.screenbuffer + ((y * 800) + x);

          //Fill the dot
          *ptr = displaydata.fg_color;
        }

        //Step to the next angle
        a += step;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height)
{
  uint16 *ptr;
  uint16  y;
  uint16  x;

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
    ptr = displaydata.screenbuffer + ((y * 800) + xpos);

    //Draw the pixels on the line
    for(x=xpos;x<width;x++)
    {
      //Set the current screen buffer pixel with the requested color
      *ptr++ = displaydata.fg_color;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rounded_rect(uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius)
{
  uint16 *ptr1, *ptr2;
  uint16  x, xc, xs, xe, xt, y, yc, ys, ye;
  uint16  a, step, r;

  //Calculate the max radius for the given width and height
  if(width < height)
  {
    r = width / 2;
  }
  else
  {
    r = height / 2;
  }
  
  //Check if the given radius is not to big
  if(radius > r)
  {
    //If it is use the max
    radius = r;
  }

  //Determine the angles step fit for the given radius  
  if(radius > 450)
    step = 1;
  else if(radius > 0)
  {
    step = 450 / radius;
  }

  //Only draw the arced corners when there is a radius
  if(radius)
  {
    //Calculate the position of the arc center
    xc = xpos + radius;
    yc = ypos + radius;
    
    //Calculate the biggest x and y end
    xt = xpos + width;
    ye = ypos + height;
    
    //Fill the horizontal lines for the corner sections by working through the angles
    for(a=2700;a>=1800;a-=step)
    {
      //Get the coordinates for the current angle
      xs = getxpos(a, xc, radius);
      y  = getypos(a, yc, radius);
      
      //Calculate the bottom line to draw
      ys = ye - (y - ypos);
      
      //Calculate the x end for this line
      xe = xt - (xs - xpos);
      
      //Check the x bound
      if(xe > displaydata.width)
      {
        xe = displaydata.width;
      }
      
      //Point to the start of the top and the bottom section line
      ptr1 = displaydata.screenbuffer + ((y * 800) + xs);
      ptr2 = displaydata.screenbuffer + ((ys * 800) + xs);
      
      //Draw the pixels on the lines
      for(x=xs;x<xe;x++)
      {
        //Set the top line current screen buffer pixel with the requested color
        *ptr1++ = displaydata.fg_color;
        
        //Check on y bound
        if(ys <= displaydata.height)
        {
          //Set the bottom line current screen buffer pixel with the requested color
          *ptr2++ = displaydata.fg_color;
        }
      }
      
    }
  }
  
  //Make width the xend
  width += xpos;
  
  //Calculate the y positions for the middle section
  ys = ypos + radius;
  ye = ypos + height - radius;
  
  //Check on x bound
  if(width > displaydata.width)
  {
    width = displaydata.width;
  }
  
  //Check on y bound
  if(ye > displaydata.height)
  {
    ye = displaydata.height;
  }
 
  //Draw all the pixels for the middle section
  for(y=ys;y<=ye;y++)
  {
    //Point to the first pixel of this line in the screen buffer
    ptr1 = displaydata.screenbuffer + ((y * 800) + xpos);

    //Draw the pixels on the line
    for(x=xpos;x<width;x++)
    {
      //Set the current screen buffer pixel with the requested color
      *ptr1++ = displaydata.fg_color;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_text(uint16 xpos, uint16 ypos, int8 *text)
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
    
    //Add bounds limiting here for both height and pixels

    //Draw all the pixels
    for(y=0;y<height;y++)
    {
      idx = y * metrics->bytes;
      pixeldata = metrics->data[idx];

      //Point to the first pixel on this line in the screen buffer
      ptr = displaydata.screenbuffer + (((displaydata.ypos + y) * 800) + displaydata.xpos);

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

void draw_fw_character(uint16 character)
{
  //Get the font information for this character
  PFONTDATA           font = displaydata.font;
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
  int16   idx;
  uint8   height;
  uint8   y;
  uint8   pixel;
  uint16  pixeldata;
  
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
    ptr = displaydata.screenbuffer + (((displaydata.ypos + y) * 800) + displaydata.xpos);

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
