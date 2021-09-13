
//Part from touch handler

      iVar11 = 1;

      iVar9 = FUN_80017790();    //check on valid touch

      puVar4 = PTR_DAT_8001ac50;

      iVar8 = DAT_8001ac4c;   //0x8019D5A0

      if (iVar9 != 0)    //check on valid touch
      {
        return;
      }

      uVar2 = *(ushort *)(PTR_DAT_8001ac50 + 0x30);  //y touch

      uVar3 = *(ushort *)(PTR_DAT_8001ac50 + 0x34);  //prev y touch

      if (*(char *)(DAT_8001ac4c + 0x16) != '\0')    //Move speed to set the divider
      {
        iVar11 = 5;
      }

      if (uVar2 < uVar3)
      {
        iVar9 = divide((uint)(ushort)(uVar3 - uVar2),iVar11);

        uVar10 = iVar9 + (uint)*(ushort *)(puVar4 + 0xc);  //saved trigger level

        bVar12 = 0x18b < uVar10;

        if (bVar12)
        {
          uVar10 = 0x18c;
        }

        uVar7 = (undefined2)uVar10;

        if (bVar12)
        {
          *(undefined2 *)(iVar8 + 0x26) = uVar7;  //actual trigger level
          return;
        }
      }
      else
      {
        iVar9 = divide((uint)(ushort)(uVar2 - uVar3),iVar11);
        uVar10 = (uint)*(ushort *)(puVar4 + 0xc);
        bVar12 = iVar9 + 6U < uVar10;

        if (bVar12)
        {
          iVar9 = uVar10 - iVar9;
        }

        uVar7 = (undefined2)iVar9;

        if (!bVar12)
        {
          uVar7 = 6;
        }
      }

      *(undefined2 *)(iVar8 + 0x26) = uVar7;
      return;
    }

    if ((*(char *)(iVar8 + 0x3a) != '\0') && (*(byte *)(iVar8 + 10) < 9))
    {
      return;
    }

