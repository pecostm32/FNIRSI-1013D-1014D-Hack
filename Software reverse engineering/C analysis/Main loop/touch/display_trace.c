


void display_trace(uint xstart,uint offset,uint samples,byte *buffer,uint color)

{
  int *piVar1;
  ushort uVar2;
  uint uVar3;
  ushort *puVar4;
  int iVar5;
  ushort *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar11;
  
  uVar2 = convert_color(color);           //Trace color

  piVar1 = Global_Frame_Buffer_Pointer;   //Where to display
  iVar7 = offset + samples + -1;          //Last count
  uVar3 = offset;                         //count

  if ((int)offset < iVar7)
  {
    do
    {
      uVar9 = (uint)*(ushort *)(buffer + uVar3 * 2);                //First sample
      uVar10 = (uint)*(ushort *)((int)(buffer + uVar3 * 2) + 2);    //Second sample
      uVar8 = uVar9 + uVar10 >> 1;                                  //Average sample

      //This is similar to what is done in the long time base trace drawing.
      //when there is a large step it draws the line straight up.
      if (uVar10 <= uVar9 && uVar9 != uVar10)                       //Line going down
      {
        if (uVar10 + 10 < uVar9)
        {
          if (uVar10 <= uVar9)
          {
            iVar5 = *piVar1 + ((xstart + uVar10 * 800 + uVar3) - offset) * 2;
            bVar11 = (uVar9 - uVar10 & 1) == 0;
            puVar6 = (ushort *)(iVar5 + -0x63e);

            if (bVar11)
            {
              puVar6 = (ushort *)(iVar5 + 2);
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar8 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }
        }
        else
        {
          //Below average
          if (uVar10 <= uVar8)
          {
            bVar11 = (uVar8 - uVar10 & 1) == 0;
            iVar5 = *piVar1 + ((xstart + uVar10 * 800 + uVar3) - offset) * 2;
            puVar6 = (ushort *)(iVar5 + -0x63e);

            if (bVar11)
            {
              puVar6 = (ushort *)(iVar5 + 2);
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar10 = (uVar8 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar10 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar10 = uVar10 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }

          if (uVar8 <= uVar9)
          {
            bVar11 = (uVar9 - uVar8 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((xstart + uVar8 * 800 + uVar3) - offset) * 2);
            puVar6 = puVar4 + -800;

            if (bVar11)
            {
              puVar6 = puVar4;
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar8 = (uVar9 - uVar8) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }
        }
      }
      else
      {
        //Can only be equal at this point
        if (uVar10 <= uVar9)
        {
          puVar6 = (ushort *)(*piVar1 + ((xstart + uVar9 * 800 + uVar3) - offset) * 2);
          *puVar6 = uVar2;
          puVar6[1] = uVar2;
        }
        else
        {
          //Line going up
          if (uVar9 + 10 < uVar10)
          {
            bVar11 = (uVar10 - uVar9 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((xstart + uVar9 * 800 + uVar3) - offset) * 2);
            puVar6 = puVar4 + -800;

            if (bVar11)
            {
              puVar6 = puVar4;
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar8 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }
          else
          {
            if (uVar9 <= uVar8)
            {
              puVar4 = (ushort *)(*piVar1 + ((xstart + uVar9 * 800 + uVar3) - offset) * 2);
              bVar11 = (uVar8 - uVar9 & 1) == 0;
              puVar6 = puVar4 + -800;

              if (bVar11)
              {
                puVar6 = puVar4;
              }

              if (bVar11)
              {
                *puVar6 = uVar2;
              }

              uVar9 = (uVar8 - uVar9) * 0x8000 + 0x8000 >> 0x10;

              while (uVar9 != 0)
              {
                puVar6[800] = uVar2;
                puVar6 = puVar6 + 0x640;
                uVar9 = uVar9 - 1 & 0xffff;
                *puVar6 = uVar2;
              }
            }

            if (uVar8 <= uVar10)
            {
              bVar11 = (uVar10 - uVar8 & 1) == 0;
              iVar5 = *piVar1 + ((xstart + uVar8 * 800 + uVar3) - offset) * 2;
              puVar6 = (ushort *)(iVar5 + -0x63e);

              if (bVar11)
              {
                puVar6 = (ushort *)(iVar5 + 2);
              }

              if (bVar11)
              {
                *puVar6 = uVar2;
              }

              uVar8 = (uVar10 - uVar8) * 0x8000 + 0x8000 >> 0x10;

              while (uVar8 != 0)
              {
                puVar6[800] = uVar2;
                puVar6 = puVar6 + 0x640;
                uVar8 = uVar8 - 1 & 0xffff;
                *puVar6 = uVar2;
              }
            }
          }
        }
      }

      uVar3 = uVar3 + 1 & 0xfffeffff;
    } while ((int)uVar3 < iVar7);
  }

  iVar7 = offset + samples + -2;
  uVar3 = offset;

  if (iVar7 <= (int)offset)
  {
    return;
  }

  //Repeat the whole deal for the double line
  do
  {
    uVar8 = (uint)*(ushort *)(buffer + uVar3 * 2);
    uVar9 = (uint)*(ushort *)((int)(buffer + uVar3 * 2) + 2);

    if (uVar8 != 0)
    {
      uVar8 = uVar8 - 1 & 0xffff;
    }

    if (uVar9 != 0)
    {
      uVar9 = uVar9 - 1 & 0xffff;
    }

    uVar10 = uVar8 + uVar9 >> 1;

    if (uVar9 <= uVar8 && uVar8 != uVar9)
    {
      if (uVar9 + 10 < uVar8)
      {
        if (uVar9 <= uVar8)
        {
          bVar11 = (uVar8 - uVar9 & 1) == 0;
          iVar5 = *piVar1 + ((xstart + uVar9 * 800 + uVar3) - offset) * 2;
          puVar6 = (ushort *)(iVar5 + -0x63e);

          if (bVar11)
          {
            puVar6 = (ushort *)(iVar5 + 2);
          }

          if (bVar11)
          {
            *puVar6 = uVar2;
          }

          uVar8 = (uVar8 - uVar9) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar6[800] = uVar2;
            puVar6 = puVar6 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar6 = uVar2;
          }
        }
      }
      else
      {
        if (uVar9 <= uVar10)
        {
          bVar11 = (uVar10 - uVar9 & 1) == 0;
          iVar5 = *piVar1 + ((xstart + uVar9 * 800 + uVar3) - offset) * 2;
          puVar6 = (ushort *)(iVar5 + -0x63e);

          if (bVar11)
          {
            puVar6 = (ushort *)(iVar5 + 2);
          }

          if (bVar11)
          {
            *puVar6 = uVar2;
          }

          uVar9 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;

          while (uVar9 != 0)
          {
            puVar6[800] = uVar2;
            puVar6 = puVar6 + 0x640;
            uVar9 = uVar9 - 1 & 0xffff;
            *puVar6 = uVar2;
          }
        }

        if (uVar10 <= uVar8)
        {
          bVar11 = (uVar8 - uVar10 & 1) == 0;
          puVar4 = (ushort *)(*piVar1 + ((xstart + uVar10 * 800 + uVar3) - offset) * 2);
          puVar6 = puVar4 + -800;

          if (bVar11)
          {
            puVar6 = puVar4;
          }

          if (bVar11)
          {
            *puVar6 = uVar2;
          }

          uVar8 = (uVar8 - uVar10) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar6[800] = uVar2;
            puVar6 = puVar6 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar6 = uVar2;
          }
        }
      }
    }
    else
    {
      if (uVar9 <= uVar8)
      {
        puVar6 = (ushort *)(*piVar1 + ((xstart + uVar8 * 800 + uVar3) - offset) * 2);
        *puVar6 = uVar2;
        puVar6[1] = uVar2;
      }
      else
      {
        if (uVar8 + 10 < uVar9)
        {
          bVar11 = (uVar9 - uVar8 & 1) == 0;
          puVar4 = (ushort *)(*piVar1 + ((xstart + uVar8 * 800 + uVar3) - offset) * 2);
          puVar6 = puVar4 + -800;

          if (bVar11)
          {
            puVar6 = puVar4;
          }

          if (bVar11)
          {
            *puVar6 = uVar2;
          }

          uVar8 = (uVar9 - uVar8) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar6[800] = uVar2;
            puVar6 = puVar6 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar6 = uVar2;
          }
        }
        else
        {
          if (uVar8 <= uVar10)
          {
            bVar11 = (uVar10 - uVar8 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((xstart + uVar8 * 800 + uVar3) - offset) * 2);
            puVar6 = puVar4 + -800;

            if (bVar11)
            {
              puVar6 = puVar4;
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar8 = (uVar10 - uVar8) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }

          if (uVar10 <= uVar9)
          {
            bVar11 = (uVar9 - uVar10 & 1) == 0;
            iVar5 = *piVar1 + ((xstart + uVar10 * 800 + uVar3) - offset) * 2;
            puVar6 = (ushort *)(iVar5 + -0x63e);

            if (bVar11)
            {
              puVar6 = (ushort *)(iVar5 + 2);
            }

            if (bVar11)
            {
              *puVar6 = uVar2;
            }

            uVar8 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar6[800] = uVar2;
              puVar6 = puVar6 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar6 = uVar2;
            }
          }
        }
      }
    }

    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while ((int)uVar3 < iVar7);

  return;
}


