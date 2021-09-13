//No FF_USE_FASTSEEK
//No FF_FS_TINY

int f_write(void *fp,void *buff,uint btw,uint *bw)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  void *apvStack44 [2];
  
  *bw = 0;

  uVar1 = validate(fp,apvStack44);

  bVar6 = uVar1 == 0;

  if (bVar6)
  {
    uVar1 = (uint)*(byte *)((int)fp + 0x11);
  }

  if (!bVar6 || uVar1 != 0)
  {
    return uVar1;
  }

  if ((*(byte *)((int)fp + 0x10) & 2) == 0)
  {
    return 7;
  }

  uVar1 = *(uint *)((int)fp + 0x14);

  if (uVar1 + btw < uVar1)
  {
    btw = ~uVar1;
  }

  while (btw != 0)
  {
    uVar1 = *(uint *)((int)fp + 0x14);

    if ((uVar1 & 0x1ff) == 0)
    {
      uVar5 = *(ushort *)((int)apvStack44[0] + 10) - 1 & uVar1 >> 9;

      if (uVar5 == 0)
      {
        if (uVar1 == 0)
        {
          iVar2 = *(int *)((int)fp + 8);

          if (iVar2 == 0)
          {
            iVar2 = FUN_8003232c(fp,0);  //create_chain
            goto LAB_80034128;
          }
        }
        else
        {
          iVar2 = FUN_8003232c(fp,*(undefined4 *)((int)fp + 0x18));  //create_chain
LAB_80034128:
          if (iVar2 == 0)
            break;
        }

        if (iVar2 == 1)
          goto LAB_80034214;

        if (iVar2 == -1)
          goto LAB_80034298;

        *(int *)((int)fp + 0x18) = iVar2;

        if (*(int *)((int)fp + 8) == 0)
        {
          *(int *)((int)fp + 8) = iVar2;
        }
      }

      if ((*(byte *)((int)fp + 0x10) & 0x80) != 0)
      {
        iVar2 = FUN_80033320(*(undefined *)((int)apvStack44[0] + 1),(int)fp + 0x28,*(undefined4 *)((int)fp + 0x1c),1);

        if (iVar2 != 0) goto LAB_80034298;
        *(byte *)((int)fp + 0x10) = *(byte *)((int)fp + 0x10) & 0x7f;
      }
      uVar1 = *(int *)((int)fp + 0x18) - 2;
      if (*(int *)((int)apvStack44[0] + 0x18) - 2U <= uVar1) {
LAB_80034214:
        *(undefined *)((int)fp + 0x11) = 2;
        return 2;
      }
      uVar4 = (uint)*(ushort *)((int)apvStack44[0] + 10);
      iVar2 = uVar4 * uVar1 + *(int *)((int)apvStack44[0] + 0x2c);
      if (iVar2 == 0) goto LAB_80034214;
      iVar2 = iVar2 + uVar5;
      uVar1 = btw >> 9;
      if (uVar1 == 0) {
        if (((*(int *)((int)fp + 0x1c) != iVar2) &&
            (*(uint *)((int)fp + 0x14) < *(uint *)((int)fp + 0xc))) &&
           (iVar3 = FUN_80033274(*(undefined *)((int)apvStack44[0] + 1),(int)fp + 0x28,iVar2,1),
           iVar3 != 0)) goto LAB_80034298;
        *(int *)((int)fp + 0x1c) = iVar2;
        goto LAB_800342b4;
      }
      if (uVar4 < uVar5 + uVar1) {
        uVar1 = uVar4 - uVar5;
      }
      iVar3 = FUN_80033320(*(undefined *)((int)apvStack44[0] + 1),buff,iVar2,uVar1);
      if (iVar3 != 0) {
LAB_80034298:
        *(undefined *)((int)fp + 0x11) = 1;
        return 1;
      }
      uVar5 = *(int *)((int)fp + 0x1c) - iVar2;
      if (uVar5 < uVar1) {
        FUN_80035518((int)fp + 0x28,(void *)((int)buff + uVar5 * 0x200),0x200);
        *(byte *)((int)fp + 0x10) = *(byte *)((int)fp + 0x10) & 0x7f;
      }
      uVar1 = uVar1 << 9;
    }
    else {
LAB_800342b4:
      uVar5 = *(ushort *)((int)fp + 0x14) & 0x1ff;
      uVar1 = 0x200 - uVar5;
      if (btw < uVar1) {
        uVar1 = btw;
      }
      FUN_80035518((int)fp + uVar5 + 0x28,buff,uVar1);
      *(byte *)((int)fp + 0x10) = *(byte *)((int)fp + 0x10) | 0x80;
    }
    btw = btw - uVar1;
    *bw = *bw + uVar1;
    buff = (void *)((int)buff + uVar1);
    uVar1 = *(int *)((int)fp + 0x14) + uVar1;
    *(uint *)((int)fp + 0x14) = uVar1;
    if (uVar1 <= *(uint *)((int)fp + 0xc)) {
      uVar1 = *(uint *)((int)fp + 0xc);
    }
    *(uint *)((int)fp + 0xc) = uVar1;
  }
  *(byte *)((int)fp + 0x10) = *(byte *)((int)fp + 0x10) | 0x40;
  return 0;
}

