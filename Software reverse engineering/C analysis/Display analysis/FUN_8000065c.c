//Is this memcpy ???

//dest, source, size, count

//dest, source, count, ???

undefined8 FUN_8000065c(uint *param_1,uint *param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  uint *puVar2;
  byte *pbVar3;
  uint *puVar4;
  byte bVar5;
  undefined2 uVar6;
  uint uVar7;
  byte bVar8;
  uint in_r12;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  
  if (3 < param_3)
  {
    uVar9 = (uint)param_1 & 3;
    in_r12 = uVar9;

    if (uVar9 != 0)
    {
      bVar5 = *(byte *)param_2;
      puVar2 = (uint *)((int)param_2 + 1);

      if (uVar9 < 3)
      {
        puVar2 = (uint *)((int)param_2 + 2);
        in_r12 = (uint)*(byte *)(uint *)((int)param_2 + 1);
      }

      *(byte *)param_1 = bVar5;
      param_2 = puVar2;

      if (uVar9 < 2)
      {
        param_2 = (uint *)((int)puVar2 + 1);
        bVar5 = *(byte *)puVar2;
      }

      puVar2 = (uint *)((int)param_1 + 1);

      if (uVar9 < 3)
      {
        puVar2 = (uint *)((int)param_1 + 2);
        *(byte *)(uint *)((int)param_1 + 1) = (byte)in_r12;
      }

      param_3 = (param_3 + uVar9) - 4;
      param_1 = puVar2;

      if (uVar9 < 2)
      {
        param_1 = (uint *)((int)puVar2 + 1);
        *(byte *)puVar2 = bVar5;
      }
    }

    param_4 = (uint)param_2 & 3;

    if (param_4 == 0)
    {
      while (uVar9 = param_3 - 0x20, 0x1f < param_3)
      {
        uVar7 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        *param_1 = *param_2;
        param_1[1] = uVar7;
        param_1[2] = uVar10;
        param_1[3] = uVar11;
        param_4 = param_2[4];
        uVar7 = param_2[5];
        uVar10 = param_2[6];
        uVar11 = param_2[7];
        param_2 = param_2 + 8;
        param_1[4] = param_4;
        param_1[5] = uVar7;
        param_1[6] = uVar10;
        param_1[7] = uVar11;
        param_1 = param_1 + 8;
        param_3 = uVar9;
      }

      if ((bool)((byte)(uVar9 >> 4) & 1))
      {
        param_4 = *param_2;
        uVar7 = param_2[1];
        uVar10 = param_2[2];
        uVar11 = param_2[3];
        param_2 = param_2 + 4;
        *param_1 = param_4;
        param_1[1] = uVar7;
        param_1[2] = uVar10;
        param_1[3] = uVar11;
        param_1 = param_1 + 4;
      }

      if ((int)(param_3 << 0x1c) < 0)
      {
        param_4 = *param_2;
        uVar7 = param_2[1];
        param_2 = param_2 + 2;
        *param_1 = param_4;
        param_1[1] = uVar7;
        param_1 = param_1 + 2;
      }

      puVar1 = param_1;
      puVar2 = param_2;

      if ((bool)((byte)(uVar9 >> 2) & 1))
      {
        puVar2 = param_2 + 1;
        param_4 = *param_2;
        puVar1 = param_1 + 1;
        *param_1 = param_4;
      }

      uVar6 = (undefined2)param_4;

      if ((uVar9 & 3) != 0)
      {
        bVar13 = (bool)((byte)(uVar9 >> 1) & 1);
        param_3 = param_3 << 0x1f;
        bVar12 = (int)param_3 < 0;
        puVar4 = puVar2;

        if (bVar13)
        {
          puVar4 = (uint *)((int)puVar2 + 2);
          uVar6 = *(undefined2 *)puVar2;
        }

        puVar2 = puVar4;

        if (bVar12)
        {
          puVar2 = (uint *)((int)puVar4 + 1);
          param_3 = (uint)*(byte *)puVar4;
        }

        puVar4 = puVar1;

        if (bVar13)
        {
          puVar4 = (uint *)((int)puVar1 + 2);
          *(undefined2 *)puVar1 = uVar6;
        }

        puVar1 = puVar4;

        if (bVar12)
        {
          puVar1 = (uint *)((int)puVar4 + 1);
          *(byte *)puVar4 = (byte)param_3;
        }

        return CONCAT44(puVar2,puVar1);
      }

      return CONCAT44(puVar2,puVar1);
    }

    bVar12 = 3 < param_3;
    param_3 = param_3 - 4;

    if (bVar12)
    {
      param_2 = (uint *)((int)param_2 - param_4);
      in_r12 = *param_2;
      puVar2 = param_1;

      if (param_4 == 2)
      {
        do
        {
          puVar1 = param_2;
          param_4 = in_r12 >> 0x10;
          param_2 = puVar1 + 1;
          in_r12 = *param_2;
          bVar12 = 3 < param_3;
          param_3 = param_3 - 4;
          param_4 = param_4 | in_r12 << 0x10;
          param_1 = puVar2 + 1;
          *puVar2 = param_4;
          puVar2 = param_1;
        } while (bVar12);

        param_2 = (uint *)((int)puVar1 + 6);
      }
      else
      {
        if (param_4 < 3)
        {
          do
          {
            puVar1 = param_2;
            param_4 = in_r12 >> 8;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar12 = 3 < param_3;
            param_3 = param_3 - 4;
            param_4 = param_4 | in_r12 << 0x18;
            param_1 = puVar2 + 1;
            *puVar2 = param_4;
            puVar2 = param_1;
          } while (bVar12);

          param_2 = (uint *)((int)puVar1 + 5);
        }
        else
        {
          do
          {
            puVar1 = param_2;
            param_4 = in_r12 >> 0x18;
            param_2 = puVar1 + 1;
            in_r12 = *param_2;
            bVar12 = 3 < param_3;
            param_3 = param_3 - 4;
            param_4 = param_4 | in_r12 << 8;
            param_1 = puVar2 + 1;
            *puVar2 = param_4;
            puVar2 = param_1;
          } while (bVar12);

          param_2 = (uint *)((int)puVar1 + 7);
        }
      }
    }
  }

  bVar8 = (byte)in_r12;
  bVar5 = (byte)param_4;
  bVar13 = (bool)((byte)(param_3 >> 1) & 1);
  param_3 = param_3 << 0x1f;
  bVar12 = (int)param_3 < 0;

  if (bVar13)
  {
    pbVar3 = (byte *)((int)param_2 + 1);
    bVar5 = *(byte *)param_2;
    param_2 = (uint *)((int)param_2 + 2);
    bVar8 = *pbVar3;
  }

  puVar2 = param_2;

  if (bVar12)
  {
    puVar2 = (uint *)((int)param_2 + 1);
    param_3 = (uint)*(byte *)param_2;
  }

  if (bVar13)
  {
    pbVar3 = (byte *)((int)param_1 + 1);
    *(byte *)param_1 = bVar5;
    param_1 = (uint *)((int)param_1 + 2);
    *pbVar3 = bVar8;
  }

  puVar1 = param_1;

  if (bVar12)
  {
    puVar1 = (uint *)((int)param_1 + 1);
    *(byte *)param_1 = (byte)param_3;
  }

  return CONCAT44(puVar2,puVar1);
}

