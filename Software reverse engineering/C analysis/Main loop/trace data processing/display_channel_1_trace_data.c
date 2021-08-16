


void FUN_80012a64(int param_1,uint param_2,int param_3,int param_4,uint param_5)

{
  int *piVar1;
  ushort uVar2;
  uint uVar3;
  ushort *puVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar11;
  
  uVar2 = convert_color(param_5);
  piVar1 = Global_Frame_Buffer_Pointer;
  iVar7 = param_2 + param_3 + -1;
  uVar3 = param_2;

  if ((int)param_2 < iVar7)
  {
    do
    {
      puVar5 = (ushort *)(param_4 + uVar3 * 2);
      uVar9 = (uint)*puVar5;
      uVar10 = (uint)puVar5[1];
      uVar8 = uVar9 + uVar10 >> 1;
      if (uVar10 <= uVar9 && uVar9 != uVar10)
      {
        if (uVar10 + 10 < uVar9)
        {
          if (uVar10 <= uVar9)
          {
            iVar6 = *piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2;
            bVar11 = (uVar9 - uVar10 & 1) == 0;
            puVar5 = (ushort *)(iVar6 + -0x63e);
            if (bVar11)
            {
              puVar5 = (ushort *)(iVar6 + 2);
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar8 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }
        }
        else
        {
          if (uVar10 <= uVar8)
          {
            bVar11 = (uVar8 - uVar10 & 1) == 0;
            iVar6 = *piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2;
            puVar5 = (ushort *)(iVar6 + -0x63e);

            if (bVar11)
            {
              puVar5 = (ushort *)(iVar6 + 2);
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar10 = (uVar8 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar10 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar10 = uVar10 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }

          if (uVar8 <= uVar9)
          {
            bVar11 = (uVar9 - uVar8 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar8 * 800 + uVar3) - param_2) * 2);
            puVar5 = puVar4 + -800;

            if (bVar11)
            {
              puVar5 = puVar4;
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar8 = (uVar9 - uVar8) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }
        }
      }
      else
      {
        if (uVar10 <= uVar9)
        {
          puVar5 = (ushort *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
          *puVar5 = uVar2;
          puVar5[1] = uVar2;
        }
        else
        {
          if (uVar9 + 10 < uVar10)
          {
            bVar11 = (uVar10 - uVar9 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
            puVar5 = puVar4 + -800;

            if (bVar11)
            {
              puVar5 = puVar4;
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar8 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }
          else
          {
            if (uVar9 <= uVar8)
            {
              puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2);
              bVar11 = (uVar8 - uVar9 & 1) == 0;
              puVar5 = puVar4 + -800;

              if (bVar11)
              {
                puVar5 = puVar4;
              }

              if (bVar11)
              {
                *puVar5 = uVar2;
              }

              uVar9 = (uVar8 - uVar9) * 0x8000 + 0x8000 >> 0x10;

              while (uVar9 != 0)
              {
                puVar5[800] = uVar2;
                puVar5 = puVar5 + 0x640;
                uVar9 = uVar9 - 1 & 0xffff;
                *puVar5 = uVar2;
              }
            }

            if (uVar8 <= uVar10)
            {
              bVar11 = (uVar10 - uVar8 & 1) == 0;
              iVar6 = *piVar1 + ((param_1 + uVar8 * 800 + uVar3) - param_2) * 2;
              puVar5 = (ushort *)(iVar6 + -0x63e);

              if (bVar11)
              {
                puVar5 = (ushort *)(iVar6 + 2);
              }

              if (bVar11)
              {
                *puVar5 = uVar2;
              }

              uVar8 = (uVar10 - uVar8) * 0x8000 + 0x8000 >> 0x10;
 
              while (uVar8 != 0)
              {
                puVar5[800] = uVar2;
                puVar5 = puVar5 + 0x640;
                uVar8 = uVar8 - 1 & 0xffff;
                *puVar5 = uVar2;
              }
            }
          }
        }
      }

      uVar3 = uVar3 + 1 & 0xfffeffff;
    } while ((int)uVar3 < iVar7);
  }

  iVar7 = param_2 + param_3 + -2;
  uVar3 = param_2;

  if (iVar7 <= (int)param_2)
  {
    return;
  }

  do
  {
    puVar5 = (ushort *)(param_4 + uVar3 * 2);
    uVar8 = (uint)*puVar5;
    uVar9 = (uint)puVar5[1];

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
          iVar6 = *piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2;
          puVar5 = (ushort *)(iVar6 + -0x63e);

          if (bVar11)
          {
            puVar5 = (ushort *)(iVar6 + 2);
          }

          if (bVar11)
          {
            *puVar5 = uVar2;
          }

          uVar8 = (uVar8 - uVar9) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar5[800] = uVar2;
            puVar5 = puVar5 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar5 = uVar2;
          }
        }
      }
      else
      {
        if (uVar9 <= uVar10)
        {
          bVar11 = (uVar10 - uVar9 & 1) == 0;
          iVar6 = *piVar1 + ((param_1 + uVar9 * 800 + uVar3) - param_2) * 2;
          puVar5 = (ushort *)(iVar6 + -0x63e);

          if (bVar11)
          {
            puVar5 = (ushort *)(iVar6 + 2);
          }

          if (bVar11)
          {
            *puVar5 = uVar2;
          }

          uVar9 = (uVar10 - uVar9) * 0x8000 + 0x8000 >> 0x10;

          while (uVar9 != 0)
          {
            puVar5[800] = uVar2;
            puVar5 = puVar5 + 0x640;
            uVar9 = uVar9 - 1 & 0xffff;
            *puVar5 = uVar2;
          }
        }

        if (uVar10 <= uVar8)
        {
          bVar11 = (uVar8 - uVar10 & 1) == 0;
          puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2);
          puVar5 = puVar4 + -800;

          if (bVar11)
          {
            puVar5 = puVar4;
          }

          if (bVar11)
          {
            *puVar5 = uVar2;
          }

          uVar8 = (uVar8 - uVar10) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar5[800] = uVar2;
            puVar5 = puVar5 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar5 = uVar2;
          }
        }
      }
    }
    else
    {
      if (uVar9 <= uVar8)
      {
        puVar5 = (ushort *)(*piVar1 + ((param_1 + uVar8 * 800 + uVar3) - param_2) * 2);
        *puVar5 = uVar2;
        puVar5[1] = uVar2;
      }
      else
      {
        if (uVar8 + 10 < uVar9)
        {
          bVar11 = (uVar9 - uVar8 & 1) == 0;
          puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar8 * 800 + uVar3) - param_2) * 2);
          puVar5 = puVar4 + -800;

          if (bVar11)
          {
            puVar5 = puVar4;
          }

          if (bVar11)
          {
            *puVar5 = uVar2;
          }

          uVar8 = (uVar9 - uVar8) * 0x8000 + 0x8000 >> 0x10;

          while (uVar8 != 0)
          {
            puVar5[800] = uVar2;
            puVar5 = puVar5 + 0x640;
            uVar8 = uVar8 - 1 & 0xffff;
            *puVar5 = uVar2;
          }
        }
        else
        {
          if (uVar8 <= uVar10)
          {
            bVar11 = (uVar10 - uVar8 & 1) == 0;
            puVar4 = (ushort *)(*piVar1 + ((param_1 + uVar8 * 800 + uVar3) - param_2) * 2);
            puVar5 = puVar4 + -800;

            if (bVar11)
            {
              puVar5 = puVar4;
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar8 = (uVar10 - uVar8) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }

          if (uVar10 <= uVar9)
          {
            bVar11 = (uVar9 - uVar10 & 1) == 0;
            iVar6 = *piVar1 + ((param_1 + uVar10 * 800 + uVar3) - param_2) * 2;
            puVar5 = (ushort *)(iVar6 + -0x63e);

            if (bVar11)
            {
              puVar5 = (ushort *)(iVar6 + 2);
            }

            if (bVar11)
            {
              *puVar5 = uVar2;
            }

            uVar8 = (uVar9 - uVar10) * 0x8000 + 0x8000 >> 0x10;

            while (uVar8 != 0)
            {
              puVar5[800] = uVar2;
              puVar5 = puVar5 + 0x640;
              uVar8 = uVar8 - 1 & 0xffff;
              *puVar5 = uVar2;
            }
          }
        }
      }
    }

    uVar3 = uVar3 + 1 & 0xfffeffff;
  } while ((int)uVar3 < iVar7);

  return;
}

