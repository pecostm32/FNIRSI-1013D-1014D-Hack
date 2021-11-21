#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"
#include "../../F1C100s/fnirsi_1013d_scope/sin_cos_math.h"
#include "../../F1C100s/fnirsi_1013d_scope/types.h"
#include "../../F1C100s/fnirsi_1013d_scope/font_structs.h"
#include "../../F1C100s/fnirsi_1013d_scope/display_lib.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define scope_screen    1

#if scope_screen
#define DESIGN_WIDTH      2120
#define DESIGN_HEIGHT      600
#else
#define DESIGN_WIDTH      1520
#define DESIGN_HEIGHT     1260
#endif

//----------------------------------------------------------------------------------------------------------------------------------

void open_signal_file(FILE **fp, u_int32_t index);

void load_display_signal_buffer(FILE *fp, u_int32_t index, u_int32_t file_index);

void make_image(tagXlibContext *xc, tagXlibDimensions *xd, XImage *scopedisplay);

//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;
extern FONTDATA font_3;
extern FONTDATA font_5;
extern FONTDATA font_7;

extern const uint16 system_settings_icon[];
extern const uint16 picture_view_icon[];
extern const uint16 waveform_view_icon[];
extern const uint16 usb_icon[];


extern const uint8 letter_c_icon[];
extern const uint8 letter_e_icon[];
extern const uint8 letter_o_icon[];
extern const uint8 letter_p_icon[];
extern const uint8 letter_s_icon[];

//DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

#if scope_screen
unsigned short maindisplaybuffer[2100 * 580];
unsigned short displaybuffer[2100 * 580];
unsigned short displaybuffer1[2100 * 580];

unsigned short gradientbuffer[580];
#else
unsigned short maindisplaybuffer[1500 * 1240];
unsigned short displaybuffer[1500 * 1240];
unsigned short displaybuffer1[1500 * 1240];
#endif

//----------------------------------------------------------------------------------------------------------------------------------

typedef unsigned long long   uint64;
typedef unsigned int         uint32;
typedef unsigned short       uint16;
typedef unsigned char        uint8;

typedef int         int32;

typedef struct tagADC2CalibrationData   ADC2CALIBRATIONDATA,  *PADC2CALIBRATIONDATA;

struct tagADC2CalibrationData
{
  uint16 flag;
  uint16 compensation;
};

uint16 samples1[3000];
uint16 samples2[3000];
uint16 samples3[3000];
uint16 samples4[3000];
uint16 samples5[3000];
uint16 samples6[3000];
uint16 samples7[3000];
uint16 samples8[3000];

ADC2CALIBRATIONDATA calib1;

//For 10.22 ==> 1 ==> 4194304
uint32 ch1k1 = 419431;
uint32 ch1k2 = 3774873;
uint32 filterch1 = 0;

//----------------------------------------------------------------------------------------------------------------------------------
//multiple traces

void scope_up_sample_x_10_mt(uint32 count)
{
  register uint32  cnt, idx;
  register uint16 *sptr;
  register uint16 *sptr2;
  register uint16 *dptr;
  register int32   sample1, sample2;
  register int32   delta;
  
  //Only do one tenth of the samples
  cnt = count / 10;
  
  //For the source point to the last sample to use
  sptr = &samples1[cnt];
  
  //For the destination point to the last result sample
  dptr = &samples2[count];
  
  //Get the first sample to use
  sample1 = *sptr--;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample
    sample2 = *sptr--;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 10;
    
    for(idx=0;idx<9;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = sample1 >> 22;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }

  //For convolution a const buffer with points is needed to do the calculations with
  //The number of samples on the output increases with the number of points minus 0
  //Every sample needs to be multiplied with the points and added to form a new sample
  
  //output += (input * point);
  
#if 0 
  //Simple filter
  //filter = (k1 * input) + (k2 * filter) >> 22
  
  //Filter the data
  cnt = count;
  sptr = samples2;
  dptr = samples3;
  
  while(cnt)
  {
    filterch1 = ((ch1k1 * *sptr) + (ch1k2 * filterch1)) >> 22;
    *dptr++ = filterch1;
    
    sptr++;
    
    cnt--;
  }
#else
  //These newly interpolated samples need to be averaged with the first set, which might be possible to do in the single run directly back into the original buffer
  
  //Create a second interpolated set of data based on the interpolated samples
  //Only do one tenth of the samples minus one since the data is shifted
  cnt = (count / 10) - 1;

  //For the source point to the last sample to use
  sptr = &samples2[count - 5];
  
  //For the destination point to the last result sample
  //Also on shifted sample to end where needed
  dptr = &samples3[count - 5];
  
  //Get the first sample to use and skip ten samples
  sample1 = *sptr;
  sptr -= 10;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr-- = sample1;
    
    //Get the second sample and skip ten samples
    sample2 = *sptr;
    sptr -= 10;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 10;
    
    for(idx=0;idx<9;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = (sample1 >> 22);
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }
  
  //Store the last sample
  *dptr = sample1;

  //Average these two sets
  cnt = count;
  sptr  = samples2;
  sptr2 = samples3;

  dptr = samples4;
  
  while(cnt)
  {
    *dptr++ = (*sptr + *sptr2) / 2;
    
    sptr++;
    sptr2++;
    
    cnt--;
  }

  //The last step is a 5 time up sampling of the processed data and averaging that with the processed data
  //Only do one fifth of the samples
  cnt = (count / 5) - 1;
  
  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &samples4[count - 8];
  
  //For the destination point to the last result sample
  dptr = &samples5[count];
  
  //Get the first sample to use and skip 5 samples
  sample1 = *sptr;
  sptr -= 5;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample and skip 5 samples
    sample2 = *sptr;
    sptr -= 5;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 5;
    
    for(idx=0;idx<4;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = (sample1 >> 22);
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }
  
  //Store the last sample
  *dptr = sample1;
  
  //Average these two sets
  cnt = count;
  sptr  = samples4;
  sptr2 = samples5;

  dptr = samples6;
  
  while(cnt)
  {
    *dptr++ = (*sptr + *sptr2) / 2;
    
    sptr++;
    sptr2++;
    
    cnt--;
  }
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_up_sample_x_10(uint16 * buffer, uint32 count)
{
  register uint32  cnt, idx;
  register uint16 *sptr;
  register uint16 *dptr;
  register int32   sample1, sample2;
  register int32   delta;
  
  //Only do one tenth of the samples
  cnt = count / 10;
  
  //For the source point to the last sample to use
  sptr = &buffer[cnt];
  
  //For the destination point to the last result sample
  dptr = &buffer[count];
  
  //Get the first sample to use
  sample1 = *sptr--;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample
    sample2 = *sptr--;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 10;
    
    for(idx=0;idx<9;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = sample1 >> 22;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //Create a second interpolated set of data based on the initially interpolated samples and average the two sets
  //Only take one tenth of the samples, minus one since the data is shifted, as input
  cnt = (count / 10) - 1;

  //For the source point to the last sample to use
  sptr = &buffer[count - 5];
  
  //For the destination point to the last result sample
  dptr = &buffer[count - 5];
  
  //Get the first sample to use and skip ten samples
  sample1 = *sptr;
  sptr -= 10;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr = (*dptr + sample1) / 2;
    
    //Point to the previous sample
    dptr--;
    
    //Get the second sample and skip ten samples
    sample2 = *sptr;
    sptr -= 10;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 10;
    
    for(idx=0;idx<9;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Average and store the decimal part of it
      *dptr = (*dptr + (sample1 >> 22)) / 2;
      
      //Point to the previous sample
      dptr--;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //Create a third interpolated set of data based on the previous interpolated and averaged samples and also average these two sets
  //Only take one fifth of the samples, minus one since the data is shifted, as input
  cnt = (count / 5) - 1;

  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &buffer[count - 8];
  
  //For the destination point to the last result sample
  dptr = &buffer[count];
  
  //Get the first sample to use and skip five samples
  sample1 = *sptr;
  sptr -= 5;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr = (*dptr + sample1) / 2;
    
    //Point to the previous sample
    dptr--;
    
    //Get the second sample and skip ten samples
    sample2 = *sptr;
    sptr -= 5;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 5;
    
    for(idx=0;idx<4;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Average and store the decimal part of it
      *dptr = (*dptr + (sample1 >> 22)) / 2;
      
      //Point to the previous sample
      dptr--;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//multiple traces

void scope_up_sample_x_25_mt(uint32 count)
{
  register uint32  cnt, idx;
  register uint16 *sptr;
  register uint16 *sptr2;
  register uint16 *dptr;
  register int32   sample1, sample2;
  register int32   delta;
  
  //Only do one twenty fifth of the samples
  cnt = count / 25;
  
  //For the source point to the last sample to use
  sptr = &samples1[cnt];
  
  //For the destination point to the last result sample
  dptr = &samples2[count];
  
  //Get the first sample to use
  sample1 = *sptr--;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample
    sample2 = *sptr--;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 25;
    
    for(idx=0;idx<24;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = sample1 >> 22;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //Store the last sample
  *dptr = sample1;

  //These newly interpolated samples need to be averaged with the first set, which might be possible to do in the single run directly back into the original buffer
  
  //Create a second interpolated set of data based on the interpolated samples
  //Only do one twenty fifth of the samples minus one since the data is shifted
  cnt = (count / 25) - 1;

  //For the source point to the last sample to use
  sptr = &samples2[count - 13];
  
  //For the destination point to the last result sample
  //Also on shifted sample to end where needed
  dptr = &samples3[count - 13];
  
  //Get the first sample to use and skip twenty five samples
  sample1 = *sptr;
  sptr -= 25;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr-- = sample1;
    
    //Get the second sample and skip twenty five samples
    sample2 = *sptr;
    sptr -= 25;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 25;
    
    for(idx=0;idx<24;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = (sample1 >> 22);
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }
  
  //Store the last sample
  *dptr = sample1;

  //Average these two sets
  cnt = count;
  sptr  = samples2;
  sptr2 = samples3;

  dptr = samples4;
  
  while(cnt)
  {
    *dptr++ = (*sptr + *sptr2) / 2;
    
    sptr++;
    sptr2++;
    
    cnt--;
  }
  
  //The next step is a 12 step interpolating of the processed data and averaging that with the processed data
  //Only do one twelfth of the samples
  cnt = (count / 12);
  
  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &samples4[count];
  
  //For the destination point to the last result sample
  dptr = &samples5[count];
  
  //Get the first sample to use and skip twelve samples
  sample1 = *sptr;
  sptr -= 12;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample and skip twelve samples
    sample2 = *sptr;
    sptr -= 12;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 12;
    
    for(idx=0;idx<11;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = (sample1 >> 22);
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }
  
  //Store the last sample
  *dptr = sample1;
  
  //Average these two sets
  cnt = count;
  sptr  = samples4;
  sptr2 = samples5;

  dptr = samples6;
  
  while(cnt)
  {
    *dptr++ = (*sptr + *sptr2) / 2;
    
    sptr++;
    sptr2++;
    
    cnt--;
  }
  
  //The next step is a 6 step interpolating of the processed data and averaging that with the processed data
  //Only do one sixth of the samples
  cnt = (count / 6);
  
  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &samples6[count];
  
  //For the destination point to the last result sample
  dptr = &samples7[count];
  
  //Get the first sample to use and skip 6 samples
  sample1 = *sptr;
  sptr -= 6;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample and skip 6 samples
    sample2 = *sptr;
    sptr -= 6;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 6;
    
    for(idx=0;idx<5;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = (sample1 >> 22);
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
    
    //In here for debugging
    if(cnt == 1)
    {
      sample2 = 20;
    }
  }
  
  //Store the last sample
  *dptr = sample1;
  
  //Average these two sets
  cnt = count;
  sptr  = samples6;
  sptr2 = samples7;

  dptr = samples8;
  
  while(cnt)
  {
    *dptr++ = (*sptr + *sptr2) / 2;
    
    sptr++;
    sptr2++;
    
    cnt--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_up_sample_x_25(uint16 *buffer, uint32 count)
{
  register uint32  cnt, idx;
  register uint16 *sptr;
  register uint16 *dptr;
  register int32   sample1, sample2;
  register int32   delta;
  
  //Only do one twenty fifth of the samples
  cnt = count / 25;
  
  //For the source point to the last sample to use
  sptr = &buffer[cnt];
  
  //For the destination point to the last result sample
  dptr = &buffer[count];
  
  //Get the first sample to use
  sample1 = *sptr--;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample
    sample2 = *sptr--;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 25;
    
    for(idx=0;idx<24;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the decimal part of it
      *dptr-- = sample1 >> 22;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //Create a second interpolated set of data based on the interpolated samples
  //Only do one twenty fifth of the samples minus one since the data is shifted
  cnt = (count / 25) - 1;

  //For the source point to the last sample to use
  sptr = &buffer[count - 13];
  
  //For the destination point to the last result sample
  //Also on shifted sample to end where needed
  dptr = &buffer[count - 13];
  
  //Get the first sample to use and skip twenty five samples
  sample1 = *sptr;
  sptr -= 25;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr = (*dptr + sample1) / 2;
      
    //Point to the previous sample
    dptr--;
    
    //Get the second sample and skip twenty five samples
    sample2 = *sptr;
    sptr -= 25;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 25;
    
    for(idx=0;idx<24;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the averaged decimal part of it
      *dptr = (*dptr + (sample1 >> 22)) / 2;
      
      //Point to the previous sample
      dptr--;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //The next step is a 12 step interpolating of the processed data and averaging that with the processed data
  //Only do one twelfth of the samples
  cnt = (count / 12);
  
  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &buffer[count];
  
  //For the destination point to the last result sample
  dptr = &buffer[count];
  
  //Get the first sample to use and skip twelve samples
  sample1 = *sptr;
  sptr -= 12;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr = (*dptr + sample1) / 2;
      
    //Point to the previous sample
    dptr--;
    
    //Get the second sample and skip twelve samples
    sample2 = *sptr;
    sptr -= 12;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 12;
    
    for(idx=0;idx<11;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the averaged decimal part of it
      *dptr = (*dptr + (sample1 >> 22)) / 2;
      
      //Point to the previous sample
      dptr--;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
  
  //The next step is a 6 step interpolating of the processed data and averaging that with the processed data
  //Only do one sixth of the samples
  cnt = (count / 6);
  
  //For the source point to the last sample to use
  //Takes the second sample as last input
  sptr = &buffer[count];
  
  //For the destination point to the last result sample
  dptr = &buffer[count];
  
  //Get the first sample to use and skip 6 samples
  sample1 = *sptr;
  sptr -= 6;
  
  //Process all the needed samples
  while(cnt)
  {
    //Average and store the first sample
    *dptr = (*dptr + sample1) / 2;
      
    //Point to the previous sample
    dptr--;
    
    //Get the second sample and skip 6 samples
    sample2 = *sptr;
    sptr -= 6;
    
    //Fill in the in between samples
    //The original code uses a different approach
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - (sample2 << 22)) / 6;
    
    for(idx=0;idx<5;idx++)
    {
      //Calculate the next sample with fixed point calculation
      //Since the direction is from last sample to first sample the step needs to be taken off
      sample1 -= delta;
      
      //Store the averaged decimal part of it
      *dptr = (*dptr + (sample1 >> 22)) / 2;
      
      //Point to the previous sample
      dptr--;
    }
    
    //Save the second sample as the first sample
    sample1 = sample2;
    
    //One set of samples done
    cnt--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_up_sample_x_2_5(uint32 count)
{
  register uint32  cnt;
  register uint16 *sptr;
  register uint16 *dptr;
  register uint32  sample1, sample2, sample3;
  register int32   delta;
  
  //Only use two fifths of the samples
  cnt = (count * 2) / 5;
  
  //For the source point to the last sample to use
  sptr = &samples1[cnt];
  
  //For the destination point to the last result sample
  dptr = &samples2[count];
  
  //Get the first sample to use
  sample1 = *sptr--;
  
  //Since the loop processes two samples per loop do half the count
  cnt /= 2;
  
  //Process all the needed samples
  while(cnt)
  {
    //Store the first sample
    *dptr-- = sample1;
    
    //Get the second sample
    sample2 = *sptr--;
    
    //Store the average of the two samples
    *dptr-- = (sample1 + sample2) / 2;
    
    //Store the second sample as third sample
    *dptr-- = sample2;
    
    //Get the third sample
    sample3 = *sptr--;
    
    //Fill in the in between samples
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample2 <<= 22;
    
    //Calculate a delta step between the samples
    delta = (sample2 - (sample3 << 22)) / 3;

    //Calculate the next sample with fixed point calculation
    //Since the direction is from last sample to first sample the step needs to be taken off
    sample2 -= delta;

    //Store the decimal part of it
    *dptr-- = sample2 >> 22;
    
    //Repeat this
    sample2 -= delta;

    //Store the decimal part of it
    *dptr-- = sample2 >> 22;

    //Save the third sample as the first sample
    sample1 = sample3;
    
    //One set of samples done
    cnt--;
    
    if(cnt == 1)
      sample2 = 100;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_channel_trace(uint16 *buffer, uint16 xpos, uint16 yoffset, uint16 count, uint32 color)
{
  register uint32 index = 0;
  register uint32 sample1, sample2;

  display_set_fg_color(color);
  
  sample1 = buffer[index++];
  
  while(index < count)
  {
    sample2 = buffer[index++];

    display_draw_line(xpos, sample1 + yoffset, xpos + 1, sample2 + yoffset);
    
    xpos++;
    
    sample1 = sample2;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------


int main(int argc,char **argv)
{
  //Basic setup for the xlib system  
	Display *display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	Window win = XCreateSimpleWindow(display, root, 0, 0, DESIGN_WIDTH + BORDER_SIZE_2, DESIGN_HEIGHT + BORDER_SIZE_2, 2, BlackPixel(display, screen_num), WhitePixel(display, screen_num));
  
	XMapWindow(display, win);
  
  //For mouse handling only button press and release are needed in combination with motion which is used for controlling the knobs
	XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask );
  
	GC gc = XCreateGC(display, win, 0, NULL);
  
  unsigned int width;	           //width and height for the new window.
  unsigned int height;
  
  unsigned int x,y;
  
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  Atom WM_PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", False);
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);
  
	XEvent event;

  double fsize;
  
  int rflag = 1;

  tagXlibContext xc;

  int numsizes;  
  XRRScreenSize *scrsize;
  
  //Get the size of the primary monitor
  scrsize = XRRSizes(display, screen_num, &numsizes);
  
  //For calculations take of a border of 5 pixels for each side
  width  = (scrsize->width - BORDER_SIZE_2) * 0.95;
  height = scrsize->height - BORDER_SIZE_2;
   
  //Determine the scaler based on the width
  xc.scaler = (float)width / (float)DESIGN_WIDTH;

  //See if it scaled fits for the height. If not determine the scaler based on the height
  if((DESIGN_HEIGHT * xc.scaler) > height)
    xc.scaler = (float)height / (float)DESIGN_HEIGHT;
  
  //Check if screen is larger than the desired size
  if(xc.scaler > 1.0)
  {
    //If so keep the scale on 1
    xc.scaler = 1.0;
  }

  //Calculate the new width and height
  width = (DESIGN_WIDTH * xc.scaler) + BORDER_SIZE_2;
  height = (DESIGN_HEIGHT * xc.scaler) + BORDER_SIZE_2;
  
  //Calculate a nice position on the screen
  x = 100;
  y = 50;
  
  //Set the window to the new position and dimensions
  XMoveResizeWindow(display, win, x, y, width, height);
  
  //Setup the data for the drawing functions
  xc.screen_num = screen_num;
  xc.root = root;
  xc.win = win;
  xc.display = display;
  xc.gc = gc;
  
  xc.visual = DefaultVisual(display, screen_num);
  xc.cmap  = DefaultColormap(display, screen_num);

  //Image for the scope display
  x = BORDER_SIZE + (10 * xc.scaler);
  y = BORDER_SIZE + (10 * xc.scaler);
  
#if scope_screen
  width  = 2100 * xc.scaler;
  height = 580 * xc.scaler;
#else  
  width  = 1500 * xc.scaler;
  height = 1240 * xc.scaler;
#endif
  
  tagXlibDimensions xd;
  
  xd.x = x;
  xd.y = y;
  xd.width = width;
  xd.height = height;
  
  //Setup the image based on a capture of the screen
  XImage *scopedisplay = XGetImage(display, win, x, y, width, height, 0, ZPixmap);
  
  //--------------------------------------------------------------------------------------------------------------------------------
  //Test section
  
#if 0
  FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/fnirsi_25ns_samples_5_interleaved_6048_per_buffer.bin", "rb");

  //Get the bitmap data
  fread(&samples1, 2, 3000, fi);
  
  fclose(fi);
    
  display_set_bg_color(0x00000000);
  display_set_dimensions(2100, 480);
  display_set_screen_buffer(displaybuffer);

  scope_display_channel_trace(samples1, 50,  20,  2000, 0x00FFFF00);
#endif

#if 0
  //FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/fnirsi_25ns_samples_5_interleaved_6048_per_buffer.bin", "rb");
  //FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/fnirsi_25ns_samples_6_interleaved_arb_signal.bin", "rb");
  FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/fnirsi_25ns_samples_5_interleaved_6048_per_buffer.bin", "rb");

  
  //Get the bitmap data
  fread(&samples1, 2, 3000, fi);
  
  fclose(fi);
    
//  scope_up_sample_x_25(1500);
//  scope_up_sample_x_2_5(1500);
  
  display_set_bg_color(0x00000000);
  display_set_dimensions(2100, 480);
  display_set_screen_buffer(displaybuffer);

  scope_display_channel_trace(samples1, 50,  20,  2000, 0x00FFFF00);
  
//  scope_up_sample_x_10(&samples1[500], 2000);
  scope_up_sample_x_25(&samples1[750], 2000);

  scope_display_channel_trace(&samples1[750], 50,  220,  2000, 0x00FFFF00);
  
#endif
  
#if 0
  //FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/fnirsi_25ns_samples_4_non_interleaved_3008_per_buffer.bin", "rb");
  FILE *fi = fopen("/home/peter/Downloads/FNIRSI 1013D/Sample_Data/New test data/sine signal/fnirsi_samples_15.bin", "rb");

  u_int32_t buffer_index = 0;
  
  u_int32_t seek_point = 16 * 6080;
  
  fseek(fi, seek_point, SEEK_SET);
  
  //Get the sample data
  fread(&samples1, 2, 1500, fi);
  
  //Point to next buffer
//  fseek(fi, 3008, SEEK_SET);
  fseek(fi, seek_point + 3040, SEEK_SET);

  //Get the sample data
  fread(&samples2, 2, 1500, fi);
  
  fclose(fi);
    
//  scope_up_sample_x_10(1500);
//  scope_up_sample_x_25(1500);
//  scope_up_sample_x_2_5(1500);
  
  display_set_bg_color(0x00000000);
  display_set_dimensions(2100, 480);
  display_set_screen_buffer(displaybuffer);

  scope_display_channel_trace(samples1, 300,  20,  1500, 0x00FFFF00);
  
  scope_display_channel_trace(samples2, 300, 220,  1500, 0x0000FF00);
  
#endif

  u_int32_t file_index = 9;
  u_int32_t buffer_index = 0;
  
  FILE *fi = NULL;
  
  display_set_bg_color(0x00000000);
  display_set_dimensions(2100, 580);
  display_set_screen_buffer(displaybuffer);
  
  open_signal_file(&fi, file_index);
  
  load_display_signal_buffer(fi, buffer_index, file_index);
  
  u_int32_t new_screen = 0;
  u_int32_t new_file = 0;
  
  //--------------------------------------------------------------------------------------------------------------------------------
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        make_image(&xc, &xd, scopedisplay);
				break;
        
			case KeyPress:
				if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
				{
					rflag = 0;
				}
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Right))
        {
          buffer_index++;

          if(buffer_index >= 50)
          {
            buffer_index = 0;
          }

          new_screen = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Left))
        {
          if(buffer_index > 0)
          {
            buffer_index--;
          }
          else
          {
            buffer_index = 49;
          }

          new_screen = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Up))
        {
          file_index++;

          if(file_index >= 30)
          {
            file_index = 9;
          }

          new_file = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Down))
        {
          if(file_index > 9)
          {
            file_index--;
          }
          else
          {
            file_index = 29;
          }

          new_file = 1;
        }

        if(new_file)
        {
          open_signal_file(&fi, file_index);
          
          new_file = 0;
          
          buffer_index = 0;
          new_screen = 1;
        }

        if(new_screen)
        {
          load_display_signal_buffer(fi, buffer_index, file_index);
          make_image(&xc, &xd, scopedisplay);
          
          new_screen = 0;
        }
        break;
        
      case ButtonPress:
        //Call mouse handling function down()
        break;
        
      case ButtonRelease:
        //Call mouse handling function up()
        break;
        
      case MotionNotify:
        //Call mouse handling function move()
        break;
        
      case ClientMessage:
        if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
        {
					rflag = 0;
        }
        break;
		}
	}
  
  if(fi)
  {
    fclose(fi);
  }
  
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void make_image(tagXlibContext *xc, tagXlibDimensions *xd, XImage *scopedisplay)
{
  //Need some scaling algo here to match the scope display to the screen display. The scaling will mostly be one but just in case
  int ix,iy,idx;

  u_int16_t *dptr = displaybuffer;

  for(iy=0;iy<scopedisplay->height;iy++)
  {
    idx = iy * scopedisplay->bytes_per_line;

    for(ix=0;ix<scopedisplay->width;ix++)
    {
      scopedisplay->data[idx + 0] = (unsigned char)(*dptr << 3) & 0x00F8;   //Blue
      scopedisplay->data[idx + 1] = (unsigned char)(*dptr >> 3) & 0x00FC;   //Green
      scopedisplay->data[idx + 2] = (unsigned char)(*dptr >> 8) & 0x00F8;   //Red

      dptr++;

      idx += (scopedisplay->bits_per_pixel / 8);
    }
  }

  //Draw the image on the screen
  XPutImage(xc->display, xc->win, xc->gc, scopedisplay, 0, 0, xd->x, xd->y, xd->width, xd->height);
}

//----------------------------------------------------------------------------------------------------------------------------------

void load_display_signal_buffer(FILE *fp, u_int32_t index, u_int32_t file_index)
{
  char file_name[256];
  
  snprintf(file_name, 256, "signals/fnirsi_samples_%d.bin", file_index);
  
  display_set_fg_color(0x00000000);
  display_fill_rect(0, 0, 2100, 580);

  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_5);
  display_decimal(20, 15, index);
  
  display_text(200, 15, file_name);
  
  if(fp)
  {
    u_int32_t seek_point = index * 6080;
    
    //Point to the buffer set
    fseek(fp, seek_point, SEEK_SET);

    //Get the sample data
    fread(&samples1, 2, 1500, fp);

    //Point to next buffer
    fseek(fp, seek_point + 3040, SEEK_SET);

    //Get the sample data
    fread(&samples2, 2, 1500, fp);

    scope_display_channel_trace(samples1, 300, 80,  1500, 0x00FFFF00);

    scope_display_channel_trace(samples2, 300, 280,  1500, 0x0000FF00);
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

void open_signal_file(FILE **fp, u_int32_t index)
{
  char file_name[256];

  if(*fp)
  {
    fclose(*fp);
  }
  
  snprintf(file_name, 256, "/home/peter/Downloads/FNIRSI 1013D/Sample_Data/New test data/sine signal/fnirsi_samples_%d.bin", index);
  
  *fp = fopen(file_name, "rb");
}

//----------------------------------------------------------------------------------------------------------------------------------
