
//current file number
//Search into the thumbnail file to find the current one for drawing???
void get_thumbnail_data(uint param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  byte *pbVar8;
  int iVar9;
  
  puVar7 = DAT_8000baf0;    //0x801C374A some buffer
  puVar4 = DAT_8000baec;    //0x8019D5A0 base of settings
  iVar3 = DAT_8000bae4;     //0x802F19CE base of thumbnail data

  uVar6 = 0;
  do
  {
    //File number in thumbnail data needs to be converted for endianess.
    if (CONCAT11(*(undefined *)(DAT_8000bae4 + uVar6),*(undefined *)(DAT_8000bae4 + uVar6 + 1)) == param_1)  //0x802F19CE start of where thumbnail data is loaded
    {
      //when found do this
      iVar5 = DAT_8000bae4 + uVar6;  //0x802F19CE start of where thumbnail data is loaded. Blocks of 400 bytes

      iVar9 = 0x57;  //87 number of samples

      pbVar8 = (byte *)(DAT_8000bae4 + uVar6 + 0x14);  //First 20 bytes are settings (only 10 are used)

      *(ushort *)(DAT_8000baec + 6) = (ushort)*(byte *)(iVar5 + 2);
      *(ushort *)(puVar4 + 0x12) = (ushort)*(byte *)(iVar5 + 3);
      *(ushort *)(puVar4 + 0x26) = (ushort)*(byte *)(iVar5 + 4);
      *(ushort *)(puVar4 + 0x24) = (ushort)*(byte *)(iVar5 + 5);       //
      *puVar4 = *(undefined *)(iVar5 + 6);                             //channel 1 enable

      puVar4[0xc] = *(undefined *)(iVar5 + 7);                         //channel 2 enable
      *(ushort *)(puVar4 + 0x1a) = (ushort)*(byte *)(iVar5 + 8);
      *(ushort *)(puVar4 + 0x1c) = (ushort)*(byte *)(iVar5 + 9);
      *(undefined *)(DAT_8000baf4 + 7) = *(undefined *)(iVar5 + 10);

      //copy channel 1 data to buffer
      *puVar7 = (ushort)*pbVar8;

      bVar1 = pbVar8[1];
      do
      {
        bVar2 = pbVar8[2];
        iVar9 = iVar9 + -1;
        puVar7[1] = (ushort)bVar1;
        bVar1 = pbVar8[3];
        puVar7 = puVar7 + 2;
        *puVar7 = (ushort)bVar2;
        pbVar8 = pbVar8 + 2;
      } while (iVar9 != 0);

      pbVar8 = (byte *)(iVar3 + uVar6 + 200);                       //channel 2 data

      *DAT_8000baf8 = (ushort)*(byte *)(iVar3 + uVar6 + 0xc3);    //0x801C38A8

      puVar7 = DAT_8000bafc;                                      //0x801C3F1A
      iVar5 = 0x57;
      *DAT_8000bafc = (ushort)*pbVar8;
      bVar1 = pbVar8[1];
      do {
        bVar2 = pbVar8[2];
        iVar5 = iVar5 + -1;
        puVar7[1] = (ushort)bVar1;
        bVar1 = pbVar8[3];
        puVar7 = puVar7 + 2;
        *puVar7 = (ushort)bVar2;
        pbVar8 = pbVar8 + 2;
      } while (iVar5 != 0);
      *DAT_8000bb00 = (ushort)*(byte *)(iVar3 + uVar6 + 0x177);    //0x801C4078
      return;
    }
    uVar6 = uVar6 + 400;
  } while (uVar6 < DAT_8000bae8);
  return;
}


